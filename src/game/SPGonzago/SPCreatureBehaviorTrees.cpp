// src/game/SPGonzago/SPCreatureBehaviorTrees.cpp -- migrated from slice(s) s00da5900, s00da49f0, s00da2360, s00d9ec20, s00d9dce0, s00d9bee0, s00d9af60 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPCreatureBehaviorTrees.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "nSPBehaviorTree/behavior_stimuli.h"
#include "SP/cSPCreatureBase.h"
#include "SP/cGameNounManager.h"
#include "SP/cLocomotiveObject.h"
#include <math.h>
#include "SP/cActionCircle.h"
#include "SP/cCommunity.h"
#include "SP/cGameData.h"
#include "SP/cPlanetModel.h"
#include "SP/cSPCreatureCitizen.h"
#include "SP/cSpatialObject.h"
#include <stdlib.h>
#include <string.h>
#include "SP/cBehaviorTreeData.h"
#include "SP/cTribe.h"
#include <new>

// unnamed retail callees and globals (address in the comment)
extern "C" extern float g_f1;            // 0x01485720 (1.0f)
extern "C" extern void* g_p016c7aa4;           // 0x016c7aa4

// ---- items of slice s00d9af60 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int uint;
struct Creature;                       // cSPCreatureBase / cSPCreatureCitizen
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
    Creature*   At(int idx);                                                       // 0x00bc9b10 (ret; [ecx+0x14]+idx)
    bool        IsEmpty();                                                         // 0x00bc9b50 (ret)
    char        pad0[0x1a4];
    int         mKey1a4;                                                           // +0x1a4
    int         mKey1a8;                                                           // +0x1a8
};
struct Creature {
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
struct SocialWidget {
    bool  Check0(int a, int b);              // 0x00e31aa0 (ret 8)
    bool  IsBusy();                          // 0x00e31a90 (ret)
    float Get(int a);                        // 0x00e31a30 (ret 4)
    void  Set(int a, float f);               // 0x00e319d0 (ret 8)
    void  Fade(int a, float f, float g);     // 0x00e32460 (ret 0xc)
    void  Clear(int a);                      // 0x00e324f0 (ret 4)
    void  Reset();                           // 0x00e31c90 (ret)
    void  SetNode(int a);                    // 0x00e31cb0 (ret 4)
};
struct SocialProposeBlock {
    int    mState;                                       // +0x00
    void*  mpTarget;                                     // +0x04
    char   pad8[0x34 - 0x8];
    int    mAux34;                                       // +0x34
    SocialWidget* mpWidget;                              // +0x38
    bool   mbAddAsPosse;                                 // +0x40
    char   pad44[0x58 - 0x44];
    uint   mFlags58;                                     // +0x58

    int RewardPlayer(Creature* c, uint param);           // 0x00d9bc70 (ret 8)
};
void*  SP_NounManager();                                  // 0x00b3d300
void*  NounMgr_GetAvatar(void* mgr);                      // 0x00b1fdb0
void*  SP_GetCurrentGameMode();                           // 0x00b5b800 (returns &DAT_01654c10)
void*  EA_Audio_GetSystemAT();                            // 0x00a206f0
void   FUN_00d39360(uint a, void* b);                     // 0x00d39360
void*  FUN_00d37cb0();                                    // 0x00d37cb0
void   FUN_00f1d430(Creature* c);                         // 0x00f1d430
void   FUN_00c77bf0(int a);                               // 0x00c77bf0
void   FUN_00c756a0(float f, int a);                      // 0x00c756a0
void   NotifyEventFull(float f, int a);                   // 0x00d2e8a0 (2-arg form)
float  FUN_00c03440(int a);                               // 0x00c03440
float  FUN_00c04140(int a);                               // 0x00c04140
void*  FUN_00b3d4c0(void* a, void* b, void* c);           // 0x00b3d4c0 (ret)
AnimHandle* FUN_00ba3f90(void* a, void* b, void* c);      // 0x00ba3f90 (ret 0xc)
void        FUN_00ba48b0(void* a, void* b, void* c);      // 0x00ba48b0 (ret 0xc)
extern "C" extern float g_f1;            // 0x01485720 (1.0f)
extern "C" extern void* g_p016c7aa4;           // 0x016c7aa4
// ---- items of slice s00d9af60 end

// ---- items of slice s00d9bee0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl FUN_00b3d300();                       // SP::NounManager
extern "C" void* __cdecl FUN_00b5b800();                       // SP::GetCurrentGameMode
extern "C" int   __cdecl FUN_00d99470(void* p);
extern "C" float __cdecl FUN_00d99ac0(void* a, void* b, int c);
extern "C" float g_1470f1c;    // 0x01470f1c  2.0f
extern "C" float g_13ec480;    // 0x013ec480  0.2f
extern "C" float g_1468908;    // 0x01468908  2.1f
extern "C" float g_1486110;    // 0x01486110  5.0f
extern "C" float g_147c190;    // 0x0147c190  FLT_MAX
extern "C" float g_1471064;    // 0x01471064  0.5f
extern "C" float g_1582f18;    // 0x01582f18
#pragma warning(disable : 4100)
typedef unsigned int u32;
typedef unsigned char u8;
struct IEmpty {};
template <int N, class B> struct VPad : VPad<N - 1, B> { virtual void vpad(VPad<N, B>*) {} };
template <class B> struct VPad<0, B> : B {};
struct Vec3 {
    float x, y, z;
};
struct cSPCreatureBase;
struct IRefCount {
    virtual void AddRef();                               // +0x00 (slot 0)
    virtual void Release();                              // +0x04 (slot 1)
};
struct ICreatureNoun : VPad<6, IRefCount> {              // slots 0x08..0x1c
    virtual u32 GetNounID();                             // +0x20 (slot 8)
};
struct ICreatureVerb : VPad<24, ICreatureNoun> {         // slots 0x24..0x80
    virtual void* FUN_84(void* p, int a, int b);         // +0x84 (slot 33)
};
struct ICreatureCombat : VPad<11, ICreatureVerb> {       // slots 0x88..0xb0
    virtual void* FUN_b4(int slot);                      // +0xb4 (slot 45)
};
struct ICreatureMisc : VPad<7, ICreatureCombat> {        // slots 0xb8..0xd0
    virtual bool FUN_d4();                               // +0xd4 (slot 53)
};
struct ILocoPos : VPad<11, IEmpty> {
    virtual const Vec3* GetPosition();                   // +0x2c (slot 11)
};
struct ILocoRadius : VPad<17, ILocoPos> {
    virtual float GetRadius();                           // +0x74 (slot 29)
};
struct cLocomotiveObject : VPad<29, ILocoRadius> {
    virtual void FUN_ec();                               // +0xec (slot 59)

    bool  IsNearGoal();                                  // 0x00c42e20
    void* FUN_00c41ec0();                                // 0x00c41ec0  -> object with flags at +0x70
};
struct cLocoGoal {                                       // object returned by FUN_00c41ec0
    u8  pad000[0x70];
    u32 mFlags_70;                                       // +0x70
};
struct behavior_stimuli {
    void* Play(int a, int b);                            // 0x00bc96a0
    void  FUN_00bc97f0(int a, int b, float c, void* d);  // 0x00bc97f0
    void  ClearAll(int a, int b);                        // 0x00bc98f0
    void* GetAny();                                      // 0x00d997e0
};
struct cMemoryBlockSlot {                                // stride 0xc
    bool  mbUsed;                                        // +0x00
    u8    pad01[3];
    void* mpObject;                                      // +0x04
    u32   mExtra;                                        // +0x08
};
struct cMemoryBlock {
    u8              pad000[0x18];
    u32             mCount;                              // +0x18
    u8              pad01c[0x04];
    cMemoryBlockSlot mSlots_20[0x21];                    // +0x20 .. 0x1ac
    cSPCreatureBase* mpOwner;                            // +0x1ac
};
struct cBehaviorTree {
    void*            mpVtbl;                             // +0x00
    u8               pad04[0x04];
    behavior_stimuli mStimuli_08;                        // +0x08
    u8               pad09[0x600 - 0x09];
    cMemoryBlock*    mpBlock_600;                        // +0x600

    void PopFront();                                     // 0x00bcaf40
};
struct cCreatureCombatPart {                             // subobject at creature+0x34
    u8    pad00[0x01];
    void* FUN_00cee330();                                // 0x00cee330
};
struct cSPCreatureBase : ICreatureMisc {
    u8                  pad04[0x34 - 0x04];
    cCreatureCombatPart mCombatPart_34;                  // +0x34
    u8                  pad35[0xc0 - 0x35];
    cLocomotiveObject   mLoco_c0;                        // +0xc0
    u8                  padc4[0xb4c - 0xc4];
    cBehaviorTree*      mpTree_b4c;                      // +0xb4c
    u32                 padb50[0x02];
    u32                 mFlags_b58;                      // +0xb58
    u8                  padb5c[0xfc8 - 0xb5c];
    u32                 mStealthTime_fc8;                // +0xfc8

    void*                  ApplyCombatTarget();          // 0x00c0ee90
    cSPCreatureBase*       GetTargetAsCreature();        // 0x00c0ee70
    void*                  GetSocialGoal();              // 0x00c0e6a0
    void                   MoveToPointAtSpeed(int mode, const Vec3* p, float a, float b);       // 0x00c1c1d0
    void                   MoveToPointAndFacingAtSpeed(int mode, const Vec3* p, const Vec3* dir,
                                                        float a, float b);                        // 0x00c1c5c0
    void*                  PlayAnimation(u32 id, int a, int b);                                  // 0x00c12190
    bool                   AnimationFinished(void* h);                                            // 0x00c12400
    void*                  PlayAnimationWithTarget(u32 id, void* target, int a, int b);           // 0x00c14940
    void*                  PlayAnimationWithTargetPos(u32 id, const Vec3* p, int a);              // 0x00c14910
    void*                  FindSlotByCombatant(int slot, u32* out);                                // 0x00c0fa10
    void                   ApplyWave(float f);                                                    // 0x00c15dc0
};
struct cGameNounManager {
    cSPCreatureBase* GetAvatar();                        // 0x00b1fdb0
};
struct cNounManager {
    void* GetItemID();                                   // 0x00b1f9c0
};
struct cSpeciesDB {
    int FindField10(u32 key);                            // 0x004d4750
};
struct IListItemVtbl : VPad<45, IEmpty> {
    virtual void* FUN_b4(int idx);                       // +0xb4 (slot 45)
};
struct cListItem : IListItemVtbl {
    u8         pad04[0xb20 - 0x04];
    cSpeciesDB* mpDB_b20;                                // +0xb20
};
struct cAbility {                                        // TuningObj-ish, only fields used
    u8    pad000[0x08];
    int   mField_08;                                     // +0x08
    u8    pad0c[0x04];
    u32   mField_10;                                     // +0x10
    u8    pad14[0x104 - 0x14];
    float mFloat_104;                                    // +0x104

