// src/game/SPGonzago/SPTribeGameBehaviorFish.cpp -- migrated from slice(s) s00d75400, s00d74060, s00d71f80 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPTribeGameBehaviorFish.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cInteractionAgent.h"
#include "SP/cLocomotiveObject.h"
#include "SP/cPlanetModel.h"
#include "SP/cSPCreatureCitizen.h"
#include "SP/cTribe.h"

// unnamed retail callees and globals (address in the comment)
extern const float kFloatMax;      // 0x0147bd98  FLT_MAX
extern const float kOneF;          // 0x01470f1c  1.0f
extern const float kSqEps;         // 0x013ec4b8  1e-8f
extern const float kHundredF;      // 0x013ec4d0  100.0f
extern const float kEatBoostF;     // 0x013ec4bc  0.07f
extern const float kFishA;         // 0x0169eee0
extern const float kFishB;         // 0x0169eee4
extern const float kFishC;         // 0x0169eee8
#include <math.h>
#include <string.h>
#include "EA/Random/RandomLinearCongruential.h"
#include "SP/cModelWorld.h"
#include "SP/cSpatialObject.h"

// ---- items of slice s00d71f80 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned char byte;
void operator delete(void* p) throw();        // 0x00f47380
void operator delete[](void* p) throw();      // 0x00f47380
void* EAAllocate(unsigned size, const char* name, unsigned a, unsigned b,
                 const char* file, int line);   // 0x00f473a0
namespace SP {
struct cSPVector3 {
    float x, y, z;
    cSPVector3() {}
    cSPVector3(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    cSPVector3(const cSPVector3& v) : x(v.x), y(v.y), z(v.z) {}
    float LengthSquared() const { return x * x + y * y + z * z; }
};
}
namespace SP {
struct cPlanetModel_s00d7_1f80 {
    float       GetWaterHeight();                                             // 0x00b7e390
    float       GetRadiusAt(const cSPVector3* pos);                           // 0x00b7ef70
    cSPVector3* DirectionToSurfacePosition(cSPVector3* out, cSPVector3* dir);  // 0x00b815a0
    cSPVector3* MakeRandomWorldPosition(cSPVector3* out, const cSPVector3* dir); // 0x00b81780
};
}
namespace SP {
cPlanetModel_s00d7_1f80* PlanetModel();                                                  // 0x00b3d350
}
namespace SP {
class cLocomotiveObject_s00d7_1f80 {
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
    virtual cSPVector3* GetPosition();               // +0x2c
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
    virtual void GetSteerParams(void* params);       // +0xdc

    char  mTail[0x3e0 - 4];                          // pad the class out to 0x3e0
    bool IsNearGoal();                               // 0x00c42e20
};
}
namespace SP {
class cTribe_s00d7_1f80;
}
namespace SP {
class cSPCreatureCitizen_s00d7_1f80;
}
namespace SP {
class cTribeMember {
public:
virtual void v00();
virtual void v04();
    cTribe_s00d7_1f80* GetTribe();                                                // 0x00c22f50
    void SetCurrentToolEffect(int tool, unsigned a);                   // 0x00c24f40
    void PlayAnimation(unsigned animID, int a, int b);                 // 0x00c12190
    void MoveToPointAndFacingAtSpeed(int speed, const cSPVector3* pt,
                                     const cSPVector3* facing, float f1, float f2); // 0x00c1c5c0
    void MoveToPointAtSpeed(int speed, const cSPVector3* pt, float f1, float f2);  // 0x00c1c1d0
    bool  QueryFlagB770();                                             // 0x00c0b770
    void  FuncC0CFF0(int a);                                           // 0x00c0cff0
    bool  FuncC0E0C0(int a);                                           // 0x00c0e0c0

    char pad00[0xc0];
    cLocomotiveObject_s00d7_1f80 mLoco;            // +0xc0
};
}
namespace SP {
class cTribe_s00d7_1f80 {
public:
    char  pad00[0x120];
    cLocomotiveObject_s00d7_1f80* mpLeader_120;    // +0x120  (GetPosition at vtable+0x2c)
    char  pad_124[0x260 - 0x124];
    void* mpLeader_260;                 // +0x260  (object whose +0x34 is a spatial base)
};
}
namespace SP {
struct Cell {
    byte       mFlag;     // +0x00
    char       pad1[3];
    cSPVector3 mPoint;    // +0x04
    cSPVector3 mHit;      // +0x10
    Cell& operator=(const Cell& o)
    {
        mFlag = o.mFlag;
        mPoint = o.mPoint;
        mHit = o.mHit;
        return *this;
    }
};
}
namespace SP {
struct CellVector {
    byte* mpBegin;      // +0x00
    byte* mpEnd;        // +0x04
    byte* mpCapacity;   // +0x08

    int  size() const { return (int)(mpEnd - mpBegin) / 0x1c; }
    void  reserve(unsigned n);                    // 0x00d72fd0
};
}
namespace SP {
struct cSurfaceSampler {
    char pad00[0x40];
    CellVector mCells;    // +0x40
};
}
namespace SP {
cSurfaceSampler* SamplerFromPos(const cSPVector3* pos);    // 0x00c94430
}
namespace SP {
class cInteractionAgent_s00d7_1f80;
}
namespace SP {
struct AgentInfoMap {
    void*    field_00;      // +0x00
    void*    mAnchorLeft;   // +0x04  (anchor, self-referential)
    void*    mAnchorParent; // +0x08
    void*    mAllocName;    // +0x0c
    uint32_t mAllocBytes;   // +0x10
    uint32_t mnSize;        // +0x14
    void* InsertNode(void** out, void* parent, uint32_t* key, char side);  // 0x00d72d50
};
}
namespace SP {
class cTribeGameBehaviorFish {
public:
    void**    vtbl0;                                       // +0x00
    void**    vtbl1;                                       // +0x04
    char      pad08[0x04];                                 // +0x08
    void**    mTargetBlocks;                               // +0x0c
    char      pad10[0x14];                                 // +0x10..+0x23
    uint32_t  mTargetIndex;                                // +0x24
    char      pad28[0x4c];                                 // +0x28..+0x73
    AgentInfoMap mAgentInfoMap;                            // +0x74  (0x18 bytes)
    float     mTotalFoodFished;                            // +0x8c
    uint32_t  field_90;                                    // +0x90
    float     mWaterCheckDistance;                         // +0x94
    byte      field_98;                                    // +0x98
    byte      field_99;                                    // +0x99
    char      pad9a[0x02];
    float     mTimeToLook;                                 // +0x9c
    float     mLuckiness;                                  // +0xa0
    float     mEatingBoost;                                // +0xa4
    float     mFoodEaten;                                  // +0xa8
    float     mFishIdleMin;                                // +0xac
    float     mFishIdleVar;                                // +0xb0
    float     mFishPerSecond;                              // +0xb4
    float     mFoodPerFish;                                // +0xb8
    void*     mpTribe;                                     // +0xbc  AutoRefCount<cTribe>
    unsigned long long mLastTime;                          // +0xc0
    cSPVector3 mClosestLand;                               // +0xc8

