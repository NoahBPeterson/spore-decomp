// src/game/SPGonzago/SPCitizenBehaviorTree.cpp -- migrated from slice(s) s00d97420, s00d964a0, s00d95c40, s00d93fd0, s00d93230, s00d922f0, s00d91540, s00d90640 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPCitizenBehaviorTree.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "nSPBehaviorTree/behavior_memory_block.h"
#include "EA/Random/RandomLinearCongruential.h"
#include "nSPBehaviorTree/behavior_stimuli.h"
#include "SP/cActionCircle.h"
#include "SP/cCity.h"
#include "SP/cCityVisualizer.h"
#include "SP/cCombatant.h"
#include "SP/cCommunity.h"
#include "SP/cGameNounManager.h"
#include "SP/cLocomotiveObject.h"
#include "SP/cPlanetModel.h"
#include "SP/cSPCreatureCitizen.h"
#include "SP/cSPCreatureBase.h"
#include "cSPVector3.h"
#include <math.h>
#include "SP/cCityWalls.h"
#include "SP/cViewer.h"
#include <float.h>
#include "SP/cAnimatingCreature.h"

// ---- items of slice s00d90640 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define PVN(n) virtual void pv##n();
struct Vec3 { float x, y, z; };
namespace EA {
namespace Random {
class RandomLinearCongruential_s00d9_0640 {
public:
    uint32_t RandomUint32Uniform(uint32_t limit);       // 0x00a68fb0
};
}
}
extern EA::Random::RandomLinearCongruential_s00d9_0640 sMathRandom;  // 0x01601760
namespace nSPBehaviorTree {
struct behavior_stimuli_s00d9_0640 {
    int   Play(int a, int b);                           // 0x00bc96a0
    void  ClearAll(int a, int b);                       // 0x00bc98f0
    void* GetAny();                                     // 0x00d997e0
};
}
struct TickState  { int mMode; float mf4; };            // +0x00 / +0x04
struct AdmireState { char mFlag; uint8_t pad0[3]; int mCount; };     // +0x00 / +0x04
struct RubbleState { char mFlag; uint8_t pad0[3]; int mId; int mAnim; };  // +0x00 / +0x04 / +0x08
class cActionCircle_s00d9_0640 {                                   // 0x00afae50 / 0x00d5c470 / 0x00d5c580
public:
    void RemoveAgent(void* agent);                      // 0x00afae50
};
class cAgentPos {                                       // 0x00afad70
public:
    int CheckPosition(Vec3* pos);                       // 0x00afad70
};
class cBehaviorAgent {                                  // the object at cSPCreatureCitizen+0xfb8
public:
    uint8_t       mPad000[0x70];                        // +0x000
    cActionCircle_s00d9_0640 mCircle070;                           // +0x070
    uint8_t       mPad071[0xd4 - 0x71];                 // +0x071 .. +0x0d3
    cAgentPos     mPos;                                 // +0x0d4
    uint8_t       mPad0D5[0x1a8 - 0xd5];                // +0x0d5 .. +0x1a7
    int           mn1A8;                                // +0x1a8
    int           mn1AC;                                // +0x1ac
    uint8_t       mPad1B0[0x1bc - 0x1b0];               // +0x1b0 .. +0x1bb
    cActionCircle_s00d9_0640 mCircle1BC;                           // +0x1bc
    uint8_t       mPad1BD[0x1c8 - 0x1bd];               // +0x1bd .. +0x1c7
    uint32_t      mn1C8;                                // +0x1c8
    uint8_t       mPad1CC[0xa28 - 0x1cc];               // +0x1cc .. +0xa27
    int           mnA28;                                // +0xa28
    int           mUnkA2C;                              // +0xa2c
    int           mnA30;                                // +0xa30
    int           mUnkA34;                              // +0xa34
    int           mnA38;                                // +0xa38
    int           mUnkA3C;                              // +0xa3c
    int           mUnkA40;                              // +0xa40
    int           mnA44;                                // +0xa44
    uint8_t       mUnkA48[8];                           // +0xa48 .. +0xa4f
    uint8_t       mbA50;                                // +0xa50

    int* GetCounter(uint32_t idx);                      // 0x00d576b0
    void EnterZone(void* p, int b);                     // 0x00d5c470
    void ExitZone(void* p);                             // 0x00d5c580
};
class cBehaviorStimuliOwner {
public:
    uint8_t  mPad000[8];                                // +0x00
    nSPBehaviorTree::behavior_stimuli_s00d9_0640 mStimuli;         // +0x08
    uint8_t  mPadStim[0x1c8 - 9];                       // +0x09 .. +0x1c7
    uint32_t mn1C8;                                     // +0x1c8
};
class cLocomotiveObject_s00d9_0640 {
public:
    PVN(0) PVN(1) PVN(2) PVN(3) PVN(4) PVN(5) PVN(6) PVN(7) PVN(8) PVN(9) PVN(10)
    virtual Vec3* GetPosition();                        // +0x2c
    PVN(12) PVN(13) PVN(14) PVN(15) PVN(16) PVN(17) PVN(18) PVN(19) PVN(20) PVN(21)
    PVN(22) PVN(23) PVN(24) PVN(25)
    virtual void* GetAux68();                           // +0x68
    uint8_t mPad04[0x5c];                               // +0x04 .. +0x5f (size 0x60)
    char IsNearGoal();                                  // 0x00c42e20
};
class cCombatant_s00d9_0640 {
public:
    PVN(0) PVN(1) PVN(2) PVN(3) PVN(4)
    PVN(5) PVN(6) PVN(7) PVN(8) PVN(9) PVN(10) PVN(11) PVN(12) PVN(13) PVN(14)
    PVN(15) PVN(16) PVN(17) PVN(18) PVN(19) PVN(20) PVN(21)
    virtual float GetMaxHealth();                       // +0x58
    uint8_t mPad04[0x11];                               // +0x04
    char    mb15;                                       // +0x15
    uint8_t mPad16[0x22];                               // +0x16 .. +0x37
    float   mfHealth38;                                 // +0x38
    uint8_t mPad3c[4];                                  // +0x3c .. +0x3f (size 0x40)
    int GetDamageState();                               // 0x008e7f80
};
class cCommunity_s00d9_0640 {
public:
    PVN(0) PVN(1) PVN(2) PVN(3) PVN(4) PVN(5) PVN(6) PVN(7) PVN(8) PVN(9) PVN(10)
    PVN(11) PVN(12) PVN(13) PVN(14) PVN(15) PVN(16) PVN(17) PVN(18) PVN(19) PVN(20)
    PVN(21)
    virtual float GetCap58();                           // +0x58
    uint8_t mPad04[0x34];                               // +0x04 .. +0x37 (size 0x38)
    void EnsureTimer(void* agent);                      // 0x00bfddc0
};
class cCityVisualizer_s00d9_0640 {
public:
    PVN(0)
    void StartSpecialVignette(void* spec, void* pCitizen);   // 0x00d5f4d0
};
class cCity_s00d9_0640 {
public:
    PVN(0)
    uint8_t mPad04[0x2d0 - 0x04];                       // +0x04 .. +0x2cf
    int     mn2D0;                                      // +0x2d0
    int  GetVehicleSpecialty();                         // 0x00bd81d0
    int  FUN_00bd8190();                                // 0x00bd8190
    void FUN_00bd8170(int v);                           // 0x00bd8170
};
class cSPCreatureCitizen_s00d9_0640 {
public:
    // ---- vtable ----
    PVN(0)  PVN(1)  PVN(2)  PVN(3)  PVN(4)  PVN(5)  PVN(6)  PVN(7)  PVN(8)  PVN(9)
    PVN(10) PVN(11) PVN(12) PVN(13) PVN(14) PVN(15) PVN(16) PVN(17) PVN(18)
    virtual int   GetIdentity();                        // +0x4c
    PVN(20) PVN(21) PVN(22) PVN(23) PVN(24) PVN(25) PVN(26) PVN(27) PVN(28) PVN(29)
    PVN(30) PVN(31) PVN(32) PVN(33) PVN(34)
    virtual void  Flag8c();                             // +0x8c
    PVN(36) PVN(37)
    virtual int   GetMode98();                          // +0x98
    virtual void  SetMode9c(int);                       // +0x9c
    PVN(40) PVN(41) PVN(42) PVN(43) PVN(44) PVN(45) PVN(46) PVN(47) PVN(48) PVN(49)
    virtual void  FlagC8(int);                          // +0xc8

    // ---- data ----
    uint8_t  mPad04[0xbc];                              // +0x04 .. +0xbf
    cLocomotiveObject_s00d9_0640 mLoco;                            // +0xc0 (size 0x60)
    cCombatant_s00d9_0640 mCombatant;                              // +0x120 (size 0x40)
    uint8_t  mPad160[0x448];                            // +0x160 .. +0x5a7
    cCommunity_s00d9_0640 mCommunity;                              // +0x5a8 (size 0x38)
    float    mf5E0;                                     // +0x5e0
    uint8_t  mPad5e4[0x568];                            // +0x5e4 .. +0xb4b
    cBehaviorStimuliOwner* mpB4C;                       // +0xb4c
    uint8_t  mPadB50[0x440];                            // +0xb50 .. +0xf8f
    char     mbF90;                                     // +0xf90
    uint8_t  mPadF91[0x27];                             // +0xf91 .. +0xfb7
    cBehaviorAgent* mpFB8;                              // +0xfb8
    char     mbFBC;                                     // +0xfbc
    uint8_t  mPadFBD[3];                                // +0xfbd .. +0xfbf
    int      mnFC0;                                     // +0xfc0
    uint8_t  mPadFC4[0x2c];                             // +0xfc4 .. +0xfef
    int      mnFF0;                                     // +0xff0
    uint8_t  mPadFF4[0x418];                            // +0xff4 .. +0x140b
    void*    mp140C;                                    // +0x140c  iterator begin
    void*    mp1410;                                    // +0x1410  iterator end

    // ---- helpers (thiscall, self == citizen) ----
    bool Flag388();                                     // 0x00c0c0e0
    int  GetAnimGuid();                                 // 0x00c0e040
    int  FUN_00c0e370();                                // 0x00c0e370
    void SetSprinting(int s);                           // 0x00c1ad10
    void InterruptAnimation(int anim, int a, int b);    // 0x00c12310
    int  PlayAnimation(int anim, int a, int b);         // 0x00c12190
    char AnimationFinished(int anim);                   // 0x00c123f0
    void Show();                                        // 0x00c0f2b0
    cCity_s00d9_0640* GetCity();                                   // 0x00c23e40
    uint32_t FUN_00c227b0();                            // 0x00c227b0
    void SetCurrentToolEffect(int a, int b);            // 0x00c24f40
    void FUN_00c0d0c0(int a, int b);                    // 0x00c0d0c0
};
void* GetCurrentGameMode();                             // 0x00b5b800
// ---- items of slice s00d90640 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern EA::Random::RandomLinearCongruential_s00d9_0640 sMathRandom;  // 0x01601760

// ---- items of slice s00d91540 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl SP_PlanetModel();                 // 0x00b3d350
extern "C" void  __cdecl FUN_00d90ac0(void*, void*);       // 0x00d90ac0
extern "C" double __cdecl pow(double, double);
typedef unsigned int   u32;
typedef int            s32;
typedef unsigned char  u8;
typedef float          f32;
typedef void  (__thiscall* FnV)(void*);
typedef void  (__thiscall* Fn1)(void*, u32);
typedef void* (__thiscall* FnP)(void*);
typedef u32   (__thiscall* FnU1P)(void*, void*);
void* FUN_00b3d4e0();                                        // 0x00b3d4e0
struct Vec3f;
struct C14750 { void Do(u32); };                           // 0x00c14750
struct BC3DF0 { u8   Do(u32); };                           // 0x00bc3df0
struct BC52A0 { void Do(u32, u32); };                      // 0x00bc52a0
struct BC5040 { void Do(u32); };                           // 0x00bc5040
struct BC64A0 { u32  Do(u32, u32, u32, u32); };            // 0x00bc64a0
struct BC4900 { void Do(u32, u32, u32); };                  // 0x00bc4900
struct C0E370 { s32  Do(); };                              // 0x00c0e370
struct C0E0C0 { u8   Do(u32); };                           // 0x00c0e0c0
struct NearGoal { u8  Do(); };                             // 0x00c42e20
struct PlayAnim { u32  Do(u32, u32, u32); };               // 0x00c12190
struct PlayAnim2 { u32 Do(u32, u32, u32); };               // 0x00c12190
struct Interrupt { void Do(u32, u32, u32); };              // 0x00c12310
struct MoveTo { void Do(u32, void*, f32, f32); };          // 0x00c1c1d0
struct GetCity { void* Do(); };                            // 0x00c23e40
struct GetLane { void** Do(); };                           // 0x0095fa00
struct RandDbl { float Do(); };                            // 0x009360d0
struct RandU32 { u32  Do(u32); };                          // 0x00a68fb0
struct Sub5A8 { u8 mPad[0x38]; void Set(f32); };           // 0x00f924e0
struct PlanetModel {
    Vec3f* MakeRandomWorldPosition(void*, void*, f32, f32); // 0x00b81780
};
struct Vec3f { f32 x, y, z; };
struct C0Sub { void* mpVtbl; };                            // +0x00
struct LaneNode { Vec3f v; u8 mPad0C[0x14]; };
struct LaneInfo { LaneNode* mpBegin; LaneNode* mpEnd; };
struct FB8Obj {
    u8      mPad000[0x144];                                // +0x000
    Vec3f*  mpBegin;                                       // +0x144
    Vec3f*  mpEnd;                                         // +0x148
};
struct B54Obj { u8 mPad00[0x80]; f32 mf80; };
struct Creature {
    void*   mpVtbl;                                        // +0x000
    u8      mPad004[0x0c0 - 0x004];
    C0Sub   mC0;                                           // +0x0c0
    u8      mPad0C4[0x110 - 0x0c4];
    u32     mn110;                                         // +0x110
    u8      mPad114[0x2b0 - 0x114];
    u32     mn2B0;                                         // +0x2b0
    u8      mPad2B4[0x5a8 - 0x2b4];
    Sub5A8  mSub5A8;                                       // +0x5a8
    f32     mf5E0;                                         // +0x5e0
    u8      mPad5E4[0xb54 - 0x5e4];
    void*   mpB54;                                         // +0xb54
    u8      mPadB58[0xb5e - 0xb58];
    u8      mbB5E;                                         // +0xb5e
    u8      mPadB5F[0xb62 - 0xb5f];
    u8      mbB62;                                         // +0xb62
    u8      mPadB63[0xfb8 - 0xb63];
    void*   mpFB8;                                         // +0xfb8
};
struct AnimState {
    u8  mPad00[0x0c];                                      // +0x00
    u8  mb0C;                                              // +0x0c
    u8  mPad0D[3];
    u32 mn10;                                              // +0x10
    u32 mn14;                                              // +0x14
};
struct DeadState {
    u32 mn00;                                              // +0x00
    f32 mf04;                                              // +0x04
    u32 mn08;                                              // +0x08
    f32 mf0C;                                              // +0x0c
    union { u32 mn10; u8 mb10; };                          // +0x10
    union { f32 mf14; u32 mn14; };                         // +0x14
    u8  mb18;                                              // +0x18
    u8  mPad19[3];
};
struct UfoState { u8 mb00; u8 mPad01[3]; f32 mf04; };
// ---- items of slice s00d91540 end