    int   GetAt(int i);                                  // 0x004d3cd0
};
struct SOCIAL_RESPOND_memory_block {
    int              mState;                             // +0x00
    cSPCreatureBase* mpTarget;                           // +0x04
    void*            mAnimHandle;                        // +0x08
    int              mSocialIdx;                         // +0x0c
    int              mAbilityType;                       // +0x10
    int              mExpectedAbilityType;               // +0x14
    float            mCountdown;                         // +0x18

    float FUN_00d9c100(cSPCreatureBase* c, cAbility* ability);   // 0x00d9c100
    int   CalculateGroupContribution(cSPCreatureBase* c);        // 0x00d9c020
    static u32 MoveToTarget(cSPCreatureBase* c, u32 idx, int* param3, int* param4);  // 0x00d9bee0
};
// ---- items of slice s00d9bee0 end

// ---- items of slice s00d9dce0 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define nullptr 0
class cPoolObject {
public:
    virtual void Destroy(char bFree);           // slot 0x00
    virtual void AddRef();                      // slot 0x04
};
struct cPoolSlot {
    union {
        uint32_t mnLinkFlags;                   // 0x000
        struct {
            uint32_t mnLink : 30;               // bits 0..29
            uint32_t mbFlag : 1;                // bit 30
            uint32_t mbUsed : 1;                // bit 31
        };
    };
    uint8_t mObject[0x20c];                     // 0x004
};
class cSocialBandPool {
public:
    cPoolObject* GetObject(uint32_t nIndex);
    void ReleaseObject(uint32_t nIndex);
    uint32_t GetNextFreeSlot(uint32_t nIndex);

    cPoolSlot* mpBegin;                         // 0x000
    cPoolSlot* mpEnd;                           // 0x004
    uint8_t mPad008[0x0c];                      // 0x008
    uint32_t mnTailIndex;                       // 0x014
    uint32_t mnHeadIndex;                       // 0x018
};
// ---- items of slice s00d9dce0 end

// ---- items of slice s00d9ec20 begin (TODO(rewrite): local stubs, replace by canonical classes)
#pragma pack(push, 4)
struct Vec3Data { float x, y, z; };
struct Vector3 : Vec3Data {
    Vector3() {}
    Vector3(const Vector3& o) { x = o.x; y = o.y; z = o.z; }
};
void Fd9da80(int* first, int hole, int len, int extra, int v, Vector3 vec); // 0x00d9da80
// ---- items of slice s00d9ec20 end

// ---- items of slice s00da2360 begin (TODO(rewrite): local stubs, replace by canonical classes)
void operator delete[](void* p);   // 0x00f47380
namespace SP {
struct cSPVector3 {
    float x, y, z;
    cSPVector3() {}
    cSPVector3(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    cSPVector3(const cSPVector3& v) { x = v.x; y = v.y; z = v.z; }
    float LengthSquared() const { return x * x + y * y + z * z; }
    cSPVector3 Normalized() const
    {
        float inv = 1.0f / sqrtf(x * x + y * y + z * z + 1e-8f);
        return cSPVector3(inv * x, y * inv, z * inv);
    }
    cSPVector3& operator+=(const cSPVector3& v) { x += v.x; y += v.y; z += v.z; return *this; }
    cSPVector3& operator*=(float s) { x *= s; y *= s; z *= s; return *this; }
    bool operator==(const cSPVector3& v) const { return x == v.x && y == v.y && z == v.z; }
};
}
namespace SP {
inline cSPVector3 operator-(const cSPVector3& a, const cSPVector3& b) { return cSPVector3(a.x - b.x, a.y - b.y, a.z - b.z); }
}
namespace SP {
inline cSPVector3 operator*(const cSPVector3& a, float s) { return cSPVector3(a.x * s, a.y * s, a.z * s); }
}
namespace SP {
inline float Dot(const cSPVector3& a, const cSPVector3& b) { return a.x * b.x + a.y * b.y + a.z * b.z; }
}
namespace SP {
extern const cSPVector3 kZeroVector;   // 0x0169f32c
}
namespace SP {
template<class T, int N> struct FixedVector {
    T*       mpBegin;
    T*       mpEnd;
    T*       mpCapacity;
    uint32_t mAllocator[2];
    int      mBufferHeader;
    T        mBuffer[N];

    __forceinline FixedVector() : mpBegin(mBuffer), mpEnd(mBuffer), mpCapacity(mBuffer + N), mBufferHeader(0) {}
    __forceinline ~FixedVector() { if (mpBegin && ((int*)mpBegin)[-1]) operator delete[](mpBegin); }

    __forceinline uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
    __forceinline bool empty() const { return mpBegin == mpEnd; }
    void DoInsertValue(T* pos, const T& value);   // 0x00b96600
    __forceinline void push_back(const T& value)
    {
        if (mpEnd < mpCapacity) {
            T* p = mpEnd++;
            if (p) *p = value;
        } else {
            DoInsertValue(mpEnd, value);
        }
    }
};
}
namespace SP {
class cPlanetModel_s00da_2360 {
public:
    cSPVector3 DirectionToSurfacePosition(const cSPVector3& dir) const;   // 0x00b815a0
};
}
namespace SP {
cPlanetModel_s00da_2360* PlanetModel();   // 0x00b3d350
}
namespace SP {
class cSpatialObject_s00da_2360 {
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
    virtual const cSPVector3& GetPosition();   // +0x2c
};
}
namespace SP {
class cGameData_s00da_2360 {
public:
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
    virtual uint32_t GetNounID();   // +0x20
};
}
namespace SP {
class cSPCreatureBase_s00da_2360 : public cGameData_s00da_2360 {
public:
    uint32_t pad04[0x2f];
    cSpatialObject_s00da_2360 mSpatial;        // +0xc0
    uint32_t padc4[0x3a1];
    int mBandRole;                  // +0x102c

    enum eSpeedState { kSpeedRun = 2 };
    void MoveToPointAndFacingAtSpeed(eSpeedState speed, const cSPVector3& point,
                                     const cSPVector3& facing, float f1, float f2);   // 0x00c1c5c0
    const cSPVector3& GetPosition() { return mSpatial.GetPosition(); }
};
}
namespace SP {
class cSPCreatureCitizen_s00da_2360 : public cSPCreatureBase_s00da_2360 {
public:
    static const uint32_t NOUN_ID = 0x018eb4b7;
    int GetBandRole();   // 0x00c22dc0 (returns mBandRole, out of line)
};
}
namespace SP {
static const uint32_t kAnimalNounID = 0x018eb45e;
}
namespace SP {
inline cSPCreatureCitizen_s00da_2360* CitizenCast(cSPCreatureBase_s00da_2360* p)
{
    if (p && p->GetNounID() == cSPCreatureCitizen_s00da_2360::NOUN_ID)
        return (cSPCreatureCitizen_s00da_2360*)p;
    return 0;
}
}
namespace SP {
class cCommunity_s00da_2360 {
public:
    cSPCreatureBase_s00da_2360* GetLeader() const;   // 0x00c00650
};
}
namespace SP {
struct cBandSkill {
    float GetSkill(int level);   // 0x00ce6a40
};
}
namespace SP {
extern cBandSkill gBandSkill;    // 0x01581208
}
namespace SP {
struct tSlot_s00da_2360 {                   // cActionCircle::tSlot (0x18 bytes)
    bool mbOccupied;             // +0x0
    uint32_t pad04[2];
    cSPVector3 mPosition;        // +0xc
    void Occupy(cSPCreatureBase_s00da_2360* pCreature);   // 0x00afa030
};
}
namespace SP {
class cActionCircle_s00da_2360 {
public:
    uint32_t pad00[0x14];
    tSlot_s00da_2360* mSlotsBegin;          // +0x50 (mSlots)
    tSlot_s00da_2360* mSlotsEnd;            // +0x54
    int FindNearestFreeSlot(const cSPVector3& point);   // 0x00afa5d0
    tSlot_s00da_2360* GetSlot(int index);                          // 0x00af9ff0
};
}
namespace SP {
struct cSocialBand {
    uint32_t pad00[2];
    cCommunity_s00da_2360* mpCommunity;     // +0x8
    uint32_t pad0c;
    cSPVector3 mStageArea;       // +0x10
    cSPVector3 mStageFacing;     // +0x1c
    uint32_t pad28[0xf];
    cSPCreatureBase_s00da_2360** mMembersBegin;   // +0x64
    cSPCreatureBase_s00da_2360** mMembersEnd;     // +0x68
    uint32_t pad6c[0x22];
    cSPVector3* mBandSectionPositions; // +0xf4 (mpBegin of the 6 section positions)
    uint32_t padf8[0x20];
    cActionCircle_s00da_2360 mActionCircle;       // +0x178
};
}
namespace SP {
typedef FixedVector<cGameData_s00da_2360*, 4> MemberVector;
}
namespace SP {
struct BandSection {
    cSPVector3 mCenter;          // +0x00
    float mDistSq;               // +0x0c
    MemberVector mMembers;       // +0x10