    bool CanJoin(cInteractionAgent_s00d7_1f80* a, void* b);           // 0x00d72c30
    void* DeleteDtor(unsigned flags);                      // 0x00d72f50
    cTribeGameBehaviorFish();                              // 0x00d72e70
};
}
namespace SP {
class cInteractionAgent_s00d7_1f80 {
public:
    virtual void v00();                                   // +0x00
    virtual void v04();                                   // +0x04
    virtual cSPCreatureCitizen_s00d7_1f80* FindCreature(int key);    // +0x08
};
}
namespace SP {
struct SPExt {
    void Nuke(void* node);        // 0x009a9600  DoNukeSubtree
    void DtorBody();              // 0x00d79fd0  FishDtorBody
    void BaseCtor();              // 0x00abf320  cTribeGameInteraction ctor
};
}
namespace SP {
extern void* SP_vtbl_Fish;    // 0x0147be30
}
namespace SP {
extern void* SP_vtbl_Fish1;   // 0x0147be1c
}
namespace SP {
void* AgentOrderFirstPending(void* a);                      // 0x00bca2c0
}
namespace SP {
cSPVector3* AgentOrderNodePos(void* a);                     // 0x00cce910
}
namespace SP {
void  RBTreeInsert(void* node, void* parent, void* anchor, int side);   // 0x009216a0
}
namespace SP {
class cSPCreatureCitizen_s00d7_1f80 : public cTribeMember {
public:
    char  pad_b4c[0xb4c - 0xc0 - 0x3e0];
    void* mpOrderManager;   // +0xb4c
};
}
extern const float kFloatMax;      // 0x0147bd98  FLT_MAX
extern const float kOneF;          // 0x01470f1c  1.0f
extern const float kSqEps;         // 0x013ec4b8  1e-8f
extern const float kHundredF;      // 0x013ec4d0  100.0f
extern const float kEatBoostF;     // 0x013ec4bc  0.07f
extern const float kFishA;         // 0x0169eee0
extern const float kFishB;         // 0x0169eee4
extern const float kFishC;         // 0x0169eee8
// ---- items of slice s00d71f80 end

// ---- items of slice s00d74060 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" double __cdecl sqrt(double);
extern float DAT_01572070;    // 0x01572070
extern float DAT_0157206c;    // 0x0157206c
extern float DAT_01687a14;    // 0x01687a14
extern float DAT_01687a10;    // 0x01687a10
extern float DAT_0169eee0;    // 0x0169eee0
extern float DAT_0169eee4;    // 0x0169eee4
extern float DAT_0169eee8;    // 0x0169eee8
extern int   DAT_0169ef34;    // 0x0169ef34
extern int   DAT_0169ef38;    // 0x0169ef38
extern int   DAT_0169ef3c;    // 0x0169ef3c
extern int   DAT_0158128c;    // 0x0158128c
extern int   DAT_015841a8;    // 0x015841a8
extern int   DAT_015841ac;    // 0x015841ac
extern float DAT_01581298;    // 0x01581298
extern float DAT_0158129c;    // 0x0158129c
extern float DAT_015812a0;    // 0x015812a0
extern char  DAT_0167ec50;    // 0x0167ec50
extern char  cRandomGlobal;   // 0x01601760
typedef unsigned char u8;
typedef unsigned int  u32;
typedef long long     i64;
struct tSlotEntry { u32 mSlotInfo; void* mpData; };
struct AgentDeque {
    tSlotEntry** mpBlocks;                 // +0x00
};
struct AgentFilter {
    void* mpOwner;
    u8    mbFlag;
    AgentFilter(void* pOwner, bool flag) : mpOwner(pOwner), mbFlag(flag ? 1 : 0) {}
};
struct AgentIterator {
    AgentDeque* mpDeque;                   // +0x00
    u32         mIndex;                    // +0x04
    AgentDeque* mpEndDeque;                // +0x08
    u32         mEndIndex;                 // +0x0c
    AgentFilter mFilter;                   // +0x10