// ---- items of slice s00d922f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define PV(n) virtual void pv##n();
struct PlanetModel_s00d9_22f0;
PlanetModel_s00d9_22f0* GetPlanetModel();                             // 0x00b3d350
struct PlanetModel_s00d9_22f0 {
    Vec3* MakeRandomWorldPosition(Vec3* out, const Vec3* center, float minDist, float maxDist); // 0x00b81780
    Vec3* DirectionToSurfacePosition(Vec3* out, const Vec3* pos);                               // 0x00b815a0
};
int   GetPlayerEmpireID();                                 // 0x01021090
namespace EA {
namespace Random {
class RandomLinearCongruential_s00d9_22f0 {
public:
    uint32_t RandomUint32Uniform(uint32_t limit);          // 0x00a68fb0
    double   RandomDoubleUniform();                        // 0x009360d0
};
}
}
extern EA::Random::RandomLinearCongruential_s00d9_22f0 sMathRandom_s00d9_22f0;   // 0x01601760
struct AnimState_s00d9_22f0 {                                         // cAnimState, returned by cAnimationPlayer::Play
    uint8_t mPad00[0x0c];
    Vec3    mPoint;                                        // +0x0c
    float   mf18;                                          // +0x18
    int     mi1c;                                          // +0x1c
};
struct AnimPlayer {
    uint8_t   mPad00[0x100];
    AnimState_s00d9_22f0* Play(uint32_t anim, uint32_t flags);        // 0x00bc96a0
    void       ClearAll(uint32_t flags, uint32_t mode);    // 0x00bc98f0
};
struct AnimComponent {                                     // at creature + 0xb4c
    uint8_t    mPad00[8];
    AnimPlayer mPlayer;                                    // +0x08
};
struct TimedPoint { float mTime; Vec3 mPoint; };           // +0,+4,+8,+0xc
struct DangerState {                                       // +0,+4,+8,+0x14
    float mf0;
    float mf4;
    Vec3  mCached;                                         // +0x08
    int   mEmpire;                                         // +0x14
};
struct CollisionInfo { uint8_t mPad000[0x258]; float mRadius; };
struct LanePoint { Vec3 mPoint; uint8_t mPad0C[0x20 - 0x0c]; };   // stride 0x20
struct LaneArray { LanePoint* mpBegin; LanePoint* mpEnd; };
struct PtrArray  { void** mpBegin; void** mpEnd; };
struct City;
struct Owner;
struct Creature_s00d9_22f0;
struct CitySub {                                           // city + 0x120
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
    virtual const Vec3* GetPosition();                     // +0x2c
};
struct City {
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12)
    PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19) PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26)
    virtual CollisionInfo* GetCollisionInfo();             // +0x6c
    uint8_t mPad004[0x120 - 4];
    CitySub mSub;                                          // +0x120
    uint8_t mPad124[0x2d0 - 0x124];
    int     mCounter2D0;                                   // +0x2d0
    int  F8190();                                          // 0x00bd8190
    void F8170(int value);                                 // 0x00bd8170
    LaneArray* GetLaneInfo();                              // 0x0095fa00
};
struct ActionSlot {
    uint8_t mPad00[0x0c];
    Vec3    mPos;                                          // +0x0c
    void Reserve(Creature_s00d9_22f0* c);                             // 0x00afa030
};
struct ActionCircle {
    uint8_t mPad00[0x14];
    ActionSlot* FindSlot(const Vec3* pos);                 // 0x00afad70
};
struct Owner {                                             // creature + 0xfb8
    uint8_t      mPad000[0xd4];
    ActionCircle mCircle;                                  // +0xd4
    Vec3         mV0E8;                                    // +0xe8
    uint8_t      mPad0F4[0x138 - 0xf4];
    Vec3         mV138;                                    // +0x138
    uint8_t      mPad144[0x1b0 - 0x144];
    Vec3         mV1B0;                                    // +0x1b0
    const Vec3*  FUN_00d579a0(Creature_s00d9_22f0* c);                // 0x00d579a0
};
struct StimulusSource {                                    // creature + 0xb54
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12)
    PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19) PV(20) PV(21)
    virtual void GetTargetInfo(int* pAnimId, int a, int* pCount, int b);   // +0x58
};
struct Locomotion {                                        // creature + 0xc0
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
    virtual const Vec3* GetPosition();                     // +0x2c
    PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19) PV(20) PV(21) PV(22)
    virtual const Vec3* GetForward(Vec3* tmp);             // +0x5c
    PV(24) PV(25) PV(26)
    virtual CollisionInfo* GetCollisionInfo();             // +0x6c
    PV(28)
    virtual float GetScale();                              // +0x74
    PV(30) PV(31) PV(32) PV(33) PV(34) PV(35) PV(36) PV(37) PV(38) PV(39)
    PV(40) PV(41) PV(42) PV(43) PV(44) PV(45) PV(46) PV(47) PV(48) PV(49)
    PV(50) PV(51) PV(52) PV(53) PV(54) PV(55) PV(56) PV(57) PV(58)
    virtual void StopMoving();                             // +0xec
    bool        IsNearGoal();                              // 0x00c42e20
    PtrArray*   GetNearbyList();                           // 0x00c420d0
};
struct Creature_s00d9_22f0 {
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12)
    PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19) PV(20) PV(21) PV(22) PV(23) PV(24) PV(25)
    PV(26) PV(27) PV(28) PV(29) PV(30) PV(31) PV(32) PV(33) PV(34) PV(35) PV(36) PV(37)
    virtual int  GetState();                               // +0x98
    virtual void SetState(int state);                      // +0x9c

    uint8_t        mPad004[0xc0 - 4];
    Locomotion     mLoco;                                  // +0xc0
    uint8_t        mPad0C4[0xb4c - 0xc0 - sizeof(Locomotion)];
    AnimComponent* mAnim;                                  // +0xb4c
    uint8_t        mPad0B50[0xb54 - 0xb50];
    StimulusSource* mpSourceB54;                           // +0xb54
    uint8_t        mPadB58[0xfb8 - 0xb58];
    Owner*         mpOwner;                                // +0xfb8
    uint8_t        mPadFBC[0x1010 - 0xfbc];
    City*          mpCity;                                 // +0x1010

    City* GetCity();                                       // 0x00c23e40
    void InterruptAnimation(uint32_t anim, int a, int b);  // 0x00c12310
    void MoveToPointAtSpeed(int mode, const Vec3* pos, float speed, float turn);   // 0x00c1c1d0
    void MoveToPointAndFacingAtSpeed(int mode, const Vec3* pos, const Vec3* facing,
                                     float speed, float turn);                     // 0x00c1c5c0
    void SetSprinting(int on);                             // 0x00c1ad10
};
void RunFromDanger_ChooseDestination(Creature_s00d9_22f0* c, Vec3* cached, Vec3* dest);   // 0x00d92990
// ---- items of slice s00d922f0 end

// ---- items of slice s00d93230 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" float __cdecl sqrtf(float);
typedef double f64;
#define VT(p) (*(void***)(p))
struct cSub;
struct cObj;
struct COps {
    // cSPCreatureBase / cLocomotiveObject / cSpatialObject
    u8    FUN_00c42e20();                 // 0x00c42e20 IsNearGoal
    void* FUN_00c42de0();                 // 0x00c42de0 position
    u8    FUN_00c123f0(u32);              // 0x00c123f0 AnimationFinished
    void  FUN_00c12190(u32, u32, u32);    // 0x00c12190 PlayAnimation
    void  FUN_00c12310(u32, u32, u32);    // 0x00c12310 InterruptAnimation
    void  FUN_00c1c1d0(u32, const void*, f32, f32);           // 0x00c1c1d0 MoveToPointAtSpeed
    void  FUN_00c1c5c0(u32, const void*, const void*, f32, f32); // 0x00c1c5c0 MoveToPointAndFacingAtSpeed
    void  FUN_00c1ad10(bool);             // 0x00c1ad10 SetSprinting
    void* FUN_00c23e40();                 // 0x00c23e40 GetCity

    // cBehavior / cActionCircle
    void* FUN_00afad70(void*);            // 0x00afad70 slot lookup
    void  FUN_00afa030(void*);            // 0x00afa030 tSlot::Reserve
    u32   FUN_00af9fa0();                 // 0x00af9fa0 CountOccupiedSlots
    void  FUN_00afae50(void*);            // 0x00afae50 RemoveAgent

    // misc
    void  FUN_00bc98f0(u32, u32);         // 0x00bc98f0 behavior_stimuli::ClearAll
    void  FUN_00bec2d0(const void*, u32); // 0x00bec2d0 RequestPosition
    void* FUN_00b81780();                 // 0x00b81780 MakeRandomWorldPosition
    void  FUN_00b815a0(const void*);      // 0x00b815a0 DirectionToSurfacePosition
    u32   FUN_00a68fb0(u32);              // 0x00a68fb0 RandomUint32Uniform
    f32   FUN_009360d0();                 // 0x009360d0 RandomDoubleUniform
};
#define MOPS(p) ((COps*)(p))
struct cSub {
    u8    pad000[0x1bc];
    u8    m1bc;
    u8    pad1bd[0x1d0 - 0x1bd];
    f32   m1d0, m1d4, m1d8;
    u8    pad1dc[0x220 - 0x1dc];
    u32   m220;
    u32   m224;
    u8    pad228[0x38c - 0x228];
    void* m38c;
    u8    pad390[0x9f4 - 0x390];
    u32   m9f4;
    u8    pad9f8[0xa14 - 0x9f8];
    f32   mA14, mA18, mA1c, mA20, mA24, mA28;
    u8    padA2c[0xa38 - 0xa2c];
    s32   mA38, mA3c;
    u8    padA40[0xa44 - 0xa40];
    s32   mA44;
    u8    padA48[0xaf0 - 0xa48];
    void* mAF0;
    u8    padAF4[0xb80 - 0xaf4];
    u8*   mB80;
    u8*   mB84;
    u8    padB88[0xb94 - 0xb88];
    u8*   mB94;
    u8*   mB98;
};
struct cEntry {
    u32 key;
    u32 count;
};
struct cState {
    u8  m0;
    u8  pad1[3];
    u32 m4;
};
struct cSlot {
    u8  pad0[0xc];
    f32 x, y, z;
};
struct cStimuli {
    u8  pad0[8];
    u8  mOp;
};
struct cObj {
    u8    pad000[0xc0];
    u8    mC0[0xb4c - 0xc0];
    void* mB4c;
    u8    padB50[0xfb8 - 0xb50];
    cSub* mFB8;
    u8    padFBC[0xff0 - 0xfbc];
    u32   mFF0;
};
extern f32 g14853e0;   // 4.0f
extern f32 g1470f1c;   // 2.0f
extern f32 g13ec4b8;   // 1e-8f
extern f32 g140c6e8;   // 32.0f
extern f32 g1485378;   // 0.0f
extern f32 g169ec74, g169ec78, g169ec7c;
extern f32 g169f20c, g169f210, g169f214;
void* __stdcall FUN_00b3d350(void*, void*, f32, f32);   // 0x00b3d350 PlanetModel
// ---- items of slice s00d93230 end

// ---- items of slice s00d93fd0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct PlanetModel_s00d9_3fd0 {                      // cPlanetModel singleton
    Vec3* MakeRandomWorldPosition(Vec3* out, const Vec3* center, float minDist, float maxDist); // 0x00b81780
};
PlanetModel_s00d9_3fd0* GetPlanetModel_s00d9_3fd0();            // 0x00b3d350
Vec3*  GetNearestLaneNode(Vec3* out, void* citizen);      // 0x00d917f0
Vec3*  normalized_safe(Vec3* out, const Vec3* in);         // 0x00449c20
struct Viewer;
class AppObject {                         // returned by App() (0x0067dd10)
 public:
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12) PV(13) PV(14)
    PV(15) PV(16) PV(17) PV(18) PV(19)
    virtual void* Slot50();                                // +0x50 (slot 20)
};
class ViewerHolder {                      // returned by AppObject::Slot50()
 public:
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6)
    virtual Viewer* GetViewer_1c();                        // +0x1c (slot 7)
};
class Viewer {
 public:
    void GetCameraLocationInfo(Vec3* out, void* a, void* b, void* c) const;  // 0x007c3d30
};
AppObject* App();                         // 0x0067dd10
class BehaviorStimuli {                   // at creature + 0xb4c + 8
 public:
    void ClearAll(int a, int b);                           // 0x00bc98f0
    void* GetAny();                                        // 0x00d997e0
};
class StimuliZone {                        // returned by ProfGetZone()
 public:
    bool Find(uint32_t key, int* out, int n);              // 0x00c0dee0
    void SetPos(const Vec3* p);                            // 0x00c15270
};
class Spatial {                           // sub-object vtable at object + 0x34
 public:
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
    virtual const Vec3* GetPosition();         // +0x2c (slot 11)
};
struct ObjView { uint8_t pad00[0x34]; Spatial mSpatial_34; };
class ActionSlot_s00d9_3fd0 {                         // cActionCircle::tSlot (sizeof 0x18)
 public:
    uint8_t mOccupied;                    // +0x00
    uint8_t mPad01[0x17];                 // +0x01 .. 0x18
    void Clear();                         // 0x00afa0a0
    void Reserve(void* gameData);         // 0x00afa030
};
class ActionCircle_s00d9_3fd0 {
 public:
    uint8_t  mPad00[0x14];                // +0x00 .. 0x14
    Vec3     mPos_14;                     // +0x14
    uint8_t  mPad20[0x30];                // +0x20 .. 0x50
    ActionSlot_s00d9_3fd0* mpBegin_50;               // +0x50
    ActionSlot_s00d9_3fd0* mpEnd_54;                 // +0x54
    ActionSlot_s00d9_3fd0* SlotAt(uint32_t idx);     // 0x00af9ff0
};
ActionSlot_s00d9_3fd0* ActionCircleFindSlot(ActionCircle_s00d9_3fd0* circle, const Vec3* p); // 0x00afad70
void  ArtifactSlotClear(void* slot);                       // 0x00dc4c60
struct CityWalls {
    uint8_t  mPad00[0x25c];
    float    mRadius_25c;                                  // +0x25c
    bool     PointInsideInnerWall(const Vec3* p);          // 0x00bec140
};
namespace EA {
namespace Random {
class RandomLinearCongruential_s00d9_3fd0 { public:
    uint32_t RandomUint32Uniform(uint32_t limit);   // 0x00a68fb0
    double   RandomDoubleUniform();                 // 0x009360d0
};
}
}
extern EA::Random::RandomLinearCongruential_s00d9_3fd0 sMathRandom_s00d9_3fd0;   // 0x01601760
namespace SP {
class Citizen;
}
namespace SP {
extern const float kFlTwo;          // 0x01470f1c = 2.0f
}
namespace SP {
extern const float kFlHalf;         // 0x01471064 = 0.5f
}
namespace SP {
extern const float kFlFifteen;      // 0x014007f4 = 15.0f
}
namespace SP {
extern const float kFlOne;          // 0x01485720 = 1.0f
}
namespace SP {
extern const float kFlSix;          // 0x0147b9f0 = 6.0f
}
namespace SP {
extern float       gForcedDeathDistSq;  // 0x0169f204
}
namespace SP {
extern uint32_t    gForcedDeathInit;    // 0x0169f208
}
namespace SP {
extern const float kFlForcedDeathDistSq;// 0x0147c11c = 22500.0f
}
namespace SP {
extern const float kFlThree;        // 0x013eb95c = 3.0f
}
namespace SP {
extern const float kFlFour;         // 0x014853e0 = 4.0f
}
namespace SP {
extern void*       gAnimEventCond;  // 0x01590c54
}
namespace SP {
class Locomotion_s00d9_3fd0 {                        // cLocomotiveObject sub-object at creature + 0xc0
 public:
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
    virtual const Vec3* GetPosition();                 // +0x2c (slot 11)
    PV(12) PV(13)
    virtual void SetPosition(const Vec3* p);           // +0x38 (slot 14)
    PV(15) PV(16) PV(17)
    virtual bool Slot48();                             // +0x48 (slot 18)
    PV(19) PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26) PV(27) PV(28)
    virtual float GetTurnRate();                       // +0x74 (slot 29)