    BandSection() : mCenter(kZeroVector) {}
    __forceinline void Add(cSPCreatureBase_s00da_2360* pCreature)
    {
        mMembers.push_back(pCreature);
        mCenter += pCreature->GetPosition();
    }
};
}
namespace SP {
void SortSectionMembers(cGameData_s00da_2360** first, cGameData_s00da_2360** last, cSPVector3 center);
}
namespace SP {
int __cdecl CompareSectionDistance(const void* a, const void* b);
}
namespace SP {
static const int kNumSectionPositions = 6;
}
// ---- items of slice s00da2360 end

// ---- items of slice s00da49f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct RefCounted {
    void** mpVTable;                                                         // +0x00
    void AddRef()  { ((void(__thiscall*)(void*))mpVTable[0])(this); }
    void Release() { ((void(__thiscall*)(void*))mpVTable[1])(this); }
};
struct cActionCircle {
    uint8_t mData[0x64];                                                     // +0x00
    void* Init();                                                            // 0x00afba10
    cActionCircle* Assign(const cActionCircle* pSrc);                        // 0x00d5d4b0
    cActionCircle* CopyInit(const cActionCircle* pSrc);                      // 0x00c278e0
};
struct VecA {                                                               // +0x064, size 0x14
    void* mpBegin;                                                           // +0x00
    void* mpEnd;                                                             // +0x04
    void* mpCap;                                                             // +0x08
    void* mpField70;                                                         // +0x70
    void* mpField74;                                                         // +0x74
    void* Assign(const VecA* pSrc);                                          // 0x01011cc0
    void  InitBuffer(int nCount, void* pSrcBuf);                             // 0x00b93c60
};
struct VecB {                                                               // +0x078, size 0x10
    void* mpBegin;                                                           // +0x00
    void* mpEnd;                                                             // +0x04
    void* mpCap;                                                             // +0x08
    void* mpField84;                                                         // +0x84
    void* Assign(const VecB* pSrc);                                          // 0x01011cc0
    void  InitBuffer(int nCount, void* pSrcBuf);                             // 0x00b93c60
};
struct VecC {                                                               // +0x08c, size 0x58
    void* mpBegin;                                                           // +0x8c
    void* mpEnd;                                                             // +0x90
    void* mpCap;                                                             // +0x94
    void* mpField98;                                                         // +0x98
    void* mpBufPtr;                                                          // +0x9c
    void* mpFieldA0;                                                         // +0xa0
    uint8_t mBuf[0x40];                                                      // +0xa4
    void* Erase(void* pFirst, void* pLast);                                  // 0x00e25bd0
    void* Assign(void* pFirst, void* pLast, void* pSrcAlloc);                // 0x00bdf600
};
struct VecD {                                                               // +0x0f4, size 0x5c
    void* mpBegin;                                                           // +0xf4
    void* mpEnd;                                                             // +0xf8
    void* mpCap;                                                             // +0xfc
    void* mpField100;                                                        // +0x100
    void* mpField104;                                                        // +0x104
    uint8_t mBuf[0x48];                                                      // +0x108
    void* InitFixed(int n);                                                  // 0x00da1d40
    void* Erase(void* pFirst, void* pLast);                                  // 0x009e0480
    void* Assign(void* pFirst, void* pLast, void* pSrcAlloc);                // 0x00da1250
};
struct VecE {                                                               // +0x150, size 0x28
    void* mpBegin;                                                           // +0x150
    void* mpEnd;                                                             // +0x154
    void* mpCap;                                                             // +0x158
    void* mpField15c;                                                        // +0x15c
    void* mpField160;                                                        // +0x160
    uint8_t mBuf[0x14];                                                      // +0x164
    void* InitFixed(int n);                                                  // 0x00da3b30
    void* Assign(void* pFirst, void* pLast, void* pDest);                    // 0x00da1e70
};
struct VecF {                                                               // +0x1e4, size 0x28
    void* mpBegin;                                                           // +0x1e4
    void* mpEnd;                                                             // +0x1e8
    void* mpCap;                                                             // +0x1ec
    void* mpField1f0;                                                        // +0x1f0
    void* mpBufPtr;                                                          // +0x1f4
    void* mpField1f8;                                                        // +0x1f8
    uint8_t mBuf[0x10];                                                      // +0x1fc
    void* Assign(void* pFirst, void* pLast, void* pDest);                    // 0x00da1f10
};
void FUN_00829110(void* pOut, void* pSrcBegin, void* pSrcEnd, void* pDest, void* pSrc); // 0x00829110
struct cSocialBand_s00da_49f0 {
    void** mpVTable;                                                         // +0x000
    void* mpField04;                                                         // +0x004
    RefCounted* mpField08;                                                   // +0x008
    RefCounted* mpField0c;                                                   // +0x00c
    uint32_t mField10;                                                       // +0x010 (Init leaves 0x10..0x30 untouched)
    uint32_t mField14;                                                       // +0x014
    uint32_t mField18;                                                       // +0x018
    uint32_t mField1c;                                                       // +0x01c
    uint32_t mField20;                                                       // +0x020
    uint32_t mField24;                                                       // +0x024
    uint32_t mField28;                                                       // +0x028
    uint32_t mField2c;                                                       // +0x02c
    uint32_t mField30;                                                       // +0x030
    float mField34;                                                          // +0x034
    float mField38;                                                          // +0x038
    float mField3c;                                                          // +0x03c
    float mField40;                                                          // +0x040
    uint32_t mField44;                                                       // +0x044
    uint32_t mField48;                                                       // +0x048
    float mField4c;                                                          // +0x04c
    uint8_t mField50;                                                        // +0x050
    uint8_t mField51;                                                        // +0x051
    uint8_t mField52;                                                        // +0x052
    uint8_t mPad53;                                                          // +0x053
    float mField54;                                                          // +0x054
    uint8_t mField58;                                                        // +0x058
    uint8_t mPad59[3];                                                       // +0x059
    float mField5c;                                                          // +0x05c
    uint32_t mField60;                                                       // +0x060
    VecA mVecA;                                                              // +0x064
    VecB mVecB;                                                              // +0x078
    uint32_t mField88;                                                       // +0x088
    VecC mVecC;                                                              // +0x08c
    RefCounted* mpFieldE4;                                                   // +0x0e4
    RefCounted* mpFieldE8;                                                   // +0x0e8
    uint32_t mFieldEc;                                                       // +0x0ec
    uint32_t mFieldF0;                                                       // +0x0f0
    VecD mVecD;                                                              // +0x0f4
    VecE mVecE;                                                              // +0x150
    cActionCircle mActionCircle;                                             // +0x178
    int32_t mField1dc;                                                       // +0x1dc
    uint32_t mField1e0;                                                      // +0x1e0
    VecF mVecF;                                                              // +0x1e4

    cSocialBand_s00da_49f0* Init();                                                     // 0x00da4f00 (default ctor)
    cSocialBand_s00da_49f0* CopyInit(const cSocialBand_s00da_49f0* pSrc);                          // 0x00da52e0 (copy ctor)
    cSocialBand_s00da_49f0* Assign(const cSocialBand_s00da_49f0* pSrc);                            // 0x00da5030 (operator=)
};
inline void BandRelease(cSocialBand_s00da_49f0* pBand)
{
    ((void(__thiscall*)(void*, int))pBand->mpVTable[0])(pBand, 0);
}
struct cSocialBandEntry {
    union {
        uint32_t mSlotInfo;                                                  // +0x000 the whole word
        struct {
            uint32_t mSlotIndex : 31;                                        // bits 0..30
            uint32_t mIsEmpty   : 1;                                         // bit 31
        };
    };
    cSocialBand_s00da_49f0 mBand;                                                       // +0x004
    cSocialBandEntry* Assign(const cSocialBandEntry& rhs);                   // 0x00da5550
};
void* FUN_00da55c0(cSocialBandEntry* pFirst, cSocialBandEntry* pLast, cSocialBandEntry* pDest); // 0x00da55c0
void  FUN_00da5620(cSocialBandEntry* pSrcBegin, cSocialBandEntry* pSrcEnd, cSocialBandEntry* pDestEnd); // 0x00da5620
void  FUN_00d9b7f0(cSocialBandEntry* pFirst, cSocialBandEntry* pLast, cSocialBandEntry* pDest);  // 0x00d9b7f0
void* EAAlloc(int nSize, const char* pTag, int n0, int n1, const char* pFile, int nLine); // 0x00f473a0
void  EAFree(void* p);                                                       // 0x00f47380
struct cSocialBandPool_s00da_49f0 {
    cSocialBandEntry* mpBegin;                                               // +0x00
    cSocialBandEntry* mpEnd;                                                 // +0x04
    cSocialBandEntry* mpCap;                                                 // +0x08

    void Reserve(uint n);                                                    // 0x00da5660
    void Insert(cSocialBandEntry* pPos, cSocialBandEntry* pValue);           // 0x00da5720
    void DoInsertEntry();                                                    // 0x00da58a0
};
struct cTuningObj {
    uint8_t mPad00[8];                                                       // +0x00
    int32_t mField08;                                                        // +0x08
    uint8_t mPad0c[4];                                                       // +0x0c
    int32_t mField10;                                                        // +0x10
    uint8_t mPad14[0x28];                                                    // +0x14
    float mField3c;                                                          // +0x3c
    uint32_t GetAt(uint i);                                                  // 0x004d3cd0
};
struct cSPCreatureBase_s00da_49f0;
struct StubField {
    bool FUN_00e31a90();                                                     // 0x00e31a90
};
struct cLocomotiveObject_s00da_49f0 {
    uint8_t mData[0x40];                                                     // +0x00
    bool IsNearGoal();                                                       // 0x00c42e20
};
struct cSocialProgressValues {
    float mField00;                                                          // +0x00
    uint8_t mPad04[4];                                                       // +0x04
    int32_t mField08;                                                        // +0x08
    uint8_t mField0c;                                                        // +0x0c
    uint8_t mField0d;                                                        // +0x0d
    uint8_t mPad0e[2];                                                       // +0x0e
    int32_t mField10;                                                        // +0x10
    uint8_t mPad14[0x0c];                                                    // +0x14

    void Update(float dt, int32_t a, cSPCreatureBase_s00da_49f0* pCreature, cSPCreatureBase_s00da_49f0* pTarget); // 0x00d9ba60
    bool FUN_00d9b010();                                                     // 0x00d9b010
    void FUN_00d9b040(int32_t v);                                            // 0x00d9b040
    void FUN_00d9b090(float v, int32_t anim);                                // 0x00d9b090
};
struct SocialProposeMemoryBlock {
    uint8_t mPad00[4];                                                       // +0x00
    cSPCreatureBase_s00da_49f0* mpField04;                                              // +0x04
    int32_t mField08;                                                        // +0x08
    int32_t mField0c;                                                        // +0x0c
    int32_t mField10;                                                        // +0x10
    int32_t mField14;                                                        // +0x14
    cSocialProgressValues mProgress;                                         // +0x18
    StubField* mpField38;                                                    // +0x38
    int32_t mField3c;                                                        // +0x3c
    uint8_t mField40;                                                        // +0x40
    uint8_t mPad41[3];                                                       // +0x41
    float mField44;                                                          // +0x44
    float mField48;                                                          // +0x48
    int32_t mField4c;                                                        // +0x4c
    int32_t mField50;                                                        // +0x50
    int32_t mField54;                                                        // +0x54
    uint32_t mField58;                                                       // +0x58

