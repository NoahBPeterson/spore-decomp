// src/game/SPGonzago/SPCommonBehaviorTreeUtil.cpp -- migrated from slice(s) s00d9af60, s00d99ff0, s00d990a0 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPCommonBehaviorTreeUtil.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "cSPVector3.h"
#include "nSPBehaviorTree/behavior_stimuli.h"
#include "SP/cActionCircle.h"
#include "SP/cAnimState.h"
#include "SP/cCombatant.h"
#include "SP/cLocomotiveObject.h"
#include "SP/cPlanetModel.h"
#include "SP/cSPCreatureBase.h"
#include "SP/cSpatialObject.h"
#include <math.h>
#include "SP/cGameNounManager.h"

// ---- items of slice s00d990a0 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define VSLOT(n) virtual void _v##n();
struct Vector3 {
    float x, y, z;
};
class cCreatureStatus {
public:
    uint8_t mOpaque[0x75];
    bool mIsAlive;                                                    // +0x75
};
class cCreatureOwner {
public:
    VSLOT(0) VSLOT(1) VSLOT(2) VSLOT(3) VSLOT(4) VSLOT(5) VSLOT(6) VSLOT(7) VSLOT(8) VSLOT(9)
    VSLOT(10)
    virtual bool IsUnavailable();                                     // +0x2c
};
class cLocomotiveObject {
public:
    bool IsNearGoal();                                                // 0x00c42e20
    uint8_t mOpaque[0x60];
};
class cCombatant {
public:
    int32_t GetDamageState();                                         // 0x008e7f80 (reads +0x34)
    uint8_t mOpaque[0x15];                                            // +0x00 .. +0x14
};
class cAnimState {
public:
    uint8_t mPad00[8];
    float mfProgress;                                                 // +0x08
};
class cAnimationPlayer {
public:
    cAnimState* Play(uint32_t nAnimID, uint32_t nFlags);              // 0x00bc96a0
};
class cAnimation {
public:
    uint8_t mPad00[8];
    cAnimationPlayer mPlayer;                                         // +0x08
};
class cActionSlot {
public:
    uint32_t mField00;                                                // +0x00
    void* mpField04;                                                  // +0x04
    uint8_t mPad08[4];
    Vector3 mPos;                                                     // +0x0c
};
class cActionCircle {
public:
    uint8_t mPad00[0x14];
    Vector3 mPos;                                                     // +0x14
    uint8_t mPad20[0x30];                                             // +0x20 .. +0x4f
    cActionSlot* mpBegin;                                             // +0x50
    cActionSlot* mpEnd;                                               // +0x54
    uint8_t mPad58[0x0c];                                             // +0x58 .. +0x63
    cActionSlot* SlotAt(uint32_t nIndex);                             // 0x00af9ff0
};
class cCreatureTree {
public:
    uint8_t mPad000[0x220];
    cActionCircle* mpCircles;                                         // +0x220
};
class cSPCreatureBase {
public:
    VSLOT(0) VSLOT(1)
    virtual cCreatureStatus* GetStatus();                             // +0x08
    virtual cCreatureOwner* GetOwner();                               // +0x0c
    VSLOT(4) VSLOT(5) VSLOT(6) VSLOT(7)
    virtual uint32_t GetTypeID();                                     // +0x20
    VSLOT(9) VSLOT(10)
    virtual bool IsUnavailable();                                     // +0x2c

    int32_t GetDamageState();                                         // 0x008e7f80 (reads +0x34)
    bool AnimationFinished(int32_t nFlags);                           // 0x00c123f0
    void PlayAnimation(uint32_t nAnimID, int32_t nLoops, int32_t nFlags);  // 0x00c12190