    struct NeighborList { void** mpBegin; void** mpEnd; };   // at +0x278
    NeighborList* GetNeighbors();                      // 0x00c420d0 (returns this + 0x278)
    bool IsNearGoal();                                 // 0x00c42e20
};
}
namespace SP {
class Combatant {                         // cCombatant sub-object at creature + 0x120
 public:
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12) PV(13) PV(14)
    PV(15) PV(16) PV(17) PV(18) PV(19) PV(20) PV(21)
    virtual float GetSize_58();                        // +0x58 (slot 22)
    uint8_t  pad04[0x30];                              // +0x04 .. 0x34
    int      mDamageState_34;                          // +0x34
    float    mHealth_38;                               // +0x38
    uint8_t  pad3c[0x24];                              // +0x3c .. 0x60
    int GetDamageState();                              // 0x008e7f80 (reads [this + 0x34])
};
}
namespace SP {
class City_s00d9_3fd0 {                              // owning city (creature + 0x1010)
 public:
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12) PV(13) PV(14)
    PV(15) PV(16) PV(17) PV(18) PV(19) PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26)
    virtual CityWalls* GetWalls();                     // +0x6c (slot 27)
    uint8_t  pad70[0x11c];                             // +0x04 .. 0x120
    Locomotion_s00d9_3fd0 mCityLoco_120;                          // +0x120
    ActionCircle_s00d9_3fd0* GetActions();                        // 0x00bd7f50 (returns this + 0x450)
    ActionCircle_s00d9_3fd0* GetRoute3ec();                       // 0x00bd7f40 (returns this + 0x3ec)
    void RouteVec(Vec3* a, Vec3* b);                   // 0x00bd7f70
};
}
namespace SP {
struct Owner_s00d9_3fd0 {                            // owner record at creature + 0xfb8
    uint8_t  pad00[0x220];
    uint8_t* mpActionPool_220;                         // +0x220 : cActionCircle pool base (stride 0x64)
    uint8_t  pad224[0xa51 - 0x224];
    uint8_t  mbArtifactNotHeld_0a51;                   // +0xa51
    uint8_t  padA52[0x02];
    void*    mpArtifact_0a54;                          // +0xa54 : held artifact (ref-counted)
    uint8_t  padA58[0xaf0 - 0xa58];
    uint8_t* mpZoneData_af0;                           // +0xaf0

    void         EnterZone(Citizen* c);                // 0x00d5c580 (thiscall)
    void         SetFlag(Citizen* c, bool f);          // 0x00d5c470 (thiscall)
    StimuliZone* GetZone(Citizen* c);                  // 0x00d59170 (thiscall)
};
}
namespace SP {
struct BehaviorTree {                      // behaviour-tree object at creature + 0xb4c
    uint8_t  pad00[0x1c8];
    uint32_t mFlags_1c8;                               // +0x1c8
    uint32_t mField_1cc;                               // +0x1cc
};
}
namespace SP {
class Object {                             // ref-counted object
 public:
    PV(0)
    virtual void Release();                            // +0x04 (slot 1)
};
}
namespace SP {
class Citizen {
 public:
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12) PV(13) PV(14)
    PV(15) PV(16) PV(17) PV(18) PV(19) PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26) PV(27) PV(28)
    PV(29) PV(30) PV(31) PV(32) PV(33) PV(34) PV(35) PV(36) PV(37) PV(38) PV(39) PV(40) PV(41) PV(42)
    PV(43) PV(44) PV(45)
    virtual void* AsInterface_b8(uint32_t id);             // +0xb8 (slot 46)
    uint8_t  pad04[0xc0 - 4];                              // +0x04 .. 0xc0
    Locomotion_s00d9_3fd0 mLoco;                                  // +0xc0 (vptr only)
    uint8_t  pad12[0x120 - 0xc4];                      // +0xc4 .. 0x120
    Combatant  mCombatant;                             // +0x120 (size 0x60)
    uint8_t  pad18[0x5a8 - 0x180];                     // +0x180 .. 0x5a8
    uint32_t mStimulusPayload_5a8;                     // +0x5a8
    uint8_t  pad5ac[0xb20 - 0x5ac];                    // +0x5ac .. 0xb20
    uint32_t mObjectId_0b20;                           // +0xb20
    uint8_t  pad0b24[0xb4c - 0xb24];                   // +0xb24 .. 0xb4c
    BehaviorTree* mpBehaviorTree_0b4c;                 // +0xb4c
    uint8_t  pad0b50[0xfb8 - 0xb50];                   // +0xb50 .. 0xfb8
    Owner_s00d9_3fd0*   mpOwner_0fb8;                             // +0xfb8
    uint8_t  pad0fbc[0xfc4 - 0xfbc];                   // +0xfbc .. 0xfc4
    uint32_t mToolEffectId_fc4;                        // +0xfc4
    void*    mpObject_0x34_hint;                       // (unused; keeps Object view anchored)
    uint8_t  pad0fcc[0x1010 - 0xfcc];                  // +0xfcc .. 0x1010
    City_s00d9_3fd0*    mpCity_1010;                              // +0x1010

    City_s00d9_3fd0* GetCity();                                   // 0x00c23e40 (returns [this + 0x1010])
    bool  IsValidTarget_c232c0();                      // 0x00c232c0
    void PlayAnimation(uint32_t anim, int a, int b);                           // 0x00c12190
    bool WaitForAnimEventOrEnd(void* cond, int* outId, int a, int b, int c);   // 0x00c14ef0
    void SetCurrentToolEffect(int tool, unsigned int id);                      // 0x00c24f40
    void SetSprinting(bool on);                                               // 0x00c1ad10
    void InterruptAnimation(uint32_t anim, int a, int b);                      // 0x00c12310
    void MoveToPointAndFacingAtSpeed(int mode, const Vec3* pos, const Vec3* facing, float speed, float turn); // 0x00c1c5c0
    void MoveToPointAtSpeed(int mode, const Vec3* pos, float a, float b);      // 0x00c1c1d0
    int  SetToolEffectId(int id) { mToolEffectId_fc4 = id; return mToolEffectId_fc4; }  // 0x00c22830
};
}
namespace SP {
struct RepairState {                       // RepairBuilding_Tick trailing record (arg6)
    uint8_t  mbFlag_0;                     // +0x00
    uint8_t  pad1[0x03];
    int      mSlotA_4;                     // +0x04
    int      mSlotB_8;                     // +0x08
    Citizen* mpTarget_c;                   // +0x0c : target creature
};
}
namespace SP {
struct ArtifactState {                     // ArtifactMover_Tick trailing record (arg6)
    Object*  mpArtifact_0;                 // +0x00 : must match owner->mpArtifact_0a54
    int      mPhase_4;                     // +0x04
    Vec3     mRoute_8;                     // +0x08
};
}
// ---- items of slice s00d93fd0 end

// ---- items of slice s00d95c40 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float g169f20c;   // 0x0169f20c
extern float g169f210;   // 0x0169f210
extern float g169f214;   // 0x0169f214
extern float g1470f1c;   // 0x01470f1c  2.0f
extern float g13ec4b4;   // 0x013ec4b4  0.9f
extern float g147c0f4;   // 0x0147c0f4  FLT_MAX
extern float g1485720;   // 0x01485720  1.0f
#define nullptr 0
#define PVCAT2(a, b) a##b
#define PVCAT(a, b) PVCAT2(a, b)
#define PV_s00d9_5c40  virtual void PVCAT(pv_, __COUNTER__)();
#define PV2 PV_s00d9_5c40 PV_s00d9_5c40
#define PV4 PV2 PV2
#define PV8 PV4 PV4
#define PV16 PV8 PV8
struct cVector3 {
    float m_fX;
    float m_fY;
    float m_fZ;
};
struct cVector4 {
    float m_fX;
    float m_fY;
    float m_fZ;
    float m_fW;
};
class cGateCitizen;
class cCity;
class cCityVisualizer;
class cCityBuilding;
class cActionCircle;
class cActionSlot;
class cBuildingData;
class cBuildingState;
class cAnimatingCreature;
class cExtinguishMemory;
class IWinText;
struct cAllocationHeader {
    int32_t m_nCapacity;
};
class cBuffer {
public:
    ~cBuffer()
    {
        if (m_pData != nullptr) {
            cAllocationHeader* pHeader = (cAllocationHeader*)m_pData - 1;
            if (pHeader->m_nCapacity != 0)
                delete[] m_pData;
        }
    }
    uint8_t* m_pData;                                // +0x00
};
class cActionSlot {                                  // stride 0x18
public:
    void Reserve(cGateCitizen* pAgent);              // 0x00afa030
    bool m_bReserved;                                // +0x00
    uint8_t m_pad001[0x0b];                          // +0x01
    cVector3 m_vPosition;                            // +0x0c
};
class cActionCircle {                                // stride 0x64
public:
    cActionSlot* GetFreeSlot();                      // 0x00aff070
    void RemoveAgent(cGateCitizen* pAgent);           // 0x00afae50
    int32_t CountOccupiedSlots();                    // 0x00af9fa0
    cActionSlot* SlotAt(uint32_t nSlot);             // 0x00af9ff0
    uint8_t m_pad000[0x64];                          // +0x00
};
class cCityBuilding {
public:
    uint8_t m_pad000[0x30];                          // +0x000
    cActionCircle m_actionCircle;                    // +0x030
    uint8_t m_pad094[0x198 - 0x94];                  // +0x094
};
class cCityVisualizer {
public:
    int32_t FindBuildingIndex(cBuildingData* pData); // 0x00d58130
    uint8_t m_pad000[0x220];                         // +0x000
    cActionCircle* m_pCircleBegin;                   // +0x220
    cActionCircle* m_pCircleEnd;                     // +0x224
    uint8_t m_pad228[0x390 - 0x228];                 // +0x228
    cCityBuilding m_buildings[1];                    // +0x390
    uint8_t m_pad528[0xa10 - 0x528];                 // +0x528
    bool m_bSimulateInProgress;                      // +0xa10
};
class cPositionSource {
public:
    PV8 PV2 PV_s00d9_5c40                                       // +0x00 .. +0x28
    virtual cVector3* GetPosition();                 // +0x2c
};
class cBuildingState {
public:
    void FUN_00bd7c80();                             // 0x00bd7c80
    uint8_t m_pad000[0x100];                         // +0x000
    cPositionSource m_position;                      // +0x100
    uint8_t m_pad104[0x1d8 - 0x104];                 // +0x104
    int32_t m_nState;                                // +0x1d8
};
class cSpatial {
public:
    PV8 PV2 PV_s00d9_5c40                                       // +0x00 .. +0x28
    virtual void FindLaneNode(void* pfnIsDamaged);   // +0x2c
    PV2                                              // +0x30 .. +0x34
    virtual void SetPosition(const cVector3* pPosition);        // +0x38
    virtual void SetOrientation(const cVector4* pOrientation);  // +0x3c
    PV16 PV16 PV4 PV2 PV_s00d9_5c40                             // +0x40 .. +0xd8
    virtual void RequestMove(void* pRequest);        // +0xdc
};
class cAnimatingCreature {
public:
    void Detach(int32_t nMode);                      // 0x00a02b00
    uint8_t m_pad000[0x64];                          // +0x00
    bool m_bFlag64;                                  // +0x64
};
class cCity {
public:
    void* GetMembers();                              // 0x00c8e810 (cTribe::GetMembers)
    cBuildingState* GetBuildingState(int32_t nIndex); // 0x00bd8d60
};
class cGateCitizen {
public:
    int32_t GetBuildingIndex();                      // 0x00c227b0
    cCity* GetCity();                                // 0x00c23e40
    void FUN_00c0cff0(int32_t nMode);                // 0x00c0cff0
    void Hide();                                     // 0x00c0f280
    bool AnimationFinished(uint32_t nAnim);          // 0x00c123f0
    void InterruptAnimation(uint32_t nAnim, int32_t nBlend, int32_t nFlags);  // 0x00c12310
    void SetSprinting(bool bSprint);                 // 0x00c1ad10
    void MoveToPointAndFacingAtSpeed(uint32_t nMode, const cVector3* pPoint,
                                     const cVector3* pFacing, float fSpeed,
                                     float fTurn);   // 0x00c1c5c0
    uint8_t m_pad000[0xc0];                          // +0x000
    cSpatial m_spatial;                              // +0x0c0
    uint8_t m_pad0c4[0x135 - 0xc4];                  // +0x0c4
    bool m_bGateActive;                              // +0x135
    uint8_t m_pad136[0xb54 - 0x136];                 // +0x136
    cAnimatingCreature* m_pAnimatingCreature;        // +0xb54
    uint8_t m_padB58[0xf90 - 0xb58];                 // +0xb58
    bool m_bFlagF90;                                 // +0xf90
    uint8_t m_padF91[0xfb8 - 0xf91];                 // +0xf91
    cCityVisualizer* m_pVisualizer;                  // +0xfb8
    bool m_bFlagFBC;                                 // +0xfbc
    uint8_t m_padFBD[0x1010 - 0xfbd];                // +0xfbd
    cCity* m_pCity;                                  // +0x1010
};
class IWinText {
public:
    virtual void V00();                              // +0x00
    virtual void Release();                          // +0x04
    virtual void V08();                              // +0x08
    virtual void Detach(int32_t nMode);              // +0x0c
};
class cWinTextRef {
public:
    void Assign(void* pText);                        // 0x00b5f950
    void Reset()
    {
        if (m_pText != nullptr) {
            m_pText->Detach(0);
            IWinText* pOld = m_pText;
            m_pText = nullptr;
            if (pOld != nullptr)
                pOld->Release();
        }
    }
    IWinText* m_pText;                               // +0x00
};
class cExtinguishMemory {
public:
    ~cExtinguishMemory();                            // 0x00d95020
    uint32_t m_n000;                                 // +0x00
    int32_t m_nBuildingIndex;                        // +0x04
    int32_t m_nSlotIndex;                            // +0x08
    cWinTextRef m_ref00C;                            // +0x0c
    cWinTextRef m_ref010;                            // +0x10
    cWinTextRef m_ref014;                            // +0x14
    cWinTextRef m_ref018;                            // +0x18
    uint8_t m_pad01C[0x28 - 0x1c];                   // +0x1c
    uint32_t m_n028;                                 // +0x28
    uint32_t m_n02C;                                 // +0x2c
    uint32_t m_n030;                                 // +0x30
    uint8_t m_pad034[0x3c - 0x34];                   // +0x34
    uint32_t m_n03C;                                 // +0x3c
    uint32_t m_n040;                                 // +0x40
    uint32_t m_n044;                                 // +0x44
    uint8_t m_pad048[0x50 - 0x48];                   // +0x48
    float m_f050;                                    // +0x50
};
struct cMoveRequest {
    cBuffer m_buffer;                                // +0x00
    uint32_t m_n004;                                 // +0x04
    uint32_t m_n008;                                 // +0x08
    uint8_t m_pad00C[4];                             // +0x0c
    float m_f010;                                    // +0x10
    uint32_t m_n014;                                 // +0x14
    float m_f018;                                    // +0x18
    float m_f01C;                                    // +0x1c
    float m_f020;                                    // +0x20
    uint32_t m_n024;                                 // +0x24
    uint8_t m_pad028[0x24];                          // +0x28
    bool m_b04C;                                     // +0x4c
    uint8_t m_pad04D[3];                             // +0x4d
    float m_f050;                                    // +0x50
    float m_f054;                                    // +0x54
    float m_f058;                                    // +0x58
    uint32_t m_n05C;                                 // +0x5c
    float m_f060;                                    // +0x60
    float m_f064;                                    // +0x64
    float m_f068;                                    // +0x68
    float m_f06C;                                    // +0x6c
    uint32_t m_n070;                                 // +0x70
};
// ---- items of slice s00d95c40 end