    AgentIterator(AgentDeque* pDeque, const AgentFilter& filter);   // 0x00abf010
    void Next();                                                    // 0x00abeb20
    bool IsDone() const
    {
        return (u32)mpDeque + mIndex == (u32)mpEndDeque + mEndIndex;
    }
    void* Get() const
    {
        return ((AgentDeque*)mpDeque)->mpBlocks[mIndex >> 7][mIndex & 0x7f].mpData;
    }
};
struct AgentObj {
    virtual void v00();
    virtual void v04();
    virtual void* __thiscall Cast(int typeID);   // +0x08
};
struct TimeMgr {
    i64 __thiscall Time();                              // 0x00b316c0
};
void* GameTimeManager();                                                // 0x00b3d380
struct FishInfoMap {
    u32 mData[7];
    int* __thiscall FindOrAdd(void** key);              // 0x00d73bc0
};
struct Eng {
    void* __thiscall GetTribe();                                            // 0x00c22f50
    char  __thiscall HasSpecializedTool(int tool);                          // 0x00c236e0
    int   __thiscall GetToolEffect(int tool);                               // 0x00c235e0
    char  __thiscall IsLeader();                                            // 0x00c232d0
    char  __thiscall PutAwayToolExceptFor(int tool);                        // 0x00c22ca0
    char  __thiscall SetToolOnAnimEvent(int tool);                          // 0x00c263e0
    char  __thiscall AnimationFinished(int handle);                         // 0x00c123f0
    char  __thiscall AnimationFinished2(int handle);                        // 0x00c12400
    int   __thiscall PlayAnimation(int id, int blend, int handle);          // 0x00c12190
    int   __thiscall InterruptAnimation(int id, int blend, int handle);     // 0x00c12310
    int   __thiscall PlayAnimationWithTarget(int id, int target, int blend, int handle);     // 0x00c14940
    int   __thiscall InterruptAnimationWithTarget(int id, int target, int blend, int handle); // 0x00c149c0
    char  __thiscall WaitForAnimEventOrEnd(int ev, int* out, int minId, int handle, int b);  // 0x00c14ef0
    void  __thiscall MoveToPointAtSpeed(int mode, float* pos, float dist, float speed);       // 0x00c1c1d0
    void  __thiscall MoveToPointAndFacingAtSpeed(int mode, void* pos, void* facing, float dist, float speed); // 0x00c1c5c0
    void  __thiscall SetCurrentToolEffect(int effect, int blend);           // 0x00c24f40
    void  __thiscall PerformSocialAction(int target, int a);                // 0x00c23300
    void  __thiscall SetToolTarget(float x, float y, float z);              // 0x00c234a0
    void  __thiscall SetToolFacing(float x, float y, float z);              // 0x00c227f0
    void  __thiscall SetToolArg(int a);                                     // 0x00c22860
    int   __thiscall AnimHandle();                                          // 0x00c22820
    int   __thiscall ToolIndex();                                           // 0x00c22a70
    void* __thiscall FindSlotByKey(int key, int a);                         // 0x00c0f9b0
    void* __thiscall FindSlotByCombatant(int a, int b);                     // 0x00c0fa10
    float __thiscall GetSkill();                                            // 0x00c0b9c0
    void  __thiscall AddSkill(float delta);                                 // 0x00c0b9d0
    char  __thiscall HasTool();                                             // 0x00c0b780
    float __thiscall GetLuckRoll();                                         // 0x00c0e3a0
    char  __thiscall DoSpotCheck(int a, int b);                             // 0x00c25480
    void* __thiscall MakeEvent(void* a, void* b, void* c, int d, float e);  // 0x00c0bc00
};
struct Tribe {
    int  __thiscall HotSpotGetClosest(void* pos);          // 0x00c8f040
    void __thiscall UpdateWater(float depth);              // 0x00c94b50
    char __thiscall WaterOkA();                            // 0x00c8e850
    char __thiscall WaterOkB();                            // 0x00c8e870
    void __thiscall FindSpot(int kind, int id);            // 0x00c98750
};
struct Locomotive {
    char __thiscall IsNearGoal();                          // 0x00c42e20
};
struct EngSub34 {
    void* __thiscall Handle();                             // 0x00cee330
    float __thiscall Radius();                             // 0x00cee380
};
struct EngLayout {                                         // ecx = layout manager
    char __thiscall LookupB(void* a, int b, int c);        // 0x00af0bd0
};
struct EngVec {                                            // ecx = temp from 0x00b3d2b0
    void __thiscall Add(float v, void* vec, int n);        // 0x00ac7ab0
    void __thiscall Add2(void* vec, void* a, int n);       // 0x00ac7d10
    void __thiscall Add3(int a, int* b);                   // 0x00ac7eb0
};
void* FUN_00b0d350();                                                          // 0x00b0d350
int   FUN_00d724f0(void* a);                                                   // 0x00d724f0
void  FUN_00da6270(void* a, int b);                                            // 0x00da6270
char  FUN_004232c0(float* a, void* b);                                         // 0x004232c0
float GetPropertyT_float(int owner, int key, float def);                       // 0x004e1c70
void  FUN_00c9af30(int spot, float* o1, void* o2, char* o3);                   // 0x00c9af30
void  FUN_00c9ae30(int spot, float delta);                                     // 0x00c9ae30
void* FUN_00b3d2b0(float v, void* vec, int n);                                 // 0x00b3d2b0
void* FUN_00b3d2b0b(int v, int* vec);                                          // 0x00b3d2b0
void  FUN_00e398e0(float a, void* b);                                          // 0x00e398e0
void  FUN_00449c20(float* dst, float* src);                                    // 0x00449c20
char  FUN_00d727b0(void* a, void* b);                                          // 0x00d727b0
int   FUN_00d72770(void* a);                                                   // 0x00d72770
void  FUN_00d72720(void* a, int b);                                            // 0x00d72720
int   FUN_00dba630(void* a, int b);                                            // 0x00dba630
void* FUN_00af13b0(void* a, int b, int c);                                     // 0x00af13b0
void* FUN_00b3d350(void* a, void* b);                                          // 0x00b3d350
void  FUN_00b81630(void* a, void* b);                                          // 0x00b81630
void* FUN_00c94430_out(int a, int* out);                                       // 0x00c94430
void* FUN_00c94430_val(int a, int v);                                          // 0x00c94430
float FUN_00c420f0(void* a, float b, float c);                                 // 0x00c420f0
struct RLC {
    u32 __thiscall RandomUint32Uniform(int n);          // 0x00a68fb0
};
class cTribeGameBehaviorFish_s00d7_4060 {
public:
    char mPad[0x2c];
    AgentDeque mAgentList;                          // +0x2c

    __declspec(noinline) int __thiscall Action();   // 0x00d74060
};
#define I32(p, o) (*(int*)((char*)(p) + (o)))
#define F32(p, o) (*(float*)((char*)(p) + (o)))
#define B8(p, o)  (*(u8*)((char*)(p) + (o)))
#define I64(p, o) (*(i64*)((char*)(p) + (o)))
#define VTSLOT(p, off) ((*(void***)(p))[(off) / 4])
#define VC0(rt, p, off)          ((rt(__thiscall*)(void*))VTSLOT(p, off))((void*)(p))
#define VCF(rt, p, off, a)       ((rt(__thiscall*)(void*, float))VTSLOT(p, off))((void*)(p), (float)(a))
#define VCI(rt, p, off, a)       ((rt(__thiscall*)(void*, int))VTSLOT(p, off))((void*)(p), (int)(a))
#define VC3(rt, p, off, d, a, b) ((rt(__thiscall*)(void*, void*, float, float))VTSLOT(p, off))((void*)(p), (void*)(d), (float)(a), (float)(b))
static float Bits(int b) { return *(float*)&b; }
#define CITIZEN   ((Eng*)pcVar4)
#define SPATIAL   ((void*)((char*)pcVar4 + 0xc0))
#define SUB34     ((EngSub34*)((char*)pcVar4 + 0x34))
// ---- items of slice s00d74060 end

// ---- items of slice s00d75400 begin (TODO(rewrite): local stubs, replace by canonical classes)
#pragma intrinsic(sqrt)
#define PV(n) virtual void pv##n();
class IWin;
struct Vector3 { float x, y, z; };
class cGameObject;
class cObject;
class IWin {
 public:
    virtual void AddRef();                                   // +0x00
    virtual void Release();                                  // +0x04
    PV(2)
    virtual cGameObject* pv03(uint32_t id);                  // +0x0c
    PV(4) PV(5) PV(6) PV(7) PV(8)
    virtual char pv09(uint32_t id, void** out);              // +0x24
    PV(10)
    virtual float* pv11();                                   // +0x2c
    PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19) PV(20) PV(21)
    virtual char pv22();                                     // +0x58
    PV(23) PV(24) PV(25)
    virtual void* pv26();                                    // +0x68
    PV(27) PV(28)
    virtual double pv29();                                   // +0x74
};
class RefText {
 public:
    RefText& operator=(IWin* p);                             // 0x00b5f950

    IWin* mpRef;                                             // +0x00
};
class cPlanetMgr {                                           // creature->mB20
 public:
    uint8_t pad00[0x590];
    float   mField590;                                       // +0x590
};
class cSubQuery {                                            // creature->mSub5c
 public:
    PV(0)
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
class cTargetSlot {
 public:
    uint8_t pad00[0x28];
    uint8_t mFlag_28;                                        // +0x28
};
class cFishOwner {                                           // behaviour->+0x74
 public:
    cTargetSlot* FUN_00d73bc0(RefText** pp);                 // 0x00d73bc0
};
class cStimulus {
 public:
    uint8_t pad00[0x14];
    int32_t mKind_14;                                        // +0x14
};
class cTribeGameBehaviorFish_s00d7_5400 : public IWin {
 public:
    void OnLayout(cGameObject* a, cStimulus* s);             // 0x00b267f0
    void CalledByStimulus(cGameObject* a, cStimulus* s);     // 0x00d75400