    int32_t RewardPlayer(cSPCreatureBase_s00da_49f0* pCreature, cSPCreatureBase_s00da_49f0* pTarget);  // 0x00d9bc70
    void FUN_00d9b230(cSPCreatureBase_s00da_49f0* pCreature, void* pBlock, int32_t anim);   // 0x00d9b230
    void FUN_00d9b110(cSPCreatureBase_s00da_49f0* pCreature);                               // 0x00d9b110
    int32_t SocialRespond_Activate(cSPCreatureBase_s00da_49f0* pCreature, int32_t prev);     // 0x00da3b90
};
struct cSocialProposeBrain {
    uint8_t mPad000[0x1a4];                                                  // +0x00
    SocialProposeMemoryBlock mPropose;                                       // +0x1a4
    bool ShouldSkip();                                                       // 0x00a75010
};
struct BehaviorStimuli_s00da_49f0 {
    void* Play(int flags, int a);                                            // 0x00bc96a0
    void  ClearAll(int flags, int a);                                        // 0x00bc98f0
};
struct cSPCreatureBase_s00da_49f0 {
    void** mpVTable;                                                         // +0x000
    uint8_t mPad004[0xc0 - 4];                                               // +0x004
    cLocomotiveObject_s00da_49f0 mLoco;                                                 // +0x0c0
    uint8_t mPad100[0xb4c - 0x100];                                          // +0x100
    void* mpFieldb4c;                                                        // +0xb4c
    uint8_t mPadb50[0xb5c - 0xb50];                                          // +0xb50
    uint8_t mFieldb5c;                                                       // +0xb5c
    uint8_t mPadb5d[0x1020 - 0xb5d];                                         // +0xb5d
    void** mpField1020;                                                      // +0x1020

    int32_t PlayAnimation(int32_t anim, int a, int b);                       // 0x00c12190
    int32_t InterruptAnimation(int32_t anim, int a, int b);                  // 0x00c12310
    bool    AnimationFinished(int32_t h);                                    // 0x00c12400
    void*   GetTargetAsCreature();                                           // 0x00c0ee70
    bool    CCM_e0c0(int32_t id);                                            // 0x00c0e0c0
};
struct SocialProposeState {
    int32_t mState;                                                          // +0x00
    int32_t mAnimHandle;                                                     // +0x04
    uint8_t mFlag8;                                                          // +0x08
    uint8_t mPad9[3];                                                        // +0x09
    int32_t mField0c;                                                        // +0x0c
};
// ---- items of slice s00da49f0 end

// ---- items of slice s00da5900 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Vec3_s00da_5900 { float x, y, z; Vec3_s00da_5900() {} Vec3_s00da_5900(float a, float b, float c) : x(a), y(b), z(c) {} };
struct Quat { float x, y, z, w; };
void* __cdecl FUN_00d994c0(void* block);           // 0x00d994c0
void* __cdecl FUN_00d999d0(void* block);           // 0x00d999d0: WatchMemoryBlock
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
struct cBehaviorTreeData {
    char             mPad00[8];
    behavior_stimuli_s00da_5900 mStimuli;                     // +0x08
    char             mPad[0x60c - 0x8 - sizeof(behavior_stimuli_s00da_5900)];
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
struct cGameNounManager_s00da_5900 {
    cTribe* GetPlayerTribe();                      // 0x00bfc5f0 (reads +0x70)
};
cGameNounManager_s00da_5900* NounManager();                   // returns FUN_00b3d300()
struct cSocialBand_s00da_5900 {
    cSocialBand_s00da_5900();
    cSocialBand_s00da_5900(const cSocialBand_s00da_5900&);
    ~cSocialBand_s00da_5900();
    void Start(void* a, void* b, void* c, void* d);   // 0x00da1330
    void Bind(void* a);                               // 0x00da1b00
    u32 mData[0x20c / 4];
};
struct cSocialBandEntry_s00da_5900 {
    u32         mFlags;                            // +0x0
    cSocialBand_s00da_5900 mItem;                             // +0x4
};
struct cSocialBandPool_s00da_5900 {
    u8*               mpBegin;                     // +0x0 (byte view of the entry array)
    u8*               mpEnd;                       // +0x4
    char              mPad08[0x14 - 0x8];
    u32               mMinFree;                    // +0x14
    u32               mFreeHead;                   // +0x18