// ---- items of slice s00d964a0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Matrix3 {
    float m[9];
    Matrix3() {}
    Matrix3(const Matrix3& o);          // 0x0041cb40 (out of line copy)
};
struct Transform {                       // 0x38 bytes: flags, count, offset, scale, rotation
    uint16_t mnFlags;
    uint16_t mnCount;
    Vec3     mOffset;
    float    mfScale;
    Matrix3  mRotation;
    struct InlineInit {};
    Transform(InlineInit);
    void SetOffset(const Vec3& v) { mOffset = v; mnFlags |= 4; ++mnCount; }
};
extern Vec3 sZeroVector;                 // 0x0169f28c
extern Matrix3 sIdentityMatrix;          // 0x0169f268
__forceinline Transform::Transform(InlineInit) : mnFlags(0), mnCount(0), mOffset(sZeroVector), mfScale(1.0f), mRotation(sIdentityMatrix) {}
struct Quat { float x, y, z, w; };
struct PlanetModel_s00d9_64a0 {
    Quat* BuildSurfaceOrientation(Quat* out, const Vec3* pos, const Vec3* dir);      // 0x00b7f250 (stdcall)
    Vec3* MakeRandomWorldPosition(Vec3* out, const Vec3* center, float minDist, float maxDist);   // 0x00b81780 (stdcall)
};
PlanetModel_s00d9_64a0* GetPlanetModel_s00d9_64a0();           // 0x00b3d350
struct EffectHandle {
    PV(0)
    virtual void Release();              // +4
    virtual void Start(int);             // +8
    virtual void Stop(int);              // +0xc
    PV(4) PV(5)
    virtual void SetTransform(const Transform* t);       // +0x18
    PV(7) PV(8) PV(9) PV(10) PV(11) PV(12) PV(13) PV(14) PV(15)
    virtual void SetPoints(int id, const Vec3* pts, int count);   // +0x40
};
struct EffectsManager {
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
    virtual void PlayEffect(uint32_t id, int flags, EffectHandle** out);   // +0x2c
};
EffectsManager* GetEffectsManager();     // 0x0067ddd0
struct Spatial_s00d9_64a0 {                         // object returned by target->GetSpatial()
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
    virtual const Vec3* GetPosition();                 // +0x2c
    PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19) PV(20) PV(21) PV(22) PV(23) PV(24) PV(25)
    PV(26)
    virtual const float* GetBoundingBox(void* buf);    // +0x6c
};
struct Target {                          // reference counted game object
    PV(0) PV(1)
    virtual Spatial_s00d9_64a0* GetSpatial();                     // +8
    PV(3) PV(4) PV(5)
    virtual void ApplyImpulse(float mag, void* source, int kind, const Vec3* dir, const void* extra);   // +0x18
    PV(7) PV(8) PV(9) PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19) PV(20)
    PV(21)
    virtual float GetScale();                          // +0x58
    PV(23)
    virtual void AddRef();                             // +0x60
    virtual void Release();                            // +0x64
};
struct Path { const Vec3* Back(); };     // 0x00c423c0 (last waypoint position)
struct Waypoint {                        // 0x3c bytes
    Vec3     pos;                         // +0
    float    speed;                       // +0xc
    int      i10;                         // +0x10
    float    rest[9];                     // +0x14 .. +0x38 (left uninitialised by the creator)
    uint8_t  flag;                        // +0x38
    Waypoint(float x, float y, float z) { pos.x = x; pos.y = y; pos.z = z; speed = 1.0f; i10 = 0; flag = 0; }
    Waypoint(const Waypoint& o);          // 0x00ac1ff0
};
void EaFree(void*);                       // 0x00f47380 operator delete[]
inline void* operator new(unsigned int, void* p) { return p; }
struct WaypointVector {                   // sp_vector<Waypoint>
    Waypoint* mpBegin;
    Waypoint* mpEnd;
    Waypoint* mpCapacity;
    WaypointVector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~WaypointVector() { if (mpBegin && ((int*)mpBegin)[-1] != 0) EaFree(mpBegin); }
    void DoInsertValue(Waypoint* pos, const Waypoint& v);     // 0x00ac45e0
    void push_back(const Waypoint& v)
    {
        if (mpEnd < mpCapacity)
            ::new((void*)mpEnd++) Waypoint(v);
        else
            DoInsertValue(mpEnd, v);
    }
};
struct PathRequest {                      // 0x74 bytes; first word is the waypoint array
    Waypoint* mpBegin;
    uint32_t  rest[28];
    PathRequest(const WaypointVector& v);   // 0x00c1bad0
    ~PathRequest() { if (mpBegin && ((int*)mpBegin)[-1] != 0) EaFree(mpBegin); }
};
struct Locomotion_s00d9_64a0 {                      // sub-object at creature + 0xc0
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
    virtual const Vec3* GetPosition();                 // +0x2c
    PV(12) PV(13)
    virtual void SetPosition(const Vec3* p);           // +0x38
    virtual void SetOrientation(const Quat* q);        // +0x3c
    PV(16) PV(17) PV(18) PV(19) PV(20) PV(21) PV(22)
    virtual const Vec3* GetForward(Vec3* tmp);         // +0x5c
    PV(24) PV(25) PV(26)
    virtual const float* GetBoundingBox(void* buf);    // +0x6c
    PV(28) PV(29) PV(30) PV(31) PV(32) PV(33) PV(34) PV(35) PV(36) PV(37) PV(38) PV(39) PV(40) PV(41)
    PV(42) PV(43) PV(44) PV(45) PV(46) PV(47) PV(48) PV(49) PV(50) PV(51) PV(52) PV(53) PV(54)
    virtual void SetPath(const PathRequest& p);        // +0xdc
    PV(56) PV(57) PV(58)
    virtual void StopMoving();                         // +0xec
    Path* GetPath();                                   // 0x00c41ec0 (returns this + 0x1f4)
};
struct Owner_s00d9_64a0 {
    uint32_t pad[0xa28 / 4];
    int      mCounter;                // +0xa28
    uint32_t pad2[(0xa58 - 0xa2c) / 4];
    Target*  mpTarget;                // +0xa58
};
struct Creature_s00d9_64a0 {
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12) PV(13)
    PV(14) PV(15) PV(16) PV(17) PV(18)
    virtual void* GetSource();                         // +0x4c
    uint32_t pad04[(0xc0 - 4) / 4];
    Locomotion_s00d9_64a0 mLoco;                 // +0xc0 : sub-object with its own vptr (size not modelled)
    uint32_t padLoco[(0x330 - 0xc4) / 4];
    uint32_t mField330;               // +0x330
    uint32_t pad334[(0x5a8 - 0x334) / 4];
    uint32_t mField5a8;               // +0x5a8
    uint32_t pad5ac[(0xfb8 - 0x5ac) / 4];
    Owner_s00d9_64a0*   mpOwner;                 // +0xfb8
    uint32_t pad_fbc;
    int      mFieldFC0;               // +0xfc0
    void MoveToPointAndFacingAtSpeed(int mode, const Vec3* pos, const Vec3* facing, float speed, float turn);   // 0x00c1c5c0 (ret 0x14)
    void SetMoveState(int state);     // 0x00c0cff0
    void Method_c0d0c0(int a, int b); // 0x00c0d0c0
};
struct City_s00d9_64a0;
struct CitizenCreature : Creature_s00d9_64a0 {
    City_s00d9_64a0* GetCity();                  // 0x00c23e40 (returns [this + 0x1010])
};
namespace EA {
namespace Random {
class RandomLinearCongruential_s00d9_64a0 { public:
    uint32_t RandomUint32Uniform(uint32_t limit);   // 0x00a68fb0
    double   RandomDoubleUniform();                 // 0x009360d0
};
}
}
extern EA::Random::RandomLinearCongruential_s00d9_64a0 sMathRandom_s00d9_64a0;   // 0x01601760
struct RouteSegment {                     // 0x50 bytes, element of the city's route list
    uint32_t pad00[2];
    float    probsA[3];               // +0x08: activity probabilities when walked U -> V
    float    probsB[3];               // +0x14: when walked V -> U
    Vec3     pointU;                  // +0x20
    Vec3     pointV;                  // +0x2c
    Vec3     dirU;                    // +0x38
    Vec3     dirV;                    // +0x44
};
struct RouteList { RouteSegment* mpBegin; RouteSegment* mpEnd; };
struct City_s00d9_64a0 { RouteList* GetRoutes(); };      // 0x00bd8230 (returns this + 0x684)
namespace SP {
namespace CitizenTree {
struct PolicemanState {
    Target*       mpTarget;           // +0
    EffectHandle* mpEffect;           // +4
};
}
}
namespace SP {
namespace CitizenTree {
struct RouteChoice {                      // output of SimFeedback_Activate
    Vec3 start;                           // +0
    Vec3 end;                             // +0xc
    int  mode;                            // +0x18
};
}
}
// ---- items of slice s00d964a0 end

// ---- items of slice s00d97420 begin (TODO(rewrite): local stubs, replace by canonical classes)
#pragma warning(disable : 4100)
class cSPCreatureCitizen_s00d9_7420;
class cActionCircle_s00d9_7420 {
public:
    void RemoveAgent(cSPCreatureCitizen_s00d9_7420* pAgent);        // 0x00afae50

    uint8_t mPayload[100];                               // +0x000 .. +0x063
};
struct tCitizenVector {
    void* mpBegin;                                       // +0x00
    void* mpEnd;                                         // +0x04
    void* mpCapacity;                                    // +0x08
    void* mpAllocatorPool;                               // +0x0c
    void* mpAllocatorOwner;                              // +0x10
};
class cCultureRecord {
public:
    uint8_t         pad000[0x94];                        // +0x000 .. +0x093
    cActionCircle_s00d9_7420   mCircles[2];                         // +0x094 .. +0x15b
    tCitizenVector  mStageGroups[1];                     // +0x15c .. +0x16f
    uint8_t         pad170[0x198 - 0x170];               // +0x170 .. +0x197
};
class cCultureRecordPage {
public:
    uint8_t         pad000[0x390];                       // +0x000 .. +0x38f
    cCultureRecord  mRecords[1];                         // +0x390
};
struct tCultureAttackInfo {
    uint32_t mField0;                                    // +0x00
    int32_t  mRecordIndex;                               // +0x04
    int32_t  mStage;                                     // +0x08
};
class cSPCreatureCitizen_s00d9_7420 {
public:
    uint8_t             pad000[0xfb8];                   // +0x000 .. +0x0fb7
    cCultureRecordPage* mpRecordPage;                    // +0xfb8
};
namespace spstl {
void __cdecl remove_1st(tCitizenVector* pVector, cSPCreatureCitizen_s00d9_7420** ppCitizen); // 0x00acca00
}
void __cdecl CultureAttack_Deactivate(cSPCreatureCitizen_s00d9_7420* pCitizen, int32_t a2, int32_t a3, int32_t a4, int32_t a5, tCultureAttackInfo* pInfo);  // 0x00d980e0 (defined below; used by a stub's inline body)
namespace SP {
class CitizenTree_s00d9_7420 {
public:
    void FUN_00d97420();
    void EnterCity_Activate();  // 0x00d97720 (SP::CitizenTree::EnterCity_Activate)
    void CultureAttack_Activate();  // 0x00d979b0 (SP::CitizenTree::CultureAttack_Activate)
    void CultureAttack_Tick();  // 0x00d97d80 (SP::CitizenTree::CultureAttack_Tick)
    void CultureAttack_Deactivate();  // 0x00d980e0 (SP::CitizenTree::CultureAttack_Deactivate)

    uint8_t           pad000[0x94];                      // +0x000 .. +0x093
    cActionCircle_s00d9_7420     mCircles[2];                       // +0x094 .. +0x15b
    tCitizenVector    mStageGroups[1];                   // +0x15c
};  // namespace SP
}
// ---- items of slice s00d97420 end

// @ 0x00d90ce0
namespace SP {
bool FUN_00d90ce0(cSPCreatureCitizen_s00d9_0640* p)
{
    if (p->mLoco.IsNearGoal()) {
        int anim = p->mpFB8->mn1A8 + 0x2481dda;
        if (p->GetAnimGuid() != anim)
            p->InterruptAnimation(anim, -1, 0);
    }
    return true;
}
}  // namespace SP

// @ 0x00d90d30
namespace SP {
float FUN_00d90d30(cSPCreatureCitizen_s00d9_0640* p)
{
    Vec3* v = p->mLoco.GetPosition();
    if (p->mpFB8->mPos.CheckPosition(v) == 0)
        return 0.0f;
    return 1.0f;
}
}  // namespace SP

// @ 0x00d90d70
namespace SP {
bool FUN_00d90d70(cSPCreatureCitizen_s00d9_0640* p, void* a2, void* a3, uint8_t flags, void* a5, int* pState)
{
    if ((flags & 0x10) == 0)
        return false;
    switch (*pState) {
    case 0:
        if (!p->mLoco.IsNearGoal())
            return true;
        *pState = 1;
        goto play;
    case 1:
        if (!p->AnimationFinished(0))
            return true;
        goto play;
    default:
        return true;
    }
play:
    p->PlayAnimation(0x2481de3, 1, -1);
    return true;
}
}  // namespace SP

// @ 0x00d90dd0
namespace SP {
bool UfoWaving_Tick(cSPCreatureCitizen_s00d9_0640* p)
{
    int r = p->mpB4C->mStimuli.Play(0x100, 0);
    if (r == 0)
        return false;
    if (p->mLoco.IsNearGoal()) {
        if (p->GetAnimGuid() != 0x2481dc7)
            p->InterruptAnimation(0x2481dc7, -1, 0);
    }
    return true;
}
}  // namespace SP

// @ 0x00d90e30
namespace SP {
bool FUN_00d90e30(cSPCreatureCitizen_s00d9_0640* p, void* a2, void* a3, void* a4, void* a5, int* pState)
{
    switch (*pState) {
    case 0:
        if (p->mLoco.IsNearGoal()) {
            p->InterruptAnimation(p->mpFB8->mn1AC, -1, 0);
            *pState = 1;
        }
        break;
    case 1:
        if (p->AnimationFinished(0))
            return false;
        break;
    default:
        break;
    }
    return true;
}
}  // namespace SP

// @ 0x00d90e90
namespace SP {
void RunFromDanger_Deactivate(cSPCreatureCitizen_s00d9_0640* p)
{
    p->SetSprinting(0);
    if (GetCurrentGameMode() == (void*)0x01654c05) {
        p->SetMode9c(0);
        int r = p->mpB4C->mStimuli.Play(4, 0);
        if (r == 0) {
            if (p->GetCity() != 0)
                p->GetCity()->mn2D0 -= 1;
        }
    }
}
}  // namespace SP

// @ 0x00d90ef0
namespace SP {
void WildPanic_Deactivate(cSPCreatureCitizen_s00d9_0640* p)
{
    p->InterruptAnimation(0x2481db0, -1, 0);
}
}  // namespace SP

// @ 0x00d90f10
namespace SP {
void CropCirclesAttract_Deactivate(cSPCreatureCitizen_s00d9_0640* p)
{
    if (p->GetMode98() == 5) {
        p->SetMode9c(0);
        int v = p->GetCity()->FUN_00bd8190() - 1;
        p->GetCity()->FUN_00bd8170(v);
    }
}
}  // namespace SP

// @ 0x00d90f60
namespace SP {
void FUN_00d90f60(cSPCreatureCitizen_s00d9_0640* p)
{
    p->SetCurrentToolEffect(0, -1);
    p->mpFB8->mnA38 -= 1;
    p->mpFB8->mCircle070.RemoveAgent(p);
}
}  // namespace SP

// @ 0x00d90f90
namespace SP {
bool FUN_00d90f90(cSPCreatureCitizen_s00d9_0640* p, void* a2, uint8_t flags, void* a4, void* a5, int* pOut)
{
    if (pOut != 0)
        *pOut = 0;
    p->GetCity();
    cBehaviorAgent* ag = p->mpFB8;
    uint32_t u = p->FUN_00c227b0();
    if (u > 3)
        return false;
    *ag->GetCounter(u) += 1;
    *pOut = 2 - (int)(flags & 1);
    return true;
}
}  // namespace SP

// @ 0x00d90ff0
namespace SP {
void FUN_00d90ff0(cSPCreatureCitizen_s00d9_0640* p)
{
    cBehaviorAgent* ag = p->mpFB8;
    uint32_t u = p->FUN_00c227b0();
    if (u > 3)
        return;
    int* pi = ag->GetCounter(u);
    if (*pi > 0)
        *pi -= 1;
}
}  // namespace SP

// @ 0x00d91020
namespace SP {
bool FUN_00d91020(cSPCreatureCitizen_s00d9_0640* p, void* a2, void* a3, void* a4, void* a5, TickState* pState, void* a7, float dt)
{
    p->GetCity();
    switch (pState->mMode) {
    case 0:
        if (p->mLoco.IsNearGoal()) {
            pState->mMode = 1;
            pState->mf4 = 0.0f;
        }
        break;
    case 1: {
        float f = pState->mf4 + dt;
        pState->mf4 = f;
        if (5.0f < f)
            return false;
        break;
    }
    default:
        break;
    }
    return true;
}
}  // namespace SP

// @ 0x00d91080
namespace SP {
char FUN_00d91080(cSPCreatureCitizen_s00d9_0640* p)
{
    return p->mbFBC == '\0';
}
}  // namespace SP