    uint8_t    pad04[0x70];                                  // +0x04..+0x74
    cFishOwner mObj74;                                       // +0x74
};
// ---- items of slice s00d75400 end

// ---- moved functions of slice s00d75400 begin (definitions kept at file scope)
void SP_BindFruitNode(cTribeGameBehaviorFish_s00d7_5400* self, cGameObject* obj);   // 0x00d754b0
void SP_PickFruitAndMove(cTribeGameBehaviorFish_s00d7_5400* self, cGameObject* obj); // 0x00d755b0
// ---- moved functions of slice s00d75400 end

// @ 0x00d72520
float SP_CastRay(SP::cSPVector3* pos, SP::cSPVector3* dir, float step, float maxDist, SP::cSPVector3* out)
{
    SP::cPlanetModel_s00d7_1f80* pm = SP::PlanetModel();
    float waterH = pm->GetWaterHeight();
    float cx = pos->x, cy = pos->y, cz = pos->z;
    float t = step;
    for (;;) {
        if (maxDist <= t)
            return kFloatMax;
        SP::cSPVector3 p(pos->x + dir->x * t, pos->y + dir->y * t, pos->z + dir->z * t);
        float r = pm->GetRadiusAt(&p);
        if (r >= waterH) {
            float inv = 1.0f / sqrtf(p.x * p.x + p.y * p.y + p.z * p.z + kSqEps);
            cx = inv * p.x * r;
            cy = inv * p.y * r;
            cz = inv * p.z * r;
            t += step;
            continue;
        }
        float inv = 1.0f / sqrtf(p.x * p.x + p.y * p.y + p.z * p.z);
        out->x = inv * p.x * waterH;
        out->y = inv * p.y * waterH;
        out->z = inv * p.z * waterH;
        pos->x = cx;
        pos->y = cy;
        pos->z = cz;
        return t;
    }
}

// @ 0x00d726e0
void SP_ClearCellByIndex(SP::cSurfaceSampler* s, unsigned index)
{
    if (s != 0) {
        if (index < (unsigned)s->mCells.size())
            *((byte*)s->mCells.mpBegin + index * 0x1c) = 0;
    }
}

// @ 0x00d72720
void SP_ClearCellAtPos(const SP::cSPVector3* pos, unsigned index)
{
    SP::cSurfaceSampler* s = SP::SamplerFromPos(pos);
    if (s != 0) {
        if (index < (unsigned)s->mCells.size())
            *((byte*)s->mCells.mpBegin + index * 0x1c) = 0;
    }
}

// @ 0x00d72770
void* SP_GetCellByIndex(SP::cSurfaceSampler* s, unsigned index)
{
    if (s != 0) {
        if (index < (unsigned)s->mCells.size())
            return (byte*)s->mCells.mpBegin + index * 0x1c;
    }
    return 0;
}

// @ 0x00d727b0
int SP_FindNearestCell(SP::cSPVector3* a, SP::cSPVector3* b, SP::cSurfaceSampler* s, unsigned* out)
{
    *out = 0xffffffff;
    unsigned count = (unsigned)s->mCells.size();
    float best = kFloatMax;
    unsigned i = 0;
    byte* base = s->mCells.mpBegin;
    while (i + 4 <= count) {
        for (int k = 0; k < 4; ++k) {
            byte* c = base + (i + k) * 0x1c;
            if (*c == 0) {
                float* pt = (float*)(c + 4);
                float* ht = (float*)(c + 0x10);
                float bx = pt[0] - b->x, by = pt[1] - b->y, bz = pt[2] - b->z;
                float ax = pt[0] - a->x, ay = pt[1] - a->y, az = pt[2] - a->z;
                float d = ((bz * bz + by * by) + bx * bx) * 2.0f
                        + ((ax * ax + az * az) + ay * ay);
                (void)ht;
                if (d < best) { *out = i + k; best = d; }
            }
        }
        i += 4;
    }
    while (i < count) {
        byte* c = base + i * 0x1c;
        if (*c == 0) {
            float* pt = (float*)(c + 4);
            float bx = pt[0] - b->x, by = pt[1] - b->y, bz = pt[2] - b->z;
            float ax = pt[0] - a->x, ay = pt[1] - a->y, az = pt[2] - a->z;
            float d = ((bz * bz + by * by) + bx * bx) * 2.0f
                    + ((ax * ax + az * az) + ay * ay);
            if (d < best) { *out = i; best = d; }
        }
        ++i;
    }
    if (*out == 0xffffffff)
        return 0xffffff00;
    base[*out * 0x1c] = 1;
    return 1;
}

// @ 0x00d72bb0
byte* SP_CopyCells(byte* first, byte* last, byte* dest)
{
    if (first != last) {
        do {
            if (dest != 0) {
                SP::Cell& d = *(SP::Cell*)dest;
                SP::Cell& f = *(SP::Cell*)first;
                d = f;
            }
            first += 0x1c;
            dest += 0x1c;
        } while (first != last);
    }
    return dest;
}

// @ 0x00d72c30
bool SP::cTribeGameBehaviorFish::CanJoin(SP::cInteractionAgent_s00d7_1f80* agent, void*)
{
    if (agent == 0)
        return false;
    SP::cSPCreatureCitizen_s00d7_1f80* creature = agent->FindCreature(0x4f176642);
    if (creature == 0)
        return false;
    void* tribe = this->mpTribe;
    if (creature->GetTribe() != (SP::cTribe_s00d7_1f80*)tribe && this->mpTribe != 0)
        return false;
    if (this->mTargetIndex == 0x3fffffff)
        return true;
    void* block = this->mTargetBlocks[this->mTargetIndex >> 7];
    void* slot = *(void**)((char*)block + (this->mTargetIndex & 0x7f) * 8 + 4);
    if (slot == 0)
        return true;
    void* node = (*(void*(**)(void*, int))slot)(slot, 0xe69e1e);
    if (node == 0)
        return true;
    void* pending = SP::AgentOrderFirstPending(*(void**)((char*)creature + 0xb4c));
    if (pending == 0 || *(int*)pending != 1)
        return true;
    if (*(unsigned short*)((char*)pending + 0x4b) == 0)
        return true;
    SP::cSPVector3* p = SP::AgentOrderNodePos((char*)pending + 0x39);
    float dx = *(float*)((char*)node + 0x24) - p->x;
    float dy = *(float*)((char*)node + 0x28) - p->y;
    float dz = *(float*)((char*)node + 0x2c) - p->z;
    if (dz * dz + dy * dy + dx * dx < kOneF)
        return true;
    return false;
}

// @ 0x00d72d50
void* SP::AgentInfoMap::InsertNode(void** out, void* parent, uint32_t* key, char side)
{
    int insertSide;
    if (side != 0 || parent == (char*)this + 4)
        insertSide = 0;
    else if (*key < *(uint32_t*)((char*)parent + 0x10))
        insertSide = 1;
    else
        insertSide = 0;

    void* node = EAAllocate(0x48, (const char*)0x013f09b4u, 0, 0, (const char*)0x013ebb38u, 0xd1);
    if ((char*)node + 0x10 != 0) {
        uint32_t* dst = (uint32_t*)((char*)node + 0x10);
        for (int i = 0xe; i != 0; --i)
            *dst++ = *key++;
    }
    SP::RBTreeInsert(node, parent, (char*)this + 4, insertSide);
    this->mnSize += 1;
    *out = node;
    return node;
}

// @ 0x00d72e70
SP::cTribeGameBehaviorFish::cTribeGameBehaviorFish()
{
    ((SPExt*)this)->BaseCtor();                            // 0x00abf320
    this->vtbl0 = (void**)&SP::SP_vtbl_Fish;               // 0x0147be30
    this->vtbl1 = (void**)&SP::SP_vtbl_Fish1;              // 0x0147be1c
    this->mAgentInfoMap.mAnchorParent = 0;
    this->mAgentInfoMap.mAllocName = 0;
    this->mAgentInfoMap.mAllocBytes = 0;
    this->mAgentInfoMap.mAllocName = 0;
    this->mAgentInfoMap.mAllocBytes = 0;
    this->mAgentInfoMap.mnSize = 0;
    void* anchor = (char*)&this->mAgentInfoMap + 0x04;
    this->mAgentInfoMap.mAnchorParent = anchor;
    this->mAgentInfoMap.mAnchorLeft = anchor;
    this->mWaterCheckDistance = 0.0f;
    this->mLuckiness = 0.0f;
    this->field_90 = 0;
    this->field_98 = 0;
    this->field_99 = 0;
    this->mTimeToLook = kHundredF;
    this->mEatingBoost = kEatBoostF;
    this->mFoodEaten = 0.0f;
    this->mFishIdleMin = 0.0f;
    this->mFishIdleVar = kFishA;
    this->mFishPerSecond = kFishB;
    this->mFoodPerFish = kFishC;
    this->mpTribe = 0;
    this->mLastTime = ~0ULL;
}

// @ 0x00d72f50
void* SP::cTribeGameBehaviorFish::DeleteDtor(unsigned flags)
{
    this->vtbl0 = (void**)&SP::SP_vtbl_Fish;
    this->vtbl1 = (void**)&SP::SP_vtbl_Fish1;
    void* tribe = this->mpTribe;
    if (tribe != 0) {
        void** vt = *(void***)tribe;
        ((void(__thiscall*)(void*))vt[1])(tribe);
    }
    SPExt* map = (SPExt*)&this->mAgentInfoMap;
    void* node = this->mAgentInfoMap.mAllocName;
    map->Nuke(node);
    ((SPExt*)this)->DtorBody();
    if (flags & 1)
        operator delete[](this);
    return this;
}

// @ 0x00d72fd0
void SP::CellVector::reserve(unsigned n)
{
    int cap = (int)(mpCapacity - mpBegin) / 0x1c;
    if (n > (unsigned)cap) {
        byte* mem;
        if (n == 0)
            mem = 0;
        else
            mem = (byte*)EAAllocate(n * 0x1c, (const char*)0x013f09b4u, 0, 0,
                                    (const char*)0x013ebb38u, 0xd1);
        SP_CopyCells(mpBegin, mpEnd, mem);
        if (mpBegin != 0 && *(int*)(mpBegin - 4) != 0)
            operator delete[](mpBegin);
        byte* oldBegin = mpBegin;
        mpBegin = mem;
        mpEnd = mem + ((mpEnd - oldBegin) / 0x1c) * 0x1c;
        mpCapacity = mem + n * 0x1c;
    }
}

// @ 0x00d74060
int cTribeGameBehaviorFish_s00d7_4060::Action()
{
    char* self = (char*)this;

    AgentIterator it(&mAgentList, AgentFilter(this, false));
    if (it.IsDone())
        return 1;

    i64 timeNow = ((TimeMgr*)GameTimeManager())->Time();
    I32(self, 0xa8) = (int)timeNow;
    I32(self, 0xac) = (int)(timeNow >> 32);

    if (it.IsDone())
        return 1;

    do {
        void* pAgentRaw = it.Get();
        if (pAgentRaw) {
            void* pcVar4 = ((AgentObj*)pAgentRaw)->Cast(0x4f176642);
            if (pcVar4) {
                float  pfS = 0.0f;
                float* pfStack_118 = 0;
                float  fStack_114 = 0.0f;
                int    vOut = 0;
                char   cOut = 0;
                int    bias = 0;
                u32    uVar6 = 0;
                void*  iv = 0;
                int*   pRec = 0;
                float  fDir[3] = { 0.0f, 0.0f, 0.0f };
                float  fPnt[3] = { 0.0f, 0.0f, 0.0f };
                float  fNeg[3] = { 0.0f, 0.0f, 0.0f };
                int    bufA[3] = { 0, 0, 0 };
                int    bufB[3] = { 0, 0, 0 };

                pfStack_118 = (float*)((char*)pcVar4 + 0x58);
                pRec = ((FishInfoMap*)(self + 0x74))->FindOrAdd((void**)&pfStack_118);
                pfStack_118 = (float*)(void*)CITIZEN->GetTribe();
                VC0(void, pfStack_118, 0xac);

                // per-record idle/tool timers
                if (pRec[0] == 0xc || pRec[0] == 10 || pRec[0] == 8) {
                    i64 last = I64(pRec, 0x10);
                    if ((double)last != 0.0) {
                        i64 dt = timeNow - last;
                        F32(pRec, 0x18) =
                            (float)((double)dt * (double)F32(pRec, 0x1c) * 0.001) + F32(pRec, 0x18);
                    }
                    I64(pRec, 0x10) = timeNow;
                }

                uVar6 = CITIZEN->HasSpecializedTool(8) ? 1u : 0u;
                if (CITIZEN->HasSpecializedTool(8))
                    fStack_114 = GetPropertyT_float(DAT_0158128c, (int)0xfceeb952u, 2.0f);
                else
                    fStack_114 = GetPropertyT_float(DAT_0158128c, (int)0xe4dd8a7cu, 1.0f);
                bias = CITIZEN->IsLeader() ? 0x20 : 0;

                switch (pRec[0]) {
                case 0: {
                    void* u = FUN_00b0d350();
                    if (FUN_00d724f0(u) == 0) {
                        FUN_00da6270(pcVar4, 1);
                        ((void(__thiscall*)(void*, AgentIterator))(*(void***)this)[0x11])(this, it);
                    } else if (CITIZEN->PutAwayToolExceptFor(8) == 0) {
                        if (CITIZEN->AnimationFinished(0)) {
                            iv = SUB34->Handle();
                            if (iv == 0) { pRec[0] = 6; B8(pRec, 0x29) = 0; }
                            else         { B8(pRec, 0x29) = 1; pRec[0] = 1; }
                        }
                    } else {
                        CITIZEN->SetToolOnAnimEvent(8);
                    }
                    break; }

                case 1: {
                    if (FUN_004232c0((float*)(self + 0xb0), &DAT_0169eee0) == 0) {
                        float d  = VC0(float, SPATIAL, 0x74) + 10.0f;
                        float d2 = VC0(float, SPATIAL, 0x74);
                        CITIZEN->MoveToPointAtSpeed(2, (float*)(self + 0xb0), d, d2 + d);
                        pRec[0] = 2;
                    } else {
                        FUN_00da6270(pcVar4, 1);
                        ((void(__thiscall*)(void*, AgentIterator))(*(void***)this)[0x11])(this, it);
                    }
                    break; }

                case 2:
                    if (((Locomotive*)SPATIAL)->IsNearGoal())
                        pRec[0] = 3;
                    break;

                case 3: {
                    if (FUN_004232c0((float*)(self + 0xb0), &DAT_0169eee0) != 0) {
                        FUN_00da6270(pcVar4, 1);
                        ((void(__thiscall*)(void*, AgentIterator))(*(void***)this)[0x11])(this, it);
                        break;
                    }
                    iv = FUN_00c94430_out((int)(size_t)(*(void**)(self + 0xc0)), &vOut);
                    iv = VCI(void*, SPATIAL, 0x2c, iv);
                    if (FUN_00d727b0((float*)(self + 0xb0), iv) == 0) {
                        FUN_00da6270(pcVar4, 1);
                        ((void(__thiscall*)(void*, AgentIterator))(*(void***)this)[0x11])(this, it);
                        break;
                    }
                    iv = FUN_00c94430_val((int)(size_t)(*(void**)(self + 0xc0)), vOut);
                    int* p = (int*)FUN_00d72770(iv);
                    pRec[1] = vOut;
                    fStack_114 = VC0(float, SPATIAL, 0x74);
                    {
                        float dx = F32(p, 4)  - F32(p, 0x10);
                        float dy = F32(p, 8)  - F32(p, 0x14);
                        float dz = F32(p, 0xc) - F32(p, 0x18);
                        float len = (float)sqrt((double)dx * dx
                                             + ((double)dy * dy + (double)dz * dz));
                        float inv = 1.0f / (len + 1.5258789e-05f);
                        float nx = dx * inv, ny = dy * inv, nz = dz * inv;
                        float t  = (fStack_114 - DAT_01572070) + len;
                        fPnt[0] = F32(p, 0x10) + nx * t;
                        fPnt[1] = F32(p, 0x14) + ny * t;
                        fPnt[2] = F32(p, 0x18) + nz * t;
                        FUN_00b3d350(fDir, fPnt);
                        FUN_00b81630(fDir, fPnt);
                        fNeg[0] = -nx; fNeg[1] = -ny; fNeg[2] = -nz;
                        CITIZEN->MoveToPointAndFacingAtSpeed(2, fDir, fNeg,
                                                            DAT_01572070, DAT_0157206c);
                    }
                    pRec[0] = 4;
                    break; }

                case 4:
                    if (((Locomotive*)SPATIAL)->IsNearGoal())
                        pRec[0] = 5;
                    break;

                case 5: {
                    if (!((Locomotive*)SPATIAL)->IsNearGoal())
                        break;
                    VC0(void, SPATIAL, 0xec);
                    int key = CITIZEN->AnimHandle();
                    void* slot = CITIZEN->FindSlotByKey(key, 0);
                    if (SUB34->Handle() == 0) {
                        void* r = FUN_00b3d2b0(0.0f, (char*)pcVar4 + 0x34, 3);
                        ((EngVec*)r)->Add(0.0f, (char*)pcVar4 + 0x34, 3);
                    }
                    if (B8(slot, 0x18) == 0) {
                        fDir[0] = Bits(DAT_0169ef34 ^ (int)0x80000000u);
                        fDir[1] = Bits(DAT_0169ef38 ^ (int)0x80000000u);
                        fDir[2] = Bits(DAT_0169ef3c ^ (int)0x80000000u);
                    } else {
                        fDir[0] = Bits(DAT_0169ef34);
                        fDir[1] = Bits(DAT_0169ef38);
                        fDir[2] = Bits(DAT_0169ef3c);
                    }
                    CITIZEN->SetToolTarget(fDir[0], fDir[1], fDir[2]);
                    iv = VCF(void*, SPATIAL, 0x2c, 40.0f);
                    int spot = ((Tribe*)pfStack_118)->HotSpotGetClosest(iv);
                    pRec[2] = spot; pRec[7] = 0; pRec[4] = 0; pRec[5] = 0;
                    if (spot != -1) {
                        int gpkey = CITIZEN->HasSpecializedTool(8)
                                        ? (int)0x5f956f3cu : (int)0x1c079d85u;
                        pRec[7] = (int)GetPropertyT_float(DAT_0158128c, gpkey, 0.07f);
                    }
                    pRec[0] = (B8(pRec, 0x29) == 0) * 2 + 6;
                    break; }

                case 6: {
                    if (CITIZEN->HasSpecializedTool(8)) {
                        int eff = CITIZEN->GetToolEffect(8);
                        if (CITIZEN->ToolIndex() != eff)
                            CITIZEN->InterruptAnimation(0x2c39200, CITIZEN->AnimHandle(), 0);
                    }
                    pRec[0] = 7;
                    break; }

                case 7: {
                    if (CITIZEN->PutAwayToolExceptFor(8) == 0)
                        pRec[0] = (B8(pRec, 0x29) != 0 ? 7 : 0) + 1;
                    else
                        CITIZEN->SetToolOnAnimEvent(8);
                    break; }

                case 8: {
                    int h = CITIZEN->AnimHandle();
                    pRec[9] = CITIZEN->PlayAnimation((int)uVar6 + 0x2c39210 + bias, 1, h);
                    pRec[0] = 9;
                    break; }

                case 9: {
                    if (!CITIZEN->AnimationFinished(pRec[9]))
                        break;
                    float a = GetPropertyT_float(DAT_0158128c, (int)0x69943cd, 1.2f);
                    float b = GetPropertyT_float(DAT_0158128c, (int)0xbca45f07u, 3.9f);
                    F32(self, 0xa0) = FUN_00c420f0(&DAT_0167ec50, a, b);
                    int h = CITIZEN->AnimHandle();
                    pRec[9] = CITIZEN->PlayAnimation((int)uVar6 + 0x2c39215 + bias, 1, h);
                    pRec[0] = 10;
                    break; }

                case 10: {
                    if (!(F32(self, 0xa0) < CITIZEN->GetLuckRoll()))
                        break;
                    int h = CITIZEN->AnimHandle();
                    pRec[9] = CITIZEN->PlayAnimation((int)uVar6 + 0x2c3921a + bias, 1, h);
                    pfS = 0.0f;
                    FUN_00c9af30(pRec[2], &pfS, fDir, &cOut);
                    if (F32(pRec, 0x18) <= 1.0f || pfS <= fStack_114 || cOut != 0) {
                        int h2 = CITIZEN->AnimHandle();
                        pRec[9] = CITIZEN->PlayAnimation(bias + 0x2c39223, 0, h2);
                        pRec[0] = 0xd;
                    } else {
                        FUN_00c9ae30(pRec[2], -fStack_114);
                        F32(pRec, 0x18) = F32(pRec, 0x18) - fStack_114;
                        pRec[0] = 0xb;
                    }
                    break; }

                case 0xb: {
                    vOut = -1;
                    if (!CITIZEN->WaitForAnimEventOrEnd(DAT_015841a8, &vOut, 0, pRec[9], 1))
                        break;
                    CITIZEN->SetCurrentToolEffect(CITIZEN->HasTool() ? 5 : 6, -1);
                    u32 rnd = ((RLC*)&cRandomGlobal)->RandomUint32Uniform(3);
                    int h = CITIZEN->AnimHandle();
                    CITIZEN->PlayAnimation((int)rnd + 0x2c39220 + bias, 1, h);
                    int ti = CITIZEN->ToolIndex();
                    int h2 = CITIZEN->AnimHandle();
                    int id = (ti == 4) ? 0x2c39225 : (bias + 0x2c39224);
                    pRec[9] = CITIZEN->PlayAnimation(id, 0, h2);
                    pRec[0] = 0xc;
                    break; }

                case 0xc: {
                    vOut = -1;
                    if (!CITIZEN->WaitForAnimEventOrEnd(DAT_015841ac, &vOut, 0, pRec[9], 1))
                        break;
                    SUB34->Handle();
                    fStack_114 = SUB34->Radius() + fStack_114;
                    {
                        float lim = VCI(float, (char*)pcVar4 + 0x34, 0x38, 3);
                        if (lim < fStack_114)
                            fStack_114 = lim;
                    }
                    {
                        float d = SUB34->Radius();
                        if (0.0f < fStack_114 - d) {
                            float dd = fStack_114 - d;
                            void* r = FUN_00b3d2b0(dd, (char*)pcVar4 + 0x34, 3);
                            ((EngVec*)r)->Add(dd, (char*)pcVar4 + 0x34, 3);
                        }
                    }
                    B8(self, 0x99) = 1;
                    if (CITIZEN->HasSpecializedTool(8) == 0) {
                        CITIZEN->SetCurrentToolEffect(0, -1);
                        pRec[0] = 0xd;
                    } else {
                        CITIZEN->SetCurrentToolEffect(4, -1);
                        pRec[0] = 0xd;
                    }
                    break; }

                case 0xd: {
                    if (!CITIZEN->AnimationFinished(pRec[9]))
                        break;
                    if (!(CITIZEN->GetSkill() >= DAT_01687a14))
                        break;
                    char ok = 1;
                    if (B8(pRec, 0x28) != 0) {
                        void* lm = FUN_00af13b0(pcVar4, 5, 0);
                        ok = ((EngLayout*)lm)->LookupB(pcVar4, 5, 0);
                    }
                    cOut = 0;
                    pfS = 0.0f;
                    FUN_00c9af30(pRec[2], &pfS, fDir, &cOut);
                    if (cOut != 1) {
                        float a = SUB34->Radius();
                        float b = VCI(float, (char*)pcVar4 + 0x34, 0x38, 3);
                        if (b > a && ok) {
                            pRec[0] = 8;
                            break;
                        }
                    }
                    pRec[0] = 0xe;
                    break; }

                case 0xe: {
                    iv = SUB34->Handle();
                    if (iv == 0 || F32(iv, 0x134) == 0.0f) {
                        FUN_00da6270(pcVar4, 1);
                        ((void(__thiscall*)(void*, AgentIterator))(*(void***)this)[0x11])(this, it);
                        break;
                    }
                    {
                        float* p1 = (float*)VC0(void*, SPATIAL, 0x2c);
                        float* p2 = (float*)VC0(void*, (char*)iv + 0x34, 0x2c);
                        fDir[0] = p2[0] - p1[0];
                        fDir[1] = p2[1] - p1[1];
                        fDir[2] = p2[2] - p1[2];
                        FUN_00449c20(fPnt, fDir);
                        void* u = VC3(void*, SPATIAL, 0x2c, fPnt, DAT_01572070, DAT_0157206c);
                        CITIZEN->MoveToPointAndFacingAtSpeed(2, u, fPnt, DAT_01572070, DAT_0157206c);
                    }
                    pRec[0] = 0xf;
                    break; }

                case 0xf: {
                    if (*(void**)((char*)pcVar4 + 0xfc8) == *(void**)((char*)pcVar4 + 0xfc4)) {
                        if (CITIZEN->DoSpotCheck(0, 0) == 0)
                            break;
                    }
                    if (!((Locomotive*)SPATIAL)->IsNearGoal())
                        break;
                    iv = SUB34->Handle();
                    pRec[9] = CITIZEN->PlayAnimationWithTarget(
                                  0x2796b30,
                                  iv ? (int)((char*)iv + 0x34) : 0,
                                  -1,
                                  (int)(size_t)(*(void**)((char*)pcVar4 + 0xfc8)));
                    pRec[0] = 0x10;
                    break; }

                case 0x10: {
                    vOut = -1;
                    if (!CITIZEN->WaitForAnimEventOrEnd(DAT_015841a8, &vOut, 0x2796b30, pRec[9], 1))
                        break;
                    CITIZEN->SetToolFacing(DAT_0169eee0, DAT_0169eee4, DAT_0169eee8);
                    iv = SUB34->Handle();
                    CITIZEN->SetToolArg(1);
                    CITIZEN->PerformSocialAction((int)(size_t)iv, -1);
                    pRec[0] = 0x11;
                    break; }

                case 0x11: {
                    if (!CITIZEN->AnimationFinished2(pRec[9]))
                        break;
                    FUN_00d72720(*(void**)(self + 0xc0), pRec[1]);
                    pRec[1] = -1;
                    iv = SUB34->Handle();
                    if (iv == 0) {
                        FUN_00da6270(pcVar4, 1);
                        ((void(__thiscall*)(void*, AgentIterator))(*(void***)this)[0x11])(this, it);
                    } else {
                        pRec[0] = 0x12;
                    }
                    break; }

                case 0x12: {
                    int r = FUN_00dba630(pcVar4, 0xd);
                    pRec[8] = r;
                    if (r != -1)
                        pRec[0] = 0x13;
                    break; }

                case 0x13: {
                    if (!((Locomotive*)SPATIAL)->IsNearGoal())
                        break;
                    iv = SUB34->Handle();
                    if (iv == 0) {
                        FUN_00da6270(pcVar4, 1);
                        ((void(__thiscall*)(void*, AgentIterator))(*(void***)this)[0x11])(this, it);
                        break;
                    }
                    void* target = *(void**)((char*)pcVar4 + 0xfc8);
                    void* slot = CITIZEN->FindSlotByCombatant((int)((char*)iv + 0x34), 0);
                    if (slot)
                        target = *(void**)slot;
                    void* at = *(void**)((char*)pfStack_118 + 0x260);
                    at = at ? (char*)at + 0x34 : 0;
                    pRec[9] = CITIZEN->InterruptAnimationWithTarget(
                                  0x4ffb325, (int)(size_t)at, -1, (int)(size_t)target);
                    pRec[0] = 0x14;
                    break; }

                case 0x14: {
                    vOut = -1;
                    if (!CITIZEN->WaitForAnimEventOrEnd(DAT_015841a8, &vOut, 0x4ffb325, pRec[9], 1))
                        break;
                    pfS = 0.0f;
                    iv = SUB34->Handle();
                    if (iv != 0) {
                        if (VC0(char, (char*)pfStack_118 + 0x120, 0x58)) {
                            int m = I32(iv, 0x12c);
                            if (m == 0 || m == 3) {
                                pfS = Bits((int)0xb4784a89u);
                                if (((Tribe*)pfStack_118)->WaterOkA()) {
                                    if (!((Tribe*)pfStack_118)->WaterOkB())
                                        pfS = Bits((int)0x45f966abu);
                                }
                                void* ev = CITIZEN->MakeEvent(
                                    bufA, bufB,
                                    *(void**)((char*)pfStack_118 + 0x234),
                                    0, (float)(i64)F32(iv, 0x134));
                                FUN_00e398e0(pfS, ev);
                            }
                            ((Tribe*)pfStack_118)->UpdateWater(F32(iv, 0x134));
                            F32(self, 0x94) = F32(self, 0x94) + F32(iv, 0x134);
                            void* r = FUN_00b3d2b0b((int)(size_t)iv,
                                                    (int*)((char*)pfStack_118 + 0x20c));
                            ((EngVec*)r)->Add3((int)(size_t)iv,
                                               (int*)((char*)pfStack_118 + 0x20c));
                        }
                    }
                    if (pRec[8] >= 0)
                        ((Tribe*)pfStack_118)->FindSpot(0xd, pRec[8]);
                    cOut = 0;
                    pfS = 0.0f;
                    FUN_00c9af30(pRec[2], &pfS, fDir, &cOut);
                    if (cOut != 0) {
                        FUN_00da6270(pcVar4, 1);
                        ((void(__thiscall*)(void*, AgentIterator))(*(void***)this)[0x11])(this, it);
                        break;
                    }
                    if (!VC0(char, SPATIAL, 0x58)) {
                        FUN_00da6270(pcVar4, 1);
                        ((void(__thiscall*)(void*, AgentIterator))(*(void***)this)[0x11])(this, it);
                        break;
                    }
                    if (B8(pRec, 0x28) != 0) {
                        void* lm = FUN_00af13b0(pcVar4, 5, 0);
                        if (((EngLayout*)lm)->LookupB(pcVar4, 5, 0) == 0) {
                            FUN_00da6270(pcVar4, 1);
                            ((void(__thiscall*)(void*, AgentIterator))(*(void***)this)[0x11])(this, it);
                            break;
                        }
                    }
                    pRec[0] = 0;
                    break; }

                case 0x15: {
                    if (!(CITIZEN->GetSkill() <= DAT_01687a14))
                        goto CASE15_SPOT;
                    if (!(0.01f < SUB34->Radius()))
                        goto CASE15_SPOT;
                    iv = SUB34->Handle();
                    if (iv == 0) {
                        CITIZEN->InterruptAnimation(0x2796b31, CITIZEN->AnimHandle(), 0);
                    } else {
                        CITIZEN->InterruptAnimationWithTarget(
                            0x2796b31, (int)((char*)iv + 0x34), -1, CITIZEN->AnimHandle());
                    }
                    pRec[0] = 0x16;
                    break;
                CASE15_SPOT:
                    cOut = 0;
                    pfS = 0.0f;
                    FUN_00c9af30(pRec[2], &pfS, fDir, &cOut);
                    if (CITIZEN->GetSkill() < DAT_01687a10 || cOut != 0) {
                        pRec[0] = 0xe;
                    } else {
                        pRec[0] = 6;
                        B8(pRec, 0x29) = 1;
                    }
                    break; }

                case 0x16: {
                    vOut = -1;
                    if (!CITIZEN->WaitForAnimEventOrEnd(DAT_015841a8, &vOut, -1, 0, 1))
                        break;
                    {
                        float a = SUB34->Radius();
                        float b = DAT_01581298;
                        float m = (b <= a) ? b : a;
                        void* r = FUN_00b3d2b0(m, (char*)pcVar4 + 0x34, 0);
                        ((EngVec*)r)->Add2((char*)pcVar4 + 0x34, 0, 3);
                    }
                    if (SUB34->Handle() == 0) {
                        void* r = FUN_00b3d2b0(0.0f, (char*)pcVar4 + 0x34, 3);
                        ((EngVec*)r)->Add(0.0f, (char*)pcVar4 + 0x34, 3);
                    }
                    CITIZEN->SetCurrentToolEffect(CITIZEN->HasTool() ? 8 : 10, -1);
                    pRec[0] = 0x18;
                    break; }

                case 0x18: {
                    if (!CITIZEN->AnimationFinished(0))
                        break;
                    pRec[0] = 0x19;
                    CITIZEN->PlayAnimation(0x2796b38, 1, CITIZEN->AnimHandle());
                    break; }

                case 0x19: {
                    if (!CITIZEN->AnimationFinished(0))
                        break;
                    CITIZEN->AddSkill(DAT_0158129c * DAT_01581298 + CITIZEN->GetSkill());
                    ((EngSub34*)((char*)pcVar4 + 0x5a8))->Radius();
                    F32(self, 0x94) = DAT_015812a0 * DAT_01581298;
                    pRec[0] = 0x15;
                    CITIZEN->SetCurrentToolEffect(0, -1);
                    break; }
                }
            }
        }
        it.Next();
    } while (!it.IsDone());

    return 1;
}

// @ 0x00d75400
void cTribeGameBehaviorFish_s00d7_5400::CalledByStimulus(cGameObject* a1, cStimulus* a2)
{
    OnLayout(a1, a2);

    if (a2 != 0 && a2->mKind_14 == 1)
    {
        RefText* target;
        if (a1 != 0)
            target = &a1->mField58;
        else
            target = 0;
        mObj74.FUN_00d73bc0(&target)->mFlag_28 = 1;
    }
}