    uint8_t mPad04[0x30];                                             // +0x04 .. +0x33
    int32_t mnDamageState;                                            // +0x34
    float mf38;                                                       // +0x38
    uint8_t mPad3c[0x84];                                             // +0x3c .. +0xbf
    cLocomotiveObject mLocomotive;                                    // +0xc0
    cCombatant mCombatant;                                            // +0x120
    bool mB135;                                                       // +0x135
    uint8_t mPad136[0x472];                                           // +0x136 .. +0x5a7
    uint8_t mB5a8;                                                    // +0x5a8
    uint8_t mPad5a9[0x5a3];                                           // +0x5a9 .. +0xb4b
    cAnimation* mB4c;                                                 // +0xb4c
    uint8_t mPadB50[8];                                               // +0xb50 .. +0xb57
    uint8_t mB58;                                                     // +0xb58 (flags)
    uint8_t mPadB59[5];                                               // +0xb59 .. +0xb5d
    bool mB5e;                                                        // +0xb5e
    uint8_t mPadB5f[0x459];                                           // +0xb5f .. +0xfb7
    cCreatureTree* mFB8;                                              // +0xfb8
};
void* ResolveObject(void* pObject);                                   // 0x00f19200
class cStimulusSource {
public:
    VSLOT(0) VSLOT(1) VSLOT(2)
    virtual cSPCreatureBase* FindObject(uint32_t nStimulusID);        // +0x0c
};
struct cStimulusContext {
    uint8_t mPad00[0x2c];
    cStimulusSource* mpSource;                                        // +0x2c
};
class cStimulusAttrA {
public:
    VSLOT(0)
    VSLOT(1) VSLOT(2) VSLOT(3) VSLOT(4) VSLOT(5) VSLOT(6) VSLOT(7) VSLOT(8) VSLOT(9) VSLOT(10)
    VSLOT(11) VSLOT(12) VSLOT(13) VSLOT(14) VSLOT(15) VSLOT(16) VSLOT(17) VSLOT(18) VSLOT(19)
    VSLOT(20) VSLOT(21) VSLOT(22) VSLOT(23)
    virtual int32_t AddRef();                                         // +0x60
    virtual int32_t Release();                                        // +0x64
};
class cStimulusAttrB {
public:
    virtual int32_t AddRef();                                         // +0x00
    virtual int32_t Release();                                        // +0x04
};
class cStimulusAttrC {
public:
    VSLOT(0)
    virtual int32_t AddRef();                                         // +0x04
    virtual int32_t Release();                                        // +0x08
};
template <class T>
class IntrusivePtr {
public:
    IntrusivePtr& operator=(T* p)
    {
        T* const pOld = mpObject;
        if (p != pOld) {
            if (p)
                p->AddRef();
            mpObject = p;
            if (pOld)
                pOld->Release();
        }
        return *this;
    }
    T* mpObject;                                                      // +0x00
};
extern Vector3 gStimulusDefaultVec;
struct sStimulusRecord {
    cStimulusAttrC* mpC;                                              // +0x00
    cStimulusAttrA* mpA;                                              // +0x04
    cStimulusAttrB* mpB;                                              // +0x08
    Vector3 mOffset;                                                  // +0x0c
    int32_t mField18;                                                 // +0x18
    int32_t mField1c;                                                 // +0x1c
    int32_t mField20;                                                 // +0x20
    float mf24;                                                       // +0x24
};
struct sStimulusAssignment {
    IntrusivePtr<cStimulusAttrA> mpA;                                 // +0x00
    IntrusivePtr<cStimulusAttrB> mpB;                                 // +0x04
    IntrusivePtr<cStimulusAttrC> mpC;                                 // +0x08
    Vector3 mOffset;                                                  // +0x0c
    int32_t mField18;                                                 // +0x18
    int32_t mField1c;                                                 // +0x1c
    int32_t mField20;                                                 // +0x20
    float mf24;                                                       // +0x24
    float mf28;                                                       // +0x28
};
void AssignStimulus(const sStimulusRecord* pSrc, sStimulusAssignment* pDst);  // 0x00d99730
// ---- items of slice s00d990a0 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern Vector3 gStimulusDefaultVec;

// callees this slice defines outside this object (rewrite.py held_callee_protos)
cSPCreatureBase* ExtinguishTarget(cSPCreatureBase* pCreature);  // 0x00d99470 (stays in the slice: not this object's)