// @ 0x00d91090
namespace SP {
void OffStage_Deactivate(cSPCreatureCitizen_s00d9_0640* p)
{
    p->mCombatant.mb15 = 1;
    p->mbF90 = 1;
    p->Show();
    p->mbFBC = 1;
    p->InterruptAnimation(0x2481db0, -1, 0);
}
}  // namespace SP

// @ 0x00d910d0
namespace SP {
bool IsFunctional(cSPCreatureCitizen_s00d9_0640* p)
{
    return p->mCombatant.GetDamageState() != 2;
}
}  // namespace SP

// @ 0x00d910f0
namespace SP {
void FUN_00d910f0(cSPCreatureCitizen_s00d9_0640* p, void* a2, void* a3, uint32_t flags)
{
    if ((flags & 0x40000) != 0)
        p->FlagC8(0);
}
}  // namespace SP

// @ 0x00d91110
namespace SP {
float FUN_00d91110(cSPCreatureCitizen_s00d9_0640* p)
{
    int id = p->mnFF0;
    if (id == p->GetIdentity())
        return 1.0f;
    return 0.0f;
}
}  // namespace SP

// @ 0x00d91130
namespace SP {
char FUN_00d91130(cSPCreatureCitizen_s00d9_0640* p)
{
    return !p->AnimationFinished(0);
}
}  // namespace SP

// @ 0x00d91150
namespace SP {
bool AdmireObject_Tick(cSPCreatureCitizen_s00d9_0640* p, void* a2, void* a3, void* a4, void* a5, AdmireState* pState)
{
    if (p->mLoco.IsNearGoal()) {
        if (pState->mFlag != 0) {
            pState->mFlag = 0;
            p->PlayAnimation(0x2d5f9c5, 1, -1);
            return true;
        }
        if (p->AnimationFinished(0)) {
            pState->mCount += 1;
            if (pState->mCount > 3)
                return false;
            p->PlayAnimation(0x2d5f9c5, 1, -1);
        }
    }
    return true;
}
}  // namespace SP

// @ 0x00d911c0
namespace SP {
void AdmireObject_Deactivate(cSPCreatureCitizen_s00d9_0640* p)
{
    p->mpFB8->mCircle1BC.RemoveAgent(p);
    p->SetSprinting(0);
}
}  // namespace SP

// @ 0x00d911f0
namespace SP {
void ActInVignette_Activate(cSPCreatureCitizen_s00d9_0640* p)
{
    p->SetSprinting(0);
    p->InterruptAnimation(0x2481db0, -1, 0);
}
}  // namespace SP

// @ 0x00d91250
namespace SP {
void ActInVignette_Deactivate(cSPCreatureCitizen_s00d9_0640* p)
{
    p->mpB4C->mStimuli.ClearAll(0x800, 0);
    p->mpFB8->ExitZone(p);
}
}  // namespace SP

// @ 0x00d91280
namespace SP {
bool ReactToRubble_Tick(cSPCreatureCitizen_s00d9_0640* p, void* a2, void* a3, void* a4, void* a5, RubbleState* pState)
{
    if (p->mpFB8->mnA44 != pState->mId)
        return false;
    if (p->mLoco.IsNearGoal()) {
        if (pState->mFlag != 0) {
            pState->mFlag = 0;
            int a = (int)sMathRandom.RandomUint32Uniform(3) + 0x51de063;
            p->InterruptAnimation(a, -1, 0);
            for (int i = 2; i != 0; --i) {
                int b = (int)sMathRandom.RandomUint32Uniform(3) + 0x51de063;
                pState->mAnim = p->PlayAnimation(b, 0, -1);
            }
            return true;
        }
        if (p->AnimationFinished(pState->mAnim))
            return false;
    }
    return true;
}
}  // namespace SP

// @ 0x00d91320
namespace SP {
int IsDamaged(cCombatant_s00d9_0640* c)
{
    if (c->GetDamageState() != 2) {
        float h = c->mfHealth38;
        if (h != c->GetMaxHealth())
            return 1;
    }
    return 0;
}
}  // namespace SP

// @ 0x00d91360
namespace SP {
int FUN_00d91360(cCombatant_s00d9_0640* c)
{
    float h = c->mfHealth38;
    if (h / c->GetMaxHealth() < 0.5f)
        return 1;
    return 0;
}
}  // namespace SP

// @ 0x00d91390
namespace SP {
bool FUN_00d91390(cSPCreatureCitizen_s00d9_0640* p)
{
    p->InterruptAnimation((int)sMathRandom.RandomUint32Uniform(3) + 0x2481dd4, -1, 0);
    p->mpB4C->mStimuli.ClearAll(0x1000, 0);
    return true;
}
}  // namespace SP

// @ 0x00d913d0
namespace SP {
bool FUN_00d913d0(cSPCreatureCitizen_s00d9_0640* p)
{
    return p->FUN_00c0e370() <= 1;
}
}  // namespace SP

// @ 0x00d91480
namespace SP {
bool AlienGreeting_Activate(cSPCreatureCitizen_s00d9_0640* p)
{
    p->mpB4C->mStimuli.ClearAll(0x1000, 0);
    if (p->mpFB8->mbA50 != 0)
        return false;
    switch (p->GetCity()->GetVehicleSpecialty()) {
    case 0:
        ((cCityVisualizer_s00d9_0640*)p->mpFB8)->StartSpecialVignette((void*)0xc3e4872d, p);
        return true;
    case 1:
        ((cCityVisualizer_s00d9_0640*)p->mpFB8)->StartSpecialVignette((void*)0xd013f836, p);
        return true;
    default:
        ((cCityVisualizer_s00d9_0640*)p->mpFB8)->StartSpecialVignette((void*)0xa9f7e664, p);
        return true;
    }
}
}  // namespace SP

// @ 0x00d91510
namespace SP {
unsigned char FUN_00d91510(cSPCreatureCitizen_s00d9_0640* p)
{
    uint32_t u = p->mpB4C->mn1C8 & 0x800;
    if (u != 0)
        return (unsigned char)u;
    return 1;
}
}  // namespace SP

// @ 0x00d91540
bool FUN_00d91540(void* self)
{
    Creature* c = (Creature*)self;
    C0Sub* s = &c->mC0;
    ((FnV)((void**)s->mpVtbl)[0xec / 4])(s);
    ((C14750*)c)->Do(0);
    return true;
}

// @ 0x00d91570
bool FUN_00d91570(void* self, u32 a1, u32 a2, u32 a3, u32 a4, u32* out)
{
    Creature* c = (Creature*)self;
    C0Sub* s = &c->mC0;
    Vec3f local;
    ((FnV)((void**)s->mpVtbl)[0xec / 4])(s);
    ((C14750*)c)->Do(0);
    u32 id = ((BC64A0*)FUN_00b3d4e0())
                 ->Do(0x499c0285, 0xa080e6cd,
                      (u32)((FnP)((void**)s->mpVtbl)[0x2c / 4])(s),
                      ((FnU1P)((void**)s->mpVtbl)[0x5c / 4])(s, &local));
    *out = id;
    if (id != 0xffffffff) {
        ((BC4900*)FUN_00b3d4e0())->Do(id, (u32)c, 0);
        return true;
    }
    return false;
}

// @ 0x00d91600
bool FUN_00d91600(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32* p)
{
    u8 r = ((BC3DF0*)FUN_00b3d4e0())->Do(*p);
    return r == 0;
}

// @ 0x00d91620
void FUN_00d91620(u32 p1, u32 a1, u32 a2, u32 a3, u32 a4, u32* p)
{
    ((BC52A0*)FUN_00b3d4e0())->Do(*p, p1);
    ((BC5040*)FUN_00b3d4e0())->Do(*p);
}

// @ 0x00d91650
bool FUN_00d91650(void* p0, u32 a1, u32 a2, u32 a3, u32 a4, AnimState* st)
{
    Creature* c = (Creature*)p0;
    if (st->mb0C != 0) {
        if (((NearGoal*)&c->mC0)->Do()) {
            st->mb0C = 0;
            st->mn14 = ((PlayAnim*)c)->Do(((u32*)0x147c0fc)[st->mn10], 1, 0xffffffff);
        }
        return true;
    }
    return ((C0E370*)c)->Do() < 1;
}

// @ 0x00d916b0
bool FUN_00d916b0(void* p0, u32 a1, u32 a2, u32 flags, u32 a4, u8* flag)
{
    Creature* c = (Creature*)p0;
    if ((flags & 0x6000000) == 0)
        return false;
    if (((NearGoal*)&c->mC0)->Do() && *flag == 0) {
        *flag = 1;
        double r = ((RandDbl*)0x1601760)->Do();
        if ((flags | 0x2000000) != 0) {
            (r < *(f32*)0x1471064)
                ? ((PlayAnim*)c)->Do(0x62d64e3, 1, 0xffffffff)
                : ((PlayAnim2*)c)->Do(0x62d64e4, 1, 0xffffffff);
            return true;
        }
        u32 anim = (r < *(f32*)0x1471064) ? 0x2481dcb : 0x2481dcc;
        ((PlayAnim*)c)->Do(anim, 1, 0xffffffff);
    }
    return true;
}

// @ 0x00d91750
f32 FUN_00d91750(void* p0)
{
    Creature* c = (Creature*)p0;
    if (c->mbB62)
        return 1.0f;
    return 0.0f;
}

// @ 0x00d91770
bool FUN_00d91770(void* p0, u32 a1, u32 a2, u32 a3, u32 a4, UfoState* st, u32 a6, f32 dt)
{
    Creature* c = (Creature*)p0;
    if (((NearGoal*)&c->mC0)->Do()) {
        if (st->mb00 == 0) {
            u32 idx = ((RandU32*)0x1601760)->Do(5);
            ((Interrupt*)c)->Do(((u32*)0x147c108)[idx], 0xffffffff, 0);
            st->mb00 = 1;
        }
        st->mf04 += dt;
        if (st->mf04 > 3.0f)
            return false;
    }
    return true;
}

// @ 0x00d917e0
u32 FUN_00d917e0(u32 a0, u32 a1, u32 a2, u32 flags)
{
    return (flags >> 27) & 1;
}

// @ 0x00d917f0
f32* FUN_00d917f0(f32* out, void* citizen)
{
    Creature* c = (Creature*)citizen;
    Vec3f* src = (Vec3f*)((FnP)((void**)c->mC0.mpVtbl)[0x2c / 4])(&c->mC0);
    Vec3f pos;
    pos.x = src->x;
    pos.y = src->y;
    pos.z = src->z;
    out[0] = pos.x;
    out[1] = pos.y;
    out[2] = pos.z;

    f32 best = *(f32*)0x147c0f4;
    LaneInfo* info = (LaneInfo*)((GetLane*)((GetCity*)c)->Do())->Do();
    LaneNode* b = info->mpBegin;
    s32 n = (s32)(info->mpEnd - info->mpBegin);
    s32 i = 0;

    for (; i < n; ++i) {
        LaneNode* p = b + i;
        f32 dx = pos.x - p->v.x;
        f32 dy = pos.y - p->v.y;
        f32 dz = pos.z - p->v.z;
        f32 d = (dx * dx + dz * dz) + dy * dy;
        if (d < best) {
            *(Vec3f*)out = p->v;
            best = d;
        }
    }
    return out;
}

// @ 0x00d91a40
bool FUN_00d91a40(void* p0, u32 a1, u32 a2, u32 a3, u32 a4, DeadState* st, u32 a6, f32 dt)
{
    Creature* c = (Creature*)p0;
    u32 state = st->mn00;
    st->mf04 += dt;

    if (state == 0) {
        st->mn08 += 1;
        if (st->mn08 >= 2)
            st->mn00 = 1;
        return true;
    }
    if (state == 1) {
        if (c->mn2B0 == 3 && (c->mn110 & 0x1000) == 0)
            return true;
        st->mn00 = 2;
        u32 anim = c->mbB5E ? 0x2481db4 : 0x3cc7f35;
        ((Interrupt*)c)->Do(anim, 0xffffffff, 0);
        ((FnV)((void**)c->mpVtbl)[0x54 / 4])(c);
        return true;
    }
    if (state != 2)
        return true;

    if (st->mb10 != 0) {
        f32 t = st->mf14 - dt;
        st->mf14 = t;
        if (t > 0.0f) {
            if (c->mpB54 != 0) {
                B54Obj* o = (B54Obj*)c->mpB54;
                double r = pow(0.1, (double)dt);
                o->mf80 = (f32)((1.0 - r) * (double)*(f32*)0x13eb960
                                + (double)o->mf80 * r);
                return true;
            }
        } else {
            ((Fn1)((void**)c->mpVtbl)[0xc8 / 4])(c, 0);
            return true;
        }
    }

    if (c->mbB5E != 0) {
        if (st->mb18 == 0 || !((C0E0C0*)c)->Do(0x2481db4)) {
            st->mb18 = 1;
            ((PlayAnim*)c)->Do(0x2481db4, 1, 0xffffffff);
        }
        st->mf0C -= dt;
        if (st->mf0C > 0.0f)
            return true;
        if (((FnP)((void**)c->mC0.mpVtbl)[0x48 / 4])(&c->mC0)) {
            st->mb10 = 1;
            st->mf14 = 1.5f;
            return true;
        }
        ((Fn1)((void**)c->mpVtbl)[0xc8 / 4])(c, 0);
        return true;
    }

    f32 v = c->mf5E0 - dt * 5.0f;
    if (v < 0.0f)
        v = 0.0f;
    c->mSub5A8.Set(v);
    FUN_00d90ac0(c, st);
    return true;
}

// @ 0x00d91fb0
bool FUN_00d91fb0(void* p0, u32 a1, u32 a2, u32 a3, u32 a4, u32* out)
{
    Creature* c = (Creature*)p0;
    if (out != 0)
        *out = 0xffffffff;

    FB8Obj* p = (FB8Obj*)c->mpFB8;
    f32 best = *(f32*)0x147c0f4;
    u32 idx = 0xffffffff;

    for (u32 i = 0; i < (u32)(p->mpEnd - p->mpBegin); ++i) {
        Vec3f* node = p->mpBegin + i;
        Vec3f* pos = (Vec3f*)((FnP)((void**)c->mC0.mpVtbl)[0x2c / 4])(&c->mC0);
        f32 dx = pos->x - node->x;
        f32 dz = pos->z - node->z;
        f32 dy = pos->y - node->y;
        f32 d = dx * dx + dz * dz + dy * dy;
        if (d < best) {
            best = d;
            idx = i;
        }
    }

    if (idx != 0xffffffff) {
        ((Interrupt*)c)->Do(0x2481db0, 0xffffffff, 0);
        ((MoveTo*)c)->Do(3, p->mpBegin + idx, 1.0f, 6.0f);
        *out = idx;
        return true;
    }
    return false;
}

// @ 0x00d921c0
bool FUN_00d921c0(void* p0, u32 a1, u32 a2, u32 flags, u32 a4, u32* out)
{
    Creature* c = (Creature*)p0;
    if (out != 0)
        out[0] = 0;
    out[1] = flags & 2;

    Vec3f pos;
    FUN_00d917f0((f32*)&pos, c);

    Vec3f* cur = (Vec3f*)((FnP)((void**)c->mC0.mpVtbl)[0x2c / 4])(&c->mC0);
    Vec3f tmp;
    if (pos.x == cur->x && pos.y == cur->y && pos.z == cur->z) {
        Vec3f* r = ((PlanetModel*)SP_PlanetModel())->MakeRandomWorldPosition(
            &tmp, (Vec3f*)((FnP)((void**)c->mC0.mpVtbl)[0x2c / 4])(&c->mC0),
            *(f32*)0x1470f1c, *(f32*)0x14853e0);
        pos = *r;
    }

    Vec3f* r2 = ((PlanetModel*)SP_PlanetModel())->MakeRandomWorldPosition(
        &tmp, &pos, 0.0f, *(f32*)0x14007f4);
    pos = *r2;

    ((Interrupt*)c)->Do(0x2481db0, 0xffffffff, 0);
    ((MoveTo*)c)->Do(2, &pos, 1.0f, *(f32*)0x147b9f0);
    return true;
}