    void DoInsertEntry();                          // 0x00da58a0
    u32  create(const cSocialBand_s00da_5900& item);          // 0x00da5900
    u32  CreateObject();                           // 0x00da5a00
    cSocialBand_s00da_5900* GetObject(u32 index);             // 0x00d9eb70
};
extern cSocialBandPool_s00da_5900 gSocialBandPool;            // 0x015935a8
struct AgentNode {
    char mPad000[0x1a8];
    u32  mBand;                                    // +0x1a8
    char mPad1ac[0x224 - 0x1ac];
    void* mFn224;                                  // +0x224
    void* mFn228;                                  // +0x228
};
struct NodeArgs {
    cTribe* a;
    cTribe* b;
    Vec3_s00da_5900    pos;
};
struct cAgentOrderManager {
    AgentNode* FindNode(u32 id, void* fn, NodeArgs* args);              // 0x00bca620 (ret 0xc)
    AgentNode* CreateNode(u32 id, u32 size, void* fn, const char* name); // 0x00bcb0b0 (ret 0x10)
};
cAgentOrderManager* AgentOrderManager();           // returns FUN_00bc9b00()
void __cdecl FUN_00da05f0();                       // 0x00da05f0
void __cdecl FUN_00d9f130();                       // 0x00d9f130 FindPrimaryAgentForSocialBandGroup
void __cdecl FUN_00d9f0a0();                       // 0x00d9f0a0 FindSocialBandGroup
struct cTribeModeStrategy {
    char mPad00[0x94];
    cSPCreatureCitizen** mpBegin;                  // +0x94
    cSPCreatureCitizen** mpEnd;                    // +0x98
    static cTribeModeStrategy* Instance();         // 0x00cd40b0
};
// ---- items of slice s00da5900 end

// @ 0x00d9b7f0
char* FUN_00d9b7f0(char* first, char* last, char* out)
{
    while (first != last) {
        unsigned f = *(unsigned*)first;
        unsigned bit = f >> 31;
        if (bit == 0) {
            typedef void (__thiscall *RelFn)(void*, int);
            void* obj = first + 4;
            ((RelFn)(*(void***)obj)[0])(obj, 0);
        }
        first += 0x210;
        out += 0x210;
    }
    return out;
}

// @ 0x00d9bc70
int SocialProposeBlock::RewardPlayer(Creature* c, uint param)
{
    int result = -1;
    void* nounMgr = SP_NounManager();
    FUN_00c77bf0((int)nounMgr);
    void* avatar = NounMgr_GetAvatar(SP_NounManager());

    Creature* target;
    if (c == 0) {
        target = 0;
    } else {
        target = (Creature*)c->QueryObj(0xd0036e08);
    }

    void* group = (char*)c + 0xb28;
    AnimHandle* node = FUN_00ba3f90(FUN_00b3d4c0(group, c, (void*)param), c, (void*)param);
    int goal = c->GetSocialGoal();
    if (goal != 0) {
        int m;
        switch ((int)node) {
            case 1:  m = 0xf37db906; break;
            case 2:
            case 5:  m = 0xd37db8f6; break;
            case 3:  m = 0x538bf747; break;
            default: m = 0x738bf75b; break;
        }
        result = m;
        if (goal == 4) mFlags58 |= 0x10;
        FUN_00ba48b0(FUN_00b3d4c0(group, c, (void*)3), (void*)3, c);
        if (goal != 4) {
            float t = mpWidget->Get(1) - 0.5f;
            float frac = (t >= 0.0f) ? t : 0.0f;
            int av = c->FUN_00c0c1a0();
            float dist = FUN_00c03440(*(int*)(av + 0x330)) * *(float*)(av + 0x328) * frac;
            float total = FUN_00c04140(1) + dist;
            NotifyEventFull(total, 1);
            FUN_00c756a0(total, 1);
            int msg[4];
            msg[0] = (int)avatar;
            msg[1] = (int)target;
            msg[2] = 0;
            FUN_00d39360(0x60b4123, msg);
        }
    }
    *(uint*)((char*)c + 0xb58) |= 0x80;
    void* p = FUN_00d37cb0();
    if (p) {
        int* ip = (int*)FUN_00d37cb0();
        typedef void (__thiscall *Fn)(int*, int);
        ((Fn)(*(void***)ip)[0x28 / 4])(ip, 0);
    }
    if (SP_GetCurrentGameMode() == (void*)0x1654c10) {
        int* gd = (int*)g_p016c7aa4;
        FUN_00f1d430((Creature*)*(int*)((char*)gd + 0x78));
    }
    int* audio = (int*)EA_Audio_GetSystemAT();
    if (audio) {
        typedef void (__thiscall *AudioFn)(int*, int);
        ((AudioFn)(*(void***)audio)[0x38 / 4])(audio, 0x3cdd1a9);
        typedef void (__thiscall *AudioFn2)(int*, int, int);
        ((AudioFn2)(*(void***)audio)[0x40 / 4])(audio, 0x34753a7, 0x8da68d69);
        typedef void (__thiscall *AudioFn3)(int*, int, float);
        ((AudioFn3)(*(void***)audio)[0x3c / 4])(audio, 0x34753aa, g_f1);
        typedef void (__thiscall *AudioFn4)(int*);
        ((AudioFn4)(*(void***)audio)[0x58 / 4])(audio);
    }
    mpWidget->Reset();
    int n = (int)FUN_00ba3f90(FUN_00b3d4c0(group, c, (void*)param), c, (void*)param);
    mpWidget->SetNode(n);
    return result;
}

// @ 0x00d9bee0
u32 SOCIAL_RESPOND_memory_block::MoveToTarget(cSPCreatureBase* c, u32 idx, int* param3, int* param4)
{
    int entries = *param4;                                     // *param_4 : array of creature ptrs
    int recs = *param3;                                        // *param_3 : array of 0x20-byte records
    u32 off = idx << 5;
    cSPCreatureBase* cur = *(cSPCreatureBase**)(entries + *(int*)(recs + off) * 4);

    while (cur != 0) {
        float fr = *(float*)(recs + off + 0x1c);
        const Vec3* p = cur->mLoco_c0.GetPosition();
        float dz = p->z - *(float*)(recs + off + 0x18);
        float dx = p->x - *(float*)(recs + off + 0x10);
        float dy = p->y - *(float*)(recs + off + 0x14);
        if (!((dz * dz + dx * dx) + dy * dy <= fr + g_13ec480))
            break;
        idx = idx + 1;
        off = off + 0x20;
        if (idx > 2)
            return 0xffffffff;
        recs = *param3;
        entries = *param4;
        cur = *(cSPCreatureBase**)(entries + *(int*)(recs + off) * 4);
    }

    off = idx << 5;
    int k = *(int*)(*param3 + off);
    int tbl = *param4;
    cSPCreatureBase* old = *(cSPCreatureBase**)(tbl + k * 4);
    if (c != old) {
        if (c != 0)
            c->AddRef();
        *(cSPCreatureBase**)(tbl + k * 4) = c;
        if (old != 0)
            old->Release();
    }
    c->MoveToPointAtSpeed(2, (const Vec3*)(*param3 + off + 0x10), 1.0f, g_1470f1c);
    return *(u32*)(*param3 + off);
}

// @ 0x00d9c020
int SOCIAL_RESPOND_memory_block::CalculateGroupContribution(cSPCreatureBase* c)
{
    cLocomotiveObject* thisLoco = &c->mLoco_c0;
    cLocomotiveObject* tgtLoco = &mpTarget->mLoco_c0;
    (void)thisLoco->GetPosition();
    (void)tgtLoco->GetPosition();
    float tr = tgtLoco->GetRadius();
    float sr = thisLoco->GetRadius();
    float s = sr + tr + g_1470f1c;
    if ((c->mFlags_b58 >> 8) & 1) {
        cSPCreatureBase* av = ((cGameNounManager*)FUN_00b3d300())->GetAvatar();
        float ar = av->mLoco_c0.GetRadius();
        s = ar + ar + s;
    }
    sr = thisLoco->GetRadius();
    float r = sr + s;
    const Vec3* p = tgtLoco->GetPosition();
    c->MoveToPointAtSpeed(2, p, s, r);
    cLocoGoal* g = (cLocoGoal*)thisLoco->FUN_00c41ec0();
    g->mFlags_70 |= 2;
    return (int)&g->mFlags_70;
}

// @ 0x00d9c100
float SOCIAL_RESPOND_memory_block::FUN_00d9c100(cSPCreatureBase* c, cAbility* ability)
{
    u32 fl = c->mFlags_b58;
    if ((fl >> 9) & 1) {
        float r = *(float*)((u8*)ability + 0x3c);
        void* v = ((cNounManager*)FUN_00b3d300())->GetItemID();
        cListItem** begin = *(cListItem***)v;
        cListItem** end = *(cListItem***)((u8*)v + 4);
        for (cListItem** it = begin; it != end; ++it) {
            cListItem* e = *it;
            int f = e->mpDB_b20->FindField10(ability->mField_10);
            if (f != -1 && e->FUN_b4(f))
                r += *(float*)((u8*)ability + 0x3c) * g_1582f18;
        }
        return r;
    }
    return 0.0f;
}

// @ 0x00d9c1a0
bool __cdecl SOCIAL_RESPOND_Tick(cSPCreatureBase* c, int, int, int, int, SOCIAL_RESPOND_memory_block* b, int, float dt)
{
    if (c->GetTargetAsCreature() != b->mpTarget || FUN_00d99470(b->mpTarget) == 0)
        return false;
    if ((c->mFlags_b58 >> 8) & 1) {
        cSPCreatureBase* av = ((cGameNounManager*)FUN_00b3d300())->GetAvatar();
        if (av->GetTargetAsCreature() != b->mpTarget)
            return false;
    }
    switch (b->mState) {
    case 0: {                                       // kToTarget
        float t = b->mCountdown - dt;
        b->mCountdown = t;
        bool arrived = false;
        if (t < 0.0f) {
            b->mCountdown = g_1471064;
            b->CalculateGroupContribution(c);
            arrived = true;
        }
        cSPCreatureBase* tg = b->mpTarget;
        void* tl = tg ? (void*)&tg->mLoco_c0 : 0;
        float d = FUN_00d99ac0(&c->mLoco_c0, tl, 1);
        if (d < g_1468908 || (arrived && c->mLoco_c0.IsNearGoal())) {
            c->mLoco_c0.FUN_ec();
            if ((c->mFlags_b58 >> 9) & 1) {
                if (FUN_00b5b800() == (void*)0x1654c10)
                    b->mAnimHandle = c->PlayAnimation(0x7a3d058, 1, -1);
                else
                    b->mAnimHandle = c->PlayAnimation(0xb4212a07, 1, -1);
                b->mState = 1;
                return true;
            }
            b->mState = 2;
            return true;
        }
        break;
    }
    case 1:                                         // kInitiating
        if (c->AnimationFinished(b->mAnimHandle)) {
            b->mAnimHandle = 0;
            cBehaviorTree* tt = b->mpTarget->mpTree_b4c;
            tt->mStimuli_08.FUN_00bc97f0(0x10000, 0, g_1486110, c);
            void* p = tt->mStimuli_08.Play(0x10000, 0);
            *(int*)((u8*)p + 0xc) = 1;
            if (b->mpTarget->FUN_d4() && b->mpTarget->GetSocialGoal() == 0)
                return false;
            b->mState = 2;
            return true;
        }
        break;
    case 2: {                                       // kWatching
        void* p = c->mpTree_b4c->mStimuli_08.Play(0x10000000, 0);
        if (p == 0 || *(int*)((u8*)p + 0xc) != 0)
            break;
        u32 social = *(u32*)((u8*)p + 0x10);
        b->mSocialIdx = (int)social;
        if (social == 0xffffffff) {
            c->mpTree_b4c->mStimuli_08.ClearAll(0x10000000, 0);
            return true;
        }
        cAbility* ab = (cAbility*)c->FUN_b4((int)social);
        b->mAnimHandle = c->PlayAnimation(ab->GetAt(0), 1, -1);
        b->mAbilityType = ab->mField_08;
        b->mExpectedAbilityType = (int)ab->mField_10;
        b->mState = 3;
        if ((c->mFlags_b58 >> 9) & 1) {
            c->ApplyWave(ab->mFloat_104);
            cBehaviorTree* tt = b->mpTarget->mpTree_b4c;
            tt->mStimuli_08.FUN_00bc97f0(0x10000000, 0, g_147c190, 0);
            void* np = tt->mStimuli_08.Play(0x10000000, 0);
            *(int*)((u8*)np + 0xc) = 1;
            *(int*)((u8*)np + 0x10) = ab->mField_08;
            *(int*)((u8*)np + 0x14) = (int)ab->mField_10;
            *(float*)((u8*)np + 0x18) = b->FUN_00d9c100(c, ab);
            *(void**)((u8*)np + 0x1c) = b->mAnimHandle;
            void* v = ((cNounManager*)FUN_00b3d300())->GetItemID();
            cListItem** it = *(cListItem***)v;
            cListItem** end = *(cListItem***)((u8*)v + 4);
            for (; it != end; ++it) {
                cListItem* e = *it;
                int f = e->mpDB_b20->FindField10(ab->mField_10);
                if (f != -1) {
                    tt->mStimuli_08.FUN_00bc97f0(0x10000000, 0, g_1470f1c, 0);
                    void* np2 = tt->mStimuli_08.Play(0x10000000, 0);
                    *(int*)((u8*)np2 + 0xc) = 0;
                    *(int*)((u8*)np2 + 0x10) = f;
                }
            }
        }
        c->mpTree_b4c->mStimuli_08.ClearAll(0x10000000, 0);
        return true;
    }
    case 3:                                         // kResponding
        if (c->AnimationFinished(b->mAnimHandle)) {
            if ((c->mFlags_b58 >> 9) & 1) {
                cBehaviorTree* tt = b->mpTarget->mpTree_b4c;
                tt->mStimuli_08.FUN_00bc97f0(0x10000000, 0, g_147c190, 0);
                void* np = tt->mStimuli_08.Play(0x10000000, 0);
                *(int*)((u8*)np + 0xc) = 2;
                *(int*)((u8*)np + 0x10) = b->mAbilityType;
                *(int*)((u8*)np + 0x14) = b->mExpectedAbilityType;
            }
            b->mSocialIdx = 0;
            b->mState = 2;
            b->mAnimHandle = 0;
        }
        break;
    }
    return true;
}

// @ 0x00d9eb70
cPoolObject* cSocialBandPool::GetObject(uint32_t nIndex)
{
    uint32_t nCount = (uint32_t)(mpEnd - mpBegin);
    uint32_t nSlot = nIndex & 0xbfffffff;
    if (nSlot < nCount) {
        cPoolSlot* pSlot = &mpBegin[nSlot];
        uint32_t* pFlags = &pSlot->mnLinkFlags;
        if (pSlot->mbUsed == 0)
            return (cPoolObject*)(pFlags + 1);
    }
    return nullptr;
}

// @ 0x00d9ebc0
void cSocialBandPool::ReleaseObject(uint32_t nIndex)
{
    cPoolSlot* pSlot = mpBegin + nIndex;
    ((cPoolObject*)pSlot->mObject)->Destroy(0);

    uint32_t nHead = mnHeadIndex;
    pSlot->mnLinkFlags = (pSlot->mnLinkFlags & 0xc0000000) | (nHead & 0x3fffffff) |
                         0x80000000;
    mnHeadIndex = nIndex;
    if (mnTailIndex == nIndex)
        mnTailIndex = GetNextFreeSlot(nIndex);
}

// @ 0x00d9ef40
void Fd9ef40(int* first, int* last, Vector3 vec)
{
    int n = (last - first);
    if (n < 2)
        return;
    int hole = ((n - 2) >> 1) + 1;
    do {
        --hole;
        Fd9da80(first, hole, n, hole, first[hole], vec);
    } while (hole != 0);
}

// @ 0x00da2360
namespace SP {
void SOCIAL_BAND_PLAY_Tick(cSocialBand* pBand)
{
    cPlanetModel_s00da_2360* pPlanet = PlanetModel();
    float skill = gBandSkill.GetSkill(*(int*)((char*)pBand->mpCommunity->GetLeader() + 0xb20)) + 1.0f;

    BandSection* sorted[4];
    BandSection* assigned[kNumSectionPositions] = { 0 };
    BandSection sections[5];

    cSPVector3 center(kZeroVector);
    for (cSPCreatureBase_s00da_2360 **it = pBand->mMembersBegin, **end = pBand->mMembersEnd; it != end; ++it) {
        cSPCreatureBase_s00da_2360* pCreature = *it;
        cSPCreatureCitizen_s00da_2360* pCitizen = CitizenCast(pCreature);
        center += pCreature->GetPosition();
        if (pCitizen) {
            switch (pCitizen->GetBandRole()) {
            case 11: {
                float dist = skill * 2.0f + 3.0f;
                cSPVector3 point = pBand->mStageArea - pBand->mStageFacing * dist;
                int index = pBand->mActionCircle.FindNearestFreeSlot(point);
                if (index != -1) {
                    tSlot_s00da_2360* pSlot = pBand->mActionCircle.GetSlot(index);
                    pSlot->Occupy(pCitizen);
                    pCitizen->MoveToPointAndFacingAtSpeed(cSPCreatureBase_s00da_2360::kSpeedRun, pSlot->mPosition,
                                                          pBand->mStageFacing, 1.0f, 2.0f);
                }
                break;
            }
            case 5:
                sections[0].Add(pCitizen);
                break;
            case 6:
                sections[1].Add(pCitizen);
                break;
            case 4:
                sections[2].Add(pCitizen);
                break;
            default:
                sections[3].Add(pCitizen);
                break;
            }
        } else if (pCreature->GetNounID() == kAnimalNounID) {
            sections[3].Add(pCreature);
        }
    }

    float invCount = 1.0f / (float)(uint32_t)(pBand->mMembersEnd - pBand->mMembersBegin);
    center.x *= invCount;
    center.y *= invCount;
    center.z = invCount * center.z;

    for (int i = 0; i < 5; ++i) {
        BandSection& section = sections[i];
        section.mDistSq = 3.402823466e+38f;
        uint32_t n = section.mMembers.size();
        if (n > 0) {
            section.mCenter *= 1.0f / (float)n;
            SortSectionMembers(section.mMembers.mpBegin, section.mMembers.mpEnd, section.mCenter);
            section.mDistSq = (section.mCenter - center).LengthSquared();
        }
    }

    sorted[0] = &sections[0];
    sorted[1] = &sections[1];
    sorted[2] = &sections[2];
    sorted[3] = &sections[3];
    qsort(sorted, 4, sizeof(BandSection*), CompareSectionDistance);

    for (uint32_t i = 0; i < 4; ++i) {
        BandSection* pSection = sorted[i];
        cSPVector3 dir = (pSection->mCenter - center).Normalized();
        int best = 0;
        float bestScore = 0.0f;
        for (int j = 1; j < kNumSectionPositions; ++j) {
            if (assigned[j] == 0 && j != 5) {
                cSPVector3 toPos = pBand->mBandSectionPositions[j] - center;
                float inv = 1.0f / (sqrtf(toPos.LengthSquared()) + 1.5258789e-05f);
                float score = (Dot(toPos * inv, dir) + 1.0f) * inv;
                if (score > bestScore) {
                    best = j;
                    bestScore = score;
                }
            }
        }
        assigned[best] = pSection;
    }

    for (int i = 1; i < kNumSectionPositions; ++i) {
        BandSection* pSection = assigned[i];
        if (pSection && !pSection->mMembers.empty()) {
            cSPVector3 surfacePos = pPlanet->DirectionToSurfacePosition(pBand->mBandSectionPositions[i]);
            uint32_t count = pSection->mMembers.size();
            for (uint32_t j = 0; j < count; ++j) {
                cSPCreatureBase_s00da_2360* pMember = static_cast<cSPCreatureBase_s00da_2360*>(pSection->mMembers.mpBegin[j]);
                const cSPVector3& pos = pMember->GetPosition();
                cSPVector3 dir = (pos - pSection->mCenter).Normalized();
                if (dir == kZeroVector)
                    dir = (pos - surfacePos).Normalized();

                tSlot_s00da_2360* pSlots = pBand->mActionCircle.mSlotsBegin;
                int numSlots = pBand->mActionCircle.mSlotsEnd - pSlots;
                int bestSlot = -1;
                float bestScore = 0.0f;
                for (uint32_t k = 0; k < (uint32_t)numSlots; ++k) {
                    if (!pSlots[k].mbOccupied) {
                        cSPVector3 toSlot = pSlots[k].mPosition - surfacePos;
                        float inv = 1.0f / sqrtf(toSlot.LengthSquared());
                        float score = (Dot(toSlot * inv, dir) + 1.0f) * inv;
                        if (score > bestScore) {
                            bestSlot = k;
                            bestScore = score;
                        }
                    }
                }
                if (bestSlot != -1) {
                    tSlot_s00da_2360* pSlot = &pSlots[bestSlot];
                    pSlot->Occupy(pMember);
                    pMember->MoveToPointAndFacingAtSpeed(cSPCreatureBase_s00da_2360::kSpeedRun, pSlot->mPosition,
                                                         pBand->mStageFacing, 1.0f, 2.0f);
                }
            }
        }
    }
}
}  // namespace SP

// @ 0x00da49f0
uint SP_SOCIAL_PROPOSE_Tick(cSPCreatureBase_s00da_49f0* pCreature, int, int, int, int, SocialProposeState* pState, int, float dt)
{
    void* pBrain = *(void**)((uint8_t*)pCreature + 0xb4c);
    cSocialProposeBrain* pB = (cSocialProposeBrain*)(*(void**)((uint8_t*)pBrain + 0x600));
    (void)pBrain;
    SocialProposeMemoryBlock* pMem = &pB->mPropose;

    if (pB->ShouldSkip())
        return 0;

    if (pState->mFlag8 != 0) {
        if (FUN_00d99470(pMem->mpField04) == 0)
            return 0;
        cSPCreatureBase_s00da_49f0* pTgt = (cSPCreatureBase_s00da_49f0*)pMem->mpField04->GetTargetAsCreature();
        if (pTgt != pCreature)
            return 0;
        if (*(int32_t*)((uint8_t*)pMem->mpField04->mpFieldb4c + 0x1d8) != (int32_t)0x941bd4bf)
            return 0;
        pMem->mProgress.Update(dt, pMem->mField3c, pCreature, pMem->mpField04);
        if (pMem->mpField38->FUN_00e31a90() && pState->mState != 8) {
            int32_t anim = pMem->RewardPlayer(pCreature, pMem->mpField04);
            if (anim != -1) {
                pState->mAnimHandle = pCreature->PlayAnimation(anim, 1, -1);
                pMem->FUN_00d9b230(pCreature, (void*)pB, anim);
            }
            pState->mState = 8;
        }
    }

    if ((uint)pState->mState > 8)
        return 1;

    switch (pState->mState) {
    case 0: {
        if (pCreature->mLoco.IsNearGoal()) {
            if (pState->mFlag8 != 0) {
                if (pMem->mField50 > 0) {
                    pMem->mField48 = 10.0f;                              // [0x01582f28] = 10.0f
                    pState->mAnimHandle = pCreature->InterruptAnimation(0x61e0673, -1, 0);
                    pState->mState = 2;
                } else {
                    pState->mState = 4;
                }
            } else {
                if (pState->mField0c != -1 && pMem->mField4c < pMem->mField50) {
                    pCreature->mFieldb5c = 1;
                    pMem->mField4c++;
                    pState->mState = 5;
                } else {
                    pCreature->mFieldb5c = 1;
                }
            }
        }
        if (pState->mFlag8 == 0)
            pState->mField0c = pMem->SocialRespond_Activate(pCreature, pState->mField0c);
        return 1;
    }
    case 1:
        return 1;
    case 2:
        pMem->mField48 = pMem->mField48 - dt;
        if (pCreature->AnimationFinished(pState->mAnimHandle)) {
            pCreature->PlayAnimation(0x61e0674, 1, -1);
            pState->mState = 3;
        }
        return 1;
    case 3:
        pMem->mField48 = pMem->mField48 - dt;
        if (!(0.0f > pMem->mField48) && pMem->mField4c != pMem->mField50)
            return 1;
        pMem->mProgress.mField00 = (float)(uint)(pMem->mField4c + 1) * pMem->mProgress.mField00;
        pMem->mField58 |= 0x20;
        pMem->mField54 = pMem->mField4c;
        pState->mState = 4;
        return 1;
    case 4: {
        if ((uint)pMem->mField0c < (uint)pMem->mField08) {
            void* pElem = pCreature->mpField1020[pMem->mField0c];
            void** pVtbl = pCreature->mpVTable;
            cTuningObj* pTune = (cTuningObj*)((void*(__thiscall*)(void*, void*))pVtbl[0xb4 / 4])(pCreature, pElem);
            uint32_t v = pTune->GetAt(0);
            pState->mAnimHandle = pCreature->InterruptAnimation((int32_t)v, -1, 0);
            pMem->mProgress.FUN_00d9b090((float)(uint)(pMem->mField54 + 1) * pTune->mField3c, pState->mAnimHandle);
            pMem->mField10 = pTune->mField08;
            pMem->mField14 = pTune->mField10;
            pState->mState = 6;
            pMem->mField58 &= 0xfffffff0u;
            pMem->mField40 = 1;
            pMem->FUN_00d9b230(pCreature, (void*)pB, (int32_t)v);
            return 1;
        }
        if (pMem->mProgress.FUN_00d9b010())
            return 1;
        pMem->mProgress.FUN_00d9b040(1);
        pState->mAnimHandle = pCreature->PlayAnimation(0x53685d8f, 1, -1);
        pMem->FUN_00d9b230(pCreature, (void*)pB, 0x53685d8f);
        pState->mState = 8;
        return 1;
    }
    case 5: {
        BehaviorStimuli_s00da_49f0* pStim = (BehaviorStimuli_s00da_49f0*)((uint8_t*)*(void**)((uint8_t*)pCreature + 0xb4c) + 8);
        void* pR = pStim->Play(0x10000000, 0);
        if (pR && *(int32_t*)((uint8_t*)pR + 0xc) == 3)
            pCreature->InterruptAnimation(*(int32_t*)((uint8_t*)pR + 0x10), -1, 0);
        pStim->ClearAll(0x10000000, 0);
        return 1;
    }
    case 6: {
        uint32_t flags = pMem->mField58;
        if (!(flags & 2)) {
            if (flags & 1) {
                pMem->mField44 = pMem->mField44 - dt;
                if (pMem->mField44 <= 0.0f)
                    return 0;
            }
        }
        if (!(flags & 1)) {
            if (pCreature->AnimationFinished(pState->mAnimHandle)) {
                pMem->mField58 |= 1;
                pState->mAnimHandle = pCreature->PlayAnimation(0x61e0675, 1, -1);
                pMem->FUN_00d9b230(pCreature, (void*)pB, 0x61e0675);
                if (!(pMem->mField58 & 2))
                    pMem->mField44 = 10.0f;                              // [0x01582f20] = 10.0f
            }
        }
        flags = pMem->mField58;
        if ((flags & 1) && !(flags & 2)) {
            if (!pMem->mProgress.FUN_00d9b010()
                && pMem->mProgress.mField0d == 0
                && pMem->mProgress.mField0c == 0) {
                pMem->mProgress.mField08 = pMem->mProgress.mField10;
                pMem->mProgress.mField0c = 1;
            }
        }
        if (pMem->mProgress.mField0d != 0) {
            if (!pCreature->CCM_e0c0(0x61e0670)) {
                pState->mAnimHandle = pCreature->PlayAnimation(0x61e0670, 1, -1);
                pMem->FUN_00d9b230(pCreature, (void*)pB, 0x61e0670);
            }
        }
        pMem->FUN_00d9b110(pCreature);
        flags = pMem->mField58;
        if (!(flags & 1))
            return 1;
        if (!(flags & 4))
            return 1;
        if (pMem->mProgress.FUN_00d9b010())
            return 1;
        pMem->mField0c++;
        if (pMem->mField58 & 8) {
            pState->mState = 4;
            return 1;
        }
        pState->mAnimHandle = pCreature->PlayAnimation(0x68d8f9c, 1, -1);
        pState->mState = 7;
        pMem->FUN_00d9b230(pCreature, (void*)pB, 0x68d8f9c);
        return 1;
    }
    case 7:
        if (pCreature->AnimationFinished(pState->mAnimHandle)) {
            pState->mAnimHandle = 0;
            pState->mState = 4;
        }
        return 1;
    default:
        if (pCreature->AnimationFinished(pState->mAnimHandle))
            return 0;
        return 1;
    }
}

// @ 0x00da4f00
cSocialBand_s00da_49f0* cSocialBand_s00da_49f0::Init()
{
    mpVTable = (void**)0x0147c1e0;
    mpField04 = 0;
    mpField08 = 0;
    mpField0c = 0;
    mField34 = 0.0f;
    mField38 = 0.0f;
    mField3c = 0.0f;
    mField40 = 0.0f;
    mField44 = 0;
    mField48 = 0;
    mField4c = 0.0f;
    mField50 = 0;
    mField51 = 0;
    mField52 = 0;
    mField54 = 0.0f;
    mField58 = 0;
    mField5c = 0.0f;
    mField60 = 0;
    mVecA.mpBegin = 0;
    mVecA.mpEnd = 0;
    mVecA.mpCap = 0;
    mVecB.mpBegin = 0;
    mVecB.mpEnd = 0;
    mVecB.mpCap = 0;

    uint8_t* pBufC = mVecC.mBuf;
    mVecC.mpBufPtr = pBufC;
    mVecC.mpEnd = pBufC;
    mVecC.mpBegin = pBufC;
    mVecC.mpCap = pBufC + 0x40;

    mpFieldE4 = 0;
    mpFieldE8 = 0;
    mFieldF0 = 0;

    uint8_t* pBufD = mVecD.mBuf;
    mVecD.mpEnd = pBufD;
    mVecD.mpBegin = pBufD;
    mVecD.mpCap = pBufD + 0x48;
    mVecD.InitFixed(6);

    uint8_t* pBufE = mVecE.mBuf;
    mVecE.mpEnd = pBufE;
    mVecE.mpBegin = pBufE;
    mVecE.mpCap = pBufE + 0x14;
    mVecE.InitFixed(5);

    mActionCircle.Init();

    mField1e0 = 0;
    mField1dc = -1;
    uint8_t* pBufF = mVecF.mBuf;
    mVecF.mpBufPtr = pBufF;
    mVecF.mpEnd = pBufF;
    mVecF.mpBegin = pBufF;
    mVecF.mpCap = pBufF + 0x10;

    return this;
}

// @ 0x00da5030
cSocialBand_s00da_49f0* cSocialBand_s00da_49f0::Assign(const cSocialBand_s00da_49f0* pSrc)
{
    mpField04 = pSrc->mpField04;

    if (mpField08 != pSrc->mpField08) {
        if (pSrc->mpField08)
            pSrc->mpField08->AddRef();
        RefCounted* pOld = mpField08;
        mpField08 = pSrc->mpField08;
        if (pOld)
            pOld->Release();
    }
    if (mpField0c != pSrc->mpField0c) {
        if (pSrc->mpField0c)
            pSrc->mpField0c->AddRef();
        RefCounted* pOld = mpField0c;
        mpField0c = pSrc->mpField0c;
        if (pOld)
            pOld->Release();
    }

    mField10 = pSrc->mField10;
    mField14 = pSrc->mField14;
    mField18 = pSrc->mField18;
    mField1c = pSrc->mField1c;
    mField20 = pSrc->mField20;
    mField24 = pSrc->mField24;
    mField28 = pSrc->mField28;
    mField2c = pSrc->mField2c;
    mField30 = pSrc->mField30;
    mField34 = pSrc->mField34;
    mField38 = pSrc->mField38;
    mField3c = pSrc->mField3c;
    mField40 = pSrc->mField40;
    mField44 = pSrc->mField44;
    mField48 = pSrc->mField48;
    mField4c = pSrc->mField4c;
    mField50 = pSrc->mField50;
    mField51 = pSrc->mField51;
    mField52 = pSrc->mField52;
    mField54 = pSrc->mField54;
    mField58 = pSrc->mField58;
    mField5c = pSrc->mField5c;
    mField60 = pSrc->mField60;

    mVecA.Assign(&pSrc->mVecA);
    mVecB.Assign(&pSrc->mVecB);

    if (&mVecC != &pSrc->mVecC) {
        mVecC.Erase(mVecC.mpBegin, mVecC.mpEnd);
        mVecC.Assign(pSrc->mVecC.mpBegin, pSrc->mVecC.mpEnd, (void*)pSrc);
    }

    if (mpFieldE4 != pSrc->mpFieldE4) {
        if (pSrc->mpFieldE4)
            pSrc->mpFieldE4->AddRef();
        RefCounted* pOld = mpFieldE4;
        mpFieldE4 = pSrc->mpFieldE4;
        if (pOld)
            pOld->Release();
    }
    if (mpFieldE8 != pSrc->mpFieldE8) {
        if (pSrc->mpFieldE8)
            pSrc->mpFieldE8->AddRef();
        RefCounted* pOld = mpFieldE8;
        mpFieldE8 = pSrc->mpFieldE8;
        if (pOld)
            pOld->Release();
    }
    mFieldEc = pSrc->mFieldEc;
    mFieldF0 = pSrc->mFieldF0;

    if (&mVecD != &pSrc->mVecD) {
        mVecD.Erase(mVecD.mpBegin, mVecD.mpEnd);
        mVecD.Assign(pSrc->mVecD.mpBegin, pSrc->mVecD.mpEnd, (void*)pSrc);
    }
    if (&mVecE != &pSrc->mVecE) {
        memcpy(mVecE.mpBegin, mVecE.mpEnd, 0);
        mVecE.mpEnd = (uint8_t*)mVecE.mpEnd + ((int)((uint8_t*)mVecE.mpEnd - (uint8_t*)mVecE.mpBegin) >> 2) * -4;
        mVecE.Assign(pSrc->mVecE.mpBegin, pSrc->mVecE.mpEnd, mVecE.mpBegin);
    }

    mActionCircle.Assign(&pSrc->mActionCircle);

    mField1dc = pSrc->mField1dc;
    mField1e0 = pSrc->mField1e0;

    if (&mVecF != &pSrc->mVecF) {
        memcpy(mVecF.mpBegin, mVecF.mpEnd, 0);
        mVecF.mpEnd = (uint8_t*)mVecF.mpEnd + ((int)((uint8_t*)mVecF.mpEnd - (uint8_t*)mVecF.mpBegin) >> 2) * -4;
        mVecF.Assign(pSrc->mVecF.mpBegin, pSrc->mVecF.mpEnd, mVecF.mpBegin);
    }

    return this;
}

// @ 0x00da52e0
cSocialBand_s00da_49f0* cSocialBand_s00da_49f0::CopyInit(const cSocialBand_s00da_49f0* pSrc)
{
    mpVTable = (void**)0x0147c1e0;
    mpField04 = pSrc->mpField04;
    mpField08 = pSrc->mpField08;
    if (mpField08)
        mpField08->AddRef();
    mpField0c = pSrc->mpField0c;
    if (mpField0c)
        mpField0c->AddRef();

    mField10 = pSrc->mField10;
    mField14 = pSrc->mField14;
    mField18 = pSrc->mField18;
    mField1c = pSrc->mField1c;
    mField20 = pSrc->mField20;
    mField24 = pSrc->mField24;
    mField28 = pSrc->mField28;
    mField2c = pSrc->mField2c;
    mField30 = pSrc->mField30;
    mField34 = pSrc->mField34;
    mField38 = pSrc->mField38;
    mField3c = pSrc->mField3c;
    mField40 = pSrc->mField40;
    mField44 = pSrc->mField44;
    mField48 = pSrc->mField48;
    mField4c = pSrc->mField4c;
    mField50 = pSrc->mField50;
    mField51 = pSrc->mField51;
    mField52 = pSrc->mField52;
    mField54 = pSrc->mField54;
    mField58 = pSrc->mField58;
    mField5c = pSrc->mField5c;
    mField60 = pSrc->mField60;

    int nA = (int)((uint8_t*)pSrc->mVecA.mpEnd - (uint8_t*)pSrc->mVecA.mpBegin) / 4;
    mVecA.InitBuffer(nA, (void*)&pSrc->mVecA.mpField70);
    void* pEndA = 0;
    FUN_00829110(&pEndA, pSrc->mVecA.mpBegin, pSrc->mVecA.mpEnd, mVecA.mpBegin, (void*)pSrc);
    mVecA.mpEnd = pEndA;

    int nB = (int)((uint8_t*)pSrc->mVecB.mpEnd - (uint8_t*)pSrc->mVecB.mpBegin) / 4;
    mVecB.InitBuffer(nB, (void*)&pSrc->mVecB.mpField84);
    void* pEndB = 0;
    FUN_00829110(&pEndB, pSrc->mVecB.mpBegin, pSrc->mVecB.mpEnd, mVecB.mpBegin, (void*)pSrc);
    mVecB.mpEnd = pEndB;

    uint8_t* pBufC = mVecC.mBuf;
    mVecC.mpBufPtr = pBufC;
    mVecC.mpEnd = pBufC;
    mVecC.mpBegin = pBufC;
    mVecC.mpCap = pBufC + 0x40;
    mVecC.Assign(pSrc->mVecC.mpBegin, pSrc->mVecC.mpEnd, (void*)pSrc);

    mpFieldE4 = pSrc->mpFieldE4;
    if (mpFieldE4)
        mpFieldE4->AddRef();
    mpFieldE8 = pSrc->mpFieldE8;
    if (mpFieldE8)
        mpFieldE8->AddRef();
    mFieldEc = pSrc->mFieldEc;
    mFieldF0 = pSrc->mFieldF0;

    uint8_t* pBufD = mVecD.mBuf;
    mVecD.mpEnd = pBufD;
    mVecD.mpBegin = pBufD;
    mVecD.mpCap = pBufD + 0x48;
    mVecD.Assign(pSrc->mVecD.mpBegin, pSrc->mVecD.mpEnd, (void*)pSrc);

    uint8_t* pBufE = mVecE.mBuf;
    mVecE.mpEnd = pBufE;
    mVecE.mpBegin = pBufE;
    mVecE.mpCap = pBufE + 0x14;
    mVecE.Assign(pSrc->mVecE.mpBegin, pSrc->mVecE.mpEnd, (void*)pSrc);

    mActionCircle.CopyInit(&pSrc->mActionCircle);

    mField1dc = pSrc->mField1dc;
    mField1e0 = pSrc->mField1e0;

    uint8_t* pBufF = mVecF.mBuf;
    mVecF.mpBufPtr = pBufF;
    mVecF.mpEnd = pBufF;
    mVecF.mpBegin = pBufF;
    mVecF.mpCap = pBufF + 0x10;
    mVecF.Assign(pSrc->mVecF.mpBegin, pSrc->mVecF.mpEnd, (void*)pSrc);

    return this;
}

// @ 0x00da5550
cSocialBandEntry* cSocialBandEntry::Assign(const cSocialBandEntry& rhs)
{
    if (!rhs.mIsEmpty) {
        if (mIsEmpty) {
            if (&mBand)
                mBand.CopyInit(&rhs.mBand);
        } else {
            mBand.Assign(&rhs.mBand);
        }
    } else {
        if (!mIsEmpty)
            BandRelease(&mBand);
    }
    mSlotInfo = rhs.mSlotInfo;
    return this;
}

// @ 0x00da55c0
void* FUN_00da55c0(cSocialBandEntry* pFirst, cSocialBandEntry* pLast, cSocialBandEntry* pDest)
{
    while (pFirst != pLast) {
        if (pDest) {
            pDest->mSlotInfo = pFirst->mSlotInfo;
            if (!pFirst->mIsEmpty)
                pDest->mBand.CopyInit(&pFirst->mBand);
        }
        pFirst = (cSocialBandEntry*)((uint8_t*)pFirst + 0x210);
        pDest = (cSocialBandEntry*)((uint8_t*)pDest + 0x210);
    }
    return pDest;
}

// @ 0x00da5660
void cSocialBandPool_s00da_49f0::Reserve(uint n)
{
    int nCount = (int)((uint8_t*)mpCap - (uint8_t*)mpBegin) / 0x210;
    if ((uint)nCount < n) {
        cSocialBandEntry* pNew = 0;
        if (n != 0)
            pNew = (cSocialBandEntry*)EAAlloc((int)(n * 0x210), "Simulator", 0, 0,
                "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
        cSocialBandEntry* pOldBegin = mpBegin;
        cSocialBandEntry* pOldEnd = mpEnd;
        FUN_00da55c0(pOldBegin, pOldEnd, pNew);
        FUN_00d9b7f0(pOldBegin, pOldEnd, pNew);
        if (mpBegin)
            EAFree(mpBegin);
        int nOld = (int)((uint8_t*)pOldEnd - (uint8_t*)pOldBegin) / 0x210;
        mpBegin = pNew;
        mpEnd = (cSocialBandEntry*)((uint8_t*)pNew + nOld * 0x210);
        mpCap = (cSocialBandEntry*)((uint8_t*)pNew + n * 0x210);
    }
}

// @ 0x00da5720
void cSocialBandPool_s00da_49f0::Insert(cSocialBandEntry* pPos, cSocialBandEntry* pValue)
{
    cSocialBandEntry* pEnd = mpEnd;
    if (pEnd != mpCap) {
        cSocialBandEntry* pSrc = pValue;
        if (!(pValue < pPos) && !(pValue >= pEnd))
            pSrc = (cSocialBandEntry*)((uint8_t*)pValue + 0x210);

        if (pEnd) {
            cSocialBandEntry* pPrev = (cSocialBandEntry*)((uint8_t*)pEnd - 0x210);
            pEnd->mSlotInfo = pPrev->mSlotInfo;
            if (!pPrev->mIsEmpty)
                pEnd->mBand.CopyInit(&pPrev->mBand);
        }

        FUN_00da5620(pPos, (cSocialBandEntry*)((uint8_t*)pEnd - 0x210), pEnd);
        pPos->Assign(*pSrc);
        mpEnd = (cSocialBandEntry*)((uint8_t*)pEnd + 0x210);
        return;
    }

    int nCount = (int)((uint8_t*)mpEnd - (uint8_t*)mpBegin) / 0x210;
    int nNew;
    if (nCount == 0)
        nNew = 1;
    else
        nNew = nCount * 2;

    cSocialBandEntry* pNew = 0;
    if (nNew != 0)
        pNew = (cSocialBandEntry*)EAAlloc(nNew * 0x210, "Simulator", 0, 0,
            "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);

    cSocialBandEntry* pOldBegin = mpBegin;
    cSocialBandEntry* pOldEnd = mpEnd;
    cSocialBandEntry* pDest = (cSocialBandEntry*)FUN_00da55c0(pOldBegin, pOldEnd, pNew);
    FUN_00d9b7f0(pOldBegin, pOldEnd, pNew);
    if (pDest) {
        pDest->mSlotInfo = pValue->mSlotInfo;
        if (!pValue->mIsEmpty)
            pDest->mBand.CopyInit(&pValue->mBand);
    }

    cSocialBandEntry* pNewEnd = (cSocialBandEntry*)FUN_00da55c0(pOldEnd, pPos,
        (cSocialBandEntry*)((uint8_t*)pDest + 0x210));
    FUN_00d9b7f0(pOldEnd, pPos, (cSocialBandEntry*)((uint8_t*)pDest + 0x210));
    if (mpBegin)
        EAFree(mpBegin);
    mpBegin = pNew;
    mpEnd = pNewEnd;
    mpCap = (cSocialBandEntry*)((uint8_t*)pNew + nNew * 0x210);
}

// @ 0x00da58a0
void cSocialBandPool_s00da_49f0::DoInsertEntry()
{
    cSocialBandEntry temp;
    cSocialBandEntry* p = mpEnd;
    if (p < mpCap) {
        mpEnd = (cSocialBandEntry*)((uint8_t*)p + 0x210);
        if (p)
            p->mSlotInfo = 0x80000000u;
        return;
    }
    temp.mSlotInfo = 0x80000000u;
    Insert(p, &temp);
    if (!temp.mIsEmpty)
        BandRelease(&temp.mBand);
}

// @ 0x00da5900
u32 cSocialBandPool_s00da_5900::create(const cSocialBand_s00da_5900& item)
{
    u32 nIndex = mFreeHead;
    if (nIndex != 0x3fffffff) {
        mFreeHead = ((cSocialBandEntry_s00da_5900*)(mpBegin + nIndex * 0x210))->mFlags & 0x3fffffff;
        ((cSocialBandEntry_s00da_5900*)(mpBegin + nIndex * 0x210))->mFlags &= 0x7fffffff;
        cSocialBand_s00da_5900* pItem = &((cSocialBandEntry_s00da_5900*)(mpBegin + nIndex * 0x210))->mItem;
        if (pItem)
            ::new (pItem) cSocialBand_s00da_5900(item);
    } else {
        const cSocialBand_s00da_5900 temp(item);
        nIndex = (u32)((mpEnd - mpBegin) / 0x210);
        DoInsertEntry();
        if (nIndex != 0)
            ((cSocialBandEntry_s00da_5900*)(mpBegin + (nIndex - 1) * 0x210))->mFlags &= 0xbfffffff;
        ((cSocialBandEntry_s00da_5900*)(mpBegin + nIndex * 0x210))->mFlags |= 0x40000000;
        ((cSocialBandEntry_s00da_5900*)(mpBegin + nIndex * 0x210))->mFlags &= 0x7fffffff;
        cSocialBand_s00da_5900* pItem = &((cSocialBandEntry_s00da_5900*)(mpBegin + nIndex * 0x210))->mItem;
        if (pItem)
            ::new (pItem) cSocialBand_s00da_5900(temp);
    }
    if (mMinFree > nIndex)
        mMinFree = nIndex;
    return nIndex;
}

// @ 0x00da5a00
u32 cSocialBandPool_s00da_5900::CreateObject()
{
    cSocialBand_s00da_5900 local;
    u32 index = create(local);
    return index | 0x40000000;
}

// @ 0x00da5a40
bool __cdecl FUN_00da5a40(cSPCreatureCitizen* c)
{
    cSPCreatureCitizen* pcVar3;
    cSPCreatureCitizen* pcVar6;
    cTribe*             playerTribe;
    cTribe*             otherTribe;
    AgentNode*          node;

    if (c == 0) {
        pcVar3 = 0;
    } else {
        pcVar3 = c->GetByHash(0x4f176642);
        c->GetByHash(0xd0036e08);
    }

    void* block = c->mpBTree->mStimuli.Play(0x10000, 0);
    if (block == 0)
        return false;

    pcVar6 = (cSPCreatureCitizen*)FUN_00d994c0(FUN_00d999d0(block));
    if (pcVar6 == 0)
        return false;

    playerTribe = NounManager()->GetPlayerTribe();
    if (pcVar3 != 0)
        playerTribe = pcVar3->GetTribe();
    otherTribe = pcVar6->GetTribe();

    NodeArgs args;
    args.a = playerTribe;
    args.b = otherTribe;
    args.pos = *pcVar6->mPos.GetPos();

    node = AgentOrderManager()->FindNode(0xf445d1cc, (void*)&FUN_00d9f0a0, &args);
    if (node == 0) {
        if (pcVar3 == 0)
            return false;
        node = AgentOrderManager()->CreateNode(0xf445d1cc, 0x20, (void*)0x18eb4b7, "Social");
        node->mFn224 = (void*)&FUN_00da05f0;
        node->mFn228 = (void*)&FUN_00d9f130;
        u32 bandIndex = gSocialBandPool.CreateObject();
        node->mBand = bandIndex;
        gSocialBandPool.GetObject(bandIndex)->Start(playerTribe, otherTribe, pcVar6, pcVar3);
        c->mpBTree->mStimuli.PlayWith(0x200000, 0, 5.0f, c);
    }

    c->mpBTree->OrderOp(node, c, 0, (void*)&FUN_00d9f0a0);
    gSocialBandPool.GetObject(node->mBand)->Bind(c);
    c->SetInteractionTarget(0.0f);

    if (pcVar3 != 0 && pcVar3->IsLeader()) {
        cTribeModeStrategy* st = cTribeModeStrategy::Instance();
        for (cSPCreatureCitizen** it = st->mpBegin; it != st->mpEnd; ++it) {
            cSPCreatureCitizen* member = *it;
            member->mpBTree->mStimuli.PlayWith(0x100000, 0, 3.402823466e+38f, 0);
            member->mpBTree->mStimuli.PlayWith(0x10000, 0, 5.0f, pcVar6);
        }
    }
    return true;
}