// ---- items of slice s00d99ff0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int uint;
void* FUN_00b3d4c0(void);                              // 0x00b3d4c0 (argless global getter)
struct Query     { bool Run(); };                      // 0x00b35bf0
struct Socialable { int GetSocialGoal(); };            // 0x00c0e6a0
struct GoalBlob  { int Query(float* goal, void* cre, void* mem); }; // 0x00ba3f90 (__thiscall, ret 0xc)
int   FUN_00d999d0(void* p);                           // 0x00d999d0
struct Vec3 { float x, y, z; };
struct CreatureTail {
    uint8_t pad00[0xb28];
    Vec3    mCachedFlockGoal;      // +0xb28
};
struct Playable {
    void* Play(int a, int b);              // 0x00bc96a0
    void  ClearAll(int a, int b);          // 0x00bc98f0
};
struct Creature {
virtual void d00();
virtual void d04();
virtual void d08();
virtual void d0c();
virtual void d10();
virtual void d14();
virtual void d18();
virtual void d1c();
virtual void d20();
virtual void d24();
virtual void d28();
virtual void d2c();
virtual void d30();
virtual void d34();
virtual void d38();
virtual void d3c();
virtual void d40();
virtual void d44();
virtual void d48();
virtual void d4c();
virtual void d50();
virtual void d54();
virtual void d58();
virtual void d5c();
virtual void d60();
virtual void d64();
virtual void d68();
virtual void d6c();
virtual void d70();
virtual void d74();
virtual void d78();
virtual void d7c();
virtual void d80();
virtual void d84();
virtual void d88();
virtual void d8c();
virtual void d90();
virtual void d94();
virtual void d98();
virtual void d9c();
virtual void da0();
virtual void da4();
virtual void da8();
virtual void dac();
virtual void db0();
virtual void db4();
virtual void db8();
virtual void dbc();
virtual void dc0();
virtual void dc4();
virtual void dc8();
virtual void dcc();
virtual void dd0();
virtual bool SlotD4();
};
// ---- items of slice s00d99ff0 end

// ---- items of slice s00d9af60 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Creature_s00d9_af60;                       // cSPCreatureBase / cSPCreatureCitizen
struct Loco;                           // cLocomotiveObject, addressed as creature + 0xc0
struct AnimHandle {
    char  pad0[0xc];
    int   mState;         // +0xc
    int   mId;            // +0x10
    int   mKind;          // +0x14
    float mValue;         // +0x18
    int   mExtra;         // +0x1c
};
struct BehaviorStimuli {
    AnimHandle* Play(uint flags, uint a);                 // 0x00bc96a0 (ret 8)
    void        ClearAll(uint flags, uint a);             // 0x00bc98f0 (ret 8)
    void        SetStimulus(uint flags, uint a, float f);// 0x00bc97f0 (ret 0x10)
    void*       GetAny();                                 // 0x00d997e0 (ret)
};
struct GoalTableEntry {               // at behaviour-tree-data + 0x1d0
    char pad0[8];
    int  mKey;                        // +0x08 (== 0x546e8804 when the table is live)
    int  mIndex;                      // +0x0c
};
struct BehaviorTreeData {
    char            pad0[0x8];
    BehaviorStimuli mStimuli;    // +0x08
    char            pad8[0x164 - 0x09];
    char            mTable[1];    // +0x164 (stride-0xac entries, field 0 read by 0x00d9b480)
    char            pad164[0x1d0 - 0x165];
    GoalTableEntry  mGoalTable;   // +0x1d0
};
struct BehaviorMgr;                       // cAgentOrderManager singleton
struct BehaviorMgr {
    AnimHandle* FindNode(uint type, void* fn, void* blk);                          // 0x00bca620 (ret 0xc)
    AnimHandle* AddOrder(uint type, uint size, uint nounId, const char* name);     // 0x00bcb0b0 (ret 0x10)
    void        SetNode(AnimHandle* st, void* creature, void* res, void* fn);      // 0x00bcb480 (ret 0x10)
    void        Activate(int a, int b, void* c, float f, void* d, void* e);        // 0x00bca810 (ret 0x18)
    int         FindSlot(int a, int b, int c, int d);                              // 0x00bca0c0 (ret 0x10)
    Creature_s00d9_af60*   At(int idx);                                                       // 0x00bc9b10 (ret; [ecx+0x14]+idx)
    bool        IsEmpty();                                                         // 0x00bc9b50 (ret)
    char        pad0[0x1a4];
    int         mKey1a4;                                                           // +0x1a4
    int         mKey1a8;                                                           // +0x1a8
};
struct Creature_s00d9_af60 {
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
virtual void s0a();
virtual void s0b();
virtual void s0c();
virtual void s0d();
virtual void s0e();
virtual void s0f();
virtual void s10();
virtual void s11();
virtual void s12();
virtual void s13();
virtual void s14();
virtual void s15();
virtual void s16();
virtual void s17();
virtual void s18();
virtual void s19();
virtual void s1a();
virtual void s1b();
virtual void s1c();
virtual void s1d();
virtual void s1e();
virtual void s1f();
virtual void s20();
virtual void s21();
virtual void s22();
virtual void s23();
virtual void s24();
virtual void s25();
virtual void s26();
virtual void s27();
virtual void s28();
virtual void s29();
virtual void s2a();
virtual void s2b();
virtual void s2c();
virtual void s2d();
virtual void s2e();
virtual void s2f();
virtual void s30();
virtual void s31();
virtual void s32();
virtual void s33();
virtual void s34();
virtual void s35();
virtual void s36();
virtual void s37();
virtual void s38();
virtual void s39();
virtual void s3a();
virtual void s3b();
virtual void s3c();
virtual void s3d();
virtual void s3e();
virtual void s3f();
    virtual void s40();
    virtual void SetTarget(void* o, int a, int b);        // +0x84 (slot 0x84/4)
    virtual void* QueryObj(uint id);                      // +0x18c (slot 0x18c/4)
    char   pad4[0xc - 4];
    float  mX;                                            // +0x0c (compared by 0x00d9b4e0)
    char   pad10[0x34 - 0x10];
    int    mSub34;                                        // +0x34 (agent-order node key)
    char   pad38[0x1a4 - 0x38];
    int    mOrderKey1a4;                                  // +0x1a4
    int    mOrderKey1a8;                                  // +0x1a8 (compared by 0x00d9b2d0)
    char   pad1ac[0xb20 - 0x1ac];
    void*  mpAux;                                         // +0xb20
    char   padb24[0xb28 - 0xb24];
    char   mGroupData[0x20];                              // +0xb28
    BehaviorMgr* mpAgentOrders;                           // +0xb48
    BehaviorTreeData* mpBehaviorTreeData;                 // +0xb4c
    char   padb50[0xb54 - 0xb50];
    int    mpAnimating;                                   // +0xb54 (cAnimatingCreature*)
    uint   mFlagsB58;                                     // +0xb58