// @ 0x00d92560
bool FUN_00d92560(Creature_s00d9_22f0* c)
{
    const Vec3* tgt = c->mpOwner->FUN_00d579a0(c);
    Vec3 pos;
    pos.x = tgt->x;
    pos.y = tgt->y;
    pos.z = tgt->z;

    float dy = c->mpOwner->mV138.y - pos.y;
    float dz = c->mpOwner->mV138.z - pos.z;
    float dx = c->mpOwner->mV138.x - pos.x;
    float inv = 1.0f / sqrtf(dy * dy + dz * dz + dx * dx + 1e-8f);

    Vec3 dir;
    dir.x = inv * dx;
    dir.y = inv * dy;
    dir.z = inv * dz;

    c->InterruptAnimation(0x2481db1, -1, 0);
    c->MoveToPointAndFacingAtSpeed(3, &pos, &dir, 1.0f, 6.0f);
    return 1;
}

// @ 0x00d92660
bool FUN_00d92660(Creature_s00d9_22f0* c, int, int, int, int, int* ctx)
{
    ActionSlot* slot = c->mpOwner->mCircle.FindSlot(c->mLoco.GetPosition());
    slot->Reserve(c);

    float dx = c->mpOwner->mV0E8.x - slot->mPos.x;
    float dy = c->mpOwner->mV0E8.y - slot->mPos.y;
    float dz = c->mpOwner->mV0E8.z - slot->mPos.z;
    float inv = 1.0f / sqrtf(dx * dx + dy * dy + dz * dz + 1e-8f);

    Vec3 dir;
    dir.x = inv * dx;
    dir.y = inv * dy;
    dir.z = inv * dz;

    c->InterruptAnimation(0x2481db0, -1, 0);
    c->MoveToPointAndFacingAtSpeed(2, &slot->mPos, &dir, 1.0f, 2.0f);
    *ctx = 0;
    return 1;
}

// @ 0x00d92880
bool FUN_00d92880(Creature_s00d9_22f0* c, int, int, int, int, int* ctx)
{
    c->mAnim->mPlayer.ClearAll(1, 0);
    *ctx = 0;

    const Vec3* pos = c->mLoco.GetPosition();
    float dx = c->mpOwner->mV1B0.x - pos->x;
    float dy = c->mpOwner->mV1B0.y - pos->y;
    float dz = c->mpOwner->mV1B0.z - pos->z;
    float inv = 1.0f / sqrtf(dx * dx + dy * dy + dz * dz + 1e-8f);

    Vec3 dir;
    dir.x = inv * dx;
    dir.y = inv * dy;
    dir.z = inv * dz;

    c->InterruptAnimation(0x2481db0, -1, 0);
    c->MoveToPointAndFacingAtSpeed(2, c->mLoco.GetPosition(), &dir, 1.0f, 2.0f);
    return 1;
}

// @ 0x00d92990
void RunFromDanger_ChooseDestination(Creature_s00d9_22f0* c, Vec3* cached, Vec3* dest)
{
    AnimState_s00d9_22f0* s = c->mAnim->mPlayer.Play(4, 0);
    Vec3 animPos;
    animPos.x = s->mPoint.x;
    animPos.y = s->mPoint.y;
    animPos.z = s->mPoint.z;

    if (c->GetCity() == 0 || cached == 0 ||
        cached->x != animPos.x || cached->y != animPos.y || cached->z != animPos.z) {
        const Vec3* pos = c->mLoco.GetPosition();
        float dz = pos->z - animPos.z;
        float dy = pos->y - animPos.y;
        float dx = pos->x - animPos.x;
        float inv = 1.0f / sqrtf(dz * dz + dy * dy + dx * dx + 1e-8f);

        float vx = (dx * inv) * 6.0f;
        float vy = (dy * inv) * 6.0f;
        float vz = (dz * inv) * 6.0f;

        const Vec3* pos2 = c->mLoco.GetPosition();
        Vec3 cand;
        cand.x = pos2->x + vx;
        cand.y = pos2->y + vy;
        cand.z = pos2->z + vz;

        City* city = c->GetCity();
        if (city != 0) {
            const Vec3* center = city->mSub.GetPosition();
            float rx = cand.x - center->x;
            float ry = cand.y - center->y;
            float rz = cand.z - center->z;
            float dist = sqrtf(rz * rz + ry * ry + rx * rx);
            float avail = city->GetCollisionInfo()->mRadius - c->mLoco.GetScale();
            if (avail < dist) {
                float t = avail / dist;
                Vec3 step;
                step.x = rx * t;
                step.y = ry * t;
                step.z = rz * t;
                const Vec3* center2 = city->mSub.GetPosition();
                cand.x = center2->x + step.x;
                cand.y = center2->y + step.y;
                cand.z = center2->z + step.z;
            }
        }

        Vec3 surface;
        *dest = *GetPlanetModel()->DirectionToSurfacePosition(&surface, &cand);
        *cached = animPos;
    } else {
        LaneArray* lanes = c->GetCity()->GetLaneInfo();
        if (lanes->mpBegin != lanes->mpEnd) {
            uint32_t i = sMathRandom_s00d9_22f0.RandomUint32Uniform((uint32_t)(lanes->mpEnd - lanes->mpBegin));
            LanePoint* lp = &lanes->mpBegin[i];
            Vec3 lane;
            lane.x = lp->mPoint.x;
            lane.y = lp->mPoint.y;
            lane.z = lp->mPoint.z;
            *dest = lane;
            Vec3 out;
            GetPlanetModel()->MakeRandomWorldPosition(&out, dest, 2.0f, 4.0f);
        }
    }
}

// @ 0x00d92cc0
bool FUN_00d92cc0(Creature_s00d9_22f0* c, int, int, int, int, DangerState* st)
{
    Vec3 dest;
    RunFromDanger_ChooseDestination(c, &st->mCached, &dest);

    AnimState_s00d9_22f0* s = c->mAnim->mPlayer.Play(4, 0);
    st->mf0 = s->mf18;
    st->mf4 = s->mf18;
    st->mEmpire = s->mi1c;

    c->InterruptAnimation(0x2481dc8 + sMathRandom_s00d9_22f0.RandomUint32Uniform(3), -1, 0);
    c->MoveToPointAtSpeed(2, &dest, 1.0f, 2.0f);
    c->SetSprinting(1);

    if (GetCurrentGameMode() == (void*)0x1654c05) {
        c->SetState(4);
        if (st->mEmpire == GetPlayerEmpireID()) {
            if (c->GetCity() != 0) {
                c->GetCity()->mCounter2D0++;
            }
        }
    }
    return 1;
}

// @ 0x00d92f60
bool FUN_00d92f60(Creature_s00d9_22f0* c)
{
    c->mLoco.StopMoving();
    c->InterruptAnimation(0x2481dc8 + sMathRandom_s00d9_22f0.RandomUint32Uniform(3), -1, 0);
    return 1;
}

// @ 0x00d92fb0
bool WildPanic_Tick(Creature_s00d9_22f0* c, int, int, uint32_t flags)
{
    if ((flags & 0x400000) == 0) {
        return 0;
    }
    if (!c->mLoco.IsNearGoal()) {
        return 1;
    }
    if (c->GetCity() == 0) {
        return 1;
    }
    LaneArray* lanes = c->GetCity()->GetLaneInfo();
    if (lanes->mpBegin != lanes->mpEnd) {
        uint32_t i = sMathRandom_s00d9_22f0.RandomUint32Uniform((uint32_t)(lanes->mpEnd - lanes->mpBegin));
        LanePoint* lp = &lanes->mpBegin[i];
        Vec3 center;
        center.x = lp->mPoint.x;
        center.y = lp->mPoint.y;
        center.z = lp->mPoint.z;
        Vec3 out;
        GetPlanetModel()->MakeRandomWorldPosition(&out, &center, 2.0f, 4.0f);
        c->InterruptAnimation(0x2481dc8 + sMathRandom_s00d9_22f0.RandomUint32Uniform(3), -1, 0);
        c->MoveToPointAtSpeed(3, &center, 1.0f, 2.0f);
    }
    return 1;
}

// @ 0x00d930b0
bool FUN_00d930b0(Creature_s00d9_22f0* c, int, int, int, int, TimedPoint* out)
{
    AnimState_s00d9_22f0* s = c->mAnim->mPlayer.Play(0x200, 0);
    float px = s->mPoint.x;
    float py = s->mPoint.y;
    float pz = s->mPoint.z;
    Vec3 v;
    v.x = px;
    v.y = py;
    v.z = pz;

    if (c->GetCity() == 0) {
        return 0;
    }
    out->mPoint = v;
    out->mTime = 0.0f;

    c->MoveToPointAtSpeed(2, &v, 5.0f, 10.0f);
    c->InterruptAnimation(0x2481db1, -1, 0);
    return 1;
}

// @ 0x00d93160
bool FUN_00d93160(Creature_s00d9_22f0* c, int, int, int, int, TimedPoint* q, int, float amount)
{
    City* city = c->GetCity();
    if (city == 0) {
        return 0;
    }
    if (c->mLoco.IsNearGoal()) {
        q->mTime += amount;
        if (q->mTime > 5.0f && c->GetState() != 5) {
            c->SetState(5);
            c->InterruptAnimation(0x2481dda + sMathRandom_s00d9_22f0.RandomUint32Uniform(3), -1, 0);
            city->F8170(city->F8190() + 1);
        }
    } else {
        c->MoveToPointAtSpeed(2, &q->mPoint, 5.0f, 10.0f);
        c->InterruptAnimation(0x2481db1, -1, 0);
    }
    return 1;
}

// @ 0x00d93230
u8 __cdecl FUN_00d93230(cObj* a1, void* a2, void* a3, void* a4, void* a5, u32* a6)
{
    cSub* sub = a1->mFB8;
    if (sub->mA38 > sub->mA3c)
        return 0;
    switch (*a6) {
    case 0:
        if (!MOPS(a1->mC0)->FUN_00c42e20())
            goto ret1;
        *a6 = 1;
        break;
    case 1:
        if (!MOPS(a1)->FUN_00c123f0(0))
            goto ret1;
        break;
    default:
        goto ret1;
    }
    u32 r = MOPS((void*)0x1601760)->FUN_00a68fb0(3);
    switch (r) {
    case 0:
        MOPS(a1)->FUN_00c12190(0x2d5f9be, 1, -1);
        return 1;
    case 1:
        MOPS(a1)->FUN_00c12190(0x2d5f9cc, 1, -1);
        return 1;
    case 2:
        MOPS(a1)->FUN_00c12190(0x2d5f9c1, 1, -1);
        return 1;
    default:
        return 1;
    }
ret1:
    return 1;
}

// @ 0x00d932e0
u8 __cdecl FUN_00d932e0(cObj* a1, void* a2, void* a3, void* a4, void* a5, u32* a6)
{
    if (a6 != 0) {
        a6[2] = 0xffffffff;
        a6[3] = 0xffffffff;
    }
    cSub* sub = a1->mFB8;
    void* viz = sub->mAF0;
    sub->m9f4 -= 1;
    f32 pos[3];
    u32 v5 = 5;
    void* city = ((void* (__thiscall*)(void*, f32*, u32))VT(viz)[0x6c / 4])(viz, pos, v5);
    MOPS(city)->FUN_00bec2d0(pos, v5);

    f32 dir[3];
    void* planet = FUN_00b3d350(dir, pos, 0.0f, 4.0f);
    f32* rp = (f32*)MOPS(planet)->FUN_00b81780();
    pos[0] = rp[0];
    pos[1] = rp[1];
    pos[2] = rp[2];

    void* city2 = ((void* (__thiscall*)(void*, f32*))VT(viz)[0x6c / 4])(viz, pos);
    f32 face[3];
    ((void (__thiscall*)(void*, f32*))VT(city2)[0x70 / 4])(city2, face);

    MOPS(a1)->FUN_00c12310(0x2481db0, 0xffffffff, 0);
    f32 speed = g14853e0;
    f32 f1 = g1470f1c;
    MOPS(a1)->FUN_00c1c5c0(3, dir, face, f1, speed);

    a6[0] = 0;
    a6[1] = 0;
    return 1;
}

// @ 0x00d933d0
u8 __cdecl FUN_00d933d0(cObj* a1)
{
    f32 c4 = g14853e0;
    f32 c2 = g1470f1c;
    MOPS(a1)->FUN_00c1c1d0(2, &g169ec74, c2, c4);
    f32 r = MOPS((void*)0x1601760)->FUN_009360d0();
    if (r < 0.5f) {
        MOPS(a1)->FUN_00c1ad10(1);
    } else {
        MOPS(a1)->FUN_00c1ad10(0);
    }
    return 1;
}

// @ 0x00d93430
u8 __cdecl FUN_00d93430(cObj* a1)
{
    if (MOPS(a1->mC0)->FUN_00c42e20())
        return 0;
    f32* p = (f32*)MOPS(a1->mC0)->FUN_00c42de0();
    if (p[0] == g169ec74 && p[1] == g169ec78 && p[2] == g169ec7c)
        return 1;
    if (g169ec74 != g169f20c || g169ec78 != g169f210 || g169ec7c != g169f214) {
        MOPS(a1)->FUN_00c1c1d0(2, &g169ec74, g1470f1c, g14853e0);
        return 1;
    }
    return 0;
}

// @ 0x00d934f0
u8 __cdecl FUN_00d934f0(cObj* a1)
{
    cSub* sub = a1->mFB8;
    u8** pBegin = &sub->mB94;
    u8* begin = *pBegin;
    u8* end = sub->mB98;
    s32 count = (s32)(end - begin) >> 3;
    s32 i = 0;
    if (count > 0) {
        u32 key = a1->mFF0;
        for (; i < count; i++) {
            if (((cEntry*)begin)[i].key == key) {
                if (((cEntry*)begin)[i].count > 0) {
                    u32 v = ((u32 (__thiscall*)(void*))VT(a1)[0x4c / 4])(a1);
                    a1->mFF0 = v;
                    u8* p = *pBegin;
                    ((cEntry*)p)[i].count -= 1;
                }
                break;
            }
        }
    }
    return 0;
}

// @ 0x00d93560
u8 __cdecl FUN_00d93560(cObj* a1)
{
    cSub* sub = a1->mFB8;
    u8* begin = sub->mB80;
    u8* end = sub->mB84;
    s32 count = (s32)(end - begin) >> 3;
    u8** pBegin = &sub->mB80;
    s32 i = 0;
    for (; i < count; i++) {
        if (((cEntry*)begin)[i].count > 0) {
            a1->mFF0 = ((cEntry*)begin)[i].key;
            u8* q = *pBegin;
            ((cEntry*)q)[i].count -= 1;
            MOPS(a1)->FUN_00c12310(0x4fe76c4, 0xffffffff, 0);
            return 1;
        }
    }
    return 0;
}

// @ 0x00d935d0
f32 __cdecl FUN_00d935d0(cObj* a1)
{
    void* q = a1->mFB8->m38c;
    if (q != 0) {
        f32* a = (f32*)((void* (__thiscall*)(void*))VT(q)[0x2c / 4])(q);
        f32* b = (f32*)((void* (__thiscall*)(void*))VT(a1->mC0)[0x2c / 4])(a1->mC0);
        f64 dx = (f64)b[0] - a[0];
        f64 dy = (f64)b[1] - a[1];
        f64 dz = (f64)b[2] - a[2];
        if (sqrt(dy * dy + (dz * dz + dx * dx)) < g140c6e8) {
            f32* c = (f32*)((void* (__thiscall*)(void*))VT(a1->mC0)[0x2c / 4])(a1->mC0);
            if (MOPS(&a1->mFB8->m1bc)->FUN_00afad70(c) != 0)
                return 1.0f;
        }
    }
    MOPS(&((cStimuli*)a1->mB4c)->mOp)->FUN_00bc98f0(0x400, 0);
    return 0.0f;
}

