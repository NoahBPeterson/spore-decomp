// src/game/SPGonzago/SPCreatureBase.cpp -- migrated from slice(s) s013329c0, s00ec0a40, s00c1bad0, s00c17de0, s00c16340, s00c14350, s00c12640, s00c12310, s00c11410, s00c09410, s00c080b0, s00c07480, s00c06630, s00c053b0, s00c22010, s00c1f580, s00c1c9f0, s00c18b40, s00c17350, s00c15310, s00c13340, s00c0eae0, s00c0acd0, s01335000, s00c1d640, s00c1aad0, s00c19b60, s00c104d0, s00c0fa70, s00c0ddb0, s00c0ce80, s00c0bd70 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPCreatureBase.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

// addresses retail relocates here, named so the build relocates them too
extern "C" char g_150c8bc[];
extern "C" char g_150c900[];
extern "C" char g_1570858[];
extern "C" char g_1571798[];
extern "C" char g_15816b8[];
extern "C" char g_1601760[];

// s00c19b60's items define the slices' own placement new(size_t, void*); s00c0acd0 adds <algorithm>, which reaches
// <new> through <memory>/<xmemory> (C2084).  Same hand guard as SPGraphicsModelManager.cpp (rewrite.py placement_new_guard).
#define __PLACEMENT_NEW_INLINE
#include "game/types.h"
#include "sse_helpers.h"
#include "SP/cCreatureLocomotion.h"

// unnamed retail callees and globals (address in the comment)
extern float  gF_150c8b8, gF_150c8b4, gF_150c8cc, gF_1485720, gF_146a32c, gF_146a330;
extern void*  g_16c7aa4;
extern int    g_15716d8[];
#include <math.h>
#include "SP/cSPCreatureBase.h"
#include "SP/cSPTimer.h"
#include "SP/cCombatant.h"
#include "SP/cLocomotiveObject.h"
#include <stddef.h>
#include <algorithm>
#include "SP/cGameData.h"
#include "SP/cSpatialObject.h"
#include "SP/cPlanetModel.h"
#include "SP/cSpeciesProfile.h"
#include "SP/cBehaviorTreeData.h"
#include "SP/cGonzagoTimer.h"
#include "SP/cInteractionTarget.h"
#define __PLACEMENT_NEW_INLINE   // the slices' own placement new/delete win over <new>'s (rewrite.py)
#include <new>
#include "EA/Random/RandomLinearCongruential.h"
#include "SP/cAnimatingCreature.h"
#include "SP/cInteractionAgent.h"
#include "SP/cSpeciesArchetype.h"
#include "SP/cVarListSerializer.h"
#include <string.h>
#include "EA/ResourceMan/Key.h"
#include "SP/cCameraManager.h"
#include "SP/cCivilization.h"
#include "SP/cGameNounManager.h"
#include "SP/cHerd.h"
#include "SP/cPollinator.h"
#include "SP/cRelationshipManager.h"
#include "SP/cTerrainSphere.h"
#include "nSPBehaviorTree/behavior_stimuli.h"
#include <float.h>
#include "nSPCreatureAnim/creature_instance_data.h"
#include <stdlib.h>
#include "cSPMatrix3.h"
#include "cSPTransform.h"
#include "cSPVector3.h"
#include <xmmintrin.h>
inline void operator delete(void*, void*) {}   // placement delete (<new>'s is skipped, rewrite.py)

// ---- items of slice s00c0bd70 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float  gF_1687a10, gF_1572040;
extern uint8_t g_169e37c;
extern float  g_168d910, g_168d914, g_168d918;
void* __cdecl SP_GetCurrentGameMode();                 // 0xb5b800
void* __cdecl FUN_00b3d4c0();                          // 0xb3d4c0
void* __cdecl SP_NounManager();                        // 0xb3d300
void* __cdecl SP_PlanetModel();                        // 0xb3d350
void* __cdecl FUN_00401090();                          // 0x401090
void* __cdecl FUN_004df420();                          // 0x4df420
void  __cdecl FUN_00ef1930(void*, float);              // 0xef1930
int   __cdecl FUN_00ebfd50(int, int);                  // 0xebfd50
bool  __cdecl FUN_00c0b1c0(void*, void*, int);         // 0xc0b1c0
bool  __cdecl FUN_00c0b220(void*, void*);              // 0xc0b220
void* __cdecl FUN_00d2e340();                          // 0xd2e340
void* __cdecl FUN_00b3d320();                          // 0xb3d320
void* __cdecl FUN_00c0c320(void*);                     // 0xc0c320
struct cVarListSerializer {
  uint32_t mData[0xa14 / 4];
  cVarListSerializer(void* owner, void* list, uint32_t sig);   // 0x00692f90
  int GetFields(void* fields);                                 // 0x00695960
};
struct GameDataFields {
  int GetFieldValues(void* fields);                            // 0x00b18420
};
struct LocoFields {
  int GetFieldValues(void* fields);                            // 0x00c0af90
};
struct CreatureBaseMgr {
  int FUN_00ba3f90(void* key, void* avatar, void* self);       // 0x00ba3f90
};
struct GameNounManager_s00c0_bd70 {
  void* GetAvatar();                                           // 0x00b1fdb0
};
struct DatabasePackedFile {
  void* GetLocation();                                         // 0x00a42730
};
struct behavior_stimuli {
  void* Play(uint32_t a, uint32_t b);                           // 0x00bc96a0
  void* Set(void* stimulus, uint32_t value, float timeout, void* obj); // 0x00bc97f0
  void  ClearAll(uint32_t a, uint32_t b);                       // 0x00bc98f0
};
struct GameModeObject {
  void* Get();                                                 // 0x00c04750
};
struct PlanetModelObj {
  float FUN_00b7e490();                                        // 0x00b7e490
};
struct Object1734 {
  void FUN_009ce720(int*, int*);                               // 0x009ce720
};
struct OrderManagerExec {
  int FindSlot(int, int, void*, int);                          // 0x00bca0c0
};
struct LocomotiveObject {
  float* GetVelocity();                                        // 0x00d20610
};
struct RandomLCG {
  uint32_t RandomUint32Uniform(uint32_t n);                    // 0x00a68fb0
};
struct Entity388 { uint8_t mPad0[0x388]; uint8_t m388; };
struct CreatureFields {
  uint8_t  mPad0[0xb20];
  void*    mB20;
  uint8_t  mPadB24[4];
  void*    mB28;
  uint8_t  mPadB2c[0xb4c - 0xb2c];
  void*    mB4c;
  uint8_t  mPadB50[0xb58 - 0xb50];
  uint32_t mB58;
};
struct CreatureB20    { uint8_t mPad0[0x544]; int m544; };
struct GameModeResult { uint8_t mPad0[0x490]; float m490; };
struct StimulusResult {
  uint8_t mPad0[0xc];
  int m0c;
  int m10;
  uint8_t mPad14[0x2c - 0x14];
  int m2c;
};
struct TransitionObject {
  uint8_t mPad0[0x135];
  uint8_t m135;
  uint8_t mPad136[0x5a8 - 0x136];
  uint8_t mSub5a8[4];
  uint8_t mPad5ac[0xb5e - 0x5ac];
  uint8_t mB5e;
};
struct TransitionState {
  float m0, m4, m8;
  uint8_t mPad0c[0x3c - 0xc];
  void* m3c;
  void* m40;
};
struct Global169e370 { uint8_t mPad0[0xf]; uint8_t mF; uint8_t m10; uint8_t m11; };
struct AnimCreatureExec {
  uint8_t mPad0[0x17c];
  void* m17c;
  uint8_t mPad180[0x188 - 0x180];
  void* m188;
  bool IsOrientStopAnim(uint32_t id);                           // 0x00a02740
  bool FUN_00a04940(void* p);                                   // 0x00a04940
};
struct OrderFlagsExec {
  uint8_t  mPad0[0x61c];
  uint32_t m61c;
  uint8_t  mPad620[0x698 - 0x620];
  uint32_t m698;
  uint32_t m69c;
  uint32_t m6a0;
};
struct LocomotionExec {
  uint8_t  mPad0[0x58];
  uint8_t  mSub58[0xc0 - 0x58];   // embedded vtable object
  uint8_t  mSubC0[4];             // embedded vtable object at +0xc0
  uint8_t  mPadC4[0x110 - 0xc4];
  uint32_t m110;
  uint8_t  mPad114[0x137 - 0x114];
  uint8_t  m137;
  uint8_t  mPad138[0xb20 - 0x138];
  OrderFlagsExec* mB20;
  uint8_t  mPadB24[0xb48 - 0xb24];
  OrderManagerExec* mB48;
  uint8_t  mPadB4c[0xb54 - 0xb4c];
  AnimCreatureExec* mB54;
  uint32_t mB58;
  uint8_t  mPadB5c[0xbbc - 0xb5c];
  float    mBbc;
  uint8_t  mPadBC0[0xe3c - 0xbc0];
  int      mE3c;
  uint8_t  mPadE40[0xe62 - 0xe40];
  uint8_t  mE62;
  uint8_t  mPadE63[0xe84 - 0xe63];
  Entity388* mE84;
  uint8_t  mPadE88[0xf98 - 0xe88];
  void*    mF98;
};
struct C_s00c0_bd70 {
  // simple accessors
  bool __thiscall Pred70(int x);
  bool __thiscall Preda0(int x);
  float __thiscall GetA();  // 0x00c0c010 (C::GetA)
  float __thiscall GetB();  // 0x00c0c040 (C::GetB)
  float __thiscall Get574();  // 0x00c0c0d0 (C::Get574)
  bool __thiscall Flag388();  // 0x00c0c0e0 (C::Flag388)
  bool __thiscall Flag389();  // 0x00c0c100 (C::Flag389)
  uint32_t __thiscall FlagF();  // 0x00c0c310 (C::FlagF)
  void __thiscall SetE84(void* p);  // 0x00c0c180 (C::SetE84)
  float __thiscall Speed1(char b);  // 0x00c0c1c0 (C::Speed1)
  int  __thiscall FindIndex(int key);  // 0x00c0c080 (C::FindIndex)
  void __thiscall CallFind13();  // 0x00c0c140 (C::CallFind13)
  void __thiscall CallFind27();  // 0x00c0c160 (C::CallFind27)
  void __thiscall IsDefaultSpecies_();  // 0x00c0c2d0 (C::IsDefaultSpecies_)
  C_s00c0_bd70*   __thiscall CopyRec(void* src);  // 0x00c0c3e0 (C::CopyRec)
  C_s00c0_bd70*   __thiscall QuatHalf(float a);  // 0x00c0c4b0 (C::QuatHalf)
  int  __thiscall RelationIndex(int idx, char b);  // 0x00c0ce30 (C::RelationIndex)
  __declspec(noinline) int __thiscall Cdb0();
  void __thiscall C200(float f);  // 0x00c0c200 (C::C200)
  int  __thiscall C0bd70(void* fields);
  void __thiscall C0bee0(int a, int b);  // 0x00c0bee0 (C::C0bee0)
  void __thiscall C0bf10(int a,int b,int c,int d,float e,int f,int g,int h,int i,int j,char k);
  int  __thiscall C0c250_();
  void __thiscall C0c630(char b,int* p3,int* p4,int* p5);
  void __thiscall C0c4b0(float a);
  bool __thiscall C0bb90();                                     // 0x00c0bb90
};
struct C {
  // simple accessors
  bool __thiscall Pred70(int x);
  bool __thiscall Preda0(int x);
  float __thiscall GetA();
  float __thiscall GetB();
  float __thiscall Get574();
  bool __thiscall Flag388();
  bool __thiscall Flag389();
  uint32_t __thiscall FlagF();
  void __thiscall SetE84(void* p);
  float __thiscall Speed1(char b);
  int  __thiscall FindIndex(int key);
  void __thiscall CallFind13();
  void __thiscall CallFind27();
  bool __thiscall IsDefaultSpecies_();
  C*   __thiscall CopyRec(void* src);
  C*   __thiscall QuatHalf(float a);
  int  __thiscall RelationIndex(int idx, char b);
  __declspec(noinline) int __thiscall Cdb0();
  void __thiscall C200(float f);
  int  __thiscall C0bd70(int x);
  void __thiscall C0bee0(int a, int b);
  void __thiscall C0bf10(int a,int b,int c,int d,int e,int f,int g,int h,int i,int j,int k,char l);
  void __thiscall C0c250_();
  void __thiscall C0c630(char b,int* p3,int* p4,int* p5);
  void __thiscall C0c4b0(float a);
  void __thiscall C0ccc0(float f);
};
struct CCommunityStub { void __thiscall func60h(int,int); };
// ---- items of slice s00c0bd70 end

// ---- items of slice s00c0ce80 begin (TODO(rewrite): local stubs, replace by canonical classes)
void* __cdecl FUN_00c03260(void*, int);                   // 0x00c03260
int   __cdecl FUN_00b3d230();                             // 0x00b3d230
void* __cdecl SP_GameTimeManager();                       // 0x00b3d380
void  __cdecl FUN_00bc86e0(double, void*, void*, void*, int, int); // 0x00bc86e0
struct F_ce30   { int   __thiscall f(int, int); };        // 0x00c0ce30
struct F_f31500 { float __thiscall f(); };                // 0x00f31500
struct F_a02bf0 { void  __thiscall f(int, int); };        // 0x00a02bf0
struct F_a062a0 { void  __thiscall f(int, int); };        // 0x00a062a0
struct F_a06250 { void  __thiscall f(int); };             // 0x00a06250
struct F_c0b9d0 { void  __thiscall f(float); };           // 0x00c0b9d0
struct F_b316c0 { long long __thiscall f(); };            // 0x00b316c0
struct F_a05270 { void  __thiscall Release(); };          // 0x00a05270
struct F_a048a0 { float* __thiscall f(); };                // 0x00a048a0
struct F_c0c080 { int   __thiscall f(int); };              // 0x00c0c080
struct F_b1daf0 { void* __thiscall f(); };                 // 0x00b1daf0
struct F_41ea70 { float* __thiscall f(); };                // 0x0041ea70
struct F_c88670 { void  __thiscall f(float*); };           // 0x00c88670
struct F_terrain { char __thiscall q(int, void*); };        // 0x00b1daf0 result
struct F_d9030 {
    int* __thiscall f(void*);                              // 0x004d9030
};
void* __cdecl FUN_00b3d320(void*);                         // 0x00b3d320
float* __cdecl FUN_0099c1a0(void*, void*, void*);          // 0x0099c1a0
struct F_timer {
    bool      __thiscall IsRunning();                     // 0x00feba90
    long long __thiscall GetElapsedTime();                // 0x00bc3190
    void      __thiscall Stop();                          // 0x00bc3110
    void      __thiscall Restart();                       // 0x00bc3130
};
#define G32(a)  (*(uint32_t*)(a))
#define GF(a)   (*(float*)(a))
struct CCB_s00c0_ce80 {
    float __thiscall ce80(int, int);
    void  __thiscall cf50();  // 0x00c0cf50 (CCB::cf50)
    float __thiscall cfa0(int, char);  // 0x00c0cfa0 (CCB::cfa0)
    void  __thiscall cff0(int);  // 0x00c0cff0 (CCB::cff0)
    int   __thiscall d050(float);  // 0x00c0d050 (CCB::d050)
    void  __thiscall d0c0(uint32_t, char);  // 0x00c0d0c0 (CCB::d0c0)
    void  __thiscall d1e0(int);  // 0x00c0d1e0 (CCB::d1e0)
    void  __thiscall d200(int, int);  // 0x00c0d200 (CCB::d200)
    void  __thiscall d240();  // 0x00c0d240 (CCB::d240)
    float* __thiscall d310(float*, int);
    void  __thiscall d340(int);  // 0x00c0d340 (CCB::d340)
    void  __thiscall UpdateHunger(float);
    bool  __thiscall d560(int, float, float);
    void  __thiscall d660(float*);
    void  __thiscall d860(float*);
    void  __thiscall d950(char);
    void  __thiscall d970(float*);
    void  __thiscall d9b0();
    int   __thiscall dac0();
    int   __thiscall db10();
    int   __thiscall db60();
    void  __thiscall dd40(float*);  // 0x00c0dd40 (CCB::dd40)
    void  __thiscall dd70(float*, float);
};
float __cdecl FUN_00c0db80(float, int);   // 0x00c0db80
float __cdecl FUN_00c0dcb0(float);        // 0x00c0dcb0
struct CCB {
    float __thiscall ce80(int, int);                  // 0x00c0ce80
    void  __thiscall cf50();
    float __thiscall cfa0(int, char);
    void  __thiscall cff0(int);
    int   __thiscall d050(float);
    void  __thiscall d0c0(uint32_t, char);
    void  __thiscall d1e0(int);
    void  __thiscall d200(int, int);
    void  __thiscall d240();
    float* __thiscall d310(float*);
    void  __thiscall d340(int);
    void  __thiscall UpdateHunger(float);
    int   __thiscall d560(int, float, float);
    void  __thiscall d660(float*);
    void  __thiscall d860(float*);
    void  __thiscall d950(char);
    void  __thiscall d970(float*);
    void  __thiscall d9b0();
    int   __thiscall dac0();
    int   __thiscall db10();
    int   __thiscall db60();
    void  __thiscall dd40(float*);
    void  __thiscall dd70(float*, float);
};
// ---- items of slice s00c0ce80 end

// ---- items of slice s00c0ddb0 begin (TODO(rewrite): local stubs, replace by canonical classes)
void* __cdecl FUN_009ff6f0(void*, void*);   // 0x009ff6f0
void* __cdecl FUN_0067cb20();                // 0x0067cb20
void* __cdecl FUN_00b3d2c0(void*);           // 0x00b3d2c0
void  __cdecl FUN_011e07ef(void*);           // 0x011e07ef
struct F_58     { void  __thiscall f(float*); };      // 0x00c886d0 cCommunity::func58h
struct F_cab60  { void* __thiscall f(int); };         // 0x009cab60
struct F_a02b40 { char  __thiscall f(int); };         // 0x00a02b40
struct F_a04940 { char  __thiscall f(int); };         // 0x00a04940
struct F_a02b20 { char  __thiscall f(int); };         // 0x00a02b20
struct F_a04990 { char  __thiscall f(int); };         // 0x00a04990
struct F_a049f0 { float __thiscall f(int); };         // 0x00a049f0
struct F_c232c0 { char  __thiscall f(); };            // 0x00c232c0
struct F_bfc5f0 { void* __thiscall f(); };            // 0x00bfc5f0
struct F_d00a70 { int   __thiscall f(); };            // 0x00d00a70
struct F_c04750 { void* __thiscall Call04750(); };      // 0x00c04750
struct VQuery3 { virtual void pv0(); virtual void pv1(); virtual void pv2(); virtual void* Query(int); };
struct F_d9b0   { void  __thiscall f(); };            // 0x00c0d9b0 (slice 117)
struct F_sw     { void __thiscall Ctor(int, int); unsigned long long __thiscall GetElapsedTime(); }; // 0x168db70
struct CCMInner {
    uint32_t pad_00[0x17c / 4];  // +0x000
    void*    mpTable_17c;        // +0x17c  lookup object (find by id)
};
struct CCM_s00c0_ddb0 {
    void  __thiscall ddb0(float*);  // 0x00c0ddb0 (CCM::ddb0)
    char  __thiscall de30();  // 0x00c0de30 (CCM::de30)
    void  __thiscall de60(int, int);
    bool  __thiscall dee0(int, int*, char);  // 0x00c0dee0 (CCM::dee0)
    void* __thiscall dfb0(int);
    void* __thiscall dfd0(int);
    char  __thiscall e000(int, int);
    void* __thiscall e040();  // 0x00c0e040 (CCM::e040)
    bool  __thiscall e070(int);  // 0x00c0e070 (CCM::e070)
    bool  __thiscall e0c0(int);  // 0x00c0e0c0 (CCM::e0c0)
    char  __thiscall e120(int);  // 0x00c0e120 (CCM::e120)
    char  __thiscall e170(int);
    char  __thiscall e2c0(int);
    void* __thiscall e370();  // 0x00c0e370 (CCM::e370)
    float __thiscall e3a0();  // 0x00c0e3a0 (CCM::e3a0)
    char  __thiscall e3d0();  // 0x00c0e3d0 (CCM::e3d0)
    char  __thiscall e420();  // 0x00c0e420 (CCM::e420)
    float __thiscall e480();
    float __thiscall e4f0();  // 0x00c0e4f0 (CCM::e4f0)
    void* __thiscall e580();
    void  __thiscall e5f0(float);  // 0x00c0e5f0 (CCM::e5f0)
    void  __thiscall e640(int);  // 0x00c0e640 (CCM::e640)
    int   __thiscall e660();  // 0x00c0e660 (CCM::e660)
    int   __thiscall e680(int);  // 0x00c0e680 (CCM::e680)
    int   __thiscall e6a0();
    char  __thiscall e8d0(int, int);

    uint32_t pad_a94[0xa94 / 4];                 // +0x000 .. +0xa93
    void*    mpGraspObj_a94;                     // +0xa94  grasped/sound object
    uint32_t pad_b54[(0xb54 - 0xa94 - 4) / 4];   // +0xa98 .. +0xb53
    CCMInner* mpInner_b54;                       // +0xb54  animation/creature table
};
struct CCM {
    void  __thiscall ddb0(float*);
    char  __thiscall de30();
    void  __thiscall de60(int, int);
    char  __thiscall dee0(int, int*, char);
    void* __thiscall dfb0(int);
    void* __thiscall dfd0(int);
    char  __thiscall e000(int, int);
    void* __thiscall e040();
    bool  __thiscall e070(int);
    bool  __thiscall e0c0(int);
    char  __thiscall e120(int);
    char  __thiscall e170(int);
    char  __thiscall e2c0(int);
    void* __thiscall e370();
    float __thiscall e3a0();
    char  __thiscall e3d0();
    char  __thiscall e420();
    float __thiscall e480();
    float __thiscall e4f0();
    void* __thiscall e580();
    void  __thiscall e5f0(float);
    void  __thiscall e640(int);
    int   __thiscall e660();
    int   __thiscall e680(int);
    int   __thiscall e6a0();
    char  __thiscall e8d0(int, int);
};
// ---- items of slice s00c0ddb0 end

// ---- items of slice s00c0fa70 begin (TODO(rewrite): local stubs, replace by canonical classes)
void  __cdecl FUN_0093aa70(void*, void*, int, int);  // 0x0093aa70 WriteUint32
void  __cdecl FUN_0093a780(void*, void*, int, int);  // 0x0093a780 ReadInt32
void  __cdecl FUN_0093ac80(void*);                   // 0x0093ac80 ReadBool
void  __cdecl FUN_0093a9a0(void*, void*, int);       // 0x0093a9a0 operator<<
void  __cdecl FUN_00c0b030(void*, void*);            // 0x00c0b030
void* __cdecl FUN_0067de30();                        // 0x0067de30 SP::PropertyManager
void* __cdecl FUN_00f473a0(int, const char*, int, int, int, int); // 0x00f473a0 operator_new
void  __cdecl FUN_00c10050(uint32_t, int, int, int, char); // 0x00c10050
void  __cdecl FUN_00c10230(int, int, int, int);      // 0x00c10230
struct F_a01f10 { void  __thiscall f(int, int); };   // 0x00a01f10
struct F_a047d0 { void  __thiscall f(int); };        // 0x00a047d0
struct F_f9b0   { char* __thiscall f(int, void*); }; // 0x00c0f9b0
struct AnimBinding {
    uint32_t id;        // +0x00
    int32_t  maskBit;   // +0x04  bit index into the lookup mask (0 = empty slot)
    uint32_t f08;       // +0x08
    uint32_t f0c;       // +0x0c
    uint32_t f10;       // +0x10
    float    weight;    // +0x14
    char     flags;     // +0x18
    int32_t  handle;    // +0x1c
    void*    target;    // +0x20
};
struct CAN {
    char         _pad0[0xb48];
    void*        playCtx;    // +0xb48  animation play context (thiscall receiver)
    char         _pad2[8];
    void*        animCtx;    // +0xb54  animation subsystem context
    char         _pad1[0xe40 - 0xb58];
    AnimBinding* bindBegin;  // +0xe40
    AnimBinding* bindEnd;    // +0xe44
    void* __thiscall fa70(uint32_t, uint32_t*);
    void  __thiscall fae0(int);
    void  __thiscall fb40(int);
    void  __thiscall fb80(int, int);
    __declspec(noinline) void* __thiscall fe30(void*);
};
struct CANCtx {
    char  _pad0[0x17c];
    void* remapTable;   // +0x17c
    char  _pad1[4];
    void* bindingDst;   // +0x184  -> F_a01f10 receiver
};
struct AnimPlayCtx {
    void __thiscall Play(int, int, void*, float, void*, int);   // 0x00bca810
};
struct AnimSlotSrc {
    char  _pad0[0x10c];
    float weight;       // +0x10c
};
struct AnimParamObj {   // the caller's animation-object argument
    char  _pad0[0xfbc];
    void* sub;          // +0xfbc
};
struct AnimFbcObj {     // *(AnimParamObj+0xfbc)
    char  _pad0[0x2c0];
    void* sub;          // +0x2c0
};
struct Anim2c0Obj {     // *(AnimFbcObj+0x2c0)
    char  _pad0[8];
    void* sub;          // +0x08
};
struct Anim08Obj {      // *(Anim2c0Obj+0x08)
    char  _pad0[0x64];
    void* finder;       // +0x64  object with the +0xc lookup method
};
// ---- items of slice s00c0fa70 end

// ---- items of slice s00c104d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const float kPi;     // 0x0157174c
extern float gTwoPi;        // 0x0168d960 (dynamic-initialized)
struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
    Vector3(const Vector3& v) : x(v.x), y(v.y), z(v.z) {}
    Vector3& operator=(const Vector3& v) { x = v.x; y = v.y; z = v.z; return *this; }
    Vector3 Cross(const Vector3& b) const
    {
        return Vector3(y * b.z - z * b.y, z * b.x - x * b.z, x * b.y - y * b.x);
    }
    float Dot(const Vector3& b) const { return x * b.x + y * b.y + z * b.z; }
    float LengthSq() const { return x * x + y * y + z * z; }
    Vector3 operator+(const Vector3& b) const { return Vector3(x + b.x, y + b.y, z + b.z); }
    Vector3 operator-(const Vector3& b) const { return Vector3(x - b.x, y - b.y, z - b.z); }
    Vector3 operator*(float s) const { return Vector3(x * s, y * s, z * s); }
};
struct Quaternion {
    float x, y, z, w;
    Quaternion() {}
    Quaternion(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w) {}
};
inline Quaternion AxisAngle(const Vector3& axis, float angle)
{
    float h = angle * 0.5f;
    float s = sinf(h);
    float c = cosf(h);
    return Quaternion(axis.x * s, axis.y * s, axis.z * s, c);
}
// Clamp: the vetted SseClamp in sse_helpers.h

inline float SmoothStep(float v)
{
    v = SseClamp(v, 0.0f, 1.0f);
    return (3.0f - v * 2.0f) * v * v;
}
inline Vector3 NormalizeSafe(const Vector3& v)
{
    float inv = 1.0f / sqrtf(v.LengthSq() + 1e-8f);
    return v * inv;
}
inline Vector3 Reject(const Vector3& v, const Vector3& n)
{
    float d = v.Dot(n);
    return v - n * d;
}
Vector3 RotateVector(const Vector3& v, const Quaternion& q);                  // 0x0059aed0
float SignedAngle(const Vector3& a, const Vector3& b, const Vector3& axis);   // 0x0069b760
struct cPlanetModel {
    static cPlanetModel* Get();                       // 0x00b3d350
    Vector3 SurfaceNormal(const Vector3& position);   // 0x00b7e3b0
};
static inline float WrapAngleMod(float a)
{
    float x = (float)fmod((double)a, (double)gTwoPi);
    if (x > kPi)
        return x - gTwoPi;
    if (x < -kPi)
        return x + gTwoPi;
    return x;
}
// ---- items of slice s00c104d0 end

// ---- items of slice s00c19b60 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern uint32_t g_CooldownThreshold;                         // 0x015716d4
inline void* operator new(size_t, void* p) { return p; }
void* operator new(size_t size, const char* name, int flags, unsigned debugFlags,
                   const char* file, int line);                          // 0x00f473a0
struct Vector3_s00c1_9b60 { float x, y, z; };
struct RefObj {
    virtual int AddRef();       // 0x00
    virtual int Release();      // 0x04
};
template <class T> struct AutoRefCount {
    T* mpObject;
    AutoRefCount(T* p);                                                  // 0x00572660 (ret 4)
    __forceinline AutoRefCount(const AutoRefCount& x) : mpObject(x.mpObject) { if (mpObject) mpObject->AddRef(); }
    __forceinline ~AutoRefCount() { if (mpObject) mpObject->Release(); }
};
typedef AutoRefCount<RefObj> ObjRef;
struct ListNode {
    ListNode* mpNext;
    ListNode* mpPrev;
    ObjRef    mValue;
};
struct ListAnchor {
    ListNode* mpNext;
    ListNode* mpPrev;
};
struct CBase {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual bool IsProtected();                 // 0x2c
    uint8_t pad[0x4];
    void FUN_00c19940(int a);                   // 0x00c19940 (ret 4)
    uint8_t pad8[0xe84 - 8];
    uint8_t* mpOverride;                        // +0xe84
};
struct CLoco {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual const Vector3_s00c1_9b60* GetVector();         // 0x2c
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54();
    virtual bool IsLocomotive();                // 0x58
    void FUN_00c41d60(const Vector3_s00c1_9b60* v);        // 0x00c41d60 (ret 4)
    void FUN_00c446d0(const Vector3_s00c1_9b60* v, int a); // 0x00c446d0 (ret 8)
};
struct CTypeObj { virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
                  virtual void v10(); virtual void v14(); virtual void v18();
                  virtual int GetType(); };     // 0x1c
struct CAgent {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual CTypeObj* GetTypeObj();             // 0x20
};
struct CManager {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
    virtual void Post(uint32_t id, void* data, const Vector3_s00c1_9b60* v);   // 0x60
};
CManager* FUN_00b3d240();                                    // 0x00b3d240 (cdecl)
struct StateObj { uint8_t pad[0x2c]; int mState; };
StateObj* FUN_00b3d4d0();                                    // 0x00b3d4d0 (cdecl)
void* StarManager();                                         // 0x00b3d2a0 (cdecl)
bool FUN_00ba6650(uint32_t id);                              // 0x00ba6650 (cdecl)
uint32_t GetCurrentGameMode();                               // 0x00b5b800 (cdecl)
int FUN_00ac80d0(CBase* b, uint32_t id);                     // 0x00ac80d0 (cdecl)
void Vector3_Normalize(Vector3_s00c1_9b60* out, const Vector3_s00c1_9b60* in);     // 0x00436ce0 (cdecl)
RefObj* FUN_00c11690(uint32_t id, CBase* b, void* attacker); // 0x00c11690 (cdecl)
float FUN_00c0db80(float damage, CBase* b);                  // 0x00c0db80 (cdecl)
float FUN_00c161f0(float damage, CBase* b);                  // 0x00c161f0 (cdecl)
float FUN_00c16340(float damage, CBase* b);                  // 0x00c16340 (cdecl)
float FUN_00c0dcb0(float damage, CBase* b);                  // 0x00c0dcb0 (cdecl)
struct Profile {
    uint8_t  pad[0x648];
    int      mCount648;
    uint8_t  pad64c[0x660 - 0x64c];
    uint32_t mCount660;
    uint32_t mCount664;
    uint32_t mCount668;
};
class cCreatureCombatant {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
    virtual void v60(); virtual void v64();

    uint32_t pad04;             // (the vptr is 8 bytes wide: cGonzagoTimer alignment)
    uint32_t mFlags8;           // +0x08 (bit 9 tested)
    uint8_t  pad0c[0x578 - 0xc];
    Profile* mpProfile;         // +0x578
    uint8_t  pad57c[0x8dc - 0x57c];
    uint8_t* mpOverride;        // +0x8dc (byte +0x388)
    uint8_t  pad8e0[0x9d8 - 0x8e0];
    uint32_t mCooldown;         // +0x9d8
    ListAnchor mEffects;        // +0x9dc

    int  GetDamageState();                                                        // 0x008e7f80
    void TakeHit(float damage, uint32_t pid, int type, const Vector3_s00c1_9b60& dir, void* attacker);  // 0x00bfcdd0

    CBase*  Base()  { return (CBase*)((char*)this - 0x5a8); }
    CLoco*  Loco()  { return (CLoco*)((char*)this - 0x4e8); }
    CAgent* Agent() { return (CAgent*)((char*)this - 0x550); }

    void TakeDamage(float damage, uint32_t attackerPID, int damageType, const Vector3_s00c1_9b60& dir, void* attacker);   // 0x00c1a3c0
};
static __forceinline bool GetBit(uint32_t v, int n) { return ((v >> n) & 1) != 0; }
static __forceinline void PushEffect(ListAnchor* list, RefObj* obj)
{
    ObjRef tmp(obj);
    ListNode* n = (ListNode*)operator new(sizeof(ListNode), "Simulator", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
        0xd1);
    ::new ((void*)&n->mValue) ObjRef(tmp);
    n->mpNext = (ListNode*)list;
    n->mpPrev = list->mpPrev;
    list->mpPrev->mpNext = n;
    list->mpPrev = n;
}
// ---- items of slice s00c19b60 end

// ---- items of slice s00c1aad0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const float kLeapMargin;                                     // 0x01582fd8 (3.0)
extern const float kLeapSpeedDefault;                               // 0x01582fc0 (10.0)
struct Vector3_s00c1_aad0 { float x, y, z; };
void operator_delete__(void* p);                                    // 0x00f47380 (cdecl)
extern const Vector3_s00c1_aad0 kZeroVec;                                      // 0x0168d910
struct cLocomotionRequest {
    char* mpBegin;
    uint32_t pad[0x73 / 4];
    cLocomotionRequest();                                           // 0x00ac9850
    cLocomotionRequest(const Vector3_s00c1_aad0* pos, float a, float b);       // 0x00ad29d0 (ret 0xc)
    __forceinline ~cLocomotionRequest()
    {
        if (mpBegin && ((int*)mpBegin)[-1])
            operator_delete__(mpBegin);
    }
};
class Body {
public:
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
    virtual void s10();
    virtual const Vector3_s00c1_aad0* GetPos();                                // 0x2c
    virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15(); virtual void s16();
    virtual void s17(); virtual void s18(); virtual void s19(); virtual void s20(); virtual void s21();
    virtual void s22();
    virtual const Vector3_s00c1_aad0* GetForward(Vector3_s00c1_aad0* out);                // 0x5c
    virtual void s24(); virtual void s25(); virtual void s26();
    virtual const float* GetBounds(float* out);                     // 0x6c (6 floats: min, max)
    virtual void s28();
    virtual float GetRadius();                                      // 0x74
    virtual void s30(); virtual void s31(); virtual void s32(); virtual void s33(); virtual void s34();
    virtual void s35(); virtual void s36(); virtual void s37(); virtual void s38(); virtual void s39();
    virtual void s40(); virtual void s41(); virtual void s42(); virtual void s43(); virtual void s44();
    virtual void s45(); virtual void s46(); virtual void s47(); virtual void s48(); virtual void s49();
    virtual void s50(); virtual void s51(); virtual void s52(); virtual void s53(); virtual void s54();
    virtual void Submit(const cLocomotionRequest& req);             // 0xdc
    const Vector3_s00c1_aad0* GetVelocity();                                   // 0x00d20610 (lea eax,[ecx+0x1c8])
    void FUN_00c446d0(const Vector3_s00c1_aad0* v, bool flag);                 // 0x00c446d0 (ret 8)
};
struct SpeciesData {
    char pad0[0x548];
    float mLeapRangeAir;       // +0x548
    char pad54c[4];
    float mLeapRange;          // +0x550
    char pad554[0x610 - 0x554];
    uint32_t m610;             // +0x610
    char pad614[8];
    uint32_t m61c;             // +0x61c
    char pad620[0x698 - 0x620];
    uint32_t m698;             // +0x698
};
class PlanetModel {
public:
    float FUN_00b7e490();                                           // 0x00b7e490 (float in st0)
    float GetRadiusAt(const Vector3_s00c1_aad0* pos);                          // 0x00b7ef70 (ret 4)
    float FUN_00b82310(Vector3_s00c1_aad0* p);                                 // 0x00b82310 (ret 4)
};
PlanetModel* GetPlanetModel();                                      // 0x00b3d350
Vector3_s00c1_aad0* normalized_safe(Vector3_s00c1_aad0* out, const Vector3_s00c1_aad0* in);          // 0x00449c20 (cdecl, sret-style: out first, returns out)
class IQueryTarget {
public:
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
    virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14();
    virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
    virtual void s20(); virtual void s21(); virtual void s22();
    virtual void* Query(uint32_t id);                               // 0x5c
};
class cSPCreatureBase {
public:
    uint32_t vptr;
    char pad04[0xbc];
    Body mBody;                      // +0xc0
    char padc4[0x110 - 0xc4];
    uint32_t mFlags;                 // +0x110
    char pad114[0x137 - 0x114];
    bool mbLeaping;                  // +0x137
    char pad138[0x2b0 - 0x138];
    int mState;                      // +0x2b0
    char pad2b4[0xb20 - 0x2b4];
    SpeciesData* mpSpecies;          // +0xb20
    char padb24[0xbb0 - 0xb24];
    bool mbBB0;                      // +0xbb0
    char padbb1[0xe7c - 0xbb1];
    IQueryTarget* mpTargetHolder;    // +0xe7c

    float FUN_00c0ce80(int a, int b);                               // 0x00c0ce80 (ret 8)
    void FUN_00c15dc0(float f);                                     // 0x00c15dc0 (ret 4)
    void FUN_00c18b40(int arg);                                     // 0x00c18b40 (ret 4)
    void InterruptAnimation(uint32_t id, int a, int b);             // 0x00c12310 (ret 0xc)
    void FUN_00c1b020(int arg);
};
struct TargetCreature {
    char pad[0xc0];
    Body mBody;
};
// ---- items of slice s00c1aad0 end

// ---- items of slice s00c1d640 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float gChargeScale;                                              // 0x01572058 (10.0)
extern float gBoundScale;                                               // 0x01572054 (1.5)
extern float g_168d910;                                         // 0x0168D910
extern float g_168d914;                                         // 0x0168D914
extern float g_168d918;                                         // 0x0168D918
typedef unsigned int uint;
struct UIntVector {
    uint* mpBegin;
    uint* mpEnd;
    uint* mpCapacity;
    uint mAllocator[2];
    void DoInsertValue(uint* position, const uint& value);              // 0x004558a0 (ret 8)
    void push_back(const uint& v)
    {
        if (mpEnd < mpCapacity) {
            uint* p = mpEnd++;
            if (p)
                *p = v;
        } else {
            DoInsertValue(mpEnd, v);
        }
    }
    ~UIntVector()
    {
        if (mpBegin && ((int*)mpBegin)[-1])
            operator_delete__(mpBegin);
    }
};
struct AbilityMask {
    uint w[3];
    bool test(uint id) const
    {
        if (id >= 0x58)
            return false;
        return (w[id >> 5] & (1u << (id & 0x1f))) != 0;
    }
};
struct Ability {
    char pad0[8];
    uint id;                    // +0x08
    int mKind;                  // +0x0c
    char pad10[0x2c];
    float f3c;                  // +0x3c
    char pad40[0x44];
    float f84;                  // +0x84
    char pad88[0x14];
    float f9c;                  // +0x9c
    char pada0[8];
    float fa8;                  // +0xa8
    char padac[0x48];
    float ff4;                  // +0xf4
    char padf8[8];
    float f100_pad;
    float f104;                 // +0x104  (cost)
    char pad108[0xc];
    unsigned char mbBusy;       // +0x114
    char pad115[0xb];
    int m120;                   // +0x120
    float GetBound(bool upper); // 0x004d3d70 (ret 4)
};
struct Entry { float f0; float f4; float f8; float fc; };               // 16-byte per-ability state
struct TypeObj {
virtual void s0();
virtual void s1();
virtual void s2();
virtual void s3();
virtual void s4();
virtual void s5();
virtual void s6();
virtual void s7();
    virtual uint GetType();                                      // slot 8 (+0x20)
};
struct TypeHolder {
virtual void s0();
virtual void s1();
virtual void s2();
    virtual TypeObj* Get();                                             // slot 3 (+0xc)
};
struct Body_s00c1_d640 {
virtual void s0();
virtual void s1();
virtual void s2();
virtual void s3();
virtual void s4();
virtual void s5();
virtual void s6();
virtual void s7();
virtual void s8();
virtual void s9();
    virtual void s10();
    virtual const void* GetPos();                                       // slot 11 (+0x2c)
virtual void s12();
virtual void s13();
virtual void s14();
virtual void s15();
virtual void s16();
virtual void s17();
virtual void s18();
virtual void s19();
virtual void s20();
virtual void s21();
virtual void s22();
virtual void s23();
virtual void s24();
virtual void s25();
virtual void s26();
virtual void s27();
virtual void s28();
    virtual float GetRadius();                                          // slot 29 (+0x74)
    const void* GetBodyPos();                                           // 0x00c42de0
};
float DistanceBetweenBodies(const void* posA, float radiusA, const void* posB, float radiusB, bool clamp0);  // 0x00d99a60
struct Creature {
virtual void s0();
virtual void s1();
virtual void s2();
virtual void s3();
virtual void s4();
virtual void s5();
virtual void s6();
virtual void s7();
virtual void s8();
virtual void s9();
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
virtual void s20();
virtual void s21();
virtual void s22();
    virtual Creature* Query(uint id);                                   // slot 23 (+0x5c)
virtual void s24();
virtual void s25();
virtual void s26();
virtual void s27();
virtual void s28();
virtual void s29();
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
virtual void s40();
virtual void s41();
virtual void s42();
virtual void s43();
    virtual uint GetAbilityCount();                                     // slot 44 (+0xb0)
    virtual Ability* GetAbility(uint index);                            // slot 45 (+0xb4)
    char pad04[0xbc];
    Body_s00c1_d640 mBody;                                                         // +0xc0 (secondary base with vptr)
    char padc4[0xa94];
    uint mFlags;                                                        // +0xb58
    char padb5c[0x54];
    unsigned char mbNoBonus;                                            // +0xbb0
    char padbb1[0x77];
    Entry* mpEntries;                                                   // +0xc28
    char padc2c[0x22c];
    float mEnergy;                                                      // +0xe58
    char pade5c[0x20];
    TypeHolder* mpTypeHolder;                                           // +0xe7c
    char pade80[0xc];
    uint mActiveAbility;                                                // +0xe8c
    char pade90[0x7e0];
    uint mCooldownCount;                                                // +0x1670

    bool IsUpper() const { return (mFlags >> 9) & 1; }
    float F00c0ce80(int a, int b);                                      // 0x00c0ce80 (ret 8)
    uint ChooseAbility(AbilityMask* mask, Creature* target, float dist, bool flag);   // 0x00c1de20
};
float GetScale(int zero, Creature* c);                                  // 0x00d38a30 (cdecl)
const uint kCombatantTypeId = 0x018eb45e;
struct Vec3_s00c1_d640 {
    float x, y, z;
};
struct Quat {
    float x, y, z, w;
};
struct PartData {
    char  mPad000[0x138];
    float mRadiusX;                 // +0x138
    float mRadiusY;                 // +0x13c
    float mRadiusZ;                 // +0x140
    char  mPad144[0x428 - 0x144];
    void* mpSound;                  // +0x428 (0 when the part is silent)
};
struct BodyPart_s00c1_d640 {
    PartData* mpData;               // +0x00
    char      mPad04[0x10 - 0x04];
    Vec3_s00c1_d640      mOffset;              // +0x10 (part-local emitter offset)
    char      mPad1c[0x2bc - 0x1c];
};
struct CreatureModel {
    char  mPad000[0x18];
    Vec3_s00c1_d640  mPosition;                // +0x18
    char  mPad024[0x3c - 0x24];
    Quat  mRotation;                // +0x3c
    char  mPad04c[0x70 - 0x4c];
    float mScale;                   // +0x70
    char  mPad074[0x2e4 - 0x74];
    BodyPart_s00c1_d640* mpParts;              // +0x2e4
};
struct AnimCreature {
    char          mPad000[0x17c];
    CreatureModel* mpModel;         // +0x17c
};
struct SoundNode {
    SoundNode* mpLeft;              // +0x00
    SoundNode* mpRight;             // +0x04
    SoundNode* mpParent;            // +0x08
    uint       mColor;              // +0x0c
    uint       mKey;                // +0x10 (creature sound id)
    uint       mHandle;             // +0x14 (audio-system handle)
    int        mPart;               // +0x18 (body-part index)
};
struct SoundMapHead {
    SoundNode* mpLeft;              // +0x00
    SoundNode* mpRight;             // +0x04
    SoundNode* mpParent;            // +0x08 (root)
    uint       mColor;              // +0x0c
};
struct UIntVec {
    uint* mpBegin;                  // +0x00
    uint* mpEnd;                    // +0x04
    uint* mpCapacity;               // +0x08
    void DoInsertValue(uint* position, const uint& value);   // 0x004558A0
    void push_back(const uint& v)
    {
        if (mpEnd < mpCapacity) {
            uint* p = mpEnd++;
            if (p)
                *p = v;
        } else {
            DoInsertValue(mpEnd, v);
        }
    }
};
class AudioSystem {
public:
virtual void s00();
virtual void s04();
virtual void s08();
virtual void s0c();
virtual void s10();
virtual void s14();
virtual void s18();
virtual void s1c();
    virtual uint s20();             // +0x20
    virtual uint s24();             // +0x24
virtual void s28();
virtual void s2c();
virtual void s30();
virtual void s34();
    virtual void s38(uint key);                         // +0x38
    virtual void s3c(uint key, float value);           // +0x3c
    virtual void s40(uint key, uint value);            // +0x40
    virtual void s44(uint key, const char* name, uint arg); // +0x44
virtual void s48();
virtual void s4c();
virtual void s50();
virtual void s54();
    virtual void s58();             // +0x58 (commit/play)
};
AudioSystem* GetSystemAT();                                     // 0x00A206F0 EA::Audio::GetSystemAT
uint QueryCreatureBodyParts(void* creature, int mode, int* parts, int maxParts); // 0x00C17420
void* SimAlloc(unsigned int size, const char* name, int a, int b,
               const char* file, int line);                     // 0x00F473A0 operator new
void RBTreeInsert(void* node, void* parent, void* head, int side); // 0x009216A0 eastl::RBTreeInsert
bool __fastcall Flag388(void* self);                            // 0x00C0C0E0 (thiscall; ecx = self)
#define VSLOT(n) virtual void vs##n()
class cSPCreatureBase_s00c1_d640 {
public:
    // Slots 0x00..0xD4 are not used here; they only preserve the primary
    // vtable offset of the sound-flag query at +0xD8.
VSLOT(00);
VSLOT(04);
VSLOT(08);
VSLOT(0c);
VSLOT(10);
VSLOT(14);
VSLOT(18);
VSLOT(1c);
VSLOT(20);
VSLOT(24);
VSLOT(28);
VSLOT(2c);
VSLOT(30);
VSLOT(34);
VSLOT(38);
VSLOT(3c);
VSLOT(40);
VSLOT(44);
VSLOT(48);
VSLOT(4c);
VSLOT(50);
VSLOT(54);
VSLOT(58);
VSLOT(5c);
VSLOT(60);
VSLOT(64);
VSLOT(68);
VSLOT(6c);
VSLOT(70);
VSLOT(74);
VSLOT(78);
VSLOT(7c);
VSLOT(80);
VSLOT(84);
VSLOT(88);
VSLOT(8c);
VSLOT(90);
VSLOT(94);
VSLOT(98);
VSLOT(9c);
VSLOT(a0);
VSLOT(a4);
VSLOT(a8);
VSLOT(ac);
VSLOT(b0);
VSLOT(b4);
VSLOT(b8);
VSLOT(bc);
VSLOT(c0);
VSLOT(c4);
VSLOT(c8);
VSLOT(cc);
VSLOT(d0);
VSLOT(d4);
    virtual uint vsD8();            // +0xD8

    char       mPad004[0xb34 - 0x04];
    int        mFieldB34;           // +0xb34
    char       mPadB38[0xb54 - 0xb38];
    AnimCreature* mpAnim;           // +0xb54
    uint       mFlagsB58;           // +0xb58
    char       mPadB5c[0xe0c - 0xb5c];
    SoundMapHead mSoundMap;         // +0xe0c
    uint       mSoundMapCount;      // +0xe1c
    char       mPadE20[0xe24 - 0xe20];
    UIntVec    mSoundIds;           // +0xe24
    char       mPadE30[0xf94 - 0xe30];
    uint       mSoundCounter;       // +0xf94

    uint FUN_00c1d640(const char* name, int mode, uint id);
    bool StartIndependentSound(const char* name, const Vec3_s00c1_d640* pos, UIntVec* out);  // 0x00c1db40 (cSPCreatureBase::StartIndependentSound)
    uint CallVd8() { return vsD8(); }
    bool Flag388() { return ::Flag388(this); }
};
static inline Vec3_s00c1_d640 RotateOffset(const Quat& q, const Vec3_s00c1_d640& v)
{
    float xx = q.x * q.x;
    float yy = q.y * q.y;
    float zz = q.z * q.z;
    float xy = q.x * q.y;
    float xz = q.x * q.z;
    float yz = q.y * q.z;
    float wx = q.w * q.x;
    float wy = q.w * q.y;
    float wz = q.w * q.z;
    Vec3_s00c1_d640 r;
    r.x = (1.0f - 2.0f * (yy + zz)) * v.x
        + 2.0f * (xy - wz) * v.y
        + 2.0f * (xz + wy) * v.z;
    r.y = 2.0f * (xy + wz) * v.x
        + (1.0f - 2.0f * (xx + zz)) * v.y
        + 2.0f * (yz - wx) * v.z;
    r.z = 2.0f * (xz - wy) * v.x
        + 2.0f * (yz + wx) * v.y
        + (1.0f - 2.0f * (xx + yy)) * v.z;
    return r;
}
// ---- items of slice s00c1d640 end

// ---- items of slice s01335000 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace eastl {
 struct string8_s0133_5000; 
}
typedef eastl::string8_s0133_5000 string8_s0133_5000;
namespace Simulator {
class ISerializerReadStream;
}
namespace Simulator {
class ISerializerWriteStream;
}
namespace Simulator {
struct Attribute;
}
namespace Simulator {
typedef bool  (*ReadFunction_t)(ISerializerReadStream*, void*);
}
namespace Simulator {
typedef bool  (*WriteFunction_t)(ISerializerWriteStream*, void*);
}
namespace Simulator {
typedef void  (*ReadTextFunction_t)(const string8_s0133_5000&, void*);
}
namespace Simulator {
typedef void  (*WriteTextFunction_t)(char*, void*);
}
namespace Simulator {
typedef bool  (*ValidateFunction_t)();
}
namespace Simulator {
typedef bool  (*ToXmlFunction_t)(void*, const char*, int);
}
namespace Simulator {
typedef void* (*OffsetFunction_t)(Attribute*);
}
namespace Simulator {
typedef void  (*SetDefaultFunction_t)(Attribute*);
}
namespace Simulator {
void* DefaultOffset(Attribute* pAttr);   // 0x00692ca0: pAttr->pCurrentObject + pAttr->offset
}
namespace Simulator {
struct Attribute
{
    Attribute(const char* pName, uint32_t nID, uint32_t nOffset,
              ReadFunction_t pRead, WriteFunction_t pWrite,
              ReadTextFunction_t pReadText, WriteTextFunction_t pWriteText,
              ValidateFunction_t pValidate, ToXmlFunction_t pToXml,
              SetDefaultFunction_t pSetDefault = 0)
    {
        name = pName;
        id = nID;
        pCurrentObject = 0;
        setDefaultFunction = pSetDefault;
        offsetFunction = DefaultOffset;
        readFunction = pRead;
        writeFunction = pWrite;
        readTextFunction = pReadText;
        writeTextFunction = pWriteText;
        validateFunction = pValidate;
        toXmlFunction = pToXml;
        offset = nOffset;
    }

    /* 00h */ const char* name;
    /* 04h */ uint32_t id;
    /* 08h */ uint32_t offset;
    /* 0Ch */ int field_0C;   // not initialized
    /* 10h */ int field_10;   // not initialized
    /* 14h */ int field_14;   // not initialized
    /* 18h */ void* pCurrentObject;
    /* 1Ch */ SetDefaultFunction_t setDefaultFunction;
    /* 20h */ OffsetFunction_t offsetFunction;
    /* 24h */ ReadFunction_t readFunction;
    /* 28h */ WriteFunction_t writeFunction;
    /* 2Ch */ ReadTextFunction_t readTextFunction;
    /* 30h */ WriteTextFunction_t writeTextFunction;
    /* 34h */ ValidateFunction_t validateFunction;
    /* 38h */ ToXmlFunction_t toXmlFunction;
};
}
namespace Simulator {
bool Read_00572810(ISerializerReadStream* pStream, void* pData);  // 0x00572810
}
namespace Simulator {
bool Read_00ac8750(ISerializerReadStream* pStream, void* pData);  // 0x00ac8750
}
namespace Simulator {
bool Read_00ac87c0(ISerializerReadStream* pStream, void* pData);  // 0x00ac87c0
}
namespace Simulator {
bool Read_00ae3430(ISerializerReadStream* pStream, void* pData);  // 0x00ae3430
}
namespace Simulator {
bool Read_00ae3470(ISerializerReadStream* pStream, void* pData);  // 0x00ae3470
}
namespace Simulator {
bool Read_00aff840(ISerializerReadStream* pStream, void* pData);  // 0x00aff840
}
namespace Simulator {
bool Read_00b02540(ISerializerReadStream* pStream, void* pData);  // 0x00b02540
}
namespace Simulator {
bool Read_00c143c0(ISerializerReadStream* pStream, void* pData);  // 0x00c143c0
}
namespace Simulator {
bool Read_00c1b8c0(ISerializerReadStream* pStream, void* pData);  // 0x00c1b8c0
}
namespace Simulator {
bool Read_00c21260(ISerializerReadStream* pStream, void* pData);  // 0x00c21260
}
namespace Simulator {
bool Read_00c7e9f0(ISerializerReadStream* pStream, void* pData);  // 0x00c7e9f0
}
namespace Simulator {
bool Write_00572840(ISerializerWriteStream* pStream, void* pData);  // 0x00572840
}
namespace Simulator {
bool Write_00ac8780(ISerializerWriteStream* pStream, void* pData);  // 0x00ac8780
}
namespace Simulator {
bool Write_00ac87f0(ISerializerWriteStream* pStream, void* pData);  // 0x00ac87f0
}
namespace Simulator {
bool Write_00ac88f0(ISerializerWriteStream* pStream, void* pData);  // 0x00ac88f0
}
namespace Simulator {
bool Write_00ae3450(ISerializerWriteStream* pStream, void* pData);  // 0x00ae3450
}
namespace Simulator {
bool Write_00ae3490(ISerializerWriteStream* pStream, void* pData);  // 0x00ae3490
}
namespace Simulator {
bool Write_00aff870(ISerializerWriteStream* pStream, void* pData);  // 0x00aff870
}
namespace Simulator {
bool Write_00bca960(ISerializerWriteStream* pStream, void* pData);  // 0x00bca960
}
namespace Simulator {
bool Write_00c0fba0(ISerializerWriteStream* pStream, void* pData);  // 0x00c0fba0
}
namespace Simulator {
bool Write_00c143e0(ISerializerWriteStream* pStream, void* pData);  // 0x00c143e0
}
namespace Simulator {
bool Write_00c15f60(ISerializerWriteStream* pStream, void* pData);  // 0x00c15f60
}
namespace Simulator {
bool Write_00cd44e0(ISerializerWriteStream* pStream, void* pData);  // 0x00cd44e0
}
namespace Simulator {
void ReadText_00692fd0(const string8_s0133_5000& text, void* pData);  // 0x00692fd0
}
namespace Simulator {
void ReadText_00692ff0(const string8_s0133_5000& text, void* pData);  // 0x00692ff0
}
namespace Simulator {
void ReadText_00693090(const string8_s0133_5000& text, void* pData);  // 0x00693090
}
namespace Simulator {
void ReadText_006930b0(const string8_s0133_5000& text, void* pData);  // 0x006930b0
}
namespace Simulator {
void ReadText_00693150(const string8_s0133_5000& text, void* pData);  // 0x00693150
}
namespace Simulator {
void ReadText_00694c80(const string8_s0133_5000& text, void* pData);  // 0x00694c80
}
namespace Simulator {
void ReadText_00c2e4e0(const string8_s0133_5000& text, void* pData);  // 0x00c2e4e0
}
namespace Simulator {
void WriteText_00692fb0(char* pBuffer, void* pData);  // 0x00692fb0
}
namespace Simulator {
void WriteText_00694c10(char* pBuffer, void* pData);  // 0x00694c10
}
namespace Simulator {
void WriteText_00694ec0(char* pBuffer, void* pData);  // 0x00694ec0
}
namespace Simulator {
void WriteText_00694ee0(char* pBuffer, void* pData);  // 0x00694ee0
}
namespace Simulator {
void WriteText_00694f00(char* pBuffer, void* pData);  // 0x00694f00
}
namespace Simulator {
void WriteText_00694fa0(char* pBuffer, void* pData);  // 0x00694fa0
}
namespace Simulator {
void WriteText_00694fc0(char* pBuffer, void* pData);  // 0x00694fc0
}
namespace Simulator {
void WriteText_00695080(char* pBuffer, void* pData);  // 0x00695080
}
namespace Simulator {
bool Validate_00ae3310();  // 0x00ae3310
}
namespace Simulator {
bool Validate_00b1fbf0();  // 0x00b1fbf0
}
namespace Simulator {
bool Validate_00b6f550();  // 0x00b6f550
}
namespace Simulator {
bool Validate_00c0fc10();  // 0x00c0fc10
}
namespace Simulator {
bool ToXml_0057cde0(void* pData, const char* pName, int depth);  // 0x0057cde0
}
namespace Simulator {
bool ToXml_0057ce00(void* pData, const char* pName, int depth);  // 0x0057ce00
}
namespace Simulator {
bool ToXml_00595a70(void* pData, const char* pName, int depth);  // 0x00595a70
}
namespace Simulator {
bool ToXml_00675ca0(void* pData, const char* pName, int depth);  // 0x00675ca0
}
namespace Simulator {
bool ToXml_00ac8050(void* pData, const char* pName, int depth);  // 0x00ac8050
}
namespace Simulator {
bool ToXml_00acbb80(void* pData, const char* pName, int depth);  // 0x00acbb80
}
namespace Simulator {
bool ToXml_00acbbc0(void* pData, const char* pName, int depth);  // 0x00acbbc0
}
namespace Simulator {
bool ToXml_00ae5720(void* pData, const char* pName, int depth);  // 0x00ae5720
}
namespace Simulator {
bool ToXml_00c19b60(void* pData, const char* pName, int depth);  // 0x00c19b60
}
namespace Simulator {
bool ToXml_00ca8710(void* pData, const char* pName, int depth);  // 0x00ca8710
}
namespace Simulator {
struct AttrStorage { char data[sizeof(Attribute)]; };
}
namespace Simulator {
AttrStorage cCreatureBase_sAttributes[35];   // 0x01571798
}
// ---- items of slice s01335000 end

// ---- items of slice s00c0acd0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float g_146a32c;         // FLT_MAX
extern float g_150c8e4, g_150c8e8, g_150c8ec, g_150c8f0;
extern float g_150c8f4, g_150c8f8, g_150c8fc;
float g_150c88c = 1.25f;                    // 0x0150c88c
float g_150c888 = 0.25f;                    // 0x0150c888
extern float g_1687a00, g_1687a04, g_1687a0c, g_1687a10, g_1687a14;
extern float g_1687a2c, g_1687a30, g_169e288;
extern int   g_168d900;
extern int   g_168d9bc, g_168da00, g_168da44, g_168da88, g_168dacc, g_168db10;
extern "C" float __fastcall FUN_00bfc490(void*);
typedef unsigned char uchar;
typedef unsigned long long uint64;
extern uchar g_168db6c;
struct AllocRec { char pad[0x40]; };
extern AllocRec g_168d998;
namespace EA {
namespace Random {
class RandomLinearCongruential_s00c0_acd0 {
 public:
  unsigned int RandomUint32Uniform(unsigned int);  // 0x00a68fb0 (EA::Random::RandomLinearCongruential::RandomUint32Uniform)
  float RandomDoubleUniform();  // 0x009360d0 (EA::Random::RandomLinearCongruential::RandomDoubleUniform)
};
}
}
#define GRAND ((EA::Random::RandomLinearCongruential_s00c0_acd0*)g_1601760)
bool __cdecl SP_GetPropertyAsUint32Array(unsigned int prop, unsigned int arg,
                                         int* count, int** data);
int  __cdecl SP_GetCurrentGameMode_s00c0_acd0();
struct AgentOrderManager {
  void __thiscall Tick(float);
  void __thiscall Activate(int, int, void*, float, void*, void*);
};
struct ModifiersCtorHelper {
  void* __thiscall Exist(AllocRec*);
};
void* __cdecl operator new(size_t, const char*, int, int, int, int);
bool __cdecl WriteUint32(void* stream, const void* data, int count, int flags);
bool __cdecl WriteUint64(void* stream, const void* data, int count, int flags);
bool __cdecl ReadUint64(void* stream, void* data, int count, int flags);
bool __cdecl ReadInt32(void* stream, void* data, int count, int flags);
bool __cdecl ReadBool(void* stream, void* data);
void __cdecl StreamWriteBool(void* stream, const void* data, int count);
namespace Simulator {
struct SpeciesData_s00c0_acd0 {
  char pad0[0x58c];
  float mAge;                               // +0x58c
  char pad1[0x608 - 0x590];
  unsigned int m608;
  unsigned int m60c;
};
}
namespace Simulator {
struct cCreatureBase {
  char pad000[0xbd];
  bool mb_bd;                               // +0xbd

  char pad0be[0x110 - 0xbe];
  unsigned int mFlags;                      // +0x110

  char pad114[0x135 - 0x114];
  bool mb_135;                              // +0x135
  char pad136[1];
  bool mb_137;                              // +0x137

  char pad138[0x2b0 - 0x138];
  int mState;                               // +0x2b0

  char pad2b4[0xb20 - 0x2b4];
  SpeciesData_s00c0_acd0* mpSpecies;                   // +0xb20
  char padb24[4];
  float mPosX;                              // +0xb28
  float mPosY;                              // +0xb2c
  float mPosZ;                              // +0xb30
  int m_b34;                                // +0xb34

  char padb38[0xb48 - 0xb38];
  AgentOrderManager* mpOrders;              // +0xb48

  char padb4c[0xb54 - 0xb4c];
  void* mpAnimCreature;                     // +0xb54
  unsigned int mGeneralFlags;               // +0xb58
  char padb5c[0xb5e - 0xb5c];
  bool mbDead;                              // +0xb5e
  char padb5f[1];
  bool mbUpdateInteractionEffect;           // +0xb60
  char padb61[0xb63 - 0xb61];
  bool mb_b63;                              // +0xb63
  char padb64[0xb67 - 0xb64];
  bool mbCasted;                            // +0xb67
  char padb68[0xb70 - 0xb68];
  int mAnimTargetCounter;                   // +0xb70

  char padb74[0xb80 - 0xb74];
  float m_b80;                              // +0xb80
  char padb84[0xb88 - 0xb84];
  int mStrengthRating;                      // +0xb88
  int m_b8c;                                // +0xb8c

  char padb90[0xbb8 - 0xb90];
  float m_bB8;                              // +0xbb8
  float m_bBC;                              // +0xbbc

  char padbc0[0xcc4 - 0xbc0];
  unsigned int mLastInteractionEffect;      // +0xcc4

  char padcc8[0xe84 - 0xcc8];
  void* mp_e84;                             // +0xe84

  char pade88[0xeac - 0xe88];
  int m_eac;                                // +0xeac

  char padeb0[0xf80 - 0xeb0];
  int m_f80;                                // +0xf80

  char padf84[0x1624 - 0xf84];
  void* mp_1624;                            // +0x1624

  char pad1628[0x1670 - 0x1628];
  unsigned int m_1670;                      // +0x1670
  void* mp_1674;                            // +0x1674

  char pad1678[0x1698 - 0x1678];
  void* mp_1698;                            // +0x1698
  float m_169c;                             // +0x169c

  void Update(unsigned int);
  void SetLastInteractionEffect(unsigned int);
  bool ForgetUpdateInteractionEffect();
  void func90h();
  bool IsHungry() const;
  bool IsTired() const;
  bool IsSick() const;
  bool CanBeAttacked(void*) const;
  bool ShouldFlee(void*) const;
  bool ShouldFight(void*) const;
  bool IsIdle(void*) const;
  float GetSpeedScalar() const;
  bool NeedsFood() const;
  void InitOrders();
  int  QueryInterface(unsigned int);
  void SetTimeFromGlobal();
  bool HasAnyCooldown() const;
  bool HasOtherCooldown() const;
  bool IsBusy(void*) const;
  bool IsAttacking(void*) const;
  bool IsStunned(void*) const;
  bool IsDoingAction(void*) const;
  int  CompareTimer(cCreatureBase*);
  int  Query(unsigned int);
  bool CheckTargetA(void*);
  bool CheckTargetB(void*);
  bool CheckTargetC(void*);
  bool CheckTargetD(void*);
  int  GetStrengthRating() const;
  int  TimerDelta(cCreatureBase*);
  void ClampHunger(float);
  void SetHunger(float);
  void ResetHunger();
  void TickCooldowns();
};
}
typedef Simulator::cCreatureBase CB;
typedef Simulator::SpeciesData_s00c0_acd0 SpeciesData_s00c0_acd0;
struct TuningObj {
  uint32_t pad0[2];                        // +0 (GetAt is a member; data starts at +8)
  int m8;                                  // +8 (switch selects the animation set)
  void* __thiscall GetAt(unsigned int);
};
struct F_abf740 { int __thiscall f(unsigned int); };
struct F_cee250 { int __thiscall f(unsigned int); };
struct F_c41d00 { int __thiscall f(unsigned int); };
struct F_ac0320 { int __thiscall f(unsigned int); };
struct F_b18460 { int __thiscall f(unsigned int); };
struct F_bfc380 { int __thiscall f(unsigned int); };
struct F_c7d050 { int __thiscall f(unsigned int); };
struct F_c884f0 { int __thiscall f(unsigned int); };
struct F_c35d20 { bool __thiscall f(); };
struct F_c35d40 { bool __thiscall f(); };
struct F_ba3f90 { int __thiscall f(void*, CB*, unsigned int); };
struct F_b48770 { void __thiscall f(CB*, int); };
int  __fastcall FUN_00b3d4c0(CB*);
void* __fastcall FUN_00b3d310(CB*);
bool __fastcall FUN_00c0bb90(CB*);
// ---- items of slice s00c0acd0 end

// ---- items of slice s00c0eae0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef int intptr_t;
#define nullptr 0
float sqrtf(float fValue);
#define __builtin_sqrtf sqrtf
struct Vec3 {
    float mX;
    float mY;
    float mZ;
};
class IRefCounted {
public:
    virtual void AddRef();          // 0x00
    virtual void Release();         // 0x04
    virtual void v08();
    virtual void* Query();   // 0x0c
    virtual void v10();
    virtual uint32_t GetPoliticalID();        // 0x14
    virtual void v18();
    virtual void v1c();
    virtual uint32_t v20();
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
    virtual void v58(int a, int b, int c, int d);
    virtual void* QueryTarget(const void* pType);   // 0x5c
};
class cSpatialObject {
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
    virtual Vec3* GetPosition();          // 0x2c
    virtual Vec3* GetDirection();         // 0x30
    virtual bool IsVisible();             // 0x58
};
class cGameData : public IRefCounted {
public:
    uint8_t mPad60[0x1c];
};
class cCombatant : public cGameData {
public:
    uint8_t mPad7c[0x20];
};
class AnimatedCreature {
public:
    uint8_t mPad00[0x88];           // 0x00
    uint32_t mFlags;                // 0x88
    uint8_t mPad8c[0xc8];           // 0x8c
    uint32_t mState;                // 0x154
    Vec3 mOrientation;              // 0x158
    Vec3 mPosition;                 // 0x164
    uint8_t mPad170[0x10];
    void __thiscall SetVisible(bool bVisible);   // 0x00a02b00
};
struct cCombatantSlot {
    int mKey;                       // 0x00
    int mSecondaryKey;              // 0x04
    uint8_t mPad08[0x18];           // 0x08
    cCombatant* mpCombatant;        // 0x20
};
class RandomLinearCongruential {
public:
    uint32_t RandomUint32Uniform(int nRange);
};
RandomLinearCongruential RandomGet();
void CreatureUpdateTransform(const Vec3* pPosition, int bFlag);
Vec3* RotateVectorAround(Vec3* pOut, const Vec3* pVector, const Vec3* pAxis);
bool IsVectorValid(const Vec3* pVector);
void* GetCurrentGameMode_s00c0_eae0();
extern uint8_t gGameModeTribe;
extern uint8_t gGameModeCity;
void CreatureAddRelation(cCombatant* pTarget);
uint32_t GetOwnPoliticalID(cSpatialObject* pObject);
void CreaturePlayAttackAnimation();
bool IsAnimationQueuedOrCurrent(void* pCreature);
void HideCreature(bool bHide);
void CreatureMoveStep(const Vec3* pDelta, int bFlag);
bool TraceTerrain(const Vec3* pFrom, const Vec3* pDirection, void* pWorld, float* pOut, int a, int b);
class Simulator_cCreatureBase : public cSpatialObject {
public:
    uint8_t mPad04[0xbc];           // 0x04
    uint8_t mLocomotiveFlags;       // 0xc0
    uint8_t mPadC1[0x76];           // 0xc1
    uint8_t mOrientationValid;      // 0x137
    uint8_t mPad138[0x9d8];         // 0x138
    uint32_t mFlags;                // 0xb10
    uint8_t mPadB14[0x04];          // 0xb14
    cCombatant* mpCombatantTarget;  // 0xb18
    int mIntentionTowardsTarget;    // 0xb1c
    void* mpSteeringModel;          // 0xb20
    uint8_t mPadB24[0x30];          // 0xb24
    AnimatedCreature* mpAnimatedCreature;   // 0xb54
    uint32_t mSteeringFlags;        // 0xb58
    uint8_t mTargetFlag;            // 0xb5c
    uint8_t mPadB5D[0x2e3];         // 0xb5d .. 0xe40
    cCombatantSlot* mpSlotsBegin;   // 0xe40
    cCombatantSlot* mpSlotsEnd;     // 0xe44
    uint8_t mPadE48[0x14];          // 0xe48 .. 0xe5c
    IRefCounted* mpSenseObject;     // 0xe5c
    uint8_t mPadE60[0x03];          // 0xe60
    uint8_t mPathValid;             // 0xe63
    uint32_t mSteeringTimer;        // 0xe64
    uint8_t mPadE68[0x14];          // 0xe68
    IRefCounted* mpSteeringTarget;  // 0xe7c
    uint8_t mPadE80[0x1c0];         // 0xe80

    void SteerTowards(const Vec3* pTarget, int nDelta);        // 0x00c0eae0
    void SetCreatureTarget(cCombatant* pTarget, bool bFlag, int nIntention);  // 0x00c0ed60
    void* GetTargetAsCreature();                                // 0x00c0ee70
    void* ApplyCombatTarget();                                  // 0x00c0ee90
    void UpdateSteering(int nDelta, float fAmount);              // 0x00c0eec0
    void Hide();                                                // 0x00c0f280
    void Show();                                                // 0x00c0f2b0
    bool TraceTo(const Vec3* pFrom, const Vec3* pTo, Vec3* pOut);  // 0x00c0f2e0
    void ResetCombatants();                                     // 0x00c0f490
    bool IsSlotEmpty(uint32_t nIndex);                          // 0x00c0f510
    int CountValid();                                           // 0x00c0f570
    bool IsFull();                                              // 0x00c0f5f0
    uint32_t FindFirstEmpty();                                  // 0x00c0f620
    uint32_t FindRandomEmpty();                                 // 0x00c0f6b0
    uint32_t FindFirstValid();                                  // 0x00c0f780
    uint32_t FindNextValid(int nAfter);                         // 0x00c0f810
    cCombatant* GetAt(uint32_t nIndex);                         // 0x00c0f8a0
    uint32_t FindByCombatant(int nCombatant);                   // 0x00c0f8f0
    uint32_t FindByKey(int nKey);                               // 0x00c0f960
    cCombatantSlot* FindSlotByKey(int nKey, uint32_t* pIndex);  // 0x00c0f9b0
    cCombatantSlot* FindSlotByCombatant(int nCombatant, uint32_t* pIndex);  // 0x00c0fa10
};
// ---- items of slice s00c0eae0 end

// ---- items of slice s00c13340 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern char    gFlockEnabled;   // 0x0169e381
extern float   gFlockScale;     // 0x0169e384
extern float   gFlockX;         // 0x0169e388
extern float   gFlockY;         // 0x0169e38c
extern float   gFlockZ;         // 0x0169e390
extern float   gHalfNeg;        // 0x01471064 (0.5f used as *0.5)
extern float   gHoverMul;       // 0x01571730
extern float   gAirMul;         // 0x01582fbc
extern float   gFallbackRange;  // 0x01582f60
extern float   gEps146a330;     // 0x0146a330 (1.5e-5)
extern float   gZero1485378;    // 0x01485378 (0.0f cmp)
extern float   gOne1485720;     // 0x01485720 (1.0f)
extern float   gProp3f14;       // 0x013ec4b8 (1e-8 squared-length bias)
extern float   gHoverSavedX;    // 0x0169e3b4
extern float   gHoverSavedY;    // 0x0169e3b8
extern float   gHoverSavedZ;    // 0x0169e3bc
#define PVCAT2(a, b) a##b
#define PVCAT(a, b) PVCAT2(a, b)
#define PV virtual void PVCAT(pv_, __COUNTER__)();
#define PV2 PV PV
#define PV4 PV2 PV2
#define PV8 PV4 PV4
struct Vector3_s00c1_3340 {
    float x, y, z;
    Vector3_s00c1_3340() {}
    Vector3_s00c1_3340(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
    Vector3_s00c1_3340(const Vector3_s00c1_3340& v) : x(v.x), y(v.y), z(v.z) {}
    Vector3_s00c1_3340& operator=(const Vector3_s00c1_3340& v) { x = v.x; y = v.y; z = v.z; return *this; }
    float Dot(const Vector3_s00c1_3340& b) const { return x * b.x + y * b.y + z * b.z; }
    float LengthSq() const { return x * x + y * y + z * z; }
    Vector3_s00c1_3340 operator+(const Vector3_s00c1_3340& b) const { return Vector3_s00c1_3340(x + b.x, y + b.y, z + b.z); }
    Vector3_s00c1_3340 operator-(const Vector3_s00c1_3340& b) const { return Vector3_s00c1_3340(x - b.x, y - b.y, z - b.z); }
    Vector3_s00c1_3340 operator*(float s) const { return Vector3_s00c1_3340(x * s, y * s, z * s); }
};
inline Vector3_s00c1_3340 operator*(float s, const Vector3_s00c1_3340& v) { return Vector3_s00c1_3340(v.x * s, v.y * s, v.z * s); }
struct Quaternion_s00c1_3340 {
    float x, y, z, w;
    Quaternion_s00c1_3340() {}
};
struct IEffect {
    PV                                        // 0x00
    virtual void Release();                   // 0x04
    PV                                        // 0x08
    virtual void Stop(int flag);              // 0x0c
    PV8 PV8 PV4 PV                            // 0x10..0x60 (21 slots)
    virtual void Detach();                    // 0x64
};
struct IRefObj {
    PV8 PV8 PV8 PV8 PV8 PV4 PV2 PV             // 0x00..0xb8 (47 slots)
    virtual void AddRef();                    // 0xbc
    virtual void SubRef();                    // 0xc0
};
struct ICombatant {
    PV2                                       // 0x00
    virtual void* ToSpatialObject();          // 0x08
    virtual void* ToGameData();               // 0x0c
    PV8 PV8 PV8 PV4 PV                         // 0x10..0x80 (29 slots)
    virtual void SetCreatureTarget(void* a, void* b, void* c);  // 0x84
};
struct IGameData {
    PV8 PV2 PV                                // 0x00..0x28
    virtual bool IsDestroyed();               // 0x2c
};
struct ISpatial {
    uint8_t pad0[0x75];                        // +0x00 .. +0x75
    uint8_t mb76;                              // +0x75 (mbEnabled)
};
struct ILoco {
    PV8 PV2 PV                                // 0x00..0x28 (11 slots)
    virtual Vector3_s00c1_3340* Get2c();                 // 0x2c (returns a Vector3 pointer)
    PV8 PV2 PV                                // 0x30..0x58 (11 slots)
    virtual void* Get5c(void* a, void* b, float c);  // 0x5c
    PV2                                       // 0x60..0x64 (2 slots)
    virtual void* Get68();                    // 0x68 (extents pointer)
    PV                                        // 0x6c
    virtual float GetScalar70();              // 0x70
};
struct IProp {
    PV8 PV8 PV8 PV8 PV8                           // 0x00..0x9c (40 slots)
    virtual void Set(void* v);                    // 0xa0
    PV2 PV2                                        // 0xa4..0xa8
    virtual int  Get();                            // 0xac
    PV2 PV2                                        // 0xb0..0xb4
    virtual void* Find(int keyword);               // 0xb8
};
struct PropData {
    void*    mpVtbl;                              // +0x00
    uint8_t  pad04[0x4c];
    uint32_t mFlags50;                            // +0x50
};
struct IKeyed {
    PV8                                             // 0x00..0x1c (slots 0..7)
    virtual void* Slot20(int key);                  // 0x20
};
struct KeyedData {
    void*   mpVtbl;                                 // +0x00
    uint8_t pad04[0x24];
    int     mKey28;                                 // +0x28
};
struct IModelWorld {
    virtual void Slot00();                        // 0x00
    virtual void Release();                       // 0x04
};
struct IStream {
    PV8                                        // 0x00..0x1c (8 slots)
    virtual void* GetWriter_20();              // 0x20
    PV                                          // 0x24
    virtual void  Slot28(int key, void* out, int b);  // 0x28
};
struct IWriterS {
    PV2 PV4                                    // 0x00..0x14 (6 slots)
    virtual void* GetStream_18();              // 0x18
};
void        FUN_00c0d660(void* self, void* out);                 // 0x00c0d660 compute
void*       FUN_00d20610(void* loco);                             // 0x00d20610 GetVelocity
void*       FUN_0099c1a0(void* out, const void* q, const void* v); // 0x0099c1a0 QuaternionVectorTransform
void*       FUN_0099c310(void* out, const void* q, const void* v); // 0x0099c310 QuaternionVectorInverseTransform
void        FUN_00c104d0v(void* out, const void* a, const void* b); // 0x00c104d0 (3-arg form at this call site)
void        FUN_00a02bf0(const void* src, char b);                // 0x00a02bf0 cAnimatingCreature::SetMode
float       FUN_004885d0(const void* v);                          // 0x004885d0 Dot3
void*       FUN_00449c20(void* out, const void* v);               // 0x00449c20 normalized_safe
void        FUN_00c446d0(const void* v, int a);                   // 0x00c446d0
void        FUN_00c12310(void* self, int anim, int a, int b);      // 0x00c12310 InterruptAnimation
void*       FUN_00b5b800();                                        // 0x00b5b800 SP::GetCurrentGameMode
void*       FUN_00ae66f0(void* creature);                          // 0x00ae66f0 CastCreature
void*       FUN_00d38840();                                        // 0x00d38840 cCreatureModeStrategy::Instance
float       FUN_004e1c70(int a, int key, float def);               // 0x004e1c70 SP::GetPropertyT<float>
void        FUN_00ad7ec0(void* dst, void* src);                   // 0x00ad7ec0 PtrField::assign
void        FUN_00c0e000(void* obj, void* a, void* b);             // 0x00c0e000 set
void*       FUN_00b3d520();                                        // 0x00b3d520 SP::GonzagoModelWorld
void*       FUN_00b3d310(void* a, int b);                          // 0x00b3d310
void        FUN_00b5a260(void* a);                                 // 0x00b5a260
void*       FUN_009cab60(void* mw, void* prop);                    // 0x009cab60
void        FUN_00c0de60(void* self, void* elem, void* offsets);   // 0x00c0de60 SetGraspedEffectOffsets
void*       FUN_00b3d300(int noun);                                // 0x00b3d300 SP::NounManager
void*__fastcall FUN_00b21000(void* nm, void* edx);                  // 0x00b21000 (thiscall, 1 arg)
int         FUN_0064f350(int a, int key, int b);                   // 0x0064f350 parser/state
void        FUN_00d7d220(void* a, void* b);                        // 0x00d7d220
int         FUN_00c11f50(void* self, int index, int a, void* b, void* c);  // 0x00c11f50 CreateBodyEffect
void        FUN_00a01f10(void* obj, void* edx, int a, int b);     // 0x00a01f10 anim_qb::Foo
int         FUN_00c0c5b0(void* self, int a, int* out);             // 0x00c0c5b0
void        FUN_00c10210(int a, int b, int c, int d);              // 0x00c10210
void        FUN_0093ac80(void* stream, void* out);            // 0x0093ac80 ReadBool
extern Vector3_s00c1_3340 gZeroVec;        // 0x0168d910 (0,0,0)
struct Rec34 {
    uint32_t mp00;      // +0x00 (cleared with no release)
    uint8_t  pad04[0x20];
    IEffect* mpThird;   // +0x24
    IEffect* mpFirst;   // +0x28
    IEffect* mpSecond;  // +0x2c
    uint8_t  pad30[4];  // +0x30
};
struct DestructOwner {
    uint32_t pad00[0x301];            // +0x0000 .. +0x0c04
    uint32_t mC04;                    // +0x0c04
    uint32_t mC08;                    // +0x0c08
    uint32_t mC0C;                    // +0x0c0c
    uint8_t  padC10[0x2a4];           // +0x0c10 .. +0x0eb4
    Rec34    mRecs[4];                // +0x0eb4
};
struct CAnim {
    PV2 PV                                      // 0x00..0x04
    virtual void* Slot08(int a, int b);         // 0x08
    virtual void  Slot0c(int a, int b);         // 0x0c
    PV2 PV2                                      // 0x10..0x14
    virtual void  Slot18(int a);                // 0x18
    virtual void  Slot1c(int a, float v);       // 0x1c
    virtual void  Slot20(int a, int v);         // 0x20
    virtual void  Slot24(int a, float v);       // 0x24
    virtual void  Slot28(int a, void* p);       // 0x28
    PV4                                          // 0x2c..0x38
    virtual void  Slot3c(int a, bool b);        // 0x3c
    virtual void  Slot40(int a, int v);         // 0x40
    PV                                          // 0x44
    virtual void  Slot48(int a, void* cb);      // 0x48
    virtual void  Slot4c(int a, int flags, int b);  // 0x4c
    uint8_t  pad4[0x160];    // +0x04 .. +0x164
    Vector3_s00c1_3340  mLocalOffset;   // +0x164
    uint8_t  pad170[0xc];
    void*    mpModelWorld;   // +0x17c
    uint8_t  pad180[4];
    void*    mpP184;         // +0x184
};
struct CModelWorld {
    uint8_t   pad00[0x18];
    Vector3_s00c1_3340   mPos;          // +0x18
    Vector3_s00c1_3340   pad24;
    Quaternion_s00c1_3340 mQuat;        // +0x3c
};
struct CitRec {
    int32_t  mId;            // +0x00
    uint8_t  pad04[0x1c];
    IRefObj* mpPtr;          // +0x20
};
struct CAnimator {
    uint8_t  pad00[0x548];
    float    mF548;          // +0x548 hover height
    float    mF54C;          // +0x54c hover height (unscaled)
    uint8_t  pad550[0x40];
    float    mF590;          // +0x590
    uint8_t  pad594[0x88];
    int32_t  mI61c;          // +0x61c
    uint8_t  pad620[0x78];
    int32_t  mI698;          // +0x698
    uint8_t  pad69c[4];
    int32_t  mI6a0;          // +0x6a0
};
struct CCreature {
    uint8_t   pad00[0x110];
    uint32_t  mFlags110;         // +0x110 (0x1000 = hover enabled)
    uint8_t   pad114[0x23];
    uint8_t   mb137;             // +0x137
    uint8_t   pad138[0x178];
    uint32_t  mAnim3;            // +0x2b0 (mode = 3)
    uint8_t   pad2B4[0x80];
    uint32_t  mB34;              // +0x334
    uint8_t   pad338[0x7e8];
    void*     mpAnimator;        // +0xb20
    uint8_t   padB24[0x30];
    void*     mpAnimating;       // +0xb54
    uint32_t  mFlagsB58;         // +0xb58
    uint8_t   padB5C[0x2e4];
    CitRec*   mpRecsBegin;       // +0xe40
    CitRec*   mpRecsEnd;         // +0xe44
    uint8_t   padE48[0x1b];
    uint8_t   mbE63;             // +0xe63
    uint32_t  mE64;              // +0xe64
    uint8_t   padE68[0x14];      // +0xe68 .. +0xe7c
    ICombatant* mpCombatantTarget;  // +0xe7c
    uint8_t   padE80[0x34];
    Rec34     mAttacks[4];       // +0xeb4
};
// ---- items of slice s00c13340 end

// ---- items of slice s00c15310 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float gF_1582e6c;       // 0x1582e6c
extern float gF_1582e70;       // 0x1582e70
extern float gF_169e280;       // 0x169e280
extern float gF_169e284;       // 0x169e284
extern float gF_146a32c;       // 0x146a32c (float sentinel, ~3.4e38)
extern float gF_168d910[];     // 0x168d910
typedef unsigned int   u32;
typedef int            s32;
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   SIZE_T;
struct Vec3_s00c1_5310 { float x, y, z; };
struct RefCnt {
  virtual void  AddRef();               // 0x00
  virtual void  Release();              // 0x04
  virtual void  pad08();
  virtual void  pad0c();
  virtual void  pad10();
  virtual void  pad14();
  virtual void  pad18();
  virtual void  pad1c();
  virtual void  pad20();
  virtual void  pad24();
  virtual void  pad28();
  virtual void  pad2c();
  virtual void  pad30();
  virtual void  pad34();
  virtual void  pad38();
  virtual void  pad3c();
  virtual void  pad40();
  virtual void  pad44();
  virtual void  pad48();
  virtual void  pad4c();
  virtual void  pad50();
  virtual void  pad54();
  virtual void  pad58();
  virtual void  pad5c();
  virtual void  pad60();
  virtual void  pad64();
  virtual void  pad68();
  virtual void  pad6c();
  virtual void  pad70();
  virtual void  pad74();
  virtual void  pad78();
  virtual void  pad7c();
  virtual void  pad80();
  virtual void  pad84();
  virtual void  pad88();
  virtual void  pad8c();
  virtual void  pad90();
  virtual void  pad94();
  virtual void  pad98();
  virtual void  pad9c();
  virtual void  pada0();
  virtual void  padA4();
  virtual void  padA8();
  virtual void  padAc();
  virtual void  padB0();
  virtual void  padB4();
  virtual void  padB8();
  virtual void  padBc();
};
struct SpatSub {
virtual void  pad00();
virtual void  pad04();
virtual void  pad08();
virtual void  pad0c();
virtual void  pad10();
virtual void  pad14();
virtual void  pad18();
virtual void  pad1c();
virtual void  pad20();
virtual void  pad24();
virtual void  pad28();
virtual void  pad2c();
virtual void  pad30();
virtual void  pad34();
virtual void  pad38();
virtual void  pad3c();
virtual void  pad40();
virtual void  pad44();
virtual void  pad48();
virtual void  pad4c();
virtual void  pad50();
virtual void  pad54();
virtual void  pad58();
  virtual Vec3_s00c1_5310* GetBounds(Vec3_s00c1_5310* out);              // 0x5c
  virtual void  pad60();
virtual void  pad64();
virtual void  pad68();
  virtual Vec3_s00c1_5310* GetBox(Vec3_s00c1_5310* out);                 // 0x6c
  virtual void  pad70();
  virtual float GetRadius();                       // 0x74
};
struct cCreatureAbility {
  u8   pad000[0x9c];
  float mF_9c;                                     // 0x9c
};
struct cAbilityState {
  u32   mU32_00;                                   // 0x00
  float mF_04;                                     // 0x04
  u32   mU32_08;                                   // 0x08
  u32   mU32_0c;                                   // 0x0c
};
struct BaseVtbl {
  virtual void* Slot0c(u32);                       // 0x0c
  virtual void  Slot18(void*);                     // 0x18
  virtual void  Slot1c(void*);                     // 0x1c
  virtual void* Slot20();                          // 0x20
  virtual void* Slot24(u32 propId, void* out);     // 0x24
  virtual u32   Slot2c(void* p);                   // 0x2c
  virtual void  Slot60();                          // 0x60
  virtual void  Slot64();                          // 0x64
  virtual Vec3_s00c1_5310* Slot6c(Vec3_s00c1_5310* out);                 // 0x6c
  virtual void  Slot70();
  virtual float Slot74();                          // 0x74
  virtual void  Slotb0();                          // 0xb0
  virtual u32   Slotb0_count();                    // 0xb0
  virtual u32   Slotb4(u32);                       // 0xb4
  virtual void* Slotb8(u32);                       // 0xb8
  virtual void  Slotbc();                          // 0xbc
  virtual void  Slotc0();                          // 0xc0
};
struct cSPCreatureBase_s00c1_5310 {
  BaseVtbl* mpVtbl;                                // 0x000
  u8        pad004[0xc0 - 0x04];
  SpatSub   mSpatial;                              // 0x0c0
  u8        pad0c4[0x1e4 - 0xc4];
  float     mF_1e4;                                // 0x1e4
  u8        pad1e8[0x4cc - 0x1e8];
  RefCnt*   mpRefA_4cc;                            // 0x4cc
  u8        pad4d0[0xb54 - 0x4d0];
  void*     mpAnimWorld_b54;                       // 0xb54 (anim world)
  u32       mFlags_b58;                            // 0xb58 (bit 9 tested)
  u8        padB5c[0xbf8 - 0xb5c];
  // mRechargingAbilityBits: a 3-word bitset at 0xbf8
  u32       mRechargeBits_bf8[3];                  // 0xbf8
  u32       mAbilityDirty_c04[3];                  // 0xc04
  u8        padC10[0xc28 - 0xc10];
  void*     mpAbilityStates_c28;                   // 0xc28 (vector block ptr)
  u8        padC2c[0xe40 - 0xc2c];
  u8*       mNeighborBegin_e40;                    // 0xe40
  u8*       mNeighborEnd_e44;                      // 0xe44
  u8        padE48[0xe58 - 0xe48];
  float     mWaveF_e58;                            // 0xe58
  u8        padE5c[0xeb0 - 0xe5c];
  // Slot 0 of the 4x0x34-byte body-effect slot block at 0xeb0. Slot 1 begins
  // at 0xee4 (aliasing mFlags_ee4 below), slots 2..3 follow it.
  u8        mBodyBlock_eb0[0x34];                   // 0xeb0
  u32       mFlags_ee4;                            // 0xee4

  void __thiscall func64h(s32 a2, float a3);       // 0xc15310
  float FUN_00c15920();                            // 0xc15920
  float FUN_00c15970();                            // 0xc15970
  void  FUN_00c15470(s32 a2, RefCnt* a3, u8 a4);   // 0xc15470
  u8    FUN_00c159c0(u32 a2, u32 a3, u8 a4);       // 0xc159c0
  void* FUN_00c15bd0(u32 a2, u8 a3, u32 a4);       // 0xc15bd0
  u8    FUN_00c15d50(u32 a2, u32 a3, u32 a4);      // 0xc15d50
  void  FUN_00c15dc0(float a2);                    // 0xc15dc0
};
struct SlotMessageVtbl {
virtual void  pad00();
virtual void  pad04();
virtual void  pad08();
virtual void  pad0c();
virtual void  pad10();
  virtual void  Dispatch(void* a, u32 b, u32 c);  // 0x14
};
u32* __cdecl FUN_00c16090(u32* a1, u32* a2, u32* a3);       // 0xc16090
u8   __cdecl FUN_00c160c0(void* a1);                        // 0xc160c0
SlotMessageVtbl* __cdecl MessageServer_s00c1_5310();                   // 0x67dcc0
void __cdecl SlotMessage_Destruct(void* p);                 // 0x421cf0
u8   __cdecl EA_IO_WriteUint32(void* stream, u32* val, s32 count, s32 a4); // 0x93aa70
u8   __cdecl EA_StreamWrite(void* stream, s32 val, s32 a3); // 0x93a9a0
void* __cdecl FUN_00c15e50_impl(void* a1, void* a2);        // 0xc15e50
u8   __cdecl FUN_00c16100_impl(void* a1);                   // 0xc16100
float __cdecl FUN_00c161f0_impl(cSPCreatureBase_s00c1_5310* self, float a2); // 0xc161f0
u32  __cdecl FUN_00c0f620_();                               // 0xc0f620
u32  __cdecl FUN_00c0dfb0_();                               // 0xc0dfb0
u8   __cdecl FUN_00c11f50(cSPCreatureBase_s00c1_5310*, u32, u32, u32, u32); // 0xc11f50
void __cdecl FUN_00c14f70(cSPCreatureBase_s00c1_5310*, u32, u32, u32);      // 0xc14f70
void* __cdecl EffectsManager();                                  // 0x67ddd0
struct tEntry {
  u32   mId_00;                                    // 0x00
  u32   mType_04;                                  // 0x04
  u8    pad08[0x18 - 0x08];
  u8    mbFlag18;                                  // 0x18
  u8    pad19[0x20 - 0x19];
  RefCnt* mpObj_20;                                // 0x20
  float mF_24;                                     // 0x24
};
struct BodyEffectVtbl {
virtual void  pad00();
virtual void  pad04();
virtual void  pad08();
virtual void  pad0c();
virtual void  pad10();
virtual void  pad14();
  virtual void  SetMatrix(void* m);                // 0x18
virtual void  pad1c();
virtual void  pad20();
virtual void  pad24();
  virtual void  pad28();
  virtual void  Slot2c();                          // 0x2c
};
struct BodyEffect {
  BodyEffectVtbl* mpVtbl;                          // 0x00
  float           mF_04;                           // 0x04
  u8              pad08[0x2c - 0x08];
  void*           mpMatrix_2c;                     // 0x2c
};
struct ObjVtbl {
virtual void  Slot00();
virtual void  Slot04();
virtual void  Slot08();
virtual void* Slot0c(u32);
virtual void  Slot10();
virtual void  Slot14();
virtual void  Slot18();
virtual void  Slot1c();
virtual void* Slot20();
virtual void  Slot24();
virtual void  Slot28();
virtual u8    Slot2c();
virtual void  Slot30();
virtual void  Slot34();
virtual void  Slot38();
virtual void  Slot3c();
virtual void  Slot40();
virtual void  Slot44();
virtual void  Slot48();
virtual void  Slot4c();
virtual void  Slot50();
virtual void  Slot54();
virtual void  Slot58();
  virtual Vec3_s00c1_5310* Slot5c(Vec3_s00c1_5310* out);                 // 0x5c
virtual void  Slot60();
virtual void  Slot64();
  virtual Vec3_s00c1_5310* Slot6c(Vec3_s00c1_5310* out);                 // 0x6c
  virtual void  Slot70();
  virtual float Slot74();                          // 0x74
virtual void  Slot78();
virtual void  Slot7c();
virtual void  Slot80();
virtual void  Slot84();
virtual void  Slot88();
virtual void  Slot8c();
virtual void  Slot90();
virtual void  Slot94();
virtual void  Slot98();
virtual void  Slot9c();
virtual void  SlotA0();
virtual void  SlotA4();
virtual void  SlotA8();
virtual void  SlotAc();
virtual void  SlotB0();
virtual void  SlotB4();
virtual void* SlotB8(u32);
virtual void  SlotBc();
  virtual void  SlotC0();
};
void*  __cdecl FUN_00b3d310();                        // 0xb3d310
int*   __cdecl FUN_00c70110(void*);                   // 0xc70110
void   __cdecl FUN_00c13db0(u32, void*);              // 0xc13db0
int    __fastcall FUN_00c06000_tc(void* thisptr);      // 0xc06000 (ecx=arg)
u8     __fastcall FUN_00c15150_tc(void* thisobj, int dummy, void* a1, u32 a2); // 0xc15150
void   __cdecl FUN_00c0fae0(void*);                   // 0xc0fae0
void   __cdecl FUN_00c0f490(void*);                   // 0xc0f490
void   __cdecl FUN_00c0ca00(Vec3_s00c1_5310*, Vec3_s00c1_5310*, float, void*, void*); // 0xc0ca00
u32    __cdecl FUN_00c0de60(cSPCreatureBase_s00c1_5310*, u32, u32);   // 0xc0de60
void   __cdecl FUN_00b453a0(void*);                   // 0xb453a0
void   __cdecl FUN_00b54200(void*);                   // 0xb54200
void   __cdecl FUN_00d7d2c0(void*, void*);            // 0xd7d2c0
void   __cdecl FUN_00c12640(float);                   // 0xc12640
void*  __cdecl FUN_0099c1a0(Vec3_s00c1_5310* out, void* quat, Vec3_s00c1_5310* in);  // 0x99c1a0
float* __cdecl FUN_0041ea70(void* prop);                       // 0x41ea70
void*  __cdecl FUN_0069b440(void* out, void* facing, void* up); // 0x69b440
void*  __cdecl FUN_009cab60(u32 a1, s32 a2);                   // 0x9cab60
void*  __cdecl cSPGetCurrentGameMode(u32);            // 0xb5b800
void*  __cdecl FUN_00b1daf0(void*);                    // 0xb1daf0
struct EffectsMgr {
  virtual void  pad0();
  virtual void  pad1();
  virtual void  pad2();
  virtual void  pad3();
  virtual void  pad4();
  virtual void  pad5();
  virtual void  pad6();
  virtual void  pad7();
  virtual void  pad8();
  virtual void  pad9();
  virtual void  padA();
  virtual u8    Slot2c(u32 a, u32 b, void** out);      // 0x2c
};
struct cSPCreatureBaseVtbl {
virtual void  pad00();
virtual void  pad04();
virtual void  pad08();
virtual void  pad0c();
virtual void  pad10();
virtual void  pad14();
virtual void  pad18();
virtual void  pad1c();
virtual void  pad20();
virtual void  pad24();
virtual void  pad28();
virtual void  pad2c();
virtual void  pad30();
virtual void  pad34();
virtual void  pad38();
virtual void  pad3c();
virtual void  pad40();
virtual void  pad44();
virtual void  pad48();
virtual void  pad4c();
virtual void  pad50();
virtual void  pad54();
virtual void  pad58();
virtual void  pad5c();
virtual void  pad60();
virtual void  pad64();
virtual void  pad68();
virtual void  pad6c();
virtual void  pad70();
virtual void  pad74();
virtual void  pad78();
virtual void  pad7c();
virtual void  pad80();
virtual void  pad84();
virtual void  pad88();
virtual void  pad8c();
virtual void  pad90();
virtual void  pad94();
virtual void  pad98();
virtual void  pad9c();
virtual void  padA0();
virtual void  padA4();
virtual void  padA8();
virtual void  padAc();
  virtual u32   GetAbilitiesCount();                    // 0xb0 (this slice)
  virtual cCreatureAbility* GetAbility(u32);            // 0xb4
  virtual void* Slotb8(u32);                            // 0xb8
};
struct SimCreature {
  cSPCreatureBaseVtbl* mpVtbl;                          // 0x000
};
static inline u32 neighborCount(cSPCreatureBase_s00c1_5310* p)
{
  return (u32)((p->mNeighborEnd_e44 - p->mNeighborBegin_e40) / 0x24);
}
struct IOStreamVtbl {
virtual void  pad00();
virtual void  pad04();
virtual void  pad08();
virtual void  pad0c();
virtual void  pad10();
virtual void  pad14();
  virtual void* Slot18();                     // 0x18
  virtual void  Slot1c();                     // 0x1c
  virtual void* Slot20();                     // 0x20
virtual void  pad24();
virtual void  pad28();
  virtual void* Slot2c(u32);                  // 0x2c
};
struct IOStream { IOStreamVtbl* mpVtbl; };
void __cdecl FUN_00c15f60_impl(IOStream* a1, void* a2);    // 0xc15f60
struct SerRecord {
  u32   mU32_00;                              // 0x00
  u32   mU32_04;                              // 0x04
  u32   mU32_08;                              // 0x08
  u32   mU32_0c;                              // 0x0c
  u32   mU32_10;                              // 0x10
  u8    mB_14[0x18 - 0x14];
  u8    mbFlag18;                             // 0x18
};
struct PropsMgrVtbl {
virtual void  pad00();
virtual void  pad04();
virtual void  pad08();
virtual void  pad0c();
virtual void  pad10();
virtual void  pad14();
virtual void  pad18();
virtual void  pad1c();
  virtual void  pad20();
  virtual u8    GetProperty(u32 id, void* out);   // 0x24
};
struct Property {
  u8    pad00[0x12];
  u16   mType_12;                                 // 0x12
};
struct AbilityObj {
  u8  pad00[0x88];
  u32 mpEffect_88;      // 0x88 (parent effect object)
  u32 mEffectId_8c;     // 0x8c (effect resource id passed to EffectsMgr)
};
struct BodyEntry {
  u8      mB_00;                          // 0x00
  u8      mB_01;                          // 0x01
  u8      pad02[0x04 - 0x02];
  u32     mU32_04;                        // 0x04
  float   mF_08;                          // 0x08
  float   mF_0c;                          // 0x0c
  float   mF_10;                          // 0x10
  float   mF_14;                          // 0x14
  float   mF_18;                          // 0x18
  float   mF_1c;                          // 0x1c
  u32     mU32_20;                        // 0x20
  float   mF_24;                          // 0x24
  RefCnt* mpTarget_28;                    // 0x28
  BodyEffect* mpEffect_2c;                // 0x2c
  u8      pad30[0x34 - 0x30];
};
// ---- items of slice s00c15310 end

// ---- items of slice s00c17350 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const uint32_t gBodyPartNames[16];  // 0x015716e8  four-character part names
extern const float kEps;                   // 0x013ec4b8  (1e-8f)
extern "C" uint32_t FUN_009b2340(uint32_t* out, uint32_t max, uint32_t model,
                                 void* query, int zero1, int zero2);   // 0x009b2340
#pragma intrinsic(sqrt)
struct cEffectSlot {
    virtual void v00();                // slot +0x00
    virtual void v04();                // slot +0x04
    virtual void v08();                // slot +0x08
    virtual void v0c();                // slot +0x0c
    virtual bool IsActive();           // slot +0x10
};
struct cEffectEntry {
    uint8_t      mPad000[0x8c];        // +0x000
    cEffectSlot* mEffect;              // +0x08c
};
struct cVector3 {
    float x, y, z;
};
struct cMatrix3 {
    float m[9];

    void Assign(const cMatrix3* src);  // 0x0041cb40
};
struct cSPTransform_s00c1_7350 {
    uint16_t  mFlags;                  // +0x00
    uint16_t  mVersion;                // +0x02
    cVector3  mOffset;                 // +0x04
    float     mScale;                  // +0x10
    cMatrix3  mRot;                    // +0x14

    void BackTransformPoint(cVector3* point);   // 0x004ff6d0
    void PreRotateY(float angle);               // 0x004099b0
};
struct cBodyPart {
    uint8_t mPad000[0x10];             // +0x000
    float   mPosition[3];              // +0x010
    uint8_t mPad01c[0x2bc - 0x1c];     // +0x01c
};
struct cAnimPartInstance {
    uint8_t mPad000[0x36c];            // +0x000
    float   mRadius;                   // +0x36c
    uint8_t mPad370[0x468 - 0x370];    // +0x370
};
struct cAnimPartSet {
    uint8_t            mPad000[0x384]; // +0x000
    cAnimPartInstance* mpParts;        // +0x384
};
struct cBodyAnim {
    cAnimPartSet*  mpAnimSet;          // +0x000
    uint8_t        mPad004[0x18 - 0x04]; // +0x004
    float          mPosX;              // +0x018
    float          mPosY;              // +0x01c
    float          mPosZ;              // +0x020
    uint8_t        mPad024[0x3c - 0x24]; // +0x024
    float          mOrientation[4];    // +0x03c
    uint8_t        mPad04c[0x70 - 0x4c]; // +0x04c
    float          mScale;             // +0x070
    uint8_t        mPad074[0x2e4 - 0x74]; // +0x074
    cBodyPart*     mpBodyParts;        // +0x2e4

    cEffectEntry* FindEffect(uint32_t key);              // 0x009cab60
    float* GetWorkspaceOrigin(float* out, int part);     // 0x009b61f0
};
struct cCreatureBody {
    uint8_t     mPad000[0x17c];        // +0x000
    cBodyAnim*  mAnim;                 // +0x17c
};
struct cUIntVector {
    uint32_t* mpBegin;                 // +0x00
    uint32_t* mpEnd;                   // +0x04
};
struct cCreaturePartManager {
    cUIntVector* GetPartsA(cCreatureBody* body);   // 0x004d9030
    cUIntVector* GetPartsB(cCreatureBody* body);   // 0x004d9050
};
struct cHashNode;
struct cListIterator {
    cHashNode* mpNode;                 // +0x00
    void**     mpBucket;               // +0x04
};
struct cHashNode {
    uint8_t mPad00[4];                 // +0x00
    void*   mpValue;                   // +0x04
};
struct cHashTable {
    uint8_t      mPad00[4];            // +0x00
    cHashNode**  mpBuckets;            // +0x04
    int32_t      mBucketIndex;         // +0x08

    void Find(cListIterator* out, const uint32_t* key);                    // 0x00645ed0
    cListIterator* Erase(cListIterator* out, cListIterator node);          // 0x00d2c9f0
};
struct cStyleValue {
    virtual void v00();                // slot +0x00
    virtual void v04();                // slot +0x04
    virtual void v08();                // slot +0x08
    virtual void v0c(void* arg);       // slot +0x0c
};
struct cTextStyleManager {
    uint8_t    mPad000[0xcc8];         // +0x000
    cHashTable mLookup;                // +0xcc8
    uint8_t    mPad0cd4[0xd68 - 0xcd4]; // +0x0cd4
    cHashTable mSecondary;             // +0x0d68
};
struct cBodyPartQuery {
    int32_t  mRootOnly;                // +0x00
    uint32_t mName;                    // +0x04
    uint32_t mPad08;                   // +0x08
    uint32_t mPad0c;                   // +0x0c
};
struct cSPCreatureBase_s00c1_7350 {
    uint8_t        mPad0000[0xb20];    // +0x0000
    cCreaturePartManager* mCreature;   // +0x0b20
    uint8_t        mPad0b24[0xb54 - 0xb24]; // +0x0b24
    cCreatureBody* mBody;              // +0x0b54

    uint32_t MakeBodyEffect(uint32_t part, uint32_t a, uint32_t b);  // 0x00c14f70
    void     BodyEffectNotify(uint32_t a, uint32_t b);               // 0x00c15150

    // 0x00c17580
    uint32_t GetBodyPartIndex(uint32_t kind, uint32_t index);  // 0x00c17580 (cSPCreatureBase::GetBodyPartIndex)
    // 0x00c17c80
    uint32_t CreateBodyEffect(uint32_t kind, uint32_t a, uint32_t b);
    // 0x00c17cc0
    uint32_t CreateBodyEffectChecked(bool flag, uint32_t kind, uint32_t a, uint32_t e,
                                     uint32_t b);
    // 0x00c17d60
    uint32_t CreateBodyEffectChecked2(bool flag, uint32_t kind, uint32_t a, uint32_t e,
                                      uint32_t b);

    // 0x00c175d0
    bool CanReachPointWithBodyPart(cSPTransform_s00c1_7350* transform, const float* point, uint32_t kind,
                                   int32_t part, float* outPos, uint8_t* outHit,
                                   float radiusAdd);
    // 0x00c17a30
    bool GetBodyPartPosition(float* outPos, uint32_t kind, bool world, int32_t part);  // 0x00c17a30 (cSPCreatureBase::GetBodyPartPosition)
};
uint32_t QueryCreatureBodyParts(cSPCreatureBase_s00c1_7350* self, int32_t kind, uint32_t* out,
                                uint32_t max);
// ---- items of slice s00c17350 end

// ---- items of slice s00c18b40 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const float kRealZero;      // 0x01485378  _HK_REAL_ZERO
extern const float kSqrtEpsilon;   // 0x013ec4b8
extern const float kThree;         // 0x013eb95c
extern float  gZeroVecX;           // 0x0168d910
extern float  gZeroVecY;           // 0x0168d914
extern float  gZeroVecZ;           // 0x0168d918
extern bool   gB_1572050;          // 0x01572050
extern bool   gB_1572051;          // 0x01572051
extern bool   gB_169e381;          // 0x0169e381
extern float  gF_169e384;          // 0x0169e384
extern float  gF_169e388;          // 0x0169e388
extern float  gF_169e38c;          // 0x0169e38c
extern float  gF_169e390;          // 0x0169e390
extern float  gF_169e3b4;          // 0x0169e3b4
extern float  gF_169e3b8;          // 0x0169e3b8
extern float  gF_169e3bc;          // 0x0169e3bc
extern const char* gBodyPartsString; // 0x015716e8
extern int gAbilityStatesAllocator;  // 0x013ebb38 (eastl allocator)
extern const float kLeapRadiusScale; // 0x01582fd8
extern const float kDefaultSpeedCap; // 0x01582fc0
extern const float kCe80Boost;       // 0x0150c900
extern const float kHalf;            // 0x01471064
extern const float kClampLow;        // 0x013eb8c8
extern const float kPlenEpsilon;     // 0x01488874
typedef unsigned int   uint32;
struct Vector3_s00c1_8b40 { float x, y, z; };
struct InventoryItem;
bool   Vector3Equal(const Vector3_s00c1_8b40* a, const Vector3_s00c1_8b40* b);                  // 0x004232c0 (cdecl)
Vector3_s00c1_8b40* normalized_safe(Vector3_s00c1_8b40* out, const Vector3_s00c1_8b40* in);                // 0x00449c20 (cdecl)
void*  operator_new(uint32 size, const char* name, int a, int b,
                    const char* file, int line);                          // 0x00f473a0 (cdecl)
void*  FUN_00ac2130(void* begin, void* end, void* dst);                   // 0x00ac2130 (cdecl, copy range)
int    EvaluateContextTargetQuery(void* out, int max, void* abilities,
                                  void* ctx, int a, int b);               // 0x009b2340 (cdecl)
class cPlanetModel_s00c1_8b40 {
public:
    float FUN_00b7e490();                                             // 0x00b7e490
    float GetRadiusAt(const Vector3_s00c1_8b40* p);                              // 0x00b7ef70
    float FUN_00b82310(const Vector3_s00c1_8b40* p);                             // 0x00b82310
};
class cLoco {
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
    virtual const Vector3_s00c1_8b40* GetPos();                                  // 0x2c
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
virtual void v5c0();
    virtual const Vector3_s00c1_8b40* GetForward(Vector3_s00c1_8b40* out);                  // 0x5c
virtual void v60();
virtual void v64();
virtual void v68();
    virtual const float* GetBounds(float* out);                       // 0x6c
    virtual void v70();
    virtual float GetRadius();                                        // 0x74
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
    virtual float GetF_0xc8();                                        // 0xc8
virtual void vcc();
virtual void vd0();
virtual void vd4();
virtual void vd8();
    virtual void Submit(const void* req);                             // 0xdc

    const Vector3_s00c1_8b40* GetVelocity();                                     // 0x00d20610
    void FUN_00c446d0(const Vector3_s00c1_8b40* v, int flag);                    // 0x00c446d0 (ret 8)
};
struct AnimatingCreature {
    char  pad000[0x170];
    uint32 mField170;         // +0x170
    char  pad174[0x17c - 0x174];
    void** mpAbilityList;     // +0x17c
};
struct BodyPartQuery {
    int         flag;         // +0x0
    const char* mpName;       // +0x4
    int         a;            // +0x8
    int         b;            // +0xc
};
struct AbilityState {
    bool  applied;         // +0x0
    bool  inRange;         // +0x1
    char  pad02[2];
    float chargeLevel;     // +0x4
    double refresh;        // +0x8
};
struct Ability_s00c1_8b40 {
    char  pad00[0x104];
    float mCost;           // +0x104
};
struct SpeciesProfile {
    char  pad00[0x548];
    float jumpingAbility;      // +0x548
    char  pad54c[4];
    float flappingAbility;     // +0x550
    char  pad554[0x610 - 0x554];
    uint32 sprintLevel;        // +0x610
    char  pad614[8];
    uint32 preferredSocialType; // +0x61c
    char  pad620[0x698 - 0x620];
    uint32 mCount698;          // +0x698
    char  pad69c[4];
    uint32 mCount6a0;          // +0x6a0
};
struct LocomotionRequest {
    char* mpBegin;
    char  pad[0x6c];
    LocomotionRequest();                                              // 0x00ac9850
};
class cSPCreatureBase_s00c1_8b40 {
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
    virtual uint32 GetAbilityCount();                                 // 0xb0
    virtual Ability_s00c1_8b40* GetAbility(uint32 index);                        // 0xb4

    char  pad04[0xc0 - 4];
    cLoco mBody;                                                      // 0xc0
    char  padc0[0x110 - 0xc4];
    uint32 mFlags;                                                    // 0x110
    char  pad114[0x137 - 0x114];
    bool  mbLeaping;                                                  // 0x137
    char  pad138[0x2b0 - 0x138];
    int   mState;                                                     // 0x2b0
    char  pad2b4[0xb20 - 0x2b4];
    SpeciesProfile* mpProfile;                                        // 0xb20
    char  padb24[0xb54 - 0xb24];
    AnimatingCreature* mpAnimCreature;                                // 0xb54
    uint32 mGeneralFlags;                                             // 0xb58
    char  padb5c[0xbb0 - 0xb5c];
    bool  mbFieldBB0;                                                 // 0xbb0
    char  padbb1[0xbec - 0xbb1];
    uint32 mInUseAbilityBits[3];                                      // 0xbec
    uint32 mRechargingAbilityBits[3];                                 // 0xbf8
    char  padc04[0xc28 - 0xc04];
    AbilityState* mpAbilityStates;                                    // 0xc28
    char  padc2c[0xe40 - 0xc2c];
    InventoryItem* mpItemBegin;                                       // 0xe40
    InventoryItem* mpItemEnd;                                         // 0xe44
    char  pade48[0xe8c - 0xe48];
    uint32 mCurrentAttackIdx;                                         // 0xe8c

    int  FindIndex(int key);                                          // 0x00c0c080 (ret 4)
    void FUN_00c15dc0(float f);                                       // 0x00c15dc0 (ret 4, ApplyWave)
    void FUN_00c15bd0(int index, int a, int b);                       // 0x00c15bd0 (ret 0xc)
    float FUN_00c0ce80(int a, int b);                                 // 0x00c0ce80 (ret 8)

    int  FUN_00c18b40(int arg);                                       // 0x00c18b40 (ret 4)
    bool TryJumpToTarget(const Vector3_s00c1_8b40* a1, const Vector3_s00c1_8b40* a2,
                         int a3, float a4, bool a5);                  // 0x00c190e0 (ret 0x14)
    uint32 FUN_00c196a0(uint32 index, bool a2, bool a3);              // 0x00c196a0 (ret 0xc)
    void FUN_00c197a0(uint32 index);                                  // 0x00c197a0 (ret 4)
    void FUN_00c19940(bool a);                                        // 0x00c19940 (ret 4)
    void InterruptAnimation(uint32 id, int a, int b);                 // 0x00c12310 (ret 0xc)
    bool GetBodyPartPositionAndOrientation(Vector3_s00c1_8b40& out, void* quat,
                                           uint32 part, bool flag) const; // 0x00c11b50 (ret 0x10)
};
struct CreatureSubView {
    char pad[0x5a8];
    Vector3_s00c1_8b40* FUN_00c19870(Vector3_s00c1_8b40* out, int part);                    // 0x00c19870 (ret 8)
};
struct InventoryItem {
    char pad[0x20];
    void* mpObject;                                                   // +0x20
};
class InventoryObject {
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
    virtual void* Query(uint32 id);                                   // 0xb8
    char padbc[0x110 - 0xbc];
    int mKind;                                                        // 0x110
};
struct Vector003c {
    void* mpBegin;                                                    // +0x0
    void* mpEnd;                                                      // +0x4
    void* mpCapacity;                                                 // +0x8
    void reserve(uint32 count);                                       // 0x00c199e0 (ret 4)
};
// ---- items of slice s00c18b40 end

// ---- items of slice s00c1c9f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef int            i32;
typedef float          f32;
typedef double         f64;
double pow(double, double);
extern f32 DAT_01687a00;   // 0x01687a00
extern f32 DAT_0150c8c0;   // 0x0150c8c0
extern f32 DAT_013f9428;   // 0x013f9428
extern f32 DAT_013ec480;   // 0x013ec480
extern f32 DAT_013f7344;   // 0x013f7344
extern f64 DAT_01447a10;   // 0x01447a10
extern const f32 _HK_REAL_ONE;   // 0x01485720
extern const f32 _HK_REAL_ZERO;  // 0x01485378
extern u8  DAT_0168d910;   // 0x0168d910
extern u8  DAT_0168d964;   // 0x0168d964
extern f32 DAT_0168d988;   // 0x0168d988
extern f32 DAT_0168d98c;   // 0x0168d98c
extern f32 DAT_0168d990;   // 0x0168d990
class cVObj {
public:
    virtual void  v00();
    virtual void  v04();                 // +0x04: Release
    virtual void  v08(i32);              // +0x08
    virtual void  v0c(i32);              // +0x0c
    virtual bool  v10();                 // +0x10
    virtual void  v14();                 // +0x14
    virtual void  v18(void*);            // +0x18
    virtual void  v1c();                 // +0x1c
    virtual void  v20();                 // +0x20
    virtual void  v24();                 // +0x24
    virtual void  v28();                 // +0x28
    virtual void  v2c(i32);              // +0x2c
    virtual i32   v30();                 // +0x30
    virtual void  v34();                 // +0x34
    virtual i32   v38(i32);              // +0x38
    virtual void  v3c();                 // +0x3c
    virtual void  v40(i32, i32);         // +0x40
    virtual void  v44();                 // +0x44
    virtual void  v48();                 // +0x48
    virtual void  v4c();                 // +0x4c
    virtual void  v50();                 // +0x50
    virtual void  v54();                 // +0x54
    virtual void  v58();                 // +0x58
    virtual void  v5c();                 // +0x5c
    virtual void  v60();                 // +0x60
    virtual void  v64();                 // +0x64
    virtual void  v68();                 // +0x68
    virtual void  v6c();                 // +0x6c
    virtual void  v70();                 // +0x70
    virtual void  v74();                 // +0x74
    virtual void  v78();                 // +0x78
    virtual void  v7c();                 // +0x7c
    virtual void  v80();                 // +0x80
    virtual void  v84();                 // +0x84
    virtual void  v88();                 // +0x88
    virtual void  v8c();                 // +0x8c
    virtual void  v90();                 // +0x90
    virtual void  v94();                 // +0x94
    virtual void  v98();                 // +0x98
    virtual void  v9c(i32);              // +0x9c
    virtual void  vA0();                 // +0xa0
    virtual void  vA4();                 // +0xa4
    virtual void  vA8();                 // +0xa8
    virtual void  vAc();                 // +0xac
    virtual i32   vB0();                 // +0xb0
    virtual i32   vB4(i32);              // +0xb4
    virtual void  vB8();                 // +0xb8
    virtual void  vBc();                 // +0xbc
    virtual void  vC0();                 // +0xc0
    virtual void  vC4();                 // +0xc4
    virtual void  vC8();                 // +0xc8
    virtual void  vCc();                 // +0xcc
    virtual void  vD0();                 // +0xd0
    virtual void  vD4();                 // +0xd4
    virtual void  vD8();                 // +0xd8
    virtual void  vDc();                 // +0xdc
    virtual void  vE0();                 // +0xe0
    virtual void  vE4();                 // +0xe4
    virtual void  vE8();                 // +0xe8
    virtual void  vEc();                 // +0xec

    // non-virtual helpers that are called directly on embedded sub objects
    void FUN_00c41d60(void* pArg);       // 0x00c41d60
    void FUN_00bfcae0();                 // 0x00bfcae0
};
class cEffectsMgr {
public:
    virtual void  e00();                 // +0x00
    virtual void  e04();                 // +0x04
    virtual void  e08();                 // +0x08
    virtual void  e0c();                 // +0x0c
    virtual void  e10();                 // +0x10
    virtual void  e14();                 // +0x14
    virtual void  e18();                 // +0x18
    virtual void  e1c();                 // +0x1c
    virtual void  e20();                 // +0x20
    virtual void  e24();                 // +0x24
    virtual void  e28();                 // +0x28
    virtual bool  e2c(i32, i32, void**); // +0x2c
};
class cOrderMgr {                        // at +0xb48
public:
    void FUN_00bc9fe0();                 // 0x00bc9fe0
};
class cSpeciesProfile {                  // at +0xb20
public:
    u8  mPad_000[0x53c];
    u32 mnSequence;                      // +0x53c
    u8  mPad_540[0x644 - 0x540];
    f32 mf_644;                          // +0x644
};
class cEffect {                          // at +0xb54
public:
    u8  mPad_000[0x80];
    f32 mf_80;                           // +0x80
};
class cDetach {                          // at +0xe7c
public:
    virtual void  d00();
    virtual void  d04();
    virtual void  d08();
    virtual void  d0c();
    virtual void  d10();
    virtual void  d14();
    virtual void  d18();
    virtual void  d1c();
    virtual void  d20();
    virtual void  d24();
    virtual void  d28();
    virtual void  d2c();
    virtual void  d30();
    virtual void  d34();
    virtual void  d38();
    virtual void  d3c();
    virtual void  d40();
    virtual void  d44();
    virtual void  d48();
    virtual void  d4c();
    virtual void  d50();
    virtual void  d54();
    virtual void  d58();
    virtual void  d5c();
    virtual void  d60();
    virtual void  d64();                 // +0x64
};
class cPHTable {
public:
    void* FUN_00b76460(u32* pKey);       // 0x00b76460
    void  FreeBuckets(cVObj** ppBuckets, u32 nCount);   // 0x00a24480
    cVObj** mppBuckets;                  // +0x00
    u32     mnBucketCount;               // +0x04
    u32     mnSize;                      // +0x08
    u32     mnElementCount;              // +0x0c
};
struct cPHNode {
    cPHNode* mpNext;                     // +0x00
    cVObj*   mpObject;                   // +0x04
    cPHNode* mpChain;                    // +0x08
    u32      mnHashKey;                  // +0x0c
};
struct cRBNode {
    cRBNode* mpLeft;                     // +0x00
    cRBNode* mpParent;                   // +0x04
    cRBNode* mpRight;                    // +0x08
    u8       mbColor;                    // +0x0c
    u8       mPad_0d[3];
};
struct cRBTree {
    u32      mUnk_00;                    // +0x00
    cRBNode  mAnchor;                    // +0x04
    u32      mnSize;                     // +0x14
};
template<class T>
class cVec {
public:
    void FUN_00c53690(i32 n);            // 0x00c53690
    void FUN_00c19d10(T* pEnd, const T* pSrc); // 0x00c19d10
    void clear() { mpEnd = mpBegin; }
    void push_back(const T& v) {
        if (mpEnd < mpCapacity) {
            if (mpEnd != 0)
                *mpEnd = v;
            ++mpEnd;
        } else {
            FUN_00c19d10(mpEnd, &v);
        }
    }
    T* mpBegin;                          // +0x00
    T* mpEnd;                            // +0x04
    T* mpCapacity;                       // +0x08
};
class cVec2 {
public:
    void clear() { mpEnd = mpBegin; }
    void* mpBegin;                       // +0x00
    void* mpEnd;                         // +0x04
};
struct cAbilityState_s00c1_c9f0 {
    u8  mbActive;                        // +0x00
    u8  mbEnabled;                       // +0x01
    u16 mwFlags;                         // +0x02
    f32 mfWeight;                        // +0x04
    u32 mGroupId;                        // +0x08
    u32 mInstanceId;                     // +0x0c
};
cEffectsMgr* __cdecl EffectsManagerPtr();                 // 0x0067ddd0
void* __cdecl FUN_00b76460(u32* pKey);                    // 0x00b76460
void* __cdecl copy_705250(const void* a, const void* b, void* c);   // 0x00705250
void  __cdecl FUN_00bcb660(u32 a);                        // 0x00bcb660
class cMatrix3_s00c1_c9f0 {
public:
    void Assign(void* pSrc);             // 0x0041cb40
    f32  mf[9];
};
class cSPCreatureBase_s00c1_c9f0 : public cVObj {
public:
    // ---- slice targets ----
    void   FUN_00c1c9f0(char a);
    bool   FUN_00c1cc80(char a);
    void   FUN_00c1cdd0(i32 a);  // 0x00c1cdd0 (cSPCreatureBase::FUN_00c1cdd0)
    void   FUN_00c1cf20();
    cVObj* FUN_00c1d120(u32 a, u32 b);
    cVObj* FUN_00c1d290(u32 a);
    cVObj* FUN_00c1d400(u32 a, u32 b);
    cVObj* FUN_00c1d430(u32 a);
    cVObj* FUN_00c1d460(u32 a, u32 b);
    i32    FUN_00c1d5e0(char a, u32 b, u32 c);

    // ---- helpers called on this ----
    void  SetStealthed(i32 a, i32 b);                     // 0x00c1aed0
    void  SetSprinting(i32 a);                           // 0x00c1ad10
    void  InterruptAnimation(u32 id, i32 a, i32 b);      // 0x00c12310
    f32   FUN_00c0bb20();                                // 0x00c0bb20
    i32   FUN_00c0c080(i32 a);                           // 0x00c0c080
    void  FUN_00c0d9b0();                                // 0x00c0d9b0
    void  FUN_00c15dc0(f32 a);                           // 0x00c15dc0
    void  FUN_00c17350(u32 a, i32 b);                    // 0x00c17350
    void  FUN_00c19940(i32 a);                           // 0x00c19940
    void  FUN_00c151b0();                                // 0x00c151b0
    cVObj* FUN_00c14e70(u32 a);                          // 0x00c14e70

    // ---- fields (offsets are exact) ----
    u8   mPad_004[0xbc];                 // 0x004 .. 0x0bf
    cVObj mSub_0c0;                      // +0x0c0
    u8   mPad_0c4[0x4c];                 // 0x0c4 .. 0x10f
    u32  mdw_110;                        // +0x110
    u8   mPad_114[0x214];                // 0x114 .. 0x327
    u8   mb_328;                         // +0x328
    u8   mPad_329[0x27f];                // 0x329 .. 0x5a7
    cVObj mSub_5a8;                      // +0x5a8
    u8   mPad_5ac[0x574];                // 0x5ac .. 0xb1f
    cSpeciesProfile* mp_b20;             // +0x0b20
    u32  mdw_b24;                        // +0x0b24
    u8   mPad_b28[0x20];                 // 0x0b28 .. 0xb47
    cOrderMgr* mp_b48;                   // +0x0b48
    cVObj*     mp_b4c;                   // +0x0b4c
    u8   mPad_b50[4];                    // 0xb50 .. 0xb53
    cEffect*   mp_b54;                   // +0x0b54
    u32  mdw_b58;                        // +0x0b58
    u8   mb_b5c;                         // +0x0b5c
    u8   mPad_b5d[1];                    // 0xb5d
    u8   mb_b5e;                         // +0x0b5e
    u8   mb_b5f;                         // +0x0b5f
    u8   mPad_b60[3];                    // 0xb60 .. 0xb62
    u8   mb_b63;                         // +0x0b63
    u8   mPad_b64[0x10];                 // 0xb64 .. 0xb73
    f32  mf_b74;                         // +0x0b74
    f32  mf_b78;                         // +0x0b78
    f32  mf_b7c;                         // +0x0b7c
    f32  mf_b80;                         // +0x0b80
    f32  mf_b84;                         // +0x0b84
    u8   mPad_b88[0x29];                 // 0xb88 .. 0xbb0
    u8   mb_bb1;                         // +0x0bb1
    u8   mPad_bb2[2];                    // 0xbb2 .. 0xbb3
    cVObj* mp_bb4;                       // +0x0bb4
    u8   mPad_bb8[4];                    // 0xbb8 .. 0xbbb
    f32  mf_bbc;                         // +0x0bbc
    u8   mPad_bc0[0x2c];                 // 0xbc0 .. 0xbeb
    u32  mdw_bec;                        // +0x0bec
    u32  mdw_bf0;                        // +0x0bf0
    u32  mdw_bf4;                        // +0x0bf4
    u32  mdw_bf8;                        // +0x0bf8
    u32  mdw_bfc;                        // +0x0bfc
    u32  mdw_c00;                        // +0x0c00
    u32  mdw_c04;                        // +0x0c04
    u32  mdw_c08;                        // +0x0c08
    u32  mdw_c0c;                        // +0x0c0c
    u8   mPad_c10[0x18];                 // 0xc10 .. 0xc27
    cVec<cAbilityState_s00c1_c9f0> mAbilities;      // +0x0c28
    u8   mPad_c34[0x94];                 // 0xc34 .. 0xcc7
    cPHTable mTable_cc8;                 // +0x0cc8
    u8   mPad_cd8[0x90];                 // 0xcd8 .. 0xd67
    cPHTable mTable_d68;                 // +0x0d68
    u8   mPad_d78[0x90];                 // 0xd78 .. 0xe07
    cRBTree  mTree_e08;                  // +0x0e08
    u8   mPad_e20[4];                    // 0xe20 .. 0xe23
    cVec2 mVec_e24;                      // +0x0e24
    u8   mPad_e2c[0x2c];                 // 0xe2c .. 0xe57
    f32  mf_e58;                         // +0x0e58
    f32  mf_e5c;                         // +0x0e5c
    u8   mPad_e60[0x1c];                 // 0xe60 .. 0xe7b
    cDetach* mp_e7c;                     // +0x0e7c
    u8   mPad_e80[0xc];                  // 0xe80 .. 0xe8b
    u32  mdw_e8c;                        // +0x0e8c
    u32  mdw_e90;                        // +0x0e90
    f32  mf_e94;                         // +0x0e94
    cVec2 mVec_e98;                      // +0x0e98
    u8   mPad_ea0[0xc];                  // 0xea0 .. 0xeab
    cVObj* mp_eac;                       // +0x0eac
};
// ---- items of slice s00c1c9f0 end

// ---- items of slice s00c1f580 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl FUN_00921340(int which);
extern "C" void          __cdecl FUN_00c0d3a0(void* p);           // 0x00c0d3a0
extern "C" void*         __cdecl FUN_00c0ff80(void* a, void* b, void* c); // 0x00c0ff80
extern "C" void          __cdecl FUN_00572020(void* p, int flag); // 0x00572020
extern "C" void          __cdecl FUN_00c29b00(void* p);           // 0x00c29b00
extern wchar_t gEmptyString16[];        // 0x01667bac (eastl's empty 16-bit string)
extern float   gField13f1cac;           // 0x013f1cac
extern float   gHKRealOne;              // 0x01485720
extern float   gField13ec5b4;           // 0x013ec5b4
extern float   gVecBe0;                 // 0x0168d910
extern float   gVecBe4;                 // 0x0168d914
extern float   gVecBe8;                 // 0x0168d918
extern int     gField15716d4;           // 0x015716d4
extern int     gField15716d8;           // 0x015716d8
extern int     gField15716dc;           // 0x015716dc
extern int     gField15716e0;           // 0x015716e0
extern int     gField15716e4;           // 0x015716e4
struct Vector3_s00c1_f580 {
    float x;
    float y;
    float z;
};
class cReleaseable {
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
};
struct cCurvePoint {
    int          mIndex;      // +0x00
    int          mField04;    // +0x04
    int          mField08;    // +0x08
    int          mField0c;    // +0x0c
    int          mField10;    // +0x10
    int          mField14;    // +0x14   (deliberately not initialized)
    union {
        unsigned char mByte18;   // +0x18  low byte: "initialised" flag
        float         mField18;  // +0x18  full slot: sampled curve limit
    };
    int          mField1c;    // +0x1c
    cReleaseable* mpRef20;    // +0x20

    cCurvePoint()
        : mIndex(-1), mField04(0), mField08(0), mField0c(0), mField10(0),
          mByte18(0), mField1c(0), mpRef20(0) {
    }
    ~cCurvePoint() {
        if (mpRef20 != 0) {
            mpRef20->vc0();
        }
    }
};
class cCurvePointVector {
public:
    cCurvePoint* mpBegin;    // +0x00
    cCurvePoint* mpEnd;      // +0x04
    cCurvePoint* mpCapacity; // +0x08
    void*        mpFixed;    // +0x0c

    void  PushBackDefault();                                          // 0x00c1f650
    void  InsertValue(cCurvePoint* pos, const cCurvePoint* value);    // 0x00c1b990
    cCurvePoint* erase(cCurvePoint* first, cCurvePoint* last);        // 0x00ac4570
    void* FUN_00c144b0(void* a, void* b);                             // 0x00c144b0
    void  fn(void* a, void* b, void* c, int count);                   // 0x00b96360
};
class cCurveHolder : public cCurvePointVector {
public:
    int     mField10;    // +0x10
    Vector3_s00c1_f580 mPoint14;    // +0x14
    char    mPad20[0x38];// +0x20
    int     mField58;    // +0x58
    int     mField5c;    // +0x5c
    void  FUN_00c199e0(int value);   // 0x00c199e0
};
class cSampleRef {
public:
    char  mPad00[0x0c];
    float mField0c;      // +0x0c
};
class cVector3Vector {
public:
    Vector3_s00c1_f580* mpBegin;    // +0x00
    Vector3_s00c1_f580* mpEnd;      // +0x04
    Vector3_s00c1_f580* mpCapacity; // +0x08

    void DoInsertValue(Vector3_s00c1_f580* position, const Vector3_s00c1_f580* value);  // 0x004b5ad0

    void push_back(const Vector3_s00c1_f580& value) {
        Vector3_s00c1_f580* slot = mpEnd;
        if (slot < mpCapacity) {
            mpEnd = slot + 1;
            if (slot != 0) {
                *slot = value;
            }
        } else {
            DoInsertValue(slot, &value);
        }
    }
};
extern cVector3Vector gVec168e81c;      // 0x0168e81c
class eastl_fixed_pool_base {
public:
    void*   mpHead;    // +0x00
    void*   mpField04; // +0x04
    void*   mpField08; // +0x08
    void*   mpField0c; // +0x0c
    int     mCount10;  // +0x10
    void*   mpField14; // +0x14

    void init(void* pBegin, int size, int align, int count, int flag); // 0x00921260
    uint FUN_009213c0(void* value);                                    // 0x009213c0
};
struct cRange {
    float mMin;   // +0x00
    float mMax;   // +0x04

    cRange() {}
    cRange(float min, float max) : mMin(min), mMax(max) {}
};
class cCreatureDataBlock {
public:
    int          mPad00[2];      // +0x00
    uint         mCount08;       // +0x08
    void*        mpField0c;      // +0x0c
    cRange       mRange10;       // +0x10
    int          mField18;       // +0x18
    char         mPad1c[0x18];   // +0x1c
    int          mpField34;      // +0x34
    char         mPad38[0x14];   // +0x38
    char         mBuffer4c[0x30]; // +0x4c
    char         mPad7c[4];      // +0x7c

    cCreatureDataBlock* FUN_00c1f580(void* param2, void* param3);   // 0x00c1f580
    void FUN_00b5d220(uint n);                                  // 0x00b5d220
    void FUN_00c142a0(void* a1, void* a2, void* a3, void* a4, void* a5,
                      void* a6, void* a7);                      // 0x00c142a0
};
class cGameData_s00c1_f580 {
public:
    cGameData_s00c1_f580();
    // The primary vtable; slot 0x00..0xbc.  Slot 0xbc is the one the retail
    // teardown calls through "this".
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
    void* mpSecondaryVtbl;   // +0x04
};
class cPropertyBag {
public:
    int FUN_00c14350();     // 0x00c14350
};
extern "C" uint          __cdecl FNVHash(const char* name, uint start, int flag); // 0x00932e80
extern "C" float         __cdecl SP_GetPropertyT_float(uint hashA, int zero, uint hashB, float fallback); // 0x00bcea30
extern "C" cPropertyBag* __cdecl FUN_00b3d310_s00c1_f580();                  // 0x00b3d310
class cBehaviorTreeData {
public:
    // Class-specific allocation: the retail constructor passes the size, an
    // allocation name and four zeroed debug/alignment parameters.
    static void* operator new(size_t size,
                              const char* name = "Simulator/cBehaviorTreeData",
                              int flags = 0, unsigned align = 0,
                              const char* file = 0, int line = 0);
    cBehaviorTreeData();          // 0x00bcb2a0
    virtual void bt0();
    void FUN_00bcb3d0();          // 0x00bcb3d0
};
class cFieldB48 {
public:
    void FUN_00bc9fe0();   // 0x00bc9fe0
};
class cBundle34 {
public:
    cBundle34();
    virtual void b00();
    void FUN_00cee7e0();    // 0x00cee7e0
    char mPad04[0x20];      // +0x04 -> 0x24
};
class cMotion58 {
public:
    cMotion58();
    virtual void m00();
    void FUN_00abf710();    // 0x00abf710
    char mPad04[0x64];      // +0x04 -> 0x68
};
class cSampleC0 {
public:
    cSampleC0();
    virtual void sc00();
    cCurveHolder* FUN_00c41ec0();     // 0x00c41ec0
    cSampleRef*   FUN_00c421f0();     // 0x00c421f0
    void FUN_00c421b0(int value);  // 0x00c421b0

    char  mPad04[0x4c];      // +0x04
    int   mFlags50;          // +0x50   (bit 0x200 = "armed")
    int   mField54;          // +0x54
    char  mPad58[0x7c];      // +0x58
    void* mpVtblD4;          // +0xd4   (secondary vtable slot)
    int   mFieldD8;          // +0xd8
    int   mFieldDc;          // +0xdc
    char  mPadE0[0x104];     // +0xe0
    float mField1e4;         // +0x1e4
    int   mField1e8;         // +0x1e8
    int   mField1ec;         // +0x1ec
    int   mField1f0;         // +0x1f0
    char  mPad1f4[0x2dc];    // +0x1f4 -> 0x4d0
};
class cInteractionTarget {
public:
    cInteractionTarget();
    virtual void it00();
    void FUN_00ac0450();    // 0x00ac0450
    char mPad04[0x14];      // +0x04 -> 0x18
};
class cCombatant_s00c1_f580 {
public:
    cCombatant_s00c1_f580();
    virtual void cb00();

    char  mPad04[0x28];      // +0x04
    float mHealth2c;         // +0x2c   (creature health)
    int   mField30;          // +0x30
    int   mField34;          // +0x34
    float mCombat38;         // +0x38   (combat strength)
    char  mPad3c[0x8c];      // +0x3c -> 0xc8
};
class cGonzagoTimer {
public:
    cGonzagoTimer();
    virtual void gt00();
    void FUN_00bc3170();     // 0x00bc3170

    char  mPad04[0x1c];      // +0x04
    float mField20;          // +0x20
    int   mField24;          // +0x24
    float mField28;          // +0x28
    float mField2c;          // +0x2c   (100.0f)
};
class cField670 {
public:
    cField670();
    virtual void f670();

    char          mPad04[0x49c];   // +0x04
    unsigned char mByte4a0;        // +0x4a0
    char          mPad4a1[7];      // +0x4a1
    unsigned char mByte4a8;        // +0x4a8
    char          mPad4a9[7];      // +0x4a9
    int           mField4b0;       // +0x4b0
    int           mField4b4;       // +0x4b4
    int           mField4b8;       // +0x4b8
    int           mField4bc;       // +0x4bc
    int           mField4c0;       // +0x4c0
    int           mField4c4;       // +0x4c4
    wchar_t*      mpStr4c8;        // +0x4c8   (empty wide string)
    wchar_t*      mpStr4cc;        // +0x4cc
    wchar_t*      mpStr4d0;        // +0x4d0
    int           mField4d4;       // +0x4d4
    cFieldB48*    mpField4d8;      // +0x4d8
    cBehaviorTreeData* mpTree4dc;  // +0x4dc
    cReleaseable* mpField4e0;      // +0x4e0
    int           mField4e4;       // +0x4e4
    int           mField4e8;       // +0x4e8
    unsigned char mBytes4ec[8];    // +0x4ec
    unsigned char mByte4f4;        // +0x4f4
    unsigned char mBytes4f5[3];    // +0x4f5
    unsigned char mByte4f8;        // +0x4f8
    unsigned char mByte4f9;        // +0x4f9
    char          mPad4fa[2];      // +0x4fa
    void*         mpField4fc;      // +0x4fc
    int           mField500;       // +0x500
    int           mField504;       // +0x504
    char          mPad508[4];      // +0x508
    float         mField50c;       // +0x50c
    float         mField510;       // +0x510
    float         mField514;       // +0x514
    int           mField518;       // +0x518
    int           mField51c;       // +0x51c -> 0x520
};
class cSPCreatureBase_s00c1_f580 : public cGameData_s00c1_f580 {
public:
    cSPCreatureBase_s00c1_f580();  // 0x00c1f8d0 (cSPCreatureBase::cSPCreatureBase_s00c1_f580)
    ~cSPCreatureBase_s00c1_f580();  // 0x00c1f8d0 (cSPCreatureBase::cSPCreatureBase_s00c1_f580)

    void  FUN_00c1fe80();                       // 0x00c1fe80
    void  FUN_00c19940(int value);              // 0x00c19940
    void  FUN_00c13340();                       // 0x00c13340
    float ce80(int a, int b);                   // 0x00c0ce80  (?ce80@CCB@@QAEMHH@Z)
    void  cff0(int value);                       // 0x00c0cff0  (?cff0@CCB@@QAEXH@Z)

    char               mPad08[0x2c];   // +0x08
    cBundle34          mBundle34;      // +0x34
    cMotion58          mMotion58;      // +0x58
    cSampleC0          mSampleC0;      // +0xc0
    cInteractionTarget mTarget590;     // +0x590
    cCombatant_s00c1_f580         mCombatant5a8;  // +0x5a8
    cField670          mField670;      // +0x670
    cGonzagoTimer      mTimerB90;      // +0xb90
    cCurvePointVector  mCurvesBc0;     // +0xbc0
    char               mPadBd0[0x10];  // +0xbd0
    float              mFieldBe0;      // +0xbe0
    float              mFieldBe4;      // +0xbe4
    float              mFieldBe8;      // +0xbe8
    int                mFieldBec;      // +0xbec
    int                mFieldBf0;      // +0xbf0
    int                mFieldBf4;      // +0xbf4
    int                mFieldBf8;      // +0xbf8
    int                mFieldBfc;      // +0xbfc
    int                mFieldC00;      // +0xc00
    int                mFieldC04;      // +0xc04
    int                mFieldC08;      // +0xc08
    int                mFieldC0c;      // +0xc0c
    char               mPadC10[0x18];  // +0xc10
    uint*              mpFixedBegin;   // +0xc28
    uint*              mpFixedEnd;     // +0xc2c
    uint*              mpFixedCapacity;// +0xc30
    char               mPadC34[8];     // +0xc34
    int                mFieldC3c;      // +0xc3c
    char               mFixedBuffer[0x80]; // +0xc40
    void*              mpFieldCc0;     // +0xcc0
    void*              mpFieldCc4;     // +0xcc4
    cCreatureDataBlock mBlockCc8;      // +0xcc8
    cCreatureDataBlock mBlockD68;      // +0xd68
    void*              mpFieldE08;     // +0xe08
    void*              mpFieldE0c;     // +0xe0c
    void*              mpFieldE10;     // +0xe10
    int                mFieldE14;      // +0xe14
    int                mFieldE18;      // +0xe18
    int                mFieldE1c;      // +0xe1c
    char               mPadE20[4];     // +0xe20
    int                mFieldE24;      // +0xe24
    int                mFieldE28;      // +0xe28
    int                mFieldE2c;      // +0xe2c
    char               mPadE30[8];     // +0xe30
    unsigned char      mByteE38;       // +0xe38
    char               mPadE39[3];     // +0xe39
    int                mFieldE3c;      // +0xe3c
    cCurvePointVector  mCurvesE40;     // +0xe40
    char               mPadE4c[8];     // +0xe4c
    int                mFieldE54;      // +0xe54
    float              mFieldE58;      // +0xe58
    float              mFieldE5c;      // +0xe5c
    unsigned char      mBytesE60[4];   // +0xe60
    int                mFieldE64;      // +0xe64
    unsigned char      mByteE68;       // +0xe68
    char               mPadE69[3];     // +0xe69
    int                mFieldE6c;      // +0xe6c
    int                mFieldE70;      // +0xe70
    int                mFieldE74;      // +0xe74
    unsigned char      mByteE78;       // +0xe78
    char               mPadE79[3];     // +0xe79
    cReleaseable*      mpFieldE7c;     // +0xe7c
    int                mFieldE80;      // +0xe80
    int                mFieldE84;      // +0xe84
    int                mFieldE88;      // +0xe88
    int                mFieldE8c;      // +0xe8c
    int                mFieldE90;      // +0xe90
    float              mFieldE94;      // +0xe94
    int                mFieldE98;      // +0xe98
    int                mFieldE9c;      // +0xe9c
    int                mFieldEa0;      // +0xea0
    char               mPadEa4[8];     // +0xea4
    int                mFieldEac;      // +0xeac
    char               mPadEb0[4];     // +0xeb0
    int                mFieldEb4;      // +0xeb4
    char               mPadEb8[0x20];  // +0xeb8
    int                mFieldEd8;      // +0xed8
    int                mFieldEdc;      // +0xedc
    int                mFieldEe0;      // +0xee0
    char               mPadEe4[4];     // +0xee4
    int                mFieldEe8;      // +0xee8
    char               mPadEec[0x20];  // +0xeec
    int                mFieldF0c;      // +0xf0c
    int                mFieldF10;      // +0xf10
    int                mFieldF14;      // +0xf14
    char               mPadF18[4];     // +0xf18
    int                mFieldF1c;      // +0xf1c
    char               mPadF20[0x20];  // +0xf20
    int                mFieldF40;      // +0xf40
    int                mFieldF44;      // +0xf44
    int                mFieldF48;      // +0xf48
    char               mPadF4c[4];     // +0xf4c
    int                mFieldF50;      // +0xf50
    char               mPadF54[0x20];  // +0xf54
    int                mFieldF74;      // +0xf74
    int                mFieldF78;      // +0xf78
    int                mFieldF7c;      // +0xf7c
    int                mFieldF80;      // +0xf80
    void*              mpFieldF84;     // +0xf84
    void*              mpFieldF88;     // +0xf88
    int                mFieldF8c;      // +0xf8c
    unsigned char      mByteF90;       // +0xf90
    char               mPadF91[3];     // +0xf91
    int                mFieldF94;      // +0xf94
    int                mFieldF98;      // +0xf98
    int                mFieldF9c;      // +0xf9c
    int                mFieldFa0;      // +0xfa0
    int                mFieldFa4;      // +0xfa4
    float              mFieldFa8;      // +0xfa8
    float              mFieldFac;      // +0xfac
    float              mFieldFb0;      // +0xfb0
    float              mFieldFb4;      // +0xfb4
    int                mFieldFb8;      // +0xfb8
};
class cCreaturePart {
public:
    void FUN_00c1ffb0(char enable);   // 0x00c1ffb0

    char    mPad00[0xd4];  // +0x00
    Vector3_s00c1_f580 mAnchorD4;     // +0xd4   (first point appended to the anchor vector)
    Vector3_s00c1_f580 mAnchorE0;     // +0xe0   (second point)
    char    mPadEc[0xb0];  // +0xec
    int     mField19c;     // +0x19c   (state bits, bit 2 = "disabled")
    char    mPad1a0[0x88c];// +0x1a0
    Vector3_s00c1_f580* mpCurveBeginA2c; // +0xa2c   (creature's +0xbc0)
    Vector3_s00c1_f580* mpCurveEndA30;   // +0xa30   (creature's +0xbc4)
    char    mPadA34[0x3d4];   // +0xa34
    int     mFieldE08;     // +0xe08   (creature's +0xf9c)
};
class cCreatureFactory {
public:
    void* FUN_00c14e70(void* arg);                  // 0x00c14e70
    void  FUN_00c17350(void* arg, int zero);        // 0x00c17350
    void* FUN_00c1d120(void* a, void* b);           // 0x00c1d120
    void* FUN_00c201a0(char flag, void* a, void* b); // 0x00c201a0
    void  FUN_00c20210(void* a, void* b);           // 0x00c20210
};
class cFactoryObject {
public:
    virtual void o00();
    virtual void o04();
    virtual void o08(void* arg);
    virtual void o0c();
    virtual bool o10();
};
// ---- items of slice s00c1f580 end

// ---- items of slice s00c22010 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern uint32_t g_kBodyParts;  // 0x015716e8
extern uint8_t g_168D904; // 0x0168d904
#define PVN(n) virtual void pv##n();
namespace EA {
namespace Random {
class RandomLinearCongruential_s00c2_2010 {
public:
    uint32_t RandomUint32Uniform(uint32_t nLimit);   // 0x00a68fb0
};
}
}
extern EA::Random::RandomLinearCongruential_s00c2_2010 sMathRandom;  // 0x01601760
int     FUN_009b2340_s00c2_2010(void* pOut, int nMax, void* pObj, void* pFlags, int, int);   // 0x009b2340
void    FUN_00c1f6d0(int* pPos, int a, int b, int value); // 0x00c1f6d0  fixed_vector append
void    FUN_00f47380(void* p);                            // 0x00f47380  operator delete[]
class cSpeciesProfile_s00c2_2010;
class cSPCreatureBase_s00c2_2010;
class cInteractionTarget_s00c2_2010;
class cBehaviorStimuliOwner;
class cInteractionAgent;
class cSpeciesProfile_s00c2_2010 {
public:
    uint8_t  mPad000[0x504];    // +0x000
    float    mf0504;            // +0x504
    float    mf0508;            // +0x508
    float    mf050C;            // +0x50c
    uint8_t  mPad510[0x53c - 0x510];
    uint32_t mn053C;            // +0x53c
    uint8_t  mPad540[0x56c - 0x540];
    float    mf056C;            // +0x56c
    uint8_t  mPad570[0x590 - 0x570];
    float    mf0590;            // +0x590
    float    mf0594;            // +0x594
    uint8_t  mPad598[0x634 - 0x598];
    int      mn0634;            // +0x634

    void*    FUN_004d9050(void* pAnim);   // 0x004d9050
    void*    FUN_004d9030(void* pAnim);   // 0x004d9030
    void*    FUN_004d5500(const void* pKey);  // 0x004df550  (species manager method)
};
struct ResourceKey { uint32_t mA; uint32_t mB; uint32_t mC; };
class cSpeciesManager {
public:
    cSpeciesProfile_s00c2_2010* GetProfile(const ResourceKey& key);     // 0x004df550
    cSpeciesProfile_s00c2_2010* GetAvatarProfile();                     // 0x004df420
    void* GetSpeciesArchetype(void* pKey, int nSomething);   // 0x004e0050
    char  GetReplacementKey(const ResourceKey& key, uint32_t nMode, ResourceKey* pOut);  // 0x004df7d0
};
class cLocoWrapper {
public:
    void FUN_00b48770(void* pCreature, int nFlag);   // 0x00b48770
};
class cObj0xA8C {
public:
    uint8_t  mPad0[0x5fc];      // +0x000
    uint32_t mn05FC;            // +0x5fc
};
class cSpeciesArchetype {
public:
    uint8_t mPad0[0x388];       // +0x000
    uint8_t mb0388;             // +0x388
};
class cAnimatingCreature {
public:
    uint8_t mPad0[0x17c];       // +0x000
    void*   mp017C;             // +0x17c
};
class cBehaviorStimuliOwner {
public:
    uint8_t  mPad000[0x88];            // +0x000
    uint8_t  mEntries[0x1d0 - 0x88];   // +0x088
    int      mn01D0;            // +0x1d0
    int      mn01D4;            // +0x1d4
    int      mn01D8;            // +0x1d8
    uint32_t mn01DC;            // +0x1dc

    int GetStimulusId() const { return *(const int*)((const char*)mEntries + mn01DC * 0xac); }
};
class cInteractionTarget_s00c2_2010 {
public:
    uint8_t mPad000[0x34];         // +0x000
    uint8_t mSub34[0x12c - 0x34];  // +0x034 (sub-object passed to FUN_00c15d50)
    int     mnType12C;             // +0x12c
    int     mn0130;                // +0x130
    float   mf0134;                // +0x134
    int     GetAttackState();      // 0x00c35b60
};
class cSub58 {
public:
    PVN(0) PVN(1) PVN(2) PVN(3) PVN(4) PVN(5) PVN(6) PVN(7) PVN(8) PVN(9)
    PVN(10) PVN(11) PVN(12)
    virtual void vIdx13();       // 0x34
    uint8_t mPad04[0x40 - 4];    // +0x04 .. +0x3f
};
class cGameData_s00c2_2010 {
public:
    PVN(0) PVN(1) PVN(2) PVN(3) PVN(4) PVN(5) PVN(6) PVN(7) PVN(8) PVN(9)
    PVN(10) PVN(11)
    virtual void* vIdx12();      // 0x30
    virtual void  vIdx13(int);   // 0x34
    virtual void  vIdx14(int);   // 0x38
    PVN(15) PVN(16) PVN(17) PVN(18) PVN(19)
    virtual void  vIdx20();      // 0x50
    PVN(21) PVN(22) PVN(23) PVN(24) PVN(25) PVN(26) PVN(27) PVN(28) PVN(29)
    PVN(30) PVN(31)
    virtual float vIdx32(int);   // 0x80
    PVN(33) PVN(34) PVN(35) PVN(36) PVN(37) PVN(38) PVN(39) PVN(40) PVN(41) PVN(42)
    virtual void  vIdx43(int);   // 0xac
    PVN(44)
    virtual void* vIdx45(int);   // 0xb4
    PVN(46)
    PVN(47) PVN(48) PVN(49) PVN(50) PVN(51) PVN(52) PVN(53)
    virtual int   vIdx54();      // 0xd8
    PVN(55) PVN(56) PVN(57) PVN(58) PVN(59)
    virtual void  vIdx60(int);   // 0xf0
    uint8_t mPad00[0x30];        // +0x04 .. +0x33
};
class cInteractionAgent {
public:
    PVN(0) PVN(1) PVN(2) PVN(3) PVN(4) PVN(5) PVN(6) PVN(7) PVN(8) PVN(9)
    PVN(10) PVN(11)
    virtual void  ia30(void* pArg);            // 0x30
    PVN(13)
    virtual float GetBundleCapacity(uint32_t nToolType);  // 0x38

    void*  mpListBegin;          // +0x04
    void*  mpListEnd;            // +0x08
    uint8_t mPad0c[0x18 - 0x0c]; // +0x0c
    void*  mp0x18;               // +0x18
    uint8_t mPad1c[0x20 - 0x1c];
    float  mf0x20;               // +0x20
    cSub58 mSub58;               // +0x24
    uint8_t mPad64[0x89 - 0x64]; // +0x64
    uint8_t mb0x89;              // +0x89
    uint8_t mPad8a[0x8c - 0x8a]; // +0x8a

    float FUN_00c22530();                 // 0x00c22530
    void  FUN_010829f0(void* pArg);       // 0x010829f0
    void  FUN_00c22f60(void* pArg);       // 0x00c22f60
};
class cLocomotiveObject {
public:
    PVN(0) PVN(1) PVN(2) PVN(3) PVN(4) PVN(5) PVN(6) PVN(7) PVN(8) PVN(9)
    PVN(10) PVN(11) PVN(12) PVN(13) PVN(14) PVN(15)
    virtual void lo40(float fScale);    // 0x40
    PVN(17) PVN(18) PVN(19)
    virtual char lo50();                // 0x50
    PVN(21)
    virtual char lo58();                // 0x58

    uint8_t mPad04[0x6c - 0x04]; // +0x04
    uint8_t mb0x6c;              // +0x6c
    uint8_t mPad6d[0x75 - 0x6d]; // +0x6d
    uint8_t mb0x75;              // +0x75
    uint8_t mPad76[0x4e8 - 0x76];// +0x76

    void FUN_00c226c0(char nFlag);   // 0x00c226c0
};
class cCombatant_s00c2_2010 {
public:
    PVN(0) PVN(1) PVN(2) PVN(3) PVN(4) PVN(5) PVN(6) PVN(7) PVN(8) PVN(9)
    PVN(10) PVN(11) PVN(12) PVN(13) PVN(14) PVN(15) PVN(16) PVN(17) PVN(18)
    PVN(19) PVN(20) PVN(21)
    virtual float GetMaxHealth();        // 0x58

    uint8_t mPad04[0x34 - 0x04]; // +0x04
    void*   mp0x34;              // +0x34
    float   mf0x38;              // +0x38
    uint8_t mPad3c[0x40 - 0x3c]; // +0x3c

    float GetHealthRatio();              // 0x00bfc490
    void  PartialRepair(float fAmount);  // 0x00bfd1a0
    void  SetHealth(float fValue);       // 0x00f924e0
    int   FUN_00c22010();                // 0x00c22010
};
class cFixedVectorInt8 {
public:
    int* mpBegin;                // +0x00
    int* mpEnd;                  // +0x04
    int* mpCap;                  // +0x08
    int  mBuffer[8];             // +0x0c
    void DoInsertValue(int* pPos, const int& value);   // 0x004281d0
};
class cSPCreatureBase_s00c2_2010 : public cGameData_s00c2_2010, public cInteractionAgent,
                        public cLocomotiveObject, public cCombatant_s00c2_2010 {
public:
    // own members, from +0x5e8
    uint8_t  mPad5e8[0xa8c - 0x5e8];
    cObj0xA8C* mp0xA8C;          // +0xa8c
    uint8_t  mPadA90[0xb20 - 0xa90];
    cSpeciesProfile_s00c2_2010* mpSpeciesProfile;  // +0xb20
    uint32_t mn0xB24;            // +0xb24
    ResourceKey mKey0xB28;       // +0xb28
    int      mn0xB34;            // +0xb34 (age)
    uint8_t  mPadB38[0xb48 - 0xb38];
    void*    mp0xB48;            // +0xb48  (object with FUN_00bc9fe0)
    cBehaviorStimuliOwner* mpB4C;// +0xb4c
    uint8_t  mPadB50[0xb54 - 0xb50];
    cAnimatingCreature* mp0xB54; // +0xb54
    uint8_t  mPadB58[0xb67 - 0xb58];
    uint8_t  mb0xB67;            // +0xb67
    uint8_t  mPadB68[0xbbc - 0xb68];
    float    mf0xBBC;            // +0xbbc
    uint8_t  mPadBC0[0xe70 - 0xbc0];
    int      mn0xE70;            // +0xe70
    int      mn0xE74;            // +0xe74
    uint8_t  mPadE78[0xe80 - 0xe78];
    void*    mp0xE80;            // +0xe80
    cSpeciesArchetype* mp0xE84;  // +0xe84
    uint8_t  mPadE88[0xfc4 - 0xe88];
    int      mn0xFC4;            // +0xfc4
    uint8_t  mPadFC8[0xff8 - 0xfc8];
    int      mn0xFF8;            // +0xff8
    uint8_t  mPadFFC[0x1004 - 0xffc];
    float    mf0x1004;           // +0x1004
    float    mf0x1008;           // +0x1008
    float    mf0x100C;           // +0x100c
    uint8_t  mPad1010[0x1014 - 0x1010];
    void*    mp0x1014;           // +0x1014
    uint8_t  mPad1018[0x102c - 0x1018];
    int      mn0x102C;           // +0x102c

    // ---- helper calls (thiscall) ----
    void  FUN_00c21bf0(int a, int b);            // 0x00c21bf0  CheckCreatureModel
    char  FUN_00c0c2d0();                        // 0x00c0c2d0  IsDefaultSpecies_
    float FUN_00c0b9c0();                        // 0x00c0b9c0
    void  FUN_00c0b9d0(float fValue);            // 0x00c0b9d0
    char  FUN_00c0bab0();                        // 0x00c0bab0
    char  FUN_00c0ba30();                        // 0x00c0ba30
    int   FUN_00c0c080(int nId);                 // 0x00c0c080  FindIndex
    char  FUN_00b183f0(void* pArg);              // 0x00b183f0
    void  FUN_00c1d640(const char* pVox, int a, int b);  // 0x00c1d640
    void  FUN_00c15d50(void* pArg, int a, int b);        // 0x00c15d50
    void  FUN_00c42350();                        // 0x00c42350
    char  FUN_00c0e0c0(int nType);                       // 0x00c0e0c0
    void  FUN_00c14aa0(void* pStream);                   // 0x00c14aa0
    void  FUN_00c0bc20Write(void* pStream);              // 0x00c0bc20  cSPCreatureBase::Write

    // ---- sliced members ----
    void  FUN_00c22210(int nAge);                        // 0x00c22210
    void  FUN_00c22240();                                // 0x00c22240
    void  FUN_00c222f0(cSpeciesProfile_s00c2_2010* pNew);           // 0x00c222f0
    bool  FUN_00c22470(void* pArg);                      // 0x00c22470
    float GetBaseMaxHitPoints();                         // 0x00c22720
    char  FUN_00c22750();                                // 0x00c22750
    void  FUN_00c227c0();                                // 0x00c227c0
    void  FUN_00c227f0(int x, int y, int z);            // 0x00c227f0
    int   FUN_00c22830(int nValue);                      // 0x00c22830
    void  FUN_00c22870();                                // 0x00c22870
    void  FUN_00c228c0Write(void* pStream);              // 0x00c228c0
    void  FUN_00c22930Read(void* pStream);               // 0x00c22930
    char  FUN_00c229a0();                                // 0x00c229a0
    void  FUN_00c22a30();                                // 0x00c22a30
    char  FUN_00c22a80(cInteractionTarget_s00c2_2010* pTarget);     // 0x00c22a80
    void  FUN_00c22ae0();                                // 0x00c22ae0
    char  FUN_00c22ca0(int nType);                       // 0x00c22ca0
    void  FUN_00c22cb0(uint32_t nVox);                   // 0x00c22cb0
    int   FUN_00c22dd0();                                // 0x00c22dd0
    void  FUN_00c22ee0(void* pObj);                      // 0x00c22ee0
};
class cObj0xB48 {
public:
    void FUN_00bc9fe0();     // 0x00bc9fe0
};
// ---- items of slice s00c22010 end

// ---- items of slice s00c053b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
void* __cdecl FUN_00c06000();                                 // 0x00c06000
struct Fn421b0 { void __thiscall f(void*); };   // 0x00c421b0
struct Fn44040 { void __thiscall f(); };         // 0x00c44040
struct Fn43fe0 { void __thiscall f(void*); };    // 0x00c43fe0
struct CB_s00c0_53b0 {
    uint8_t  pad0[0xc0];
    uint8_t  padloc[0xb54 - 0xc0];       // +0xc0 locomotion subobject
    void*    mpStrat;                    // +0xb54  locomotion strategy obj
    uint32_t mGeneralFlags;              // +0xb58
    uint8_t  pad1[0x1000 - 0xb5c];
    float    mField1000;                 // +0x1000

    void func74h(int param_2, int param_3);     // 0x00c053b0
    void func58h(float dt);                     // 0x00c05810
    void func5a8h(int param_2);                 // 0x00c05a80
    float func5bf0();                           // 0x00c05bf0
    char func5d40(int param_2);                 // 0x00c05d40
    void func6500();                            // 0x00c06500
    float GetRankThunk(int param_2);            // 0x00c06320
    void  RankForward(int param_2);             // 0x00c06340
};
// ---- items of slice s00c053b0 end

// ---- items of slice s00c06630 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef void* P;
struct E32 { uint32_t d[8]; };
void __cdecl FUN_011e0744(void*, const void*, size_t);
#define memmove(d, s, n) FUN_011e0744((d), (s), (n))
struct Pool { void __thiscall Alloc(void*); };                 // 0x00c06070
struct VObj { virtual void v0(); virtual void v1(); virtual void v2(); };
void __cdecl FUN_00c06120(P*, P*, P);                          // 0x00c06120
void __cdecl FUN_00c06160(P*, P*, P);                          // 0x00c06160
void __cdecl FUN_00c04960(P*, int, int, int, P, P);            // 0x00c04960
E32* __cdecl FUN_00c033a0(E32*, E32*, E32*);                   // 0x00c033a0
void* __cdecl operator_new(size_t, const char*, int, int, const char*, int); // 0xf473a0
void  __cdecl FUN_00ac4190(int);                               // 0x00ac4190
void  __cdecl FUN_00d7ca90(void*);                             // 0x00d7ca90
void* __cdecl FUN_00b18530(void*);                             // 0x00b18530
void* __cdecl FUN_00f3c0e0(void*);                             // 0x00f3c0e0
void  __cdecl FUN_00d9a290(void*, void*, void*);               // 0x00d9a290
void  __cdecl FUN_00bc97f0(void*, int, int, float, int);       // 0x00bc97f0
struct BaseCtor   { void __thiscall ctor(); };                 // 0x00c1f8d0
struct Gonzago    { void __thiscall ctor(); };                 // 0x00b63890
struct SPTimer    { void __thiscall Restart(); };              // 0x00bc3130
struct Fnbc9c10   { void __thiscall ctor(); };                 // 0x00bc9c10
struct Fn1fe80    { void __thiscall f(); };                    // 0x00c1fe80
struct Fn9de0     { void __thiscall f(int); };                 // 0x00bc9de0
struct Fn05ee0    { void __thiscall f(); };                    // 0x00c05ee0
struct Fn1c9f0    { void __thiscall f(int); };                 // 0x00c1c9f0
struct Fn3170     { void __thiscall f(); };                    // 0x00bc3170
struct Fnbfc470   { void __thiscall f(uint8_t); };             // 0x00bfc470
struct Fnbfc460   { void __thiscall f(int); };                 // 0x00bfc460
struct Fn8e7f80   { int  __thiscall f(); };                    // 0x008e7f80
struct Fnc0c0e0   { bool __thiscall f(int,int); };             // 0x00c0c0e0
struct Fnc12310   { void __thiscall f(int); };                 // 0x00c12310
struct Fnf25080   { bool __thiscall f(void*); };               // 0x00f25080
struct Fnc7dc20   { void __thiscall f(); };                    // 0x00c7dc20
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
#define ERASE_ALL(self, off) do { \
    P* end_ = *(P**)((char*)(self)+(off)+4); \
    P* beg_ = *(P**)((char*)(self)+(off)); \
    memmove(beg_, end_, (char*)end_ - (char*)end_); \
    int d_ = (int)end_ - (int)beg_; d_ >>= 2; d_ = -d_; d_ += d_; d_ += d_; \
    *(int*)((char*)(self)+(off)+4) += d_; } while(0)
struct VErase { P* mpBegin; P* mpEnd; P* mpCapacity;
    void** __thiscall erase(void** first, void** last); };
struct V32 { E32* mpBegin; E32* mpEnd; E32* mpCapacity;
    void __thiscall push_back(E32* p);
    void __thiscall insert(E32* pos, E32* val); };
struct CCAnimal { char pad[0x1700]; void __thiscall Ctor(); };
struct CCBeh { char pad[0x1700]; void __thiscall funcC4h(); };
struct CCCh { char pad[0x1700]; void __thiscall funcCCh(int a); };
struct CTick { char pad[0x1700]; void __thiscall Tick(); };
struct V32B { E32* mpBegin; E32* mpEnd; E32* mpCapacity;
    void __thiscall push_back(E32* p); };
struct V4Stub { P* a; P* b; P* c; void __thiscall insert(P*, P*); }; // 0x00b96600
struct V4 { P* mpBegin; P* mpEnd; P* mpCapacity;
    void __thiscall push_back(P* p); };
struct CSetId { char pad[0x1700]; void __thiscall set(int id); };
// ---- items of slice s00c06630 end

// ---- items of slice s00c07480 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" long __cdecl _InterlockedExchange(volatile long* target, long value);
extern float kCharmThreshold;                       // 0x01582fe4
extern float kCharmThresholdEpic;                   // 0x01582fe8
extern float kCharmDuration;                        // 0x01582fec
extern float kAvatarProvokeTime;                    // 0x01582f84
#pragma warning(disable: 4100)
#pragma intrinsic(_InterlockedExchange)
enum {
    kGameCreature = 0x1654C01,
    kGameTribe    = 0x1654C02,
    kGameCiv      = 0x1654C04,
    kScenarioMode = 0x1654C10,
};
enum {
    kCreatureBaseType   = 0xCE9F6639,   // cCreatureBase::TYPE
    kCreatureAnimalNoun = 0x18EB45E,    // cCreatureAnimal::NOUN_ID
};
struct Vector3_s00c0_7480 { float x, y, z; };
struct ResourceKey_s00c0_7480 {
    uint32_t instanceID, typeID, groupID;
    ResourceKey_s00c0_7480() {}
    ResourceKey_s00c0_7480(uint32_t i, uint32_t t, uint32_t g) : instanceID(i), typeID(t), groupID(g) {}
};
struct cSPTimer {
    uint32_t data[8];
    void Restart();                 // 0x00bc3130
    bool IsRunning();               // 0x00feba90
    uint64_t GetElapsedTime();      // 0x00bc3190
};
struct cSpeciesProfile_s00c0_7480 {
    uint32_t pad[0x504 / 4];
    ResourceKey_s00c0_7480 mCreatureKey;       // 0x504
};
struct cBehaviorEvent {
    uint32_t pad[3];
    int field_0C;
    int field_10;
    int field_14;
};
struct cBehaviorEvents {
    cBehaviorEvent* Add(int type, int arg, float priority, void* source);   // 0x00bc97f0
};
struct cBehaviorPerception {
    void Alert(int type, float radius, void* source, int arg);              // 0x00bc9d40
};
struct cBehaviorSubTree { uint32_t pad[0x10 / 4]; int field_10; };
struct cBehaviorTreeData_s00c0_7480 {
    uint32_t pad[8 / 4];
    cBehaviorEvents mEvents;        // 0x08
    uint32_t pad0c[(0x1d8 - 0xc) / 4];
    uint32_t mTreeID;               // 0x1d8
    uint32_t pad1dc[(0x600 - 0x1dc) / 4];
    cBehaviorSubTree* field_600;    // 0x600
};
struct cAnimationQueue {
    int Find(int a, int b, int c, int d);   // 0x00bca0c0
    void Stop(int index);                   // 0x00bca040
};
class cCombatant_s00c0_7480;
class cCreatureBase_s00c0_7480;
class cGameData_s00c0_7480 {
public:
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
    virtual uint32_t GetNounID();                   // 0x20
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
    virtual uint32_t GetPoliticalID();              // 0x4c
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
    virtual void AttackTarget(cCombatant_s00c0_7480* target, int a, int b);   // 0x84
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
    virtual bool IsBusy();                          // 0xd0
    uint32_t gameDataFields[0x30 / 4];
    uint32_t creatureBases34[(0xc0 - 0x34) / 4];    // cGameBundleContainer, cBehaviorAgent
};
class cLocomotiveObject_s00c0_7480 {
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
    virtual const Vector3_s00c0_7480& GetPosition();           // 0x2c
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
    virtual bool IsMoving();                        // 0x58
virtual void v5c();
virtual void v60();
virtual void v64();
virtual void v68();
virtual void v6c();
virtual void v70();
    virtual float GetBoundingRadius();              // 0x74
    uint32_t pad04[(0x590 - 0xc4) / 4];
    uint32_t behaviorList[(0x5a8 - 0x590) / 4];     // cBehaviorList base
};
class cCombatant_s00c0_7480 {
public:
virtual void v00();
virtual void v04();
virtual void v08();
    virtual cGameData_s00c0_7480* ToGameData();                // 0x0c
virtual void v10();
virtual void v14();
    virtual void TakeDamage(float damage, uint32_t attackerPoliticalID, int damageType,
                            const Vector3_s00c0_7480& direction, cCombatant_s00c0_7480* pAttacker);   // 0x18
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
    virtual void* Cast(uint32_t type);              // 0x5c

    int GetDamageState();                           // 0x008e7f80 (returns field_34; 2 = dead)
    uint32_t pad04[(0xc8 - 4) / 4];
};
struct cCombatantPtr {
    cCombatant_s00c0_7480* mpObject;
    cCombatant_s00c0_7480* get() const { return mpObject; }
    cCombatantPtr& operator=(cCombatant_s00c0_7480* p);        // 0x00ae6690
};
class cCreatureBase_s00c0_7480 : public cGameData_s00c0_7480, public cLocomotiveObject_s00c0_7480, public cCombatant_s00c0_7480 {
public:
    bool IsEpic();                                  // 0x00c0c0e0
    bool IsBaby();                                  // 0x00c0b770
    const ResourceKey_s00c0_7480* GetSpeciesKey();             // 0x00c0bc00
    cSpeciesProfile_s00c0_7480* GetSpeciesProfile();           // 0x00c0bbd0
    cCombatant_s00c0_7480* GetCombatantTarget();               // 0x00c0ee60
    float GetAttackDamage(int arg);                 // 0x00c04140
    void SetStealthed(int a, int b);                // 0x00c1aed0
    void StopAttacking(int arg);                    // 0x00c14750
    void SetIntention(int arg);                     // 0x00c073a0

    virtual void TakeDamage(float damage, uint32_t attackerPoliticalID, int damageType,
                            const Vector3_s00c0_7480& direction, cCombatant_s00c0_7480* pAttacker);   // 0x00c1a3c0

    bool IsPlayerAvatar() const { return (mGeneralFlags >> 9) & 1; }

    uint32_t pad670[(0xb20 - 0x670) / 4];
    cSpeciesProfile_s00c0_7480* mpSpeciesProfile;              // 0xb20
    uint32_t mProfileSeq;                           // 0xb24
    ResourceKey_s00c0_7480 mSpeciesKey;                        // 0xb28
    int mAge;                                       // 0xb34
    uint32_t padb38[(0xb48 - 0xb38) / 4];
    cAnimationQueue* field_B48;                     // 0xb48
    cBehaviorTreeData_s00c0_7480* mpBehaviorTree;              // 0xb4c
    uint32_t padb50[2];
    uint32_t mGeneralFlags;                         // 0xb58
    bool field_B5C;
    bool mbTeleport;
    bool mbDead;                                    // 0xb5e
    uint8_t padb5f;
    uint32_t padb60[(0xfc0 - 0xb60) / 4];
};
struct cHerd {
    uint32_t pad[0x88 / 4];
    uint32_t field_88;                              // 0x88
    uint32_t pad8c[(0xf0 - 0x8c) / 4];
    uint32_t field_F0;                              // 0xf0
    uint32_t padf4[(0x164 - 0xf4) / 4];
    cCreatureBase_s00c0_7480* mpLeader;                        // 0x164
};
struct cSpeciesArchetype_s00c0_7480 {
    uint32_t pad[0x434 / 4];
    float mAlertRadius;                             // 0x434
    int mMaxDefenders;                              // 0x438
};
struct cSpeciesArchetypeManager {
    cSpeciesArchetype_s00c0_7480* GetArchetype(uint32_t a, uint32_t b);   // 0x004e0050
};
cSpeciesArchetypeManager* SpeciesArchetypeManager();          // 0x00401090
struct cNearbyEntry { uint32_t pad[2]; cCreatureBase_s00c0_7480* mpCreature; };
struct cNearbyVector { cNearbyEntry** mpBegin; cNearbyEntry** mpEnd; };
struct cNearbyFilter { bool operator()(cNearbyEntry* e); };   // 0x00c02600
struct cNearbyIterator {
    cNearbyEntry** mpCurrent;
    cNearbyEntry** mpEnd;
    cNearbyFilter mFilter;
    cNearbyIterator(const cNearbyVector& v, const cNearbyFilter& f);   // 0x00b41a40
    void Next();                                                       // 0x00b3d850
};
class cCreatureAnimal : public cCreatureBase_s00c0_7480 {
public:
    virtual void TakeDamage(float damage, uint32_t attackerPoliticalID, int damageType,
                            const Vector3_s00c0_7480& direction, cCombatant_s00c0_7480* pAttacker);

    cSPTimer mNoDamageTimer;                        // 0xfc0
    cSPTimer mLastAvatarDamageTimer;                // 0xfe0
    uint32_t pad1000[(0x1124 - 0x1000) / 4];
    cNearbyVector mNearby;                          // 0x1124
    uint32_t pad112c[(0x1624 - 0x112c) / 4];
    cBehaviorPerception* mpPerception;              // 0x1624
    uint32_t pad1628[(0x1674 - 0x1628) / 4];
    cHerd* mpHerd;                                  // 0x1674
    uint32_t pad1678[(0x1694 - 0x1678) / 4];
    float mCharmDamage;                             // 0x1694
    cCombatantPtr mpCharmer;                        // 0x1698
    float mCharmTime;                               // 0x169c
};
struct cCivilizationBase { virtual void v00(); uint32_t pad[(0x3c - 4) / 4]; };
struct cIdentityColorable {
    virtual void v00();
    uint32_t mIdentityColor;
    uint32_t GetIdentityColor() const { return mIdentityColor; }
};
struct cCivilization : public cCivilizationBase, public cIdentityColorable {
    cSpeciesProfile_s00c0_7480* GetSpeciesProfile();           // 0x00bef950
};
struct cGameNounManager {
    cCivilization* GetPlayerCivilization();         // 0x00b25fb0
    uint32_t GetPlayerPoliticalID();                // 0x00b1f9d0
    cCreatureBase_s00c0_7480* GetAvatar();                     // 0x00b1fdb0
    struct cTerrainSphere* GetPlanet();             // 0x00f67d90
};
cGameNounManager* GameNounManager();                // 0x00b3d300
void __cdecl LogEvent(uint32_t eventID, const ResourceKey_s00c0_7480* a, const ResourceKey_s00c0_7480* b,
                      const ResourceKey_s00c0_7480* c, uint32_t color, int d, int e);   // 0x00e3c7c0
struct cTerrainSphere { void OnCreatureKilled(float value, int arg); };   // 0x00c756a0
void __cdecl NotifyCreatureKilled(float value);     // 0x00d2e8a0
struct cAudioManager {
    uint32_t pad[0x58 / 4];
    struct cPollinator* field_58;                   // 0x58
    void PlayForSpecies(uint32_t id, const ResourceKey_s00c0_7480* key);   // 0x0060d860
};
struct cServerID { uint32_t a, b; };
struct cPollinator {
    bool GetServerID(const ResourceKey_s00c0_7480* key, struct cServerID* id, int arg);   // 0x0054e530
};
cAudioManager* AudioManager();                      // 0x0067cb30
struct cRelationshipManager {
    int GetRelationship(const ResourceKey_s00c0_7480* key, cCreatureBase_s00c0_7480* avatar, cCreatureBase_s00c0_7480* creature);   // 0x00ba3f90
    void ApplyEvent(int type, const ResourceKey_s00c0_7480* key, cCreatureBase_s00c0_7480* creature);                   // 0x00ba48b0
};
cRelationshipManager* RelationshipManager();        // 0x00b3d4c0
struct cPosseSimulator { void OnEvent(int type, int arg); };   // 0x00d52e90
cPosseSimulator* PosseSimulator();                  // 0x00d539d0
struct cCreatureStat { uint32_t pad[0x2c / 4]; int field_2C; int field_30; int field_34; };
struct cCreatureStatRecord { uint32_t pad[0xc / 4]; cCreatureStat* mpStat; };
struct cKillInfo { cCreatureBase_s00c0_7480* mpVictim; int field_4; int mDamageType; };
struct cCreatureModeStrategy {
    void OnCreatureEvent(uint32_t id, cKillInfo* info);   // 0x00d39360
    void SignalCreatureEvent(uint32_t id);                 // 0x00d3cdc0
    cCreatureStatRecord* AddStat(int a, int b);            // 0x00d39670
};
cCreatureModeStrategy* CreatureModeStrategy();      // 0x00d38840
struct cAchievements { void Trigger(uint32_t id, int a, int b); };   // 0x00676ed0
cAchievements* AchievementsController();            // 0x00675250
struct cCombatAlertManager {
    void AlertCreatures(const Vector3_s00c0_7480& pos, float radius, int arg, uint32_t politicalID);   // 0x00f315a0
};
cCombatAlertManager* CombatAlertManager();          // 0x00c03260
struct cTribeReactions {
    void React(uint32_t id, const Vector3_s00c0_7480& pos, float radius, float time,
               cCreatureBase_s00c0_7480* attacker, cCreatureBase_s00c0_7480* victim);   // 0x00bc8400
};
cTribeReactions* TribeReactions();                  // 0x00bc8000
float __cdecl DistanceBetween(cLocomotiveObject_s00c0_7480* a, cLocomotiveObject_s00c0_7480* b, int arg);   // 0x00d99ac0
bool __cdecl IsValidRetaliationTarget(cCombatant_s00c0_7480* attacker);                        // 0x00d30f60
struct cCameraState { uint32_t pad[0x54 / 4]; bool field_54; };
struct cCameraMode { uint32_t pad[0x90 / 4]; int mMode; void SetLock(int a); void SetMode(int m); };   // 0x00f1b640 / 0x00f1aae0
struct cCameraManager {
    uint32_t pad[0x68 / 4];
    cCameraState* field_68;                         // 0x68
    uint32_t pad6c[(0x78 - 0x6c) / 4];
    cCameraMode* field_78;                          // 0x78
};
extern cCameraManager* g_pCameraManager;           // 0x016c7aa4
class cBehaviorMessage {
public:
    virtual void _v00();
    volatile long mnRefCount;                       // +04
    cBehaviorMessage() { _InterlockedExchange(&mnRefCount, 0); }
};
class cDamageMessage : public cBehaviorMessage {
public:
    float mDamage;                                  // +08
    uint32_t field_C[9];
    uint32_t mMessageID;                            // +30
    uint32_t field_34;
    void* mpData;                                   // +38

    cDamageMessage(uint32_t id) : mMessageID(id), mpData(0) {}
    virtual void _v00();
    ~cDamageMessage();                              // 0x00421cf0
};
struct IMessageServer {
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
    virtual void PostMSG(uint32_t id, void* msg, void* p);   // 0x14
};
IMessageServer* MessageServer();                    // 0x0067dcc0
template <class T> inline const T& Max(const T& a, const T& b) { return (a < b) ? b : a; }
// ---- items of slice s00c07480 end

// ---- items of slice s00c080b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float DAT_0168d844;                                  // 0x0168d844 default orientation x
extern float DAT_0168d848;                                  // 0x0168d848 default orientation y
extern float DAT_0168d84c;                                  // 0x0168d84c default orientation z
#define VTC(p, off) (*(void**)((char*)(*(void**)(p)) + (off)))
void* SP_NounManager();                                     // 0x00b3d300
void* SP_PosseSimulator();                                  // 0x00d539d0
void* SP_BehaviorManager();                                 // 0x00b3d260
void  FUN_011e0744(void* first, void* last, int value);     // 0x011e0744 eastl::vector<bool>::DoInsertValue
void  remove_1st(void* vec, void* value);                   // 0x00acca00 spstl::remove_1st<...>
struct AllocHeader { int mOwner; };
struct cBehaviorAgent { void* mpVtbl; };
struct cLocomotionAgent
{
    void* mpVtbl;                                   // +0x00
    void  FUN_00c41d60(const float* dir);           // 0x00c41d60
};
struct cAttackState
{
    void* mpVtbl;                                   // +0x00
    void  FUN_00bc9de0(int anim);                   // 0x00bc9de0
};
struct cGlobalManager
{
    void* mpVtbl;                                   // +0x00
    void  FUN_00b45410(void* arg);                  // 0x00b45410
};
struct cGameNounManager_s00c0_80b0
{
    void* mpVtbl;                                   // +0x00
    int   GetAvatar();                              // 0x00b1fdb0
    void  FUN_00b1fd50(int arg);                    // 0x00b1fd50
};
struct cPosseSimulator_s00c0_80b0
{
    void* mpVtbl;                                   // +0x00
    void  RemovePosseMember(void* member, int a, int b);  // 0x00d53490
};
struct cBehaviorManager { void* mpVtbl; };
struct cGameDataFlags
{
    unsigned pad0  : 8;     // bits 0..7
    unsigned mbOwned : 1;   // bit 8
    unsigned pad9  : 23;    // bits 9..31
};
struct AttackParams
{
    void* mpBegin;        // +0x00  eastl::vector<bool> heap block (released after the call)
    void* mpEnd;          // +0x04
    void* mpCapacity;     // +0x08
    char  pad0c[8];       // +0x0c
    float qx;             // +0x14
    float qy;             // +0x18
    float qz;             // +0x1c
    float qw;             // +0x20
    int   i24;            // +0x24
    char  pad28[0x24];    // +0x28
    char  b4c;            // +0x4c
    char  pad4d[3];       // +0x4d
    float f50;            // +0x50
    float f54;            // +0x54
    float f58;            // +0x58
    int   i5c;            // +0x5c
    float f60;            // +0x60
    float f64;            // +0x64
    float f68;            // +0x68
    float f6c;            // +0x6c
    int   i70;            // +0x70
};
struct cCreatureBase_s00c0_80b0
{
    void*            mpVtbl;        // +0x00
    char             pad04[0x58 - 0x04];
    cBehaviorAgent   agent58;       // +0x58
    char             pad5c[0xc0 - 0x58 - 0x04];
    cLocomotionAgent agentC0;       // +0xc0
    char             padc4[0x328 - 0xc0 - 0x04];
    char             mbSelfPowered; // +0x328
    char             pad329[0x5e0 - 0x328 - 1];
    float            f5e0;          // +0x5e0
    char             pad5e4[0xb5e - 0x5e0 - 4];
    char             mbDead;        // +0xb5e
    char             padb5f[0xe3c - 0xb5e - 1];
    int              fE3C;          // +0xe3c
    char             pade40[0xe8c - 0xe3c - 4];
    int              fE8C;          // +0xe8c
    int              fE90;          // +0xe90
    float            fE94;          // +0xe94
    char*            mpE98;         // +0xe98
    char*            mpE9C;         // +0xe9c
    char             padea0[0x1624 - 0xe9c - 4];
    cAttackState*    mpAttackState; // +0x1624
    char             pad1628[0x1674 - 0x1624 - 4];
    void*            mp1674;        // +0x1674
    char             pad1678[0x1698 - 0x1674 - 4];
    void*            mp1698;        // +0x1698

    void  func8Ch();                // 0x00c080b0
    void  FUN_00c0cff0(int arg);    // 0x00c0cff0
    void  FUN_00c0d240();           // 0x00c0d240
    void  FUN_00c17350(int id, int arg);  // 0x00c17350
};
struct cGameData_s00c0_80b0
{
    void*          mpVtbl;          // +0x00
    char           pad04[0x58 - 0x04];
    cBehaviorAgent agent58;         // +0x58
    char           pad5c[0xb58 - 0x58 - 0x04];
    cGameDataFlags   flagsB58;      // +0xb58
    char           padb5c[0x1624 - 0xb58 - 4];
    cAttackState*  mpAttackState;   // +0x1624
    char           pad1628[0x1674 - 0x1624 - 4];
    void*          mp1674;          // +0x1674
    char           pad1678[0x1698 - 0x1674 - 4];
    void*          mp1698;          // +0x1698

    void RemoveOwner();             // 0x00c08270
    void FUN_00c1c8e0();            // 0x00c1c8e0
};
// ---- items of slice s00c080b0 end

// ---- items of slice s00c09410 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* FUN_00b3d300();                 // SP::NounManager
extern "C" void* FUN_00b3d380();                 // SP::GameTimeManager
extern "C" void* FUN_00b3d260();                 // SP::BehaviorManager
extern "C" void* FUN_00b3d350();                 // SP::PlanetModel
extern "C" void* FUN_00b3d480();                 // cCityVisualizer accessor
extern "C" void* FUN_0067cb40();                 // SP::ObjectTemplateDB
extern "C" void* FUN_0067cb30(int, void*);       // resource key lookup
extern "C" float   FUN_00d38a30(int, void*);     // creature tuning scalar
extern "C" float   FUN_00c02690(float*);         // vector length
extern "C" void*   FUN_00c04820(void*, void*, void*, void*);
extern "C" void*   FUN_00c07320(void*, void*, void*);
extern "C" void*   FUN_00d995f0(float, double, void*, void*, void*, void*, void*, void*);
extern "C" void*   FUN_00aea5d0(void*, void*);   // eastl::vector<...>::push_back
extern "C" float   FUN_00572a10(float, float);   // RandomFloatRange
extern "C" void*   FUN_00c02710(float);
extern "C" float   FUN_00c033d0(void*);
extern "C" void*   FUN_0059aed0(float*, void*, void*);
extern "C" void*   FUN_00c035f0(void*);
extern "C" int     FUN_00c02790(void*);
extern float g_015d96b8;   // 0x015d96b8
extern float g_01687a54;   // 0x01687a54
extern float g_01687a58;   // 0x01687a58
extern float g_01471064;   // 0x01471064
extern float g_01571278;   // 0x01571278
extern float g_0157127c;   // 0x0157127c
extern float g_01571280;   // 0x01571280
extern float g_01571284;   // 0x01571284
extern float g_01571288;   // 0x01571288
extern float g_0157128c;   // 0x0157128c
extern float g_01571290;   // 0x01571290
struct M
{
	void* FUN_00b1fdb0();                      // 0xb1fdb0 cGameNounManager::GetAvatar
	void* FUN_00b20c60(int);                   // 0xb20c60 cGameNounManager::CreateNoun
	void  FUN_00b1fd50(void*);                 // 0xb1fd50 NounMgr::SetAvatar
	void  FUN_00b225d0(void*);                 // 0xb225d0 cGameNounManager::RemoveNoun
	void* FUN_00bca0c0(int, int, int, int);    // 0xbca0c0 cAgentOrderManager::FindSlot
	void* FUN_00ad20e0(void*, void*);          // 0xad20e0 cCityVisualizer::findVignetteEntry
	void  FUN_00c6b440(void*);                 // 0xc6b440 cHerd::OnAnimalRemoved
	void* FUN_004df420();                      // 0x4df420 GetAvatarProfile
	void* FUN_004e01b0();                      // 0x4e01b0
	void* FUN_004e0050(int, int);              // 0x4e0050 GetSpeciesArchetype
	void  FUN_004df3e0(void*);                 // 0x4df3e0 SetAvatarProfile
	void  FUN_00c0c180(void*);                 // 0xc0c180 C::SetE84
	char  FUN_00c037c0(void*, void*, int);     // 0xc037c0 C::attach
	char  FUN_00c0c0e0();                      // 0xc0c0e0 C::Flag388
	void  FUN_0060d860(void*, void*);          // 0x60d860 UpdateProperty
	void  FUN_00c0d9b0();                      // 0xc0d9b0 C::apply
	void* FUN_00c0c1a0();                      // 0xc0c1a0 C::getActiveOrder
	void  FUN_00c0fb80(int, int);              // 0xc0fb80 CAN::fb80
	void* FUN_00c0bbe0();                      // 0xc0bbe0
	void* FUN_00c042e0();                      // 0xc042e0
	void  FUN_00f924e0(float);                 // 0xf924e0
	void* FUN_00c05e80();                      // 0xc05e80
	void  FUN_00c05ea0();                      // 0xc05ea0
	void  FUN_00c06bf0(void*);                 // 0xc06bf0 vector::erase
	void* FUN_00c072f0(void*);                 // 0xc072f0 vector::push_back
	float FUN_00c0e4f0();                      // 0xc0e4f0 CCM::e4f0
	float FUN_00c0c010();                      // 0xc0c010 C::GetA
	float FUN_00c0c040();                      // 0xc0c040 C::GetB
	char  FUN_00c0c130();                      // 0xc0c130 C::isValid
	char  FUN_00c0d560(void*, float, float);   // 0xc0d560 C::proximity
	int   FUN_00c0c140();                      // 0xc0c140 C::CallFind13
	float FUN_004d3d70(int);                   // 0x4d3d70 TuningObj::GetBound
	int   FUN_00bc96a0(int, int);              // 0xbc96a0 cSPCreatureBase::Play
	void  FUN_00bc97f0(int, int, float, void*); // 0xbc97f0 cSPCreatureBase::queue
	void* FUN_00bc9980(float);                 // 0xbc9980 cSPCreatureBase::emit
	void  FUN_00b7f250(void*, void*, void*);   // 0xb7f250 BuildSurfaceOrientation2
	long long FUN_00b316c0();                  // 0xb316c0 GameTimeManager::now
};
typedef void  (__thiscall *VF0)(void*);
typedef void* (__thiscall *VP0)(void*);
typedef float (__thiscall *VFl0)(void*);
typedef int   (__thiscall *VI0)(void*);
typedef void  (__thiscall *VF1)(void*, void*);
typedef void* (__thiscall *VP1)(void*, void*);
typedef void  (__thiscall *VF2)(void*, void*, void*);
static inline void  vv0(void* p, int off) { (*(VF0*)(*(char**)p + off))(p); }
static inline void* vp0(void* p, int off) { return (*(VP0*)(*(char**)p + off))(p); }
static inline float vf0(void* p, int off) { return (*(VFl0*)(*(char**)p + off))(p); }
static inline int   vi0(void* p, int off) { return (*(VI0*)(*(char**)p + off))(p); }
static inline void  vv1(void* p, int off, void* a) { (*(VF1*)(*(char**)p + off))(p, a); }
static inline void* vp1(void* p, int off, void* a) { return (*(VP1*)(*(char**)p + off))(p, a); }
static inline void  vv2(void* p, int off, void* a, void* b) { (*(VF2*)(*(char**)p + off))(p, a, b); }
struct CCM_s00c0_9410
{
	void FUN_00c09410(int param_2);
};
// ---- items of slice s00c09410 end

// ---- items of slice s00c11410 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float gF_150c8b8;        // 0x150c8b8  default sight cos threshold
extern float gF_157174c;        // 0x157174c  half-turn angle (radians)
extern float gF_146a330;        // 0x146a330  max sight range
extern float gF_13ec480;        // 0x13ec480  overhead-effect offset
extern float gF_13ef74c;        // 0x13ef74c  body-effect part scale
struct Vector3_s00c1_1410 {
    float x, y, z;
    Vector3_s00c1_1410() {}
    Vector3_s00c1_1410(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
    Vector3_s00c1_1410(const Vector3_s00c1_1410& v) : x(v.x), y(v.y), z(v.z) {}
    float Length() const { return sqrtf(x * x + y * y + z * z); }
    float SquaredLength() const { return x * x + y * y + z * z; }
};
inline Vector3_s00c1_1410 operator+(const Vector3_s00c1_1410& a, const Vector3_s00c1_1410& b) { return Vector3_s00c1_1410(a.x + b.x, a.y + b.y, a.z + b.z); }
inline Vector3_s00c1_1410 operator-(const Vector3_s00c1_1410& a, const Vector3_s00c1_1410& b) { return Vector3_s00c1_1410(a.x - b.x, a.y - b.y, a.z - b.z); }
inline Vector3_s00c1_1410 operator*(const Vector3_s00c1_1410& a, float s) { return Vector3_s00c1_1410(a.x * s, a.y * s, a.z * s); }
inline Vector3_s00c1_1410 operator*(float s, const Vector3_s00c1_1410& a) { return Vector3_s00c1_1410(s * a.x, s * a.y, s * a.z); }
struct Matrix3 {
    float m[9];
};
struct Transform {
    uint16_t mFlags;
    uint16_t mVersion;
    Vector3_s00c1_1410 mOffset;       // +0x04
    float mScale;          // +0x10
    Matrix3 mRot;          // +0x14
    void SetOffset(const Vector3_s00c1_1410& v) { mFlags |= 4; mVersion++; mOffset = v; }
    void SetScale(float s) { mScale = s; mVersion++; }
    void SetRotation(const Matrix3& m) { mRot = m; mFlags |= 2; mVersion++; }
};
Matrix3* Matrix3FromQuaternion(Matrix3* out, const Quaternion* q);             // 0x0059c190
Matrix3* Matrix3FromFacingAndUp(Matrix3* out, const Vector3_s00c1_1410* facing, const Vector3_s00c1_1410* up);  // 0x0069b440
Vector3_s00c1_1410* QuaternionVectorTransform(Vector3_s00c1_1410* out, const Quaternion* q, const Vector3_s00c1_1410* v);  // 0x0099c1a0
void Matrix3Assign(Matrix3* out, const Matrix3* src);                          // 0x0041cb40
void PreRotateY(Transform* t, float angle);                                    // 0x004099b0
float RandomFloatRange(float a, float b);                                      // 0x00572a10
int CCB_d050(void* creature, float f);                                         // 0x00c0d050
float CCM_e4f0(void* creature);                                                // 0x00c0e4f0
bool C_C5b0(void* self, int id, int* out);                                     // 0x00c0c5b0
void C_QuatHalf(void* self, float f);                                          // 0x00c0c4b0
void FUN_00c10250(void* self, int handle, int arg3, void* layer);              // 0x00c10250
void FUN_00c111b0();                                                           // 0x00c111b0
void* FUN_009cb300(void* instanceData, int id, int a, int b);                  // 0x009cb300  AddEffect
void FUN_009caa40(void* effect, int partIdx, int a, int b);                    // 0x009caa40  effect::Init
bool FUN_00a04990(void* self, int a);                                          // 0x00a04990
void FUN_00a02bc0(void* self);                                                 // 0x00a02bc0
void* FUN_00b3d310(void* self);                                                // 0x00b3d310
void FUN_00b45410(void* self);                                                 // 0x00b45410
void FUN_00b453a0(void* self);                                                 // 0x00b453a0
void FUN_00b54200(void* self);                                                 // 0x00b54200
extern const Matrix3 gM_168d964;   // 0x168d964  identity matrix (3x3)
extern const Matrix3 gM_168db30;   // 0x168db30  identity matrix (3x3)
extern const Vector3_s00c1_1410 gV_168d910;   // 0x168d910  default body-effect offset
extern const Vector3_s00c1_1410 gV_168d988;   // 0x168d988  default transform offset
struct cEffectsManager {
    PV8 PV2 PV
    virtual bool CreateVisualEffect(uint32_t id, int flags, void** ppEffect);  // +0x2c
};
cEffectsManager* EffectsManager_s00c1_1410();                   // 0x0067ddd0
struct cLayerManager {
    PV8 PV4 PV4
    virtual void* GetLayer(uint32_t id);             // +0x40
};
cLayerManager* LayerManager();                       // 0x0067cb20
struct cRefObj {
    virtual void AddRef();                           // +0x00
    virtual void Release();                          // +0x04
    virtual void* Cast(uint32_t type);               // +0x08
    virtual void* V0C(void* arg);                    // +0x0c
};
struct cIVisualEffect : public cRefObj {
    PV2
    virtual void Start(int flags);                   // +0x18
    virtual void Stop(int flags);                    // +0x1c
    virtual bool IsRunning();                        // +0x20
    PV
    virtual void SetTransform(const Transform& t);   // +0x28
};
struct BodyPart {
    uint32_t pad00[4];
    Vector3_s00c1_1410 mPosition;          // +0x10
    Quaternion mOrientation;    // +0x1c
    uint32_t pad2C[0x38];
    float mRestDim0;            // +0x10c
    uint32_t pad110[0x0a];
    float mUnk138;              // +0x138
    float mUnk13C;              // +0x13c
    float mUnk140;              // +0x140
};
struct cCreatureInstanceData {
    uint32_t pad00[6];
    Vector3_s00c1_1410 mPosition;          // +0x18 (creature root position)
    Quaternion mOrientation;    // +0x1c
    Vector3_s00c1_1410 mUnk3C;             // +0x3c
    Vector3_s00c1_1410 mUnk48;             // +0x48
    Vector3_s00c1_1410 mUnk54;             // +0x54
    uint32_t pad60[0xa1];
    BodyPart* mBodyParts;       // +0x2e4
};
struct cAnimatedCreature {
    uint32_t pad00[0x5f];
    cCreatureInstanceData* mpInstanceData;           // +0x17c

    virtual void* V08(uint32_t layerID, int b);      // +0x08
    virtual void V0C(void* handle, bool b);          // +0x0c
    PV2                                              // 0x10..0x18
    virtual void V18(void* handle);                  // +0x18
    PV8 PV8 PV8 PV8 PV8 PV8 PV8                      // 0x1c..0x3c
    virtual void V3C(void* handle, int a);           // +0x3c
    virtual void V40(void* handle, uint32_t id);     // +0x40
    virtual void V44(void* handle, float f);         // +0x44
    PV4                                              // 0x48..0x58
    virtual void* V58(uint32_t id, int a, int b, int c, void* out);  // +0x58
};
struct cCreatureEffect {
    virtual void AddRef();                           // +0x00
    virtual void Release();                          // +0x04
    PV8 PV8 PV8 PV8                                  // 0x08..0x18
    Quaternion mQuat;                                // +0x18
    PV8 PV8 PV8 PV8 PV8 PV8                          // 0x28..0x40
    uint32_t mRefCount;                              // +0x40
    uint32_t pad44[0x03];                            // 0x44..0x50
    uint32_t mStateFlags;                            // +0x50
    uint32_t pad54[0x04];                            // 0x54..0x64
    cRefObj* mpField64;                              // +0x64
    uint32_t pad68[0x02];                            // 0x68..0x70
    uint8_t mFlag70;                                 // +0x70
    uint8_t mFlag71;                                 // +0x71
    uint16_t pad72;
    uint8_t mFlag75;                                 // +0x75
    uint32_t pad76[0x05];                            // 0x76..0x8c
    cRefObj* mpField8C;                              // +0x8c
    cCreatureEffect* mpField90;                      // +0x90
    uint32_t pad94[0x04];                            // 0x94..0xa4
    void* mpEffect;                                  // +0xa4
    void (*mpCallback)();                            // +0xa8
    uint32_t padAC[0x31];                            // 0xac..0x170
    virtual void V170(int release);                  // +0x170
};
struct cEffectSource {
    PV8 PV8 PV8 PV8 PV8 PV8 PV8 PV8 PV8 PV8 PV8 PV8 PV8 PV8 PV8 PV8
    PV8 PV8 PV8 PV8 PV8 PV8 PV8 PV8 PV8 PV8 PV8 PV8 PV8 PV8 PV8 PV8
    PV8 PV8 PV8 PV8 PV8 PV8 PV8 PV8 PV8 PV8 PV8 PV8 PV8
    virtual void* Cast(uint32_t type);               // +0xb8
};
struct cCreatureBonus {
    uint32_t pad00[0xd4];
    float mRadius;                  // +0x350
};
struct CreatureBase;
struct cSpatialObject_s00c1_1410 {
    PV8 PV2 PV
    virtual const Vector3_s00c1_1410& GetPosition();            // +0x2c
    virtual const Quaternion& GetOrientation();      // +0x30
    virtual float GetScale();                        // +0x34
    PV8 PV
    virtual Vector3_s00c1_1410* GetSampleDir(Vector3_s00c1_1410* out);     // +0x5c
    PV2
    virtual const Vector3_s00c1_1410* GetLocalExtents();        // +0x68
    PV
    virtual float GetFootprintRadius();              // +0x74

    // 00c11410 (retail ecx = creature+0xc0)
    void SetSpeedState(float a, float b);
};
struct CreatureBase {
    uint32_t pad00[0x30];                    // 0x00..0xc0
    cSpatialObject_s00c1_1410 mSpatial;                 // +0xc0
    uint32_t padC4[0x77];                    // 0xc4..0x2a0
    float mValue2A0;                         // +0x2a0 (spatial this+0x1e0)
    uint32_t pad2A4[0x22c];                  // 0x2a4..0xb54
    cAnimatedCreature* mpAnimatedCreature;   // +0xb54
    uint32_t mFlagsB58;                      // +0xb58 (spatial this+0xa98)
    uint32_t padB5C[0x15];                   // 0xb5c..0xbb0
    uint8_t mByteBB0;                        // +0xbb0
    uint8_t mbStealthed;                     // +0xbb1
    uint32_t padBB2[0xb4];                   // 0xbb2..0xe84
    cCreatureBonus* mpBonus;                 // +0xe84
    void* mpMostRecentAnimHandle;            // +0xe88
    uint32_t padE8C[0x43];                   // 0xe8c..0xf98
    int32_t mStateF98;                       // +0xf98 (spatial this+0xed8)

    // 00c11480
    bool IsWithinSight(const Vector3_s00c1_1410& target, float angle, float range);
    // 00c115d0
    bool funcC0h(CreatureBase* other, float angle, float range);
    // 00c11920
    void OneShotOverheadEffect(uint32_t effectID);
    // 00c11b50
    bool GetBodyPartPositionAndOrientation(Vector3_s00c1_1410* pos, Quaternion* orient, int partIdx, bool local);
    // 00c11f50
    bool CreateBodyEffect(int partIdx, void* effect, void* obj, uint32_t id);
    // 00c12190
    int PlayAnimation(uint32_t id, bool arg2, int arg3);
    // 00c122c0
    void PlayAnimationRange(uint32_t id, float a, float b);

    cSpatialObject_s00c1_1410& GetSpatial() { return mSpatial; }
};
// ---- items of slice s00c11410 end

// ---- items of slice s00c12310 begin (TODO(rewrite): local stubs, replace by canonical classes)
float gNegOne = -1.0f;
float gFLTMax = 3.4028234663852886e+38f;
float gOne = 1.0f;
float gZeroPointTwo = 0.2f;
float gEpsilon = 1.52587890625e-05f;
struct cTarget;
class cSPCreatureBase_s00c1_2310;
class cAnimCreature
{
public:
virtual void a00();
virtual void a04();
    virtual uint32_t GetLength(uint32_t id, int a);          // +0x08 (raw float bits)
    virtual void  SetLength(uint32_t bits, int a);            // +0x0c
    virtual void  a10();
    virtual void  SetPause(uint32_t bits, float a);           // +0x14
    virtual void  a18(uint32_t bits);                         // +0x18
virtual void  a1c();
virtual void  a20();
virtual void  a24();
virtual void  a28();
virtual void  a2c();
virtual void  a30();
virtual void  a34();
virtual void  a38();
    virtual void  a3c(uint32_t bits, int a);                  // +0x3c
    virtual void  a40(uint32_t bits, uint32_t id);            // +0x40
};
class cAnimationManager
{
public:
virtual void m00();
virtual void m04();
virtual void m08();
virtual void m0c();
virtual void m10();
virtual void m14();
virtual void m18();
virtual void m1c();
virtual void m20();
virtual void m24();
virtual void m28();
virtual void m2c();
virtual void m30();
virtual void m34();
virtual void m38();
virtual void m3c();
    virtual void* GetAnimation(uint32_t id);                 // +0x40
};
cAnimationManager* AnimationManager();                       // 0x0067cb20
void ResolveAnimation(void* self, uint32_t id, uint32_t* out); // 0x00c0c5b0 (cdecl)
void FUN_00c10250(void* self, uint32_t bits, int arg2, void* handle); // 0x00c10250 (cdecl)
struct TargetSlot
{
    char  pad0[4];
    float mValue;                                            // +0x04
    char  pad8[8];
};
struct cTarget
{
    char  pad0[8];
    int   mType;                                             // +0x08
    int   mState;                                            // +0x0c
    char  pad10[0x3c - 0x10];
    float mScore;                                            // +0x3c
    char  pad40[0xa8 - 0x40];
    float mRadiusA;                                          // +0xa8
    char  padAC[0xf4 - 0xac];
    float mRadiusB;                                          // +0xf4
    char  padF8[0x104 - 0xf8];
    float mMaxRange;                                         // +0x104
    char  pad108[0x114 - 0x108];
    bool  mFlag114;                                          // +0x114

    float GetTimeToReach(int flags);                         // 0x004d3d70
};
class cSPCreatureBase_s00c1_2310
{
public:
    uint32_t vptr;                                           // +0x00
    char     pad04[0xb54 - 0x04];
    cAnimCreature* mpAnimCreature;                           // +0xb54
    uint32_t mFlags;                                         // +0xb58
    char     padB5C[0xc28 - 0xb5c];
    TargetSlot* mTargetSlots;                                // +0xc28
    char     padC2C[0xe58 - 0xc2c];
    float    mMaxDistance;                                   // +0xe58
    char     padE5C[0xe88 - 0xe5c];
    uint32_t mAnimLength;                                    // +0xe88 (raw float bits)
    int      mCurrentAnim;                                   // +0xe8c

    uint32_t InterruptAnimation(uint32_t animID, int arg2, char arg3);  // 0x00c12310 (cSPCreatureBase::InterruptAnimation)
    uint32_t FUN_00c12410(const uint32_t* pMask, float range, char a3,
                          char a4, char a5, char a6, char a7);
};
// ---- items of slice s00c12310 end

// ---- items of slice s00c12640 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Vector3_s00c1_2640 {
    float x, y, z;
    Vector3_s00c1_2640() {}
    Vector3_s00c1_2640(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
    Vector3_s00c1_2640(const Vector3_s00c1_2640& v) : x(v.x), y(v.y), z(v.z) {}
    float Length() const { return sqrtf(x * x + y * y + z * z); }
    float SquaredLength() const { return x * x + y * y + z * z; }
};
inline Vector3_s00c1_2640 operator+(const Vector3_s00c1_2640& a, const Vector3_s00c1_2640& b) { return Vector3_s00c1_2640(a.x + b.x, a.y + b.y, a.z + b.z); }
inline Vector3_s00c1_2640 operator-(const Vector3_s00c1_2640& a, const Vector3_s00c1_2640& b) { return Vector3_s00c1_2640(a.x - b.x, a.y - b.y, a.z - b.z); }
inline Vector3_s00c1_2640 operator*(const Vector3_s00c1_2640& a, float s) { return Vector3_s00c1_2640(a.x * s, a.y * s, a.z * s); }
inline Vector3_s00c1_2640 operator*(float s, const Vector3_s00c1_2640& a) { return Vector3_s00c1_2640(s * a.x, s * a.y, s * a.z); }
inline Vector3_s00c1_2640 Cross(const Vector3_s00c1_2640& a, const Vector3_s00c1_2640& b)
{
    return Vector3_s00c1_2640(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
}
struct Quaternion_s00c1_2640 {
    float x, y, z, w;
};
struct BoundingBox {
    Vector3_s00c1_2640 mMin;
    Vector3_s00c1_2640 mMax;
    BoundingBox();                                   // 0x00576b40
    void Set(const BoundingBox& other);              // 0x00571d60
};
struct Transform_s00c1_2640 {
    unsigned short mFlags;     // bit0 scaled, bit1 rotated, bit2 translated
    unsigned short mVersion;
    Vector3_s00c1_2640 mPos;
    float mScale;
    Matrix3 mRot;

    Transform_s00c1_2640();                                     // 0x00434040
    void SetOffsetOutOfLine(const Vector3_s00c1_2640& v);       // 0x00571d40
    void SetOffset(const Vector3_s00c1_2640& v) { mFlags |= 4; mVersion++; mPos = v; }
    void SetScale(float s) { mScale = s; mVersion++; }
    void SetRotation(const Matrix3& m) { mRot = m; mFlags |= 2; mVersion++; }
};
template <typename T> inline const T& Min(const T& a, const T& b) { return (b < a) ? b : a; }
Vector3_s00c1_2640 normalized_safe(const Vector3_s00c1_2640& v);                                         // 0x00449c20
Vector3_s00c1_2640 Vector3_Normalize(const Vector3_s00c1_2640& v);                                       // 0x00436ce0
Matrix3 Matrix3FromFacingAndUp(const Vector3_s00c1_2640& facing, const Vector3_s00c1_2640& up);          // 0x0069b440
Matrix3 Matrix3FromAxes(const Vector3_s00c1_2640& x, const Vector3_s00c1_2640& y, const Vector3_s00c1_2640& z);     // 0x00afa0c0
Vector3_s00c1_2640 RotateVector_s00c1_2640(const Vector3_s00c1_2640& v, const Quaternion_s00c1_2640& q);                       // 0x0059aed0
extern const Vector3_s00c1_2640 kUpAxis;                // 0x0168db54
static const uint32_t kGameDataUFO = 0x18ebadc;
namespace EA {
namespace Swarm {
class cIVisualEffect_s00c1_2640 { public:
    PV2
    virtual void Start(int flags);                   // +0x08
    virtual void Stop(int flags);                    // +0x0c
    virtual bool IsRunning();                        // +0x10
    PV
    virtual void SetTransform(const Transform_s00c1_2640& t);   // +0x18
    PV
    virtual const Transform_s00c1_2640& GetTransform(Transform_s00c1_2640& out); // +0x20
};
}
}
struct VisualEffectRef {
    EA::Swarm::cIVisualEffect_s00c1_2640* mpObject;
    void** AsPPTypeParam();                          // 0x00a16f40
};
cEffectsManager* EffectsManager_s00c1_2640();                   // 0x0067ddd0
struct cPlanetModel_s00c1_2640 {
    float GetGravity();                              // 0x00b7e490
};
namespace SP {
 cPlanetModel_s00c1_2640* PlanetModel();   // 0x00b3d350
}
namespace nSPCreatureAnim {
struct creature_instance_data_s00c1_2640 {
    void HitBody(int a, const Vector3_s00c1_2640* impulse, int b, int c, float d);   // 0x009bb680
};
}
struct cAnimatedCreature_s00c1_2640 {
    uint32_t pad00[0x5f];
    nSPCreatureAnim::creature_instance_data_s00c1_2640* mpInstanceData;   // +0x17c
};
struct cCreatureAbility_s00c1_2640 {
    uint32_t pad00[0xf];
    float mDamage;                                   // +0x3c
    uint32_t pad40[0x14];
    uint32_t mImpactEffectID;                        // +0x90
    uint32_t pad94[5];
    float mRange;                                    // +0xa8
    uint32_t padAC;
    float mSpeed;                                    // +0xb0
    uint32_t padB4[0x10];
    float mRushingRange;                             // +0xf4
};
struct cSpatialObject_s00c1_2640 {
    PV8 PV2 PV
    virtual const Vector3_s00c1_2640& GetPosition();            // +0x2c
    virtual const Quaternion_s00c1_2640& GetOrientation();      // +0x30
    virtual float GetScale();                        // +0x34
    PV8 PV
    virtual Vector3_s00c1_2640 GetDirection();                  // +0x5c
    PV2
    virtual const BoundingBox& GetLocalExtents();    // +0x68
    virtual BoundingBox GetBoundingBox();           // +0x6c
    PV
    virtual float GetFootprintRadius();              // +0x74
};
struct cGameData_s00c1_2640 {
    PV8
    virtual uint32_t GetNounID();                    // +0x20
    uint32_t pad04[0xc];
    cSpatialObject_s00c1_2640 mSpatial;                         // +0x34 (cGameDataUFO)
};
struct cCombatant_s00c1_2640 {
    PV2
    virtual cSpatialObject_s00c1_2640* ToSpatialObject();       // +0x08
    virtual cGameData_s00c1_2640* ToGameData();                 // +0x0c
    PV8 PV8 PV2 PV
    virtual void* Cast(uint32_t type);               // +0x5c
};
struct cTargetCreature {
    PV8 PV2 PV
    virtual bool IsDead();                           // +0x2c
    uint32_t pad04[0x4c];
    uint8_t pad134;
    bool mb135;                                      // +0x135
    uint8_t pad136[0xa1e];
    cAnimatedCreature_s00c1_2640* mpAnimatedCreature;           // +0xb54
    uint32_t padB58;
    uint8_t padB5C[2];
    bool mbB5E;                                      // +0xb5e
};
struct cRangedAttack {                               // 0x34
    bool mbAlwaysHit;
    bool mbHoming;                                   // +0x01
    int mState;                                      // +0x04 (1 moving, 2 hit)
    Vector3_s00c1_2640 mPosition;                               // +0x08
    Vector3_s00c1_2640 mVelocity;                               // +0x14
    uint32_t mAttackIndex;                           // +0x20
    float mDistanceTraveled;                         // +0x24
    cCombatant_s00c1_2640* mpTarget;                            // +0x28
    EA::Swarm::cIVisualEffect_s00c1_2640* mpTrailEffect;        // +0x2c
    VisualEffectRef mpHitEffect;                     // +0x30
    void Reset();                                    // 0x00c0f490
};
struct bitset88 {
    uint32_t mWord[3];
    bool any() const
    {
        for (uint32_t i = 0; i < 3; ++i)
            if (mWord[i] != 0)
                return true;
        return false;
    }
    bool test(uint32_t i) const
    {
        if (i < 88)
            return (mWord[i >> 5] & (1 << (i & 31))) != 0;
        return false;
    }
};
float GetAttackRangeScale(int a, struct cCreatureBase_s00c1_2640* creature);          // 0x00d38a30
struct cCreatureBase_s00c1_2640 {
    PV8 PV8 PV8 PV8 PV8 PV4 PV
    virtual cCreatureAbility_s00c1_2640* GetAbility(int index);                         // +0xb4
    virtual void OnRangedAttackHit(cCombatant_s00c1_2640* target, int abilityIndex, Vector3_s00c1_2640* hitPosition);  // +0xb8
    uint32_t pad04[0x2f];
    cSpatialObject_s00c1_2640 mSpatial;                         // +0xc0
    uint32_t padC4[0x2d0];
    bitset88 mInUseRangedAttackBits;                 // +0xc04
    uint32_t padC10[0xa8];
    cRangedAttack mRangedAttacks[4];                 // +0xeb0

    void UpdateRangedAttacks(float deltaTime);
};
// ---- items of slice s00c12640 end

// ---- items of slice s00c14350 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float gF_13eb1bc;         // 0x13eb1bc  duration for animation-mode 2
extern uint32_t gSingleton168d900;  // 0x168d900
struct Vector3_s00c1_4350 {
    float x, y, z;
};
struct Quaternion_s00c1_4350 {
    float x, y, z, w;
};
struct cGameData_s00c1_4350 {
    PV8 PV8 PV8 PV8 PV8 PV2 PV
    virtual void* GetStream();                       // +0x20  (returns object whose +0x18 is the reader)
    PV8 PV8 PV2 PV2 PV2 PV2 PV4
    virtual uint32_t GetID();                        // +0x3c
};
struct cContentValidationSummarizer {
    PV2
    virtual void v08();                              // +0x08
};
cContentValidationSummarizer* GetContentValidationSummarizer();   // 0x00c14350
struct IRefCounted_s00c1_4350 {
    virtual void AddRef();                           // +0x00
    virtual void Release();                          // +0x04
    PV2
    virtual void Init();                             // +0x10
    virtual void Deinit();                           // +0x14
};
struct BodyPart_s00c1_4350 {
    uint32_t pad00[4];
    Vector3_s00c1_4350 mPosition;          // +0x10
    Quaternion_s00c1_4350 mOrientation;    // +0x1c
    uint32_t pad2C[0x38];
    float mRestDim0;            // +0x10c
    uint32_t pad110[0x0a];
    float mUnk138;              // +0x138
    float mUnk13C;              // +0x13c
    float mUnk140;              // +0x140
};
struct cCreatureInstanceData_s00c1_4350 {
    uint32_t pad00[6];
    Vector3_s00c1_4350 mPosition;          // +0x18
    Quaternion_s00c1_4350 mOrientation;    // +0x1c
    uint32_t pad2C[0xae];
    BodyPart_s00c1_4350* mBodyParts;       // +0x2e4
};
struct cAnimatedCreature_s00c1_4350 {
    PV2                                              // +0x00, +0x04 (vptr, slot1)
    virtual void* V08(uint32_t layerID, int b);      // +0x08
    virtual void V0C(void* handle, int b);           // +0x0c
    PV2                                              // +0x10, +0x14
    virtual void V18(void* handle);                  // +0x18
    PV                                               // +0x1c
    virtual void V20(void* handle, int a);           // +0x20
    virtual void V24(void* handle, float f);         // +0x24

    uint32_t pad04[(0x17c - 0x04) / 4];              // 0x04..0x17c
    cCreatureInstanceData_s00c1_4350* mpInstanceData;           // +0x17c
    uint32_t pad180;
    void* mpField184;                                // +0x184  anim quest handle set
    uint32_t mpField188;                             // +0x188
    uint32_t mpCurrentAnim;                          // +0x18c
};
struct cSpatialObject_s00c1_4350 {
    PV8 PV2 PV
    virtual const Vector3_s00c1_4350& GetPosition();            // +0x2c
    virtual const Quaternion_s00c1_4350& GetOrientation();      // +0x30
    virtual float GetScale();                        // +0x34
    PV8 PV
    virtual Vector3_s00c1_4350* GetSampleDir(Vector3_s00c1_4350* out);     // +0x5c
    virtual void* GetLocalExtents();                 // +0x68
    PV
    virtual float GetFootprintRadius();              // +0x74

    void FUN_c421b0(void* arg);                      // 0x00c421b0
};
struct XformMsg {
    uint16_t mFlags;         // +0x00
    uint16_t mVersion;       // +0x02
    uint32_t pad04;
    Vector3_s00c1_4350 mOffset;         // +0x04 (+4)
    Matrix3 mRot;            // +0x10
    float   mScale;          // +0x34
};
void XformMsg_ctor(XformMsg* msg);                   // 0x00434040
struct cDamageSub {
    int GetDamageState();                            // 0x008e7f80
};
struct cCreatureProfile {
    uint32_t pad00[0x61c / 4];
    uint32_t mField61C;                              // +0x61c
    uint32_t pad620[(0x698 - 0x620) / 4];
    uint32_t mField698;                              // +0x698
    uint32_t pad69C;
    uint32_t mField6A0;                              // +0x6a0
};
struct CreatureBase_s00c1_4350 {
    PV8 PV8 PV8 PV8 PV8 PV2 PV
    virtual void* Cast(uint32_t type);               // +0x20
    PV8 PV8
    virtual void V2C(int a);                         // +0x2c
    PV8 PV8 PV8 PV8 PV8 PV8
    virtual void V48(int a);                         // +0x48
    virtual void V4C(int a);                         // +0x4c
    PV8 PV8 PV8 PV8 PV8 PV8 PV8 PV8 PV8 PV8
    virtual void V78(int a);                         // +0x78
    PV8 PV8

    uint8_t  pad04[(0xb0 - 0x04)];                   // 0x04..0xb0
    int32_t  mAttackTimer;                           // +0xb0
    uint8_t  padB4[(0xc0 - 0xb4)];
    uint8_t  mSpatial[(0x2b0 - 0xc0)];               // +0xc0 cSpatialObject sub-object (opaque here)
    int32_t  mLocomotionState;                       // +0x2b0
    uint8_t  pad2B4[(0x328 - 0x2b4)];
    uint8_t  mbSelfPowered;                          // +0x328
    uint8_t  pad329[(0x5a8 - 0x329)];
    uint32_t mCombatantVptr;                         // +0x5a8  (damage-state sub-object at (char*)self+0x5a8)
    uint8_t  pad5AC[(0xb20 - 0x5ac)];
    cCreatureProfile* mpSpeciesProfile;              // +0xb20
    uint8_t  padB24[(0xb38 - 0xb24)];
    wchar_t* mpDefinitionName;                       // +0xb38
    uint8_t  padB3C[(0xb54 - 0xb3c)];
    cAnimatedCreature_s00c1_4350* mpAnimatedCreature;           // +0xb54
    uint16_t padB58;
    uint8_t  padB5A[(0xb5e - 0xb5a)];
    uint8_t  mbB5E;                                  // +0xb5e
    uint8_t  padB5F[(0xe38 - 0xb5f)];
    uint8_t  mbE38;                                  // +0xe38
    uint8_t  padE39[(0xf98 - 0xe39)];
    int32_t  mLocomotionStateF98;                    // +0xf98

    cAnimatedCreature_s00c1_4350* Anim() { return mpAnimatedCreature; }
    void* FUN_b3d310();                              // 0x00b3d310
    int   FUN_b3d240();                              // 0x00b3d240

    // 00c14590..00c15270
    int  AnimationAction(uint32_t id, int mode);
    void UpdateLocomotionAnimation();
    void UpdateLocomotion(int param2);
    int  PlayAnimationWithTarget(uint32_t id, void* target, int arg4);
    int  PlayAnimationWithTargetObj(uint32_t id, void* target, int arg5);
    int  InterruptAnimationWithTarget(uint32_t id, void* target, int arg4);
    int  InterruptAnimationWithTargetObj(uint32_t id, void* target, int arg5);
    void DoHitGround();
    void OnStartSwimming();
    void NotifySummarizer();
    int  WaitForAnimEventOrEnd(int event, uint32_t* out, int arg4, int arg5);
    void* CreateBodyEffectByIndex(int partIdx, uint32_t visualEffectId, uint32_t id);
    bool DetachBodyEffectById(void* handle, void* arg3);
    void DetachAllBodyEffects();
    void SetBodyEffectParam(uint32_t param);

    // external callees that are thiscall on the creature
    int  PlayAnimation(uint32_t id, int arg2, int arg3);        // 0x00c12190
    int  InterruptAnimation(uint32_t id, int arg2, int arg3);   // 0x00c12310
    int  FUN_00c0e040();                                        // 0x00c0e040
    void FUN_00c0c630(int a, int* b, int* c, int* d);           // 0x00c0c630
    int  FUN_00c0e2c0(int a);                                   // 0x00c0e2c0
    int  FUN_00c0e170(int a);                                   // 0x00c0e170
    void FUN_00c0cff0(int a);                                   // 0x00c0cff0
};
void*  EAAllocate(uint32_t size, const char* name, int a, int b, const char* file, int line);  // 0x00f473a0
void   EAFree(void* p);                                                                       // 0x00f47380
bool   FUN_00c04750(void* self);                                                              // 0x00c04750
void*  FUN_00b18600(void* self, void* stream);                                                // 0x00b18600  cGameData::Read
bool   FUN_00cee440(void* self, void* stream);                                                // 0x00cee440
bool   FUN_00c43c10(void* self, void* stream);                                                // 0x00c43c10
bool   FUN_00bfc540(void* self, void* stream);                                                // 0x00bfc540
void   FUN_00bc9ac0(void* stream);                                                            // 0x00bc9ac0
void   FUN_00c0c4b0(void* self, float f);                                                     // 0x00c0c4b0  QuatHalf
bool   FUN_00a02b40(void* self, int a);                                                       // 0x00a02b40
int    FUN_00a01f10(void* a, int b);                                                          // 0x00a01f10
int    FUN_009ff6f0_s00c1_4350(void* a, void* b);                                                        // 0x009ff6f0
void*  FUN_009cab60(void* a);                                                                 // 0x009cab60
void   FUN_009cb460(void* effect);                                                            // 0x009cb460
int    FUN_00a02bd0(void* self);                                                              // 0x00a02bd0
void   Matrix3FromQuaternion(Matrix3* out, const Quaternion_s00c1_4350* q);                              // 0x0059c190
void*  GetCurrentGameMode_s00c1_4350();                                                                  // 0x00b5b800
void*  InterfaceCast(void* obj);                                                              // 0x00ac8960
int    ReadInt32_s00c1_4350(void* stream, void* out, int count, int a);                                  // 0x0093a780
void   VtFind(void* self, void* out, uint32_t* key);                                          // 0x00645ed0
int    FUN_00cee330(void* self);                                                              // 0x00cee330
void   FUN_00c3c10Serializer(void* self, void* stream);                                       // 0x00692f90 (cVarListSerializer + Read)
void   ExitHandler(void);                                                                     // 0x013c3590
void   AddSetAnimationTargetModifier3(CreatureBase_s00c1_4350* self, int handle, void* target);          // 0x00c0b570
void   AddSetAnimationTargetModifier4(CreatureBase_s00c1_4350* self, int handle, void* target, void* obj); // 0x00c0b510
void   DetachBodyEffect(void* rec, bool release);                                             // 0x00c12080
void   FUN_00c0cff0(CreatureBase_s00c1_4350* self, int a);                                               // 0x00c0cff0
cEffectsManager* EffectsManager_s00c1_4350();                   // 0x0067ddd0
struct PoolNode {
    uint32_t mNext;     // +0x00  (free-list link, = node[0] when free)
    uint32_t mValue1;   // +0x04
    uint32_t mValue2;   // +0x08
};
struct Pool_s00c1_4350 {
    uint32_t pad00[0x1c / 4];
    PoolNode* mpFree;        // +0x1c
    uint32_t pad20[3];       // 0x20..0x2c
    uint32_t mnAllocSize;    // +0x2c

    void* Alloc(uint32_t* out);  // 0x00d652a0 (Pool::Alloc)
};
struct cEffectMgr {
    int DecrementNode(void* node);                   // 0x00c14070
};
struct Str {
    char* mpBegin;   // +0x00
    char* mpEnd;     // +0x04
    char* mpCap;     // +0x08
    void assign(const char* first, const char* last);   // 0x00423650 (basic_string<char>)
};
extern "C" cContentValidationSummarizer* __cdecl GetContentValidationSummarizerExternal(void);   // 0x00c14350
// ---- items of slice s00c14350 end

// ---- items of slice s00c16340 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct GameModeObj {
    virtual bool vf0();
    virtual bool vf1();
    virtual bool vf2();
    virtual bool vf3();
    virtual bool vf4();
    virtual bool vf5();
    virtual bool vf6();
    virtual bool vf7();
    virtual bool vf8();
    virtual bool vf9(int id, void** out);
    GameModeObj* Fn1(void* mode, int flag);
};
struct PropObj {
    float* GetFloat();
};
struct TerrainObj {
    char pad_e58[0xe58];
    float f_e58;
    void ApplyWave(float v);                                             // 0x00c15dc0
};
extern "C" GameModeObj* __cdecl FUN_00b5b800_s00c1_6340();                          // SP::GetCurrentGameMode
extern "C" GameModeObj* __cdecl FUN_00b3d320_s00c1_6340();                          // global game-mode getter
// ---- items of slice s00c16340 end

// ---- items of slice s00c17de0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float const kLookAtScale;        // 0x01473c70  (10.0f)
extern float const kZero;               // 0x01485378
extern float const kEpsilon;            // 0x013ec4b8  (1e-8f)
extern float const kMilli;              // 0x013f9428  (0.001f)
extern float const kNetScaleA;          // 0x01571728
extern float const kNetScaleB;          // 0x0157172c
extern bool const gUseGroundMotion;     // 0x0169e381
extern float const gGravityScale;       // 0x0169e384
class cVector3_s00c1_7de0 {
public:
    float x;    // +0x00
    float y;    // +0x04
    float z;    // +0x08
    cVector3_s00c1_7de0() {}
    cVector3_s00c1_7de0(float fValue) : x(fValue), y(fValue), z(fValue) {}
};
class cQuaternion {
public:
    float x;
    float y;
    float z;
    float w;
};
bool Vector3Equal(const cVector3_s00c1_7de0* a, const cVector3_s00c1_7de0* b);      // 0x004232c0
bool Vector3_NotEqual(const cVector3_s00c1_7de0* a, const cVector3_s00c1_7de0* b);  // 0x0041dd30
float* normalized_safe(float* out, const float* v);           // 0x00449c20
namespace checkerlib
{
    float* QuaternionVectorTransform(float* out, const float* quat, const float* v);  // 0x0099c1a0
}
namespace SP
{
    cVector3_s00c1_7de0 const kNoDirection;        // 0x0168d910
}
extern cVector3_s00c1_7de0 const gGravityDirection;  // 0x0169e388
extern cVector3_s00c1_7de0 gStoredDirection;       // 0x0169e3b4
class cPose;
class cBonePose
{
public:
    uint32_t pad00[(0x10) / 4];
    cVector3_s00c1_7de0 mLocalPosition;          // +0x10
    uint32_t pad1c[(0x2bc - 0x1c) / 4];
};
class cPose
{
public:
    uint32_t pad00[(0x18) / 4];
    cVector3_s00c1_7de0 mPosition;               // +0x18
    uint32_t pad24[(0x3c - 0x24) / 4];
    cQuaternion mRotation;            // +0x3c
    uint32_t pad4c[(0x17c - 0x4c) / 4];
    cPose* mpParent;                  // +0x17c
    uint32_t pad180[(0x2e4 - 0x180) / 4];
    cBonePose* mpBones;               // +0x2e4
};
class cAnimTarget
{
public:
virtual void t00();
virtual void t01();
virtual void t02();
virtual void t03();
virtual void t04();
virtual void t05();
virtual void t06();
virtual void t07();
virtual void t08();
virtual void t09();
virtual void t10();
virtual void t11();
virtual void t12();
virtual void t13();
virtual void t14();
virtual void t15();
virtual void t16();
virtual void t17();
virtual void t18();
virtual void t19();
virtual void t20();
virtual void t21();
    virtual void GetCurrentAnimation(uint32_t* out, int a, int b, int c);   // +0x58
    virtual void t23();

    uint32_t pad04[(0x154 - 0x04) / 4];
    int      mState;                  // +0x154
    int      mSubState;               // +0x158
    cPose*   mpPose;                  // +0x15c
    int      mBoneIndex;              // +0x160
    cVector3_s00c1_7de0 mLookAtPoint;            // +0x164

    bool      IsOrientIdleAnim(uint32_t nGUID);                  // 0x00a027a0
    int       GetBodyPartIndex(int nPart, int nSide);            // 0x00c17580
    cVector3_s00c1_7de0* GetBodyPartPosition(cVector3_s00c1_7de0* out, int a, int b, int c);  // 0x00c17a30
};
class cAnimData
{
public:
    uint32_t pad00[(0x14) / 4];
    cVector3_s00c1_7de0 mOffset;                 // +0x14
    uint32_t pad20[(0x5c - 0x20) / 4];
    cAnimTarget* mpTarget;            // +0x5c
};
class cPlayPrefix
{
public:
    uint32_t mHandle;                 // +0x00
    uint32_t mFlags;                  // +0x04
};
class cAnimationPlayer
{
public:
virtual void a00();
virtual void a01();
virtual void a02();
virtual void a03();
    uint32_t pad14[(0x1c0 - 0x14) / 4];
    cAnimData* mpCurrent;             // +0x1c0
    cAnimData* mpPending;             // +0x1c4

    cAnimData* Play(int nFlags, int nMode);                       // 0x00bc96a0
};
class cAnimPlayer : public cPlayPrefix, public cAnimationPlayer
{
};
class cLocomotiveObject_s00c1_7de0
{
public:
virtual void l00();
virtual void l01();
virtual void l02();
virtual void l03();
virtual void l04();
virtual void l05();
virtual void l06();
virtual void l07();
virtual void l08();
virtual void l09();
virtual void l10();
    virtual cVector3_s00c1_7de0* GetPosition();                              // +0x2c
virtual void l12();
virtual void l13();
virtual void l14();
virtual void l15();
    virtual void l16();
    virtual bool IsOrientationLocked();                           // +0x48
virtual void l19();
virtual void l20();
virtual void l21();
    virtual bool IsFacingValid();                                 // +0x58
    virtual cVector3_s00c1_7de0* GetForward();                               // +0x5c

    uint32_t pad60[(0x1f4 - 0x60) / 4];
    cAnimData* GetAnimData();                                     // 0x00c41ec0
    uint32_t pad1f8[(0x548 - 0x1f8) / 4];

    cVector3_s00c1_7de0* GetVelocity();                                      // 0x00d20610
    void OffsetPosition(cVector3_s00c1_7de0& vDelta, int nMode);             // 0x00c446d0
};
class cSpecies
{
public:
    uint32_t pad000[(0x548) / 4];
    float    mLookAtRadius;           // +0x548
    uint32_t pad54c[(0x698 - 0x54c) / 4];
    int      mWaveCount;              // +0x698
};
class cSPCreatureBase_s00c1_7de0
{
public:
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
virtual void c22();
virtual void c23();
virtual void c24();
virtual void c25();
virtual void c26();
virtual void c27();
    virtual void c28();
    virtual void SetAnimData(cAnimData* pData);                   // +0x74
virtual void c30();
virtual void c31();
virtual void c32();
virtual void c33();
virtual void c34();
virtual void c35();
virtual void c36();
virtual void c37();
virtual void c38();
virtual void c39();
virtual void c40();
virtual void c41();
virtual void c42();
virtual void c43();
virtual void c44();
    virtual void* GetPartData(int nIndex);                        // +0xb4

    uint8_t  pad04[(0xc0 - 0x04) / 4 * 4];
    cLocomotiveObject_s00c1_7de0 mLocomotion;    // +0xc0
    uint8_t  padc4[(0x137 - 0xc4)];
    bool     mbSteering;              // +0x137
    uint8_t  pad138[(0x2b0 - 0x138)];
    int      mSteerState;             // +0x2b0
    uint8_t  pad2b4[(0xb20 - 0x2b4)];
    cSpecies* mpSpecies;              // +0xb20
    uint8_t  padb24[(0xb4c - 0xb24)];
    cAnimPlayer* mpAnimPlayer;        // +0xb4c
    cAnimTarget* mpAnimTarget;        // +0xb54
    uint32_t mFlags;                  // +0xb58
    uint8_t  padb5c[(0xb5e - 0xb5c)];
    bool     mbHasPartFlag;           // +0xb5e
    uint8_t  padb5f[(0xb66 - 0xb5f)];
    bool     mbLookAtEnabled;         // +0xb66
    uint8_t  padb67[(0xe58 - 0xb67)];
    float    mWaveHeight;             // +0xe58
    uint8_t  pade5c[(0xe62 - 0xe5c)];
    bool     mbWaveFinished;          // +0xe62
    uint8_t  pade63[(0xe7c - 0xe63)];
    class cGameNounManager_s00c1_7de0* mpNounManager;   // +0xe7c
    uint8_t  pade80[(0xeac - 0xe80)];
    int      mLookAtState;            // +0xeac

    void      LookAtUpdate(float fBlend);                         // 0x00c17de0
    void      UpdateNetDirection();                               // 0x00c18370
    void      UpdateWaveMotion(float fBlend, uint32_t nAmount);    // 0x00c18740
    void      SetLookAt(cSPCreatureBase_s00c1_7de0* pTarget, int nPart);      // 0x00c0d200
    void      ClearLookAt();                                      // 0x00c0d240
    void      LookAtTo(float fBlend, cVector3_s00c1_7de0& vPoint, int nMode); // 0x00c133d0
    uint32_t  GetCurrentAnimationGUID();                          // 0x00c0e040
    int       FindIndex(int nID);                                 // 0x00c0c080
    void      ApplyWave(float fAmount);                           // 0x00c15dc0
    void      InterruptAnimation(uint32_t nID, int nA, int nB);    // 0x00c12310
};
class cPlanetModel_s00c1_7de0
{
public:
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
virtual void p11();
virtual void p12();
virtual void p13();
    virtual cVector3_s00c1_7de0* GetSurfaceOffset(cVector3_s00c1_7de0* out, int nMode, cVector3_s00c1_7de0 vDir);  // +0x38

    cVector3_s00c1_7de0* DirectionToSurfacePosition(cVector3_s00c1_7de0* out, const cVector3_s00c1_7de0* dir);  // 0x00b815a0
    float GetLookAtRange();                                       // 0x00b7e500
};
class cMessageServer
{
public:
virtual void m00();
virtual void m01();
virtual void m02();
virtual void m03();
    virtual void m04();
    virtual void PostMessage(uint32_t nID, int nA, int nB);       // +0x14
};
cMessageServer* MessageServer_s00c1_7de0();                                  // 0x0067dcc0
cPlanetModel_s00c1_7de0* PlanetModel_s00c1_7de0();                                      // 0x00b3d350
void* FUN_00b3d240_s00c1_7de0();                                             // 0x00b3d240
void* WatchMemoryBlock(void* pBlock);                             // 0x00d999d0
void* FUN_00ac80d0(cSPCreatureBase_s00c1_7de0* pCreature, uint32_t nID);    // 0x00ac80d0
class cGameNounManager_s00c1_7de0
{
public:
virtual void n00();
virtual void n01();
virtual void n02();
virtual void n03();
virtual void n04();
virtual void n05();
virtual void n06();
virtual void n07();
virtual void n08();
virtual void n09();
virtual void n10();
virtual void n11();
virtual void n12();
virtual void n13();
virtual void n14();
virtual void n15();
virtual void n16();
virtual void n17();
virtual void n18();
virtual void n19();
virtual void n20();
virtual void n21();
virtual void n22();
    virtual cSPCreatureBase_s00c1_7de0* FindCreature(uint32_t nID);           // +0x5c
};
// ---- items of slice s00c17de0 end

// ---- items of slice s00c1bad0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void* g_vtbl_cSPCreatureBase;   // 0x0146a5f0
extern void* g_vtbl_cGameData;         // 0x0146a5dc
extern void* g_vtbl_cInteractionAgent; // 0x0146a598
extern void* g_vtbl_cLocoSub;          // 0x0146a530
extern void* g_vtbl_cLocomotiveObject; // 0x0146a430
extern void* g_vtbl_cLocoSub2;         // 0x0146a424
extern void* g_vtbl_cSPCreatureBase2;  // 0x0146a408
extern void* g_vtbl_cCombatant;        // 0x0146a3a0
extern void* g_vtbl_cSub670;           // 0x0146a388
struct Vec3_s00c1_bad0 { f32 x, y, z; };
class cSPCreatureBase_s00c1_bad0;
class cLocomotiveObject_s00c1_bad0;
extern const f32 _DivOneFifty;         // 0x013ec4b4
extern const f32 _BigFloat;            // 0x0146a32c
extern const f32 _Tolerance;           // 0x013ec4d0
extern const f32 _SmallTolerance;      // 0x013ef480
extern f32 g_DefaultGoalDir[3];        // 0x0168d910, 0x0168d914, 0x0168d918
extern f32 g_SpeedBonus;               // 0x0150c900
struct ListHead { ListHead* mpNext; ListHead* mpPrev; };
struct tNavigationWaypoint
{
    tNavigationWaypoint* mpNext;      // +0x00   (linked-list forward pointer / copied buffer)
    u8   mPad04[0x04];
    void* mpPathOwner;                // +0x08   (owner passed to the vector helper)
    u8   mPad0c[0x08];
    Vec3_s00c1_bad0 mPos;                        // +0x14   (destination position)
    u8   mPad20[0x10];
    f32  mf30;                        // +0x30
    u8   mPad34[0x08];
    u8   mb3c;                        // +0x3c
    u8   mPad3d[0x13];
    f32  mf50;                        // +0x50
    f32  mf54;                        // +0x54
    f32  mf58;                        // +0x58
    u8   mb5c;                        // +0x5c   (accessible = initialized)
    u8   mPad5d[0x03];
    f32  mf60;                        // +0x60   (arrival radius)
    f32  mf64;                        // +0x64   (speed)
    f32  mf68;                        // +0x68   (facing tolerance)
    f32  mf6c;                        // +0x6c   (facing offset)
    void* mp70;                       // +0x70   (path-plan owner)
};
class cGameData_s00c1_bad0 {
public:
    PVN(0) PVN(1) PVN(2) PVN(3) PVN(4) PVN(5) PVN(6) PVN(7) PVN(8) PVN(9)
    PVN(10) PVN(11)
    virtual void* vIdx12();      // 0x30   (the SpVector<cCurvePoint>* parent of a goal)
    virtual void  vIdx13(int);   // 0x34
    PVN(14) PVN(15) PVN(16) PVN(17) PVN(18) PVN(19) PVN(20)
    virtual void* vIdx21(int);   // 0x54
    virtual void  vIdx22(int);   // 0x58
    virtual void  vIdx23();      // 0x5c
    PVN(24) PVN(25) PVN(26) PVN(27) PVN(28) PVN(29) PVN(30) PVN(31) PVN(32)
    virtual void  vIdx33(void*); // 0x84
    PVN(34) PVN(35) PVN(36) PVN(37) PVN(38) PVN(39) PVN(40) PVN(41)
    virtual f32   GetTime(int);  // 0xa8
    PVN(43) PVN(44) PVN(45) PVN(46) PVN(47) PVN(48) PVN(49) PVN(50)
    virtual void* vIdx51();      // 0xcc
    virtual void  vIdx52();      // 0xd0
    PVN(53) PVN(54)
    virtual void  vIdx55(void*); // 0xdc
    PVN(56) PVN(57) PVN(58) PVN(59) PVN(60) PVN(61) PVN(62) PVN(63) PVN(64)
    virtual void  vIdx65();      // 0x104
    u8 mPad04[0x30];
};
class cInteractionAgent_s00c1_bad0 {
public:
    PVN(0) PVN(1) PVN(2) PVN(3) PVN(4) PVN(5) PVN(6) PVN(7) PVN(8) PVN(9)
    PVN(10) PVN(11)
    virtual void  ia30(void*);   // 0x30
    PVN(13)
    virtual f32   ia38(u32);     // 0x38
    u8 mPad04[0x8c - 4];
};
class cLocomotiveObject_s00c1_bad0 {
public:
    virtual void* lo2c();                 // 0x2c  GetPosition -> Vec3*
    PVN(12) PVN(13) PVN(14) PVN(15)
    virtual void  lo40(u32);              // 0x40
    PVN(17) PVN(18) PVN(19) PVN(20)
    virtual void  lo54();                 // 0x54
    virtual void  lo58();                 // 0x58
    virtual void  lo5c();                 // 0x5c
    PVN(24) PVN(25) PVN(26) PVN(27) PVN(28) PVN(29)
    virtual f32   lo78(int, int);         // 0x78
    PVN(31) PVN(32) PVN(33) PVN(34)
    virtual void  lo8c();                 // 0x8c
    PVN(36)
    virtual bool  lo94();                 // 0x94
    PVN(38)
    virtual void  lo9c(void*);            // 0x9c
    PVN(40) PVN(41)
    virtual void  loa8();                 // 0xa8
    PVN(43) PVN(44) PVN(45) PVN(46) PVN(47) PVN(48) PVN(49) PVN(50) PVN(51)
    virtual void  lod0();                 // 0xd0
    virtual void  lod4(int, void*);       // 0xd4
    virtual void  lod8();                 // 0xd8
    virtual void  lodc(void*);            // 0xdc
    PVN(56) PVN(57) PVN(58) PVN(59) PVN(60) PVN(61)
    virtual void  lof8();                 // 0xf8

    u8   mPad04[0x54 - 0x04];
    tNavigationWaypoint* mpGoal;          // +0x054
    u8   mPad58[0x194 - 0x58];
    u32  mdw194;                          // +0x194
    u8   mPad198[0x2a0 - 0x198];
    f32  mf_2a0;                          // +0x2a0 (loco-relative 0x1e0; current speed)
    u8   mPad_2a4[0x2b0 - 0x2a4];
    void* mp_2b0;                         // +0x2b0 (loco-relative 0x1f0)
    u8   mPad_2b4[0x330 - 0x2b4];
    u32  mdw_330;                         // +0x330 (loco-relative 0x270)
    u8   mPad_334[0x4e8 - 0x334];

    void Shutdown();                      // 0x00c43f90
};
class cCombatant_s00c1_bad0 {
public:
    PVN(0) PVN(1) PVN(2) PVN(3) PVN(4) PVN(5) PVN(6) PVN(7) PVN(8) PVN(9)
    PVN(10) PVN(11) PVN(12) PVN(13) PVN(14) PVN(15) PVN(16) PVN(17) PVN(18)
    PVN(19) PVN(20) PVN(21) PVN(22) PVN(23) PVN(24) PVN(25) PVN(26)
    virtual void  co6c();                 // 0x6c
    PVN(28)
    virtual void  co74();                 // 0x74
    u8 mPad04[0x40 - 4];
};
class cSPCreatureBase_s00c1_bad0 : public cGameData_s00c1_bad0, public cInteractionAgent_s00c1_bad0,
                        public cLocomotiveObject_s00c1_bad0, public cCombatant_s00c1_bad0
{
public:
    // ---- helpers (thiscall) ----
    tNavigationWaypoint* FUN_00c1bad0(tNavigationWaypoint* pGoal, void* pPathOwner);  // 0x00c1bad0
    void  FUN_00c1bbd0();                                                    // 0x00c1bbd0
    void  FUN_00c1c080(u32 a, Vec3_s00c1_bad0* pPos, Vec3_s00c1_bad0* pDir, f32 f1, f32 f2);       // 0x00c1c080
    void  MoveToPointAtSpeed(void* pTarget, Vec3_s00c1_bad0* pPos, f32 f0, f32 f1);     // 0x00c1c1d0
    void  MoveToPointAtSpeedPathPlan(void* pOwner, Vec3_s00c1_bad0* pPos, f32 f0,
                                     u32 flags, char bPlan);                 // 0x00c1c310
    void  MoveToPointAndFacingAtSpeed(void* pOwner, Vec3_s00c1_bad0* pPos, Vec3_s00c1_bad0* pFacing,
                                      f32 f0, f32 f1);                       // 0x00c1c5c0
    void  Shutdown();                                                        // 0x00c1c8e0
    f32   FUN_00c0ce80(int a, int b);                                        // 0x00c0ce80
    void* FUN_00c41ec0();                                                    // 0x00c41ec0

    // ---- fields at absolute offsets >= 0x5e8 (the bases above already cover 0x000..0x5e7) ----
    u8   mPad_5e8[0xbb0 - 0x5e8];
    u8   mb_bb0;                       // +0xbb0
    u8   mPad_bb1[1];
    u8   mCurve[0x14];                 // +0xbc0  (SpVector<cCurvePoint>: begin/end/cap/alloc)
    Vec3_s00c1_bad0 mLastGoalPos;                 // +0xbd4  (last accepted destination)
    u8   mPad_be0[0xbf4 - 0xbe0];
    tNavigationWaypoint* mpGoal_bf4;   // +0xbf4  (inline goal target)
    u8   mPad_bf8[0xf84 - 0xbf8];
    ListHead mRenderList;              // +0xf84  (eastl::list sentinel)
    u8   mPad_f8c[0xf98 - 0xf8c];
    void* mp_f98;                      // +0xf98
    void* mp_f9c;                      // +0xf9c
};
void  FUN_00c1b790(tNavigationWaypoint* pGoal, void* pSrc);          // 0x00c1b790
void  FUN_00b47520(void* p);                                          // 0x00b47520
void  FUN_00ac4570(void* pBegin, void* pEnd);                         // 0x00ac4570
void  FUN_00c0cff0(cSPCreatureBase_s00c1_bad0* pCreature, u32 a, f32 f, void* pHint,
                   void* pOut, u32 flags);                            // 0x00c0cff0
void  FUN_00b3d290(void* pSearch, void* pCtx);                        // 0x00b3d290
void* FUN_00ac65d0(void* pSearch, void* pCtx, Vec3_s00c1_bad0* pPos, u32 a, f32 f,
                   void* pHint, void* pOut, u32 flags, u32 b);        // 0x00ac65d0
void  FUN_00c144b0(void* pBegin, void* pEnd);                         // 0x00c144b0
void  FUN_00a24480(void* pBegin, void* pEnd);                         // 0x00a24480
void  DoNukeSubtree(void* pNode);                                     // rbtree nuke
void  FreeLooseBuffer(void* pBegin, void* pEnd, void** ppFreeList,
                      void* pPoolBegin, void* pPoolEnd);              // inline buffer free
void  FUN_00c7d650();                                                 // 0x00c7d650
void  FUN_00bfcd00();                                                 // 0x00bfcd00
void  FUN_00ac0520();                                                 // 0x00ac0520
void  FUN_00c432e0();                                                 // 0x00c432e0
void  FUN_00abfec0();                                                 // 0x00abfec0
void  FUN_00cee7a0();                                                 // 0x00cee7a0
void  FUN_00b184c0();                                                 // 0x00b184c0
void  FUN_00bc9fa0(void* p);                                          // 0x00bc9fa0
void  FUN_00bcae90(void* p);                                          // 0x00bcae90
void  cGonzagoTimer_Destroy(void* p);                                 // cGonzagoTimer::~cGonzagoTimer
void  cAnimatingCreature_Release(void* p);                            // 0x00a05270
void  EASTL_deallocate(void* p);                                      // 0x00f47380
static inline void* VFn(void* pObj, u32 slot)
{
    return *(void**)((u8*)*(void**)pObj + slot);
}
static inline u8* VCall(void* pObj, u32 slot)
{
    return (u8*)(*(void*(__thiscall**)(void*))VFn(pObj, slot))(pObj);
}
static inline void VCall0(void* pObj, u32 slot)
{
    (*(void(__thiscall**)(void*))VFn(pObj, slot))(pObj);
}
// ---- items of slice s00c1bad0 end

// ---- items of slice s00ec0a40 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct IRefCounted_s00ec_0a40 {
    virtual void AddRef();    // +0x00
    virtual void Release();   // +0x04
};
struct Stimulus {
    uint         id;          // +0x00
    uint         mask;        // +0x04
    float        duration;    // +0x08
    uint         pad0c[8];    // +0x0c
    IRefCounted_s00ec_0a40* object;      // +0x2c
    uint         pad30[2];    // +0x30
};
struct Stimuli {
    void SetStimulus(Stimulus* s, uint a, uint b, float c, IRefCounted_s00ec_0a40* obj); // 0x00bc9700
    void* Find(uint a, uint b);
    Stimulus* Add(uint a, uint b, float c, IRefCounted_s00ec_0a40* obj);

    Stimulus slot[8];         // +0x000
    uint     mMask0;          // +0x1c0
    uint     mMask1;          // +0x1c4
};
extern void (*g_0168b550)(void*);   // 0x0168b550  slot-changed callback
// ---- items of slice s00ec0a40 end

// ---- items of slice s013329c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
unsigned int FNVHash_s0133_29c0(const char* pText, unsigned int nSeed, int nMode);   // 0x00932e80
struct ResourceKey_s0133_29c0
{
    unsigned int mnNameHash;          // +0x00
    unsigned int mnTypeHash;          // +0x04
};
extern ResourceKey_s0133_29c0 g_ScenarioOverridesKey;   // 0x01572038
// ---- items of slice s013329c0 end

// @ 0x00bc96a0
void* Stimuli::Find(uint a, uint b)
{
    if (((mMask0 & a) | (mMask1 & b)) == 0)
        return 0;
    for (uint i = 0; i < 8; ++i)
    {
        Stimulus* s = &slot[i];
        if ((s->id & a) | (s->mask & b))
        {
            if (g_0168b550)
                g_0168b550(s);
            return s;
        }
    }
    return 0;
}

struct ActionCtx;
void FUN_00b498d0(ActionCtx* ctx);   // 0x00b498d0
void FUN_00b49730(void* ctx);        // 0x00b49730
void FUN_00b493e0(void* ctx);        // 0x00b493e0
void FUN_00b4c730(void* ctx);        // 0x00b4c730

// @ 0x00c06500
void CB_s00c0_53b0::func6500()
{
    void* self = this;
    SP_GetCurrentGameMode();
    *(uint32_t*)((char*)self + 0x2b0) = 0;
    char* body = (char*)self + 0xc0;
    void* v = (void*)FUN_00c06000_tc(FUN_00b3d310());
    ((Fn421b0*)body)->f(v);
    ((Fn44040*)body)->f();
    int* m = (int*)FUN_00b3d310();
    switch (m[0x20 / 4]) {
    case 0:
    case 2:
        ((Fn43fe0*)body)->f((void*)&FUN_00b498d0);
    }
    bool on = ((*(uint32_t*)((char*)self + 0xb58) >> 9) & 1) != 0;
    if (on && SP_GetCurrentGameMode() == (void*)0x01654c05) {
        ((Fn43fe0*)body)->f((void*)&FUN_00b49730);
        ((Fn43fe0*)body)->f((void*)&FUN_00b493e0);
        ((Fn43fe0*)body)->f((void*)&FUN_00b4c730);
    }
}

// @ 0x00c06630
void __cdecl FUN_00c06630(P* base, P* first, P* last, P key)
{
    FUN_00c06120(base, first, key);
    for (P* p = first; p < last; ++p) {
        if (*(float*)*base > *(float*)*p) {
            P cur = *p;
            *p = *base;
            FUN_00c04960(base, 0, (int)(first - base), 0, cur, key);
        }
    }
    FUN_00c06160(base, first, key);
}

// @ 0x00c066a0
void* __cdecl FUN_00c066a0(char* c, P* value, float f, uint8_t b1, uint8_t b2)
{
    int local_8 = 0, local_4 = 0;
    char local_14[12];
    int iVar2 = *(int*)(c + 0x18);
    if (iVar2 + 0x14 == *(int*)(c + 0x20)) {
        local_8 = 0; local_4 = 0;
        ((Pool*)c)->Alloc(local_14);
    } else {
        *(int*)(c + 0x18) = iVar2 + 0x14;
        if (iVar2 != 0) { *(int*)(iVar2 + 0xc) = 0; *(int*)(iVar2 + 0x10) = 0; }
    }
    iVar2 = *(int*)(c + 0x18);
    if (iVar2 == *(int*)(c + 0x1c)) iVar2 = *(int*)(*(int*)(c + 0x24) - 4) + 0xa0;
    void* old = *(void**)(iVar2 - 8);
    if (value != old) {
        if (value) ((VObj*)value)->v0();
        *(void**)(iVar2 - 8) = value;
        if (old) ((VObj*)old)->v1();
    }
    char* r = (char*)(iVar2 - 0x14);
    *(float*)r = f;
    r[4] = b1;
    r[5] = b2;
    (void)local_8; (void)local_4;
    return r;
}

// @ 0x00c06750
void* __cdecl FUN_00c06750(char* c, P value, float f, uint8_t b1, uint8_t b2)
{
    int local_8 = 0, local_4 = 0;
    char local_14[12];
    int iVar2 = *(int*)(c + 0x18);
    if (iVar2 + 0x14 == *(int*)(c + 0x20)) {
        local_8 = 0; local_4 = 0;
        ((Pool*)c)->Alloc(local_14);
    } else {
        *(int*)(c + 0x18) = iVar2 + 0x14;
        if (iVar2 != 0) { *(int*)(iVar2 + 0xc) = 0; *(int*)(iVar2 + 0x10) = 0; }
    }
    iVar2 = *(int*)(c + 0x18);
    if (iVar2 == *(int*)(c + 0x1c)) iVar2 = *(int*)(*(int*)(c + 0x24) - 4) + 0xa0;
    char* r = (char*)(iVar2 - 0x14);
    *(void**)(r + 8) = value;
    *(float*)r = f;
    r[4] = b1;
    r[5] = b2;
    void* old = *(void**)(r + 0x10);
    if (value != old) {
        if (value) ((VObj*)value)->v0();
        *(void**)(r + 0x10) = value;
        if (old) ((VObj*)old)->v1();
    }
    (void)local_8; (void)local_4;
    return r;
}

// @ 0x00c06800
void __thiscall CCAnimal::Ctor()
{
    char* self = (char*)this;
    ((BaseCtor*)self)->ctor();
    *(uint32_t*)(self + 0x000) = 0x146a0e0;
    *(uint32_t*)(self + 0x004) = 0x146a0cc;
    *(uint32_t*)(self + 0x034) = 0x146a088;
    *(uint32_t*)(self + 0x058) = 0x146a020;
    *(uint32_t*)(self + 0x0c0) = 0x1469f20;
    *(uint32_t*)(self + 0x194) = 0x1469f14;
    *(uint32_t*)(self + 0x590) = 0x1469ef8;
    *(uint32_t*)(self + 0x5a8) = 0x1469e90;
    *(uint32_t*)(self + 0x670) = 0x1469e74;
    self[0xfb8] = 0; self[0xfb9] = 0;
    ((Gonzago*)(self + 0xfc0))->ctor();
    ((Gonzago*)(self + 0xfe0))->ctor();
    *(float*)(self + 0x1000) = 0.0f;
    *(uint32_t*)(self + 0x1004) = 0;
    *(uint32_t*)(self + 0x1008) = 0;
    *(uint32_t*)(self + 0x100c) = 0;
    *(float*)(self + 0x1010) = *(float*)0x157126c;
    *(float*)(self + 0x1014) = *(float*)0x1571270;
    *(float*)(self + 0x1018) = *(float*)0x1571274;
    *(uint32_t*)(self + 0x101c) = 0;
    *(uint32_t*)(self + 0x1020) = 0;
    *(uint32_t*)(self + 0x1024) = 0;
    *(uint32_t*)(self + 0x1028) = 0;
    for (int i = 0; i < 0x28; i += 4) *(uint32_t*)(self + 0x1034 + i) = 0;
    FUN_00ac4190(0);
    for (int i = 0; i < 0x28; i += 4) *(uint32_t*)(self + 0x1060 + i) = 0;
    FUN_00ac4190(0);
    *(uint32_t*)(self + 0x108c) = (uint32_t)(self + 0x10a4);
    *(uint32_t*)(self + 0x1090) = (uint32_t)(self + 0x10a4);
    *(uint32_t*)(self + 0x1094) = (uint32_t)(self + 0x1124);
    *(uint32_t*)(self + 0x10a0) = 0;
    *(uint32_t*)(self + 0x1124) = (uint32_t)(self + 0x113c);
    *(uint32_t*)(self + 0x1128) = (uint32_t)(self + 0x113c);
    *(uint32_t*)(self + 0x112c) = (uint32_t)(self + 0x133c);
    *(uint32_t*)(self + 0x1138) = 0;
    *(uint32_t*)(self + 0x1350) = 0;
    *(uint32_t*)(self + 0x133c) = (uint32_t)(self + 0x1354);
    *(uint32_t*)(self + 0x1340) = (uint32_t)(self + 0x1354);
    *(uint32_t*)(self + 0x1344) = (uint32_t)(self + 0x13d4);
    *(uint32_t*)(self + 0x13d4) = (uint32_t)(self + 0x13ec);
    *(uint32_t*)(self + 0x13d8) = (uint32_t)(self + 0x13ec);
    *(uint32_t*)(self + 0x13dc) = (uint32_t)(self + 0x140c);
    *(uint32_t*)(self + 0x13e8) = 0;
    *(uint32_t*)(self + 0x140c) = (uint32_t)(self + 0x1424);
    *(uint32_t*)(self + 0x1410) = (uint32_t)(self + 0x1424);
    *(uint32_t*)(self + 0x1420) = 0;
    *(uint32_t*)(self + 0x1414) = (uint32_t)(self + 0x1624);
    *(uint32_t*)(self + 0x1624) = 0;
    ((Gonzago*)(self + 0x1628))->ctor();
    *(uint32_t*)(self + 0x1648) = 0;
    *(uint32_t*)(self + 0x164c) = 0;
    *(uint32_t*)(self + 0x1650) = 1;
    *(float*)(self + 0x1654) = 0.0f;
    *(float*)(self + 0x1658) = 0.0f;
    *(float*)(self + 0x165c) = 0.0f;
    *(float*)(self + 0x1660) = 0.0f;
    *(uint32_t*)(self + 0x1664) = 5;
    *(uint32_t*)(self + 0x1668) = 0;
    self[0x166d] = 0;
    *(uint32_t*)(self + 0x1670) = 0;
    *(uint32_t*)(self + 0x1674) = 0;
    *(uint32_t*)(self + 0x1678) = 0;
    *(float*)(self + 0x167c) = 0.0f;
    *(uint32_t*)(self + 0x1680) = 0;
    *(uint32_t*)(self + 0x1684) = 0;
    *(uint32_t*)(self + 0x1688) = 0;
    *(float*)(self + 0x168c) = 0.0f;
    *(float*)(self + 0x1690) = 0.0f;
    *(float*)(self + 0x1694) = 0.0f;
    *(uint32_t*)(self + 0x1698) = 0;
    *(float*)(self + 0x169c) = 0.0f;
    *(uint32_t*)(self + 0x2b0) = 0;
    void* eax = FUN_00b3d310();
    void* v = FUN_00c06000();
    ((Fn421b0*)(self + 0xc0))->f(v);
    (void)eax;
    void* mem = operator_new(0xe4, "Simulator/cAIMemory", 0, 0, 0, 0);
    if (mem != 0) { ((Fnbc9c10*)mem)->ctor(); }
    else mem = 0;
    FUN_00d7ca90(self);
    *(void**)(self + 0x1624) = mem;
    ((SPTimer*)(self + 0xfc0))->Restart();
}

// @ 0x00c06bf0
void** __thiscall VErase::erase(void** first, void** last)
{
    memmove(first, last, (char*)mpEnd - (char*)last);
    mpEnd = mpEnd - (last - first);
    return first;
}

// @ 0x00c06c30
void __thiscall V32::insert(E32* pos, E32* val)
{
    E32* end = mpEnd;
    if (end != mpCapacity) {
        if (pos <= val && val < end) val = val + 1;
        *end = *(end - 1);
        E32* q = end - 1;
        E32* d = end;
        while (q != pos) { --q; --d; *d = *q; }
        *pos = *val;
        mpEnd = end + 1;
        return;
    }
    int n = (int)(end - mpBegin);
    int cap;
    E32* buf;
    if (n <= 0) { cap = 1; }
    else { cap = n * 2; if (cap == 0) { buf = 0; goto haveBuf; } }
    buf = (E32*)operator_new(cap << 5, "Simulator", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
haveBuf:
    E32* r = FUN_00c033a0(mpBegin, pos, buf);
    if (r) *r = *val;
    E32* r2 = FUN_00c033a0(pos, mpEnd, r + 1);
    E32* old = mpBegin;
    if (old != 0 && *(int*)((char*)old - 4) != 0) operator_delete__(old);
    mpEnd = r2;
    mpBegin = buf;
    mpCapacity = (E32*)((char*)buf + (cap << 5));
}

// @ 0x00c06d60
void __cdecl FUN_00c06d60(P* first, P* last, int depth, P key)
{
    while ((int)((char*)last - (char*)first) > 0x70) {
        if (depth <= 0) break;
        unsigned n = (unsigned)((char*)last - (char*)first);
        int mid = ((int)(n >> 2)) / 2;
        P* pm = first + mid;
        P* pl = last - 1;
        float a = *(float*)*first;
        float b = *(float*)*pm;
        float c = *(float*)*pl;
        P* pivot = pm;
        if (b > a) {
            if (c > b) pivot = pl;
            else if (c > a) pivot = first;
        } else {
            if (c > a) pivot = first;
            else if (c > b) pivot = pl;
        }
        P piv = *pivot;
        P* i = first;
        P* j = last;
        for (;;) {
            while (*(float*)*i <= *(float*)piv && *(float*)piv != *(float*)*i) ++i;
            do { --j; } while (*(float*)piv < *(float*)*j);
            if (i >= j) break;
            P t = *i; *i = *j; *j = t;
            ++i;
        }
        FUN_00c06d60(i, last, --depth, key);
        last = i;
    }
    if (depth == 0) FUN_00c06630(first, last, last, key);
}

// @ 0x00c06e50
void __thiscall CCBeh::funcC4h()
{
    char* self = (char*)this;
    ((Fn1fe80*)self)->f();
    FUN_00c0d3a0(self);
    ((Fn9de0*)(self + 0x1624))->f(-1);
    ERASE_ALL(self, 0x108c);
    ERASE_ALL(self, 0x1124);
    ERASE_ALL(self, 0x133c);
    ERASE_ALL(self, 0x13d4);
    ERASE_ALL(self, 0x140c);
    ((Fn05ee0*)(self + 0x1034))->f();
    ((Fn05ee0*)(self + 0x1060))->f();
    (*(void(__thiscall**)(void*,int))((*(void***)self)[0x48/4]))(self, -1);
}

// @ 0x00c06f70
void __thiscall CTick::Tick()
{
    char* self = (char*)this;
    if (((*(uint32_t*)(self + 0xb58) >> 9) & 1) != 0) return;
    void* ebp = 0;
    void* gm = SP_GetCurrentGameMode();
    if (gm == (void*)0x1654c10) {
        void* d = FUN_00b18530(self);
        if (d != 0) {
            void* p = *(void**)0x16c7aa4;
            void* q = *(void**)((char*)p + 0x74);
            int idx = (int)FUN_00f3c0e0(q);
            ebp = (char*)*(int*)((char*)d + 0x70) + idx * 0x4e0;
        }
    }
    void* g = *(void**)0x16c7aa4;
    void* a = *(void**)((char*)g + 0x78);
    void* edi = *(void**)((char*)a + 0xb8);
    void* vt = *(void**)self;
    int v;
    v = (*(int(__thiscall**)(void*,void*))((*(void***)(self + 0xc0))[0x2c/4]))((void*)(self + 0xc0), (void*)(self + 0x1648));
    FUN_00d9a290(edi, *(void**)(self + 0x18), (void*)v);
    edi = self + 0x5a8;
    ((Fnbfc470*)edi)->f(*(uint8_t*)((char*)ebp + 1));
    if (*(uint8_t*)((char*)ebp + 2) != 0) {
        if (((Fn8e7f80*)edi)->f() != 2) {
            float f = *(float*)(self + 0x5e0) + *(float*)0x1485720;
            (*(void(__thiscall**)(void*,float,int,int,void*,int))((*(void***)edi)[0x18/4]))(
                edi, f, -1, 2, (void*)0x168d8c4, 0);
            ((Fnbfc460*)edi)->f(2);
            bool b = ((Fnc0c0e0*)self)->f(-1, 1);
            ((Fnc12310*)self)->f((int)(0x5807346 - (b ? 1 : 0)));
            self[0xb5e] = 1;
        }
    } else {
        int n = *(int*)((char*)*(void**)((char*)*(void**)0x16c7aa4 + 0x78) + 0xb8);
        if (n > 0) {
            void* d = FUN_00b18530(self);
            if (d != 0 && *(uint8_t*)((char*)*(int*)((char*)d + 0x70) + n * 0x4e0 - 0x4de) == 1) {
                (*(void(__thiscall**)(void*,int))((*(void***)edi)[0x2c/4]))(edi, 0);
                self[0xb5e] = 0;
            }
        }
    }
    if (*(uint8_t*)((char*)ebp + 0x4c8) == 0) {
        int n = *(int*)((char*)*(void**)((char*)*(void**)0x16c7aa4 + 0x78) + 0xb8);
        if (n <= 0) {
            ((Fnc7dc20*)(self + 0x670))->f();
            void* fl = *(void**)(self + 0xb4c);
            bool b = ((Fnc0c0e0*)self)->f(-1, 1);
            *(int*)((char*)fl + 0x5fc) |= ((b ? -1 : 0) & 0x80);
        } else {
            void* d = FUN_00b18530(self);
            void* e = (char*)*(int*)((char*)d + 0x70) + n * 0x4e0 - 0x4e0;
            if (((Fnf25080*)ebp)->f(e)) {
                FUN_00bc97f0((char*)*(void**)(self + 0xb4c) + 8, 0x8000000, 0, *(float*)0x1469e30, 0);
            }
        }
    }
    void* fl = *(void**)(self + 0xb4c);
    *(int*)((char*)fl + 0x5fc) &= 0xfdfffff;
    fl = *(void**)(self + 0xb4c);
    *(int*)((char*)fl + 0x5fc) &= 0xfffdffff;
    if (*(uint8_t*)((char*)ebp + 0x4c8) == 0) {
        switch (*(int*)((char*)ebp + 0x4ac)) {
        case 1: *(int*)((char*)fl + 0x5fc) |= 0x10000000; break;
        case 2: *(int*)((char*)fl + 0x5fc) |= 0x40000000; break;
        case 3: *(int*)((char*)fl + 0x5fc) |= 0x80000000; break;
        case 4: *(int*)((char*)fl + 0x5fc) |= 0x200000; break;
        case 5: *(int*)((char*)fl + 0x5fc) |= 0x20000000; break;
        }
        if (*(int*)((char*)ebp + 0x4b8) == 1) {
            fl = *(void**)(self + 0xb4c);
            *(int*)((char*)fl + 0x5fc) |= 0x20000;
        }
    }
    int r = (*(int(__thiscall**)(void*))((*(void***)self)[0xd8/4]))(self);
    if (r > 4) {
        fl = *(void**)(self + 0xb4c);
        *(int*)((char*)fl + 0x5fc) |= 0x200;
    }
    (*(void(__thiscall**)(void*))((*(void***)(self + 0xc0))[0xf4/4]))((void*)(self + 0xc0));
    *(float*)(self + 0x32c) = *(float*)((char*)ebp + 0x484);
}

// @ 0x00c072b0
void __thiscall V32B::push_back(E32* p)
{
    E32* e = mpEnd;
    if (e < mpCapacity) { mpEnd = e + 1; if (e) *e = *p; }
    else { ((V32*)this)->insert(e, p); }
}

// @ 0x00c072f0
void __thiscall V4::push_back(P* p)
{
    P* e = mpEnd;
    if (e < mpCapacity) { mpEnd = e + 1; if (e) *e = *p; }
    else { ((V4Stub*)this)->insert(e, p); }
}

// @ 0x00c073a0
void __thiscall CSetId::set(int id)
{
    char* self = (char*)this;
    *(int*)(self + 0xe8c) = id;
    if (id == -1) {
        *(int*)(self + 0xe90) = -1;
        *(float*)(self + 0xe94) = 0.0f;
        P* end = *(P**)(self + 0xe9c);
        P* beg = *(P**)(self + 0xe98);
        memmove(beg, end, (char*)end - (char*)end);
        int d = (int)end - (int)beg; d >>= 2; d = -d; d += d; d += d;
        *(int*)(self + 0xe9c) += d;
    }
}

// @ 0x00c07400
void __thiscall CCCh::funcCCh(int a)
{
    char* self = (char*)this;
    ((Fn1c9f0*)self)->f(a);
    self[0xe38] = 0;
    ((SPTimer*)(self + 0xfc0))->Restart();
    ((Fn3170*)(self + 0xfe0))->f();
    *(float*)(self + 0x1000) = 0.0f;
    _ReadWriteBarrier();
    {
        P* const last = *(P**)(self + 0x1024);
        P* const first = *(P**)(self + 0x1020);
        memmove(first, last, (char*)*(P**)(self + 0x1024) - (char*)last);
        int d = (int)last - (int)first; d >>= 2; d = -d; d += d; d += d;
        *(int*)(self + 0x1024) += d;
    }
    *(uint32_t*)(self + 0x1678) = 0;
    *(uint32_t*)(self + 0x101c) = 0;
}

// @ 0x00c07480
void cCreatureAnimal::TakeDamage(float damage, uint32_t attackerPoliticalID, int damageType, const Vector3_s00c0_7480& direction, cCombatant_s00c0_7480* pAttacker)
{
    if (GetDamageState() == 2)
        return;
    if (damage < 1.5258789e-05f)
        return;

    if (damageType == 3 && pAttacker) {
        // charm damage
        if (pAttacker == mpCharmer.get()) {
            mCharmDamage += damage;
        }
        else {
            float charm = damage;
            if (mpCharmer.get()) {
                cGameData_s00c0_7480* pCharmer = mpCharmer.get()->ToGameData();
                if (pAttacker->ToGameData()->GetPoliticalID() == pCharmer->GetPoliticalID())
                    charm = mCharmDamage + damage;
            }
            mCharmDamage = charm;
            mpCharmer = pAttacker;
        }

        if (mCharmDamage >= (IsEpic() ? kCharmThresholdEpic : kCharmThreshold)) {
            mCharmTime = kCharmDuration;
            mCharmDamage = 0.0f;
            if (GetCurrentGameMode() == kGameCiv
                && attackerPoliticalID == GameNounManager()->GetPlayerPoliticalID()
                && IsEpic())
            {
                cCivilization* pCiv = GameNounManager()->GetPlayerCivilization();
                ResourceKey_s00c0_7480 key(0, 0, 0);
                LogEvent(0x13525C87, &GameNounManager()->GetPlayerCivilization()->GetSpeciesProfile()->mCreatureKey,
                         &mpSpeciesProfile->mCreatureKey, &key, pCiv->GetIdentityColor(), 0, 0);
                AudioManager()->PlayForSpecies(0x280FCA87, GetSpeciesKey());
            }
        }
        else {
            cBehaviorEvent* pEvent = mpBehaviorTree->mEvents.Add(0x400, 0, 4.0f, pAttacker->ToGameData());
            if (pEvent) {
                pEvent->field_0C = 3;
                *(float*)&pEvent->field_10 = mCharmDamage;
            }
        }
        return;
    }

    cCreatureBase_s00c0_7480::TakeDamage(damage, attackerPoliticalID, damageType, direction, pAttacker);

    cCreatureBase_s00c0_7480* pAttackerCreature;
    cCreatureAnimal* pAttackerAnimal = 0;
    if (pAttacker) {
        pAttackerCreature = (cCreatureBase_s00c0_7480*)pAttacker->Cast(kCreatureBaseType);
        cGameData_s00c0_7480* pData = pAttacker->ToGameData();
        if (pData && pData->GetNounID() == kCreatureAnimalNoun)
            pAttackerAnimal = (cCreatureAnimal*)pData;
    }
    else {
        pAttackerCreature = 0;
    }

    bool bIsAvatar = IsPlayerAvatar();
    mNoDamageTimer.Restart();
    SetStealthed(0, 0);

    if (GetCurrentGameMode() == kScenarioMode) {
        if (bIsAvatar) {
            {
                cDamageMessage msg(0x7C6551E);
                msg.mDamage = damage;
                MessageServer()->PostMSG(msg.mMessageID, &msg, 0);
            }
            if (!GetCombatantTarget() && pAttacker && IsValidRetaliationTarget(pAttacker))
                AttackTarget(pAttacker, 1, 0);
        }
        if (GetDamageState() == 2) {
            if (bIsAvatar) {
                g_pCameraManager->field_68->field_54 = false;
                cCameraMode* pMode = g_pCameraManager->field_78;
                if (pMode && pMode->mMode == 3) {
                    pMode->SetLock(0);
                    pMode->SetMode(6);
                }
            }
            CombatAlertManager()->AlertCreatures(GetPosition(), GetBoundingRadius(), 1, GetPoliticalID());
        }
    }

    if ((pAttackerAnimal && pAttackerAnimal->IsPlayerAvatar()) || GetDamageState() == 2) {
        int index = field_B48->Find(1, 1, 0, 0);
        if (index != -1)
            field_B48->Stop(index);
        index = field_B48->Find(2, 1, 0, 0);
        if (index != -1)
            field_B48->Stop(index);
    }

    if (pAttackerCreature && pAttackerCreature->IsPlayerAvatar())
        mLastAvatarDamageTimer.Restart();

    if (pAttacker || GetDamageState() == 2) {
        cGameData_s00c0_7480* pSource = pAttacker ? pAttacker->ToGameData() : 0;
        cBehaviorEvent* pEvent = mpBehaviorTree->mEvents.Add(0x400, 0, 10.0f, pSource);
        if (pEvent) {
            pEvent->field_0C = damageType;
            if (bIsAvatar)
                PosseSimulator()->OnEvent(0x400, 0);
        }
    }

    bool bProvoked;
    if (pAttackerAnimal) {
        if (pAttackerAnimal->IsMoving())
            bProvoked = true;
        else if (RelationshipManager()->GetRelationship(&pAttackerAnimal->mSpeciesKey,
                     GameNounManager()->GetAvatar(), pAttackerAnimal) == 6
                 && mLastAvatarDamageTimer.IsRunning()
                 && (float)mLastAvatarDamageTimer.GetElapsedTime() * 0.001f < kAvatarProvokeTime)
            bProvoked = true;
        else
            bProvoked = false;
    }
    else {
        bProvoked = false;
    }

    bool bRetaliate;
    if (pAttackerCreature && pAttackerCreature->IsMoving() && !IsBusy()) {
        bRetaliate = true;
        RelationshipManager()->ApplyEvent(2, &mSpeciesKey, this);
    }
    else {
        bRetaliate = false;
    }

    int eventType;
    cCreatureBase_s00c0_7480* pExclude;
    if (GetDamageState() == 2) {
        if (bProvoked) {
            float value = GetAttackDamage(0);
            NotifyCreatureKilled(value);
            GameNounManager()->GetPlanet()->OnCreatureKilled(value, 0);
        }
        if (bRetaliate || bProvoked)
            RelationshipManager()->ApplyEvent(IsBaby() ? 0 : 5, &mSpeciesKey, this);

        if (pAttackerAnimal) {
            if (bIsAvatar)
                RelationshipManager()->ApplyEvent(1, &pAttackerAnimal->mSpeciesKey, pAttackerAnimal);
            if (pAttackerAnimal->IsEpic() && GetCurrentGameMode() == kGameTribe)
                AudioManager()->PlayForSpecies(0x6E77F36F, &pAttackerAnimal->GetSpeciesProfile()->mCreatureKey);
        }

        eventType = 0x80000;
        pExclude = pAttackerAnimal;
        if (bIsAvatar && GetCurrentGameMode() == kGameCreature) {
            cKillInfo info;
            info.mpVictim = this;
            info.field_4 = 0;
            info.mDamageType = damageType;
            CreatureModeStrategy()->OnCreatureEvent(0xD3353639, &info);
            CreatureModeStrategy()->SignalCreatureEvent(0xD3353639);
            AchievementsController()->Trigger(0xD456D958, 2, 1);
            cCreatureStatRecord* pRecord = CreatureModeStrategy()->AddStat(5, 3);
            pRecord->mpStat->field_34 = damageType;
            if (pAttackerAnimal) {
                cPollinator* pPollinator = AudioManager()->field_58;
                if (pPollinator) {
                    cServerID id;
                    id.a = 0xFFFFFFFF;
                    id.b = 0xFFFFFFFF;
                    if (pPollinator->GetServerID(pAttackerAnimal->GetSpeciesKey(), &id, 0)
                        && (id.a & id.b) != 0xFFFFFFFF)
                    {
                        pRecord->mpStat->field_2C = id.b;
                        pRecord->mpStat->field_30 = id.a;
                    }
                }
            }
        }

        if (mpHerd && mpHerd->mpLeader == this) {
            for (cNearbyIterator it(mNearby, cNearbyFilter()); it.mpCurrent != it.mpEnd; it.Next()) {
                cCreatureBase_s00c0_7480* pCreature = (*it.mpCurrent)->mpCreature;
                if (pCreature && pCreature->GetNounID() == kCreatureAnimalNoun && !pCreature->IsBaby()
                    && pCreature->mpSpeciesProfile == mpSpeciesProfile)
                {
                    pCreature->mpBehaviorTree->mEvents.Add(0, 2, 10.0f, pAttackerCreature);
                }
            }
        }

        if (GetCurrentGameMode() == kGameCiv
            && attackerPoliticalID == GameNounManager()->GetPlayerPoliticalID()
            && IsEpic())
        {
            cCivilization* pCiv = GameNounManager()->GetPlayerCivilization();
            ResourceKey_s00c0_7480 key(0, 0, 0);
            LogEvent(0x1ECB526C, &GameNounManager()->GetPlayerCivilization()->GetSpeciesProfile()->mCreatureKey,
                     &mpSpeciesProfile->mCreatureKey, &key, pCiv->GetIdentityColor(), 0, 0);
        }
    }
    else {
        if (bRetaliate && pAttackerCreature && pAttackerCreature->IsPlayerAvatar() && !mbDead
            && damageType != 7 && !IsEpic())
        {
            StopAttacking(1);
            SetIntention(-1);
        }
        pExclude = this;
        eventType = 0x200;
    }

    if (pAttackerCreature) {
        int defenders = 0;
        int alertRadius = 0;
        if (eventType == 0x200 && defenders == 0 && mpHerd) {
            cSpeciesArchetype_s00c0_7480* pArchetype = SpeciesArchetypeManager()->GetArchetype(mpHerd->field_88, mpHerd->field_F0);
            if (pArchetype) {
                int busy = 0;
                if (mpBehaviorTree->mTreeID == 0x2D852E6 && mpBehaviorTree->field_600)
                    busy = mpBehaviorTree->field_600->field_10 - 1;
                defenders = Max(pArchetype->mMaxDefenders - busy, 0);
                alertRadius = (int)pArchetype->mAlertRadius;
            }
        }

        for (cNearbyIterator it(mNearby, cNearbyFilter()); it.mpCurrent != it.mpEnd; it.Next()) {
            cCreatureBase_s00c0_7480* pCreature = (*it.mpCurrent)->mpCreature;
            bool bDefend = false;
            if (pCreature && pCreature->GetNounID() == kCreatureAnimalNoun && !pCreature->mbDead
                && !pCreature->IsPlayerAvatar() && pCreature != pExclude)
            {
                bool bSameSpecies = pCreature->mpSpeciesProfile == mpSpeciesProfile;
                cBehaviorEvent* pEvent = pCreature->mpBehaviorTree->mEvents.Add(eventType, 0, 5.0f, pExclude);
                pEvent->field_0C = bSameSpecies;
                pEvent->field_10 = (int)pAttackerCreature;
                if (defenders > 0 && pCreature->mpSpeciesProfile == mpSpeciesProfile) {
                    if (DistanceBetween(static_cast<cCreatureBase_s00c0_7480*>(this), pCreature, 1) <= alertRadius) {
                        defenders--;
                        bDefend = true;
                    }
                }
                pEvent->field_14 = bDefend;
                ((cCreatureAnimal*)pCreature)->mpPerception->Alert(0x21, 15.0f, pExclude, 0);
            }
        }

        if (GetCurrentGameMode() == kGameTribe) {
            TribeReactions()->React(0xB9D14C31, GetPosition(),
                                    pAttackerCreature->GetBoundingRadius() + GetBoundingRadius(),
                                    5.0f, pAttackerCreature, this);
        }
    }

    if (bIsAvatar && GetCurrentGameMode() == kGameCreature)
        CreatureModeStrategy()->SignalCreatureEvent(0x533535DE);
}

// @ 0x00c080b0
void cCreatureBase_s00c0_80b0::func8Ch()
{
    // stop the running behaviour (agent embedded at +0x58, vtable slot +0x34)
    ((void (__thiscall*)(void*))VTC(&agent58, 0x34))(&agent58);

    // SetCreatureTarget(null, null, false) on the creature itself (vtable slot +0x84)
    ((void (__thiscall*)(void*, int, int, int))VTC(this, 0x84))(this, 0, 0, 0);

    mbSelfPowered = 0;
    f5e0 = 0.0f;

    // build the locomotion parameter block
    AttackParams p;
    p.qx = DAT_0168d844;
    p.qy = DAT_0168d848;
    p.qz = DAT_0168d84c;
    p.qw = 1.0f;
    p.f60 = 2.0f;
    p.f64 = 0.9f;
    p.mpBegin = 0;
    p.mpEnd = 0;
    p.mpCapacity = 0;
    p.i24 = 0;
    p.b4c = 0;
    p.f50 = 0.0f;
    p.f54 = 0.0f;
    p.f58 = 0.0f;
    p.i5c = 0;
    p.f68 = 3.402823466e+38F;
    p.f6c = 0.0f;
    p.i70 = 0;

    // locomotion agent (embedded at +0xc0), vtable slot +0xdc
    ((void (__thiscall*)(void*, AttackParams*))VTC(&agentC0, 0xdc))(&agentC0, &p);

    // release the eastl vector<bool> buffer the call may have allocated
    if (p.mpBegin != 0) {
        AllocHeader* hdr = (AllocHeader*)p.mpBegin - 1;
        if (hdr->mOwner != 0) {
            char* block = (char*)p.mpBegin;
            delete[] block;
        }
    }

    FUN_00c0cff0(0);
    agentC0.FUN_00c41d60(&DAT_0168d844);

    fE8C = -1;
    fE90 = -1;
    fE94 = 0.0f;

    char* const begin = mpE98;
    FUN_011e0744(begin, mpE9C, 0);
    mpE9C += -((int)(mpE9C - begin) >> 2) * 4;

    fE3C = -1;
    FUN_00c0d240();
    mbDead = 1;
    mpAttackState->FUN_00bc9de0(-1);
    FUN_00c17350(0x2c4bf1c, 0);

    if (FUN_00b3d310() != 0)
        ((cGlobalManager*)FUN_00b3d310())->FUN_00b45410(&agentC0);
}

// @ 0x00c08270
void cGameData_s00c0_80b0::RemoveOwner()
{
    FUN_00c0d3a0(this);
    mpAttackState->FUN_00bc9de0(-1);

    if (this == (cGameData_s00c0_80b0*)((cGameNounManager_s00c0_80b0*)SP_NounManager())->GetAvatar())
        ((cGameNounManager_s00c0_80b0*)SP_NounManager())->FUN_00b1fd50(0);

    if (flagsB58.mbOwned)
        ((cPosseSimulator_s00c0_80b0*)SP_PosseSimulator())->RemovePosseMember(this, 0, 1);

    void* agent = &agent58;
    cBehaviorManager* bm = (cBehaviorManager*)SP_BehaviorManager();
    ((void (__thiscall*)(void*, void*))VTC(bm, 0x3c))(bm, agent);

    ((void (__thiscall*)(void*, int, int, int))VTC(this, 0x84))(this, 0, 0, 0);

    if (mp1674 != 0) {
        cGameData_s00c0_80b0* tmp = this;
        remove_1st((char*)mp1674 + 0x40, &tmp);
    }
    if (mp1674 != 0) {
        void* obj = mp1674;
        mp1674 = 0;
        ((void (__thiscall*)(void*))VTC(obj, 0x04))(obj);
    }

    void* obj = mp1698;
    mp1698 = 0;
    if (obj != 0)
        ((void (__thiscall*)(void*))VTC(obj, 0x64))(obj);

    FUN_00c1c8e0();
}

// @ 0x00c09410
void CCM_s00c0_9410::FUN_00c09410(int param_2)
{
	char* self = (char*)this;
	if (*(int*)(*(int*)(self + 0xb4c)) == 0)
		return;

	void* nounMgr = FUN_00b3d300();
	int* avatar = (int*)((M*)nounMgr)->FUN_00b1fdb0();

	int bVar6 = 0;
	int bVar7 = 0;
	int* piVar18 = 0;
	char cVar8 = 0;

	if (*(char*)(self + 0xb5e) == 0 && avatar != 0)
	{
		float fVar20 = FUN_00d38a30(1, this);
		float fVar21 = FUN_00d38a30(2, this);
		float fVar22 = ((M*)this)->FUN_00c0e4f0() * fVar21;
		float fVar23 = ((M*)this)->FUN_00c0c010();
		void* piVar1 = self + 0xc0;
		float cosVal = (float)cos(fVar23 * 0.008726646f);

		float outv[4];
		vv1(piVar1, 0x5c, outv);
		float* pfVar12 = (float*)vp0(piVar1, 0x2c);
		float fThis74 = vf0(piVar1, 0x74);
		piVar18 = (int*)(int)fThis74;

		float* pfVar13 = (float*)vp0((char*)avatar + 0xc0, 0x2c);
		float fDx = pfVar13[0] - pfVar12[0];
		float fDy = pfVar13[1] - pfVar12[1];
		float fDz = pfVar13[2] - pfVar12[2];
		float fLen = FUN_00c02690(&fDx);
		float fAv74 = vf0((char*)avatar + 0xc0, 0x74);

		float fGap = fLen - (fAv74 + fThis74);
		float fStack_10 = 0.0f;
		if (0.0f <= fGap)
			fStack_10 = fGap;

		float fDot = outv[0] * fDx + outv[1] * fDy + outv[2] * fDz;

		cVar8 = ((M*)avatar)->FUN_00c0c130();
		if (cVar8 != 0 || fVar22 < fStack_10 || fDot < cosVal)
			cVar8 = 0;
		else
			cVar8 = 1;

		char cVar9 = ((M*)this)->FUN_00c0d560(avatar, fVar20, fStack_10);

		if (cVar8 == 0 && cVar9 == 0)
		{
			cVar8 = (char)vi0(piVar1, 0x58);
			if (cVar8 == 0 && (cVar8 = (char)vi0(self, 0xd0)) == 0 &&
				(cVar8 = ((M*)avatar)->FUN_00c0c130()) != 0)
			{
				float fVar2 = (float)avatar[0x400];
				float fB = ((M*)this)->FUN_00c0c040();
				int bVar5;
				if (fVar2 <= 1.5258789e-05f || (fB * fVar20 + fVar2) <= fStack_10)
					bVar5 = 0;
				else
					bVar5 = 1;
				int bVar4;
				if (fVar22 < fStack_10 || fDot < cosVal)
					bVar4 = 0;
				else
					bVar4 = 1;
				int iVar14 = ((M*)avatar)->FUN_00c0c140();
				if ((bVar5 || bVar4) && iVar14 != -1)
				{
					iVar14 = (int)vp1(avatar, 0xb4, (void*)iVar14);
					if (iVar14 != 0 &&
						(bVar5 || (bVar4 && fStack_10 < *(float*)(iVar14 + 0xa8))))
					{
						bVar7 = 1;
						piVar18 = avatar;
						bVar6 = 0;
						if (bVar4)
						{
							int t = ((*(unsigned*)((char*)avatar + 0xb58)) >> 9) & 1;
							float fBound = ((M*)(void*)iVar14)->FUN_004d3d70(t);
							if (fStack_10 < fBound)
								bVar6 = 1;
						}
					}
				}
			}
		}
		else
		{
			char* cnt = self + 0x1034;
			if (*(int*)(self + 0x103c) != *(int*)(self + 0x104c))
			{
				int iVar14 = (int)((M*)cnt)->FUN_00c05e80();
				if (*(int*)(iVar14 + 0x10) == (int)avatar)
					((M*)cnt)->FUN_00c05ea0();
			}
			void* vEnd = *(void**)(self + 0x1128);
			void* uVar16 = FUN_00c04820(*(void**)(self + 0x1124), vEnd,
										 (void*)FUN_00c02790, vEnd);
			((M*)(self + 0x1124))->FUN_00c06bf0(uVar16);
			void* res67 = FUN_00c06750(cnt, avatar, fStack_10, cVar8, 0);
			((M*)(self + 0x1124))->FUN_00c072f0(&res67);
			FUN_00c07320(*(void**)(self + 0x1124), *(void**)(self + 0x1128),
						 (void*)param_2);
			bVar6 = 1;
			((M*)(void*)(*(int*)(self + 0xb4c) + 8))->FUN_00bc97f0(0x4000000, 0,
																	0x40a00000f, avatar);
			piVar18 = avatar;
		}
	}

	// LAB_00c097f2
	if (avatar != 0)
	{
		void* creature = (void*)(*(int*)(self + 0xb4c) + 8);
		int iVar14 = ((M*)creature)->FUN_00bc96a0(0x4000000, 0);
		if (iVar14 == 0)
			*(char*)(self + 0xfb9) = 1;
		if (bVar6)
		{
			if (piVar18 != 0 && ((M*)piVar18)->FUN_00c0c130() != 0)
				((M*)creature)->FUN_00bc97f0(0, 8, 0x41200000f, piVar18);
			*(int*)(self + 0x101c) = 1;
		}
		else if (bVar7)
		{
			if (piVar18 != 0 && ((M*)piVar18)->FUN_00c0c130() != 0)
				((M*)creature)->FUN_00bc97f0(0x100, 0, 0x41200000f, piVar18);
			*(int*)(self + 0x101c) = 2;
		}
		else
		{
			*(int*)(self + 0x101c) = 0;
		}
	}

	// LAB_00c098a5
	{
		int iVar14 = *(int*)(self + 0xeac);
		unsigned uVar19 = ((unsigned)*(int*)(self + 0xb58) >> 8 & 1)
			| ((((*(unsigned*)(self + 0x110) & 0x100) != 0x100) ? 0xffffe000u : 0u) + 0x2000u)
			| *(unsigned*)(*(int*)(self + 0xb4c) + 0x5fc);
		if (iVar14 == 0)
			uVar19 |= 0x40000u;
		else if (iVar14 == 1)
			uVar19 |= 0x80000u;
		else if (iVar14 == 2)
			uVar19 |= 0x100000u;

		void* agentOrderMgr = *(void**)(self + 0xb48);
		int slot1 = (int)((M*)agentOrderMgr)->FUN_00bca0c0(1, 1, 0, 0);
		int slot2 = (int)((M*)agentOrderMgr)->FUN_00bca0c0(2, 1, 0, 0);
		void* creature = (void*)(*(int*)(self + 0xb4c) + 8);
		void* uVar16 = ((M*)creature)->FUN_00bc9980((float)param_2);
		void* gtMgr = FUN_00b3d380();
		long long uVar25 = ((M*)gtMgr)->FUN_00b316c0();
		double dTime = (double)(uVar25 & 0x7fffffffffffffffLL) * 0.0010000000474974513;
		int* puVar3 = *(int**)(self + 0xb4c);
		FUN_00d995f0((float)param_2, dTime, (void*)puVar3[0], self,
					 (void*)(puVar3 + 0x74), (void*)puVar3[0x17a],
					 (void*)(uVar19
							 | (slot1 != -1 ? 0x2000000u : 0u)
							 | (slot2 != -1 ? 0x4000000u : 0u)),
					 uVar16);
	}
}

// @ 0x00c099e0
extern "C" int* FUN_00c099e0(int a1, int* profile, int a3, int a4, int flagA, int flagB)
{
	char* p2 = (char*)profile;
	int* piVar4 = (int*)FUN_0067cb40();
	int* piVar12 = (int*)(p2 + 0x504);
	vv2(piVar4, 0x58, piVar12, (void*)1);

	int useFallback = 1;
	if (flagB != 0)
	{
		int* p = (int*)((M*)FUN_00b3d480())->FUN_00ad20e0(profile, (void*)piVar12);
		if (p != 0 && vp0(p, 0x20) == (void*)0x18eb45e)
		{
			piVar4 = p;
			useFallback = 0;
		}
	}
	if (useFallback)
	{
		void* nounMgr = FUN_00b3d300();
		int* p = (int*)((M*)nounMgr)->FUN_00b20c60(0x18eb45e);
		if (p == 0)
			piVar4 = 0;
		else
			piVar4 = (int*)vp1(p, 0xc, (void*)0xd0036e08);
	}

	*(int*)((char*)piVar4 + 0xb34) = (int)piVar12;
	if (*(int*)((char*)piVar4 + 0x1674) != 0)
		((M*)(void*)*(int*)((char*)piVar4 + 0x1674))->FUN_00c6b440(piVar4);
	{
		int* piVar13 = (int*)*(int*)((char*)piVar4 + 0x1674);
		if (piVar12 != piVar13)
		{
			if (piVar12 != 0)
				vv0(piVar12, 0);
			*(int*)((char*)piVar4 + 0x1674) = (int)piVar12;
			if (piVar13 != 0)
				vv0(piVar13, 4);
		}
	}

	int iVar7 = (int)((M*)FUN_00401090())->FUN_004df420();
	if (piVar12 != 0)
	{
		void* uVar8;
		if (profile == (int*)iVar7)
			uVar8 = ((M*)FUN_00401090())->FUN_004e01b0();
		else
			uVar8 = ((M*)FUN_00401090())->FUN_004e0050(*(int*)(p2 + 0x58c),
													   *(int*)(p2 + 0x5f4));
		((M*)piVar4)->FUN_00c0c180(uVar8);
	}
	if (flagA != 0)
	{
		((M*)FUN_00b3d300())->FUN_00b1fd50(piVar4);
		void* setting = FUN_00401090();
		if (profile != (int*)iVar7)
			((M*)setting)->FUN_004df3e0(profile);
	}

	char cVar3 = ((M*)piVar4)->FUN_00c037c0(profile, (void*)flagA, 0);
	if (cVar3 == 0)
	{
		((M*)FUN_00b3d300())->FUN_00b225d0(piVar4);
		return 0;
	}

	cVar3 = ((M*)piVar4)->FUN_00c0c0e0();
	if (cVar3 != 0)
	{
		*(float*)((char*)piVar4 + 0x2a8) = g_015d96b8;
		int gm = (int)FUN_00b5b800();
		int key = 0;
		if (gm == 0x1654c01)
			key = 0xf3ff72ef;
		else if ((gm = (int)FUN_00b5b800()) == 0x1654c02)
			key = 0x4f84bd4;
		if (key != 0)
		{
			void* pm = FUN_0067cb30(key, profile);
			((M*)pm)->FUN_0060d860((void*)key, profile);
		}
	}

	// LAB_00c09b8c
	((M*)piVar4)->FUN_00c0d9b0();
	if (piVar12 != 0)
	{
		int iVar14 = (int)((M*)piVar4)->FUN_00c0c1a0();
		if (iVar14 == 0)
		{
			int* q = *(int**)((char*)piVar4 + 0xb20);
			iVar14 = (int)FUN_00c02710((*(float*)((char*)q + 0x5b0)
										+ *(float*)((char*)q + 0x56c)) * 0.1f);
		}
		else
		{
			iVar14 = *(int*)(iVar14 + 0x330);
		}
		*(int*)((char*)piVar4 + 0xb88) = iVar14;

		int* pv = piVar4;
		vv0(piVar4, 0);
		int* puVar10 = *(int**)(p2 + 0x548);
		int* piVar13;
		if (puVar10 < *(int**)(p2 + 0x54c))
		{
			*(int**)(p2 + 0x548) = puVar10 + 1;
			piVar13 = piVar4;
			if (puVar10 != 0)
			{
				*puVar10 = (int)piVar4;
				vv0(piVar4, 0);
			}
		}
		else
		{
			FUN_00aea5d0(puVar10, &pv);
			piVar13 = pv;
		}
		if (piVar13 != 0)
			vv0(piVar13, 4);
	}

	if (flagA == 0)
	{
		vv1((char*)piVar4 + 0x5a8, 0x2c, (void*)1);
		float fVar1 = *(float*)((char*)piVar4 + 0x5e0);
		float fVar14 = FUN_00572a10(g_01687a54, g_01687a58);
		((M*)((char*)piVar4 + 0x5a8))->FUN_00f924e0(fVar14 * fVar1);
		if (piVar12 != 0 && *(int*)(p2 + 0x660) != 1 &&
			(int)FUN_00b5b800() != 0x1654c10)
		{
			int uVar8 = (int)((M*)piVar4)->FUN_00c0c1a0();
			float fVar14b = FUN_00c033d0((void*)uVar8);
			int iVar9;
			if (*(int*)(p2 + 0x5f8) < 1 || *(char*)(p2 + 0x588) != 0)
			{
				iVar9 = 0;
			}
			else
			{
				float fStack_2c = (float)*(int*)(p2 + 0x5f8) * fVar14b;
				iVar9 = (int)fStack_2c;
				if ((float)iVar9 < fStack_2c)
					iVar9 = iVar9 + 1;
			}
			if (0 < iVar9)
			{
				int iVar7b = 0;
				for (int* it = *(int**)(p2 + 0x544); it != *(int**)(p2 + 0x548); ++it)
				{
					if (*it != 0 && (*(unsigned char*)(*it + 0xb58) & 1) != 0)
						iVar7b = iVar7b + 1;
				}
				*(int*)((char*)piVar4 + 0xb58) |= (unsigned)(iVar7b < iVar9);
			}
		}
	}
	else
	{
		vv1((char*)piVar4 + 0x5a8, 0x2c, 0);
	}

	vv1((char*)piVar4 + 0xc0, 0x38, (void*)a1);

	float fAngle = g_01571278 * g_01471064;
	float s1 = (float)sin(fAngle);
	float f38 = g_0157127c * s1;
	float f3c = g_01571280 * s1;
	float f40 = s1 * g_01571284;
	float f44 = (float)cos(fAngle);

	float s2 = (float)sin(fAngle);
	float co = (float)cos(fAngle);
	float x0 = s2 * g_01571288;
	float x1 = s2 * g_0157128c;
	float x2 = s2 * g_01571290;
	float f20 = x2 * f3c - x1 * f40;
	float f24 = x0 * f40 - x2 * f38;
	float f28 = x1 * f38 - x0 * f3c;
	float f1c = co;

	float m10 = co * f38;
	float m14 = co * f3c;
	float m18 = co * f40;
	float r0 = f44 * x0 + m10 + f20;
	float r1 = x1 * f44 + m14 + f24;
	float r2 = x2 * f44 + m18 + f28;
	float r3 = f1c * f44 - (x2 * f40 + x0 * f38 + x1 * f3c);

	float q[4];
	q[0] = r0;
	q[1] = r1;
	q[2] = r2;
	q[3] = r3;

	float fStack_24 = f44;
	float w[4];
	void* puVar10 = FUN_0059aed0(q, (void*)a1, w);

	float uStack_3c = ((float*)puVar10)[0];
	float uStack_38 = ((float*)puVar10)[1];
	float uStack_34 = ((float*)puVar10)[2];
	void* planetModel = FUN_00b3d350();
	float auStack_20[6];
	((M*)planetModel)->FUN_00b7f250(auStack_20, (void*)a1, &uStack_3c);
	vv1((char*)piVar4 + 0xc0, 0x3c, auStack_20);

	((M*)piVar4)->FUN_00c0fb80(a1, (int)&fStack_24);
	((M*)piVar4)->FUN_00c0bbe0();
	((M*)piVar4)->FUN_00c042e0();
	vv0(piVar4, 0x54);
	*(int*)((char*)piVar4 + 0x2b0) = 0;
	void* behaviorMgr = FUN_00b3d260();
	vv1(behaviorMgr, 0x38, (char*)piVar4 + 0x58);

	if (flagA != 0)
	{
		*(char*)((char*)piVar4 + 0xbd) = 0;
		int iVar = *(int*)((char*)piVar4 + 0xb54);
		if (iVar != 0)
			*(int*)(iVar + 0x54) = 2;
	}
	FUN_00c035f0(piVar4);
	return piVar4;
}

// @ 0x00c0b000
bool __fastcall FUN_00c0b000(CB* self)
{
  return *(float*)((char*)self + 0xf4) > 0.0f &&
         *(int*)((char*)self + 0xf8) != -1;
}

// @ 0x00c0b030
int* __cdecl FUN_00c0b030(int* stream, char* data)
{
  // retail keeps the double temp in the 8-byte frame slot; the float and bool temps
  // share one 4-byte temp (float and bool bytes at the same address).
  void* inner = ((void* (__thiscall*)(void*))(*(void***)stream)[0x20 / 4])(stream);
  double v = *(double*)(data + 8);
  void* s = ((void* (__thiscall*)(void*))(*(void***)inner)[0x18 / 4])(inner);
  WriteUint64(s, &v, 1, 0);

  inner = ((void* (__thiscall*)(void*))(*(void***)stream)[0x20 / 4])(stream);
  union { float f; bool b; } u;
  u.f = *(float*)(data + 4);
  s = ((void* (__thiscall*)(void*))(*(void***)inner)[0x18 / 4])(inner);
  WriteUint32(s, &u.f, 1, 0);

  inner = ((void* (__thiscall*)(void*))(*(void***)stream)[0x20 / 4])(stream);
  char b0 = *data;                 // kept across the vcall (ebx in the retail build)
  s = ((void* (__thiscall*)(void*))(*(void***)inner)[0x18 / 4])(inner);
  u.b = b0 != 0;
  StreamWriteBool(s, &u.b, 1);

  inner = ((void* (__thiscall*)(void*))(*(void***)stream)[0x20 / 4])(stream);
  char b1 = data[1];                // kept across the vcall (ebx in the retail build)
  s = ((void* (__thiscall*)(void*))(*(void***)inner)[0x18 / 4])(inner);
  u.b = b1 != 0;
  StreamWriteBool(s, &u.b, 1);
  return stream;
}

// @ 0x00c0b100
int* __cdecl FUN_00c0b100(int* stream, char* data)
{
  void* inner = ((void* (__thiscall*)(void*))(*(void***)stream)[0x20 / 4])(stream);
  void* s = ((void* (__thiscall*)(void*))(*(void***)inner)[0x18 / 4])(inner);
  ReadUint64(s, data + 8, 1, 0);

  inner = ((void* (__thiscall*)(void*))(*(void***)stream)[0x20 / 4])(stream);
  s = ((void* (__thiscall*)(void*))(*(void***)inner)[0x18 / 4])(inner);
  ReadInt32(s, data + 4, 1, 0);

  inner = ((void* (__thiscall*)(void*))(*(void***)stream)[0x20 / 4])(stream);
  ReadBool(((void* (__thiscall*)(void*))(*(void***)inner)[0x18 / 4])(inner), data);

  inner = ((void* (__thiscall*)(void*))(*(void***)stream)[0x20 / 4])(stream);
  ReadBool(((void* (__thiscall*)(void*))(*(void***)inner)[0x18 / 4])(inner), data + 1);
  return stream;
}

// @ 0x00c0b190
bool __cdecl FUN_00c0b190(CB* self, int* info)
{
  if (self != 0) {
    if ((((unsigned char)(self->mGeneralFlags >> 9)) & 1) == 0 || info[2] != 0x3d) {
      if (info[0x120 / 4] != -1)
        return true;
    }
  }
  return false;
}

// @ 0x00c0b1c0
bool __cdecl FUN_00c0b1c0(unsigned int arg, unsigned int* out, unsigned int prop)
{
  int count = 0;
  int* data = 0;
  if (!SP_GetPropertyAsUint32Array(prop, arg, &count, &data) || count <= 0)
    return false;
  *out = data[GRAND->RandomUint32Uniform((unsigned int)count)];
  return true;
}

// @ 0x00c0b220
bool __cdecl FUN_00c0b220(unsigned int arg, unsigned int* out)
{
  int mode = SP_GetCurrentGameMode_s00c0_acd0();
  if ((mode >= 0x1654c00 && mode < 0x1654c07) || mode == 0x1654c10) {
    int index = mode - 0x1654c00;
    if (mode == 0x1654c10) index = 6;
    unsigned int entry = ((unsigned int*)g_168d900)[index];
    return FUN_00c0b1c0(arg, out, entry);
  }
  return false;
}

// @ 0x00c0b270
bool __stdcall FUN_00c0b270(unsigned int arg, unsigned int* out)
{
  int mode = SP_GetCurrentGameMode_s00c0_acd0();
  if ((unsigned int)(mode - 0x1654c00) > 6) return false;
  int count = 0;
  int* data = 0;
  unsigned int entry = ((unsigned int*)g_168d900)[mode - 0x1654c00];
  if (!SP_GetPropertyAsUint32Array(entry, arg, &count, &data) ||
      count <= 0)
    return false;
  *out = GRAND->RandomUint32Uniform((unsigned int)count);
  return true;
}

// @ 0x00c0b2f0
bool __stdcall FUN_00c0b2f0(unsigned int arg, unsigned int index, unsigned int* out)
{
  int mode = SP_GetCurrentGameMode_s00c0_acd0();
  if ((unsigned int)(mode - 0x1654c00) > 6) return false;
  int count = 0;
  int* data = 0;
  unsigned int entry = ((unsigned int*)g_168d900)[mode - 0x1654c00];
  if (!SP_GetPropertyAsUint32Array(entry, arg, &count, &data) ||
      count <= 0 || index >= (unsigned int)count)
    return false;
  *out = data[index];
  return true;
}

// @ 0x00c0b380
void* __cdecl FUN_00c0b380(CB* self, TuningObj* tuning)
{
  void* result = tuning->GetAt(0);
  switch (tuning->m8) {
  case 0x1e:
    result = (void*)0x4bc047d;
    break;
  case 0x1f:
    result = (void*)0x4bc0481;
    break;
  case 0x20:
    result = (void*)0x5b6db0a;
    break;
  case 0x21:
    result = (void*)0x4bc0485;
    if (self->mpSpecies->mAge > 0.0f &&
        (int)GRAND->RandomUint32Uniform(100) < 0x32)
      result = (void*)0x4c074c7;
    break;
  }
  return result;
}

// @ 0x00c0b410
bool __cdecl FUN_00c0b410()
{
  float threshold = g_169e288;
  return threshold >= GRAND->RandomDoubleUniform();
}

// @ 0x00c0b440
float __cdecl FUN_00c0b440(unsigned int which)
{
  float value = gOne1485720;                       // _HK_REAL_ONE
  switch ((int)which < 0 ? 0 : (int)which) {
  case 0: value = g_150c8e4; break;
  case 1: value = g_150c8e8; break;
  case 2: value = g_150c8ec; break;
  case 3: value = g_150c8f0; break;
  case 4: value = g_150c8f4; break;
  case 5: value = g_150c8f8; break;
  case 6: value = g_150c8fc; break;
  }
  return value;
}

// @ 0x00c0b510
void __cdecl SP_AddSetAnimationTargetModifierA(CB* self, void* target, void* owner, void* extra)
{
  if (target == 0) return;
  float weight = g_146a32c;
  int local[8];
  local[0] = (int)target;
  local[1] = 0;
  local[2] = (int)extra;
  local[3] = ++self->mAnimTargetCounter;
  self->mpOrders->Activate(3, 0, self, weight, local, owner);
}

// @ 0x00c0b570
void __cdecl SP_AddSetAnimationTargetModifierB(CB* self, void* target, float* position)
{
  if (target == 0) return;
  float weight = g_146a32c;
  int local[8];
  local[0] = (int)target;
  local[1] = 0;
  local[2] = -1;
  local[3] = ++self->mAnimTargetCounter;
  ((uint32_t*)&local[4])[0] = ((uint32_t*)position)[0];
  ((uint32_t*)&local[4])[1] = ((uint32_t*)position)[1];
  ((uint32_t*)&local[4])[2] = ((uint32_t*)position)[2];
  self->mpOrders->Activate(3, 0, self, weight, local, 0);
}

// @ 0x00c0b5e0
void __cdecl FUN_00c0b5e0(CB* self)
{
  if (g_168db6c == 0) {
    g_168db6c = 1;
    g_168d9bc = 0;
    g_168da00 = 1;
    g_168da44 = 2;
    g_168da88 = 3;
    g_168dacc = 4;
    g_168db10 = 5;
  }
  void* p = operator new(0x230, "Simulator/cModifiers", 0, 0, 0, 0);
  self->mpOrders = p != 0
      ? (AgentOrderManager*)((ModifiersCtorHelper*)p)->Exist(&g_168d998)
      : 0;
}

// @ 0x00c0b670
int __thiscall CB::Query(unsigned int id)
{
  CB* self = this;
  if (id == 0xce9f6639) return (int)self;
  int r = ((F_abf740*)((char*)self + 0x58))->f(id);
  if (r != 0) return r;
  r = ((F_cee250*)((char*)self + 0x34))->f(id);
  if (r != 0) return r;
  r = ((F_c41d00*)((char*)self + 0xc0))->f(id);
  if (r != 0) return r;
  r = ((F_ac0320*)((char*)self + 0x590))->f(id);
  if (r != 0) return r;
  r = ((F_b18460*)self)->f(id);
  if (r != 0) return r;
  r = ((F_bfc380*)((char*)self + 0x5a8))->f(id);
  if (r != 0) return r;
  r = ((F_c7d050*)((char*)self + 0x670))->f(id);
  if (r != 0) return r;
  return ((F_c884f0*)((char*)self + 0xc0))->f(id);
}

// @ 0x00c0b710
void __fastcall FUN_00c0b710(CB* self)
{
  // The millisecond count is rounded (fistp, round-half-to-even) to an int64; a C
  // cast would go through __ftol2, which truncates, so the conversion is written out.
  float ms = g_1687a30 * 1000.0f;
  __declspec(align(8)) long long t;
  t = X87RoundToInt64(ms);
  self->m_b8c = (int)t;
}

// @ 0x00c0b780
bool __fastcall FUN_00c0b780(CB* self)
{
  return self->mpSpecies->m608 > 0;
}

// @ 0x00c0b7a0
bool __fastcall FUN_00c0b7a0(CB* self)
{
  return self->mpSpecies->m60c > 0;
}

// @ 0x00c0b7c0
bool __thiscall CB::CheckTargetA(void* target)
{
  CB* self = this;
  return (self->mpSpecies->m60c > 0 && ((F_c35d20*)target)->f())
      || (self->mpSpecies->m608 > 0 && ((F_c35d40*)target)->f());
}

// @ 0x00c0b810
bool __thiscall CB::CheckTargetB(void* argp)
{
  CB* self = this;
  unsigned int arg = (unsigned int)(size_t)argp;
  int base = FUN_00b3d4c0(self);
  if (base != 0) {
    int r = ((F_ba3f90*)base)->f((char*)self + 0xb28, self, arg);
    return r == 2 || r == 5 || r == 3 || r == 4;
  }
  return false;
}

// @ 0x00c0b860
bool __thiscall CB::CheckTargetC(void* argp)
{
  CB* self = this;
  unsigned int arg = (unsigned int)(size_t)argp;
  int base = FUN_00b3d4c0(self);
  if (base != 0) {
    int r = ((F_ba3f90*)base)->f((char*)self + 0xb28, self, arg);
    return r == 2 || r == 5;
  }
  return false;
}

// @ 0x00c0b8a0
bool __thiscall CB::CheckTargetD(void* argp)
{
  CB* self = this;
  unsigned int arg = (unsigned int)(size_t)argp;
  int base = FUN_00b3d4c0(self);
  if (base != 0)
    return ((F_ba3f90*)base)->f((char*)self + 0xb28, self, arg) == 1;
  return false;
}

// @ 0x00c0b8d0
int Simulator::cCreatureBase::GetStrengthRating() const
{
  return mStrengthRating;
}

// @ 0x00c0b8e0
int __thiscall CB::TimerDelta(CB* other)
{
  CB* self = this;
  return self->mStrengthRating - other->mStrengthRating;
}

// @ 0x00c0b910
void __thiscall Simulator::cCreatureBase::SetLastInteractionEffect(unsigned int value)
{
  if (this->mLastInteractionEffect != value) {
    this->mLastInteractionEffect = value;
    this->mbUpdateInteractionEffect = true;
  }
}

// @ 0x00c0b930
bool __thiscall Simulator::cCreatureBase::ForgetUpdateInteractionEffect()
{
  bool old = this->mbUpdateInteractionEffect;
  this->mbUpdateInteractionEffect = false;
  return old;
}

// @ 0x00c0b950
void __fastcall FUN_00c0b950(CB* self)
{
  self->m_bBC = g_1687a00;
}

// @ 0x00c0b9a0
void __thiscall Simulator::cCreatureBase::func90h()
{
  this->mbDead = false;
  this->m_bBC = g_1687a00;
}

// EA's SSE min/max __asm helpers (maxss/minss), as in the original module
// (see match/slices/s00c02600 and s00533dc0: MinF/MaxF/clamp helpers are __asm there too).
// ClampF: the vetted SseClamp in sse_helpers.h

// @ 0x00c0b9d0
void __thiscall CB::ClampHunger(float value)
{
  value = SseClamp(value, g_1687a04, g_1687a00);
  this->m_bBC = value;
}

// @ 0x00c0ba10
void __fastcall FUN_00c0ba10(CB* self)
{
  self->m_bB8 = -g_1687a2c;
}

// @ 0x00c0ba30
bool __fastcall FUN_00c0ba30(CB* self)
{
  if (g_1687a0c > self->m_bBC) return true;
  if (FUN_00bfc490((char*)self + 0x5a8) * 100.0f < g_1687a0c) {
    return true;
  }
  return false;
}

// @ 0x00c0ba70
bool __fastcall FUN_00c0ba70(CB* self)
{
  if (g_1687a10 > self->m_bBC) return true;
  if (FUN_00bfc490((char*)self + 0x5a8) * 100.0f < g_1687a10) {
    return true;
  }
  return false;
}

// @ 0x00c0bab0
bool __fastcall FUN_00c0bab0(CB* self)
{
  if (g_1687a14 > self->m_bBC) return false;
  if (g_1687a14 > FUN_00bfc490((char*)self + 0x5a8) * 100.0f) return false;
  return true;
}

// @ 0x00c0bb20
float __fastcall FUN_00c0bb20(CB* self)
{
  float value;
  if (self->mp_e84 != 0)
    value = *(float*)((char*)self->mp_e84 + 0x368);
  else
    value = *(float*)((char*)self->mpSpecies + 0x570);
  if (self->m_b34 != 1) {
    value = g_150c888 * value;
  } else if (self->mGeneralFlags & 1) {
    value = g_150c88c * value;
  }
  return value;
}

// @ 0x00c0bb90
bool __fastcall FUN_00c0bb90(CB* self)
{
  return FUN_00bfc490((char*)self + 0x5a8) * g_1687a00 < g_1687a10;
}

// @ 0x00c0bbe0
void __fastcall FUN_00c0bbe0(CB* self)
{
  void* base = FUN_00b3d310(self);
  ((F_b48770*)base)->f(self, 1);
}

// @ 0x00c0bc00
char* __fastcall FUN_00c0bc00(CB* self)
{
  if (self->mpSpecies != 0)
    return (char*)self->mpSpecies + 0x504;
  return (char*)self + 0xb28;
}

// @ 0x00c0bd70
int __thiscall C_s00c0_bd70::C0bd70(void* fields)
{
  int sum = ((GameDataFields*)this)->GetFieldValues(fields);
  {
    cVarListSerializer v((char*)this + 0x34, (void*)g_15816b8, 0x1a80d26);
    sum += v.GetFields(fields);
  }
  sum += ((LocoFields*)((char*)this + 0xc0))->GetFieldValues(fields);
  {
    cVarListSerializer v((char*)this + 0x5a8, (void*)g_1570858, 0x1a80d26);
    sum += v.GetFields(fields);
  }
  cVarListSerializer v3(this, (void*)g_1571798, 0x1a80d26);
  sum += v3.GetFields(fields);
  return sum;
}

// @ 0x00c0be70
bool __cdecl FUN_00c0be70(int x)
{
  if (x == 0x25b3bc0 || x == 0x772ff58 || x == 0x7995fdc || x == 0x7982fb2 || x == 0x7b5063e)
    return true;
  return false;
}

// @ 0x00c0bea0
bool __cdecl FUN_00c0bea0(int x)
{
  if (x == 0x5261d56 || x == 0x5261d78 || x == 0x692e5bf || x == 0x5485a4c ||
      x == 0x77300f2 || x == 0x77300fb || x == 0x77300ff)
    return true;
  return false;
}

// @ 0x00c0bee0
void __thiscall C_s00c0_bd70::C0bee0(int a, int b)
{
  ((CCommunityStub*)this)->func60h(a, b);
  *(uint8_t*)((char*)this + 0xa9d) = 1;
}

// @ 0x00c0bf10
void __thiscall C_s00c0_bd70::C0bf10(int a,int b,int c,int d,float e,int f,int g,int h,int i,int j,char k)
{
  CreatureFields* cf = (CreatureFields*)this;
  behavior_stimuli* bs = (behavior_stimuli*)((char*)cf->mB4c + 8);
  bs->ClearAll((~a) & c, (~b) & d);
  void* r = bs->Play(a, b);
  bool changed = r == 0;
  if (r != 0 && k != 0) {
    StimulusResult* rr = (StimulusResult*)r;
    changed = !(rr->m2c == j && rr->m10 == i);
  }
  if ((f != 0 || g != 0) && changed) {
    bs->Set((void*)f, (uint32_t)g, gF_146a32c, 0);
    if ((cf->mB58 >> 9) & 1) {
      void* p = FUN_00b3d320();
      if (((DatabasePackedFile*)p)->GetLocation() == (void*)0x1654c01) {
        g_169e37c = 0;
      } else {
        void* q = FUN_00b3d320();
        if (((DatabasePackedFile*)q)->GetLocation() == (void*)0x1654c10) g_169e37c = 0;
      }
    }
  }
  StimulusResult* e2 = (StimulusResult*)bs->Set((void*)a, (uint32_t)b, e, (void*)j);
  e2->m0c = h;
  e2->m10 = i;
}

// @ 0x00c0c010
float __thiscall C_s00c0_bd70::GetA()
{
  void* p = *(void**)((char*)this + 0xe84);
  if (p) { float f = *(float*)((char*)p + 0x350); if (f >= 0.0f) return f; }
  return gF_150c8b8;
}

// @ 0x00c0c040
float __thiscall C_s00c0_bd70::GetB()
{
  void* p = *(void**)((char*)this + 0xe84);
  if (p) { float f = *(float*)((char*)p + 0x354); if (f >= 0.0f) return f; }
  return gF_150c8b4;
}

// @ 0x00c0c080
int __thiscall C_s00c0_bd70::FindIndex(int key)
{
  uint32_t n = (*(uint32_t(__thiscall*)(void*))((*(void***)this)[0xb0/4]))(this);
  for (uint32_t i = 0; i < n; ++i) {
    void* e = (*(void*(__thiscall*)(void*, uint32_t))((*(void***)this)[0xb4/4]))(this, i);
    if (*(int*)((char*)e + 8) == key) return (int)i;
  }
  return -1;
}

// @ 0x00c0c0d0
float __thiscall C_s00c0_bd70::Get574()
{ return *(float*)((char*)*(void**)((char*)this + 0xa60) + 0x574); }

// @ 0x00c0c0e0
bool __thiscall C_s00c0_bd70::Flag388()
{
  void* p = *(void**)((char*)this + 0xe84);
  return p != 0 && *(char*)((char*)p + 0x388) != 0;
}

// @ 0x00c0c100
bool __thiscall C_s00c0_bd70::Flag389()
{
  void* p = *(void**)((char*)this + 0xe84);
  return p != 0 && *(char*)((char*)p + 0x389) != 0;
}

// @ 0x00c0c140
void __thiscall C_s00c0_bd70::CallFind13()
{ if (FindIndex(0xd) == -1) FindIndex(0x52); }

// @ 0x00c0c160
void __thiscall C_s00c0_bd70::CallFind27()
{ if (FindIndex(0x27) == -1) FindIndex(0x50); }

// @ 0x00c0c180
void __thiscall C_s00c0_bd70::SetE84(void* p)
{
  *(void**)((char*)this + 0xe84) = p;
  if (p) *(void**)((char*)this + 0xe80) = *(void**)((char*)p + 0x10);
}

// @ 0x00c0c1c0
float __thiscall C_s00c0_bd70::Speed1(char b)
{
  float v = 1.0f;
  if (*(int*)((char*)this + 0xb34) != 1 && b == 0) v = gF_150c8cc;
  return v;
}

// @ 0x00c0c200
void __thiscall C_s00c0_bd70::C200(float f)
{
  void* gm = SP_GetCurrentGameMode();
  if (gm == (void*)0x1654c10 && *(int*)((char*)g_16c7aa4 + 0xcc) == 2) {
    if (this) FUN_00ef1930((char*)this + 0x5a8, f);
    else FUN_00ef1930(0, f);
  }
}

// @ 0x00c0c250
int __thiscall C_s00c0_bd70::C0c250_()
{
  CreatureFields* cf = (CreatureFields*)this;
  bool b = false;
  void* p = FUN_00b3d4c0();
  if (p) {
    b = ((CreatureBaseMgr*)p)->FUN_00ba3f90(
            &cf->mB28, ((GameNounManager_s00c0_bd70*)SP_NounManager())->GetAvatar(), this) == 6;
  }
  if ((bool)((cf->mB58 >> 7) & 1) || b ||
      ((*(bool(__thiscall*)(void*))((*(void***)this)[0xd0/4]))(this) &&
       SP_GetCurrentGameMode() != (void*)0x1654c10))
    return 1;
  return 0;
}

// @ 0x00c0c2d0
bool __thiscall C::IsDefaultSpecies_()
{
  cSpeciesManager* mgr = (cSpeciesManager*)FUN_00401090();
  return mgr->GetAvatarProfile() == *(cSpeciesProfile_s00c2_2010**)((char*)this + 0xb20);
}

// @ 0x00c0c310
uint32_t __thiscall C_s00c0_bd70::FlagF()
{ return (*(uint32_t*)((char*)this + 0xb58) >> 0xf) & 1; }

// @ 0x00c0c3e0
C_s00c0_bd70* __thiscall C_s00c0_bd70::CopyRec(void* srcv)
{
  uint32_t* s = (uint32_t*)srcv;
  uint32_t* d = (uint32_t*)this;
  d[0]=s[0]; d[1]=s[1]; d[2]=s[2]; d[3]=s[3]; d[4]=s[4];
  *(float*)(d+5) = *(float*)(s+5);
  *(uint8_t*)(d+6) = *(uint8_t*)(s+6);
  d[7]=s[7];
  void* o = (void*)s[8];
  d[8]=(uint32_t)o;
  if (o) (*(void(__thiscall*)(void*))((*(void***)o)[0xbc/4]))(o);
  return this;
}

// @ 0x00c0c440
void* __cdecl FUN_00c0c440(uint32_t* first, uint32_t* last, uint32_t* dst)
{
  while (first != last) {
    if (dst) {
      dst[0]=first[0]; dst[1]=first[1]; dst[2]=first[2]; dst[3]=first[3];
      dst[4]=first[4];
      *(float*)(dst+5) = *(float*)(first+5);
      *(uint8_t*)(dst+6) = *(uint8_t*)(first+6);
      dst[7]=first[7];
      void* o = (void*)first[8];
      dst[8]=(uint32_t)o;
      if (o) (*(void(__thiscall*)(void*))((*(void***)o)[0xbc/4]))(o);
    }
    first += 9; dst += 9;
  }
  return dst;
}

// @ 0x00c0c4b0
C_s00c0_bd70* __thiscall C_s00c0_bd70::QuatHalf(float a)
{
  float* q = (float*)this;
  float x=q[0], y=q[1], z=q[2], w=q[3];
  float c = cosf(a * 0.5f);
  float s = sinf(a * 0.5f);
  q[0] = x*c + w*0.0f - z*s + y*0.0f;
  q[1] = y*c + w*s + z*0.0f - x*0.0f;
  q[2] = z*c - y*0.0f + x*s + w*0.0f;
  q[3] = w*c - x*0.0f - y*s - z*0.0f;
  return this;
}

// @ 0x00c0c5b0
bool __cdecl C5b0(int obj, int b, int* out)
{
  if (SP_GetCurrentGameMode() == (void*)0x1654c10) {
    int r = FUN_00ebfd50(obj, b);
    *out = r;
    return r != b;
  }
  void* p = *(void**)((char*)obj + 0xe84);
  if (p && *(char*)((char*)p + 0x388) != 0) {
    void* mgr = *(void**)0x168d900;
    if (FUN_00c0b1c0((void*)b, (void*)out, *(int*)((char*)mgr + 0x1c))) return true;
  }
  return FUN_00c0b220((void*)b, (void*)out);
}

// @ 0x00c0c630
void __thiscall C_s00c0_bd70::C0c630(char bparam, int* p3, int* p4, int* p5)
{
  LocomotionExec* o = (LocomotionExec*)this;
  uint8_t* sub58 = (uint8_t*)this + 0x58;
  uint8_t* subc0 = (uint8_t*)this + 0xc0;
  char cVar4 = (*(char(__thiscall*)(void*))((*(void***)subc0)[0x58/4]))(subc0);
  bool bVar3 = false;
  if (o->mE84 != 0 && o->mE84->m388 != 0) bVar3 = true;
  (*(void(__thiscall*)(void*))((*(void***)this)[0x20/4]))(this);
  *p5 = -1;
  *p4 = 0x2481de5;
  if (o->mE3c != -1) { *p4 = o->mE3c; return; }

  if (o->m137 == 0) {
    void* r58 = (*(void*(__thiscall*)(void*))((*(void***)sub58)[0x20/4]))(sub58);
    if (r58 != 0) {
      void* r58b = (*(void*(__thiscall*)(void*))((*(void***)sub58)[0x20/4]))(sub58);
      if ((*(int(__thiscall*)(void*))((*(void***)r58b)[0x1c/4]))(r58b) == 0x114242e6) {
        *p4 = 0x3cc7eb4;
        return;
      }
    }
    if (o->m110 & 0x1000) {
      if (bVar3) return;
      float v = (*(float(__thiscall*)(void*))((*(void***)subc0)[0xc8/4]))(subc0);
      *p4 = (v <= gF_146a330) ? 0x2e6ea7d : 0x293bb70;
      return;
    }
    if (o->mE62 != 0) { *p4 = 0x7982f7e; return; }
    OrderFlagsExec* m = o->mB20;
    if (m->m61c == 0) {
      *p4 = ((m->m6a0 != 0) ? 0xe019ea : 0) + 0x692e6a9;
      return;
    }
    if ((o->mB58 >> 9) & 1) *p4 = ((m->m698 != 0) ? 0xe01b3c : 0) + 0x692e5bf;
    else                    *p4 = ((m->m698 != 0) ? 0x24ce383 : 0) + 0x5261d78;
    return;
  }

  int a0 = 0, a1 = 0;
  AnimCreatureExec* ac = o->mB54;
  ((Object1734*)((char*)ac->m17c + 0x15b8))->FUN_009ce720(&a0, &a1);
  void* f98 = o->mF98;
  if (a0 == 2 && f98 == 0) {
    float* vel = ((LocomotiveObject*)subc0)->GetVelocity();
    float tmp[3];
    float* q = (*(float*(__thiscall*)(void*, void*))((*(void***)subc0)[0x5c/4]))(subc0, tmp);
    float dot = q[2]*vel[2] + q[1]*vel[1] + q[0]*vel[0];
    if (!(dot <= gF_1572040)) goto LRand;
  }
  if (ac->IsOrientStopAnim((uint32_t)*p3)) {
    if (bparam == 0) {
      if (!ac->FUN_00a04940(ac->m188)) {
        if (f98 == 0) goto LRand;
      }
    }
  }
  if (bVar3) goto L957;
  if (((C_s00c0_bd70*)this)->C0bb90()) { *p4 = 0x2481deb; return; }
  if (o->mB48->FindSlot(0, 0, this, 0) != -1) { *p4 = 0x4adc8db; return; }
L957:
  if (cVar4 != 0 && gF_1687a10 > o->mBbc) { *p4 = 0x54ac987; return; }
  {
    Global169e370* r = (Global169e370*)FUN_00d2e340();
    if ((a0 != 0 && f98 != 0) ||
        (((o->mB58 >> 9) & 1) != 0 && r != 0 && r->m11 != 0 &&
         (r->mF != 0 || r->m10 != 0))) {
      if (*p3 == 0x4866dab) { *p4 = 0x4866dab; return; }
      *p4 = 0x4866d8e;
      *p5 = 0x4866dab;
    }
  }
  return;
LRand:
  if (ac->IsOrientStopAnim((uint32_t)*p3)) { *p4 = *p3; return; }
  {
    uint32_t rr = ((RandomLCG*)0x1601760)->RandomUint32Uniform(3);
    if (rr == 1) *p4 = 0x4866dcb;
    else if (rr == 2) *p4 = 0x4866dd4;
    else *p4 = 0x4866dc3;
  }
}

// @ 0x00c0ca00
bool __cdecl FUN_00c0ca00(float* p1, float* p2, float t, float* out, float* vel)
{
  PlanetModelObj* pm = (PlanetModelObj*)SP_PlanetModel();
  float g = pm->FUN_00b7e490();
  float dx = p2[0] - p1[0];
  float dy = p2[1] - p1[1];
  float dz = p2[2] - p1[2];
  float dist = sqrtf(dx*dx + dy*dy + dz*dz);
  float a1 = asinf(-((dist * g) / (t * t)));
  float bx = p2[0], by = p2[1], bz = p2[2];
  if (vel[0] != g_168d910 || vel[1] != g_168d914 || vel[2] != g_168d918) {
    float s1 = sinf(a1 * 0.5f);
    float f = (s1 * t + s1 * t) / -g;
    bx += vel[0] * f;
    by += vel[1] * f;
    bz += vel[2] * f;
  }
  dx = bx - p1[0];
  dy = by - p1[1];
  dz = bz - p1[2];
  dist = sqrtf(dx*dx + dy*dy + dz*dz);
  float inv = 1.0f / dist;
  float q = -((dist * g) / (t * t));
  if (q <= 1.0f && q >= -1.0f) {
    float ang = 0.5f * asinf(q);
    float s2 = sinf(ang) * t;
    float c2 = cosf(ang) * t;
    float invA = 1.0f / sqrtf(p1[0]*p1[0] + p1[1]*p1[1] + p1[2]*p1[2]);
    out[0] = (dx * inv) * c2 + (p1[0] * invA) * s2;
    out[1] = (dy * inv) * c2 + (p1[1] * invA) * s2;
    out[2] = (dz * inv) * c2 + (p1[2] * invA) * s2;
    return true;
  }
  return false;
}

// @ 0x00c0ccc0
char __cdecl FUN_00c0ccc0(float* p, float dt)
{
  TransitionState* s = (TransitionState*)p;
  TransitionObject* pre = (TransitionObject*)s->m3c;
  void* obj = pre ? (void*)(*(void*(__thiscall*)(void*, int))((*(void***)pre)[0xc/4]))(pre, 0xce9f6639) : 0;
  TransitionObject* o = (TransitionObject*)obj;
  char c = (*(char(__thiscall*)(void*))((*(void***)o)[0x2c/4]))(o);
  if (c == 0 && o->mB5e == 0 && o->m135 != 0) {
    if (s->m4 >= s->m0) {
      void* ent = 0;
      if (s->m40 != 0) ent = FUN_00c0c320(&s->m40);
      int u = -1;
      if (ent) u = (*(int(__thiscall*)(void*))((*(void***)ent)[0x10/4]))(ent);
      void* vt = *(void**)o->mSub5a8;
      float f = s->m8 * s->m0;
      (*(void(__thiscall*)(void*, float, int, int, void*, void*))((*(void***)vt)[0x18/4]))(
          o->mSub5a8, f, u, 7, (void*)0x168d910, ent);
      s->m4 = 0.0f;
      return 1;
    } else {
      s->m4 += dt;
      return 1;
    }
  }
  return 0;
}

// @ 0x00c0cdb0
int __thiscall C_s00c0_bd70::Cdb0()
{
  if (SP_GetCurrentGameMode() == (void*)0x1654c10) {
    void* obj = 0;
    if (this) obj = (*(void*(__thiscall*)(void*, int))((*(void***)this)[0xc/4]))(this, 0xd0036e08);
    GameModeResult* r = (GameModeResult*)((GameModeObject*)obj)->Get();
    if (r) return (int)r->m490;
  }
  CreatureB20* p = (CreatureB20*)((CreatureFields*)this)->mB20;
  if (p) return p->m544;
  return 0;
}

// @ 0x00c0ce30
int __thiscall C_s00c0_bd70::RelationIndex(int idx, char b)
{
  if (*(int*)((char*)this + 0xb20) != 0) {
    if (idx != 0) {
      int v = Cdb0() + g_15716d8[idx];
      if (b == 0) v += *(int*)((char*)this + 0xfa0);
      if (v >= 0)
        return v < 6 ? v : 5;
    }
  }
  return 0;
}

// @ 0x00c0ce80
float __thiscall CCB_s00c0_ce80::ce80(int index, int flag)
{
    if (index == 0) return 0.0f;
    int iVar2 = ((F_ce30*)this)->f(index, flag);
    void* gm = SP_GetCurrentGameMode();
    float local_4;
    if (gm == (void*)0x1654c10) {   // needs the dword at 0x1654c10 (DAT_01654c10)
        void* r = FUN_00c03260(this, iVar2);
        local_4 = ((F_f31500*)r)->f();
    } else {
        local_4 = GF(0x15d9650 + iVar2 * 4);
    }
    if ((*(char(__thiscall*)(void*))((*(void***)((char*)this + 0xc0))[0x58 / 4]))((char*)this + 0xc0)) {
        float p = local_4;
        if (iVar2 + 1U < 6) p = GF(0x15d9654 + iVar2 * 4);
        else if (iVar2 != 0) p = GF(0x15d964c + iVar2 * 4);
        return fabsf(local_4 - p) * GF(0x1471064) + local_4;
    }
    return local_4;
}

// @ 0x00c0cf50
void __thiscall CCB::cf50()
{
    GF((char*)this + 0xfa8) = 0.0f;
    GF((char*)this + 0xfac) = ce80(1, 1);
    GF((char*)this + 0xfb0) = ce80(2, 1);
    GF((char*)this + 0xfb4) = ce80(3, 1);
    GF((char*)this + 0x2a4) = GF((char*)this + 0xfb0);
}

// @ 0x00c0cfa0
float __thiscall CCB::cfa0(int index, char flag)
{
    if (*(char*)((char*)this + 0xbb0) != 0)
        return ce80(2, 1) + GF((int)g_150c900);
    float v = flag != 0 ? GF((char*)this + 0xfa8 + index * 4) : ce80(index, 0);
    return v;
}

// @ 0x00c0cff0
void __thiscall CCB_s00c0_ce80::cff0(int param)
{
    G32((char*)this + 0xf98) = param;
    float v;
    if (*(char*)((char*)this + 0xbb0) != 0)
        v = ce80(2, 1) + GF((int)g_150c900);
    else
        v = ce80(param, 0);
    GF((char*)this + 0x2a0) = v;
}

// @ 0x00c0d050
int __thiscall CCB::d050(float param)
{
    int idx = 3;
    int iVar1 = 0;
    do {
        if (iVar1 != 1) {
            float f;
            if (*(char*)((char*)this + 0xbb0) != 0)
                f = ce80(2, 1) + GF((int)g_150c900);
            else
                f = ce80(iVar1, 0);
            if (f >= param) {
                idx = iVar1;
                break;
            }
        }
        ++iVar1;
    } while (iVar1 < 4);
    return idx;
}

// @ 0x00c0d0c0
void __thiscall CCB_s00c0_ce80::d0c0(uint32_t param_2, char param_3)
{
    bool bVar3;
    if (param_2 < 8) {
        uint32_t bit = 1u << (param_2 & 0x1f);
        bVar3 = (G32((char*)this + 0xfa4) & bit) != 0;
        if (param_3 == 0) G32((char*)this + 0xfa4) &= ~bit;
        else G32((char*)this + 0xfa4) |= bit;
    } else bVar3 = false;
    if (param_3 == bVar3) return;
    int iVar1 = (param_3 == 0 || bVar3) ? -1 : 1;
    int* pfa0 = (int*)((char*)this + 0xfa0);
    switch (param_2) {
    case 0: *pfa0 += iVar1; break;
    case 1: case 2: case 3: *pfa0 -= iVar1; break;
    case 4: iVar1 = -iVar1 * 2; *pfa0 += iVar1; break;
    case 5: *pfa0 += (*(int*)((char*)*(void**)((char*)this + 0xb20) + 0x5d0)) * iVar1; break;
    case 6: iVar1 = -iVar1 * 4; *pfa0 += iVar1; break;
    case 7: *pfa0 += iVar1 * 2; break;
    }
    float v;
    if (*(char*)((char*)this + 0xbb0) == 0) v = ce80(G32((char*)this + 0xf98), 0);
    else v = ce80(2, 1) + GF(0x150c900);
    GF((char*)this + 0x2a0) = v;
}

// @ 0x00c0d1e0
void __thiscall CCB_s00c0_ce80::d1e0(int param)
{
    void* p = *(void**)((char*)this + 0xb54);
    if (p != 0) ((F_a02bf0*)p)->f(param, 1);
}

// @ 0x00c0d200
void __thiscall CCB_s00c0_ce80::d200(int param_2, int param_3)
{
    if (*(int*)((char*)this + 0xb54) != 0) {
        void* eax = *(void**)((char*)param_2 + 0xb54);
        if (eax != 0) {
            void* ths = *(void**)((char*)this + 0xb54);
            if (param_3 != -1) ((F_a062a0*)ths)->f((int)eax, param_3);
            else ((F_a06250*)ths)->f((int)eax);
        }
    }
}

// @ 0x00c0d240
void __thiscall CCB_s00c0_ce80::d240()
{
    void* p = *(void**)((char*)this + 0xb54);
    if (p != 0) {
        float local_14 = *(float*)((char*)p + 0x3c) * GF(0x1473c70);
        float r = (*(float(__thiscall*)(void*))((*(void***)((char*)this + 0xc0))[0x74 / 4]))((char*)this + 0xc0);
        float af[2]; af[0] = r;
        float* pf = &local_14;
        if (local_14 <= r) pf = af;
        float neg = -(*pf);
        *(uint32_t*)((char*)p + 0x154) = 1;
        void* q = *(void**)((char*)this + 0xb54);
        *(uint32_t*)((char*)q + 0x164) = 0;
        *(float*)((char*)q + 0x168) = neg;
        *(uint32_t*)((char*)q + 0x16c) = 0;
        void* r2 = *(void**)((char*)this + 0xb54);
        if (*(int*)((char*)r2 + 0x15c) != 0) {
            void* contained = *(void**)((char*)r2 + 0x15c);
            *(uint32_t*)((char*)r2 + 0x15c) = 0;
            ((F_a05270*)contained)->Release();
        }
    }
    *(uint8_t*)((char*)this + 0xb66) = 0;
}

// @ 0x00c0d310
float* __thiscall CCB_s00c0_ce80::d310(float* param_2, int param_3)
{
    float* pu = (float*)(*(void*(__thiscall*)(void*))((*(void***)((char*)this + 0x8c))[0x2c / 4]))((char*)this + 0x8c);
    param_2[0] = pu[0];
    param_2[1] = pu[1];
    param_2[2] = pu[2];
    return param_2;
}

// @ 0x00c0d340
void __thiscall CCB_s00c0_ce80::d340(int param_2)
{
    void* iVar2 = *(void**)((char*)param_2 + 0x34);
    *(uint32_t*)((char*)param_2 + 0x130) = 0;
    float* u = (float*)(*(float*(__thiscall**)(void*))((*(void***)((char*)this + 0x8c))[0x2c / 4]))((char*)this + 0x8c);
    void* self2 = (char*)param_2 + 0x34;
    (*(void(__thiscall**)(void*, void*))(*(void**)((char*)iVar2 + 0x38)))(self2, u);
    void* piVar3 = *(void**)((char*)this + 0x18);
    void* piVar1 = (char*)this - 0x34;
    if (piVar1 != piVar3) {
        if (piVar1) (*(void(__thiscall**)(void*))((*(void***)piVar1)[0]))(piVar1);
        *(void**)((char*)this + 0x18) = piVar1;
        if (piVar3) (*(void(__thiscall**)(void*))((*(void***)piVar3)[1]))(piVar3);
    }
}

// @ 0x00c0d3a0
void __cdecl FUN_00c0d3a0(int param_1)
{
    if (*(void**)(param_1 + 0xb4c) != 0 && **(int**)(param_1 + 0xb4c) != 0) {
        if (FUN_00b3d230() != 0) {
            if (SP_GameTimeManager() != 0) {
                void* g = SP_GameTimeManager();
                unsigned long long u = (unsigned long long)((F_b316c0*)g)->f();
                void* pu = *(void**)(param_1 + 0xb4c);
                double d = 0.0;
                if ((long long)u < 0) d = (double)(long long)u; else d = (double)u;
                FUN_00bc86e0(d * 0.001f, pu, (void*)param_1, (char*)pu + 0x1d0,
                             *(int*)((char*)pu + 0x5e8), *(int*)((char*)pu + 0x5fc));
            }
        }
    }
}

// @ 0x00c0d440
void __thiscall CCB_s00c0_ce80::UpdateHunger(float param)
{
    if (!(*(char(__thiscall**)(void*))((*(void***)((char*)this + 0xc0))[0x58 / 4]))((char*)this + 0xc0)) return;
    if (((G32((char*)this + 0xb58) >> 8) & 1) != 0) return;
    if (SP_GetCurrentGameMode() == (void*)0x1654c10) return;
    F_timer* pcVar1 = (F_timer*)((char*)this + 0xb90);
    float fVar6;
    if (pcVar1->IsRunning()) {
        long long u = pcVar1->GetElapsedTime();
        if ((int)((unsigned long long)u >> 32) == 0 && G32((char*)this + 0xb8c) > (uint32_t)u) {
            fVar6 = GF(0x1687a00);
        } else goto LAB_d4b5;
    } else {
    LAB_d4b5:
        if (!pcVar1->IsRunning() && GF((char*)this + 0xbbc) == GF(0x1687a00)) {
            if (*(int*)((char*)this + 0xb34) == 1) pcVar1->Restart();
            goto LAB_d511;
        }
        pcVar1->Stop();
        fVar6 = GF((char*)this + 0xbb8) * param + GF((char*)this + 0xbbc);
    }
    ((F_c0b9d0*)this)->f(fVar6);
LAB_d511:
    if (GF((char*)this + 0xbbc) < 1.0f) {
        void* vt = *(void**)((char*)this + 0x5a8);
        float x = GF(0x1687a1c) * param;
        (*(void(__thiscall**)(void*, float, int, int, int, int))(*(void**)((char*)vt + 0x18)))(
            (char*)this + 0x5a8, x, -1, 5, 0x168d910, 0);
    }
}

// @ 0x00c0d560
bool __thiscall CCB_s00c0_ce80::d560(int other, float scale, float dist)
{
    if (GF((char*)other + 0xb80) <= 0.0f) return false;
    void* e = *(void**)((char*)this + 0xe84);
    float thr;
    if (e == 0) thr = GF(0x150c8b4);
    else {
        float v = GF((char*)e + 0x354);
        if (v < 0.0f) thr = GF(0x150c8b4);
        else thr = v;
    }
    thr = thr * scale + GF((char*)other + 0xb80);
    if (fabsf(dist) <= 0.0f) {
        float* p1 = (float*)(*(void*(__thiscall*)(void*))((*(void***)((char*)this + 0xc0))[0x2c / 4]))((char*)this + 0xc0);
        float* p2 = (float*)(*(void*(__thiscall*)(void*))((*(void***)((char*)other + 0xc0))[0x2c / 4]))((char*)other + 0xc0);
        float dx = p2[0] - p1[0], dy = p2[1] - p1[1], dz = p2[2] - p1[2];
        float d = sqrtf(dx * dx + dy * dy + dz * dz + GF(0x13ec4b8));
        float r2 = (*(float(__thiscall*)(void*))((*(void***)((char*)other + 0xc0))[0x74 / 4]))((char*)other + 0xc0);
        float r1 = (*(float(__thiscall*)(void*))((*(void***)((char*)this + 0xc0))[0x74 / 4]))((char*)this + 0xc0);
        if (d - (r2 + r1) < thr) return true;
    } else if (dist < thr) return true;
    return false;
}

// @ 0x00c0d660
void __thiscall CCB_s00c0_ce80::d660(float* param_2)
{
    int* pi = ((F_d9030*)*(void**)((char*)this + 0xb20))->f(*(void**)((char*)this + 0xb54));
    if (pi[0] == pi[1]) {
        void* self = (char*)this + 0xc0;
        char* eax = (char*)(*(void*(__thiscall*)(void*))((*(void***)self)[0x68 / 4]))(self);
        float fv = (GF(eax + 0x14) - GF(eax + 8)) * GF(0x13ec4b0);
        float fwd[3];
        (*(void(__thiscall*)(void*, float*))((*(void***)self)[0x5c / 4]))(self, fwd);
        float* p1 = (float*)(*(void*(__thiscall*)(void*))((*(void***)self)[0x2c / 4]))(self);
        float inv = 1.0f / sqrtf(p1[0] * p1[0] + p1[1] * p1[1] + p1[2] * p1[2] + GF(0x13ec4b8));
        float* p2 = (float*)(*(void*(__thiscall*)(void*))((*(void***)self)[0x2c / 4]))(self);
        param_2[0] = p2[0] + (p1[0] * inv) * fv + fwd[0] * GF(0x13ec4b0);
        param_2[1] = p2[1] + (p1[1] * inv) * fv + fwd[1] * GF(0x13ec4b0);
        param_2[2] = p2[2] + (p1[2] * inv) * fv + fwd[2] * GF(0x13ec4b0);
    } else {
        int iVar9 = *(int*)(*(int*)((char*)this + 0xb54) + 0x17c);
        int* pu = ((F_d9030*)*(void**)((char*)this + 0xb20))->f(*(void**)((char*)this + 0xb54));
        int iVar10 = *(int*)(*(int*)((char*)this + 0xb54) + 0x17c);
        float local_c[3];
        float* pf = FUN_0099c1a0(local_c, (void*)(iVar10 + 0x3c),
                                  (void*)(*(int*)(*pu) * 0x2bc + *(int*)(iVar10 + 0x2e4) + 0x10));
        param_2[0] = pf[0] + GF(iVar9 + 0x18);
        param_2[1] = pf[1] + GF(iVar9 + 0x1c);
        param_2[2] = pf[2] + GF(iVar9 + 0x20);
    }
}

// @ 0x00c0d860
void __thiscall CCB_s00c0_ce80::d860(float* param_2)
{
    float* pf = ((F_a048a0*)(*(void**)((char*)this + 0xb54)))->f();
    float f1 = pf[0], f2 = pf[1], f3 = pf[2];
    float inv = 1.0f / sqrtf(f1 * f1 + f2 * f2 + f3 * f3 + GF(0x13ec4b8));
    char* iVar8 = (char*)(*(void*(__thiscall*)(void*))((*(void***)((char*)this + 0xc0))[0x68 / 4]))((char*)this + 0xc0);
    float f9 = GF(iVar8 + 0x14) + GF(0x13ec480);
    param_2[0] = pf[0] + (f1 * inv) * f9;
    param_2[1] = pf[1] + (f2 * inv) * f9;
    param_2[2] = pf[2] + (f3 * inv) * f9;
}

// @ 0x00c0d950
void __thiscall CCB_s00c0_ce80::d950(char param_2)
{
    *(uint8_t*)((char*)this + 0xb65) = (uint8_t)param_2;
    *(uint8_t*)((char*)*(void**)((char*)this + 0xb54) + 0x84) = (uint8_t)param_2;
}

// @ 0x00c0d970
struct IdentityColorRGB { uint32_t r, g, b; };
struct IdentityColorTarget {
    char pad[0x74];
    IdentityColorRGB color;   // +0x74
    float alpha;              // +0x80
};
void __thiscall CCB_s00c0_ce80::d970(float* param_2)
{
    IdentityColorTarget* t = *(IdentityColorTarget**)((char*)this + 0xb54);
    t->color = *(IdentityColorRGB*)param_2;
    t = *(IdentityColorTarget**)((char*)this + 0xb54);
    t->alpha = 1.0f;
}

// @ 0x00c0d9b0
void __thiscall CCB_s00c0_ce80::d9b0()
{
    void* c = *(void**)((char*)this + 0xb54);
    void* b = *(void**)((char*)this + 0xb20);
    float f = GF((char*)c + 0x3c);
    float x = GF((char*)b + 0x554) * f;
    float y = GF((char*)b + 0x558) * f;
    float z = GF((char*)b + 0x55c);
    float fVar4 = x * -0.5f;
    float fVar5 = y * -0.5f;
    float fVar2 = z * f;
    void* self = (char*)this + 0xc0;
    float r = (*(float(__thiscall*)(void*))((*(void***)self)[0x34 / 4]))(self);
    float vec[6];
    vec[0] = fVar4; vec[1] = fVar5; vec[2] = 0.0f;
    vec[3] = -fVar4; vec[4] = -fVar5; vec[5] = fVar2;
    (*(void(__thiscall*)(void*, float*, float))((*(void***)self)[0x64 / 4]))(self, vec, 1.0f);
    G32((char*)self + 0x50) |= 0x20;
    GF((char*)this + 0x124) = r;
    GF((char*)this + 0x13c) = r;
}

// @ 0x00c0dac0
int __thiscall CCB_s00c0_ce80::dac0()
{
    int u = ((F_c0c080*)this)->f(0x25);
    if ((*(int(__thiscall*)(void*, int))((*(void***)this)[0xb4 / 4]))(this, u) == 0)
        u = ((F_c0c080*)this)->f(0x54);
    if ((*(int(__thiscall*)(void*, int))((*(void***)this)[0xb4 / 4]))(this, u) == 0)
        return ((F_c0c080*)this)->f(0x4d);
    return u;
}

// @ 0x00c0db10
int __thiscall CCB_s00c0_ce80::db10()
{
    int u = ((F_c0c080*)this)->f(0x1e);
    if ((*(int(__thiscall*)(void*, int))((*(void***)this)[0xb4 / 4]))(this, u) == 0)
        u = ((F_c0c080*)this)->f(0x3e);
    if ((*(int(__thiscall*)(void*, int))((*(void***)this)[0xb4 / 4]))(this, u) == 0)
        return ((F_c0c080*)this)->f(0x4a);
    return u;
}

// @ 0x00c0db60
int __thiscall CCB_s00c0_ce80::db60()
{
    if (*(int*)((char*)this + 0xa94) != 0)
        return *(int*)(*(int*)((char*)this + 0xa94) + 0x180);
    return *(int*)((char*)this + 0x9c);
}

// @ 0x00c0db80
float __cdecl FUN_00c0db80(float param_1, int param_2)
{
    void* a = FUN_00b3d320(SP_GetCurrentGameMode());
    void* t = ((F_b1daf0*)a)->f();
    float local_c = GF(0x13ec4d0);
    float local_4 = GF(0x1486114);
    float local_10 = GF(0x1488874);
    float fVar7 = local_4;
    if (t != 0) {
        void* h = 0;
        if (((F_terrain*)t)->q(0x7422b3b, &h) && *(short*)((char*)h + 0x12) == 0xd)
            local_c = *((F_41ea70*)h)->f();
        h = 0;
        if (((F_terrain*)t)->q(0x760c17c, &h) && *(short*)((char*)h + 0x12) == 0xd) {
            local_4 = *((F_41ea70*)h)->f();
            fVar7 = local_4;
        }
        h = 0;
        if (((F_terrain*)t)->q(0x760c181, &h) && *(short*)((char*)h + 0x12) == 0xd)
            local_10 = *((F_41ea70*)h)->f();
    }
    float fVar8 = local_10 * param_1 * fVar7 * local_c + GF(param_2 + 0xe58);
    float* pf5 = (float*)(param_2 + 0xe58);
    float* pf6 = (float*)(param_2 + 0xe5c);
    *pf5 = fVar8;
    if (fVar8 > *pf6) *pf5 = *pf6;
    return param_1 - fVar7 * param_1;
}

// @ 0x00c0dcb0
float __cdecl FUN_00c0dcb0(float param_1)
{
    void* a = FUN_00b3d320(SP_GetCurrentGameMode());
    void* t = ((F_b1daf0*)a)->f();
    float local_8 = GF(0x13eb8a0);
    if (t != 0) {
        void* h = 0;
        ((F_terrain*)t)->q(0x7422b3b, &h);
        h = 0;
        if (((F_terrain*)t)->q(0x760c184, &h) && *(short*)((char*)h + 0x12) == 0xd)
            local_8 = *((F_41ea70*)h)->f();
    }
    return param_1 - local_8 * param_1;
}

// @ 0x00c0dd40
void __thiscall CCB_s00c0_ce80::dd40(float* param_2)
{
    ((F_c88670*)this)->f(param_2);
    char* eax = *(char**)((char*)this + 0xa94);
    if (eax != 0) {
        *(int*)(eax + 4) = *(int*)param_2;
        *(int*)(eax + 8) = *(int*)((char*)param_2 + 4);
        *(int*)(eax + 0xc) = *(int*)((char*)param_2 + 8);
    }
}

// @ 0x00c0dd70
void __thiscall CCB_s00c0_ce80::dd70(float* param_2, float param_3)
{
    char* p = *(char**)((char*)this + 0xb54);
    if (p != 0) {
        *(int*)(p + 0x44) = *(int*)param_2;
        *(int*)(p + 0x48) = *(int*)((char*)param_2 + 4);
        *(int*)(p + 0x4c) = *(int*)((char*)param_2 + 8);
        char* q = *(char**)((char*)this + 0xb54);
        *(float*)(q + 0x40) = param_3;
    }
}

// @ 0x00c0ddb0
void __thiscall CCM_s00c0_ddb0::ddb0(float* param_2)
{
    ((F_58*)this)->f(param_2);
    char* p = *(char**)((char*)this + 0xa94);
    if (p != 0) {
        *(int*)(p + 0x10) = *(int*)((char*)param_2 + 4);
        GF(p + 0x14) = -param_2[0];
        *(int*)(p + 0x18) = *(int*)((char*)param_2 + 0xc);
        GF(p + 0x1c) = -param_2[2];
    }
}

// @ 0x00c0dfb0
void* __thiscall CCM_s00c0_ddb0::dfb0(int param)
{
    void* p = mpInner_b54;
    if (p != 0) {
        p = ((CCMInner*)p)->mpTable_17c;
        return ((F_cab60*)p)->f(param);
    }
    return 0;
}

// @ 0x00c0dfd0
void* __thiscall CCM_s00c0_ddb0::dfd0(int param)
{
    CCMInner* p = mpInner_b54;
    if (p != 0) {
        F_cab60* t = (F_cab60*)p->mpTable_17c;
        char* r = (char*)t->f(param);
        if (r != 0) return *(void**)(r + 0x8c);
    }
    return 0;
}

// @ 0x00c0e000
char __thiscall CCM_s00c0_ddb0::e000(int param_2, int param_3)
{
    char ok = 0;
    CCMInner* p = mpInner_b54;
    if (p != 0) {
        F_cab60* t = (F_cab60*)p->mpTable_17c;
        char* r = (char*)t->f(param_2);
        if (r != 0 && param_3 != -1) {
            *(int*)(r + 8) = param_3;
            ok = 1;
        }
    }
    return ok;
}

// @ 0x00c0e040
void* __thiscall CCM::e040()
{
    char* c = *(char**)((char*)this + 0xb54);
    uint32_t local_4 = 0;
    if (c != 0) {
        void* vt = *(void**)c;
        ((void(__thiscall*)(void*, void*, int, int, int))(*(void**)((char*)vt + 0x58)))(
            c, &local_4, 0, 0, 0);
    }
    return (void*)local_4;
}

// @ 0x00c0e070
bool __thiscall CCM_s00c0_ddb0::e070(int param_2)
{
    char* c = *(char**)((char*)this + 0xb54);
    if (c != 0 && *(int*)(c + 0x184) != 0) {
        char* r = (char*)FUN_009ff6f0(*(void**)(c + 0x184), (void*)param_2);
        if (r != 0) return *(int*)(r + 0xc0) != 0;
        return 0;
    }
    return 1;
}

// @ 0x00c0e0c0
bool __thiscall CCM::e0c0(int param_2)
{
    char* c = *(char**)((char*)this + 0xb54);
    if (c == 0) return 0;
    uint32_t local_4 = 0;
    void* vt = *(void**)c;
    ((void(__thiscall*)(void*, void*, int, int, int))(*(void**)((char*)vt + 0x58)))(
        c, &local_4, 0, 0, 0);
    if ((int)local_4 == param_2) return 1;
    if (!((F_a02b40*)c)->f(param_2)) return 0;
    return 1;
}

// @ 0x00c0e120
char __thiscall CCM_s00c0_ddb0::e120(int param_2)
{
    char* p = *(char**)(*(char**)((char*)this + 0xb54) + 0x184);
    for (int i = 0; i < 0x10; ++i) {
        int v = ((int*)(p + 0xf4c))[i];
        if (v != -1 && *(int*)(v * 0xf0 + (int)p + 0xe0) == param_2) return 1;
    }
    return 0;
}

// @ 0x00c0e170
char __thiscall CCM_s00c0_ddb0::e170(int param_2)
{
    char* pi = *(char**)((char*)this + 0xb54);
    if (pi == 0) return 1;
    if (param_2 == 0) {
        char* r = (char*)FUN_009ff6f0(*(void**)(pi + 0x184), *(void**)((char*)this + 0xe88));
        if (r != 0) {
            if (*(int*)(r + 0xc0) == 0) return 0;
            if (((F_a04940*)pi)->f(*(int*)((char*)this + 0xe88))) return 1;
            if (((F_a02b20*)pi)->f(*(int*)((char*)this + 0xe88))) return 1;
            if (!((F_a04990*)pi)->f(*(int*)((char*)this + 0xe88))) return 0;
            if (((F_a049f0*)pi)->f(*(int*)((char*)this + 0xe88)) < 1.0f) return 0;
            return 1;
        }
    } else {
        uint32_t local = 0;
        void* vt = *(void**)pi;
        (*(void(__thiscall**)(void*, void*, int, int, int))(*(void**)((char*)vt + 0x58)))(
            pi, &local, 0, 0, 0);
        if (local != 0) {
            if (param_2 != (int)local) {
                return ((F_a02b40*)pi)->f(param_2) == 0;
            }
            if (((F_a04940*)pi)->f(0)) return 1;
            if (((F_a02b20*)pi)->f(0)) return 1;
            if (((F_a04990*)pi)->f(0)) {
                if (((F_a049f0*)pi)->f(0) >= 1.0f) return 1;
            }
            return 0;
        }
    }
    return 1;
}

// @ 0x00c0e2c0
char __thiscall CCM_s00c0_ddb0::e2c0(int param_2)
{
    char* c = *(char**)((char*)this + 0xb54);
    if (c == 0 || *(int*)(c + 0x184) == 0) return 1;
    char* r = (char*)FUN_009ff6f0(*(void**)(c + 0x184), (void*)param_2);
    if (r == 0) return 1;
    if (*(int*)(r + 0xc0) == 0) return 0;
    if (((F_a04940*)c)->f(param_2)) return 1;
    if (((F_a02b20*)c)->f(param_2)) return 1;
    if (((F_a04990*)c)->f(param_2)) {
        if (((F_a049f0*)c)->f(*(int*)((char*)this + 0xe88)) >= 1.0f) return 1;
    }
    return 0;
}

// @ 0x00c0e370
void* __thiscall CCM::e370()
{
    char* c = *(char**)((char*)this + 0xb54);
    uint32_t local_4 = 0;
    if (c != 0) {
        void* vt = *(void**)c;
        ((void(__thiscall*)(void*, int, int, void*, int))(*(void**)((char*)vt + 0x58)))(
            c, 0, 0, &local_4, 0);
    }
    return (void*)local_4;
}

// @ 0x00c0e3a0
float __thiscall CCM_s00c0_ddb0::e3a0()
{
    char* c = *(char**)((char*)this + 0xb54);
    float local_4 = 0.0f;
    if (c != 0) {
        void* vt = *(void**)c;
        ((void(__thiscall*)(void*, void*, void*, int, int))(*(void**)((char*)vt + 0x58)))(
            c, 0, &local_4, 0, 0);
    }
    return local_4;
}

// @ 0x00c0e3d0
char __thiscall CCM_s00c0_ddb0::e3d0()
{
    char* c = *(char**)((char*)this + 0xa94);
    if (c == 0) return 1;
    uint32_t local_4 = 0;
    void* vt = *(void**)c;
    ((void(__thiscall*)(void*, void*, int, int, int))(*(void**)((char*)vt + 0x58)))(
        c, &local_4, 0, 0, 0);
    if (local_4 != 0) {
        void* lm = FUN_0067cb20();
        char* r = (char*)((void*(__thiscall*)(void*, uint32_t))(*(void**)((char*)*(void**)lm + 0x40)))(
            lm, local_4);
        if (r != 0) return *(char*)(r + 0x1d);
    }
    return 1;
}

// @ 0x00c0e420
char __thiscall CCM_s00c0_ddb0::e420()
{
    void* lm = FUN_0067cb20();
    char* c = *(char**)((char*)this + 0xb54);
    uint32_t local_4 = 0;
    if (c != 0) {
        void* vt = *(void**)c;
        ((void(__thiscall*)(void*, void*, int, int, int))(*(void**)((char*)vt + 0x58)))(
            c, &local_4, 0, 0, 0);
    }
    char* r = (char*)((void*(__thiscall*)(void*, uint32_t))(*(void**)((char*)*(void**)lm + 0x40)))(
        lm, local_4);
    return (r != 0 && *(char*)(r + 0x1c) != 0) ? 1 : 0;
}

// @ 0x00c0e480
double SP::cSPCreatureBase::GetTime()
{
    if ((G32(0x168db88) & 1) == 0) {
        G32(0x168db88) |= 1;
        ((F_sw*)0x168db70)->Ctor(4, 1);
        FUN_011e07ef((void*)0x13c3580);
    }
    unsigned long long u = ((F_sw*)0x168db70)->GetElapsedTime();
    double d = (double)(long long)u;
    return (float)(d * *(double*)0x13f6560);
}

// @ 0x00c0e4f0
float __thiscall CCM::e4f0()
{
    if (SP_GetCurrentGameMode() == (void*)0x1654c10
        && *(int*)(G32((int)&g_16c7aa4) + 0xcc) == 2
        && this != 0) {
        int r = (int)((VQuery3*)this)->Query(0xd0036e08);
        bool bFlag = ((G32((char*)this + 0xb58) >> 9) & 1) != 0;
        if (r != 0 && !bFlag) {
            void* q = ((F_c04750*)(void*)r)->Call04750();
            if (q != 0) return GF((char*)q + 0x484);
        }
    }
    char* e = *(char**)((char*)this + 0xe84);
    if (e != 0) {
        float v = GF(e + 0x34c);
        if (v >= 0.0f) return v;
    }
    return GF((int)g_150c8bc);
}

// @ 0x00c0e580
void* __thiscall CCM_s00c0_ddb0::e580()
{
    char* c = *(char**)((char*)this + 0xb54);
    if (c != 0) {
        float* p = ((F_a048a0*)c)->f();
        if (p[0] != GF((int)&g_168d910) || p[1] != GF((int)&g_168d914) || p[2] != GF((int)&g_168d918)) {
            return ((F_a048a0*)(*(void**)((char*)this + 0xb54)))->f();
        }
    }
    void* self = (char*)this + 0xc0;
    return ((void*(__thiscall*)(void*))((*(void***)self)[0x2c / 4]))(self);
}

// @ 0x00c0e5f0
void __thiscall CCM_s00c0_ddb0::e5f0(float param_2)
{
    char* p = *(char**)((char*)this + 0xa94);
    if (p != 0) {
        GF(p + 0x3c) = param_2;
        SP_GetCurrentGameMode();
    }
    if (param_2 != GF((char*)this + 0x64)) {
        GF((char*)this + 0x64) = param_2;
        GF((char*)this + 0x7c) = param_2;
        ((F_d9b0*)((char*)this - 0xc0))->f();
    }
}

// @ 0x00c0e640
void __thiscall CCM_s00c0_ddb0::e640(int param_2)
{
    char* p = *(char**)((char*)this + 0xb54);
    if (p != 0) *(int*)(p + 0x170) = param_2;
}

// @ 0x00c0e660
int __thiscall CCM::e660()
{
    char* b = *(char**)((char*)this + 0xb20);
    struct IntVec { int* mpBegin; int* mpEnd; };
    IntVec* v = (IntVec*)(b + 0x6d4);
    return (int)(v->mpEnd - v->mpBegin);
}

// @ 0x00c0e680
int __thiscall CCM_s00c0_ddb0::e680(int param_2)
{
    if (param_2 == -1) return 0;
    char* b = *(char**)((char*)this + 0xb20);
    return *(int*)(*(int*)(b + 0x6d4) + param_2 * 4);
}

// @ 0x00c0e6a0
int __thiscall CCM_s00c0_ddb0::e6a0()
{
    int u = 0;
    if (this == 0) return 0;
    char* pi = (char*)(*(void*(__thiscall**)(void*, int))((*(void***)this)[0xc / 4]))(this, 0x4f176642);
    if (pi == 0) return 0;
    if (!((F_c232c0*)pi)->f()) return 0;
    void* nm = FUN_00b3d300();
    void* gd = ((F_bfc5f0*)nm)->f();
    void* a = (*(void*(__thiscall**)(void*, int))(*(void**)((char*)gd + 0x4c)))(gd, 1);
    void* b = (*(void*(__thiscall**)(void*, void*))(*(void**)((char*)pi + 0x4c)))(pi, a);
    void* rm = FUN_00b3d2c0(b);
    int iVar8 = ((F_d00a70*)rm)->f();
    char c1 = (*(char(__thiscall**)(void*))((*(void***)this)[0xd4 / 4]))(this);
    if (iVar8 == 1) { if (c1 == 0) return 3; }
    else if (iVar8 == 2) { if (c1 == 0) return 2; }
    else if (iVar8 == 3 && c1 == 0) return 1;
    return u;
}

void* __cdecl FUN_00ac8960(void*);           // 0x00ac8960
struct F_c04790 { int __thiscall f(); };      // 0x00c04790

// @ 0x00c0e8d0
char __thiscall CCM_s00c0_ddb0::e8d0(int param_2, int param_3) {
    char* p2 = (char*)param_2;
    if ((G32((char*)this + 0xb20) == G32(p2 + 0xb20) && SP_GetCurrentGameMode() != (void*)0x1654c10)
        || (((G32((char*)this + 0xb58) >> 8) & 1) != 0
            && (((G32(p2 + 0xb58) >> 8) & 1) != 0 || ((G32(p2 + 0xb58) >> 9) & 1) != 0)))
        return 1;
    if (SP_GetCurrentGameMode() == (void*)0x1654c10) {
        if (((G32((char*)this + 0xb58) >> 9) & 1) != 0 && ((G32(p2 + 0xb58) >> 8) & 1) != 0)
            return 1;
    } else {
        char c1 = (*(char(__thiscall**)(void*, int))((*(void***)this)[0xd0 / 4]))(this, param_3);
        if (c1 != 0 && ((G32(p2 + 0xb58) >> 8) & 1) != 0) return 1;
    }
    char* ebx = (char*)FUN_00b3d4c0();
    if (ebx == 0) return 0;
    if (((G32((char*)this + 0xb58) >> 8) & 1) != 0) {
        if (SP_GetCurrentGameMode() == (void*)0x1654c10
            && ((G32(p2 + 0xb58) >> 9) & 1) == 0
            && ((G32((char*)this + 0xb58) >> 9) & 1) == 0) {
            char* s = (char*)FUN_00ac8960((void*)param_2);
            char* d = (char*)FUN_00ac8960((void*)this);
            if (s == 0 || d == 0) return 0;
            int x = ((F_c04790*)s)->f();
            int y = ((F_c04790*)d)->f();
            if (x != y || y == 1) return 0;
            return 1;
        }
        switch (param_3) {
        case 3:
            if (((F_ba3f90*)ebx)->f((void*)((char*)this + 0xb28), (CB*)this, (unsigned int)param_2) == 3) return 1;
            /* fallthrough */
        case 4:
            if (((F_ba3f90*)ebx)->f((void*)((char*)this + 0xb28), (CB*)this, (unsigned int)param_2) == 4) return 1;
            /* fallthrough */
        case 6:
            return ((F_ba3f90*)ebx)->f((void*)((char*)this + 0xb28), (CB*)this, (unsigned int)param_2) == 6;
        default:
            return 0;
        }
    }
    switch (param_3) {
    case 3:
        if (((F_ba3f90*)ebx)->f((void*)(p2 + 0xb28), (CB*)this, (unsigned int)param_2) == 3) return 1;
        /* fallthrough */
    case 4:
        if (((F_ba3f90*)ebx)->f((void*)(p2 + 0xb28), (CB*)this, (unsigned int)param_2) == 4) return 1;
        /* fallthrough */
    case 6:
        return ((F_ba3f90*)ebx)->f((void*)(p2 + 0xb28), (CB*)this, (unsigned int)param_2) == 6;
    default:
        return 0;
    }
}

// @ 0x00c0eae0
void Simulator_cCreatureBase::SteerTowards(const Vec3* pTarget, int nDelta)
{
    (void)nDelta;
    Vec3* pPosition = GetPosition();
    Vec3 direction;
    direction.mX = pTarget->mX - pPosition->mX;
    direction.mY = pTarget->mY - pPosition->mY;
    direction.mZ = pTarget->mZ - pPosition->mZ;

    float fDistance = direction.mX * direction.mX + direction.mY * direction.mY +
                      direction.mZ * direction.mZ;
    fDistance = (float)__builtin_sqrtf(fDistance);

    if (fDistance <= 0.0001f) {
        Vec3 local;
        local.mX = -1.0f;
        local.mY = 0.0f;
        local.mZ = 0.0f;
        Vec3* pRotated = RotateVectorAround(&local, &local, &mpAnimatedCreature->mOrientation);
        if (!IsVectorValid(&local))
            (void)pRotated;
    } else {
        float fInv = 1.0f / fDistance;
        direction.mX *= fInv;
        direction.mY *= fInv;
        direction.mZ *= fInv;
    }

    if (mpAnimatedCreature != nullptr) {
        CreatureUpdateTransform(&direction, 1);
    }
}

// @ 0x00c0ed60
void Simulator_cCreatureBase::SetCreatureTarget(cCombatant* pTarget, bool bFlag, int nIntention)
{
    mTargetFlag = bFlag ? 1 : 0;
    mIntentionTowardsTarget = nIntention;

    if (mpCombatantTarget == pTarget)
        return;

    if (pTarget == nullptr) {
        if (mpCombatantTarget != nullptr) {
            IRefCounted* pOld = mpCombatantTarget;
            mpCombatantTarget = nullptr;
            pOld->Release();
        }
        if (mpAnimatedCreature != nullptr && mpAnimatedCreature->mState == 0)
            IsAnimationQueuedOrCurrent(this);
    } else {
        cCombatant* pOld = mpCombatantTarget;
        if (pTarget != pOld) {
            pTarget->AddRef();
            mpCombatantTarget = pTarget;
            if (pOld != nullptr)
                pOld->Release();
        }
    }

    if (IsVisible() && mpCombatantTarget != nullptr) {
        uint32_t nTargetPolitical = mpCombatantTarget->GetPoliticalID();
        if (nTargetPolitical != GetOwnPoliticalID(this) && GetCurrentGameMode_s00c0_eae0() == &gGameModeTribe) {
            CreatureAddRelation(pTarget);
            CreaturePlayAttackAnimation();
        }
    }
}

// @ 0x00c0ee70
void* Simulator_cCreatureBase::GetTargetAsCreature()
{
    IRefCounted* pTarget = mpSteeringTarget;
    if (pTarget != nullptr)
        return pTarget->QueryTarget((const void*)0xce9f6639);
    return nullptr;
}

// @ 0x00c0ee90
void* Simulator_cCreatureBase::ApplyCombatTarget()
{
    IRefCounted* pSteering = mpSteeringTarget;
    if (pSteering != nullptr) {
        IRefCounted* pTarget = (IRefCounted*)pSteering->Query();
        if (pTarget != nullptr) {
            if (pTarget->v20() == 0x18eb45e)
                return pTarget;
        }
    }
    return nullptr;
}

// @ 0x00c0eec0
void Simulator_cCreatureBase::UpdateSteering(int nDelta, float fAmount)
{
    mSteeringTimer += nDelta;

    if (fAmount == 0.0f) {
        mSteeringTimer = 0;
        mPathValid = 0;
        return;
    }

    if (mSteeringTimer > 1000u) {
        mSteeringTimer = 0;
        mPathValid = 0;
    }

    Vec3 offset;
    offset.mX = 0.0f;
    offset.mY = 0.0f;
    offset.mZ = 0.0f;

    float fScale = 1.0f;
    if ((mSteeringFlags >> 9 & 1) != 0 && mpSteeringModel != nullptr && mOrientationValid != 0) {
        Vec3* pDirection = GetDirection();
        if (pDirection->mX * pDirection->mX + pDirection->mY * pDirection->mY +
                pDirection->mZ * pDirection->mZ == 0.0f) {
            offset.mX = 0.0f;
            offset.mY = 1.0f;
        }
    }

    float fSpeed = *(float*)((uint8_t*)mpSteeringModel + 0x548);
    if (mOrientationValid == 0) {
        Vec3 velocity;
        Vec3* pDirection = GetDirection();
        float fLen = pDirection->mX * pDirection->mX + pDirection->mY * pDirection->mY +
                     pDirection->mZ * pDirection->mZ;
        float fInv = 1.0f / (float)__builtin_sqrtf(fLen + 1e-08f);
        velocity.mX = pDirection->mX * fInv;
        velocity.mY = pDirection->mY * fInv;
        velocity.mZ = pDirection->mZ * fInv;
        float fDot = velocity.mX * offset.mX + velocity.mY * offset.mY + velocity.mZ * offset.mZ;
        if (fDot < 0.0f)
            fSpeed += fDot;
    }

    Vec3* pForward = GetDirection();
    float fLen = pForward->mX * pForward->mX + pForward->mY * pForward->mY +
                 pForward->mZ * pForward->mZ;
    float fInv = 1.0f / (float)__builtin_sqrtf(fLen + 1e-08f);
    float fAmountScaled = (float)mSteeringTimer;
    offset.mX += pForward->mX * fInv * fSpeed * fAmountScaled * 0.001f * fScale;
    offset.mY += pForward->mY * fInv * fSpeed * fAmountScaled * 0.001f * fScale;
    offset.mZ += pForward->mZ * fInv * fSpeed * fAmountScaled * 0.001f * fScale;

    CreatureMoveStep(&offset, 0);
}

// @ 0x00c0f280
void Simulator_cCreatureBase::Hide()
{
    if (mpAnimatedCreature != nullptr) {
        mpAnimatedCreature->mFlags &= ~1u;
        *(uint8_t*)((uint8_t*)mpAnimatedCreature + 0x64) = 0;
        mpAnimatedCreature->SetVisible(true);
    }
}

// @ 0x00c0f2b0
void Simulator_cCreatureBase::Show()
{
    if (mpAnimatedCreature != nullptr) {
        mpAnimatedCreature->mFlags |= 1u;
        *(uint8_t*)((uint8_t*)mpAnimatedCreature + 0x64) = 1;
    }
}

// @ 0x00c0f2e0
bool Simulator_cCreatureBase::TraceTo(const Vec3* pFrom, const Vec3* pTo, Vec3* pOut)
{
    Vec3 direction;
    direction.mX = pTo->mX - pFrom->mX;
    direction.mY = pTo->mY - pFrom->mY;
    direction.mZ = pTo->mZ - pFrom->mZ;

    float fLen = direction.mX * direction.mX + direction.mY * direction.mY +
                 direction.mZ * direction.mZ;
    float fInv = 1.0f / (float)__builtin_sqrtf(fLen + 1e-08f);
    direction.mX *= fInv;
    direction.mY *= fInv;
    direction.mZ *= fInv;

    Vec3 hit;
    hit.mX = 0.0f;
    hit.mY = 0.0f;
    hit.mZ = 0.0f;

    if (!TraceTerrain(pFrom, &direction, nullptr, &hit.mX, 0, 0))
        return false;

    *pOut = hit;

    float fToHit = (pFrom->mX - pOut->mX) * (pFrom->mX - pOut->mX) +
                   (pFrom->mY - pOut->mY) * (pFrom->mY - pOut->mY) +
                   (pFrom->mZ - pOut->mZ) * (pFrom->mZ - pOut->mZ);
    float fToEnd = (pFrom->mX - pTo->mX) * (pFrom->mX - pTo->mX) +
                   (pFrom->mY - pTo->mY) * (pFrom->mY - pTo->mY) +
                   (pFrom->mZ - pTo->mZ) * (pFrom->mZ - pTo->mZ);
    return __builtin_sqrtf(fToHit) <= __builtin_sqrtf(fToEnd);
}

// 0x00c0f490 (byte-exact lifted version: match/slices/s00c0f490/s00c0f490.cpp)
void Simulator_cCreatureBase::ResetCombatants()
{
    mFlags = 0;
    if (mpSenseObject != nullptr) {
        IRefCounted* pOld = mpSenseObject;
        pOld->Query();
        if (mpSenseObject != nullptr) {
            mpSenseObject = nullptr;
            pOld->Release();
        }
    }
    if (mpSteeringTarget != nullptr) {
        IRefCounted* pOld = mpSteeringTarget;
        pOld->Query();
        if (mpSteeringTarget != nullptr) {
            mpSteeringTarget = nullptr;
            pOld->Release();
        }
    }
    if (mpCombatantTarget != nullptr) {
        cCombatant* pOld = mpCombatantTarget;
        mpCombatantTarget = nullptr;
        pOld->Release();
    }
    mIntentionTowardsTarget = 0;
}

// @ 0x00c0f510
bool Simulator_cCreatureBase::IsSlotEmpty(uint32_t nIndex)
{
    int nCount = (int)(mpSlotsEnd - mpSlotsBegin);
    bool bEmpty = true;
    if (nIndex < (uint32_t)nCount) {
        cCombatantSlot* pSlot = &mpSlotsBegin[nIndex];
        if (pSlot->mpCombatant != nullptr)
            bEmpty = false;
        if (pSlot->mSecondaryKey != 0)
            bEmpty = false;
    }
    return bEmpty;
}

// @ 0x00c0f570
int Simulator_cCreatureBase::CountValid()
{
    int nValid = 0;
    for (int i = 0; i < (int)(mpSlotsEnd - mpSlotsBegin); ++i) {
        if (mpSlotsBegin[i].mSecondaryKey != 0 || mpSlotsBegin[i].mpCombatant != 0)
            ++nValid;
    }
    return nValid;
}

// @ 0x00c0f5f0
bool Simulator_cCreatureBase::IsFull()
{
    int nValid = CountValid();
    return nValid == (int)(mpSlotsEnd - mpSlotsBegin);
}

// @ 0x00c0f620
uint32_t Simulator_cCreatureBase::FindFirstEmpty()
{
    uint32_t nCount = (uint32_t)(mpSlotsEnd - mpSlotsBegin);
    for (uint32_t i = 0; i < nCount; ++i) {
        cCombatantSlot* pSlot = &mpSlotsBegin[i];
        if (pSlot->mpCombatant == nullptr && pSlot->mSecondaryKey == 0)
            return i;
    }
    return 0xffffffff;
}

// @ 0x00c0f6b0
uint32_t Simulator_cCreatureBase::FindRandomEmpty()
{
    int nValid = CountValid();
    int nCount = (int)(mpSlotsEnd - mpSlotsBegin);
    int nEmpty = nCount - nValid;
    uint32_t nPick = RandomGet().RandomUint32Uniform(nEmpty);
    int nSeen = 0;
    for (int i = 0; i < nCount; ++i) {
        if (mpSlotsBegin[i].mpCombatant == nullptr && mpSlotsBegin[i].mSecondaryKey == 0) {
            if (nSeen == (int)nPick)
                return (uint32_t)i;
            ++nSeen;
        }
    }
    return 0xffffffff;
}

// @ 0x00c0f780
uint32_t Simulator_cCreatureBase::FindFirstValid()
{
    uint32_t nCount = (uint32_t)(mpSlotsEnd - mpSlotsBegin);
    for (uint32_t i = 0; i < nCount; ++i) {
        if (mpSlotsBegin[i].mpCombatant != nullptr || mpSlotsBegin[i].mSecondaryKey != 0)
            return i;
    }
    return 0xffffffff;
}

// @ 0x00c0f810
uint32_t Simulator_cCreatureBase::FindNextValid(int nAfter)
{
    int nCount = (int)(mpSlotsEnd - mpSlotsBegin);
    for (int i = nAfter + 1; i < nCount; ++i) {
        if (mpSlotsBegin[i].mpCombatant != nullptr || mpSlotsBegin[i].mSecondaryKey != 0)
            return (uint32_t)i;
    }
    return 0xffffffff;
}

// @ 0x00c0f8a0
cCombatant* Simulator_cCreatureBase::GetAt(uint32_t nIndex)
{
    unsigned nCount = (unsigned)(int)(mpSlotsEnd - mpSlotsBegin);
    cCombatant* pResult = nullptr;
    if (nIndex < nCount)
        pResult = mpSlotsBegin[nIndex].mpCombatant;
    return pResult;
}

// @ 0x00c0f8f0
uint32_t Simulator_cCreatureBase::FindByCombatant(int nCombatant)
{
    uint32_t result = 0xffffffff;
    uint32_t nCount = (uint32_t)(mpSlotsEnd - mpSlotsBegin);
    for (uint32_t i = 0; i < nCount; ++i) {
        if (nCombatant == 0)
            return 0xffffffff;
        if ((int)(intptr_t)mpSlotsBegin[i].mpCombatant == nCombatant)
            return i;
    }
    return result;
}

// @ 0x00c0f960
uint32_t Simulator_cCreatureBase::FindByKey(int nKey)
{
    uint32_t result = 0xffffffff;
    int nCount = (int)(mpSlotsEnd - mpSlotsBegin);
    for (uint32_t i = 0; i < (uint32_t)nCount; ++i) {
        if (mpSlotsBegin[i].mKey == nKey) {
            result = i;
            break;
        }
    }
    return result;
}

// @ 0x00c0f9b0
cCombatantSlot* Simulator_cCreatureBase::FindSlotByKey(int nKey, uint32_t* pIndex)
{
    uint32_t nCount = (uint32_t)(mpSlotsEnd - mpSlotsBegin);
    cCombatantSlot* pSlot = mpSlotsBegin;
    for (uint32_t i = 0; i < nCount; ++i, ++pSlot) {
        if (pSlot->mKey == nKey) {
            if (pIndex != nullptr)
                *pIndex = i;
            return pSlot;
        }
    }
    return nullptr;
}

// @ 0x00c0fa10
cCombatantSlot* Simulator_cCreatureBase::FindSlotByCombatant(int nCombatant, uint32_t* pIndex)
{
    uint32_t nCount = (uint32_t)(mpSlotsEnd - mpSlotsBegin);
    cCombatantSlot* pSlot = mpSlotsBegin;
    for (uint32_t i = 0; i < nCount; ++i, ++pSlot) {
        if ((int)(intptr_t)pSlot->mpCombatant == nCombatant) {
            if (pIndex != nullptr)
                *pIndex = i;
            return pSlot;
        }
    }
    return nullptr;
}

// @ 0x00c0fa70
void* __thiscall CAN::fa70(uint32_t mask, uint32_t* pIndex)
{
    int n = (int)((char*)this->bindEnd - (char*)this->bindBegin);
    unsigned count = (unsigned)(n / 0x24);
    if (count == 0) return 0;
    AnimBinding* e = this->bindBegin;
    unsigned i = 0;
    do {
        int b = e->maskBit;
        if (b != 0 && (mask & (1u << b)) != 0) {
            if (pIndex != 0) *pIndex = i;
            return e;
        }
        ++i;
        ++e;
    } while (i < count);
    return 0;
}

// @ 0x00c0fae0
void __thiscall CAN::fae0(int param_2)
{
    if (param_2 == 0) return;
    AnimBinding* b = (AnimBinding*)param_2;
    int v = b->handle;
    if (v != 0) {
        void* c = this->animCtx;
        if (c != 0) ((F_a01f10*)((CANCtx*)c)->bindingDst)->f(v, 0);
        b->handle = 0;
    }
    b->maskBit = 0;
    b->f08 = 0;
    b->f0c = 0;
    b->f10 = 0;
    b->weight = 0.0f;
    void** slot = (void**)&b->target;
    if (void* q = *slot) {
        *slot = 0;
        ((void (__thiscall *)(void*))(*(int**)q)[0xc0 / 4])(q);
    }
}

// @ 0x00c0fb40
void __thiscall CAN::fb40(int param_2)
{
    if (param_2 == 0) return;
    AnimBinding* b = (AnimBinding*)param_2;
    int v = b->handle;
    if (v == 0) return;
    void* c = this->animCtx;
    if (c == 0) return;
    ((F_a01f10*)((CANCtx*)c)->bindingDst)->f(v, 0);
    b->handle = 0;
}

// @ 0x00c0fb80
void __thiscall CAN::fb80(int, int)
{
    char* c = *(char**)((char*)this + 0xb54);
    if (c != 0) ((F_a047d0*)c)->f(1);
}

// @ 0x00c0fba0
void __cdecl FUN_00c0fba0(int* self, int* vec)
{
    int count = (vec[1] - vec[0]) >> 4;
    int* o = (int*)(*(void*(__thiscall**)(int*))((*(int**)self)[0x20 / 4]))(self);
    void* s = (*(void*(__thiscall**)(void*))((*(void***)o)[0x18 / 4]))(o);
    FUN_0093aa70(s, &count, 1, 0);
    int* p = (int*)vec[0];
    int* end = (int*)vec[1];
    while (p != end) {
        FUN_00c0b030(self, p);
        p += 4;
    }
    (*(void(__thiscall**)(int*))((*(int**)self)[0x1c / 4]))(self);
}

// @ 0x00c0fc10
char __cdecl FUN_00c0fc10(int param_1, int* param_2)
{
    AnimBinding* p = (AnimBinding*)param_2[0];
    AnimBinding* end = (AnimBinding*)param_2[1];
    while (p != end) {
        if (p != 0) {
            void* q = p->target;
            void (__thiscall *fn)(void*, int) =
                (void (__thiscall *)(void*, int))(*(int**)q)[0x1c / 4];
            fn(q, param_1);
        }
        ++p;
    }
    return 1;
}

struct RefObj_s00c0_fc40 {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c(); 
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c(); 
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c(); 
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c(); 
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c(); 
    virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c(); 
    virtual void v60(); virtual void v64(); virtual void v68(); virtual void v6c(); 
    virtual void v70(); virtual void v74(); virtual void v78(); virtual void v7c(); 
    virtual void v80(); virtual void v84(); virtual void v88(); virtual void v8c(); 
    virtual void v90(); virtual void v94(); virtual void v98(); virtual void v9c(); 
    virtual void va0(); virtual void va4(); virtual void va8(); virtual void vac(); 
    virtual void vb0(); virtual void vb4(); virtual void vb8(); 
    virtual void AddRef();     // +0xbc
    virtual void Release();    // +0xc0
};
struct RefPtr_s00c0_fc40 {
    RefObj_s00c0_fc40* mp;
    RefPtr_s00c0_fc40& operator=(const RefPtr_s00c0_fc40& x)
    {
        RefObj_s00c0_fc40* const p = x.mp;
        if (p != mp) {
            RefObj_s00c0_fc40* const old = mp;
            if (p) p->AddRef();
            mp = p;
            if (old) old->Release();
        }
        return *this;
    }
};
inline bool operator==(const RefPtr_s00c0_fc40& a, const RefPtr_s00c0_fc40& b) { return a.mp == b.mp; }
static inline RefPtr_s00c0_fc40* AdjacentFind_s00c0_fc40(RefPtr_s00c0_fc40* first, RefPtr_s00c0_fc40* last)
{
    if (first != last) {
        RefPtr_s00c0_fc40* i = first;
        for (++i; i != last; ++i) {
            if (*first == *i)
                return first;
            first = i;
        }
    }
    return last;
}

// @ 0x00c0fc40
int* __cdecl FUN_00c0fc40(int* pfirst, int* plast)
{
    RefPtr_s00c0_fc40* first = (RefPtr_s00c0_fc40*)pfirst;
    RefPtr_s00c0_fc40* last = (RefPtr_s00c0_fc40*)plast;
    first = AdjacentFind_s00c0_fc40(first, last);
    if (first != last) {
        RefPtr_s00c0_fc40* i = first;
        for (++i; i != last; ++i) {
            if (!(*first == *i))
                *++first = *i;
        }
        ++first;
        return (int*)first;
    }
    return (int*)last;
}

struct SerStream_s00c0_fda0 {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14();
    virtual void* GetStream();
};
struct SerIface_s00c0_fda0 {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual SerStream_s00c0_fda0* GetSer();
};
struct Bits88Set_s00c0_fcf0 {
    uint32_t mWord[3];
    void set(uint32_t i, bool value)
    {
        if (i < 0x58) {
            if (value)
                mWord[i >> 5] |= 1u << (i & 31);
            else
                mWord[i >> 5] &= ~(1u << (i & 31));
        }
    }
};

// @ 0x00c0fcf0
int* __cdecl FUN_00c0fcf0(int* piface, int param_2)
{
    SerIface_s00c0_fda0* iface = (SerIface_s00c0_fda0*)piface;
    Bits88Set_s00c0_fcf0& bits = *(Bits88Set_s00c0_fcf0*)param_2;
    int count;
    void* st = iface->GetSer()->GetStream();
    FUN_0093a780(st, &count, 1, 0);
    for (int i = 0; i < count; ++i) {
        bool b = false;
        FUN_0093ac80(iface->GetSer()->GetStream(), &b);
        bits.set(i, b);
    }
    return piface;
}

struct Bits88_s00c0_fda0 {
    uint32_t mWord[3];
    bool test(uint32_t i) const
    {
        if (i < 0x58)
            return (mWord[i >> 5] & (1u << (i & 31))) != 0;
        return false;
    }
};
static inline void WriteBool_s00c0_fda0(void* s, bool v)
{
    char b = v ? 1 : 0;
    FUN_0093a9a0(s, &b, 1);
}

static inline void WriteU32_s00c0_fda0(void* s, uint32_t v)
{
    FUN_0093aa70(s, &v, 1, 0);
}

// @ 0x00c0fda0
int* __cdecl FUN_00c0fda0(int* piface, int param_2)
{
    SerIface_s00c0_fda0* iface = (SerIface_s00c0_fda0*)piface;
    const Bits88_s00c0_fda0& bits = *(const Bits88_s00c0_fda0*)param_2;
    WriteU32_s00c0_fda0(iface->GetSer()->GetStream(), 0x58);
    for (int i = 0; i < 0x58; ++i) {
        bool t = bits.test(i);
        WriteBool_s00c0_fda0(iface->GetSer()->GetStream(), t);
    }
    return piface;
}

// 0x00c0fe30 (byte-exact lifted version: match/slices/s00c0fe30/s00c0fe30.cpp)
void* __thiscall CAN::fe30(void* src)
{
    AnimBinding* d = (AnimBinding*)this;
    AnimBinding* s = (AnimBinding*)src;
    d->id = s->id;
    d->maskBit = s->maskBit;
    d->f08 = s->f08;
    d->f0c = s->f0c;
    d->f10 = s->f10;
    d->weight = s->weight;
    d->flags = s->flags;
    d->handle = s->handle;
    void* old = d->target;
    void* nw = s->target;
    if (nw != old) {
        if (nw != 0) ((void (__thiscall *)(void*))(*(int**)nw)[0xbc / 4])(nw);
        d->target = nw;
        if (old != 0) ((void (__thiscall *)(void*))(*(int**)old)[0xc0 / 4])(old);
    }
    return this;
}

// @ 0x00c0fea0
struct AnimBind_c0fea0 {      // 0x24-byte animation binding record
    int    m00, m04, m08, m0c, m10;
    float  m14;
    bool   m18;
    int    m1c;
    void*  m20;                // animation object (vtable +0xbc lock / +0xc0 unlock)
    AnimBind_c0fea0(const AnimBind_c0fea0& o)
        : m00(o.m00), m04(o.m04), m08(o.m08), m0c(o.m0c), m10(o.m10),
          m14(o.m14), m18(o.m18), m1c(o.m1c), m20(o.m20) {}
};
void __cdecl FUN_00c0fea0(int* src, int* dst)
{
    AnimBind_c0fea0 local = *(AnimBind_c0fea0*)src;
    void* p = ((AnimBind_c0fea0*)src)->m20;
    if (p != 0) (*(void(__thiscall**)(void*))(*(char**)p + 0xbc))(p);
    ((CAN*)src)->fe30(dst);
    ((CAN*)dst)->fe30(&local);
    if (p != 0) (*(void(__thiscall**)(void*))(*(char**)p + 0xc0))(p);
}

struct AnimBindingRec_s00c0_ffc0 {   // 0x24-byte binding record
    int   m00;
    int   m04;
    int   m08;
    int   m0c;
    int   m10;
    float m14;
    char  m18;
    int   m1c;
    RefPtr_s00c0_fc40 mpObj;          // +0x20
    __forceinline AnimBindingRec_s00c0_ffc0& operator=(const AnimBindingRec_s00c0_ffc0& x)
    {
        m00 = x.m00; m04 = x.m04; m08 = x.m08; m0c = x.m0c; m10 = x.m10;
        m14 = x.m14; m18 = x.m18; m1c = x.m1c;
        mpObj = x.mpObj;
        return *this;
    }
};

// @ 0x00c0ffc0
void* __cdecl FUN_00c0ffc0(int param_1, int param_2, int* param_3)
{
    if (param_2 != param_1) {
        AnimBindingRec_s00c0_ffc0* dest = (AnimBindingRec_s00c0_ffc0*)param_3;
        do {
            param_2 -= 0x24;
            --dest;
            *dest = *(AnimBindingRec_s00c0_ffc0*)param_2;
        } while (param_2 != param_1);
        return dest;
    }
    return param_3;
}

// @ 0x00c10050
void __cdecl FUN_00c10050(uint32_t param_1, int param_2, int param_3, int param_4, char param_5)
{
    if (param_3 == 0) return;
    AnimFbcObj* a = (AnimFbcObj*)((AnimParamObj*)param_3)->sub;
    if (a == 0) return;
    Anim2c0Obj* b = (Anim2c0Obj*)a->sub;
    if (b == 0) return;
    Anim08Obj* c = (Anim08Obj*)b->sub;
    if (c == 0) return;
    void* finder = c->finder;
    CAN* ctx;
    if (finder == 0) ctx = 0;
    else ctx = (CAN*)((int (__thiscall *)(void*, int))(*(int**)finder)[0xc / 4])(finder, 0xce9f6639);

    uint32_t local_40[16];
    local_40[0] = 0; local_40[1] = 1;
    local_40[2] = 0; local_40[3] = 2;
    local_40[4] = 0; local_40[5] = 3;
    local_40[6] = 0; local_40[7] = 4;
    uint32_t uVar7 = 0;
    if (param_1 != 0xffffffff) {
        uint32_t uVar4 = param_1;
        do {
            local_40[uVar7 * 2] = uVar4 & 0xff;
            ++uVar7;
            if (uVar7 >= 4) break;
            uint32_t t = uVar4 >> 8;
            uVar4 = uVar4 >> 8;
            if ((char)t == -1) break;
        } while (1);
    }
    uint32_t uVar6 = 0;
    int* piVar3 = (int*)FUN_009ff6f0((void*)param_3, (void*)param_4);
    if (piVar3 != 0 && *piVar3 != 0) {
        int iVar5 = *(int*)(*piVar3 + 8);
        if (iVar5 != 0 && uVar7 != 0) {
            if (*(uint32_t*)(iVar5 + 0x18) < 2) {
                if (*(int*)(iVar5 + 0x14) == 2) {
                    CANCtx* cc = (CANCtx*)ctx->animCtx;
                    int remap = (int)cc->remapTable;
                    int arr = *(int*)(remap + 0x2e4);
                    AnimSlotSrc* elem = (AnimSlotSrc*)*(void**)(arr + local_40[0] * 700);
                    if (0.0f < elem->weight) uVar6 = 1;
                } else {
                    uVar6 = 0;
                }
            } else {
                void* c2 = ctx->animCtx;
                char* extra = 0;
                uint32_t rr = ((uint32_t (__thiscall *)(void*, int, uint32_t*, uint32_t, void*))
                               (*(int**)c2)[0x68 / 4])(c2, param_4, local_40, uVar7, &extra);
                if (rr < *(uint32_t*)(*(int*)(*piVar3 + 8) + 0x14)) uVar6 = rr;
            }
        }
    }
    void* c3 = ctx->animCtx;
    ((void (__thiscall *)(void*, int, uint32_t))(*(int**)c3)[0x3c / 4])(c3, param_4, uVar6);
    if (param_5 == 0 && param_2 != -1) {
        uint32_t val = (uint32_t)param_2;
        for (int i = 0; i < 4; ++i) {
            uint32_t local = 0;
            char* e = ((F_f9b0*)ctx)->f((int)(val & 0xff), &local);
            if (e != 0 && *(int*)(e + 4) != 0) {
                local_40[6] = local;
                local_40[7] = (uint32_t)param_4;
                local_40[8] = 0;
                ((AnimPlayCtx*)ctx->playCtx)->Play(5, 0, (void*)ctx, GF(0x146a32c), &local_40[6], 0);
            }
            uint32_t t = val >> 8;
            val = val >> 8;
            if ((char)t == -1) break;
        }
    }
}

// @ 0x00c10210
void __cdecl FUN_00c10210(int a1, int a2, int a3, int a4)
{
    FUN_00c10050((uint32_t)a1, a2, a3, a4, 1);
}

// @ 0x00c10230
void __cdecl FUN_00c10230(int a1, int a2, int a3, int a4)
{
    FUN_00c10050((uint32_t)a1, a2, a3, a4, 0);
}

// @ 0x00c10250
void __cdecl FUN_00c10250(int param_1, int param_2, uint32_t param_3, int param_4)
{
    CAN* self = (CAN*)param_1;
    if (*(int*)(param_4 + 0x24) != 0) {
        uint32_t u = 0xffffffff;
        char* p = (char*)self->fa70(*(uint32_t*)(param_4 + 0x24), 0);
        if (p != 0) u = *(uint32_t*)p;
        if (u != param_3 && u != 0xffffffff) param_3 = u;
    }
    char* c = *(char**)(param_1 + 0xb54);
    int iVar1 = *(int*)(c + 0x17c);
    uint32_t cnt = (uint32_t)((*(int*)(iVar1 + 0x2e8) - *(int*)(iVar1 + 0x2e4)) / 700);
    if (cnt <= param_3) param_3 = 0xffffffff;
    uint32_t u2 = 0xffffffff;
    if (*(int*)(param_4 + 0x20) != 0) {
        char* p2 = (char*)self->fa70(*(uint32_t*)(param_4 + 0x20), 0);
        if (p2 != 0 && *(uint32_t*)p2 != 0xffffffff) u2 = *(uint32_t*)p2 | 0xffffff00;
    }
    param_3 |= 0xffffff00;
    char* c2 = *(char**)(param_1 + 0xb54);
    void* vt = *(void**)c2;
    (*(void(__thiscall**)(void*, int, void*))((char*)vt + 0x48))(c2, param_2, (void*)FUN_00c10230);
    (*(void(__thiscall**)(void*, int, uint32_t, uint32_t))((char*)vt + 0x4c))(c2, param_2, param_3, u2);
}

// @ 0x00c10330
void __cdecl FUN_00c10330(int param_1, int param_2, int param_3, uint32_t param_4, int param_5, uint32_t param_6)
{
    uint32_t uVar8 = 0xffffffff;
    uint32_t local_4 = 4;
    uint32_t* pu = &local_4;
    if (param_4 < 5) pu = &param_4;
    uint32_t uVar5 = 0;
    if (*pu != 0) {
        char bVar6 = 0;
        do {
            int iVar1 = (int)(uVar5 * 4);
            char bVar2 = bVar6 & 0x1f;
            char bVar3 = bVar6 & 0x1f;
            ++uVar5;
            bVar6 = (char)(bVar6 + 8);
            uVar8 = ((uint32_t)*(uint8_t*)(param_3 + iVar1) << bVar3) | (~(0xffu << bVar2) & uVar8);
        } while (uVar5 < *pu);
    }
    uint32_t uVar7 = 0xffffffff;
    uVar5 = 0;
    if (param_6 != 0) {
        char bVar6 = 0;
        do {
            int iVar1 = (int)(uVar5 * 4);
            char bVar2 = bVar6 & 0x1f;
            char bVar3 = bVar6 & 0x1f;
            ++uVar5;
            bVar6 = (char)(bVar6 + 8);
            uVar7 = ((uint32_t)*(uint8_t*)(param_5 + iVar1) << bVar3) | (~(0xffu << bVar2) & uVar7);
        } while (uVar5 < param_6);
    }
    char* c = *(char**)(param_1 + 0xb54);
    void* vt = *(void**)c;
    (*(void(__thiscall**)(void*, int, void*))((char*)vt + 0x48))(c, param_2, (void*)FUN_00c10230);
    (*(void(__thiscall**)(void*, int, uint32_t, uint32_t))((char*)vt + 0x4c))(c, param_2, uVar8, uVar7);
}

// @ 0x00c103f0
void __cdecl FUN_00c103f0(void)
{
    void* a = FUN_00f473a0(0x20, "Simulator/cAnimationRemapping", 0, 0, 0, 0);
    G32(0x168d900) = (uint32_t)(uintptr_t)a;
    if (a != 0) {
        for (int i = 0; i < 8; ++i) *(int*)((char*)a + i * 4) = 0;
    } else {
        G32(0x168d900) = 0;
    }
    int* pm = (int*)FUN_0067de30();
    intptr_t base = (intptr_t)G32(0x168d900);
    uint32_t uVar5 = 0;
    int iVar3 = 0;
    do {
        if (G32(0x1572008 + uVar5) != 0) {
            int* piVar1 = *(int**)(base + iVar3);
            int* puVar4 = (int*)(base + iVar3);
            if (piVar1 != 0) {
                *puVar4 = 0;
                (*(void(__thiscall**)(void*))((*(void***)piVar1)[1]))((void*)piVar1);
            }
            (*(void(__thiscall**)(void*, int, int, void*))((char*)*(void**)pm + 0x2c))(
                pm, (int)G32(0x1572008 + uVar5), (int)G32(0x157200c + uVar5), puVar4);
        }
        uVar5 += 8;
        iVar3 += 4;
    } while (uVar5 < 0x38);
    intptr_t base2 = (intptr_t)G32(0x168d900);
    int* piVar1 = *(int**)(base2 + 0x1c);
    int* puVar4 = (int*)(base2 + 0x1c);
    if (piVar1 != 0) {
        *puVar4 = 0;
        (*(void(__thiscall**)(void*))((*(void***)piVar1)[1]))((void*)piVar1);
    }
    (*(void(__thiscall**)(void*, uint32_t, uint32_t, void*))((char*)*(void**)pm + 0x2c))(
        pm, 0x3bd27948u, 0x623d3400u, puVar4);
}

// @ 0x00c104d0
void FUN_00c104d0(Vector3* out, const Vector3& up, const Vector3& fwd, const Vector3& target, const Vector3& goal, float t)
{
    Vector3 u = up;
    float inv = 1.0f / sqrtf(u.LengthSq());
    Vector3 n = u * inv;
    Vector3 d = target - u;
    Vector3 dp = Reject(d, n);
    Vector3 fp = Reject(fwd, n);
    Vector3 dpN = NormalizeSafe(dp);
    float cosA = NormalizeSafe(fp).Dot(dpN);

    Vector3 side = NormalizeSafe(dp.Cross(n));
    float angle = WrapAngleMod(SignedAngle(dp, d, side));

    Vector3 surfUp = cPlanetModel::Get()->SurfaceNormal(up);
    Vector3 fpSide = NormalizeSafe(fp.Cross(n));
    float baseAngle = WrapAngleMod(SignedAngle(fp, Reject(fp, surfUp), fpSide));

    if (cosA < 0.5f) {
        float turn = WrapAngleMod(SignedAngle(fp, dpN, n));
        if (turn > 0.0f)
            turn = 1.0471976f;
        else
            turn = -1.0471976f;
        Vector3 r = RotateVector(fp, AxisAngle(n, turn));
        float w = SmoothStep((cosA + 1.0f) * 0.6666667f);
        float iw = 1.0f - w;
        dp = Vector3(r.x * w + fp.x * iw, r.y * w + fp.y * iw, r.z * w + fp.z * iw);
        dpN = NormalizeSafe(dp);
        angle = iw * baseAngle + w * angle;
    }

    float len = sqrtf(dp.LengthSq());
    if (len < 1.0f) {
        float w = SmoothStep(len);
        float iw = 1.0f - w;
        float k = iw * 3.0f;
        dp = Vector3(dpN.x * w + fp.x * k, dpN.y * w + fp.y * k, dpN.z * w + fp.z * k);
        angle = iw * baseAngle + w * angle;
    }

    Vector3 axis = NormalizeSafe(dp.Cross(n));
    Vector3 r = RotateVector(dp, AxisAngle(axis, angle));
    float f = (float)exp((double)(t * -3.0103f));
    float g = 1.0f - f;
    Vector3 p = up + r;
    out->x = goal.x * f + p.x * g;
    out->y = goal.y * f + p.y * g;
    out->z = goal.z * f + p.z * g;
}

// 0x00c11410 (byte-exact lifted version: match/slices/s00c11410/s00c11410_lifted.cpp)
void cSpatialObject_s00c1_1410::SetSpeedState(float a, float b)
{
    CreatureBase* owner = (CreatureBase*)((char*)this - 0xc0);
    owner->mStateF98 = CCB_d050(owner, a);
    if ((owner->mFlagsB58 & 0x200) || (owner->mFlagsB58 & 0x100))
        owner->mValue2A0 = 1.5f * b;
    else
        owner->mValue2A0 = 1.0f * b;
}

// @ 0x00c11480
bool CreatureBase::IsWithinSight(const Vector3_s00c1_1410& target, float angle, float range)
{
    if (range == 0.0f)
        return true;
    Vector3_s00c1_1410 delta = target - mSpatial.GetPosition();
    if (CCM_e4f0(this) * angle < range)
        return false;
    float inv =
        1.0f / sqrtf(delta.x * delta.x + delta.y * delta.y + delta.z * delta.z + 1e-8f);
    Vector3_s00c1_1410 dir = delta * inv;
    Vector3_s00c1_1410 sample;
    mSpatial.GetSampleDir(&sample);
    float cone = gF_150c8b8;
    if (mpBonus && mpBonus->mRadius >= 0.0f)
        cone = mpBonus->mRadius;
    float c = cosf(cone * 0.008726646f);
    float dot = sample.z * dir.z + sample.y * dir.y + sample.x * dir.x;
    return dot >= c;
}

// @ 0x00c115d0
bool CreatureBase::funcC0h(CreatureBase* other, float angle, float range)
{
    if (other->mbStealthed)
        return false;
    const Vector3_s00c1_1410& otherPos = other->mSpatial.GetPosition();
    float rs;
    if (gF_146a330 <= range) {
        rs = range;
    } else {
        Vector3_s00c1_1410 delta = otherPos - mSpatial.GetPosition();
        float dist = sqrtf(delta.x * delta.x + delta.y * delta.y + delta.z * delta.z);
        rs = dist - (mSpatial.GetFootprintRadius() + other->mSpatial.GetFootprintRadius());
    }
    return IsWithinSight(otherPos, angle, rs);
}

// @ 0x00c11690
void* FUN_00c11690(CreatureBase* self, void* arg1, void* obj, uint32_t id)
{
    void* ref = 0;
    cEffectsManager* mgr = EffectsManager_s00c1_1410();
    void* effect = 0;
    (void)arg1;
    if (!mgr->CreateVisualEffect(id, 0, &ref))
        return 0;
    effect = ref;

    Transform t;
    t.mFlags = 0;
    t.mVersion = 0;
    t.mOffset = gV_168d988;
    t.mScale = 1.0f;
    Matrix3Assign(&t.mRot, &gM_168d964);
    t.mOffset = self->GetSpatial().GetPosition();
    t.mFlags |= 4;
    t.mVersion++;

    if (obj) {
        CreatureBase* other = (CreatureBase*)obj;
        const Vector3_s00c1_1410& faceFrom = other->GetSpatial().GetPosition();
        const Vector3_s00c1_1410& faceTo = self->GetSpatial().GetPosition();
        Vector3_s00c1_1410 nf = faceTo - faceFrom;
        Vector3_s00c1_1410 nu = faceTo;
        float fi = 1.0f / sqrtf(nf.x * nf.x + nf.y * nf.y + nf.z * nf.z);
        nf = nf * fi;
        float ui = 1.0f / sqrtf(nu.x * nu.x + nu.y * nu.y + nu.z * nu.z);
        nu = nu * ui;
        Matrix3 rot;
        Matrix3FromFacingAndUp(&rot, &nf, &nu);
        t.mRot = rot;
    } else {
        Matrix3 rot;
        Matrix3FromQuaternion(&rot, &self->GetSpatial().GetOrientation());
        t.mRot = rot;
    }
    t.mFlags |= 2;
    t.mVersion++;
    t.mScale = self->GetSpatial().GetScale();
    t.mVersion++;

    if (effect) {
        ((cIVisualEffect*)effect)->SetTransform(t);
        ((cIVisualEffect*)effect)->Start(0);
    }
    if (ref)
        ((cRefObj*)ref)->Release();

    return (void*)1;
}

// @ 0x00c11920
void CreatureBase::OneShotOverheadEffect(uint32_t effectID)
{
    void* ref = 0;
    cEffectsManager* mgr = EffectsManager_s00c1_1410();
    if (!mgr->CreateVisualEffect(effectID, 0, &ref))
        return;
    cIVisualEffect* effect = (cIVisualEffect*)ref;

    const Vector3_s00c1_1410& pos = mSpatial.GetPosition();
    Vector3_s00c1_1410 dir = pos;
    float inv = 1.0f / sqrtf(dir.x * dir.x + dir.y * dir.y + dir.z * dir.z + 1e-8f);
    dir = dir * inv;
    float dist = mSpatial.GetLocalExtents()[5].x + gF_13ec480;
    Vector3_s00c1_1410 endPos = pos + dir * dist;

    Transform t;
    t.mFlags = 0;
    t.mVersion = 0;
    t.mOffset = endPos;
    t.mScale = 1.0f;
    Matrix3Assign(&t.mRot, &gM_168d964);
    t.mFlags |= 4;
    t.mVersion++;
    Matrix3 rot;
    Matrix3FromQuaternion(&rot, &mSpatial.GetOrientation());
    t.mRot = rot;
    t.mFlags |= 2;
    t.mVersion++;
    t.mScale = mSpatial.GetScale();
    t.mVersion++;

    effect->SetTransform(t);
    effect->Start(0);

    effect->Release();
}

// @ 0x00c11b50
bool CreatureBase::GetBodyPartPositionAndOrientation(Vector3_s00c1_1410* pos, Quaternion* orient, int partIdx, bool local)
{
    if (partIdx == -1)
        return false;
    cCreatureInstanceData* inst = mpAnimatedCreature->mpInstanceData;
    BodyPart* parts = inst->mBodyParts;
    const BodyPart& bp = parts[partIdx];
    if (local) {
        Vector3_s00c1_1410 v = *pos + bp.mPosition;
        Vector3_s00c1_1410 rotated;
        QuaternionVectorTransform(&rotated, &inst->mOrientation, &v);
        *pos = rotated + inst->mPosition;
        *orient = bp.mOrientation;
        return true;
    }
    *pos = *pos + bp.mPosition;
    Transform t;
    t.mFlags = 0;
    t.mVersion = 0;
    t.mOffset = gV_168d910;
    t.mScale = 1.0f;
    Matrix3Assign(&t.mRot, &gM_168db30);
    PreRotateY(&t, -gF_157174c);
    if (t.mFlags & 2) {
        Vector3_s00c1_1410 v = *pos;
        *pos = Vector3_s00c1_1410(t.mRot.m[0] * v.x + t.mRot.m[1] * v.y + t.mRot.m[2] * v.z,
                       t.mRot.m[3] * v.x + t.mRot.m[4] * v.y + t.mRot.m[5] * v.z,
                       t.mRot.m[6] * v.x + t.mRot.m[7] * v.y + t.mRot.m[8] * v.z);
    }
    *pos = *pos * t.mScale;
    *orient = bp.mOrientation;
    return true;
}

// @ 0x00c11f50
bool CreatureBase::CreateBodyEffect(int partIdx, void* effect, void* obj, uint32_t id)
{
    if (effect == 0 && obj == 0)
        return false;
    if (partIdx == -1)
        return false;
    cCreatureInstanceData* inst = mpAnimatedCreature->mpInstanceData;
    cCreatureEffect* rec = (cCreatureEffect*)FUN_009cb300(inst, id, 0, 0);
    if (rec == 0)
        return false;
    FUN_009caa40(rec, partIdx, 0, 0);
    BodyPart* parts = inst->mBodyParts;
    BodyPart* bp = &parts[partIdx];
    if ((bp->mUnk138 + bp->mUnk13C + bp->mUnk140) * gF_13ef74c < bp->mRestDim0)
        C_QuatHalf(&rec->mQuat, gF_157174c);
    void* src = 0;
    cEffectSource* source = (cEffectSource*)obj;
    if (source)
        src = source->Cast(0xee3f516e);
    void* old = rec->mpEffect;
    if (src != old) {
        if (src) ((cRefObj*)src)->AddRef();
        rec->mpEffect = src;
        if (old) ((cRefObj*)old)->Release();
    }
    if (source) {
        rec->mpCallback = FUN_00c111b0;
        if (FUN_00b3d310(obj))
            FUN_00b45410(FUN_00b3d310(obj));
    }
    return true;
}

// @ 0x00c12080
void DetachBodyEffect(cCreatureEffect* rec, bool release)
{
    cCreatureEffect* r = 0;
    if (rec->mpEffect) {
        cRefObj* p = (cRefObj*)rec->mpEffect;
        r = (cCreatureEffect*)p->V0C((void*)0x01186577);
    }
    if (rec->mpField90) {
        cRefObj* inner = rec->mpField90->mpField64;
        if (inner)
            r = (cCreatureEffect*)inner->V0C((void*)0x01186577);
    }
    if (r) {
        rec->mpCallback = 0;
        r->mStateFlags &= ~4u;
        r->mFlag70 = 1;
        r->mFlag71 = 0;
        if (r->mFlag75) {
            if (FUN_00b3d310(r)) {
                FUN_00b453a0(FUN_00b3d310(r));
                FUN_00b54200(r);
            }
        }
        cCreatureEffect* h = rec->mpField90;
        if (h) {
            rec->mpField90 = 0;
            if ((int)h->mRefCount <= 1)
                h->V170((int)(((unsigned)h->mRefCount) >> 31) & 1);
            else
                h->mRefCount--;
        }
        cCreatureEffect* e = (cCreatureEffect*)rec->mpEffect;
        if (e) {
            rec->mpEffect = 0;
            e->Release();
        }
    }
    if (rec->mpField8C)
        rec->mpField8C->V0C((void*)(release ? 1 : 0));
}

// @ 0x00c12190
int CreatureBase::PlayAnimation(uint32_t id, bool arg2, int arg3)
{
    int layerID = id;
    C_C5b0(this, (int)id, &layerID);
    void* layer = LayerManager()->GetLayer((uint32_t)layerID);
    if (!layer)
        return 0;

    int handle = 0;
    cAnimatedCreature* anim = mpAnimatedCreature;
    if (anim) {
        int unk = 0;
        anim->V58(layerID, 0, 0, 0, &unk);
        anim = mpAnimatedCreature;
        if (layerID == (int)id && FUN_00a04990(anim, 0))
            return 0;
        anim = mpAnimatedCreature;
        bool wasPlaying = FUN_00a04990(anim, 0);
        if (arg2)
            FUN_00a02bc0(mpAnimatedCreature);
        anim = mpAnimatedCreature;
        handle = (int)anim->V08(layerID, 0);
        anim->V0C((void*)handle, wasPlaying);
        anim->V18((void*)handle);
        anim->V40((void*)handle, id);
        anim->V3C((void*)handle, 0);
        FUN_00c10250(this, handle, arg3, layer);
        if (((char*)layer)[0x1c] != 1)
            mpMostRecentAnimHandle = (void*)handle;
    }
    return handle;
}

// @ 0x00c122c0
void CreatureBase::PlayAnimationRange(uint32_t id, float a, float b)
{
    int handle = PlayAnimation(id, true, -1);
    if (handle)
        mpAnimatedCreature->V44((void*)handle, RandomFloatRange(b, a));
}

// @ 0x00c12310
uint32_t cSPCreatureBase_s00c1_2310::InterruptAnimation(uint32_t animID, int arg2, char arg3)
{
    uint32_t length = 0;
    if (!mpAnimCreature)
        goto done;

    uint32_t layerID = animID;
    ResolveAnimation(this, animID, &layerID);
    uint32_t resolvedID = layerID;
    void* handle = AnimationManager()->GetAnimation(resolvedID);
    if (!handle)
        return 0;

    length = mpAnimCreature->GetLength(resolvedID, 0);
    mpAnimCreature->SetLength(length, 1);
    if (arg3)
        mpAnimCreature->SetPause(length, 0.0f);
    mpAnimCreature->a18(length);
    mpAnimCreature->a40(length, animID);
    mpAnimCreature->a3c(length, 0);

    FUN_00c10250(this, length, arg2, handle);
    if (*(char*)((char*)handle + 0x1c) != 1)
        mAnimLength = length;
done:
    return length;
}

// @ 0x00c12410
uint32_t cSPCreatureBase_s00c1_2310::FUN_00c12410(const uint32_t* pMask, float range, char a3, char a4, char a5, char a6, char a7)
{
    uint32_t offset;
    float    scale;
    float    bestDist;
    uint32_t bestIndex;
    bool     flags;
    float    limit;
    float    dist;
    float    zero;
    uint32_t count;
    float    bestScore;

    if (a4 == 0 && mCurrentAnim != -1)
        return 0xffffffff;

    scale = FUN_00d38a30(0, this);
    count = ((uint32_t (__thiscall*)(cSPCreatureBase_s00c1_2310*))
             ((*(void***)(void*)this)[0xb0 / 4]))(this);
    bestScore = gNegOne;
    bestIndex = 0xffffffff;
    bestDist = gFLTMax;

    if (count > 0) {
        offset = 0;
        uint32_t i = 0;
        do {
            TargetSlot* slot = (TargetSlot*)((char*)mTargetSlots + offset);
            cTarget* target = ((cTarget* (__thiscall*)(cSPCreatureBase_s00c1_2310*, uint32_t))
                               ((*(void***)(void*)this)[0xb4 / 4]))(this, i);

            if (pMask) {
                uint32_t type = (uint32_t)target->mType;
                if (type >= 0x58)
                    goto next;
                bool hit = (pMask[type >> 5] & (1u << (type & 31))) != 0;
                if (!hit)
                    goto next;
            }
            if (target->mState != 1)
                goto next;
            if (target->mFlag114)
                goto next;
            if (0.0f >= target->mMaxRange)
                goto maxRangePass;
            if (!(mMaxDistance >= target->mMaxRange))
                goto next;
        maxRangePass:
            if (a3 != 0)
                goto a3Pass;
            if (!(slot->mValue >= gOne))
                goto next;
        a3Pass:
            if (a6 != 0)
                goto a6Pass;
            if (!((target->mRadiusB + target->mRadiusA) * scale >= range))
                goto next;
        a6Pass:

            if (a5 == 0) {
                limit = gZeroPointTwo;
                limit += range;
                flags = ((mFlags >> 9) & 1) != 0;
                float reach = target->GetTimeToReach(flags);
                if (limit < reach)
                    goto next;
            }

            float score = target->mScore;
            if (score > 0.0f || target->mType == 0x20) {
                zero = 0.0f;
                dist = range - (target->mRadiusB + target->mRadiusA) * scale;
                float* pClamped = &zero;
                if (!(zero > dist))
                    pClamped = &dist;
                float clamped = *pClamped;

                if (a7 != 0) {
                    if (bestDist > clamped)
                        goto update;
                    if (!(gEpsilon > clamped - bestDist))
                        goto next;
                    if (!(score > bestScore))
                        goto next;
                } else {
                    if (!(score > bestScore))
                        goto next;
                }
            update:
                bestDist = clamped;
                bestIndex = i;
                bestScore = score;
            }

        next:
            offset += 0x10;
            i++;
        } while (i < count);
    }

    return bestIndex;
}

// @ 0x00c12640
void cCreatureBase_s00c1_2640::UpdateRangedAttacks(float deltaTime)
{
    if (!mInUseRangedAttackBits.any())
        return;
    float rangeScale = GetAttackRangeScale(0, this);
    float gravity = SP::PlanetModel()->GetGravity();
    bitset88 pending = mInUseRangedAttackBits;

    cRangedAttack* attack = &mRangedAttacks[0];
    for (uint32_t i = 0; pending.any() && i < 4; i++, attack++) {
        if (!pending.test(i))
            continue;
        uint32_t word = i >> 5;
        uint32_t clearMask = ~(1 << (i & 31));
        pending.mWord[word] &= clearMask;

        cCombatant_s00c1_2640* target = attack->mpTarget;
        cTargetCreature* creature = target ? (cTargetCreature*)target->Cast(0xce9f6639) : 0;
        cSpatialObject_s00c1_2640* targetSpatial = target ? target->ToSpatialObject() : 0;

        bool bRemove;
        switch (attack->mState) {
        case 1:
            if (creature && (creature->mbB5E || !creature->mb135)) {
                bRemove = true;
            } else {
                bRemove = false;
                BoundingBox box;
                float boxScale = 1.0f;
                Vector3_s00c1_2640 aim;
                if (targetSpatial) {
                    cGameData_s00c1_2640* gameData;
                    if (target && (gameData = target->ToGameData()) != 0 && gameData->GetNounID() == kGameDataUFO)
                        boxScale = gameData->mSpatial.GetScale();
                    box.Set(targetSpatial->GetBoundingBox());
                    // scale the box about its centre
                    Vector3_s00c1_2640 center((box.mMax.x + box.mMin.x) * 0.5f, (box.mMax.y + box.mMin.y) * 0.5f,
                                   (box.mMax.z + box.mMin.z) * 0.5f);
                    box.mMin = (box.mMin - center) * boxScale + center;
                    box.mMax = (box.mMax - center) * boxScale + center;
                    aim = (box.mMax + box.mMin) * 0.5f;
                } else {
                    cSpatialObject_s00c1_2640* self = &mSpatial;
                    const BoundingBox& extents = self->GetLocalExtents();
                    Vector3_s00c1_2640 up = normalized_safe(self->GetPosition()) * extents.mMax.z;
                    Vector3_s00c1_2640 ahead = self->GetDirection() * 10.0f;
                    aim = ahead + self->GetPosition() + up;
                }

                Vector3_s00c1_2640 delta = aim - attack->mPosition;
                float len = delta.Length() + 1e-8f;
                Vector3_s00c1_2640 dir = delta * (1.0f / len);
                cCreatureAbility_s00c1_2640* ability = GetAbility(attack->mAttackIndex);
                float step = Min(ability->mSpeed * deltaTime, len);
                attack->mDistanceTraveled += step;

                Vector3_s00c1_2640 newPos;
                if (!attack->mbHoming || !targetSpatial) {
                    // ballistic step under planet gravity
                    Vector3_s00c1_2640 up = normalized_safe(attack->mPosition);
                    float g = gravity * deltaTime;
                    attack->mVelocity.x += up.x * g;
                    attack->mVelocity.y += up.y * g;
                    attack->mVelocity.z += up.z * g;
                    newPos.x = attack->mVelocity.x * deltaTime + attack->mPosition.x;
                    newPos.y = deltaTime * attack->mVelocity.y + attack->mPosition.y;
                    newPos.z = attack->mVelocity.z * deltaTime + attack->mPosition.z;
                    attack->mbHoming = newPos.SquaredLength() < aim.SquaredLength();
                }
                if (attack->mbHoming) {
                    Vector3_s00c1_2640 from;
                    if (attack->mpTrailEffect) {
                        Transform_s00c1_2640 t;
                        from = attack->mpTrailEffect->GetTransform(t).mPos;
                    } else
                        from = attack->mPosition;
                    newPos = dir * step + from;
                }
                if (attack->mpTrailEffect) {
                    Transform_s00c1_2640 t;
                    t.SetOffset(newPos);
                    Transform_s00c1_2640 current;
                    t.SetScale(attack->mpTrailEffect->GetTransform(current).mScale);
                    t.SetRotation(Matrix3FromFacingAndUp(Vector3_Normalize(dir), Vector3_Normalize(newPos)));
                    attack->mpTrailEffect->SetTransform(t);
                }

                if (targetSpatial && newPos.x >= box.mMin.x && box.mMax.x >= newPos.x && newPos.y >= box.mMin.y &&
                    box.mMax.y >= newPos.y && newPos.z >= box.mMin.z && box.mMax.z >= newPos.z) {
                    // cylinder test around the target's up axis
                    Vector3_s00c1_2640 axis = RotateVector_s00c1_2640(kUpAxis, targetSpatial->GetOrientation());
                    const Vector3_s00c1_2640& targetPos = targetSpatial->GetPosition();
                    Vector3_s00c1_2640 rel = newPos - targetPos;
                    float along = rel.z * axis.z + rel.y * axis.y + rel.x * axis.x;
                    Vector3_s00c1_2640 perp = rel - axis * along;
                    float radius = targetSpatial->GetFootprintRadius() * boxScale;
                    if (radius * radius >= perp.SquaredLength()) {
                        attack->mState = 2;
                        if (attack->mpTrailEffect)
                            attack->mpTrailEffect->Stop(0);
                        if (EffectsManager_s00c1_2640()->CreateVisualEffect(ability->mImpactEffectID, 0,
                                                                 attack->mpHitEffect.AsPPTypeParam())) {
                            Transform_s00c1_2640 t;
                            t.SetOffsetOutOfLine(attack->mPosition);
                            Vector3_s00c1_2640 up = Vector3_Normalize(targetSpatial->GetPosition());
                            Vector3_s00c1_2640 side = Cross(dir, up);
                            t.SetRotation(Matrix3FromAxes(dir, up, side));
                            attack->mpHitEffect.mpObject->SetTransform(t);
                            attack->mpHitEffect.mpObject->Start(0);
                        }
                        if (creature && !creature->IsDead()) {
                            Vector3_s00c1_2640 impulse = dir * ability->mDamage * 1000000.0f;
                            creature->mpAnimatedCreature->mpInstanceData->HitBody(0, &impulse, 0, 0, 1.5f);
                        }
                        OnRangedAttackHit(attack->mpTarget, attack->mAttackIndex, &newPos);
                    }
                } else {
                    float reach = mSpatial.GetFootprintRadius() * 2.0f;
                    if (targetSpatial)
                        reach = targetSpatial->GetFootprintRadius() + reach;
                    if (attack->mDistanceTraveled >
                        (ability->mRushingRange + ability->mRange) * rangeScale + reach + 3.0f)
                        bRemove = true;
                }
                attack->mPosition = newPos;
            }
            break;
        case 2:
            bRemove = !attack->mpHitEffect.mpObject || !attack->mpHitEffect.mpObject->IsRunning();
            break;
        default:
            continue;
        }

        if (bRemove) {
            mInUseRangedAttackBits.mWord[word] &= clearMask;
            attack->Reset();
        }
    }
}

// 0x00c13340 (byte-exact lifted version: match/slices/s00c13340/s00c13340_lifted.cpp)
void __fastcall FUN_00c13340(DestructOwner* self, void* edx)
{
    (void)edx;
    Rec34* rec = self->mRecs;
    for (int i = 4; i != 0; --i, ++rec) {
        IEffect* p;
        p = rec->mpFirst;
        rec->mp00 = 0;
        if (p) {
            p->Stop(0);
            p = rec->mpFirst;
            if (p) {
                rec->mpFirst = 0;
                p->Release();
            }
        }
        p = rec->mpSecond;
        if (p) {
            p->Stop(0);
            p = rec->mpSecond;
            if (p) {
                rec->mpSecond = 0;
                p->Release();
            }
        }
        p = rec->mpThird;
        if (p) {
            rec->mpThird = 0;
            p->Detach();
        }
    }
    self->mC04 = 0;
    self->mC08 = 0;
    self->mC0C = 0;
}

// @ 0x00c133d0
void __fastcall FUN_00c133d0(CCreature* self, void* edx, float dt, Vector3_s00c1_3340* target, uint32_t direct)
{
    (void)edx;
    CAnim* anim = (CAnim*)self->mpAnimating;
    Vector3_s00c1_3340 offset = anim->mLocalOffset;
    CModelWorld* mw = (CModelWorld*)anim->mpModelWorld;
    ILoco* loco = (ILoco*)((char*)self + 0xc0);

    if (!(uint8_t)direct) {
        Vector3_s00c1_3340 tmp;
        FUN_0099c1a0(&tmp, &mw->mQuat, &offset);
        offset.x = mw->mPos.x + tmp.x;
        offset.y = mw->mPos.y + tmp.y;
        offset.z = mw->mPos.z + tmp.z;
    }

    if (offset.x == gZeroVec.x && offset.y == gZeroVec.y && offset.z == gZeroVec.z) {
        offset = *target;
    } else {
        Vector3_s00c1_3340 bodySpace;
        FUN_00c0d660(self, &bodySpace);
        Vector3_s00c1_3340* v = (Vector3_s00c1_3340*)FUN_00d20610(loco);
        offset.x = v->x * dt + offset.x;
        offset.y = v->y * dt + offset.y;
        offset.z = v->z * dt + offset.z;
        Vector3_s00c1_3340* u = (Vector3_s00c1_3340*)loco->Get5c(target, &offset, dt);
        Vector3_s00c1_3340 out;
        FUN_00c104d0v(&out, &bodySpace, u);
        offset = out;
    }

    if (!(uint8_t)direct) {
        Vector3_s00c1_3340 d;
        d.x = offset.x - mw->mPos.x;
        d.y = offset.y - mw->mPos.y;
        d.z = offset.z - mw->mPos.z;
        Vector3_s00c1_3340 tmp;
        FUN_0099c310(&tmp, &mw->mQuat, &d);
        offset = tmp;
    }

    FUN_00a02bf0(&offset, (char)direct);
}

// @ 0x00c135f0
void __fastcall FUN_00c135f0(CCreature* self, void* edx, int dummy)
{
    (void)edx;
    (void)dummy;
    ICombatant* target = self->mpCombatantTarget;
    if (!target)
        return;
    IGameData* gd = (IGameData*)target->ToGameData();
    if (!(gd && gd->IsDestroyed())) {
        ISpatial* so = (ISpatial*)target->ToSpatialObject();
        if (!so)
            return;
        if (so->mb76)
            return;
    }
    ((ICombatant*)self)->SetCreatureTarget(0, 0, 0);
}

// @ 0x00c13650
void __fastcall FUN_00c13650(CCreature* self, void* edx)
{
    (void)edx;
    Vector3_s00c1_3340 pos = gZeroVec;
    uint32_t fl = self->mFlagsB58 >> 9;
    uint8_t bl = self->mb137;
    ILoco* loco = (ILoco*)((char*)self + 0xc0);

    if ((fl & 1) && gFlockEnabled) {
        Vector3_s00c1_3340* v = (Vector3_s00c1_3340*)FUN_00d20610(loco);
        if (v->x * v->x + v->y * v->y + v->z * v->z == 0.0f) {
            pos.x = gFlockX * gFlockScale;
            pos.y = gFlockY * gFlockScale;
            pos.z = gFlockZ * gFlockScale;
        }
    }

    CAnimator* anim = (CAnimator*)self->mpAnimator;
    float dist = anim->mF548;

    if (!bl) {
        Vector3_s00c1_3340* v = (Vector3_s00c1_3340*)FUN_00d20610(loco);
        Vector3_s00c1_3340 dir = *(loco->Get2c());
        float inv = 1.0f / sqrtf(dir.x * dir.x + dir.y * dir.y + dir.z * dir.z + gProp3f14);
        Vector3_s00c1_3340 n(dir.x * inv, dir.y * inv, dir.z * inv);
        if (v->x * v->x + v->y * v->y + v->z * v->z > 0.0f) {
            float d = n.x * v->x + n.y * v->y + n.z * v->z;
            Vector3_s00c1_3340 proj(n.x * d, n.y * d, n.z * d);
            if (proj.x * n.x + proj.y * n.y + proj.z * n.z < 0.0f)
                dist += sqrtf(proj.x * proj.x + proj.y * proj.y + proj.z * proj.z);
        }
    }

    Vector3_s00c1_3340* f = loco->Get2c();
    float inv = 1.0f / sqrtf(f->x * f->x + f->y * f->y + f->z * f->z + gProp3f14);
    pos.x += f->x * inv * dist * gHoverMul;
    pos.y += f->y * inv * dist * gHoverMul;
    pos.z += f->z * inv * dist * gHoverMul;
    FUN_00c446d0(&pos, 0);

    if (!bl) {
        if (anim->mI698 == 0) {
            FUN_00c12310(self, 0x5485a4c, -1, 0);
            return;
        }
        FUN_00c12310(self, 0x77300ff, -1, 0);
        return;
    }

    int clip;
    if (anim->mI61c == 0) {
        clip = (anim->mI6a0 == 0) ? 0x25b3bc0 : 0x7995fdc;
    } else if (anim->mI6a0 == 0) {
        clip = (anim->mI698 == 0) ? 0x5261d56 : 0x77300f2;
    } else {
        clip = 0x7995fdc;
    }
    FUN_00c12310(self, clip, -1, 0);

    self->mAnim3 = 3;
    self->mb137 = 0;
    if ((fl & 1)) {
        Vector3_s00c1_3340* p = loco->Get2c();
        gHoverSavedX = p->x;
        gHoverSavedY = p->y;
        gHoverSavedZ = p->z;
    }
    self->mbE63 = 1;
    self->mE64 = 0;
}

// @ 0x00c13a30
uint32_t __fastcall FUN_00c13a30(CCreature* self, void* edx, uint8_t enable)
{
    (void)edx;
    if (!enable) {
        self->mFlagsB58 &= 0xffffefff;
        return 1;
    }

    CAnimator* anim = (CAnimator*)self->mpAnimator;
    if (anim->mI61c == 0 || (self->mFlags110 & 0x1000))
        return 0;

    float delta = anim->mF54C * gAirMul;
    uint8_t bl = self->mb137;
    ILoco* loco = (ILoco*)((char*)self + 0xc0);
    Vector3_s00c1_3340* ext = (Vector3_s00c1_3340*)loco->Get68();
    delta += ((float*)ext)[5] * gHalfNeg;
    if (delta == 0.0f)
        delta = anim->mF54C;
    if (!bl)
        delta = 0.0f;

    Vector3_s00c1_3340 pos = gZeroVec;
    if ((self->mFlagsB58 >> 9 & 1) && gFlockEnabled) {
        Vector3_s00c1_3340* v = (Vector3_s00c1_3340*)FUN_00d20610(loco);
        if (FUN_004885d0(v) == 0.0f) {
            pos.x = gFlockX * gFlockScale;
            pos.y = gFlockY * gFlockScale;
            pos.z = gFlockZ * gFlockScale;
        }
    }

    Vector3_s00c1_3340* g = loco->Get2c();
    Vector3_s00c1_3340 n;
    FUN_00449c20(&n, g);
    pos.x += n.x * delta;
    pos.y += n.y * delta;
    pos.z += n.z * delta;
    FUN_00c446d0(&pos, 0);

    if (bl) {
        if (anim->mI698 == 0)
            FUN_00c12310(self, 0x5261d56, -1, 0);
        else
            FUN_00c12310(self, 0x77300f2, -1, 0);
        self->mAnim3 = 3;
        self->mb137 = 0;
    }
    self->mFlagsB58 |= 0x1000;
    return 1;
}

// @ 0x00c13c60
uint8_t __fastcall FUN_00c13c60(CCreature* self, void* edx, int* target, uint8_t p3, uint8_t p4)
{
    (void)edx;
    uint8_t result = 0;
    void* gameMode = FUN_00b5b800();
    uint8_t isStrategy = (gameMode == (void*)0x01654c10);
    int count = (int)(self->mpRecsEnd - self->mpRecsBegin) / 0x24;

    if (count <= 0)
        return result;
    if (self->mB34 != 1 && !isStrategy)
        return result;
    if (!target)
        return result;
    uint32_t flags = *(uint32_t*)((char*)target + 0x50);
    if ((flags & 0x200) == 0)
        return result;
    if (!p3 && (int8_t)flags < 0)
        return result;
    if (*(uint8_t*)((char*)target + 0x70) == 0)
        return result;
    if (!p3 && (flags & 0x100) != 0)
        return result;
    if (p4) {
        CAnimator* anim = (CAnimator*)self->mpAnimator;
        if (!(anim->mF590 > gZero1485378))
            return result;
    }

    if (!isStrategy) {
        float ratio = ((ILoco*)target)->GetScalar70();
        ILoco* loco = (ILoco*)((char*)self + 0xc0);
        float denom = loco->GetScalar70() + gEps146a330;
        ratio = ratio / denom;
        void* creature = FUN_00ae66f0(target);
        float limit = gFallbackRange;
        if (creature) {
            void* strat = FUN_00d38840();
            limit = FUN_004e1c70(*(int*)((char*)strat + 0xb4), (int)0xd7e2f8aa, 0.5f);
        }
        if (ratio > limit)
            return result;
    }
    result = 1;
    return result;
}

// @ 0x00c13db0
uint8_t __fastcall FUN_00c13db0(CCreature* self, void* edx, int a, int b)
{
    (void)edx;
    int count = (int)(self->mpRecsEnd - self->mpRecsBegin) / 0x24;
    if (a >= count)
        return 0;
    if (b >= count)
        return 0;

    CitRec* begin = self->mpRecsBegin;
    CitRec* recA = &begin[a];
    CitRec* recB = &begin[b];

    IRefObj* held = recA->mpPtr;
    if (held)
        held->AddRef();

    FUN_00ad7ec0(&recA->mpPtr, &recB->mpPtr);
    FUN_00ad7ec0(&recB->mpPtr, &held);

    if (recA->mpPtr)
        FUN_00c0e000(self, recA->mpPtr, (void*)recA->mId);
    if (recB->mpPtr)
        FUN_00c0e000(self, recB->mpPtr, (void*)recB->mId);
    if (held)
        held->SubRef();
    return 1;
}

// @ 0x00c13eb0
void __fastcall FUN_00c13eb0(CCreature* self, void* edx)
{
    (void)edx;
    if (!self->mpAnimator)
        return;
    int count = (int)(self->mpRecsEnd - self->mpRecsBegin) / 0x24;
    if (count <= 0)
        return;

    CitRec* rec = self->mpRecsBegin;
    for (int i = 0; i < count; ++i, ++rec) {
        IProp* prop = (IProp*)rec->mpPtr;
        if (!prop)
            continue;

        if (prop->Get() == 0) {
            void* world = FUN_00b3d520();
            if (world)
                ((IModelWorld*)world)->Slot00();
            ((PropData*)prop)->mFlags50 |= 8;
            prop->Set(world);
            int key = (int)prop->Find(0x116dd1b);
            void* a = FUN_00b3d310(prop, key);
            FUN_00b5a260(a);
            if (world)
                ((IModelWorld*)world)->Release();
        }

        int id = rec->mId;
        if (id == -1)
            continue;
        if (!FUN_00c11f50(self, id, 0, prop, prop))
            continue;

        void* offsets = 0;
        CAnim* anim = (CAnim*)self->mpAnimating;
        if (anim) {
            offsets = FUN_009cab60(anim->mpModelWorld, prop);
        }
        CAnim* anim2 = (CAnim*)self->mpAnimating;
        void* mw2 = anim2->mpModelWorld;
        void* array = *(void**)((char*)mw2 + 0x2e4);
        void* elem = *(void**)((char*)array + id * 0x2bc);
        FUN_00c0de60(self, elem, offsets);

        IKeyed* sub = (IKeyed*)prop->Find(0x017f243b);
        if (sub) {
            void* noun = sub->Slot20(((KeyedData*)sub)->mKey28);
            void* nm = FUN_00b3d300((int)noun);
            void* hit = FUN_00b21000(nm, 0);
            if (hit && FUN_0064f350(*(int*)((char*)hit + 0xc), (int)0x670f1af, 0)) {
                float* f = (float*)offsets;
                f[6] = 0.0f;
                f[7] = gOne1485720;
                f[8] = 0.0f;
                f[9] = 0.0f;
            }
        }
        FUN_00d7d220(prop, self);
    }
}

// @ 0x00c14070
void __fastcall FUN_00c14070(CCreature* self, void* edx, uint32_t* prop)
{
    (void)edx;
    CAnim* anim = (CAnim*)self->mpAnimating;
    if (!anim || !prop)
        return;

    if (prop[7]) {
        FUN_00a01f10(anim->mpP184, 0, (int)prop[7], 0);
        prop[7] = 0;
    }

    int key = (int)prop[2];
    FUN_00c0c5b0(self, key, &key);

    uint32_t handle = (uint32_t)anim->Slot08(key, 0);
    prop[7] = handle;
    anim->Slot0c((int)handle, 2);
    anim->Slot18((int)handle);
    anim->Slot1c((int)handle, 3.0f);
    anim->Slot20((int)handle, 1);
    anim->Slot24((int)handle, -1.0f);
    anim->Slot3c((int)handle, (uint8_t)prop[6] == 0);
    anim->Slot40((int)handle, (int)prop[2]);
    uint32_t flags = *prop | 0xffffff00;
    anim->Slot48((int)handle, (void*)&FUN_00c10210);
    anim->Slot4c((int)handle, (int)flags, 0);
}

// @ 0x00c141b0
void*__cdecl FUN_00c141b0(IStream* stream, int* rec)
{
    IRefObj** slot = (IRefObj**)((char*)rec + 0x20);
    IRefObj* old = *slot;
    if (old) {
        *slot = 0;
        old->SubRef();
    }

    stream->Slot28(0x01186577, slot, 0);

    IWriterS* w;
    void* s;
    w = (IWriterS*)stream->GetWriter_20();
    s = w->GetStream_18();
    FUN_0093a780(s, rec, 1, 0);
    w = (IWriterS*)stream->GetWriter_20();
    s = w->GetStream_18();
    FUN_0093a780(s, (char*)rec + 8, 1, 0);
    w = (IWriterS*)stream->GetWriter_20();
    s = w->GetStream_18();
    FUN_0093a780(s, (char*)rec + 4, 1, 0);
    w = (IWriterS*)stream->GetWriter_20();
    s = w->GetStream_18();
    FUN_0093a780(s, (char*)rec + 0x10, 1, 0);
    w = (IWriterS*)stream->GetWriter_20();
    FUN_0093ac80(w->GetStream_18(), (char*)rec + 0x18);
    return stream;
}

// @ 0x00c14350
cContentValidationSummarizer* GetContentValidationSummarizer()
{    static cContentValidationSummarizer* sSingleton;
    if (sSingleton != 0)
        return sSingleton;
    struct Base1 {
        virtual int AddRef() { return 0; }
        uint32_t mPad;
    };
    struct Base2 {
        virtual void b2_v0() {}
        int mRefCount;
        Base2() : mRefCount(0) {}
    };
    struct Derived : Base1, Base2 {
        virtual int AddRef() { return 0; }
        virtual void b2_v0() {}
    };
    struct V0 {
        virtual void f() {}
    };
    void* mem = EAAllocate(0x10, "Simulator/LocomotionStrategy_Template", 0, 0, 0, 0);
    V0* p = mem ? (V0*)(new (mem) Derived()) : 0;
    *(cContentValidationSummarizer* volatile*)&sSingleton = (cContentValidationSummarizer*)p;
    p->f();
    return sSingleton;}

// @ 0x00c144e0
void* Pool_s00c1_4350::Alloc(uint32_t* out)
{
    PoolNode* node = mpFree;
    if (node == 0) {
        node = (PoolNode*)EAAllocate(
            mnAllocSize, "Simulator", 0, 0,
            "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
            0xd1);
    } else {
        mpFree = (PoolNode*)node->mNext;
    }
    if (node != 0) {
        node->mNext = out[0];
        node->mValue1 = out[1];
    }
    node->mValue2 = 0;
    return node;
}

// @ 0x00c14530
struct RefSlot_s00c1_4530 {
    IRefCounted_s00c1_4350* mp;
    ~RefSlot_s00c1_4530() { if (mp) mp->Release(); }
};
struct Pool_s00c1_4530 {
    RefSlot_s00c1_4530 mSlots[7];
    RefSlot_s00c1_4530 mLast;  // +0x1c
    static void operator delete(void* p) { EAFree(p); }
};
void DestroyPool()
{
    delete (Pool_s00c1_4530*)gSingleton168d900;
    gSingleton168d900 = 0;
}

// @ 0x00c14590
int CreatureBase_s00c1_4350::AnimationAction(uint32_t id, int mode)
{
    if (mode == 0)
        return PlayAnimation(id, 1, -1);
    if (mode == 1)
        return InterruptAnimation(id, -1, 0);
    if (mode == 2) {
        cAnimatedCreature_s00c1_4350* anim = mpAnimatedCreature;
        int h = (int)anim->V08(id, 0);
        anim->V0C((void*)h, 2);
        anim->V18((void*)h);
        anim->V20((void*)h, 1);
        anim->V24((void*)h, gF_13eb1bc);
        return h;
    }
    return 0;
}

// @ 0x00c14640
void CreatureBase_s00c1_4350::UpdateLocomotionAnimation()
{
    cAnimatedCreature_s00c1_4350* pi = 0;
    if (this != 0 && Cast(0x18eb4b7) != 0)
        pi = mpAnimatedCreature;

    uint32_t anim;
    if (mLocomotionStateF98 == 1)
        anim = 0x2481de6;
    else if (mLocomotionStateF98 == 3)
        anim = 0x35455a4;
    else
        anim = 0x354559b;
    if (mbB5E)
        anim = 0x35455a4;

    cAnimatedCreature_s00c1_4350* anim2 = mpAnimatedCreature;
    if (pi != 0 && FUN_00cee330((char*)pi + 0x34) != 0) {
        FUN_00a01f10((void*)anim2->mpCurrentAnim, 0);
        anim2->mpCurrentAnim = 0;
        return;
    }
    int rec = FUN_009ff6f0_s00c1_4350((void*)anim2->mpField184, (void*)anim2->mpCurrentAnim);
    if (rec != 0 && *(uint32_t*)rec != 0 && *(uint32_t*)(*(uint32_t*)rec) != 0) {
        if (*(uint32_t*)(rec + 0xd8) == anim)
            return;
        uint32_t old = anim2->mpCurrentAnim;
        uint32_t nh = (uint32_t)AnimationAction(anim, 2);
        anim2->mpCurrentAnim = nh;
        FUN_00a01f10((void*)old, 0);
        return;
    }
    cAnimatedCreature_s00c1_4350* a3 = mpAnimatedCreature;
    a3->mpCurrentAnim = (uint32_t)AnimationAction(anim, 2);
}

// @ 0x00c14750
void CreatureBase_s00c1_4350::UpdateLocomotion(int param2)
{
    if (mbB5E)                     // +0xb5e
        return;
    if (mbE38)                     // +0xe38
        return;
    cAnimatedCreature_s00c1_4350* anim = mpAnimatedCreature;
    if (anim == 0)
        return;
    if (anim->mpField184 == 0)
        return;

    if (GetCurrentGameMode_s00c1_4350() == (void*)0x1654c10 && *(uint32_t*)((char*)0x16c7aa4 + 0xcc) == 1) {
        bool dead = FUN_00c04750(InterfaceCast(this));
        if (dead && *(uint8_t*)((char*)dead + 2) != 0)
            return;
    }

    int cur = FUN_00c0e040();        // GetCurrentAnimationGUID
    int local4 = cur;
    int localC = cur;
    int local8 = -1;
    FUN_00c0c630(param2, &local4, &localC, &local8);

    int got = localC;
    if (cur == got)
        return;

    bool q = FUN_00a02b40(mpAnimatedCreature, got);
    char mode = (char)param2;
    if (!q || mode != 0) {
        AnimationAction(got, mode != 0 ? 1 : 0);
        if (local8 != -1) {
            AnimationAction(local8, mode != 0 ? 1 : 0);
            UpdateLocomotionAnimation();
            return;
        }
        cAnimatedCreature_s00c1_4350* a = mpAnimatedCreature;
        FUN_00a01f10((void*)a->mpField188, 0);
        FUN_00a01f10((void*)a->mpCurrentAnim, 0);
        a->mpCurrentAnim = 0;
    }
}

// @ 0x00c148a0
bool ReleaseEffectRef(uint32_t* self)
{
    if (self[0xf] != 0) {
        void* obj = (void*)self[0xf];
        uint32_t r = (*(uint32_t(**)(void*, uint32_t))(*(uint32_t*)obj + 0xc))(obj, 0xce9f6639);
        if (r != 0 && self != 0) {
            if (self[2] != 0) {
                uint32_t base = *(uint32_t*)(r + 0xe40);
                uint32_t idx = *self * 0x24;
                uint32_t cnt = *(uint32_t*)(base + idx + 0xc);
                uint8_t* ent = (uint8_t*)(base + idx);
                if (cnt > 0)
                    *(uint32_t*)(ent + 0xc) = cnt - 1;
                if (*(uint32_t*)(ent + 0xc) == 0 && *(uint32_t*)(ent + 8) != 0)
                    ((cEffectMgr*)base)->DecrementNode(ent);
            }
            return true;
        }
    }
    return false;
}

// @ 0x00c14910
int CreatureBase_s00c1_4350::PlayAnimationWithTarget(uint32_t id, void* target, int arg4)
{
    int h = PlayAnimation(id, 1, arg4);
    AddSetAnimationTargetModifier3(this, h, target);
    return h;
}

// 0x00c14940 (byte-exact lifted version: match/slices/s00c14940/s00c14940.cpp)
int CreatureBase_s00c1_4350::PlayAnimationWithTargetObj(uint32_t id, void* target, int arg5)
{
    int h = PlayAnimation(id, 1, arg5);
    if (target != 0) {
        void* r = (*(void*(__thiscall**)(void*, uint32_t))(*(uint32_t*)target + 0xb8))(target, 0xee3f516e);
        if (r != 0)
            AddSetAnimationTargetModifier4(this, h, r, target);
    }
    return h;
}

// 0x00c149c0 (byte-exact lifted version: match/slices/s00c149c0/s00c149c0.cpp)
int CreatureBase_s00c1_4350::InterruptAnimationWithTargetObj(uint32_t id, void* target, int arg5)
{
    int h = InterruptAnimation(id, arg5, 0);
    if (target != 0) {
        void* r = (*(void*(__thiscall**)(void*, uint32_t))(*(uint32_t*)target + 0xb8))(target, 0xee3f516e);
        if (r != 0)
            AddSetAnimationTargetModifier4(this, h, r, target);
    }
    return h;
}

// @ 0x00c14a10
void __fastcall AssignDefinitionName(void* self, void* /*edx*/, Str* out)
{
    intptr_t holder = (intptr_t)self - 0x68;
    void* a = (*(void*(**)(void*))(*(uint32_t*)holder + 0x20))((void*)holder);
    if (a == 0)
        return;
    void* b = (*(void*(**)(void*))(*(uint32_t*)holder + 0x20))((void*)holder);
    const char* s = (const char*)(*(const char*(**)(void*))(*(uint32_t*)b + 0x14))(b);
    const char* end = s;
    while (*end)
        end++;
    out->assign(s, end);
}

// @ 0x00c14a60
void* GetGlobalNameList()
{
    static void* sList[3];
    static uint32_t sInit;
    if ((sInit & 1) == 0) {
        sInit |= 1;
        sList[0] = 0;
        sList[1] = 0;
        sList[2] = 0;
        atexit(ExitHandler);
    }
    return sList;
}

// @ 0x00c14aa0
bool ReadGameData(cGameData_s00c1_4350* self, void* stream)
{
    // stream->vt[0x20]() then result->vt[0x18]() -> reader; read one int32.
    void* a = (*(void*(**)(void*))stream)(stream);
    void* reader = (*(void*(**)(void*))a)(a);
    int v0 = 0;
    ReadInt32_s00c1_4350(reader, &v0, 1, 0);

    bool ok;
    if (!FUN_00b18600(self, stream))
        ok = false;
    else if (!FUN_00cee440((char*)self + 0x34, stream))
        ok = false;
    else if (!FUN_00c43c10((char*)self + 0xc0, stream))
        ok = false;
    else if (!FUN_00bfc540((char*)self + 0x5a8, stream))
        ok = false;
    else
        ok = true;

    void* b = (*(void*(**)(void*))stream)(stream);
    void* reader2 = (*(void*(**)(void*))b)(b);
    int v1 = 0;
    ReadInt32_s00c1_4350(reader2, &v1, 1, 0);
    *(uint8_t*)((char*)self + 0xbd) = v1 != 0;

    FUN_00bc9ac0(stream);
    FUN_00c3c10Serializer((char*)self, stream);
    uint32_t ver = self->GetID();
    (void)ver;
    return ok;
}

// @ 0x00c14cb0
void CreatureBase_s00c1_4350::DoHitGround()
{
    uint32_t local10 = 0;
    cAnimatedCreature_s00c1_4350* anim = mpAnimatedCreature;
    bool matched = false;
    if (anim != 0) {
        // anim->vt[0x58](&local10, 0, 0, 0)
        (*(void(__thiscall*)(void*, uint32_t*, int, int, int))(*(uint32_t*)anim + 0x58))(anim, &local10, 0, 0, 0);
        switch (local10) {
        case 0x25b3bc0: case 0x772ff58: case 0x7995fdc:
        case 0x7982fb2: case 0x7b5063e:
            matched = true; break;
        default: break;
        }
    }
    if (!matched) {
        switch (local10) {
        case 0x5261d56: case 0x5261d78: case 0x692e5bf:
        case 0x5485a4c: case 0x77300f2: case 0x77300fb: case 0x77300ff:
            matched = true; break;
        default: break;
        }
    }
    if (matched) {
        if (mbB5E == 0) {
            cCreatureProfile* prof = mpSpeciesProfile;
            if (prof->mField61C == 0) {
                UpdateLocomotion(1);
                prof = mpSpeciesProfile;
                uint32_t a = (prof->mField6A0 == 0) ? 0x25b3bc2 : 0x773009a;
                InterruptAnimation(a, -1, 0);
            } else {
                uint32_t a = (prof->mField698 == 0) ? 0x5261d57 : 0x7730105;
                InterruptAnimation(a, -1, 0);
            }
        }
    }

    mLocomotionState = 0;

    if (((cDamageSub*)((char*)this + 0x5a8))->GetDamageState() == 2) {
        void* mgr = (void*)FUN_b3d240();
        cSpatialObject_s00c1_4350* sp = (cSpatialObject_s00c1_4350*)((char*)this + 0xc0);
        Vector3_s00c1_4350 buffer;
        Vector3_s00c1_4350* sd = sp->GetSampleDir(&buffer);
        Vector3_s00c1_4350* pos = (Vector3_s00c1_4350*)(*(void*(**)(void*))(*(uint32_t*)sd + 0x2c))(sd);
        void* mgrVt = *(void**)mgr;
        (*(void(**)(void*, uint32_t, void*))((char*)mgrVt + 0x60))(mgr, 0x1b55d9a, pos);
        FUN_00c0cff0(0);
    }
    if (mbSelfPowered == 0)
        mbSelfPowered = 1;
}

// @ 0x00c14e10
void CreatureBase_s00c1_4350::OnStartSwimming()
{
    if (mpSpeciesProfile->mField61C == 0)
        UpdateLocomotion(1);
    mLocomotionState = 3;
    if (mbSelfPowered == 0)
        mbSelfPowered = 1;
}

// The object FUN_b3d310 returns is passed as `this` to the summarizer getter at 0x00c14350
// (the getter itself never reads it).
struct SummarizerHost_s00c1_4e50 {
    cContentValidationSummarizer* GetContentValidationSummarizer();   // 0x00c14350
};

// @ 0x00c14e50
void CreatureBase_s00c1_4350::NotifySummarizer()
{
    void* c = (void*)((SummarizerHost_s00c1_4e50*)FUN_b3d310())->GetContentValidationSummarizer();
    ((cSpatialObject_s00c1_4350*)((char*)this + 0xc0))->FUN_c421b0(c);
}

// @ 0x00c14e70
void* __fastcall LookupTextStyle(void* self, void* /*edx*/, uint32_t* key)
{
    struct Hash {
        uint32_t pad0;       // +0x00
        void** mpBuckets;    // +0x04
        uint32_t mnIndex;    // +0x08
    };
    Hash* h1 = (Hash*)((uint8_t*)self + 0xcc8);
    void* it1 = 0;
    VtFind(h1, &it1, key);
    if (it1 != (void*)h1->mpBuckets[h1->mnIndex])
        return *(void**)((char*)it1 + 4);

    Hash* h2 = (Hash*)((uint8_t*)self + 0xd68);
    void* it2 = 0;
    VtFind(h2, &it2, key);
    if (it2 != (void*)h2->mpBuckets[h2->mnIndex])
        return *(void**)((char*)it2 + 4);
    return 0;
}

// @ 0x00c14ef0
int CreatureBase_s00c1_4350::WaitForAnimEventOrEnd(int event, uint32_t* out, int arg4, int arg5)
{
    *out = 0xffffffff;
    int ret;
    if (arg5 != 0) {
        ret = FUN_00c0e2c0(arg5);
    } else {
        int a = (arg4 == -1) ? 0 : arg4;
        ret = FUN_00c0e170(a);
    }
    cAnimatedCreature_s00c1_4350* anim = mpAnimatedCreature;
    uint32_t count = *(uint32_t*)((char*)anim + 0x14c);
    uint32_t i = 0;
    if (count != 0) {
        uint8_t* p = (uint8_t*)anim + 0x8c;
        while (*(int*)p != event) {
            i++;
            p += 0xc;
            if (i >= count)
                return ret;
        }
        *out = *(uint32_t*)((char*)anim + (i * 3 + 0x24) * 4);
        return 1;
    }
    return ret;
}

// @ 0x00c14f70
void* CreatureBase_s00c1_4350::CreateBodyEffectByIndex(int partIdx, uint32_t visualEffectId, uint32_t id)
{
    if (partIdx == -1)
        return 0;

    void* ref = 0;
    if (ref != 0)
        (*(void(**)(void*))(*(uint32_t*)ref + 4))(ref);

    cEffectsManager* mgr = EffectsManager_s00c1_4350();
    if (!mgr->CreateVisualEffect(id, 0, &ref)) {
        if (ref != 0)
            (*(void(**)(void*))(*(uint32_t*)ref + 4))(ref);
        return 0;
    }

    cAnimatedCreature_s00c1_4350* anim = mpAnimatedCreature;
    if (anim != 0 && FUN_00a02bd0(anim) == 0) {
        XformMsg msg;
        XformMsg_ctor(&msg);
        cSpatialObject_s00c1_4350* sp = (cSpatialObject_s00c1_4350*)((char*)this + 0xc0);
        Vector3_s00c1_4350* p = (Vector3_s00c1_4350*)&sp->GetPosition();
        msg.mOffset = *p;
        msg.mFlags |= 4;
        msg.mVersion++;
        const Quaternion_s00c1_4350* q = &sp->GetOrientation();
        Matrix3FromQuaternion(&msg.mRot, q);
        msg.mFlags |= 2;
        msg.mVersion++;
        (*(void(**)(void*, XformMsg*))(*(uint32_t*)ref + 0x18))(ref, &msg);
    }
    (*(void(**)(void*, int))(*(uint32_t*)ref + 8))(ref, 0);

    void* out = ref;
    if (ref != 0) {
        cAnimatedCreature_s00c1_4350* a2 = mpAnimatedCreature;
        cCreatureInstanceData_s00c1_4350* inst = a2->mpInstanceData;
        void* rec = FUN_009cb300(inst, id, 0, 0);
        if (rec != 0) {
            FUN_009caa40(rec, partIdx, 0, 0);
            BodyPart_s00c1_4350* bp = &inst->mBodyParts[partIdx];
            if ((bp->mUnk138 + bp->mUnk13C + bp->mUnk140) * gF_13ef74c < bp->mRestDim0)
                FUN_00c0c4b0((char*)rec + 0x18, gF_157174c);
            void* old = *(void**)((char*)rec + 0xa4);
            if (old != 0) {
                *(void**)((char*)rec + 0xa4) = 0;
                (*(void(**)(void*))(*(uint32_t*)old + 4))(old);
            }
        }
    }
    if (ref != 0)
        (*(void(**)(void*))(*(uint32_t*)ref + 4))(ref);
    return out;
}

// 0x00c15150 (byte-exact lifted version: match/slices/s00c15150/s00c15150.cpp)
bool CreatureBase_s00c1_4350::DetachBodyEffectById(void* handle, void* arg3)
{
    if (mpAnimatedCreature == 0)
        return false;
    void* rec = FUN_009cab60(handle);
    if (rec == 0)
        return false;
    DetachBodyEffect(rec, arg3 != 0);
    FUN_009cb460(rec);
    return true;
}

// @ 0x00c151b0
void CreatureBase_s00c1_4350::DetachAllBodyEffects()
{
    if (mpAnimatedCreature == 0)
        return;
    if (mpAnimatedCreature->mpInstanceData == 0)
        return;
    for (;;) {
        uint8_t* inst = (uint8_t*)mpAnimatedCreature->mpInstanceData;
        void** buckets = *(void***)(inst + 0x17a4);
        uint32_t index = *(uint32_t*)(inst + 0x17a8);
        void* cur = buckets[0];
        if (cur == 0) {
            void** p = buckets + 1;
            while (*p == 0)
                p++;
            cur = *p;
        }
        if (cur == buckets[index])
            break;
        uint8_t* inst2 = (uint8_t*)mpAnimatedCreature->mpInstanceData;
        void** b2 = *(void***)(inst2 + 0x17a4);
        void* c2 = b2[0];
        if (c2 == 0) {
            void** p = b2 + 1;
            while (*p == 0)
                p++;
            c2 = *p;
        }
        if (mpAnimatedCreature != 0) {
            void* rec = FUN_009cab60(*(void**)c2);
            if (rec != 0) {
                DetachBodyEffect(rec, true);
                FUN_009cb460(rec);
            }
        }
    }
}

// @ 0x00c15270
void CreatureBase_s00c1_4350::SetBodyEffectParam(uint32_t param)
{
    uint8_t* inst = (uint8_t*)mpAnimatedCreature->mpInstanceData;
    void** buckets = *(void***)(inst + 0x17a4);
    uint32_t index = *(uint32_t*)(inst + 0x17a8);
    void* cur = buckets[0];
    if (cur == 0) {
        void** p = buckets + 1;
        while (*p == 0)
            p++;
        cur = *p;
    }
    void* end = buckets[index];
    while (cur != end) {
        void* inner = *(void**)((char*)*(void**)((char*)cur + 4) + 0x8c);
        if (inner != 0) {
            if ((*(bool(**)(void*))(*(uint32_t*)inner + 0x10))(inner))
                (*(void(**)(void*, int, uint32_t, int))(*(uint32_t*)inner + 0x44))(inner, 5, param, 3);
        }
        cur = *(void**)((char*)cur + 8);
        while (cur == 0) {
            buckets++;
            cur = *buckets;
        }
    }
}

// @ 0x00c15310
void __thiscall cSPCreatureBase_s00c1_5310::func64h(s32 a2, float a3)
{
  (void)a2;
  // Refresh ability-recharge timers.
  u32 n = 0;
  u32* pBits = this->mRechargeBits_bf8;
  do {
    if (pBits[0] != 0) {
      SimCreature* pSim = (SimCreature*)this;
      u32 count = pSim->mpVtbl->GetAbilitiesCount();
      u32 words[3];
      words[0] = pBits[0];
      words[1] = pBits[1];
      words[2] = pBits[2];
      u32 idx = 0;
      // first: check recharging words for set bits
      for (;;) {
        if (words[idx] != 0)
          break;
        idx++;
        if (idx >= 3) goto checkDirty;
      }
      while (idx < count) {
        if (idx < 0x58) {
          u32 bit = 1u << (idx & 0x1f);
          u32 wi = idx >> 5;
          if ((words[wi] & bit) == 0) { idx++; continue; }
          cAbilityState* pStates = (cAbilityState*)this->mpAbilityStates_c28;
          u32 clearMask = ~bit;
          words[wi] &= clearMask;
          if (pStates[idx].mF_04 >= 1.0f) {
            pStates[idx].mF_04 = 1.0f;
            this->mRechargeBits_bf8[wi] &= clearMask;
          } else {
            cCreatureAbility* pAb = ((SimCreature*)this)->mpVtbl->GetAbility(idx);
            u32 delta = (u32)((1.0f / pAb->mF_9c) * (float)count);
            pStates[idx].mF_04 = (float)delta + pStates[idx].mF_04;
          }
        }
        idx++;
      }
    }
    n++;
    pBits++;
  } while (n < 3);

checkDirty:
  n = 0;
  u32* pDirty = this->mAbilityDirty_c04;
  do {
    if (pDirty[0] != 0) {
      FUN_00c12640(a3);
      return;
    }
    n++;
    pDirty++;
  } while (n < 3);
}

// @ 0x00c15470
void cSPCreatureBase_s00c1_5310::FUN_00c15470(s32 a2, RefCnt* a3, u8 a4)
{
  u32 count = ((SimCreature*)this)->mpVtbl->GetAbilitiesCount();
  if ((u32)a2 >= count)
    return;
  BodyEntry* pBase = (BodyEntry*)this->mBodyBlock_eb0;
  u32 idx = 0;
  BodyEntry* e = pBase;
  for (; idx < 4; idx++) {
    if (e->mU32_04 == 0)
      break;
    e = (BodyEntry*)((u8*)e + 0x34);
  }
  if (idx == 4) {
    FUN_00c0f490(pBase);
    this->mAbilityDirty_c04[0] |= 2;
    e = pBase;
  } else {
    this->mAbilityDirty_c04[idx >> 5] |= (1u << (idx & 0x1f));
  }
  if (pBase == 0)
    return;
  void* pAbilityRaw = ((SimCreature*)this)->mpVtbl->GetAbility(a2);
  AbilityObj* pAbility = (AbilityObj*)pAbilityRaw;
  u32 pBoneless = (u32)(SIZE_T)pAbility;
  e->mU32_04 = 1;
  e->mU32_20 = a2;
  RefCnt* pOld = e->mpTarget_28;
  if (pOld != a3) {
    if (a3 != 0)
      ((ObjVtbl*)a3)->Slot60();
    e->mpTarget_28 = a3;
    if (pOld != 0)
      ((ObjVtbl*)pOld)->Slot64();
  }
  e->mB_00 = a4;
  u8* pSpat = (u8*)&this->mSpatial;
  e->mF_24 = 0.0f;
  Vec3_s00c1_5310 box[2];
  Vec3_s00c1_5310* pb = this->mSpatial.GetBox(box);
  float midX = (pb[1].x + pb[0].x) * 0.5f;
  float midY = (pb[1].y + pb[0].y) * 0.5f;
  float midZ = (pb[1].z + pb[0].z) * 0.5f;
  if (a2 == -1) {
    e->mF_24 = -this->mSpatial.GetRadius();
  } else {
    void* pAnimWorld = this->mpAnimWorld_b54;
    u32 pArr = *(u32*)((u8*)pAnimWorld + 0x17c);
    Vec3_s00c1_5310 t;
    FUN_0099c1a0(&t, (void*)(pArr + 0x3c), (Vec3_s00c1_5310*)(*(u32*)(pArr + 0x2e4) + a2 * 700 + 0x10));
    midX = t.x + *(float*)(pArr + 0x18);
    midY = t.y + *(float*)(pArr + 0x1c);
    midZ = t.z + *(float*)(pArr + 0x20);
    FUN_00c15150_tc(this, 0, (void*)(pAbility->mpEffect_88 + (u32)(SIZE_T)e), 0);
    FUN_00c14f70(this, (u32)(SIZE_T)pAbility, pAbility->mpEffect_88,
                 pAbility->mpEffect_88 + (u32)(SIZE_T)e);
  }
  e->mF_08 = midX;
  e->mF_0c = midY;
  e->mF_10 = midZ;
  e->mB_01 = 1;
  if (a3 == 0) {
    e->mF_14 = 1.0f;
    e->mF_18 = 1.0f;
    e->mF_1c = 1.0f;
  } else {
    Vec3_s00c1_5310 b2[2];
    Vec3_s00c1_5310* pb2 = this->mSpatial.GetBox(b2);
    float c0 = (pb2[1].x + pb2[0].x) * 0.5f;
    float c1 = (pb2[1].y + pb2[0].y) * 0.5f;
    float c2 = (pb2[1].z + pb2[0].z) * 0.5f;
    Vec3_s00c1_5310 c = { c0, c1, c2 };
    FUN_00c0ca00(&c, &c, 0.0f, &e->mF_14, gF_168d910);
  }
  EffectsMgr* mgr = (EffectsMgr*)(void*)EffectsManager();
  BodyEffect* pEff = e->mpEffect_2c;
  BodyEffect** ppEff = &e->mpEffect_2c;
  if (pEff != 0) {
    *ppEff = 0;
    ((ObjVtbl*)pEff)->Slot04();
  }
  u8 ok = mgr->Slot2c(pAbility->mEffectId_8c, 0, (void**)ppEff);
  (void)pSpat; (void)pBoneless;
  if (ok != 0) {
    Vec3_s00c1_5310 fwd = { e->mF_14, e->mF_18, e->mF_1c };
    float len2 = fwd.x * fwd.x + fwd.y * fwd.y + fwd.z * fwd.z;
    float inv = 1.0f / len2;
    Vec3_s00c1_5310 norm = { fwd.x * inv, fwd.y * inv, fwd.z * inv };
    Vec3_s00c1_5310 up = { midX, midY, midZ };
    Vec3_s00c1_5310 out;
    FUN_0069b440(&out, &norm, &up);
    ((ObjVtbl*)(*ppEff))->Slot18();
    ((ObjVtbl*)(*ppEff))->Slot08();
  }
}

// @ 0x00c15920
float cSPCreatureBase_s00c1_5310::FUN_00c15920()
{
  s32 saved = (s32)(u32)(this->mpRefA_4cc);
  s32 cur = FUN_00c06000_tc(FUN_00b3d310());
  if (saved != cur)
    return gF_146a32c;
  bool bBit = ((this->mFlags_ee4 >> 5) & 1) != 0;
  if (bBit)
    return gF_146a32c;
  return this->mF_1e4 * gF_1582e6c + gF_169e280;
}

// @ 0x00c15970
float cSPCreatureBase_s00c1_5310::FUN_00c15970()
{
  s32 saved = (s32)(u32)(this->mpRefA_4cc);
  s32 cur = FUN_00c06000_tc(FUN_00b3d310());
  if (saved != cur)
    return gF_146a32c;
  bool bBit = ((this->mFlags_ee4 >> 5) & 1) != 0;
  if (bBit)
    return gF_146a32c;
  return this->mF_1e4 * gF_1582e70 + gF_169e284;
}

// @ 0x00c159c0
u8 cSPCreatureBase_s00c1_5310::FUN_00c159c0(u32 a2, u32 a3, u8 a4)
{
  u8 cVar1 = 0;
  if ((u32)((this->mNeighborEnd_e44 - this->mNeighborBegin_e40) / 0x24) <= a3)
    return 0;
  tEntry* pEntry = (tEntry*)(this->mNeighborBegin_e40 + a3 * 0x24);
  RefCnt* pObj = pEntry->mpObj_20;
  if (pObj != 0) {
    if (a4 == 0) {
      // fall through to the assign label
    } else {
      u32 r = FUN_00c0f620_();
      FUN_00c13db0(a3, (void*)r);
    }
  }
  {
    u8 doAssign = (pObj == 0) ? 1 : (a4 == 0);
    if (doAssign) {
      FUN_00c70110((void*)a2);
      cVar1 = 1;
    }
  }
  {
    tEntry* pe = (tEntry*)(this->mNeighborBegin_e40 + a3 * 0x24);
    u32 v = pe->mId_00;
    if (v == 0xffffffff)
      return cVar1;
    if (cVar1 != 0) {
      cVar1 = (u8)FUN_00c11f50(this, v, 0, a2, a2);
      if (cVar1 != 0) {
        u32 pGrasp = FUN_00c0dfb0_();
        void* pAnimWorld = this->mpAnimWorld_b54;
        u32* pArr = *(u32**)((u8*)pAnimWorld + 0x17c);
        u32 item = *(u32*)(*(u32*)((u8*)pArr + 0x2e4) + v * 700);
        FUN_00c0de60(this, item, pGrasp);
        return 1;
      }
    }
    return 0;
  }
}

// @ 0x00c15bd0
void* cSPCreatureBase_s00c1_5310::FUN_00c15bd0(u32 a2, u8 a3, u32 a4)
{
  (void)a4;
  RefCnt* pSaved = 0;
  u32 n = neighborCount(this);
  if (a2 < n) {
    tEntry* p = (tEntry*)(this->mNeighborBegin_e40 + a2 * 0x24);
    RefCnt* pObj = p->mpObj_20;
    if (pObj != 0) {
      ((ObjVtbl*)pObj)->SlotBc();          // 0xbc
      pSaved = pObj;
    }
    FUN_00c0fae0(p);
    if (pSaved != 0) {
      u8 r = FUN_00c15150_tc(this, 0, pSaved, 1);
      if (r == 0) {
        ((u32*)pSaved)[0x14] &= 0xfffffffb;      // +0x50
        ((u8*)pSaved)[0x70] = 1;
        ((u8*)pSaved)[0x71] = 0;
        if (((u8*)pSaved)[0x75] != 0) {
          void* q = FUN_00b3d310();
          if (q != 0) {
            FUN_00b3d310();
            FUN_00b453a0(q);
            FUN_00b54200(pSaved);
          }
        }
      }
      FUN_00d7d2c0(pSaved, this);
    }
  }
  if (a3 != 0) {
    u32 i = a2 + 1;
    if (i < neighborCount(this)) {
      u32 off = i * 0x24;
      do {
        if (i < neighborCount(this)) {
          tEntry* p = (tEntry*)(this->mNeighborBegin_e40 + off);
          if (p->mpObj_20 != 0 || p->mType_04 != 0) {
            FUN_00c13db0(a2, (void*)i);
            break;
          }
        }
        i++;
        off += 0x24;
      } while (i < neighborCount(this));
    }
  }
  if (pSaved != 0)
    ((ObjVtbl*)pSaved)->SlotC0();          // 0xc0
  return pSaved;
}

// @ 0x00c15d50
u8 cSPCreatureBase_s00c1_5310::FUN_00c15d50(u32 a2, u32 a3, u32 a4)
{
  u32 n = neighborCount(this);
  if (n == 0)
    return 0;
  tEntry* p = (tEntry*)(this->mNeighborBegin_e40 + 0x20);
  for (u32 i = 0; i < n; i++) {
    if (p->mpObj_20 == (RefCnt*)a2)
      return this->FUN_00c15bd0(i, (u8)a3, a4) != 0;
    p = (tEntry*)((u8*)p + 0x24);
  }
  return 0;
}

// @ 0x00c15dc0
void cSPCreatureBase_s00c1_5310::FUN_00c15dc0(float a2)
{
  float cur = this->mWaveF_e58;
  float dec = a2;
  if (cur < dec)
    dec = cur;
  this->mWaveF_e58 = cur - dec;
  if (((this->mFlags_b58 >> 9) & 1) != 0) {
    u8 msg[0x40];
    *(u32*)(msg + 0x30) = 0x7c7a52e;
    *(u32*)(msg + 0x00) = 0x13eb90c;
    u32 zero = 0;
    *(volatile u32*)(msg + 0x04) = zero;
    *(u32*)(msg + 0x00) = 0x13eb844;
    *(u32*)(msg + 0x38) = 0;
    *(float*)(msg + 0x08) = dec;
    SlotMessageVtbl* vt = (SlotMessageVtbl*)MessageServer_s00c1_5310();
    if (vt != 0) {
      vt->Dispatch(msg, 0, 0);
      SlotMessage_Destruct(msg);
    }
  }
}

// @ 0x00c15e50
void* __cdecl FUN_00c15e50_impl(void* a1, SerRecord* a2)
{
  u32 u = 0;
  if (*(void**)((u8*)a2 + 0x20) != 0)
    u = (u32)(SIZE_T)((ObjVtbl*)*(void**)((u8*)a2 + 0x20))->SlotB8(0x179c807);
  IOStream* s = (IOStream*)a1;
  s->mpVtbl->Slot2c(u);
  void* p;
  p = s->mpVtbl->Slot20();
  u32 v = a2->mU32_00;
  ((ObjVtbl*)p)->Slot18();  // stream writer slot
  EA_IO_WriteUint32(p, &v, 1, 0);
  p = s->mpVtbl->Slot20();
  v = a2->mU32_08;
  EA_IO_WriteUint32(p, &v, 1, 0);
  p = s->mpVtbl->Slot20();
  v = a2->mU32_04;
  EA_IO_WriteUint32(p, &v, 1, 0);
  p = s->mpVtbl->Slot20();
  v = a2->mU32_10;
  EA_IO_WriteUint32(p, &v, 1, 0);
  p = s->mpVtbl->Slot20();
  u32 b = (a2->mbFlag18 != 0) ? 1 : 0;
  EA_StreamWrite(p, (s32)&b, 1);
  return (void*)a1;
}

// @ 0x00c15f60
void __cdecl FUN_00c15f60_impl(IOStream* a1, void* a2)
{
  SerRecord* pBegin = (SerRecord*)(*(void**)a2);
  SerRecord* pEnd   = (SerRecord*)(*((void**)a2 + 1));
  u32 count = (u32)(((u8*)pEnd - (u8*)pBegin) / 0x24);
  void* p = a1->mpVtbl->Slot20();
  ((ObjVtbl*)p)->Slot18();
  EA_IO_WriteUint32(p, &count, 1, 0);
  for (SerRecord* it = pBegin; it != pEnd; it = (SerRecord*)((u8*)it + 0x24))
    FUN_00c15e50_impl(a1, it);
  a1->mpVtbl->Slot1c();
}

// @ 0x00c16090
u32* __cdecl FUN_00c16090(u32* a1, u32* a2, u32* a3)
{
  while (a2 != a1) {
    a2--;
    a3--;
    *a3 = *a2;
  }
  return a3;
}

// @ 0x00c160c0
u8 __cdecl FUN_00c160c0(void* a1)
{
  void** ppSlot = (void**)((u8*)a1 + 0x3c);
  if (*ppSlot == 0)
    return 0;
  void* p = ((ObjVtbl*)*ppSlot)->Slot0c(0xce9f6639);
  if (p == 0)
    return 0;
  if (a1 == 0)
    return 0;
  u8* pBase = (u8*)*(u32*)0x15716d0 + (u32)a1;
  return FUN_00c15150_tc(p, 0, pBase, 1);
}

// @ 0x00c16100
u8 __cdecl FUN_00c16100_impl(void* a1)
{
  void** ppBase = (void**)a1;
  void** ppSlot = (void**)((u8*)a1 + 0x3c);
  if (*ppSlot == 0)
    return 0;
  void* p = ((ObjVtbl*)*ppSlot)->Slot0c(0xce9f6639);
  if (p == 0)
    return 0;
  ObjVtbl* po = (ObjVtbl*)p;
  if (po->Slot2c() != 0)                       // returns bool (char)
    return 0;
  if (((u8*)p)[0x135] == 0)
    return 0;
  s32 i = (s32)(SIZE_T)*ppBase;
  s32 end = (s32)(SIZE_T)ppBase[1] + i;
  u8 acc = 0;
  for (; i < end; i++) {
    void* pAnimWorld = *((void**)((u8*)p + 0xb54));
    if (pAnimWorld == 0)
      continue;
    void* pPart = (void*)FUN_009cab60(*((u32*)((u8*)pAnimWorld + 0x17c)), i);
    if (pPart == 0)
      continue;
    u8 b = 0;
    u32* p90 = *(u32**)((u8*)pPart + 0x90);
    if (p90 != 0)
      b = (u8)((p90[1] >> 0xf) & 1);
    if (*(u32*)((u8*)pPart + 0xa4) != 0) {
      u32* q = *(u32**)((u8*)pPart + 0xa4);
      if (q != 0) {
        void* r = ((ObjVtbl*)q)->Slot0c(0x1186577);
        if (r != 0)
          b |= *(u8*)((u8*)r + 0x75);
      }
    }
    acc |= b;
    if (b == 0)
      FUN_00c15150_tc(p, 0, (void*)i, 1);
  }
  return acc;
}

// @ 0x00c161f0
float __cdecl FUN_00c161f0_impl(cSPCreatureBase_s00c1_5310* self, float a2)
{
  void* gm = cSPGetCurrentGameMode(1);
  void* mgr = FUN_00b3d320(gm);
  PropsMgrVtbl* pm = (PropsMgrVtbl*)FUN_00b1daf0(mgr);

  float f1 = 0.5f;   // local to [esp+4]
  float f2 = 0.5f;   // local to [esp+8]
  float f3 = 0.5f;   // third prop

  if (pm != 0) {
    Property* prop = 0;
    if (pm->GetProperty(0x7422b3b, &prop) && prop->mType_12 == 0xd)
      f1 = *FUN_0041ea70(prop);
    Property* prop2 = 0;
    if (pm->GetProperty(0x7422b41, &prop2) && prop2->mType_12 == 0xd)
      f2 = *FUN_0041ea70(prop2);
    Property* prop3 = 0;
    if (pm->GetProperty(0x7422b47, &prop3) && prop3->mType_12 == 0xd)
      f3 = *FUN_0041ea70(prop3);
  }

  float local_10 = 100.0f;
  float v = f3 * a2;                    // xmm0
  float prod = v * f2 * f1;             // xmm4
  if (prod > self->mWaveF_e58)
    f1 = ((1.0f / f1) / f2) * self->mWaveF_e58;
  float clamp = f1;                     // xmm0 holds the clamp here
  float waveArg = clamp * f2 * f1;
  (void)local_10;
  self->FUN_00c15dc0(waveArg);
  return a2 - f1;
}

// @ 0x00c16340
double FUN_00c16340(float param_1, TerrainObj* param_2)
{
    GameModeObj* p = FUN_00b3d320_s00c1_6340()->Fn1(FUN_00b5b800_s00c1_6340(), 1);
    float f = 100.0f;
    if (p != 0) {
        PropObj* out;
        if (p->vf9(0x7422b3b, (void**)&out) && *(int16_t*)((char*)out + 0x12) == 0xd) {
            f = *out->GetFloat();
        }
    }
    float v = param_1;
    if (f * param_1 > param_2->f_e58) {
        v = param_2->f_e58 / f;
    }
    param_2->ApplyWave(v * f);
    return (double)param_1 - (double)v;
}

// @ 0x00c17350
bool __fastcall TextStyleRemove(cTextStyleManager* self, int, uint32_t key, void* arg)
{
    cListIterator it;
    self->mLookup.Find(&it, &key);
    if (it.mpNode != self->mLookup.mpBuckets[self->mLookup.mBucketIndex]) {
        ((cStyleValue*)it.mpNode->mpValue)->v0c(arg);
        self->mLookup.Erase(&it, it);
        return true;
    }

    self->mSecondary.Find(&it, &key);
    if (it.mpNode != self->mSecondary.mpBuckets[self->mSecondary.mBucketIndex]) {
        ((cStyleValue*)it.mpNode->mpValue)->v0c(arg);
        self->mSecondary.Erase(&it, it);
        return true;
    }
    return false;
}

// @ 0x00c17420
uint32_t QueryCreatureBodyParts(cSPCreatureBase_s00c1_7350* self, int32_t kind, uint32_t* out, uint32_t max)
{
    if (self == 0) {
        return 0;
    }
    cCreatureBody* body = self->mBody;
    if (body == 0) {
        return 0;
    }
    cBodyAnim* anim = body->mAnim;
    if (anim == 0) {
        return 0;
    }

    int32_t k = kind;
    if (k >= 0x10) {
        k = 0;
    }

    if (k == 2) {
        cUIntVector* v = self->mCreature->GetPartsA(body);
        uint32_t count = (uint32_t)(v->mpEnd - v->mpBegin);
        uint32_t n = (count < max) ? count : max;
        uint32_t* src = self->mCreature->GetPartsA(body)->mpBegin;
        uint32_t* src2 = self->mCreature->GetPartsA(body)->mpBegin;
        memcpy(out, src2, (size_t)((char*)src2 + n * 4 - (char*)src));
        return n;
    }

    if (k == 0xb) {
        cUIntVector* v = self->mCreature->GetPartsB(body);
        uint32_t count = (uint32_t)(v->mpEnd - v->mpBegin);
        uint32_t n = (count < max) ? count : max;
        uint32_t* src = self->mCreature->GetPartsB(body)->mpBegin;
        uint32_t* src2 = self->mCreature->GetPartsB(body)->mpBegin;
        memcpy(out, src2, (size_t)((char*)src2 + n * 4 - (char*)src));
        return n;
    }

    cBodyPartQuery query;
    query.mRootOnly = (k == 0);
    query.mName = gBodyPartNames[k];
    query.mPad08 = 0;
    query.mPad0c = 0;
    return FUN_009b2340(out, max, (uint32_t)(uintptr_t)anim->mpAnimSet, &query, 0, 0);
}

// @ 0x00c17580
uint32_t cSPCreatureBase_s00c1_7350::GetBodyPartIndex(uint32_t kind, uint32_t index)
{
    uint32_t result = 0xffffffff;
    uint32_t parts[255];
    uint32_t count = QueryCreatureBodyParts(this, kind, parts, 255);
    if (index < count) {
        result = parts[index];
    }
    return result;
}

// @ 0x00c175d0
bool cSPCreatureBase_s00c1_7350::CanReachPointWithBodyPart(cSPTransform_s00c1_7350* transform, const float* point, uint32_t kind, int32_t part, float* outPos, uint8_t* outHit, float radiusAdd)
{
    uint32_t parts[255];
    int32_t count = (int32_t)QueryCreatureBodyParts(this, (int32_t)kind, parts, 255);
    if (count <= 0 || part > count) {
        if (outHit != 0) {
            *outHit = 0;
        }
        return false;
    }

    cVector3 local;
    local.x = point[0];
    local.y = point[1];
    local.z = point[2];
    transform->BackTransformPoint(&local);

    int32_t start = 0;
    int32_t end = count;
    if (part >= 0) {
        start = part;
        end = part + 1;
    }

    for (int32_t i = start; i < end; ++i) {
        uint32_t partId = parts[i];
        cBodyAnim* anim = mBody->mAnim;
        cAnimPartSet* set = anim->mpAnimSet;
        cAnimPartInstance* partData = &set->mpParts[partId];
        cVector3 origin;
        anim->GetWorkspaceOrigin(&origin.x, (int)partId);
        float radius = anim->mScale * partData->mRadius;
        float dx = origin.x - local.x;
        float dy = origin.y - local.y;
        float dz = origin.z - local.z;
        if (radius * radius + radiusAdd > dz * dz + dy * dy + dx * dx) {
            float vx = origin.x;
            float vy = origin.y;
            float vz = origin.z;
            if (transform->mFlags & 2) {
                float nx = transform->mRot.m[6] * vz + transform->mRot.m[3] * vy
                         + transform->mRot.m[0] * vx;
                float ny = transform->mRot.m[7] * vz + transform->mRot.m[4] * vy
                         + transform->mRot.m[1] * vx;
                float nz = transform->mRot.m[8] * vz + transform->mRot.m[5] * vy
                         + transform->mRot.m[2] * vx;
                vx = nx;
                vy = ny;
                vz = nz;
            }
            if (outPos != 0 && outHit != 0) {
                outPos[0] = transform->mOffset.x + vx * transform->mScale;
                outPos[1] = transform->mOffset.y + vy * transform->mScale;
                outPos[2] = transform->mOffset.z + vz * transform->mScale;
                *outHit = 1;
            }
            return true;
        }
    }

    if (outPos != 0 && outHit != 0) {
        uint32_t partId = parts[(part < 0) ? 0 : part];
        cBodyAnim* anim = mBody->mAnim;
        cAnimPartSet* set = anim->mpAnimSet;
        cAnimPartInstance* partData = &set->mpParts[partId];
        cVector3 origin;
        anim->GetWorkspaceOrigin(&origin.x, (int)partId);
        float radius = anim->mScale * partData->mRadius;
        float dx = origin.x - local.x;
        float dy = origin.y - local.y;
        float dz = origin.z - local.z;
        float len = (float)(1.0 / sqrt((double)dz * dz + (double)dy * dy
                                       + (double)dx * dx + (double)kEps));
        float vx = local.x + (len * dx) * radius;
        float vy = local.y + (len * dy) * radius;
        float vz = local.z + (len * dz) * radius;
        if (transform->mFlags & 2) {
            float nx = transform->mRot.m[6] * vz + transform->mRot.m[3] * vy
                     + transform->mRot.m[0] * vx;
            float ny = transform->mRot.m[1] * vx + transform->mRot.m[7] * vz
                     + transform->mRot.m[4] * vy;
            float nz = transform->mRot.m[2] * vx + transform->mRot.m[8] * vz
                     + transform->mRot.m[5] * vy;
            vx = nx;
            vy = ny;
            vz = nz;
        }
        outPos[0] = transform->mOffset.x + vx * transform->mScale;
        outPos[1] = transform->mOffset.y + vy * transform->mScale;
        outPos[2] = transform->mOffset.z + vz * transform->mScale;
        *outHit = 1;
    }
    return false;
}

extern const float kOne;                   // 0x01485720
extern const cVector3 gZeroVector;         // 0x0168d910
extern const cMatrix3 gIdentityMatrix;     // 0x0168db30

// @ 0x00c17a30
bool cSPCreatureBase_s00c1_7350::GetBodyPartPosition(float* outPos, uint32_t kind, bool world, int32_t part)
{
    uint32_t parts[255];
    cVector3 local;
    cSPTransform_s00c1_7350 xf;

    if (part < 0) {
        part = 0;
    }

    uint32_t count = QueryCreatureBodyParts(this, (int32_t)kind, parts, 255);
    if ((uint32_t)part >= count) {
        return false;
    }

    int32_t partIndex = (int32_t)parts[part];
    if (partIndex == -1) {
        return false;
    }

    cBodyAnim* anim = mBody->mAnim;
    if (world) {
        cBodyPart* bp = anim->mpBodyParts + partIndex;
        FUN_0099c1a0((void*)&local.x, (const void*)anim->mOrientation, (const void*)bp->mPosition);
        outPos[0] = local.x + anim->mPosX;
        outPos[1] = local.y + anim->mPosY;
        outPos[2] = local.z + anim->mPosZ;
        return true;
    }

    cBodyPart* bp = anim->mpBodyParts + partIndex;
    outPos[0] = bp->mPosition[0];
    outPos[1] = bp->mPosition[1];
    outPos[2] = bp->mPosition[2];

    xf.mFlags = 0;
    xf.mVersion = 0;
    xf.mOffset = gZeroVector;
    xf.mScale = kOne;
    xf.mRot.Assign(&gIdentityMatrix);
    xf.PreRotateY(-kPi);

    if (xf.mFlags & 2) {
        float x = outPos[0];
        float y = outPos[1];
        float z = outPos[2];
        outPos[0] = xf.mRot.m[0] * x + xf.mRot.m[3] * y + xf.mRot.m[6] * z;
        outPos[1] = xf.mRot.m[1] * x + xf.mRot.m[4] * y + xf.mRot.m[7] * z;
        outPos[2] = xf.mRot.m[2] * x + xf.mRot.m[5] * y + xf.mRot.m[8] * z;
    }
    outPos[0] *= xf.mScale;
    outPos[1] *= xf.mScale;
    outPos[2] *= xf.mScale;
    return true;
}

// @ 0x00c17c80
uint32_t cSPCreatureBase_s00c1_7350::CreateBodyEffect(uint32_t kind, uint32_t a, uint32_t b)
{
    uint32_t part;
    if (QueryCreatureBodyParts(this, kind, &part, 1) != 0) {
        return MakeBodyEffect(part, a, b);
    }
    return 0;
}

// @ 0x00c17cc0
uint32_t cSPCreatureBase_s00c1_7350::CreateBodyEffectChecked(bool flag, uint32_t kind, uint32_t a, uint32_t e, uint32_t b)
{
    if (flag != 0) {
        if (mBody != 0) {
            cEffectEntry* found = mBody->mAnim->FindEffect(e);
            if (found != 0) {
                cEffectSlot* eff = found->mEffect;
                if (eff != 0 && eff->IsActive()) {
                    return 0;
                }
            }
        }
        BodyEffectNotify(e, 1);
        uint32_t part;
        if (QueryCreatureBodyParts(this, kind, &part, 1) != 0) {
            return MakeBodyEffect(part, a, e);
        }
        return 0;
    }
    BodyEffectNotify(e, b);
    return 0;
}

// @ 0x00c17d60
uint32_t cSPCreatureBase_s00c1_7350::CreateBodyEffectChecked2(bool flag, uint32_t kind, uint32_t a, uint32_t e, uint32_t b)
{
    if (flag != 0) {
        if (mBody != 0) {
            cEffectEntry* found = mBody->mAnim->FindEffect(e);
            if (found != 0) {
                cEffectSlot* eff = found->mEffect;
                if (eff != 0 && eff->IsActive()) {
                    return 0;
                }
            }
        }
        BodyEffectNotify(e, 1);
        return MakeBodyEffect(kind, a, e);
    }
    BodyEffectNotify(e, b);
    return 0;
}

// @ 0x00c17de0
void __declspec(noinline) cSPCreatureBase_s00c1_7de0::LookAtUpdate(float fBlend)
{
    cVector3_s00c1_7de0 vTarget;
    cVector3_s00c1_7de0 vScale;
    cVector3_s00c1_7de0 vPos;
    cVector3_s00c1_7de0 vForward;

    if (!mpAnimTarget)
        return;
    if (!mLocomotion.IsOrientationLocked())
        return;
    if (mLookAtState != 2)
        return;

    vTarget = SP::kNoDirection;

    if (mbLookAtEnabled)
    {
        if (mpNounManager)
        {
            cSPCreatureBase_s00c1_7de0* pFound = mpNounManager->FindCreature(0xce9f6639);
            if (pFound)
            {
                if (pFound->mpAnimTarget)
                {
                    if (pFound->mbHasPartFlag)
                        SetLookAt(pFound, pFound->mpAnimTarget->GetBodyPartIndex(1, 0));
                    else
                        SetLookAt(pFound, pFound->mpAnimTarget->GetBodyPartIndex(2, 0));
                    goto UpdateState;
                }
            }
        }
    }

    if (mLocomotion.IsFacingValid())
    {
        if ((mFlags & 0x200) != 0)
        {
            if (gUseGroundMotion)
            {
                cVector3_s00c1_7de0* pForward = mLocomotion.GetForward();
                vScale.x = pForward->x * kLookAtScale;
                vScale.y = pForward->y * kLookAtScale;
                vScale.z = pForward->z * kLookAtScale;
                cVector3_s00c1_7de0* pPosition = mLocomotion.GetPosition();
                vPos.x = pPosition->x + vScale.x;
                vPos.y = pPosition->y + vScale.y;
                vPos.z = pPosition->z + vScale.z;
                cPlanetModel_s00c1_7de0* pModel = PlanetModel_s00c1_7de0();
                vTarget = *pModel->DirectionToSurfacePosition(&vPos, &vForward);
            }
            else
            {
                cPlanetModel_s00c1_7de0* pModel = (cPlanetModel_s00c1_7de0*)FUN_00b3d240_s00c1_7de0();
                cVector3_s00c1_7de0 vOffset = SP::kNoDirection;
                vTarget = *pModel->GetSurfaceOffset(&vPos, 1, vOffset);
            }

            if (Vector3Equal(&vTarget, &SP::kNoDirection))
            {
                cVector3_s00c1_7de0* pForward = mLocomotion.GetForward();
                vScale.x = pForward->x * kLookAtScale;
                vScale.y = pForward->y * kLookAtScale;
                vScale.z = pForward->z * kLookAtScale;
                cVector3_s00c1_7de0* pPosition = mLocomotion.GetPosition();
                vPos.x = pPosition->x + vScale.x;
                vPos.y = pPosition->y + vScale.y;
                vPos.z = pPosition->z + vScale.z;
                cPlanetModel_s00c1_7de0* pModel = PlanetModel_s00c1_7de0();
                vTarget = *pModel->DirectionToSurfacePosition(&vPos, &vForward);
            }
        }
        else if (mLocomotion.IsOrientationLocked())
        {
            cAnimData* pData = mLocomotion.GetAnimData();
            if (pData->mpTarget)
            {
                vTarget = pData->mOffset;
            }
            else
            {
                cVector3_s00c1_7de0* pForward = mLocomotion.GetForward();
                vScale.x = pForward->x * kLookAtScale;
                vScale.y = pForward->y * kLookAtScale;
                vScale.z = pForward->z * kLookAtScale;
                cVector3_s00c1_7de0* pPosition = mLocomotion.GetPosition();
                vPos.x = pPosition->x + vScale.x;
                vPos.y = pPosition->y + vScale.y;
                vPos.z = pPosition->z + vScale.z;
                cPlanetModel_s00c1_7de0* pModel = PlanetModel_s00c1_7de0();
                vTarget = *pModel->DirectionToSurfacePosition(&vPos, &vForward);
            }
        }
    }
    else
    {
        ClearLookAt();

        if (FUN_00ac80d0(this, 0x18eb45e))
        {
            cAnimData* pData = mpAnimPlayer->Play(0x4000000, 0);
            if (pData)
            {
                cSPCreatureBase_s00c1_7de0* pCreature = (cSPCreatureBase_s00c1_7de0*)WatchMemoryBlock(pData);
                if (pCreature)
                {
                    if (pCreature->mpAnimTarget)
                        pCreature->mpAnimTarget->GetBodyPartPosition(&vTarget, 2, 1, -1);
                }
            }
        }
    }

UpdateState:
    switch (mpAnimTarget->mState)
    {
    case 0:
        {
            cPose* pSource = mpAnimTarget->mpPose;
            if (pSource && pSource->mpParent && mpAnimTarget->mSubState == 2)
            {
                cPose* pPose = pSource->mpParent;
                cVector3_s00c1_7de0 vLocal;
                cVector3_s00c1_7de0* pRotated = (cVector3_s00c1_7de0*)checkerlib::QuaternionVectorTransform(
                    (float*)&vLocal, (float*)&pPose->mRotation,
                    (float*)&pPose->mpBones[mpAnimTarget->mBoneIndex].mLocalPosition);
                mpAnimTarget->mLookAtPoint.x = pRotated->x + pPose->mPosition.x;
                mpAnimTarget->mLookAtPoint.y = pRotated->y + pPose->mPosition.y;
                mpAnimTarget->mLookAtPoint.z = pRotated->z + pPose->mPosition.z;
            }
        }
        break;
    case 1:
        if (Vector3_NotEqual(&vTarget, &SP::kNoDirection))
            LookAtTo(fBlend, vTarget, 0);
        break;
    case 2:
        if (!mbLookAtEnabled)
        {
            uint32_t nGUID = GetCurrentAnimationGUID();
            cAnimData* pData = mLocomotion.GetAnimData();
            if (mpAnimTarget->IsOrientIdleAnim(nGUID) && pData->mpTarget)
            {
                SetAnimData(pData);
                return;
            }
            if (!Vector3_NotEqual(&vTarget, &SP::kNoDirection))
            {
                ClearLookAt();
                return;
            }
            LookAtTo(fBlend, vTarget, 1);
        }
        break;
    }
}

// @ 0x00c18370
void __declspec(noinline) cSPCreatureBase_s00c1_7de0::UpdateNetDirection()
{
    cVector3_s00c1_7de0 vDir;
    cVector3_s00c1_7de0 vVel;

    vDir = SP::kNoDirection;

    uint32_t nFlags = mFlags;
    bool bSteering = mbSteering;

    if ((nFlags & 0x200) != 0)
    {
        MessageServer_s00c1_7de0()->PostMessage(0x7c66a67, 0, 0);

        if (gUseGroundMotion)
        {
            cVector3_s00c1_7de0* pVel = mLocomotion.GetVelocity();
            float fLenSq = pVel->x * pVel->x + pVel->y * pVel->y + pVel->z * pVel->z;
            if (fLenSq == kZero)
            {
                vDir.x = gGravityDirection.x * gGravityScale;
                vDir.y = gGravityDirection.y * gGravityScale;
                vDir.z = gGravityDirection.z * gGravityScale;
            }
        }
    }

    float fRadius = mpSpecies->mLookAtRadius;

    if (!bSteering)
    {
        cVector3_s00c1_7de0* pVel = mLocomotion.GetVelocity();
        vVel = *pVel;

        cVector3_s00c1_7de0 vUp;
        cVector3_s00c1_7de0* pPos = mLocomotion.GetPosition();
        float fInv = 1.0f / sqrtf(pPos->x * pPos->x + pPos->y * pPos->y + pPos->z * pPos->z
                                   + kEpsilon);
        vUp.x = pPos->x * fInv;
        vUp.y = pPos->y * fInv;
        vUp.z = pPos->z * fInv;

        float fVelSq = vVel.x * vVel.x + vVel.y * vVel.y + vVel.z * vVel.z;
        if (kZero < fVelSq)
        {
            float fDot = vUp.x * vVel.x + vUp.z * vVel.z + vUp.y * vVel.y;
            cVector3_s00c1_7de0 vProj;
            vProj.x = vUp.x * fDot;
            vProj.y = vUp.y * fDot;
            vProj.z = vUp.z * fDot;
            if (kZero > (vProj.x * vUp.x + vProj.z * vUp.z + vProj.y * vUp.y))
                fRadius = sqrtf(vProj.z * vProj.z + (vProj.y * vProj.y + vProj.x * vProj.x))
                          + fRadius;
        }
    }

    cVector3_s00c1_7de0* pPos2 = mLocomotion.GetPosition();
    float fInv2 = 1.0f / sqrtf(pPos2->x * pPos2->x + pPos2->y * pPos2->y + pPos2->z * pPos2->z
                               + kEpsilon);
    cVector3_s00c1_7de0 vPush;
    vPush.x = pPos2->x * fInv2;
    vPush.y = pPos2->y * fInv2;
    vPush.z = pPos2->z * fInv2;
    vDir.x = vPush.x * fRadius * kNetScaleA + vDir.x;
    vDir.y = vPush.y * fRadius * kNetScaleA + vDir.y;
    vDir.z = vPush.z * fRadius * kNetScaleA + vDir.z;

    mLocomotion.OffsetPosition(vDir, 0);

    void* pPart = GetPartData(FindIndex(0x53));
    ApplyWave(*(float*)((char*)pPart + 0x104));

    if (bSteering)
    {
        uint32_t nCheck = mFlags;

        mSteerState = 3;
        mbSteering = false;

        if ((nCheck & 0x200) != 0)
        {
            cVector3_s00c1_7de0* pPos3 = mLocomotion.GetPosition();
            gStoredDirection = *pPos3;
        }

        InterruptAnimation(0x772ff58, -1, 0);
        mbWaveFinished = true;
        return;
    }

    if (mpSpecies->mWaveCount > 0)
        InterruptAnimation(0x77300ff, -1, 0);
    else
        InterruptAnimation(0x5485a4c, -1, 0);
}

// @ 0x00c18740
void __declspec(noinline) cSPCreatureBase_s00c1_7de0::UpdateWaveMotion(float fBlend, uint32_t nAmount)
{
    cVector3_s00c1_7de0* pPos = mLocomotion.GetPosition();
    float fDist = sqrtf(pPos->x * pPos->x + pPos->y * pPos->y + pPos->z * pPos->z);
    float fRange = PlanetModel_s00c1_7de0()->GetLookAtRange();

    if (fDist > fRange)
    {
        mbWaveFinished = false;
        InterruptAnimation(0x7982fb2, -1, 0);
    }

    if ((nAmount & 0xff) == 0)
    {
        uint32_t nAnim = 0;
        if (mpAnimTarget)
        {
            mpAnimTarget->GetCurrentAnimation(&nAnim, 0, 0, 0);
            if (nAnim == 0x772ff58)
                return;
        }
        mbWaveFinished = false;
        InterruptAnimation(0x7982fb2, -1, 0);
        return;
    }

    void* pPart = GetPartData(FindIndex(0x53));
    float fAmount = *(float*)((char*)pPart + 0x104) * (float)(uint32_t)nAmount * kMilli;

    if (mWaveHeight > fAmount)
    {
        ApplyWave(fAmount);

        cVector3_s00c1_7de0 vDir;
        cVector3_s00c1_7de0 vVel;

        vDir = SP::kNoDirection;

        uint32_t nFlags = mFlags;
        bool bSteering = mbSteering;

        if ((nFlags & 0x200) != 0 && gUseGroundMotion)
        {
            cVector3_s00c1_7de0* pVelocity = mLocomotion.GetVelocity();
            float fLenSq = pVelocity->x * pVelocity->x + pVelocity->y * pVelocity->y
                           + pVelocity->z * pVelocity->z;
            if (fLenSq == kZero)
            {
                vDir.x = gGravityDirection.x * gGravityScale;
                vDir.y = gGravityDirection.y * gGravityScale;
                vDir.z = gGravityDirection.z * gGravityScale;
            }
        }

        float fRadius = mpSpecies->mLookAtRadius;

        if (!bSteering)
        {
            cVector3_s00c1_7de0* pVelocity = mLocomotion.GetVelocity();
            vVel = *pVelocity;

            cVector3_s00c1_7de0 vUp;
            cVector3_s00c1_7de0* pPosition = mLocomotion.GetPosition();
            normalized_safe((float*)&vUp, (float*)pPosition);

            float fVelSq = vVel.x * vVel.x + vVel.y * vVel.y + vVel.z * vVel.z;
            if (kZero < fVelSq)
            {
                float fDot = vUp.x * vVel.x + vUp.z * vVel.z + vUp.y * vVel.y;
                cVector3_s00c1_7de0 vProj;
                vProj.x = vUp.x * fDot;
                vProj.y = vUp.y * fDot;
                vProj.z = vUp.z * fDot;
                if (kZero > (vProj.x * vUp.x + vProj.z * vUp.z + vProj.y * vUp.y))
                    fRadius = sqrtf(vProj.z * vProj.z + (vProj.y * vProj.y + vProj.x * vProj.x))
                              + fRadius;
            }
        }

        cVector3_s00c1_7de0* pPos2 = mLocomotion.GetPosition();
        float fInv = 1.0f / sqrtf(pPos2->x * pPos2->x + pPos2->y * pPos2->y + pPos2->z * pPos2->z
                                  + kEpsilon);
        cVector3_s00c1_7de0 vPush;
        vPush.x = pPos2->x * fInv;
        vPush.y = pPos2->y * fInv;
        vPush.z = pPos2->z * fInv;
        vDir.x = vPush.x * fRadius * fBlend * kMilli * kNetScaleB + vDir.x;
        vDir.y = vPush.y * fRadius * fBlend * kMilli * kNetScaleB + vDir.y;
        vDir.z = vPush.z * fRadius * fBlend * kMilli * kNetScaleB + vDir.z;

        mLocomotion.OffsetPosition(vDir, 0);
        return;
    }

    mbWaveFinished = false;
    InterruptAnimation(0x7982fb2, -1, 0);
}

// @ 0x00c18b40
int cSPCreatureBase_s00c1_8b40::FUN_00c18b40(int arg)
{
    SpeciesProfile* prof = mpProfile;
    if (prof->sprintLevel == 0)
        return 0;

    bool bLeap = mbLeaping;
    float range;
    if (bLeap) {
        range = prof->jumpingAbility;
    } else {
        if (mFlags & 0x1000)
            return 0;
        range = prof->flappingAbility;
    }
    if (range <= kRealZero)
        return 0;

    bool isAvatar = ((mGeneralFlags >> 9) & 1) != 0;

    const Vector3_s00c1_8b40* pos = mBody.GetPos();
    Vector3_s00c1_8b40 res = { gZeroVecX, gZeroVecY, gZeroVecZ };

    float inv = 1.0f / sqrtf(pos->x*pos->x + pos->y*pos->y + pos->z*pos->z
                             + kSqrtEpsilon);
    Vector3_s00c1_8b40 fwd = { pos->x*inv, pos->y*inv, pos->z*inv };

    Vector3_s00c1_8b40 face;
    mBody.GetForward(&face);

    const Vector3_s00c1_8b40* vel = mBody.GetVelocity();
    float speed = sqrtf(vel->x*vel->x + vel->y*vel->y + vel->z*vel->z);

    float dot = (fwd.x*vel->y + fwd.y*vel->z) + range*vel->x;
    float q  = range * dot;
    float projX = vel->x - q;
    float t  = fwd.y * dot;
    float projZ = vel->z - t;
    float u  = fwd.x * dot;
    float projY = vel->y - u;
    float projLen = sqrtf(projY*projY + (projZ*projZ + projX*projX));

    float radius = mBody.GetF_0xc8();

    if (gB_1572051 && isAvatar && gB_169e381 &&
        Vector3Equal(vel, (const Vector3_s00c1_8b40*)&gZeroVecX)) {
        res.x = gF_169e388 * gF_169e384;
        res.y = gF_169e38c * gF_169e384;
        res.z = gF_169e390 * gF_169e384;
    }

    if (bLeap) {
        Vector3_s00c1_8b40 r;
        r.z = fwd.z*range + vel->z;
        r.y = fwd.y*range + vel->y;
        r.x = fwd.x*range + vel->x;
        float len = sqrtf(r.z*r.z + r.y*r.y + r.x*r.x);
        float lim = (speed > range) ? speed : range;
        if (len > lim) {
            float s = lim / len;
            r.x *= s;
            r.y *= s;
            r.z *= s;
        }
        r.x -= vel->x;
        r.y -= vel->y;
        r.z -= vel->z;
        res = r;
    } else {
        Vector3_s00c1_8b40 dir = fwd;
        if (radius > projLen) {
            Vector3_s00c1_8b40 a = { face.x + fwd.x*kThree,
                          face.y + fwd.y*kThree,
                          face.z + fwd.z*kThree };
            normalized_safe(&dir, &a);
        }
        res.x = dir.x * range;
        res.y = dir.y * range;
        res.z = dir.z * range;
        if (gB_1572050 && speed > kRealZero &&
            (projX*fwd.x + projY*fwd.y + projZ*fwd.z) < kRealZero) {
            res.x -= projX;
            res.y -= projY;
            res.z -= projZ;
        }
    }

    mBody.FUN_00c446d0(&res, 0);

    if (isAvatar) {
        LocomotionRequest req;
        mBody.Submit(&req);
        if (req.mpBegin && ((int*)req.mpBegin)[-1] != 0)
            operator_delete__(req.mpBegin);
    }

    FUN_00c15dc0((float)arg);

    if (!bLeap) {
        if (prof->mCount698 == 0)
            InterruptAnimation(0x5485a4cu, -1, 0);
        else
            InterruptAnimation(0x77300ffu, -1, 0);
        return 1;
    }

    uint32 id;
    if (prof->preferredSocialType == 0) {
        id = (prof->mCount6a0 == 0) ? 0x25b3bc0u : 0x7995fdcu;
    } else if (prof->mCount6a0 != 0) {
        id = 0x7995fdcu;
    } else {
        id = (prof->mCount698 != 0) ? 0x77300f2u : 0x5261d56u;
    }
    InterruptAnimation(id, -1, 0);

    mState = 3;
    mbLeaping = false;
    if (isAvatar) {
        gF_169e3b4 = pos->x;
        gF_169e3b8 = pos->y;
        gF_169e3bc = pos->z;
    }
    return 1;
}

// @ 0x00c190e0
bool cSPCreatureBase_s00c1_8b40::TryJumpToTarget(const Vector3_s00c1_8b40* a1, const Vector3_s00c1_8b40* a2, int a3, float a4, bool a5)
{
    SpeciesProfile* prof = mpProfile;
    if (!a5 && prof->sprintLevel == 0)
        return false;

    float r1 = mBody.GetRadius();
    float r2 = mBody.GetRadius();
    float maxSq = a4*a4 + (kLeapRadiusScale*kLeapRadiusScale + r2*r1);

    const Vector3_s00c1_8b40* pos = mBody.GetPos();
    float dx = pos->x - a2->x;
    float dy = pos->y - a2->y;
    float dz = pos->z - a2->z;
    if (dx*dx + dy*dy + dz*dz < maxSq)
        return false;

    bool bLeap = mbLeaping;
    float range;
    if (bLeap) {
        range = prof->jumpingAbility;
    } else {
        range = (mFlags & 0x1000) ? 0.0f : prof->flappingAbility;
    }
    if (a5) {
        if (range <= 0.0f)
            range = 5.0f;
    } else {
        if (range <= 0.0f)
            return false;
    }

    bool flagB = (prof->preferredSocialType != 0) || (prof->flappingAbility > 0.0f);

    cPlanetModel_s00c1_8b40* pm = (cPlanetModel_s00c1_8b40*)GetPlanetModel();
    float f7 = pm->FUN_00b7e490();

    const Vector3_s00c1_8b40* p2 = mBody.GetPos();
    Vector3_s00c1_8b40 face;
    mBody.GetForward(&face);

    float inv = 1.0f / sqrtf(p2->x*p2->x + p2->y*p2->y + p2->z*p2->z
                             + kSqrtEpsilon);
    float fx = p2->x * inv;
    float fy = p2->y * inv;
    float fz = p2->z * inv;

    const Vector3_s00c1_8b40* vel = mBody.GetVelocity();
    float dist = sqrtf(p2->x*p2->x + (p2->y*p2->y + p2->z*p2->z));
    pm->GetRadiusAt(p2);

    float dot = vel->x*fx + fy*vel->y + fz*vel->z;
    float px = vel->x - fx*dot;
    float pz = vel->z - fz*dot;
    float py = vel->y - fy*dot;
    float plen = sqrtf(py*py + (pz*pz + px*px));

    float speedLim = kDefaultSpeedCap;
    if (!flagB) {
        float g;
        if (!mbFieldBB0)
            g = FUN_00c0ce80(2, 0);
        else
            g = FUN_00c0ce80(2, 1) + kCe80Boost;
        speedLim = (g <= plen) ? plen : g;
    }

    float ratio;
    if (plen <= kPlenEpsilon) {
        ratio = 1.0f;
    } else {
        Vector3_s00c1_8b40 proj = { px, py, pz };
        Vector3_s00c1_8b40 dir;
        normalized_safe(&dir, &proj);
        ratio = dir.x*face.x + dir.y*face.y + dir.z*face.z;
    }
    float r = ratio + kHalf;
    if (r <= kClampLow)
        r = kClampLow;
    if (r >= 1.0f)
        r = 1.0f;

    float a = pm->FUN_00b82310(a1);
    float ax = a1->x - p2->x;
    float ay = a1->y - p2->y;
    float az = a1->z - p2->z;
    float d2 = az*az + ay*ay + ax*ax;
    float dd = sqrtf(d2);
    float invd = 1.0f / sqrtf(d2 + kSqrtEpsilon);
    float scale = dd / speedLim;
    float t = (a - dist) / scale - (scale * range) * kHalf;
    if (t > 0.0f)
        t = 0.0f;
    float v = t;

    Vector3_s00c1_8b40 out;
    out.x = fx*v + (invd*ax)*speedLim - vel->x;
    out.y = fy*v + (invd*ay)*speedLim - vel->y;
    out.z = fz*v + (invd*az)*speedLim - vel->z;

    mBody.FUN_00c446d0(&out, 0);
    FUN_00c15dc0((float)a3);

    if (bLeap) {
        uint32 id = (prof->mCount698 == 0) ? 0x5261d56u : 0x77300f2u;
        InterruptAnimation(id, -1, 0);
        mState = 3;
        mbLeaping = false;
        return true;
    }
    uint32 id = (prof->mCount698 == 0) ? 0x5485a4cu : 0x77300ffu;
    InterruptAnimation(id, -1, 0);
    {
        LocomotionRequest req;
        mBody.Submit(&req);
        if (req.mpBegin && ((int*)req.mpBegin)[-1] != 0)
            operator_delete__(req.mpBegin);
    }
    return true;
}

// @ 0x00c196a0
uint32 cSPCreatureBase_s00c1_8b40::FUN_00c196a0(uint32 index, bool a2, bool a3)
{
    uint32 result = 0xffffffffu;
    uint32* mask = a2 ? mRechargingAbilityBits : mInUseAbilityBits;
    if (index < 0x58) {
        bool inUse = (mask[index >> 5] & (1u << (index & 0x1f))) != 0;
        if (inUse)
            goto done;
    }
    if (mCurrentAttackIdx != 0xffffffffu)
        goto done;
    if (index >= GetAbilityCount())
        goto done;
    {
        AbilityState* st = &mpAbilityStates[index];
        Ability_s00c1_8b40* ab = GetAbility(index);
        if (st->chargeLevel < 1.0f)
            goto done;
        if (index < 0x58)
            mask[index >> 5] |= 1u << (index & 0x1f);
        if (a2 || a3) {
            st->chargeLevel = 0.0f;
            FUN_00c15dc0(ab->mCost);
        }
        st->applied = false;
        mpAnimCreature->mField170 = 0;
        result = index;
    }
done:
    return result;
}

// @ 0x00c197a0
void cSPCreatureBase_s00c1_8b40::FUN_00c197a0(uint32 index)
{
    if (index >= 0x58)
        return;
    uint32 bit = 1u << (index & 0x1f);
    uint32 word = index >> 5;
    bool inUse = (mInUseAbilityBits[word] & bit) != 0;
    if (!inUse)
        return;
    if (index >= GetAbilityCount())
        return;
    mInUseAbilityBits[word] &= ~bit;
    mRechargingAbilityBits[word] |= bit;
    AbilityState* st = &mpAbilityStates[index];
    Ability_s00c1_8b40* ab = GetAbility(index);
    st->chargeLevel = 0.0f;
    int i = FindIndex(0x27);
    if (i == -1)
        i = FindIndex(0x50);
    if ((int)index == i)
        return;
    int j = FindIndex(0xd);
    if (j == -1)
        j = FindIndex(0x52);
    if ((int)index == j)
        return;
    FUN_00c15dc0(ab->mCost);
}

// @ 0x00c19870
Vector3_s00c1_8b40* CreatureSubView::FUN_00c19870(Vector3_s00c1_8b40* out, int part)
{
    int buf[0xff];
    BodyPartQuery query;
    int p = part;
    if (part == -1) {
        p = -1;
        cSPCreatureBase_s00c1_8b40* base = (cSPCreatureBase_s00c1_8b40*)((char*)this - 0x5a8);
        if (base != 0) {
            AnimatingCreature* anim = base->mpAnimCreature;
            if (anim != 0 && anim->mpAbilityList != 0) {
                query.flag = 1;
                query.mpName = gBodyPartsString;
                query.a = 0;
                query.b = 0;
                uint32 n = (uint32)EvaluateContextTargetQuery(buf, 0xff,
                                            *anim->mpAbilityList, &query, 0, 0);
                if (n > 0)
                    p = buf[0];
            }
        }
    }
    out->x = gZeroVecX;
    out->y = gZeroVecY;
    out->z = gZeroVecZ;
    ((cSPCreatureBase_s00c1_8b40*)((char*)this - 0x5a8))->GetBodyPartPositionAndOrientation(
        *out, &query, (uint32)p, true);
    return out;
}

// @ 0x00c19940
void cSPCreatureBase_s00c1_8b40::FUN_00c19940(bool a)
{
    int count = (int)(mpItemEnd - mpItemBegin);
    if (count == 0)
        return;
    InventoryItem* it = mpItemBegin;
    int i = 0;
    do {
        if (a != 0) {
            if (i >= (int)(mpItemEnd - mpItemBegin))
                goto docall;
            if (it->mpObject == 0)
                goto docall;
            InventoryObject* o = (InventoryObject*)it->mpObject;
            if (o->Query(0x398420d) == 0)
                goto docall;
            if (o->mKind != 3)
                goto docall;
            goto next;
        }
    docall:
        FUN_00c15bd0(i, 0, 0);
    next:
        ++i;
        ++it;
    } while (i < count);
}

// @ 0x00c199e0
void Vector003c::reserve(uint32 count)
{
    uint32 cur = (uint32)(((char*)mpCapacity - (char*)mpBegin) / 0x3c);
    if (count <= cur)
        return;
    char* p;
    if (count != 0) {
        p = (char*)operator_new(count * 0x3c, "Simulator", 0, 0,
               (const char*)&gAbilityStatesAllocator, 0xd1);
    } else {
        p = 0;
    }
    FUN_00ac2130(mpBegin, mpEnd, p);
    if (mpBegin && ((int*)mpBegin)[-1])
        operator_delete__(mpBegin);
    uint32 n = (uint32)(((char*)mpEnd - (char*)mpBegin) / 0x3c);
    mpBegin = p;
    mpEnd = p + n * 0x3c;
    mpCapacity = p + count * 0x3c;
}

// @ 0x00c1a3c0
void cCreatureCombatant::TakeDamage(float damage, uint32_t attackerPID, int damageType, const Vector3_s00c1_9b60& dir, void* attacker)
{
    Vector3_s00c1_9b60 tmp;
    CBase* base = Base();
    if (base->IsProtected())
        return;
    if (GetBit(mFlags8, 9) && GetCurrentGameMode() == 0x1654c05)
        return;

    CLoco* loco = Loco();
    if (loco->IsLocomotive()) {
        int s = FUN_00b3d4d0()->mState;
        if (s == 1 || s == 2)
            return;
    }

    if (GetCurrentGameMode() == 0x1654c05) {
        StarManager();
        if (FUN_00ba6650(attackerPID) && (base->mpOverride == 0 || base->mpOverride[0x388] == 0))
            damage = 10000.0f;
    }

    if (GetCurrentGameMode() == 0x1654c10 && damageType != 7) {
        bool fired = false;
        if (mpProfile->mCount668 > 0) {
            float r = FUN_00c0db80(damage, base);
            if (r < damage && mCooldown > g_CooldownThreshold) {
                RefObj* o = FUN_00c11690(0xf7a8a2b1, base, attacker);
                if (o)
                    PushEffect(&mEffects, o);
                fired = true;
            }
            damage = r;
        }
        if (mpProfile->mCount648 > 0) {
            float r = FUN_00c161f0(damage, base);
            if (r < damage && mCooldown > g_CooldownThreshold) {
                RefObj* o = FUN_00c11690(0x924bae45, base, attacker);
                if (o)
                    PushEffect(&mEffects, o);
                fired = true;
            }
            damage = r;
        }
        if (mpProfile->mCount664 > 0) {
            float r = FUN_00c16340(damage, base);
            if (r < damage && mCooldown > g_CooldownThreshold) {
                RefObj* o = FUN_00c11690(0xb9716d18, base, attacker);
                if (o)
                    PushEffect(&mEffects, o);
                fired = true;
            }
            damage = r;
        }
        if (mpProfile->mCount660 > 0) {
            float r = FUN_00c0dcb0(damage, base);
            if (r < damage && mCooldown > g_CooldownThreshold) {
                RefObj* o = FUN_00c11690(0x4c1b2351, base, attacker);
                if (o)
                    PushEffect(&mEffects, o);
                fired = true;
            }
            damage = r;
        }
        if (fired)
            mCooldown = 0;
    }

    TakeHit(damage, attackerPID, damageType, dir, attacker);

    if (GetDamageState() == 2) {
        mFlags8 &= 0xffffefff;
        if (GetCurrentGameMode() == 0x1654c10)
            base->FUN_00c19940(0);
        CAgent* agent = Agent();
        bool skip = false;
        if (agent->GetTypeObj() != 0 && agent->GetTypeObj()->GetType() == 0x3cdbbe9)
            skip = true;
        if (skip || (damageType != 0 && damageType != 1)) {
            if (GetCurrentGameMode() != 0x1654c01 && GetCurrentGameMode() != 0x1654c02 &&
                FUN_00ac80d0(base, 0x18eb45e) == 0 && GetCurrentGameMode() != 0x1654c04)
                ((void (__thiscall*)(CBase*, int))(*(void***)base)[0xc8 / 4])(base, 0);
        } else if (damageType == 0) {
            tmp.x = -dir.x; tmp.y = -dir.y; tmp.z = -dir.z;
            FUN_00b3d240()->Post(0x1b55d9a, (void*)loco->GetVector(), &tmp);
        } else {
            tmp.x = -dir.x; tmp.y = -dir.y; tmp.z = -dir.z;
            FUN_00b3d240()->Post(0x1b55d9b, (void*)loco->GetVector(), &tmp);
            return;
        }
    }
    if (damageType != 0)
        return;
    if ((mpOverride == 0 || mpOverride[0x388] == 0) && GetCurrentGameMode() != 0x1654c10) {
        Vector3_Normalize(&tmp, loco->GetVector());
        const float k2 = 2.0f;
        const float tx = tmp.x * k2, ty = tmp.y * k2, tz = tmp.z * k2;
        tmp.x = (tx + dir.x) * 4.0f; tmp.y = (ty + dir.y) * 4.0f; tmp.z = (tz + dir.z) * 4.0f;
        loco->FUN_00c41d60(&tmp);
        tmp.x = tx + dir.x; tmp.y = ty + dir.y; tmp.z = tz + dir.z;
        loco->FUN_00c446d0(&tmp, 0);
        *(int*)((char*)this - 0x2f8) = 3;
    }
}

// @ 0x00c1b020
void cSPCreatureBase::FUN_00c1b020(int arg)
{
    if (mpTargetHolder) {
        TargetCreature* other = (TargetCreature*)mpTargetHolder->Query(0xce9f6639);
        if (other) {
            Body* me = &mBody;
            Body* ob = &other->mBody;
            const Vector3_s00c1_aad0* myPos = me->GetPos();
            const Vector3_s00c1_aad0* otherPos = ob->GetPos();
            Vector3_s00c1_aad0 d;
            d.z = otherPos->z - myPos->z;
            d.y = otherPos->y - myPos->y;
            d.x = otherPos->x - myPos->x;
            float inv = 1.0f / sqrtf((d.z * d.z + d.y * d.y) + d.x * d.x + 1e-8f);
            d.x = inv * d.x;
            d.y = d.y * inv;
            d.z = d.z * inv;
            Vector3_s00c1_aad0 fwdTmp;
            if (!(d.x == kZeroVec.x && d.y == kZeroVec.y && d.z == kZeroVec.z)) {
                const Vector3_s00c1_aad0* fwd = me->GetForward(&fwdTmp);
                if ((fwd->y * d.y + fwd->z * d.z) + fwd->x * d.x > 0.7f) {
                    float boundsTmp[6];
                    const float* bb = ob->GetBounds(boundsTmp);
                    Vector3_s00c1_aad0 center;
                    center.x = (bb[3] + bb[0]) * 0.5f;
                    center.y = (bb[4] + bb[1]) * 0.5f;
                    center.z = (bb[5] + bb[2]) * 0.5f;
                    float otherRadius = ob->GetRadius();
                    ob->GetVelocity();
                    SpeciesData* sp = mpSpecies;
                    if (sp->m610 != 0) {
                        float thr = (me->GetRadius() * me->GetRadius() + otherRadius * otherRadius) +
                                    kLeapMargin * kLeapMargin;
                        const Vector3_s00c1_aad0* p = me->GetPos();
                        float dz = p->z - center.z;
                        float dy = p->y - center.y;
                        float dx = p->x - center.x;
                        if (!(thr > (dz * dz + dy * dy) + dx * dx)) {
                            bool bLeaping = mbLeaping;
                            float range;
                            if (bLeaping) {
                                range = sp->mLeapRangeAir;
                            } else {
                                if (mFlags & 0x1000)
                                    goto L_submit;
                                range = sp->mLeapRange;
                            }
                            if (range > 0.0f) {
                                bool bBig;
                                if (sp->m61c > 0u || sp->mLeapRange > 0.0f)
                                    bBig = true;
                                else
                                    bBig = false;
                                PlanetModel* pm = GetPlanetModel();
                                float g = pm->FUN_00b7e490();
                                const Vector3_s00c1_aad0* pos = me->GetPos();
                                Vector3_s00c1_aad0 fwd2;
                                me->GetForward(&fwd2);
                                float pinv = 1.0f / sqrtf((pos->x * pos->x + pos->y * pos->y) + pos->z * pos->z + 1e-8f);
                                Vector3_s00c1_aad0 up;
                                up.x = pos->x * pinv;
                                up.y = pinv * pos->y;
                                up.z = pinv * pos->z;
                                const Vector3_s00c1_aad0* vel = ob->GetVelocity();
                                float posLen = sqrtf((pos->z * pos->z + pos->y * pos->y) + pos->x * pos->x);
                                pm->GetRadiusAt(pos);
                                float vup = (vel->x * up.x + vel->y * up.y) + vel->z * up.z;
                                Vector3_s00c1_aad0 t;
                                t.x = vel->x - up.x * vup;
                                t.y = vel->y - up.y * vup;
                                t.z = vel->z - up.z * vup;
                                Vector3_s00c1_aad0 t2;
                                t2.x = t.x;
                                t2.y = t.y;
                                t2.z = t.z;
                                float speed = sqrtf((t.x * t.x + t.z * t.z) + t.y * t.y);
                                float cap = kLeapSpeedDefault;
                                if (!bBig) {
                                    float v;
                                    if (mbBB0)
                                        v = FUN_00c0ce80(2, 1) + 10.0f;
                                    else
                                        v = FUN_00c0ce80(2, 0);
                                    const float* pc = &speed;
                                    if (v > speed)
                                        pc = &v;
                                    cap = *pc;
                                }
                                float dotv;
                                if (speed > 0.1f) {
                                    Vector3_s00c1_aad0* n = normalized_safe(&t, &t2);
                                    dotv = (n->y * fwd2.y + n->z * fwd2.z) + n->x * fwd2.x;
                                } else {
                                    dotv = 1.0f;
                                }
                                float w = dotv + 0.5f;
                                float lo = 0.3f, hi = 1.0f;
                                __asm {
                                    movss xmm0, w
                                    maxss xmm0, lo
                                    minss xmm0, hi
                                    movss w, xmm0
                                }
                                float groundR = pm->FUN_00b82310(&center);
                                Vector3_s00c1_aad0 e;
                                e.x = center.x - pos->x;
                                e.z = center.z - pos->z;
                                e.y = center.y - pos->y;
                                float e2 = (e.x * e.x + e.z * e.z) + e.y * e.y;
                                float tt = sqrtf(e2) / cap;
                                float einv = 1.0f / sqrtf(e2 + 1e-8f);
                                float vz = (groundR - posLen) / tt - (tt * g) * 0.5f;
                                const float* pv = &range;
                                if (!(vz > range))
                                    pv = &vz;
                                float vzc = *pv;
                                Vector3_s00c1_aad0 acc;
                                acc.x = (up.x * vzc + (einv * e.x) * cap) - vel->x;
                                acc.y = (up.y * vzc + (e.y * einv) * cap) - vel->y;
                                acc.z = (up.z * vzc + (e.z * einv) * cap) - vel->z;
                                me->FUN_00c446d0(&acc, false);
                                FUN_00c15dc0((float)arg);
                                if (bLeaping) {
                                    if (sp->m698 > 0u)
                                        InterruptAnimation(0x77300f2, -1, 0);
                                    else
                                        InterruptAnimation(0x5261d56, -1, 0);
                                    mState = 3;
                                    mbLeaping = false;
                                } else {
                                    if (sp->m698 > 0u)
                                        InterruptAnimation(0x77300ff, -1, 0);
                                    else
                                        InterruptAnimation(0x5485a4c, -1, 0);
                                    me->Submit(cLocomotionRequest());
                                }
                            }
                        }
                    }
                L_submit:
                    me->Submit(cLocomotionRequest(ob->GetPos(), 1.0f, 2.0f));
                    return;
                }
            }
        }
    }
    FUN_00c18b40(arg);
}

// @ 0x00c1bad0
tNavigationWaypoint* cSPCreatureBase_s00c1_bad0::FUN_00c1bad0(tNavigationWaypoint* pGoal, void* pPathOwner)
{
    pGoal->mpNext   = 0;                   // +0x00
    pGoal->mPos.x   = 0.0f;                // +0x14
    pGoal->mPos.y   = 0.0f;                // +0x18
    pGoal->mPos.z   = 0.0f;                // +0x1c
    pGoal->mf50     = 0.0f;                // +0x50
    pGoal->mf54     = 0.0f;                // +0x54
    pGoal->mf58     = 0.0f;                // +0x58
    pGoal->mf60     = 1.0f;                // +0x60
    pGoal->mf64     = _DivOneFifty;        // +0x64
    pGoal->mf68     = 1.0f;                // +0x68
    pGoal->mf6c     = 0.0f;                // +0x6c
    pGoal->mp70     = (void*)pPathOwner;   // +0x70
    pGoal->mb3c     = 0;                   // +0x3c
    pGoal->mb5c     = 0;                   // +0x5c

    if (*(void**)pPathOwner != *(void**)((u8*)pPathOwner + 4))   // begin != end
    {
        FUN_00c1b790(pGoal, pPathOwner);
        tNavigationWaypoint* pSrc = pGoal->mpNext;
        pGoal->mb5c = 1;
        u32* pDst = (u32*)((u8*)pGoal + 0x14);
        u32* pS   = (u32*)pSrc;
        for (int i = 0; i < 0xf; ++i)
            pDst[i] = pS[i];
        FUN_00b47520(pSrc);
        return pGoal;
    }
    pGoal->mb5c   = 0;
    pGoal->mPos.x = 0.0f;
    pGoal->mPos.y = 0.0f;
    pGoal->mPos.z = 0.0f;
    return pGoal;
}

// @ 0x00c1bbd0
void cSPCreatureBase_s00c1_bad0::FUN_00c1bbd0()
{
    *(void**)((u8*)this + 0x000) = &g_vtbl_cSPCreatureBase;
    *(void**)((u8*)this + 0x004) = &g_vtbl_cGameData;
    *(void**)((u8*)this + 0x034) = &g_vtbl_cInteractionAgent;
    *(void**)((u8*)this + 0x058) = &g_vtbl_cLocoSub;
    *(void**)((u8*)this + 0x0c0) = &g_vtbl_cLocomotiveObject;
    *(void**)((u8*)this + 0x194) = &g_vtbl_cLocoSub2;
    *(void**)((u8*)this + 0x590) = &g_vtbl_cSPCreatureBase2;
    *(void**)((u8*)this + 0x5a8) = &g_vtbl_cCombatant;
    *(void**)((u8*)this + 0x670) = &g_vtbl_cSub670;

    void* p = *(void**)((u8*)this + 0xb48);          // +0x2d2 dwords
    if (p)
    {
        FUN_00bc9fa0(p);
        EASTL_deallocate(p);
    }

    p = *(void**)((u8*)this + 0xb4c);                // +0x2d3 dwords
    if (p)
    {
        FUN_00bcae90(p);
        EASTL_deallocate(p);
    }

    FUN_00ac4570(*(void**)((u8*)this + 0xf88), *(void**)((u8*)this + 0xf84));

    // Three 0x20-byte repetition records at +0xf90 / +0xfb0 / +0xfd0, each owning
    // two AutoRefs and one slot-0x64 object.
    for (int i = 0; i < 3; ++i)
    {
        u8* rec = (u8*)this + 0xf90 + i * 0x20;
        void** ppHead = (void**)(rec + 0x00);
        void** ppA    = (void**)((u8*)rec - 0x04);
        void** ppB    = (void**)(rec + 0x18);
        void** ppC    = (void**)((u8*)rec - 0x08);

        *ppHead = 0;
        if (*ppA)
        {
            VCall(*ppA, 0x0c);
            if (*ppA)
            {
                *ppA = 0;
                VCall0(*ppA, 0x04);
            }
        }
        if (*ppB)
        {
            VCall(*ppB, 0x0c);
            if (*ppB)
            {
                *ppB = 0;
                VCall0(*ppB, 0x04);
            }
        }
        if (*ppC)
        {
            *ppC = 0;
            VCall0(*ppC, 0x64);
        }
        if (*ppB)
            VCall0(*ppB, 0x04);
        if (*ppA)
            VCall0(*ppA, 0x04);
        if (*ppC)
            VCall0(*ppC, 0x64);
    }

    p = *(void**)((u8*)this + 0xf90 + 0x360);        // +0x3a6 dwords
    if (p && *(int*)((u8*)p - 4) != 0)
        EASTL_deallocate(p);

    p = *(void**)((u8*)this + 0x15b8);               // +0x39f dwords
    if (p)
        VCall0(p, 0x64);

    FUN_00c144b0(*(void**)((u8*)this + 0x1640), *(void**)((u8*)this + 0x1644));
    p = *(void**)((u8*)this + 0x1640);               // +0x390 dwords
    if (p && *(int*)((u8*)p - 4) != 0)
        EASTL_deallocate(p);

    p = *(void**)((u8*)this + 0x15e0);               // +0x389 dwords
    if (p && *(int*)((u8*)p - 4) != 0)
        EASTL_deallocate(p);

    DoNukeSubtree(*(void**)((u8*)this + 0x1a10));    // +0x385 dwords (rbtree root)

    FUN_00a24480(*(void**)((u8*)this + 0x2b78), *(void**)((u8*)this + 0x2b7c));
    FreeLooseBuffer(*(void**)((u8*)this + 0x2b78), *(void**)((u8*)this + 0x2b7c),
                    (void**)((u8*)this + 0x2bb4),
                    *(void**)((u8*)this + 0x2b98), *(void**)((u8*)this + 0x2b9c));

    FUN_00a24480(*(void**)((u8*)this + 0x2698), *(void**)((u8*)this + 0x269c));
    FreeLooseBuffer(*(void**)((u8*)this + 0x2698), *(void**)((u8*)this + 0x269c),
                    (void**)((u8*)this + 0x26d4),
                    *(void**)((u8*)this + 0x26b8), *(void**)((u8*)this + 0x26bc));

    p = *(void**)((u8*)this + 0xc28);                // +0x30a dwords
    if (p && *(int*)((u8*)p - 4) != 0)
        EASTL_deallocate(p);

    p = *(void**)((u8*)this + 0xbc0);                // +0x2f0 dwords
    if (p && *(int*)((u8*)p - 4) != 0)
        EASTL_deallocate(p);

    cGonzagoTimer_Destroy((u8*)this + 0xb90);        // +0x2e4 dwords

    p = *(void**)((u8*)this + 0xb54);                // +0x2d5 dwords (animating creature)
    if (p)
        cAnimatingCreature_Release(p);

    p = *(void**)((u8*)this + 0xb50);                // +0x2d4 dwords
    if (p)
        VCall0(p, 0x04);

    p = *(void**)((u8*)this + 0xb38);                // +0x2ce dwords
    if (((i32)((u8*)*(void**)((u8*)this + 0xb40) - (u8*)p) >> 1) * 2 > 2 && p)
        EASTL_deallocate(p);

    FUN_00c7d650();
    FUN_00bfcd00();
    FUN_00ac0520();
    FUN_00c432e0();
    FUN_00abfec0();
    FUN_00cee7a0();
    FUN_00b184c0();
}

// @ 0x00c1c080
void cSPCreatureBase_s00c1_bad0::FUN_00c1c080(u32 a, Vec3_s00c1_bad0* pPos, Vec3_s00c1_bad0* pDir, f32 f1, f32 f2)
{
    tNavigationWaypoint goal;
    goal.mPos    = *pDir;                  // +0x14 destination orientation
    goal.mPad0c[0] = 0;                    // clear the racy tail dwords
    goal.mf50    = 0.0f;
    goal.mf54    = 0.0f;
    goal.mf58    = 0.0f;
    goal.mf60    = f2;                     // +0x60
    goal.mf64    = _BigFloat;              // +0x64
    goal.mf68    = 4.0f;                   // +0x68 literal (local_10)
    goal.mf6c    = _DivOneFifty;           // +0x6c (local_c)
    goal.mb5c    = 0;
    goal.mf30    = 0.0f;
    goal.mpNext  = 0;
    goal.mpPathOwner = 0;

    // loco slot 0xdc: set goal / recompute path with the local waypoint.
    (*(void(__thiscall**)(void*, void*))((u8*)*(void**)((u8*)this + 0xc0) + 0xdc))
        ((u8*)this + 0xc0, &goal);

    mp_f98 = (void*)a;

    f32 t;
    if (mb_bb0 == 0)
        t = FUN_00c0ce80(1, 0);
    else
        t = FUN_00c0ce80(2, 1) + g_SpeedBonus;
    mf_2a0 = t;
    mdw_330 = 0;

    FUN_00ac4570(mCurve, *(void**)(mCurve + 4));       // erase the whole curve span

    if (goal.mpNext && *(int*)((u8*)goal.mpNext - 4) != 0)
        EASTL_deallocate(goal.mpNext);
}

// @ 0x00c1c1d0
void cSPCreatureBase_s00c1_bad0::MoveToPointAtSpeed(void* pTarget, Vec3_s00c1_bad0* pPos, f32 f0, f32 f1)
{
    tNavigationWaypoint goal;
    goal.mPos    = *pPos;                  // +0x14
    goal.mf50    = 0.0f;
    goal.mf54    = 0.0f;
    goal.mf58    = 0.0f;
    goal.mf60    = f1;                     // +0x60
    goal.mf64    = f0;                     // +0x64
    goal.mf68    = _DivOneFifty;           // +0x68
    goal.mf6c    = 1.0f;                   // +0x6c
    goal.mb5c    = 0;
    goal.mf30    = 0.0f;
    goal.mpNext  = 0;
    goal.mpPathOwner = 0;

    (*(void(__thiscall**)(void*, void*))((u8*)*(void**)((u8*)this + 0xc0) + 0xdc))
        ((u8*)this + 0xc0, &goal);

    if (goal.mpNext && *(int*)((u8*)goal.mpNext - 4) != 0)
        EASTL_deallocate(goal.mpNext);

    mp_f98 = pTarget;

    f32 t;
    if (mb_bb0 == 0)
        t = FUN_00c0ce80(1, 0);
    else
        t = FUN_00c0ce80(2, 1) + g_SpeedBonus;
    mf_2a0 = t;
    mdw_330 = 0;

    FUN_00ac4570(mCurve, *(void**)(mCurve + 4));
}

// @ 0x00c1c310
void cSPCreatureBase_s00c1_bad0::MoveToPointAtSpeedPathPlan(void* pOwner, Vec3_s00c1_bad0* pPos, f32 f0, u32 flags, char bPlan)
{
    u8* pCurve = mCurve;                               // SpVector<cCurvePoint>
    tNavigationWaypoint* pGoal = mpGoal_bf4;

    if (!bPlan)
        goto clear;

    if (*(void**)pCurve == *(void**)(pCurve + 4))
        goto clear;

    {
        Vec3_s00c1_bad0* pCur = (Vec3_s00c1_bad0*)VCall((u8*)this + 0xc0, 0x2c);
        f32 dy = pCur->y - mLastGoalPos.y;
        f32 dx = pCur->x - mLastGoalPos.x;
        f32 dz = pCur->z - mLastGoalPos.z;
        f32 d2 = (dy * dy + dx * dx) + dz * dz;
        if (_Tolerance <= d2)
            goto clear;

        Vec3_s00c1_bad0* pLast = (Vec3_s00c1_bad0*)((u8*)*(void**)(pCurve + 4) - 0x3c);
        f32 gy = pLast->y - pPos->y;
        f32 gx = pLast->x - pPos->x;
        f32 gz = pLast->z - pPos->z;
        f32 g2 = (gy * gy + gx * gx) + gz * gz;
        if (_Tolerance <= g2)
            goto clear;

        // Accept the new destination: move the tail curve point, update the goal speed,
        // clear the 0x4 path-plan bit and re-issue the goal.
        Vec3_s00c1_bad0* pTail = (Vec3_s00c1_bad0*)((u8*)*(void**)(pCurve + 4) - 0x3c);
        *pTail = *pPos;
        *(f32*)((u8*)*(void**)(pCurve + 4) - 0x30) = f0;
        mdw_330 &= 0xfffffffb;

        tNavigationWaypoint local;
        FUN_00c1bad0(&local, pCurve);
        (*(void(__thiscall**)(void*, void*))((u8*)*(void**)((u8*)this + 0xc0) + 0xdc))
            ((u8*)this + 0xc0, &local);
        if (local.mpNext && *(int*)((u8*)local.mpNext - 4) != 0)
            EASTL_deallocate(local.mpNext);

        void* pR = FUN_00c41ec0();
        *(f32*)((u8*)pR + 0x20) = f0;
        pR = FUN_00c41ec0();
        *(f32*)((u8*)pR + 0x60) = (f32)flags;

        FUN_00c0cff0(this, flags, f0, &local, pGoal, 4);
        return;
    }

clear:
    FUN_00ac4570(*(void**)pCurve, *(void**)(pCurve + 4));
    {
        Vec3_s00c1_bad0* pCur = (Vec3_s00c1_bad0*)VCall((u8*)this + 0xc0, 0x2c);
        mLastGoalPos = *pCur;
    }
    FUN_00c41ec0();

    pGoal->mf50 = 0.0f;                                // +0x50
    pGoal->mPos = *pPos;                               // +0x14
    pGoal->mf60 = f0;                                  // +0x60
    pGoal->mf54 = 0.0f;
    pGoal->mf58 = (f32)flags;                          // +0x58
    pGoal->mb5c = 0;

    mp_f9c = pOwner;
    mdw_330 = 4;

    u32 searchId = (u32)VCall((u8*)this + 0xc0, 0x58);
    void* pCtx = FUN_00ac65d0(this, pPos, pPos, 0, f0,
                              mCurve, (void*)mpGoal_bf4, searchId & 0xff, 0);
    void* pSearch = (void*)((u8*)this + 0x194);
    FUN_00b3d290((void*)0x01565b68, pCtx);
    FUN_00ac65d0(pSearch, pCtx, pPos, 0, f0, mCurve, (void*)mpGoal_bf4,
                 searchId & 0xff, 0);
}

// @ 0x00c1c5c0
void cSPCreatureBase_s00c1_bad0::MoveToPointAndFacingAtSpeed(void* pOwner, Vec3_s00c1_bad0* pPos, Vec3_s00c1_bad0* pFacing, f32 f0, f32 f1)
{
    Vec3_s00c1_bad0 facing = *pFacing;

    Vec3_s00c1_bad0* pCur = (Vec3_s00c1_bad0*)VCall((u8*)this + 0xc0, 0x2c);

    if (mp_2b0 == 0 &&
        !(pCur->x == g_DefaultGoalDir[0] && pCur->y == g_DefaultGoalDir[1] &&
          pCur->z == g_DefaultGoalDir[2]))
    {
        // Project the requested facing onto the plane orthogonal to pPos.
        f32 inv = 1.0f / (f32)sqrt((double)((pPos->x * pPos->x + pPos->y * pPos->y)
                                             + pPos->z * pPos->z));
        f32 dot = (pFacing->y * (pPos->y * inv) + pFacing->x * (pPos->x * inv))
                  + pFacing->z * (pPos->z * inv);
        facing.x = pFacing->x - (pPos->x * inv) * dot;
        facing.y = pFacing->y - (pPos->y * inv) * dot;
        facing.z = pFacing->z - (pPos->z * inv) * dot;

        if (facing.x != g_DefaultGoalDir[0] || facing.y != g_DefaultGoalDir[1] ||
            facing.z != g_DefaultGoalDir[2])
        {
            f32 len = (f32)sqrt((double)(facing.x * facing.x
                                         + (facing.y * facing.y + facing.z * facing.z)));
            f32 n = 1.0f / len;
            facing.x *= n;
            facing.y *= n;
            facing.z *= n;
        }
    }

    tNavigationWaypoint goal;
    goal.mPos  = *pPos;                    // +0x14
    goal.mf50  = f0;                       // +0x50
    goal.mf30  = facing.x;                 // (rotation slot used as facing)
    goal.mPad34[0] = 0;
    goal.mf54  = facing.y;
    goal.mf58  = facing.z;
    goal.mf60  = 0.0f;                     // +0x60
    goal.mf64  = _SmallTolerance;          // +0x64
    goal.mf68  = 0.0f;                     // +0x68
    goal.mf6c  = 0.0f;                     // +0x6c
    goal.mb5c  = 0;
    goal.mb3c  = 3;
    goal.mpNext  = 0;
    goal.mpPathOwner = 0;

    (*(void(__thiscall**)(void*, void*))((u8*)*(void**)((u8*)this + 0xc0) + 0xdc))
        ((u8*)this + 0xc0, &goal);

    if (goal.mpNext && *(int*)((u8*)goal.mpNext - 4) != 0)
        EASTL_deallocate(goal.mpNext);

    mp_f98 = pOwner;

    f32 t;
    if (mb_bb0 == 0)
        t = FUN_00c0ce80(1, 0);
    else
        t = FUN_00c0ce80(2, 1) + g_SpeedBonus;
    mf_2a0 = t;
    mdw_330 = 0;

    FUN_00ac4570(mCurve, *(void**)(mCurve + 4));
}

void  FUN_00c7dba0(void* pSub);                                       // 0x00c7dba0
void  FUN_00bfc720(void* pSub);                                       // 0x00bfc720

// @ 0x00c1c8e0
void cSPCreatureBase_s00c1_bad0::Shutdown()
{
    VCall0(this, 0xc4);

    ((cLocomotiveObject_s00c1_bad0*)((u8*)this + 0xc0))->Shutdown();
    FUN_00c7dba0((u8*)this + 0x670);

    void* pAnim = *(void**)((u8*)this + 0xb54);
    if (pAnim && *(void**)pAnim)
    {
        if ((i32)VCall(pAnim, 0x70))
        {
            typedef void (__thiscall* fn_set)(void*, void*);
            (*(fn_set)((u8*)*(void**)pAnim + 0x70))(pAnim, (void*)0);
            void* pInner = (void*)VCall(pAnim, 0x70);
            (*(void(__thiscall**)(void*, void*))((u8*)*(void**)pInner + 0x3c))(pInner, pAnim);
            if (pAnim)
            {
                *(void**)((u8*)this + 0xb54) = 0;
                cAnimatingCreature_Release(pAnim);
            }
        }
    }

    FUN_00bfc720((u8*)this + 0x5a8);

    void* pSub = *(void**)((u8*)this + 0x2c);
    if (pSub)
    {
        *(void**)((u8*)this + 0x2c) = 0;
        VCall0(pSub, 0x04);
    }

    // eastl vector compact: memmove(begin, end, begin), then shrink end.
    u8* pBegin = *(u8**)((u8*)this + 0xc28);
    u8* pEnd   = *(u8**)((u8*)this + 0xc2c);
    FUN_011e0744((void*)pBegin, (const void*)pEnd, (size_t)(u32)(pEnd - pBegin));
    *(u8**)((u8*)this + 0xc2c) += ((i32)(pBegin - pEnd) >> 4) * 16;

    // Walk the render list at +0xf84; first reset each entry, then delete each node.
    u8* pSentinel = (u8*)this + 0xf84;
    u8* pNode = *(u8**)pSentinel;
    while (pNode != pSentinel)
    {
        void* pObj = *(void**)(pNode + 8);
        VCall(pObj, 0x0c);
        pNode = *(u8**)pNode;
    }

    pNode = *(u8**)pSentinel;
    while (pNode != pSentinel)
    {
        u8* pNext = *(u8**)pNode;
        void* pObj = *(void**)(pNode + 8);
        if (pObj)
            VCall0(pObj, 0x04);
        EASTL_deallocate(pNode);
        pNode = pNext;
    }
    *(u8**)(pSentinel + 4) = pSentinel;
    *(u8**)pSentinel = pSentinel;
}

// @ 0x00c1c9f0
void cSPCreatureBase_s00c1_c9f0::FUN_00c1c9f0(char a)
{
    if (a == 0) {
        mSub_5a8.v2c(1);
        mf_bbc = DAT_01687a00;
        mf_b84 = FUN_00c0bb20();
    }

    mp_eac = 0;
    SetStealthed(0, 0);
    SetSprinting(0);
    mf_b78 = 0.0f;
    mp_bb4 = 0;

    mdw_bec = 0;
    mdw_bf0 = 0;
    mdw_bf4 = 0;
    mdw_c04 = 0;
    mdw_c08 = 0;
    mdw_c0c = 0;

    if (a == 0) {
        u32* p = &mdw_bf8;
        for (i32 i = 0; i < 3; ++i) {
            if (p[i] != 0) {
                for (cAbilityState_s00c1_c9f0* q = mAbilities.mpBegin; q != mAbilities.mpEnd; ++q)
                    q->mfWeight = 1.0f;
                mdw_bf8 = 0;
                mdw_bfc = 0;
                mdw_c00 = 0;
                break;
            }
        }
    }

    mdw_110 &= 0xffffff7f;
    mdw_b58 &= 0xffff778f;

    mb_b5f = 0;
    mb_b5c = 0;
    mb_b63 = 0;

    if (mp_e7c != 0) {
        cDetach* p = mp_e7c;
        mp_e7c = 0;
        p->d64();
    }

    mp_b48->FUN_00bc9fe0();

    mf_b74 = 0.0f;
    mf_b80 = DAT_0150c8c0;

    if (a == 0)
        mb_b5e = 0;

    mdw_e8c = 0xffffffff;
    mdw_e90 = 0xffffffff;
    mf_e94 = 0.0f;

    mVec_e98.clear();
    mVec_e98.clear();

    mb_328 = 1;
    mSub_0c0.FUN_00c41d60(&DAT_0168d910);

    if (mp_b54 != 0)
        InterruptAnimation(0x02481de5, -1, 0);

    FUN_00c0d3a0(this);
    FUN_00bcb660(*(u32*)mp_b4c);
    mSub_0c0.vEc();
}

// @ 0x00c1cc80
bool cSPCreatureBase_s00c1_c9f0::FUN_00c1cc80(char a)
{
    if (mp_b20 == 0)
        return false;

    if (a == 0 && mp_b20->mnSequence == mdw_b24)
        return false;

    i32 n = vB0();

    cAbilityState_s00c1_c9f0* pEnd = mAbilities.mpEnd;
    copy_705250(pEnd, pEnd, mAbilities.mpBegin);
    mAbilities.mpEnd = mAbilities.mpBegin;
    mAbilities.FUN_00c53690(n);

    mdw_bec = 0;
    mdw_bf0 = 0;
    mdw_bf4 = 0;
    mdw_c04 = 0;
    mdw_c08 = 0;
    mdw_c0c = 0;
    mdw_bf8 = 0;
    mdw_bfc = 0;
    mdw_c00 = 0;

    for (i32 i = n; i != 0; --i) {
        cAbilityState_s00c1_c9f0 e;
        e.mbActive = 0;
        e.mbEnabled = 0;
        e.mwFlags = 0;
        e.mfWeight = 1.0f;
        mAbilities.push_back(e);
    }

    FUN_00c0d9b0();

    mdw_b24 = mp_b20->mnSequence;
    f32 f = mp_b20->mf_644;
    mf_e5c = f;
    mf_e58 = f;
    return true;
}

// @ 0x00c1cdd0
void cSPCreatureBase_s00c1_c9f0::FUN_00c1cdd0(i32 a)
{
    if (mp_b54 == 0)
        return;

    i32 idx = FUN_00c0c080(0x0d);
    if (idx == -1)
        idx = FUN_00c0c080(0x52);

    i32 r = vB4(idx);

    if (r != 0 && mb_bb1 != 0) {
        f32 t = (f32)((f64)(u32)a * DAT_013f9428) * *(f32*)((char*)r + 0x104);
        FUN_00c15dc0(t);
        if (mf_e58 == _HK_REAL_ZERO)
            SetStealthed(0, 0);
    }

    if (mb_b5e == 0 && (mdw_b58 & 0x800) == 0) {
        f32 p = (f32)pow(DAT_01447a10, (f64)(u32)a * DAT_013f9428);
        f32 target = (mb_bb1 != 0) ? DAT_013ec480 : 1.0f;
        f32 nv = (1.0f - p) * target + mf_b7c * p;
        mf_b7c = nv;
        if (nv > DAT_013f7344)
            mf_b7c = 1.0f;
        mp_b54->mf_80 = mf_b7c;
    }
}

// @ 0x00c1cf20
void cSPCreatureBase_s00c1_c9f0::FUN_00c1cf20()
{
    FUN_00c19940(0);

    // release every live node held in the +0xcc8 table
    {
        cPHNode* p = (cPHNode*)mTable_cc8.mppBuckets[0];
        if (p == 0) {
            u32* pBuckets = (u32*)mTable_cc8.mppBuckets;
            while (pBuckets[1] == 0) {
                ++pBuckets;
                if (pBuckets[1] != 0)
                    break;
                ++pBuckets;
                if (pBuckets[1] == 0)
                    ++pBuckets;
            }
        }
    }

    for (u32 i = 0; i < mTable_cc8.mnBucketCount; ++i) {
        cPHNode* p = (cPHNode*)mTable_cc8.mppBuckets[i];
        while (p != 0) {
            cPHNode* pNext = p->mpChain;
            cVObj* pObj = p->mpObject;
            cVObj* pNew = 0;
            if (pObj != 0)
                pNew = pObj;
            else
                pNew = 0;
            (void)pNew;
            if (p != 0) {
                if (p->mpObject != 0)
                    p->mpObject->v0c(0);
            }
            if (pNext != 0)
                pNext->mpObject->v04();
            p = pNext;
        }
    }

    mTable_cc8.FreeBuckets((cVObj**)mTable_cc8.mppBuckets, mTable_cc8.mnBucketCount);
    mTable_cc8.mppBuckets = 0;
    mTable_cc8.mnBucketCount = 0;
    mTable_cc8.mnSize = 0;
    mTable_cc8.mnElementCount = 0;

    // second table at +0xd68
    for (u32 i = 0; i < mTable_d68.mnBucketCount; ++i) {
        cPHNode* p = (cPHNode*)mTable_d68.mppBuckets[i];
        while (p != 0) {
            cPHNode* pNext = p->mpChain;
            if (p->mpObject != 0)
                p->mpObject->v0c(0);
            if (pNext != 0)
                pNext->mpObject->v04();
            p = pNext;
        }
    }
    mTable_d68.FreeBuckets((cVObj**)mTable_d68.mppBuckets, mTable_d68.mnBucketCount);
    mTable_d68.mppBuckets = 0;
    mTable_d68.mnBucketCount = 0;
    mTable_d68.mnSize = 0;
    mTable_d68.mnElementCount = 0;

    // tear down the +0xe08 rbtree
    {
        cRBTree* pTree = &mTree_e08;
        cRBNode* pNode = (cRBNode*)pTree->mAnchor.mpParent;
        pTree->mAnchor.mpParent = (cRBNode*)&pTree->mAnchor;
        if (pNode != (cRBNode*)&pTree->mAnchor) {
            for (;;) {
                cRBNode* pNext = (cRBNode*)pNode->mpRight;
                if (pNode->mpRight == 0) {
                    cRBNode* pParent = (cRBNode*)pNode->mpParent;
                    if ((cRBNode*)pNode == (cRBNode*)pParent->mpParent)
                        break;
                    pNode->mpRight = 0;
                    pNode = pParent;
                    pNode = (cRBNode*)&pTree->mAnchor;
                    if (pNode != (cRBNode*)pTree->mAnchor.mpParent)
                        ;
                } else {
                    pNode = pNext;
                }
            }
        }
    }

    mVec_e24.clear();

    mSub_0c0.FUN_00bfcae0();
    mSub_5a8.FUN_00bfcae0();

    FUN_00c151b0();
}

// @ 0x00c1d120
cVObj* cSPCreatureBase_s00c1_c9f0::FUN_00c1d120(u32 a, u32 b)
{
    cVObj* local = 0;
    cEffectsMgr* eff = EffectsManagerPtr();
    if (!eff->e2c((i32)a, 0, (void**)&local))
        return 0;

    cMatrix3_s00c1_c9f0 mat;
    u16  uFlag0 = 0;
    u16  uFlag1 = 0;
    u16  uFlag2 = 0;
    u16  uFlag3 = 0;
    f32  fX = DAT_0168d988;
    f32  fY = DAT_0168d98c;
    f32  fZ = DAT_0168d990;
    f32  fW = _HK_REAL_ONE;
    u32  uArg = b;

    mTable_cc8.FUN_00b76460(&b);
    (void)uArg;

    mat.Assign(&DAT_0168d964);

    void* pObj = (void*)((char*)this + 0xc0);
    u32* pFree = (u32*)(*(void**)((char*)pObj));
    (void)pFree;
    {
        cVObj* sub = &mSub_0c0;
        cVObj* p1 = (cVObj*)*(void**)sub;
        (void)p1;
        // build the parameter block and notify the object
        u32 params[6];
        params[0] = (u32)uFlag0 | ((u32)uFlag1 << 16);
        params[1] = *(u32*)&fX;
        params[2] = *(u32*)&fY;
        params[3] = *(u32*)&fZ;
        params[4] = *(u32*)&fW;
        params[5] = 0;
        uFlag2 |= 4;
        uFlag3 += 1;
        local->v18(params);
    }

    local->v04();
    return local;
}

// @ 0x00c1d290
cVObj* cSPCreatureBase_s00c1_c9f0::FUN_00c1d290(u32 a)
{
    cVObj* local = 0;
    cEffectsMgr* eff = EffectsManagerPtr();
    if (!eff->e2c((i32)a, 0, (void**)&local))
        return 0;

    mTable_cc8.FUN_00b76460(&a);

    cMatrix3_s00c1_c9f0 mat;
    mat.Assign(&DAT_0168d964);

    {
        cVObj* sub = &mSub_0c0;
        (void)sub;
        u32 params[6];
        params[0] = 0;
        params[1] = *(u32*)&DAT_0168d988;
        params[2] = *(u32*)&DAT_0168d98c;
        params[3] = *(u32*)&DAT_0168d990;
        params[4] = *(u32*)&_HK_REAL_ONE;
        params[5] = 0;
        local->v18(params);
    }

    local->v04();
    return local;
}

// @ 0x00c1d400
cVObj* cSPCreatureBase_s00c1_c9f0::FUN_00c1d400(u32 a, u32 b)
{
    cVObj* r = FUN_00c1d120(a, b);
    if (r != 0)
        r->v08(0);
    return r;
}

// @ 0x00c1d430
cVObj* cSPCreatureBase_s00c1_c9f0::FUN_00c1d430(u32 a)
{
    cVObj* r = FUN_00c1d290(a);
    if (r != 0)
        r->v08(0);
    return r;
}

// @ 0x00c1d460
cVObj* cSPCreatureBase_s00c1_c9f0::FUN_00c1d460(u32 a, u32 b)
{
    cVObj* local = 0;
    cEffectsMgr* eff = EffectsManagerPtr();
    if (!eff->e2c((i32)a, 0, (void**)&local))
        return 0;

    mTable_d68.FUN_00b76460(&b);

    cMatrix3_s00c1_c9f0 mat;
    mat.Assign(&DAT_0168d964);

    {
        u32 params[6];
        params[0] = 0;
        params[1] = *(u32*)&DAT_0168d988;
        params[2] = *(u32*)&DAT_0168d98c;
        params[3] = *(u32*)&DAT_0168d990;
        params[4] = *(u32*)&_HK_REAL_ONE;
        params[5] = 0;
        local->v18(params);
    }

    local->v08(0);
    local->v04();
    return local;
}

// @ 0x00c1d5e0
i32 cSPCreatureBase_s00c1_c9f0::FUN_00c1d5e0(char a, u32 b, u32 c)
{
    if (a != 0) {
        cVObj* p = FUN_00c14e70(c);
        if (p != 0 && p->v10() != 0)
            return 0;
        FUN_00c17350(c, 0);
        return (i32)FUN_00c1d460(b, c);
    }
    FUN_00c17350(c, 0);
    return 0;
}

// @ 0x00c1d640
uint cSPCreatureBase_s00c1_d640::FUN_00c1d640(const char* name, int mode, uint id)
{
    AudioSystem* audio = GetSystemAT();
    if (!audio)
        return id;

    int parts[255];
    uint count = QueryCreatureBodyParts(this, mode, parts, 0xff);
    if (count == 0 || id != 0) {
        id = 0;
    } else {
        ++mSoundCounter;
        id = mSoundCounter;
        if (id != 0) {
            if (mSoundIds.mpEnd < mSoundIds.mpCapacity) {
                uint* p = mSoundIds.mpEnd++;
                if (p)
                    *p = id;
            } else {
                mSoundIds.DoInsertValue(mSoundIds.mpEnd, id);
            }
        }
    }

    for (uint i = 0; i < count; ++i) {
        BodyPart_s00c1_d640* part = &mpAnim->mpModel->mpParts[parts[i]];
        if (!part->mpData->mpSound)
            continue;

        AudioSystem* sys = GetSystemAT();
        uint handle = sys ? sys->s24() : 0;
        int partIndex = parts[i];

        SoundNode* root = mSoundMap.mpParent;
        SoundNode* parent = (SoundNode*)&mSoundMap;
        while (root) {
            parent = root;
            if (id < root->mKey)
                root = root->mpRight;
            else
                root = root->mpLeft;
        }
        int side = 0;
        if (parent != (SoundNode*)&mSoundMap && !(id < parent->mKey))
            side = 1;

        SoundNode* node = (SoundNode*)SimAlloc(
            0x1c, "Simulator", 0, 0,
            "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
            0xd1);
        if (node) {
            node->mKey = id;
            node->mHandle = handle;
            node->mPart = partIndex;
        }
        RBTreeInsert(node, parent, &mSoundMap, side);
        ++mSoundMapCount;

        audio->s38(0x3475365);
        audio->s44(0x347537e, name, 0);
        audio->s40(0x3475385, handle);
        audio->s40(0x39f9e01, (uint)(uintptr_t)part->mpData->mpSound);

        Vec3_s00c1_d640 pos = RotateOffset(mpAnim->mpModel->mRotation, part->mOffset);
        pos.x += mpAnim->mpModel->mPosition.x;
        pos.y += mpAnim->mpModel->mPosition.y;
        pos.z += mpAnim->mpModel->mPosition.z;
        audio->s3c(0x3475391, pos.x);
        audio->s3c(0x3475395, pos.y);
        audio->s3c(0x3475398, pos.z);

        float scale = mpAnim->mpModel->mScale;
        float rx = part->mpData->mRadiusX * scale;
        float ry = part->mpData->mRadiusY * scale;
        float rz = part->mpData->mRadiusZ * scale;
        float radius = sqrtf(rx * rx + (rz * rz + ry * ry));
        audio->s3c(0x39f9e0f, radius + radius);

        audio->s40(0x39f9e08, CallVd8());
        audio->s40(0x44d6399, (mFlagsB58 >> 9) & 1);
        audio->s40(0x44d63a2, mFieldB34 == 1);
        audio->s40(0x48def6d, (uint)Flag388() & 0xff);
        audio->s40(0x3475381, 0);
        audio->s58();
    }
    return id;
}

// @ 0x00c1db40
bool cSPCreatureBase_s00c1_d640::StartIndependentSound(const char* name, const Vec3_s00c1_d640* pos, UIntVec* out)
{
    AudioSystem* audio = GetSystemAT();
    if (!audio)
        return false;

    int parts[255];
    uint count = QueryCreatureBodyParts(this, 2, parts, 0xff);

    // Clear the caller-supplied handle vector (the original emits a zero-length
    // memcpy for the element destructor pass, then resets end to begin).
    memcpy(out->mpBegin, out->mpEnd, 0);
    out->mpEnd = out->mpBegin;

    for (uint i = 0; i < count; ++i) {
        BodyPart_s00c1_d640* part = &mpAnim->mpModel->mpParts[parts[i]];
        if (!part->mpData->mpSound)
            continue;

        uint handle = audio->s20();
        out->push_back(handle);

        audio->s38(0x3475365);
        audio->s44(0x347537e, name, 0);
        audio->s40(0x3475385, handle);
        audio->s40(0x39f9e01, (uint)(uintptr_t)part->mpData->mpSound);

        if (pos->x == g_168d910 && pos->y == g_168d914 && pos->z == g_168d918) {
            audio->s40(0x3475389, 0);
        } else {
            audio->s40(0x3475389, 1);
            audio->s3c(0x3475391, pos->x);
            audio->s3c(0x3475395, pos->y);
            audio->s3c(0x3475398, pos->z);
        }

        float scale = mpAnim->mpModel->mScale;
        float rx = part->mpData->mRadiusX * scale;
        float ry = part->mpData->mRadiusY * scale;
        float rz = part->mpData->mRadiusZ * scale;
        float radius = sqrtf(rx * rx + (rz * rz + ry * ry));
        audio->s3c(0x39f9e0f, radius + radius);

        audio->s40(0x39f9e08, CallVd8());
        audio->s40(0x44d6399, 0);
        audio->s40(0x44d63a2, 1);
        audio->s40(0x48def6d, 0);
        audio->s40(0x3475381, 0);
        audio->s58();
    }
    return count != 0;
}

// @ 0x00c1de20
uint Creature::ChooseAbility(AbilityMask* mask, Creature* target, float dist, bool flag)
{
    uint best = (uint)-1;
    if (mActiveAbility != (uint)-1)
        return best;

    if (mask) {
        mask->w[2] &= 0xfffffdff;
        mask->w[0] &= 0xdfffffff;
    }
    float scale = GetScale(0, this);

    Creature* tc = target ? target->Query(0xd0036e08) : 0;
    bool nearTarget = false;
    if (tc) {
        TypeObj* owner;
        TypeHolder* holder = tc->mpTypeHolder;
        if (holder && (owner = holder->Get()) != 0 && owner->GetType() == kCombatantTypeId) {
        } else {
            owner = 0;
        }
        if ((void*)owner == (void*)this) {
            Body_s00c1_d640* tb = &tc->mBody;
            Body_s00c1_d640* mb = &mBody;
            float d = DistanceBetweenBodies(mb->GetPos(), mb->GetRadius(), tb->GetBodyPos(), tb->GetRadius(), true);
            if (dist < 5.0f || d < 5.0f)
                nearTarget = true;
        }
    }

    uint count = GetAbilityCount();
    float bestScore = 0.0f;
    bool bestReady = false;
    Ability* bestAbility = 0;
    float bestMargin = dist;
    UIntVector cands;
    cands.mpBegin = 0; cands.mpEnd = 0; cands.mpCapacity = 0;
    for (uint i = 0; i < count; ++i) {
        Entry* e = &mpEntries[i];
        Ability* a = GetAbility(i);
        if (mask && !mask->test(a->id))
            continue;
        if (tc) {
            if (!((tc->IsUpper() && a->id == 0x3d) || a->m120 == -1)) {
                if (tc->mCooldownCount > 0)
                    continue;
            }
        }
        if (a->mKind != 1 || a->mbBusy || !(mEnergy >= a->f104))
            continue;

        float lo = (a->ff4 + a->fa8) * scale;
        float hi = a->GetBound(IsUpper()) * scale;
        bool inRange = lo >= dist && dist >= hi;
        bool noBound = lo < 10.0f && a->GetBound(IsUpper()) == 0.0f;
        float score = (a->f84 + a->f3c) / a->f9c;
        bool ready = e->f4 >= 1.0f;
        uint id = a->id;
        switch (id) {
        case 0x1f:
            if (inRange && ready) score = gChargeScale * score;
            break;
        case 0x48:
            if (inRange && ready) score = 90.0f;
            break;
        case 0x4b:
            if (inRange && ready) score = 100.0f;
            else score = 0.0f;
            break;
        }
        if (!noBound && id != 0x1f)
            score = gBoundScale * score;

        float penalty = 0.0f;
        float margin = dist;
        if (!inRange) {
            float gap = 0.0f;
            float w = 1.0f;
            if (dist > lo) {
                gap = dist - lo;
                margin = lo;
            } else if (hi > dist) {
                gap = hi - dist;
                margin = hi;
                w = 0.5f;
            }
            float norm = mbNoBonus ? F00c0ce80(2, 1) + 10.0f : F00c0ce80(2, 0);
            penalty = gap / norm * w;
        }

        if ((noBound && !flag) || (inRange && ready) || (!nearTarget && !flag)) {
            score = score - penalty * score * 0.1f;
            if (score > bestScore || !bestAbility) {
                bestMargin = margin;
                bestScore = score;
                best = i;
                bestReady = ready;
                bestAbility = a;
            }
            cands.push_back(i);
        }
    }

    if (bestMargin == dist && !bestReady) {
        float top = 0.0f;
        int n = (int)(cands.mpEnd - cands.mpBegin);
        for (int j = 0; j < n; ++j) {
            uint idx = cands.mpBegin[j];
            Entry* e = &mpEntries[idx];
            Ability* a = GetAbility(idx);
            float lo = (a->ff4 + a->fa8) * scale;
            float hi = a->GetBound(IsUpper()) * scale;
            bool inRange = lo >= dist && dist >= hi;
            bool ready = e->f4 >= 1.0f;
            if (inRange && ready) {
                float extra = bestAbility ? bestAbility->f104 : 0.0f;
                if (mEnergy > a->f104 + extra) {
                    float s = (a->f84 + a->f3c) / a->f9c;
                    if (s > top) {
                        top = s;
                        best = idx;
                    }
                }
            }
        }
    }
    return best;
}

#define PV16 PV8 PV8
#define CHECK_OFFSET(T, m, off) typedef char PVCAT(check_, __COUNTER__)[offsetof(T, m) == (off) ? 1 : -1]
namespace sl_s00c1_e460 {
extern float g_1582ef0;      // 0x01582ef0 (attack range slack)
extern float g_1582ef4;      // 0x01582ef4

float __cdecl FUN_00d38a30(int nWhich, void* pCreature);            // 0x00d38a30
float __cdecl FUN_00d99ac0(void* pA, void* pB, bool bFlags);        // 0x00d99ac0 (distance)
unsigned int FUN_00c0b380(void* pCreature, void* pAbility);   // 0x00c0b380

// Animation context-target query: fills pOut with up to nMax noun ids of the records that match
// the 16-byte query record, returns how many were written.
int FUN_009b2340(void* pOut, int nMax, unsigned int nModel, void* pRecord,
                            int nA, int nB);                        // 0x009b2340


// Four-character animation result tags / noun ids reached through the target.
enum {
    kNounTribeTool = 0x018c8f0c,
    kNounTribeHut  = 0x01e4daae,
};

enum {
    kAnimNone = 0x02c39370,
};

struct cIdVector {
    int* mpBegin;      // +0x00
    int* mpEnd;        // +0x04
    int* mpCapacity;   // +0x08
};

// 16-byte animation context query record handed to EvaluateContextTargetQuery.
struct ContextQueryRecord {
    unsigned int mKind;      // +0x00
    unsigned int mTag;       // +0x04
    unsigned int mField08;   // +0x08
    unsigned int mField0c;   // +0x0c
};

class cGameData {
public:
    PV8
    virtual uint32_t GetNounID();                                   // 0x20
};

// The spatial/locomotive sub-object living at +0xc0 of a creature.
class cSpatialObject {
public:
    PV16 PV2
    virtual bool CanAttack();                                       // 0x48
};

// Target interface held at +0xe7c.
class IQueryTarget {
public:
    PV2
    virtual void* ToSpatialObject();                                // 0x08
    virtual cGameData* ToGameData();                                // 0x0c
    PV16 PV2 PV
    virtual void* Query(unsigned int nID);                          // 0x5c
};

// Animated-creature payload at +0xb54 (only the model pointer is needed here).
class cAnimatedCreature {
public:
    char pad00[0x17c];
    void* mpModel;     // +0x17c
};

// The per-frame ability record returned by GetAbility() (vtable slot 0xb4).
class cCreatureAbility {
public:
    unsigned int GetAnimationID(unsigned int nIndex);               // 0x004d3cd0
    /* +0x00 */ char pad00[8];
    /* +0x08 */ int mType;
    /* +0x0c */ char pad0c[0x48 - 0x0c];
    /* +0x48 */ cIdVector mAnimIds;
    /* +0x54 */ char pad54[0x78 - 0x54];
    /* +0x78 */ unsigned int mTribeAnimationID;
    /* +0x7c */ char pad7c[0xa8 - 0x7c];
    /* +0xa8 */ float mRangeA8;
    /* +0xac */ char padac[0xf4 - 0xac];
    /* +0xf4 */ float mRangeF4;
    /* +0xf8 */ unsigned int mAnimationID;
    /* +0xfc */ char padfc[0x100 - 0xfc];
    /* +0x100 */ unsigned char mbFlags100;
};
CHECK_OFFSET(cCreatureAbility, mType, 0x08);
CHECK_OFFSET(cCreatureAbility, mAnimIds, 0x48);
CHECK_OFFSET(cCreatureAbility, mRangeA8, 0xa8);
CHECK_OFFSET(cCreatureAbility, mRangeF4, 0xf4);
CHECK_OFFSET(cCreatureAbility, mAnimationID, 0xf8);
CHECK_OFFSET(cCreatureAbility, mbFlags100, 0x100);

// Ability override record (kept at +0xe84).
class cAbilityOverride {
public:
    char pad00[0x388];
    unsigned char mbFlags388;   // +0x388
};

class SpeciesData {
public:
    cIdVector* GetAnimationList(void* pAnimContext);                 // 0x004d9030
};

namespace SP {

class cSPCreatureBase {
public:
    PV16 PV16 PV8 PV4
    virtual int GetAbilitiesCount();                                          // 0xb0
    virtual cCreatureAbility* GetAbility(int nIndex);                         // 0xb4

    int  BeginAttack(unsigned int nIndex, bool bA, bool bB);                  // 0x00c196a0
    void CancelAttackAnimation(int nIndex);                                   // 0x00c073a0
    unsigned int InterruptAnimation(unsigned int nAnimationID, int nA, int nB);   // 0x00c12310
    unsigned int InterruptAnimationWithTarget(unsigned int nAnimationID, void* pTarget,
                                              int nA, int nB);                // 0x00c149c0

    /* +0x000 */ char pad000[0xc0 - 0x04];
    /* +0x0c0 */ cSpatialObject mBody;
    /* +0x0c4 */ char pad0c4[0xb20 - 0x0c4];
    /* +0xb20 */ SpeciesData* mpSpecies;
    /* +0xb24 */ char pad0b24[0xb4c - 0xb24];
    /* +0xb4c */ void* mpBehaviorData;
    /* +0xb50 */ char pad0b50[4];
    /* +0xb54 */ cAnimatedCreature* mpAnimatedCreature;
    /* +0xb58 */ unsigned int mGeneralFlags;
    /* +0xb5c */ unsigned char mbFlags5c;
    /* +0xb5d */ char pad0b5d[0xe7c - 0xb5d];
    /* +0xe7c */ IQueryTarget* mpTargetHolder;
    /* +0xe80 */ char pad0e80[0xe84 - 0xe80];
    /* +0xe84 */ cAbilityOverride* mpOverride;
    /* +0xe88 */ char pad0e88[0xe8c - 0xe88];
    /* +0xe8c */ unsigned int mCurrentAttackIdx;
    /* +0xe90 */ unsigned int mCurrentAttackAnimId;
    /* +0xe94 */ float mRushDistanceLeft;
    /* +0xe98 */ char pad0e98[0xeac - 0xe98];
    /* +0xeac */ int mAttackState;

    unsigned int Attack(unsigned int nAttackIndex, unsigned int* pnAnimationID);
};
CHECK_OFFSET(cSPCreatureBase, mBody, 0xc0);
CHECK_OFFSET(cSPCreatureBase, mpSpecies, 0xb20);
CHECK_OFFSET(cSPCreatureBase, mpAnimatedCreature, 0xb54);
CHECK_OFFSET(cSPCreatureBase, mbFlags5c, 0xb5c);
CHECK_OFFSET(cSPCreatureBase, mpTargetHolder, 0xe7c);
CHECK_OFFSET(cSPCreatureBase, mpOverride, 0xe84);
CHECK_OFFSET(cSPCreatureBase, mCurrentAttackAnimId, 0xe90);
CHECK_OFFSET(cSPCreatureBase, mRushDistanceLeft, 0xe94);
CHECK_OFFSET(cSPCreatureBase, mAttackState, 0xeac);

// @ 0x00c1e460
unsigned int cSPCreatureBase::Attack(unsigned int nAttackIndex, unsigned int* pnAnimationID)
{
    unsigned int nAbilityIndex = BeginAttack(nAttackIndex, true, false);
    if (nAbilityIndex != (unsigned int)-1) {
        int nVariant;
        IQueryTarget* pTarget = mpTargetHolder;
        cCreatureAbility* pAbility = GetAbility(nAbilityIndex);

        if (pAbility->mRangeF4 > ::kZero && pAbility->mAnimationID != (unsigned int)-1) {
            mCurrentAttackAnimId = pAbility->mAnimationID;
            float fScale = FUN_00d38a30(0, this);
            mRushDistanceLeft = (pAbility->mRangeA8 + pAbility->mRangeF4) * fScale;
            mRushDistanceLeft += g_1582ef0;
            mRushDistanceLeft += g_1582ef4;
            mbFlags5c = pAbility->mbFlags100;
        } else if (pAbility->mType == 0x2b) {
            if (pTarget == NULL)
                goto done;
            {
                void* pSpatial = pTarget->ToSpatialObject();
                float fDistance = FUN_00d99ac0(&mBody, pSpatial, true);
                if (FUN_00d38a30(0, this) * pAbility->mRangeF4 < fDistance) {
                    mCurrentAttackAnimId = kAnimNone;
                    goto done;
                }
            }
            {
                unsigned int nCount =
                    (unsigned int)(pAbility->mAnimIds.mpEnd - pAbility->mAnimIds.mpBegin);
                if (nCount > 0) {
                    unsigned int nIndex = ::sMathRandom.RandomUint32Uniform(nCount);
                    mCurrentAttackAnimId = pAbility->GetAnimationID(nIndex);
                } else {
                    unsigned int nIndex = 0;
                    mCurrentAttackAnimId = pAbility->GetAnimationID(nIndex);
                }
            }
        } else {
            if (mpOverride != NULL && mpOverride->mbFlags388 != 0) {
                mCurrentAttackAnimId = FUN_00c0b380(this, pAbility);
                goto done;
            }
            {
                unsigned int nCount =
                    (unsigned int)(pAbility->mAnimIds.mpEnd - pAbility->mAnimIds.mpBegin);
                unsigned int nIndex = (nCount > 0) ? ::sMathRandom.RandomUint32Uniform(nCount) : 0;
                mCurrentAttackAnimId = pAbility->GetAnimationID(nIndex);
            }
            if (pTarget == NULL)
                goto done;
        }
        {
            cGameData* pGameData = pTarget->ToGameData();
            unsigned int nNounID = pGameData->GetNounID();
            if ((nNounID == kNounTribeTool || nNounID == kNounTribeHut)
                && pAbility->mTribeAnimationID != 0)
                mCurrentAttackAnimId = pAbility->mTribeAnimationID;
        }

    done:
        {
            nVariant = -1;
            if (mBody.CanAttack() && mAttackState == 2) {
                int nType = pAbility->mType;
                switch (nType) {
                case 0x1e: {
                    cIdVector* pAnimList = mpSpecies->GetAnimationList(mpAnimatedCreature);
                    unsigned int nCount =
                        (unsigned int)(pAnimList->mpEnd - pAnimList->mpBegin);
                    nVariant = pAnimList->mpBegin[::sMathRandom.RandomUint32Uniform(nCount)];
                    break;
                }
                case 0x21: {
                    unsigned int aResults[0xff];
                    ContextQueryRecord record = { 0, 0x73726b73, 0, 0 };
                    unsigned int nFound = FUN_009b2340(aResults, 0xff,
                                                       *(unsigned int*)mpAnimatedCreature->mpModel,
                                                       &record, 0, 0);
                    if (nFound > 0)
                        nVariant = aResults[::sMathRandom.RandomUint32Uniform(nFound)];
                    break;
                }
                }
            }

            unsigned int nResult;
            void* pQueryResult = (pTarget != NULL) ? pTarget->Query(0x1186577) : NULL;
            if (pQueryResult != NULL)
                nResult = InterruptAnimationWithTarget(mCurrentAttackAnimId, pQueryResult, -1, nVariant);
            else
                nResult = InterruptAnimation(mCurrentAttackAnimId, nVariant, 0);

            if (pnAnimationID != NULL)
                *pnAnimationID = nResult;
            CancelAttackAnimation(nAbilityIndex);
        }
    }
    return nAbilityIndex;
}

}  // namespace SP

}  // namespace sl_s00c1_e460
#undef CHECK_OFFSET
#undef PV16

// @ 0x00c1f580
cCreatureDataBlock* cCreatureDataBlock::FUN_00c1f580(void* param2, void* param3)
{
    eastl_fixed_pool_base pool;

    pool.mpHead = 0;
    pool.init(mBuffer4c, 0x30, 0xc, 4, 0);

    pool.mpField08 = mBuffer4c;
    pool.mpField0c = mPad7c;
    pool.mCount10  = 0xc;
    pool.mpField14 = &mpField34;

    void* resource = FUN_00921340(5);
    FUN_00c142a0(resource, param2, &param3, &param3, param3, &param3, &pool);

    mRange10 = cRange(10000.0f, 2.0f);
    mField18 = 0;

    uint used = pool.FUN_009213c0(mpField0c);
    if (mCount08 < used) {
        FUN_00b5d220(used);
    }

    return this;
}

// @ 0x00c1f650
void cCurvePointVector::PushBackDefault()
{
    cCurvePoint* p = mpEnd;

    if (p < mpCapacity) {
        mpEnd = p + 1;
        if (p != 0) {
            new (p) cCurvePoint;
        }
        return;
    }

    cCurvePoint value;
    InsertValue(p, &value);
}

class cUIntVector_s00c1_f580 {
public:
    uint* mpBegin;    // +0x00
    uint* mpEnd;      // +0x04
    uint* mpCapacity; // +0x08
    uint* mpFixed;    // +0x10

    void insert(void* position, const uint* first, const uint* last, uint); // 0x00c1f6d0
};
extern "C" void* __cdecl operator_new_fun_00f473a0(uint size, const char* name, int a3, int a4, const char* file, int line);
extern "C" void  __cdecl operator_delete_array(void* p);
extern "C" void  __cdecl FUN_00bc4030(void* a, const void* b, const void* c);

// @ 0x00c1f6d0
void cUIntVector_s00c1_f580::insert(void* position, const uint* first, const uint* last, uint)
{
    if (first == last) {
        return;
    }

    uint* pEnd = mpEnd;
    const uint count = (uint)(last - first);

    if (count <= (uint)(mpCapacity - pEnd)) {
        // The run fits inside the existing block.
        const uint after = (uint)(pEnd - (uint*)position);

        if (after <= count) {
            // The run reaches past the old end: the input tail moves into the
            // free room, then the old tail slides up behind it.
            FUN_00bc4030((uint*)first + after, (uint*)last, pEnd);
            mpEnd = pEnd + (count - after);

            memmove((void*)mpEnd, (const void*)position, (size_t)((char*)pEnd - (char*)position));
            mpEnd = mpEnd + after;

            FUN_00c16090((uint*)first, (uint*)first + after,
                         (uint*)position + after);
        } else {
            // The run fits entirely behind "position": shift the tail right
            // by "count" elements and drop the run into the gap.
            uint* pShift = pEnd - count;
            memcpy(pEnd, pShift, (uint)((char*)pEnd - (char*)pShift));
            mpEnd = pEnd + count;

            memmove((void*)((char*)pEnd - ((char*)pShift - (char*)position)),
                    (const void*)position, (size_t)((char*)pShift - (char*)position));

            FUN_00bc4030((uint*)first, (uint*)last, position);
        }
        return;
    }

    // Grow: allocate a fresh block, splice the three pieces in, then free the
    // old block unless it is the in-place buffer.
    const uint size = (uint)(pEnd - mpBegin);
    uint newCapacity = size * 2;
    if (size == 0) {
        newCapacity = 1;
    }
    uint needed = size + count;
    if (needed < newCapacity) {
        needed = newCapacity;
    }

    uint* pNew = 0;
    if (needed != 0) {
        pNew = (uint*)operator_new_fun_00f473a0(
            needed * 4, "Simulator", 0, 0,
            "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\"
            "UTFKernel\\EASTL\\include\\EASTL/allocator.h",
            0xd1);
    }

    const uint headBytes = (uint)((char*)position - (char*)mpBegin);
    memcpy(pNew, mpBegin, headBytes);
    uint* pDst = (uint*)((char*)pNew + headBytes);

    for (const uint* src = first; src != last; ++src) {
        *pDst++ = *src;
    }

    const uint tailBytes = (uint)((char*)pEnd - (char*)position);
    memcpy(pDst, position, tailBytes);
    uint* pNewEnd = (uint*)((char*)pDst + tailBytes);

    if (mpBegin != 0 && mpBegin != mpFixed) {
        operator_delete_array(mpBegin);
    }

    mpEnd      = pNewEnd;
    mpBegin    = pNew;
    mpCapacity = (uint*)((char*)pNew + needed * 4);
}

// @ 0x00c1f8d0
cSPCreatureBase_s00c1_f580::cSPCreatureBase_s00c1_f580()
: mBundle34()
    , mMotion58()
    , mSampleC0()
    , mTarget590()
    , mCombatant5a8()
    , mField670()
    , mTimerB90()
{
    // ---- behaviour-tree / path state (inside cField670) ------------------
    mField670.mByte4a0 = 0;                 // +0xb10
    mField670.mByte4a8 = 0;                 // +0xb18
    mField670.mField4b0 = 0;                // +0xb20
    mField670.mField4b4 = 0;                // +0xb24
    mField670.mField4b8 = 0;                // +0xb28
    mField670.mField4bc = 0;                // +0xb2c
    mField670.mField4c0 = 0;                // +0xb30
    mField670.mField4c4 = 1;                // +0xb34
    mField670.mpStr4c8 = gEmptyString16;         // +0xb38  (empty wide string)
    mField670.mpStr4cc = gEmptyString16;         // +0xb3c
    mField670.mpStr4d0 = gEmptyString16 + 1;     // +0xb40  (its terminator)
    mField670.mpField4d8 = 0;               // +0xb48
    mField670.mpTree4dc  = 0;               // +0xb4c
    mField670.mpField4e0 = 0;               // +0xb50
    mField670.mField4e4 = 0;                // +0xb54
    mField670.mField4e8 = 0;                // +0xb58
    mField670.mBytes4ec[0] = 0;             // +0xb5c  (four zeroed bools)
    mField670.mBytes4ec[1] = 0;
    mField670.mBytes4ec[2] = 0;
    mField670.mBytes4ec[3] = 0;
    mField670.mBytes4ec[4] = 0;
    mField670.mBytes4ec[5] = 0;
    mField670.mBytes4ec[6] = 0;
    mField670.mBytes4ec[7] = 0;             // +0xb63
    mField670.mByte4f4 = 1;                 // +0xb64
    mField670.mBytes4f5[0] = 0;             // +0xb65
    mField670.mBytes4f5[1] = 0;
    mField670.mBytes4f5[2] = 0;             // +0xb67
    mField670.mByte4f8 = 1;                 // +0xb68
    mField670.mByte4f9 = 0;                 // +0xb69
    mField670.mpField4fc = 0;               // +0xb6c
    mField670.mField500 = 0;                // +0xb70
    mField670.mField504 = 0;                // +0xb74
    mField670.mField50c = gHKRealOne;       // +0xb7c  (standard speed = 1)
    mField670.mField510 = 0.0f;             // +0xb80  (turn rate)
    mField670.mField514 = gField13f1cac;    // +0xb84
    mField670.mField518 = 5;                // +0xb88

    // ---- goal / timer block ----------------------------------------------
    mTimerB90.mField20 = 0.0f;              // +0xbb0
    mTimerB90.mField24 = 0;                 // +0xbb4
    mTimerB90.mField28 = 0.0f;              // +0xbb8
    mTimerB90.mField2c = 100.0f;            // +0xbbc  (v2 = (100,0,0))

    mFieldBe0 = gVecBe0;                    // +0xbe0  (goal.facing)
    mFieldBe4 = gVecBe4;                    // +0xbe4  (movementMode)
    mFieldBe8 = gVecBe8;                    // +0xbe8  (acceptableStopDistance)
    mFieldBec = 0;                          // +0xbec
    mFieldBf0 = 0;                          // +0xbf0
    mFieldBf4 = 0;                          // +0xbf4
    mFieldBf8 = 0;                          // +0xbf8
    mFieldBfc = 0;                          // +0xbfc
    mFieldC00 = 0;                          // +0xc00
    mFieldC04 = 0;                          // +0xc04
    mFieldC08 = 0;                          // +0xc08
    mFieldC0c = 0;                          // +0xc0c

    // ---- neighbour vector with an in-place buffer ------------------------
    mpFixedBegin    = (uint*)mFixedBuffer;                  // +0xc28
    mpFixedEnd      = (uint*)mFixedBuffer;                  // +0xc2c
    mpFixedCapacity = (uint*)(mFixedBuffer + 0x80);         // +0xc30
    mFieldC3c = 0;                                          // +0xc3c

    // ---- the two pooled data blocks --------------------------------------
    mpFieldCc0 = 0;                         // +0xcc0
    mpFieldCc4 = 0;                         // +0xcc4

    char scratch;                           // address-only, as in the image
    mBlockCc8.FUN_00c1f580(&scratch, &scratch);     // +0xcc8
    mBlockD68.FUN_00c1f580(&scratch, &scratch);     // +0xd68

    // ---- reference lists -------------------------------------------------
    mFieldE14 = 0;                          // +0xe14
    mFieldE18 = 0;                          // +0xe18
    mFieldE1c = 0;                          // +0xe1c
    mpFieldE0c = (void*)&mpFieldE0c;         // +0xe0c  (self-referential list head)
    mpFieldE10 = (void*)&mpFieldE0c;         // +0xe10
    mFieldE24 = 0;                          // +0xe24
    mFieldE28 = 0;                          // +0xe28
    mFieldE2c = 0;                          // +0xe2c
    mByteE38  = 0;                          // +0xe38
    mFieldE3c = -1;                         // +0xe3c
    mCurvesE40.mpBegin    = 0;              // +0xe40
    mCurvesE40.mpEnd      = 0;              // +0xe44
    mCurvesE40.mpCapacity = 0;              // +0xe48
    mFieldE54 = 0;                          // +0xe54
    mFieldE58 = gField13ec5b4;              // +0xe58
    mFieldE5c = gField13ec5b4;              // +0xe5c
    mBytesE60[0] = 0;                       // +0xe60
    mBytesE60[1] = 0;
    mBytesE60[2] = 0;
    mBytesE60[3] = 0;
    mFieldE64 = 0;                          // +0xe64
    mByteE68  = 0;                          // +0xe68
    mFieldE6c = 0;                          // +0xe6c
    mFieldE70 = -1;                         // +0xe70
    mFieldE74 = -1;                         // +0xe74
    mByteE78  = 0;                          // +0xe78
    mpFieldE7c = 0;                         // +0xe7c
    mFieldE80 = 0;                          // +0xe80
    mFieldE84 = 0;                          // +0xe84
    mFieldE88 = 0;                          // +0xe88
    mFieldE8c = -1;                         // +0xe8c
    mFieldE90 = -1;                         // +0xe90
    mFieldE94 = 0.0f;                       // +0xe94
    mFieldE98 = 0;                          // +0xe98
    mFieldE9c = 0;                          // +0xe9c
    mFieldEa0 = 0;                          // +0xea0
    mFieldEac = 0;                          // +0xeac
    mFieldEd8 = 0;                          // +0xed8
    mFieldEdc = 0;                          // +0xedc
    mFieldEe0 = 0;                          // +0xee0
    mFieldEe8 = 0;                          // +0xee8
    mFieldEb4 = 0;                          // +0xeb4
    mFieldF0c = 0;                          // +0xf0c
    mFieldF10 = 0;                          // +0xf10
    mFieldF14 = 0;                          // +0xf14
    mFieldF1c = 0;                          // +0xf1c
    mFieldF40 = 0;                          // +0xf40
    mFieldF44 = 0;                          // +0xf44
    mFieldF48 = 0;                          // +0xf48
    mFieldF50 = 0;                          // +0xf50
    mFieldF74 = 0;                          // +0xf74
    mFieldF78 = 0;                          // +0xf78
    mFieldF7c = 0;                          // +0xf7c
    mFieldF80 = gField15716d4;              // +0xf80
    mpFieldF84 = (void*)&mpFieldF84;         // +0xf84  (self-referential list head)
    mpFieldF88 = (void*)&mpFieldF84;         // +0xf88
    mFieldF8c = 0;                          // +0xf8c
    mByteF90  = 1;                          // +0xf90
    mFieldF94 = 0;                          // +0xf94
    mFieldF98 = 0;                          // +0xf98
    mFieldF9c = 0;                          // +0xf9c
    mFieldFa0 = 0;                          // +0xfa0
    mFieldFa4 = 0;                          // +0xfa4

    mSampleC0.mField1f0 = 0;                // +0x2b0
    mSampleC0.mField54  = 1;                // +0x114

    // ---- health / combat numbers out of the property bag -----------------
    uint hashHealth = FNVHash("StandardCreatureHealth", 0x811c9dc5, 1);
    uint hashCombat = FNVHash("Combat", 0x811c9dc5, 1);
    float property = SP_GetPropertyT_float(hashCombat, 0, hashHealth, 100.0f);
    mCombatant5a8.mHealth2c = property;     // +0x5d4
    mCombatant5a8.mCombat38 = property;     // +0x5e0

    gField15716d8 = 0;                      // +0x15716d8
    gField15716dc = -1;                     // +0x15716dc
    gField15716e0 = 0;                      // +0x15716e0
    gField15716e4 = 1;                      // +0x15716e4

    mFieldFa8 = 0.0f;                       // +0xfa8

    mFieldFac = ce80(1, 1);                 // +0xfac
    mFieldFb0 = ce80(2, 1);                 // +0xfb0
    mFieldFb4 = ce80(3, 1);                 // +0xfb4
    mSampleC0.mField1e4 = mFieldFb0;        // +0x2a4  (copy of the middle value)

    mField670.mField51c = 0;                // +0xb8c
    mTimerB90.FUN_00bc3170();

    cPropertyBag* bag = FUN_00b3d310_s00c1_f580();
    mSampleC0.FUN_00c421b0(bag->FUN_00c14350());

    mField670.mpTree4dc = new cBehaviorTreeData;    // +0xb4c

    FUN_00c0b5e0((CB*)this);

    mSampleC0.mFlags50 |= 0x200;            // +0x110
    mField670.mField4e8 &= 0xffff778f;      // +0xb58
}

// 0x00c1fe80 (byte-exact lifted version: match/slices/s00c1fe80/s00c1fe80.cpp)
void cSPCreatureBase_s00c1_f580::FUN_00c1fe80()
{
    mMotion58.FUN_00abf710();
    mTarget590.FUN_00ac0450();
    mBundle34.FUN_00cee7e0();

    vbc();                                  // [this]+0xbc

    FUN_00c0d3a0(this);

    if (mField670.mpTree4dc != 0) {
        mField670.mpTree4dc->FUN_00bcb3d0();
    }
    if (mField670.mpField4d8 != 0) {
        mField670.mpField4d8->FUN_00bc9fe0();
    }

    mCurvesBc0.erase(mCurvesBc0.mpBegin, mCurvesBc0.mpEnd);

    if (mField670.mpField4e0 != 0) {
        cReleaseable* released = mField670.mpField4e0;
        mField670.mpField4e0 = 0;
        released->v04();
    }

    mField670.mField4e8 = 0;

    if (mField670.mpField4fc != 0) {
        FUN_00572020(mField670.mpField4fc, 0);
        mField670.mpField4fc = 0;
    }

    mFieldE3c = -1;
    FUN_00c13340();

    if (mpFieldE7c != 0) {
        cReleaseable* released = mpFieldE7c;
        mpFieldE7c = 0;
        released->v64();
    }

    mField670.mField504 = 0;
    FUN_00c19940(0);

    // The second curve vector is re-based: the tail is relocated and the end
    // pointer advanced by exactly the number of live elements.
    cCurvePoint* curveBegin = mCurvesE40.mpBegin;
    cCurvePoint* curveEnd   = mCurvesE40.mpEnd;
    void* relocated = FUN_00c0ff80(curveEnd, curveEnd, curveBegin);
    mCurvesE40.FUN_00c144b0(relocated, mCurvesE40.mpEnd);

    uint elements = (uint)((char*)curveEnd - (char*)curveBegin) / 0x24;
    mCurvesE40.mpEnd = (cCurvePoint*)((char*)mCurvesE40.mpEnd + elements * 0x24);

    FUN_00c29b00(this);
}

// @ 0x00c1ffb0
void cCreaturePart::FUN_00c1ffb0(char enable)
{
    cSampleC0* samples = (cSampleC0*)((char*)this - 0xd4);
    cSPCreatureBase_s00c1_f580* owner = (cSPCreatureBase_s00c1_f580*)((char*)this - 0x194);

    if (enable != 0) {
        if (mpCurveBeginA2c == mpCurveEndA30) {
            return;
        }

        mField19c &= 0xfffffffb;

        cCurveHolder* holder = samples->FUN_00c41ec0();
        cSampleRef*   ref    = samples->FUN_00c421f0();
        float         limit  = ref->mField0c;

        holder->mPoint14 = *mpCurveBeginA2c;
        if (holder->mField5c == 0) {
            holder->mField5c = 1;
        }

        holder->erase(holder->mpBegin, holder->mpEnd);

        float count = (float)(int)((uint)((char*)mpCurveEndA30
                                         - (char*)mpCurveBeginA2c) / 0x24 - 1);
        float clamped = (count > 0.0f) ? count : 0.0f;
        holder->FUN_00c199e0((int)clamped);

        holder->fn(holder->mpEnd, (void*)((char*)mpCurveBeginA2c + 0x3c),
                   mpCurveEndA30, (int)clamped);

        if (holder->mpBegin != holder->mpEnd) {
            const float kOne = gHKRealOne;
            float value = (kOne > limit) ? kOne : limit;
            holder->mpEnd[-2].mField18 = value;
        }

        owner->cff0(mFieldE08);
        return;
    }

    // Switch the part off: record the disabled state and remember its anchors.
    mField19c = 8;
    gVec168e81c.push_back(mAnchorD4);
    gVec168e81c.push_back(mAnchorE0);
}

// @ 0x00c201a0
void* cCreatureFactory::FUN_00c201a0(char flag, void* param2, void* param3)
{
    cFactoryObject* created;

    if (flag != 0) {
        cFactoryObject* found = (cFactoryObject*)FUN_00c14e70(param3);
        if (found == 0 || !found->o10()) {
            FUN_00c17350(param3, 0);
            created = (cFactoryObject*)FUN_00c1d120(param2, param3);
            if (created != 0) {
                created->o08(0);
            }
            return created;
        }
    } else {
        FUN_00c17350(param3, 0);
    }
    return 0;
}

// @ 0x00c20210
void cCreatureFactory::FUN_00c20210(void* param1, void* param2)
{
    FUN_00c201a0((char)param1, param2, param2);
}

// @ 0x00c22010
int cCombatant_s00c2_2010::FUN_00c22010()
{
    cSPCreatureBase_s00c2_2010* pOwner = (cSPCreatureBase_s00c2_2010*)this;
    int nResult = -1;

    if (pOwner->mp0xE84 == 0 || pOwner->mp0xE84->mb0388 == 0) {
        cAnimatingCreature* pAnim = pOwner->mp0xB54;
        if (pOwner != 0 && pAnim != 0 && pAnim->mp017C != 0) {
            uint32_t aFlags[4] = { 1, g_kBodyParts, 0, 0 };
            int aOut[255];
            int n = FUN_009b2340_s00c2_2010(aOut, 0xff, *(void**)pAnim->mp017C, aFlags, 0, 0);
            if (n != 0)
                nResult = aOut[0];
        }
    } else {
        cFixedVectorInt8 vec;
        vec.mpBegin = vec.mBuffer;
        vec.mpEnd   = vec.mBuffer;
        vec.mpCap   = vec.mBuffer + 8;

        cAnimatingCreature* pAnim = pOwner->mp0xB54;
        if (pOwner != 0 && pAnim != 0 && pAnim->mp017C != 0) {
            uint32_t aFlags[4] = { 1, g_kBodyParts, 0, 0 };
            int aOut[255];
            int n = FUN_009b2340_s00c2_2010(aOut, 0xff, *(void**)pAnim->mp017C, aFlags, 0, 0);
            if (n != 0)
                nResult = aOut[0];
        }

        if (vec.mpEnd < vec.mpCap) {
            *vec.mpEnd = nResult;
            if (vec.mpEnd != 0)
                vec.mpEnd += 1;
        } else {
            vec.DoInsertValue(vec.mpEnd, nResult);
        }
        if (pOwner->mpSpeciesProfile->mf0590 > 0.0f) {
            int* p = (int*)pOwner->mpSpeciesProfile->FUN_004d9050(pOwner->mp0xB54);
            FUN_00c1f6d0(vec.mpEnd, p[0], p[1], nResult);
        }
        if (pOwner->mpSpeciesProfile->mf0594 > 0.0f) {
            int* p = (int*)pOwner->mpSpeciesProfile->FUN_004d9030(pOwner->mp0xB54);
            FUN_00c1f6d0(vec.mpEnd, p[0], p[1], nResult);
        }
        int nCount = (int)(vec.mpEnd - vec.mpBegin);
        nResult = vec.mpBegin[sMathRandom.RandomUint32Uniform((uint32_t)nCount)];
        if (vec.mpBegin != 0 && vec.mpBegin != vec.mBuffer)
            FUN_00f47380(vec.mpBegin);
    }
    return nResult;
}

// @ 0x00c22210
void cSPCreatureBase_s00c2_2010::FUN_00c22210(int nAge)
{
    mn0xB34 = nAge;
    FUN_00c21bf0(1, 1);
    this->mSub58.vIdx13();
}

// @ 0x00c22240
void cSPCreatureBase_s00c2_2010::FUN_00c22240()
{
    float fMax = this->GetMaxHealth();
    float fRatio = this->mf0x38 / fMax;
    mn0xB34 = 1;
    FUN_00c21bf0(1, 1);
    this->mSub58.vIdx13();
    float fScale = this->vIdx32(0);
    this->lo40(fScale);
    ((cLocoWrapper*)FUN_00b3d310())->FUN_00b48770(this, 1);
    float f = this->GetMaxHealth() * fRatio;
    this->SetHealth(f);
    this->mb0x89 = 1;
    ((cObj0xB48*)mp0xB48)->FUN_00bc9fe0();
}

// @ 0x00c222f0
void cSPCreatureBase_s00c2_2010::FUN_00c222f0(cSpeciesProfile_s00c2_2010* pNew)
{
    cSpeciesProfile_s00c2_2010* pOld = mpSpeciesProfile;
    mpSpeciesProfile = pNew;

    bool bDiff;
    uint32_t nBaseline = mn0xB24;
    if (pOld == pNew && (pNew == 0 || pNew->mn053C == nBaseline))
        bDiff = false;
    else
        bDiff = true;

    bool bSame = (pOld == pNew);

    if (pNew != 0) {
        mn0xB24 = pNew->mn053C;
        mKey0xB28.mA = ((uint32_t*)&pNew->mf0504)[0];
        mKey0xB28.mB = ((uint32_t*)&pNew->mf0504)[1];
        mKey0xB28.mC = ((uint32_t*)&pNew->mf0504)[2];
    } else {
        cSpeciesManager* mgr = (cSpeciesManager*)FUN_00401090();
        cSpeciesProfile_s00c2_2010* p = mgr->GetAvatarProfile();
        mpSpeciesProfile = p;
        if (p != 0) {
            mn0xB24 = p->mn053C;
            mKey0xB28.mA = ((uint32_t*)&p->mf0504)[0];
            mKey0xB28.mB = ((uint32_t*)&p->mf0504)[1];
            mKey0xB28.mC = ((uint32_t*)&p->mf0504)[2];
        }
    }

    if (g_168D904 == 0)
        FUN_00c21bf0(bDiff ? 1 : 0, bSame ? 1 : 0);
    this->vIdx43(bDiff ? 1 : 0);

    int idx = FUN_00c0c080(0x25);
    if (this->vIdx45(idx) == 0) idx = FUN_00c0c080(0x54);
    if (this->vIdx45(idx) == 0) idx = FUN_00c0c080(0x4d);
    mn0xE74 = idx;

    int idx2 = FUN_00c0c080(0x1e);
    if (this->vIdx45(idx2) == 0) idx2 = FUN_00c0c080(0x3e);
    if (this->vIdx45(idx2) == 0)
        mn0xE70 = FUN_00c0c080(0x4a);
    else
        mn0xE70 = idx2;
}

// @ 0x00c22470
bool cSPCreatureBase_s00c2_2010::FUN_00c22470(void* pArg)
{
    if (mb0xB67 != 0 && mb0x75 == 0)
        return true;

    cSpeciesProfile_s00c2_2010* p1 = ((cSpeciesManager*)FUN_00401090())->GetProfile(mKey0xB28);
    if (FUN_00b183f0(pArg) == 0)
        return false;

    bool b;
    if (mKey0xB28.mA == 0) {
        b = (mb0x75 == 0);
    } else {
        cSpeciesProfile_s00c2_2010* p2 = ((cSpeciesManager*)FUN_00401090())->GetProfile(mKey0xB28);
        if (p1 != p2) {
            FUN_00c222f0(p2);
            b = (mpSpeciesProfile != 0);
        } else {
            mpSpeciesProfile = p2;
            FUN_00c21bf0(1, 1);
            b = (mpSpeciesProfile != 0);
        }
    }
    if (b && mp0xE80 != 0)
        mp0xE84 = (cSpeciesArchetype*)((cSpeciesManager*)FUN_00401090())
                      ->GetSpeciesArchetype(mp0xE80, 0);
    return b;
}

// @ 0x01334ee0
void FUN_01334ee0(void)
{
    g_ScenarioOverridesKey.mnNameHash = FNVHash_s0133_29c0("Scenario_Overrides", 0x811c9dc5, 1);
    g_ScenarioOverridesKey.mnTypeHash = 0x623d3400;
}

// Enter/update/leave callbacks stored in the six creature-action records (retail 0x0168d998).
// 0xc160c0, 0xc0ccc0 and 0xc16100 are defined in this module (FUN_00c160c0, FUN_00c0ccc0, FUN_00c16100_impl).
void __cdecl FUN_00c19e30(void);   // 0x00c19e30  damage-over-time start
void __cdecl FUN_00c10f80(void);   // 0x00c10f80  speed boost start
void __cdecl FUN_00c10fc0(void);   // 0x00c10fc0  speed boost update
void __cdecl FUN_00c11030(void);   // 0x00c11030  speed boost stop
void __cdecl FUN_00c11090(void);   // 0x00c11090  manage speed boost
void __cdecl FUN_00c19ee0(void);   // 0x00c19ee0  update animation target
void __cdecl FUN_00c1a270(void);   // 0x00c1a270  set animation event control
void __cdecl FUN_00c148a0(void);   // 0x00c148a0  apply damage over time
void __cdecl FUN_00c110e0(void);   // 0x00c110e0  disable animation overlay
void __cdecl FUN_013c3550(void);   // 0x013c3550  action-array destructor

// One 0x44-byte action record; SetupAction fills kind/state/sub/f0c and the three callbacks.
struct ActionRecord
{
    void SetupAction(float fMaxTime, void* pStart, void* pUpdate, void* pStop, const char* pName);  // 0x00bc9e30
};

extern char g_ActionRecords[];    // 0x0168d998  six 0x44-byte records

// @ 0x01334f10
void FUN_01334f10(void)
{
    ((ActionRecord*)(g_ActionRecords + 0x00))->SetupAction(FLT_MAX, (void*)&FUN_00c19e30,
        (void*)&FUN_00c160c0, (void*)&FUN_00c0ccc0, "DamageOverTime");
    ((ActionRecord*)(g_ActionRecords + 0x44))->SetupAction(FLT_MAX, (void*)&FUN_00c10f80,
        (void*)&FUN_00c10fc0, (void*)&FUN_00c11030, "SpeedBoost");
    ((ActionRecord*)(g_ActionRecords + 0x88))->SetupAction(FLT_MAX, 0,
        0, (void*)&FUN_00c16100_impl, "ManageBodyEffects");
    ((ActionRecord*)(g_ActionRecords + 0xCC))->SetupAction(FLT_MAX, 0,
        (void*)&FUN_00c11090, (void*)&FUN_00c19ee0, "SetAnimationTarget");
    ((ActionRecord*)(g_ActionRecords + 0x110))->SetupAction(FLT_MAX, 0,
        0, (void*)&FUN_00c1a270, "SetAnimEventControl");
    ((ActionRecord*)(g_ActionRecords + 0x154))->SetupAction(FLT_MAX, 0,
        (void*)&FUN_00c148a0, (void*)&FUN_00c110e0, "DisableAnimationOverlay");
    atexit(&FUN_013c3550);
}

// @ 0x01335000
namespace Simulator {
void InitCreatureBaseAttributes()
{
    {
        Attribute a("mbTeleport", 0x02415ec6, 0xb5d,
                  Read_00ac8750, Write_00ac8780, ReadText_00693090, WriteText_00694fa0,
                  Validate_00b1fbf0, ToXml_0057ce00);
        *(Attribute*)&cCreatureBase_sAttributes[0] = a;
    }
    {
        Attribute a("mbDead", 0x02415ebc, 0xb5e,
                  Read_00ac8750, Write_00ac8780, ReadText_00693090, WriteText_00694fa0,
                  Validate_00b1fbf0, ToXml_0057ce00);
        *(Attribute*)&cCreatureBase_sAttributes[1] = a;
    }
    {
        Attribute a("mbUpdateInteractionEffect", 0x02415ebd, 0xb60,
                  Read_00ac8750, Write_00ac8780, ReadText_00693090, WriteText_00694fa0,
                  Validate_00b1fbf0, ToXml_0057ce00);
        *(Attribute*)&cCreatureBase_sAttributes[2] = a;
    }
    {
        Attribute a("mbUpdateMotiveEffect", 0x02415ebe, 0xb61,
                  Read_00ac8750, Write_00ac8780, ReadText_00693090, WriteText_00694fa0,
                  Validate_00b1fbf0, ToXml_0057ce00);
        *(Attribute*)&cCreatureBase_sAttributes[3] = a;
    }
    {
        Attribute a("mbIsDiseased", 0x0303fb98, 0xb62,
                  Read_00ac8750, Write_00ac8780, ReadText_00693090, WriteText_00694fa0,
                  Validate_00b1fbf0, ToXml_0057ce00);
        *(Attribute*)&cCreatureBase_sAttributes[4] = a;
    }
    {
        Attribute a("mLastInteractionEffect", 0x021d1baa, 0xcc4,
                  Read_00572810, Write_00572840, ReadText_00692ff0, WriteText_00694ee0,
                  Validate_00b1fbf0, ToXml_0057cde0);
        *(Attribute*)&cCreatureBase_sAttributes[5] = a;
    }
    {
        Attribute a("mLastMotiveState", 0x021d1bab, 0xcc0,
                  Read_00572810, Write_00572840, ReadText_00692ff0, WriteText_00694ee0,
                  Validate_00b1fbf0, ToXml_0057cde0);
        *(Attribute*)&cCreatureBase_sAttributes[6] = a;
    }
    {
        Attribute a("mSpeciesKey", 0x03f64a78, 0xb28,
                  Read_00ae3430, Write_00ae3450, ReadText_00693150, WriteText_00695080,
                  Validate_00b1fbf0, ToXml_00ae5720);
        *(Attribute*)&cCreatureBase_sAttributes[7] = a;
    }
    {
        Attribute a("mProfileSeq", 0x02415ec8, 0xb24,
                  Read_00572810, Write_00572840, ReadText_00693090, WriteText_00694f00,
                  Validate_00b1fbf0, ToXml_00675ca0);
        *(Attribute*)&cCreatureBase_sAttributes[8] = a;
    }
    {
        Attribute a("mAge", 0x52773f6f, 0xb34,
                  Read_00572810, Write_00572840, ReadText_00692ff0, WriteText_00694ee0,
                  Validate_00b1fbf0, ToXml_0057cde0);
        *(Attribute*)&cCreatureBase_sAttributes[9] = a;
    }
    {
        Attribute a("mbCasted", 0x024cd902, 0xb67,
                  Read_00ac8750, Write_00ac8780, ReadText_00693090, WriteText_00694fa0,
                  Validate_00b1fbf0, ToXml_0057ce00);
        *(Attribute*)&cCreatureBase_sAttributes[10] = a;
    }
    {
        Attribute a("mpWhoIsInteractingWithMe", 0xb2774021, 0xb50,
                  Read_00b02540, Write_00bca960, ReadText_00c2e4e0, WriteText_00692fb0,
                  Validate_00b6f550, ToXml_00ac8050);
        *(Attribute*)&cCreatureBase_sAttributes[11] = a;
    }
    {
        Attribute a("mbStealthed", 0x06948b64, 0xbb1,
                  Read_00ac8750, Write_00ac8780, ReadText_00693090, WriteText_00694fa0,
                  Validate_00b1fbf0, ToXml_0057ce00);
        *(Attribute*)&cCreatureBase_sAttributes[12] = a;
    }
    {
        Attribute a("mCurrentLoudness", 0xd277405a, 0xb80,
                  Read_00572810, Write_00ac88f0, ReadText_006930b0, WriteText_00694fc0,
                  Validate_00b1fbf0, ToXml_00acbb80);
        *(Attribute*)&cCreatureBase_sAttributes[13] = a;
    }
    {
        Attribute a("mFoodValue", 0x021d1ba5, 0xb84,
                  Read_00572810, Write_00ac88f0, ReadText_006930b0, WriteText_00694fc0,
                  Validate_00b1fbf0, ToXml_00acbb80);
        *(Attribute*)&cCreatureBase_sAttributes[14] = a;
    }
    {
        Attribute a("mbHasBeenEaten", 0x72774074, 0xb5f,
                  Read_00ac8750, Write_00ac8780, ReadText_00693090, WriteText_00694fa0,
                  Validate_00b1fbf0, ToXml_0057ce00);
        *(Attribute*)&cCreatureBase_sAttributes[15] = a;
    }
    {
        Attribute a("mStrengthRating", 0x021d1bac, 0xb88,
                  Read_00572810, Write_00572840, ReadText_00692ff0, WriteText_00694ee0,
                  Validate_00b1fbf0, ToXml_0057cde0);
        *(Attribute*)&cCreatureBase_sAttributes[16] = a;
    }
    {
        Attribute a("mSpeedState", 0x02415eca, 0xf98,
                  Read_00572810, Write_00572840, ReadText_00692ff0, WriteText_00694ee0,
                  Validate_00b1fbf0, ToXml_0057cde0);
        *(Attribute*)&cCreatureBase_sAttributes[17] = a;
    }
    {
        Attribute a("mCreatureName", 0x03d97b19, 0xb38,
                  Read_00ac87c0, Write_00ac87f0, ReadText_00694c80, WriteText_00694c10,
                  Validate_00b1fbf0, ToXml_00acbbc0);
        *(Attribute*)&cCreatureBase_sAttributes[18] = a;
    }
    {
        Attribute a("mCurrentAttackIdx", 0x021d239f, 0xe8c,
                  Read_00572810, Write_00572840, ReadText_00693090, WriteText_00694f00,
                  Validate_00b1fbf0, ToXml_00675ca0);
        *(Attribute*)&cCreatureBase_sAttributes[19] = a;
    }
    {
        Attribute a("mCurrentAttackAnimId", 0x0547c1bf, 0xe90,
                  Read_00572810, Write_00572840, ReadText_00693090, WriteText_00694f00,
                  Validate_00b1fbf0, ToXml_00675ca0);
        *(Attribute*)&cCreatureBase_sAttributes[20] = a;
    }
    {
        Attribute a("mbColorIsIdentity", 0x042a2b0e, 0xb65,
                  Read_00ac8750, Write_00ac8780, ReadText_00693090, WriteText_00694fa0,
                  Validate_00b1fbf0, ToXml_0057ce00);
        *(Attribute*)&cCreatureBase_sAttributes[21] = a;
    }
    {
        Attribute a("mHunger", 0x05501f64, 0xbbc,
                  Read_00572810, Write_00ac88f0, ReadText_006930b0, WriteText_00694fc0,
                  Validate_00b1fbf0, ToXml_00acbb80);
        *(Attribute*)&cCreatureBase_sAttributes[22] = a;
    }
    {
        Attribute a("mHungerDelta", 0x05501f65, 0xbb8,
                  Read_00572810, Write_00ac88f0, ReadText_006930b0, WriteText_00694fc0,
                  Validate_00b1fbf0, ToXml_00acbb80);
        *(Attribute*)&cCreatureBase_sAttributes[23] = a;
    }
    {
        Attribute a("mHungerDelayTimer", 0x04653b60, 0xb90,
                  Read_00ae3470, Write_00ae3490, ReadText_00c2e4e0, WriteText_00692fb0,
                  Validate_00ae3310, ToXml_00ac8050);
        *(Attribute*)&cCreatureBase_sAttributes[24] = a;
    }
    {
        Attribute a("mArchetype", 0x33ace6b5, 0xe80,
                  Read_00572810, Write_00572840, ReadText_00693090, WriteText_00694f00,
                  Validate_00b1fbf0, ToXml_00675ca0);
        *(Attribute*)&cCreatureBase_sAttributes[25] = a;
    }
    {
        Attribute a("mGeneralFlags", 0x051b38ff, 0xb58,
                  Read_00572810, Write_00572840, ReadText_00693090, WriteText_00694f00,
                  Validate_00b1fbf0, ToXml_00675ca0);
        *(Attribute*)&cCreatureBase_sAttributes[26] = a;
    }
    {
        Attribute a("mNoAttackTimer", 0x5242896a, 0xb78,
                  Read_00572810, Write_00ac88f0, ReadText_006930b0, WriteText_00694fc0,
                  Validate_00b1fbf0, ToXml_00acbb80);
        *(Attribute*)&cCreatureBase_sAttributes[27] = a;
    }
    {
        Attribute a("DEPRECATED_mRechargingAbilityBits", 0x0528933e, 0xc18,
                  Read_00aff840, Write_00aff870, ReadText_00692fd0, WriteText_00694ec0,
                  Validate_00b1fbf0, ToXml_00595a70);
        *(Attribute*)&cCreatureBase_sAttributes[28] = a;
    }
    {
        Attribute a("DEPRECATED_mInUseAbilityBits", 0x0535a140, 0xc10,
                  Read_00aff840, Write_00aff870, ReadText_00692fd0, WriteText_00694ec0,
                  Validate_00b1fbf0, ToXml_00595a70);
        *(Attribute*)&cCreatureBase_sAttributes[29] = a;
    }
    {
        Attribute a("mRechargingAbilityBits", 0x076c8f4d, 0xbf8,
                  Read_00c143c0, Write_00c143e0, ReadText_00c2e4e0, WriteText_00692fb0,
                  Validate_00b1fbf0, ToXml_00ac8050);
        *(Attribute*)&cCreatureBase_sAttributes[30] = a;
    }
    {
        Attribute a("mInUseAbilityBits", 0x076c8f46, 0xbec,
                  Read_00c143c0, Write_00c143e0, ReadText_00c2e4e0, WriteText_00692fb0,
                  Validate_00b1fbf0, ToXml_00ac8050);
        *(Attribute*)&cCreatureBase_sAttributes[31] = a;
    }
    {
        Attribute a("mIntentionTowardsTarget", 0x05675535, 0xb74,
                  Read_00c7e9f0, Write_00cd44e0, ReadText_00c2e4e0, WriteText_00692fb0,
                  Validate_00b1fbf0, (ToXmlFunction_t)Validate_00b1fbf0);  // same stub in both slots
        *(Attribute*)&cCreatureBase_sAttributes[32] = a;
    }
    {
        Attribute a("mAbilityStates", 0x0521e608, 0xc28,
                  Read_00c1b8c0, Write_00c0fba0, ReadText_00c2e4e0, WriteText_00692fb0,
                  Validate_00b1fbf0, ToXml_00ca8710);
        *(Attribute*)&cCreatureBase_sAttributes[33] = a;
    }
    {
        Attribute a("mItemInventory", 0x05ef360e, 0xe40,
                  Read_00c21260, Write_00c15f60, ReadText_00c2e4e0, WriteText_00692fb0,
                  Validate_00c0fc10, ToXml_00c19b60);
        *(Attribute*)&cCreatureBase_sAttributes[34] = a;
    }
}
}  // namespace Simulator