    Loco*  GetLoco();                                     // this + 0xc0
    uint   GetNounID();                                   // virtual +0x20
    int    GetSocialGoal();                               // 0x00c0e6a0
    int    GetTribe();                                    // 0x00c22f50 (citizen)
    bool   IsLeader();                                    // 0x00c232d0 (citizen)
    bool   IsAnimFinished(void* h);                       // 0x00c12400 (ret 0x1c)
    uint   InterruptAnim(uint a, int b, int c);           // 0x00c12310
    void   FUN_00c14750(bool v);                          // 0x00c14750
    int    FUN_00c0c1a0();                                // 0x00c0c1a0
};
struct Loco {
    char pad0[0xc0];
};
void*  FUN_00d999d0(int handle);                          // 0x00d999d0 (WatchMemoryBlock)
// ---- items of slice s00d9af60 end

// @ 0x00d99830
bool AssignDefaultStimulus(void* p1, void* p2, void* p3, void* p4, void* p5, sStimulusAssignment* pDst, const sStimulusRecord* pSrc)
{
    if (pDst != 0) {
        pDst->mpA.mpObject = 0;
        pDst->mpB.mpObject = 0;
        pDst->mpC.mpObject = 0;
        pDst->mOffset.x = gStimulusDefaultVec.x;
        pDst->mOffset.y = gStimulusDefaultVec.y;
        pDst->mOffset.z = gStimulusDefaultVec.z;
        pDst->mField18 = 0;
        pDst->mField1c = 0;
        pDst->mField20 = 0;
        pDst->mf24 = 0.0f;
        pDst->mf28 = 0.0f;
    }
    AssignStimulus(pSrc, pDst);
    return true;
}

// @ 0x00d998d0
int32_t QueryStimulus(cStimulusContext* pContext, uint32_t nStimulusID)
{
    if (pContext != 0) {
        cStimulusSource* pSource = pContext->mpSource;
        if (pSource != 0)
            return (int32_t)pSource->FindObject(nStimulusID);
    }
    return 0;
}