// @ 0x00d93670
u8 __cdecl FUN_00d93670(cObj* a1, void* a2, void* a3, void* a4, void* a5, u8* a6)
{
    if (a6 != 0)
        ((cState*)a6)->m4 = 0;
    f32* pos = (f32*)((void* (__thiscall*)(void*))VT(a1->mC0)[0x2c / 4])(a1->mC0);
    void* slot = MOPS(&a1->mFB8->m1bc)->FUN_00afad70(pos);
    if (slot == 0)
        return 0;
    MOPS(slot)->FUN_00afa030(a1);
    MOPS(a1)->FUN_00c12310(0x2481db0, 0xffffffff, 0);
    cSub* sub = a1->mFB8;
    cSlot* s = (cSlot*)slot;
    f32 dx = sub->m1d0 - s->x;
    f32 dy = sub->m1d4 - s->y;
    f32 dz = sub->m1d8 - s->z;
    f32 inv = 1.0f / sqrtf(dx * dx + dy * dy + dz * dz + g13ec4b8);
    f32 nx = inv * dx;
    f32 ny = inv * dy;
    f32 nz = inv * dz;
    MOPS(a1)->FUN_00c1c5c0(2, &s->x, &nx, 1.0f, g1470f1c);
    MOPS(a1)->FUN_00c1ad10(1);
    ((cState*)a6)->m0 = 1;
    return 1;
}

// @ 0x00d937b0
f32 __cdecl FUN_00d937b0(cObj* a1)
{
    cSub* sub = a1->mFB8;
    f32 radius = sub->mA24;
    if (radius > g1485378) {
        f32 pos[3];
        pos[0] = sub->mA14;
        pos[1] = sub->mA18;
        pos[2] = sub->mA1c;
        f32* p = (f32*)((void* (__thiscall*)(void*))VT(a1->mC0)[0x2c / 4])(a1->mC0);
        f32 d[3];
        d[0] = p[0] - pos[0];
        d[1] = p[1] - pos[1];
        d[2] = p[2] - pos[2];
        if (sqrt((f64)d[2] * d[2] + (f64)d[1] * d[1] + (f64)d[0] * d[0]) < radius + 12.0f)
            return 1.0f;
    }
    return 0.0f;
}

// @ 0x00d93df0
f32 __cdecl FUN_00d93df0(cObj* a1)
{
    cSub* sub = a1->mFB8;
    s32 idx = sub->mA44;
    if (idx != -1) {
        u32 base = sub->m220;
        void* circle = (void*)(base + idx * 100);
        if (MOPS(circle)->FUN_00af9fa0() < 5)
            return 1.0f;
    }
    return 0.0f;
}

// @ 0x00d93f70
void __cdecl FUN_00d93f70(cObj* a1, void* a2, void* a3, void* a4, void* a5, u32* a6)
{
    s32 idx = (s32)a6[1];
    if (idx != -1) {
        cSub* sub = a1->mFB8;
        s32 count = (s32)(sub->m224 - sub->m220) / 100;
        if (count > idx) {
            void* circle = (void*)(sub->m220 + idx * 100);
            MOPS(circle)->FUN_00afae50(a1);
        }
    }
    MOPS(a1)->FUN_00c1ad10(0);
}

// @ 0x00d93fd0
namespace SP { namespace CitizenTree {
bool RepairBuilding_Tick(Citizen* c, int a2, int a3, int a4, int a5, RepairState* st, int a7, int a8)
{
    Citizen* tgt = st->mpTarget_c;
    Combatant* comb = tgt ? &tgt->mCombatant : 0;
    if (comb->GetDamageState() == 2)
        return false;
    if (comb->GetSize_58() == comb->mHealth_38)
        return false;
    if (c->mLoco.IsNearGoal())
    {
        if (st->mbFlag_0)
        {
            st->mbFlag_0 = 0;
            if (sMathRandom_s00d9_3fd0.RandomUint32Uniform(10) < 5)
                c->PlayAnimation(0x50f3406, 1, -1);
            else
                c->PlayAnimation(0x50f3407, 1, -1);
            return true;
        }
        int outId;
        if (c->WaitForAnimEventOrEnd(gAnimEventCond, &outId, -1, 0, 0))
        {
            if (outId != -1)
            {
                c->SetCurrentToolEffect(0x13, (unsigned int)c->SetToolEffectId(outId));
                return true;
            }
            ActionCircle_s00d9_3fd0* circle = (ActionCircle_s00d9_3fd0*)(c->mpOwner_0fb8->mpActionPool_220 + st->mSlotA_4 * 100);
            int count = (int)(circle->mpEnd_54 - circle->mpBegin_50);
            int cur = st->mSlotB_8;
            int next;
            if (sMathRandom_s00d9_3fd0.RandomUint32Uniform(10) < 5)
                next = (cur == count - 1) ? 0 : cur + 1;
            else
                next = (cur == 0) ? count - 1 : cur - 1;

            ActionSlot_s00d9_3fd0* slot = circle->SlotAt((uint32_t)next);
            if (!slot->mOccupied)
            {
                circle->SlotAt((uint32_t)cur)->Clear();
                slot->Reserve(c);
                st->mSlotB_8 = next;
            }
            const Vec3* here = c->mLoco.GetPosition();
            Vec3 facing;
            facing.x = circle->mPos_14.x - here->x;
            facing.y = circle->mPos_14.y - here->y;
            facing.z = circle->mPos_14.z - here->z;
            c->MoveToPointAndFacingAtSpeed(2, c->mLoco.GetPosition(), &facing, kFlHalf, kFlTwo);
            c->SetCurrentToolEffect(0, 0xffffffff);
            st->mbFlag_0 = 1;
        }
    }
    return true;
}
}}  // namespace SP::CitizenTree

// @ 0x00d941e0
namespace SP { namespace CitizenTree {
float OutsideCity_Decide(Citizen* c)
{
    City_s00d9_3fd0* city = c->GetCity();
    if (city)
    {
        float wallR = city->GetWalls()->mRadius_25c;
        const Vec3* cp = city->mCityLoco_120.GetPosition();
        const Vec3* mp = c->mLoco.GetPosition();
        float dx = mp->x - cp->x;
        float dy = mp->y - cp->y;
        float dz = mp->z - cp->z;
        float dist = sqrtf((dx * dx + dz * dz) + dy * dy);
        if (dist > wallR)
            return 1.0f;
    }
    return 0.0f;
}
}}  // namespace SP::CitizenTree

// @ 0x00d94260
namespace SP { namespace CitizenTree {
bool HostileAlien_Activate(Citizen* c, int a2, int a3, int a4, int a5, uint8_t* out)
{
    City_s00d9_3fd0* city = c->GetCity();
    Vec3 start = *c->mLoco.GetPosition();
    if (city->GetWalls()->PointInsideInnerWall(&start))
        GetNearestLaneNode(&start, c);
    const Vec3* cp = city->mCityLoco_120.GetPosition();
    Vec3 d;
    d.x = cp->x - start.x;
    d.y = cp->y - start.y;
    d.z = cp->z - start.z;
    Vec3 facing;
    normalized_safe(&facing, &d);
    c->MoveToPointAndFacingAtSpeed(2, &start, &facing, kFlOne, kFlTwo);
    *out = 1;
    return true;
}
}}  // namespace SP::CitizenTree

// @ 0x00d943b0
namespace SP { namespace CitizenTree {
float AttackNearbyTribe_Decide(Citizen* c, int a2, int a3, int a4, void* stimuli, uint8_t* out)
{
    Locomotion_s00d9_3fd0::NeighborList* list = c->mLoco.GetNeighbors();
    void** it = list->mpBegin;
    void** end = list->mpEnd;
    if (it == end)
        return 0.0f;
    do
    {
        Citizen* candidate = (Citizen*)*it;
        if (candidate)
        {
            Citizen* obj = (Citizen*)candidate->AsInterface_b8(0x4f176642);
            if (obj && obj->IsValidTarget_c232c0() && c->mObjectId_0b20 != obj->mObjectId_0b20)
            {
                if (stimuli)
                    ((BehaviorStimuli*)stimuli)->GetAny();
                void* payload = &obj->mStimulusPayload_5a8;
                *(void**)((char*)stimuli + 4) = payload;
                *out = 1;
                return 1.0f;
            }
        }
        ++it;
    } while (it != end);
    return 0.0f;
}
}}  // namespace SP::CitizenTree

// @ 0x00d94440
namespace SP { namespace CitizenTree {
float DetectNearbyCreature_Decide(Citizen* c, int a2, int a3, int a4, void* stimuli, uint8_t* out)
{
    Locomotion_s00d9_3fd0::NeighborList* list = c->mLoco.GetNeighbors();
    void** it = list->mpBegin;
    void** end = list->mpEnd;
    if (it == end)
        return 0.0f;
    do
    {
        Citizen* candidate = (Citizen*)*it;
        if (candidate)
        {
            Citizen* obj = (Citizen*)candidate->AsInterface_b8(0xd0036e08);
            if (obj && c->mObjectId_0b20 != obj->mObjectId_0b20)
            {
                if (stimuli)
                    ((BehaviorStimuli*)stimuli)->GetAny();
                void* payload = &obj->mStimulusPayload_5a8;
                *(void**)((char*)stimuli + 4) = payload;
                *out = 1;
                return 1.0f;
            }
        }
        ++it;
    } while (it != end);
    return 0.0f;
}
}}  // namespace SP::CitizenTree

// @ 0x00d94610
namespace SP { namespace CitizenTree {
float ForcedDeath_Decide(Citizen* c)
{
    if (c->mLoco.Slot48())
        return 0.0f;
    AppObject* app = App();
    ViewerHolder* vh = (ViewerHolder*)app->Slot50();
    Viewer* viewer = vh->GetViewer_1c();
    Vec3 cam;
    viewer->GetCameraLocationInfo(&cam, 0, 0, 0);
    if (!(gForcedDeathInit & 1))
    {
        gForcedDeathInit |= 1;
        gForcedDeathDistSq = kFlForcedDeathDistSq;
    }
    const Vec3* mp = c->mLoco.GetPosition();
    float dx = cam.x - mp->x;
    float dy = cam.y - mp->y;
    float dz = cam.z - mp->z;
    float d2 = (dz * dz + dy * dy) + dx * dx;
    if (d2 > gForcedDeathDistSq)
        return 1.0f;
    return 0.0f;
}
}}  // namespace SP::CitizenTree

// @ 0x00d946e0
namespace SP { namespace CitizenTree {
float ArtifactHeld_Decide(Citizen* c)
{
    Owner_s00d9_3fd0* o = c->mpOwner_0fb8;
    if (o && !o->mbArtifactNotHeld_0a51 && o->mpArtifact_0a54)
        return 1.0f;
    return 0.0f;
}
}}  // namespace SP::CitizenTree

// @ 0x00d94710
namespace SP { namespace CitizenTree {
bool ArtifactMover_Tick(Citizen* c, int a2, int a3, int a4, int a5, ArtifactState* st, int a7, int a8)
{
    Owner_s00d9_3fd0* owner = c->mpOwner_0fb8;
    if (st->mpArtifact_0 != (Object*)owner->mpArtifact_0a54)
        return false;

    if (st->mPhase_4 == 1)
    {
        if (c->mLoco.IsNearGoal())
        {
            ActionSlot_s00d9_3fd0* slot = ActionCircleFindSlot(c->GetCity()->GetActions(), &st->mRoute_8);
            if (slot)
            {
                Object* art = st->mpArtifact_0;
                (*(void(**)(void*, const Vec3*))(*(uint32_t*)((char*)art + 0x34) + 0x38))((char*)art + 0x34, &st->mRoute_8);
                slot->Reserve(art);
            }
            Object* old = st->mpArtifact_0;
            st->mpArtifact_0 = 0;
            if (old)
                old->Release();
            Object* old2 = (Object*)c->mpOwner_0fb8->mpArtifact_0a54;
            c->mpOwner_0fb8->mpArtifact_0a54 = 0;
            if (old2)
                old2->Release();
            return false;
        }
        const Vec3* p1 = c->mLoco.GetPosition();
        Vec3 base = *p1;
        Object* art = st->mpArtifact_0;
        const Vec3* p2 = (*(const Vec3*(**)(void*))(*(uint32_t*)((char*)art + 0x34) + 0x2c))((char*)art + 0x34);
        Vec3 d;
        d.x = p2->x - base.x;
        d.y = p2->y - base.y;
        d.z = p2->z - base.z;
        float turn = (*(float(**)(void*))(*(uint32_t*)((char*)art + 0x34) + 0x74))((char*)art + 0x34);
        float scale = turn + kFlOne;
        Vec3 n;
        normalized_safe(&n, &d);
        Vec3 target;
        target.x = n.x * scale + base.x;
        target.y = n.y * scale + base.y;
        target.z = n.z * scale + base.z;
        (*(void(**)(void*, const Vec3*))(*(uint32_t*)((char*)art + 0x34) + 0x38))((char*)art + 0x34, &target);
        return true;
    }
    if (st->mPhase_4 == 0)
    {
        if (!c->mLoco.IsNearGoal())
            return true;
        c->GetCity()->GetWalls();
        const Vec3* mp = c->mLoco.GetPosition();
        Vec3 pos = *mp;
        ActionSlot_s00d9_3fd0* slot = ActionCircleFindSlot(c->GetCity()->GetActions(), &pos);
        if (!slot)
        {
            ArtifactSlotClear(&c->mpOwner_0fb8->mpArtifact_0a54);
            return false;
        }
        st->mRoute_8 = *(Vec3*)((char*)slot + 0xc);
        c->SetSprinting(false);
        c->MoveToPointAtSpeed(2, &st->mRoute_8, kFlOne, kFlTwo);
        st->mPhase_4 = 1;
    }
    return true;
}
}}  // namespace SP::CitizenTree

// @ 0x00d949a0
namespace SP { namespace CitizenTree {
bool ArtifactSeek_Activate(Citizen* c, int a2, int a3, int a4, int a5, uint8_t* out)
{
    if (out)
        *out = 0;
    Vec3 lane;
    GetNearestLaneNode(&lane, c);
    const Vec3* mp = c->mLoco.GetPosition();
    if (lane.x == mp->x && lane.y == mp->y && lane.z == mp->z)
        GetPlanetModel_s00d9_3fd0()->MakeRandomWorldPosition(&lane, c->mLoco.GetPosition(), kFlTwo, kFlFour);
    Vec3 rnd;
    GetPlanetModel_s00d9_3fd0()->MakeRandomWorldPosition(&rnd, &lane, 0.0f, kFlFifteen);
    lane = rnd;
    c->InterruptAnimation(0x2481db0, -1, 0);
    City_s00d9_3fd0* city = c->GetCity();
    const Vec3* cp = city->mCityLoco_120.GetPosition();
    Vec3 facing;
    facing.x = cp->x - lane.x;
    facing.y = cp->y - lane.y;
    facing.z = cp->z - lane.z;
    Vec3 d;
    normalized_safe(&d, &facing);
    c->MoveToPointAndFacingAtSpeed(2, &lane, &d, kFlOne, kFlSix);
    return true;
}
}}  // namespace SP::CitizenTree

// @ 0x00d94b60
namespace SP { namespace CitizenTree {
bool WanderFlee_Activate(Citizen* c, int a2, int a3, int a4, int a5, uint8_t* out)
{
    if (out)
    {
        *out = 0;
        *(float*)(out + 4) = 0.0f;
    }
    City_s00d9_3fd0* city = c->GetCity();
    Vec3 routeB, routeA;
    city->RouteVec(&routeB, &routeA);
    ActionCircle_s00d9_3fd0* circle = city->GetRoute3ec();
    const Vec3* mp = c->mLoco.GetPosition();
    ActionSlot_s00d9_3fd0* slot = ActionCircleFindSlot(circle, mp);
    Vec3 pt;
    if (slot)
        pt = *(Vec3*)((char*)slot + 0xc);
    else
        pt = routeA;
    float maxD = routeB.z - c->mLoco.GetTurnRate();
    Vec3 rnd;
    GetPlanetModel_s00d9_3fd0()->MakeRandomWorldPosition(&rnd, &pt, 0.0f, maxD);
    c->MoveToPointAtSpeed(2, &rnd, kFlOne, kFlThree);
    return true;
}
}}  // namespace SP::CitizenTree

// @ 0x00d94c60
namespace SP { namespace CitizenTree {
void* FindNearestObj(void** vec, const Vec3* p, bool (*pred)(void*))
{
    void** begin = (void**)vec[0];
    void** end = (void**)vec[1];
    void* best = 0;
    float bestD = FLT_MAX;
    if (begin == end)
        return 0;
    do
    {
        void* o = *begin;
        if (pred(o))
        {
            const Vec3* op = ((ObjView*)o)->mSpatial_34.GetPosition();
            float dx = op->x - p->x;
            float dy = op->y - p->y;
            float dz = op->z - p->z;
            float d = (dx * dx + dz * dz) + dy * dy;
            if (d < bestD)
            {
                bestD = d;
                best = o;
            }
        }
        ++begin;
    } while (begin != end);
    return best;
}
}}  // namespace SP::CitizenTree