// @ 0x00d998f0
void* GetExtinguishAnchor(cSPCreatureBase* pCreature)
{
    if (pCreature != 0 && pCreature->mf38 > 0.0000152587890625f) {
        if (pCreature->GetDamageState() != 2) {
            cCreatureStatus* pStatus = pCreature->GetStatus();
            if (pStatus == 0 || pStatus->mIsAlive) {
                cCreatureOwner* pOwner = pCreature->GetOwner();
                if (pOwner == 0)
                    return pCreature;
                if (!pOwner->IsUnavailable()) {
                    void* pResolved = ResolveObject((void*)pCreature->GetOwner());
                    if (pResolved == 0)
                        return pCreature;
                    cSPCreatureBase* pOther = ExtinguishTarget((cSPCreatureBase*)pResolved);
                    if (pOther == 0)
                        return 0;
                    return &pOther->mB5a8;
                }
            }
        }
    }
    return 0;
}

// @ 0x00d99980
cSPCreatureBase* GetAnimalFromStimulus(cStimulusContext* pContext)
{
    if (pContext != 0) {
        cStimulusSource* pSource = pContext->mpSource;
        if (pSource != 0) {
            cSPCreatureBase* pCreature = pSource->FindObject(0xd0036e08);
            if (pCreature != 0) {
                if (pCreature->mB135 && !pCreature->IsUnavailable() &&
                    (pCreature->mB58 & 4) == 0)
                    return pCreature;
            }
        }
    }
    return 0;
}

// @ 0x00d999d0
cSPCreatureBase* WatchMemoryBlock(cStimulusContext* pContext)
{
    if (pContext != 0) {
        cStimulusSource* pSource = pContext->mpSource;
        if (pSource != 0) {
            cSPCreatureBase* pCreature = pSource->FindObject(0xce9f6639);
            if (pCreature != 0) {
                if (pCreature->mB135 && !pCreature->IsUnavailable())
                    return pCreature;
            }
        }
    }
    return 0;
}

// @ 0x00d9aea0
float FUN_00d9aea0(char* self, void* a2, void* a3, uint flags)
{
    void* r = ((Playable*)(*(char**)(self + 0xb4c) + 8))->Play(0x10000, 0);
    int   mem = FUN_00d999d0(r);
    int   goal = ((Socialable*)self)->GetSocialGoal();
    if (goal == 0) return 0.0f;
    if ((flags & 0x4000000) != 0) return 1.0f;
    Vec3* pcVar3 = &((CreatureTail*)self)->mCachedFlockGoal;
    char* pcVar4 = self;
    int q = ((GoalBlob*)FUN_00b3d4c0())->Query((float*)pcVar3, pcVar4, (void*)mem);
    if (q == 5) {
        ((Playable*)(*(char**)(self + 0xb4c) + 8))->ClearAll(0x10000, 0);
        return 0.0f;
    }
    return 1.0f;
}

// @ 0x00d9af20
float FUN_00d9af20(char* self)
{
    void* r = ((Playable*)(*(char**)(self + 0xb4c) + 8))->Play(0x10000, 0);
    int   mem = FUN_00d999d0(r);
    if (mem == 0) return 0.0f;
    if (((Creature*)self)->SlotD4()) return 1.0f;
    return 0.0f;
}

// @ 0x00d9af60
bool FUN_00d9af60(Creature_s00d9_af60* self, void* param2, uint* out)
{
    AnimHandle* h = self->mpBehaviorTreeData->mStimuli.Play(0x10000, 0);
    int r = (int)FUN_00d999d0((int)h);
    if (r == 0) return false;
    typedef void (__thiscall *LocoFn)(void*);
    void* loco = (void*)((char*)self + 0xc0);
    ((LocoFn)(*(void***)loco)[0xec / 4])(loco);
    typedef void (__thiscall *SetTargetFn)(Creature_s00d9_af60*, void*, int, int);
    ((SetTargetFn)(*(void***)self)[0x84 / 4])(self, (void*)(r + 0x5a8), 1, 0);
    uint v = (uint)self->InterruptAnim(0x6496897, -1, 0);
    *out = v;
    (void)param2;
    return true;
}