// @ 0x00d94d10
namespace SP { namespace CitizenTree {
void* FindNearestObjCitizen(void** vec, const Vec3* p, bool (*pred)(void*))
{
    void** begin = (void**)vec[0];
    void** end = (void**)vec[1];
    void* best = 0;
    float bestD = FLT_MAX;
    if (begin == end)
        return 0;
    do
    {
        Citizen* o = (Citizen*)*begin;
        if (pred(o ? &o->mCombatant : 0))
        {
            const Vec3* op = ((ObjView*)o)->mSpatial_34.GetPosition();
            float dx = op->x - p->x;
            float dy = op->y - p->y;
            float dz = op->z - p->z;
            float d = (dx * dx + dz * dz) + dy * dy;
            if (d < bestD)
            {
                bestD = d;
                best = o;
            }
        }
        ++begin;
    } while (begin != end);
    return best;
}
}}  // namespace SP::CitizenTree

// @ 0x00d94dd0
namespace SP { namespace CitizenTree {
bool ProfZone_Tick(Citizen* c, int a2, int a3, uint32_t flags)
{
    BehaviorTree* tree = c->mpBehaviorTree_0b4c;
    if (tree->mFlags_1c8 & 0x8000)
    {
        ((BehaviorStimuli*)((char*)c->mpBehaviorTree_0b4c + 8))->ClearAll(0x8000, 0);
        ((BehaviorStimuli*)((char*)c->mpBehaviorTree_0b4c + 8))->ClearAll(0x800, 0);
        c->mpOwner_0fb8->EnterZone(c);
        c->mpOwner_0fb8->SetFlag(c, (flags & 0x801) != 0);
        return true;
    }
    if (tree->mFlags_1c8 & 0x800)
        return false;
    StimuliZone* zone = c->mpOwner_0fb8->GetZone(c);
    if (zone)
    {
        int id = -1;
        if (zone->Find(0x6d30dd42, &id, 1))
        {
            uint8_t* zd = c->mpOwner_0fb8->mpZoneData_af0;
            Vec3 v = *(Vec3*)(zd + 0x7d8);
            zone->SetPos(&v);
        }
        if (zone->Find(0x6d30dd41, &id, 1))
        {
            uint8_t* zd = c->mpOwner_0fb8->mpZoneData_af0;
            Vec3 v = *(Vec3*)(zd + 0x7e4);
            zone->SetPos(&v);
        }
    }
    return true;
}
}}  // namespace SP::CitizenTree

// @ 0x00d960b0
bool __cdecl ExtinguishCitizen_Activate(cGateCitizen* pCitizen)
{
    {
        cMoveRequest request;
        request.m_f010 = g169f20c;
        request.m_f060 = g1470f1c;
        request.m_f018 = g169f210;
        request.m_f01C = g169f214;
        request.m_f020 = g1485720;
        request.m_f064 = g13ec4b4;
        request.m_buffer.m_pData = nullptr;
        request.m_n004 = 0;
        request.m_n008 = 0;
        request.m_n024 = 0;
        request.m_b04C = false;
        request.m_f050 = 0.0f;
        request.m_f054 = 0.0f;
        request.m_f058 = 0.0f;
        request.m_n05C = 0;
        request.m_f068 = g147c0f4;
        request.m_f06C = 0.0f;
        request.m_n070 = 0;
        pCitizen->m_spatial.RequestMove(&request);
    }
    pCitizen->FUN_00c0cff0(0);
    pCitizen->m_bGateActive = false;
    pCitizen->m_bFlagF90 = false;
    pCitizen->Hide();
    pCitizen->m_bFlagFBC = false;
    return true;
}

// @ 0x00d963d0
void __cdecl ExtinguishBuilding_Deactivate(cGateCitizen* pCitizen, int32_t nArg2, int32_t nArg3, int32_t nArg4, int32_t nArg5, cExtinguishMemory* pMem)
{
    if (pMem->m_nBuildingIndex != -1) {
        cCityVisualizer* pVisualizer = pCitizen->m_pVisualizer;
        int32_t nCircles = (int32_t)(pVisualizer->m_pCircleEnd - pVisualizer->m_pCircleBegin);
        if (pMem->m_nBuildingIndex < nCircles)
            (pVisualizer->m_pCircleBegin + pMem->m_nBuildingIndex)->RemoveAgent(pCitizen);
    }
    pCitizen->SetSprinting(false);
    pCitizen->InterruptAnimation(0x02481db0, -1, 0);
    pMem->m_ref010.Reset();
    pMem->m_ref014.Reset();
    pMem->m_ref018.Reset();
    pMem->~cExtinguishMemory();
}

// @ 0x00d964a0
namespace SP { namespace CitizenTree {
bool Policeman_Tick(Creature_s00d9_64a0* c, int a2, int a3, int a4, int a5, PolicemanState* st, int a7, float dt)
{
    Target* newTarget = c->mpOwner->mpTarget;
    Target* oldTarget = st->mpTarget;
    if (newTarget != oldTarget)
    {
        if (newTarget)
            newTarget->AddRef();
        st->mpTarget = newTarget;
        if (oldTarget)
            oldTarget->Release();
    }
    if (!st->mpTarget)
        return false;

    const Vec3* tp = st->mpTarget->GetSpatial()->GetPosition();
    Vec3 tpos = *tp;
    Locomotion_s00d9_64a0* loco = &c->mLoco;
    const Vec3* mp = loco->GetPosition();
    Vec3 mpos = *mp;
    Vec3 d;
    d.x = tpos.x - mpos.x;
    d.y = tpos.y - mpos.y;
    d.z = tpos.z - mpos.z;
    float dist = sqrtf((d.x * d.x + d.z * d.z) + d.y * d.y);
    float inv = 1.0f / dist;
    Vec3 dir;
    dir.x = inv * d.x;
    dir.y = d.y * inv;
    dir.z = d.z * inv;
    bool far = dist > 12.0f;
    Vec3 ftmp;
    const Vec3* fwd = loco->GetForward(&ftmp);
    bool notFacing = 0.9f > (fwd->z * dir.z + fwd->y * dir.y) + dir.x * fwd->x;

    if (far)
    {
        const Vec3* goal = loco->GetPath()->Back();
        float gx = goal->x - tpos.x;
        float gy = goal->y - tpos.y;
        float gz = goal->z - tpos.z;
        if (sqrtf((gx * gx + gz * gz) + gy * gy) > 12.0f)
        {
            Vec3 rnd;
            GetPlanetModel_s00d9_64a0()->MakeRandomWorldPosition(&rnd, &tpos, 6.0f, 10.0f);
            c->MoveToPointAndFacingAtSpeed(2, &rnd, &dir, 1.0f, 2.0f);
        }
    }
    else if (notFacing)
    {
        c->MoveToPointAndFacingAtSpeed(2, &mpos, &dir, 1.0f, 2.0f);
    }
    else
    {
        loco->StopMoving();
        if (!st->mpEffect)
        {
            EffectsManager* mgr = GetEffectsManager();
            if (st->mpEffect)
            {
                EffectHandle* old = st->mpEffect;
                st->mpEffect = 0;
                old->Release();
            }
            mgr->PlayEffect(0xcd7bc525, 0, &st->mpEffect);
            if (st->mpEffect)
                st->mpEffect->Start(0);
        }
        if (st->mpEffect)
        {
            uint32_t buf[12];
            const float* b = loco->GetBoundingBox(buf);
            Vec3 ctmp;
            ctmp.x = (b[0] + b[3]) * 0.5f;
            ctmp.y = (b[4] + b[1]) * 0.5f;
            ctmp.z = (b[5] + b[2]) * 0.5f;
            Vec3 C = ctmp;
            uint32_t buf2[12];
            const float* b2 = st->mpTarget->GetSpatial()->GetBoundingBox(buf2);
            float tx = (b2[0] + b2[3]) * 0.5f;
            float ty = (b2[4] + b2[1]) * 0.5f;
            float tz = (b2[5] + b2[2]) * 0.5f;
            float ex = tx - C.x;
            float ey = ty - C.y;
            float ez = tz - C.z;
            float len = sqrtf((ez * ez + ey * ey) + ex * ex);
            float ilen = 1.0f / len;
            float step = len * 0.14285715f;
            float sx = (ilen * ex) * step;
            float sy = (ey * ilen) * step;
            float sz = (ez * ilen) * step;
            Vec3 pts[8];
            pts[0] = C;
            pts[1].x = sx + C.x;  pts[1].y = sy + C.y;  pts[1].z = sz + C.z;
            pts[2].x = sx * 2.0f + C.x;  pts[2].y = sy * 2.0f + C.y;  pts[2].z = sz * 2.0f + C.z;
            pts[3].x = sx * 3.0f + C.x;  pts[3].y = sy * 3.0f + C.y;  pts[3].z = sz * 3.0f + C.z;
            pts[4].x = sx * 4.0f + C.x;  pts[4].y = sy * 4.0f + C.y;  pts[4].z = sz * 4.0f + C.z;
            pts[5].x = sx * 5.0f + C.x;  pts[5].y = sy * 5.0f + C.y;  pts[5].z = sz * 5.0f + C.z;
            pts[6].x = sx * 6.0f + C.x;  pts[6].y = sy * 6.0f + C.y;  pts[6].z = sz * 6.0f + C.z;
            pts[7].x = sx * 7.0f + C.x;  pts[7].y = sy * 7.0f + C.y;  pts[7].z = sz * 7.0f + C.z;
            st->mpEffect->SetPoints(13, pts, 8);

            Transform xf((Transform::InlineInit()));
            xf.mRotation = sIdentityMatrix;
            xf.SetOffset(C);
            xf.mfScale = 1.0f;
            st->mpEffect->SetTransform(&xf);
        }

        float mag = (st->mpTarget->GetScale() * dt) * 0.1f;
        Vec3 away;
        away.x = mpos.x - tpos.x;
        away.y = mpos.y - tpos.y;
        away.z = mpos.z - tpos.z;
        float ia = 1.0f / sqrtf(((away.z * away.z + away.y * away.y) + away.x * away.x) + 1e-8f);
        Vec3 u;
        u.x = ia * away.x;
        u.y = away.y * ia;
        u.z = away.z * ia;
        st->mpTarget->ApplyImpulse(mag, c->GetSource(), 1, &u, &c->mField5a8);
        return true;
    }

    if (st->mpEffect)
    {
        st->mpEffect->Stop(0);
        EffectHandle* e = st->mpEffect;
        st->mpEffect = 0;
        if (e)
            e->Release();
    }
    return true;
}
}}  // namespace SP::CitizenTree

// @ 0x00d96da0
namespace SP { namespace CitizenTree {
bool SimFeedback_Activate(CitizenCreature* c, int a2, int a3, uint8_t flags, int a5, RouteChoice* out)
{
    RouteList* routes = c->GetCity()->GetRoutes();
    if (routes->mpBegin == routes->mpEnd)
        return false;
    uint32_t n = (uint32_t)(((char*)routes->mpEnd - (char*)routes->mpBegin) / 0x50);
    RouteSegment* seg = routes->mpBegin + sMathRandom_s00d9_64a0.RandomUint32Uniform(n);

    Vec3 S, E, dS, dE;
    float p1, p2, p3;
    if (0.5f <= sMathRandom_s00d9_64a0.RandomDoubleUniform())
    {
        S = seg->pointV;
        dS = seg->dirV;
        E = seg->pointU;
        dE = seg->dirU;
        p1 = seg->probsB[0];
        p2 = seg->probsB[1];
        p3 = seg->probsB[2];
    }
    else
    {
        S = seg->pointU;
        dS = seg->dirU;
        E = seg->pointV;
        dE = seg->dirV;
        p1 = seg->probsA[0];
        p2 = seg->probsA[1];
        p3 = seg->probsA[2];
    }

    float r = (float)sMathRandom_s00d9_64a0.RandomDoubleUniform();
    if (r < p1)
    {
        out->mode = 0;
        c->mFieldFC0 = 0;
    }
    else
    {
        int m;
        if (p2 + p1 > r)
            m = 1;
        else if ((p3 + p2) + p1 > r)
        {
            out->mode = 2;
            c->Method_c0d0c0(2, 1);
            c->mFieldFC0 = 2;
            goto modeDone;
        }
        else
            m = 3;
        out->mode = m;
        c->mFieldFC0 = m;
    }
modeDone:
    out->start = S;
    out->end = E;

    WaypointVector path;
    Locomotion_s00d9_64a0* loco = &c->mLoco;
    if (flags & 1)
    {
        float t = (float)sMathRandom_s00d9_64a0.RandomDoubleUniform();
        Vec3 P;
        P.x = (E.x - S.x) * t + S.x;
        P.y = (E.y - S.y) * t + S.y;
        P.z = (E.z - S.z) * t + S.z;
        loco->SetPosition(&P);
        Vec3 d;
        d.x = E.x - S.x;
        d.y = E.y - S.y;
        d.z = E.z - S.z;
        float inv = 1.0f / sqrtf(((d.x * d.x + d.z * d.z) + d.y * d.y) + 1e-8f);
        Vec3 u;
        u.x = inv * d.x;
        u.y = d.y * inv;
        u.z = d.z * inv;
        Quat q;
        loco->SetOrientation(GetPlanetModel_s00d9_64a0()->BuildSurfaceOrientation(&q, &S, &u));
        path.push_back(Waypoint(dE.x * 3.0f + E.x, dE.y * 3.0f + E.y, dE.z * 3.0f + E.z));
        path.push_back(Waypoint(E.x, E.y, E.z));
    }
    else
    {
        loco->SetPosition(&S);
        Quat q;
        loco->SetOrientation(GetPlanetModel_s00d9_64a0()->BuildSurfaceOrientation(&q, &S, &dS));
        path.push_back(Waypoint(dS.x * 3.0f + S.x, dS.y * 3.0f + S.y, dS.z * 3.0f + S.z));
        path.push_back(Waypoint(dE.x * 3.0f + E.x, dE.y * 3.0f + E.y, dE.z * 3.0f + E.z));
        path.push_back(Waypoint(E.x, E.y, E.z));
    }
    loco->SetPath(PathRequest(path));
    c->SetMoveState(2);
    c->mField330 = 0;
    c->mpOwner->mCounter++;
    return true;
}
}}  // namespace SP::CitizenTree

// @ 0x00d97420
void __thiscall SP::CitizenTree_s00d9_7420::FUN_00d97420()
{
}

// @ 0x00d97720
void __thiscall SP::CitizenTree_s00d9_7420::EnterCity_Activate()
{
}

// @ 0x00d979b0
void __thiscall SP::CitizenTree_s00d9_7420::CultureAttack_Activate()
{
}

// @ 0x00d97d40
void __cdecl RemoveFromCultureStageGroup(SP::CitizenTree_s00d9_7420* pTree, int32_t stage, cSPCreatureCitizen_s00d9_7420* pCitizen)
{
    pTree->mCircles[stage].RemoveAgent(pCitizen);
    spstl::remove_1st(&pTree->mStageGroups[stage], &pCitizen);
}

// @ 0x00d97d80
void __thiscall SP::CitizenTree_s00d9_7420::CultureAttack_Tick()
{
}

// @ 0x00d980e0
void __cdecl CultureAttack_Deactivate(cSPCreatureCitizen_s00d9_7420* pCitizen, int32_t a2, int32_t a3, int32_t a4, int32_t a5, tCultureAttackInfo* pInfo)
{
    if (pInfo->mRecordIndex == -1)
        return;
    cCultureRecord* pRecord = &pCitizen->mpRecordPage->mRecords[pInfo->mRecordIndex];
    int32_t stage = pInfo->mStage;
    cSPCreatureCitizen_s00d9_7420* pAgent = pCitizen;
    pRecord->mCircles[stage].RemoveAgent(pCitizen);
    spstl::remove_1st(&pRecord->mStageGroups[stage], &pAgent);
}
