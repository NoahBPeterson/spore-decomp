// src/game/SPGonzago/SPAnimalBehaviorTrees.cpp -- migrated from slice(s) s00d9bee0, s00d8e8d0, s00d8d820, s00d8cbb0, s00d8a2a0, s00d885a0, s00d87620, s00d86a30, s00d85ad0, s00d84c50, s00d83a60, s00d824a0, s00d81940, s00d7ff20, s00d7f790, s00d7e290, s00d7d370, s00d7c3e0, s00d7b550, s00d7a5c0, s00aee680 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPAnimalBehaviorTrees.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "nSPBehaviorTree/behavior_stimuli.h"
#include <stddef.h>
#include "SP/cCombatant.h"
#include "SP/cGameNounManager.h"
#include "SP/cPlanetModel.h"
#include "EA/Random/RandomLinearCongruential.h"
#include "SP/cSPCreatureBase.h"
#include "SP/cSpatialObject.h"
#include "SP/cLocomotiveObject.h"
#include "cSPVector3.h"
#include "nSPBehaviorTree/behavior_memory_block.h"
#include "nSPBehaviorTree/decider.h"
#include "nSPBehaviorTree/decider_state.h"
#include <math.h>
#include "SP/cInteractableObject.h"
#include "SP/cCreatureAbility.h"
#include "SP/cGroupData.h"
#include "SP/cModifier.h"
#include "SP/cOrnament.h"
#include "SP/cSpeciesArchetype.h"
#include "SP/cGameData.h"

// unnamed retail callees and globals (address in the comment)
extern void* gBehaviorResourceBlock;
extern void* gRandomState;

// ---- items of slice s00aee680 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define nullptr 0
class IRefCounted {
public:
    virtual void AddRef();                      // 0x00
    virtual void Release();                     // 0x04
    virtual void v08();
    virtual void* Query(const void* pType);     // 0x0c
    virtual void v10();
};
class cGameNounManager {
public:
    void* GetPlayerCivilization();
    void* GetGameDataVector(void* pFilterA, void* pFilterB, void* pFilterC,
                            void* pFilterD, void* pOutput);
};
class cCity {
public:
    void* GetCivilization();
};
class cILocomotion : public IRefCounted {
public:
    uint8_t mPad14[0x04];                       // 0x14
};
class cUFOLocomotion : public cILocomotion {
public:
    uint32_t* CalculateAvoidanceDestination(uint32_t* pOut, void* pTarget,
                                            void* pUnused, int nFilter);
    uint8_t mPad18[0x08];                       // 0x18
};
class cBehaviorTable {
public:
    void* Find(void* pKey);
    void* FindSubRecord(void* pKey);
    uint32_t* CollectLongVectors(void* pKey);
    void CollectFilters(void* pKey, uint32_t* pMask, uint32_t* pList);

    uint8_t mPad00[0x10];                       // 0x00
    uint8_t mbFlag10;                           // 0x10
    uint8_t mbFlag11;                           // 0x11
    uint8_t mbFlag12;                           // 0x12
    uint8_t mbFlag13;                           // 0x13
    uint8_t mbFlag14;                           // 0x14
    uint8_t mPad15[0x03];                       // 0x15
    uint32_t mnId18;                            // 0x18
    uint32_t mnId1c;                            // 0x1c
    uint32_t mnId20;                            // 0x20
    uint32_t mnId24;                            // 0x24
    uint32_t mnId28;                            // 0x28
    uint8_t mPad2c[0x10];                       // 0x2c
    uint32_t mnEntryBegin3c;                    // 0x3c
    uint32_t mnEntryEnd40;                      // 0x40
};
class cBehaviorSubRecord {
public:
    uint8_t mPad00[0x50];                       // 0x00
    uint32_t mnValue50;                         // 0x50
    uint32_t mnValue54;                         // 0x54
    uint32_t mnValue58;                         // 0x58
    uint32_t mnValue5c;                         // 0x5c
    uint8_t mPad60[0x04];                       // 0x60
    uint8_t mbFlag64;                           // 0x64
    uint8_t mPad65[0x5f];                       // 0x65
};
class cGameDataVector {
public:
    uint8_t mPad00[0x04];                       // 0x00
    void** mpBegin;                             // 0x04
    void** mpEnd;                               // 0x08
};
class cPropertyList {
public:
    virtual void v00();
    virtual void Release();
    virtual void v08();
    virtual void v0c();
};
void* NounManager();
void* LookupResource(void* pKey);
void* LookupResourceRecord(void* pKey);
int32_t GetCivilizationDistance(void* pA, void* pB, int nFlag);
uint32_t GetCivilizationLevel(void* pCivilization);
void* GetPlayerAvatarNouns();
int32_t GetContinentDistance(int a, void* pCity, int b);
int32_t GetDistanceToCity(void* pTarget, int nFilter);
bool IsCivilizationNomadic(void* pCivilization);
void ApplyBehaviorRecordFlags(void* pRecord, void* pKey);
bool MatchesBehaviorFilter(void* pRecord, void* pKey);
void GatherBehaviorValues(void* pOut, void* pKey, int a, int b, int c);
void GatherBehaviorVectors(void* pOut, void* pKey, void* pExtra, int a, int b);
void RandomUint32Uniform(void* pRandom, uint32_t nRange);
extern void* gBehaviorResourceBlock;
extern void* gRandomState;
extern uint32_t gAvoidanceFilterTable[0x40];
// ---- items of slice s00aee680 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern uint32_t gAvoidanceFilterTable[0x40];

// ---- items of slice s00d7a5c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float g_1485720;         // 1.0f
extern float g_1687a00;         // 1.0f
extern float g_1687a0c;         // threshold
extern float g_1473c70;         // 10.0f
extern float g_1486110;         // 5.0f
extern "C" void* __cdecl FUN_00d999d0(void*);
extern "C" void* __cdecl FUN_00d998d0(void*, int);
extern "C" void* __cdecl FUN_00d99a10(void*);
extern "C" void* __cdecl FUN_00d998f0(void*);
extern "C" void* __cdecl FUN_00d99980(void*);
extern "C" void* __cdecl FUN_00d99500(void*);
extern "C" float __cdecl FUN_00d99ac0(void*, void*, int);
extern "C" float __cdecl FUN_00d38a30(int, void*);
extern "C" void* __cdecl FUN_00ac80d0(void*, void*);
extern "C" void* __cdecl FUN_00b3d300();
extern "C" void* __fastcall FUN_00989360(void*);
extern "C" void* __fastcall FUN_00f67d90(void*);
extern "C" int   __fastcall FUN_00c02c70(void*);
typedef unsigned int uint;
struct Stimuli {
  void __thiscall GetAny();                 // 0x00d997e0
};
struct LayoutMgr {
  bool __thiscall LookupA(void*, int, float*);
};
LayoutMgr* __cdecl CreateLayoutManager();
struct BStim {
  char pad[8];
  int  __thiscall Play(int a, int f);       // 0x00bc96a0
  void __thiscall ClearAll(int a, int f);   // 0x00bc98f0
};
struct Iter {
  bool  __thiscall AtBegin();               // 0x00bc9b50
  void* __thiscall Cur();                   // 0x00bc9b10
};
struct TerrainEditor {
  bool __thiscall Sub(int, int*);
};
struct GeneralFlagsB58 {
  unsigned int mBit0 : 1, mBit1 : 1, mBit2 : 1, mBit3 : 1, mBit4 : 1, mBit5 : 1, mBit6 : 1,
               mBit7 : 1, mBit8 : 1, mBit9 : 1, mBit10 : 1, mBit11 : 1, mBit12 : 1, mBit13 : 1,
               mBit14 : 1, mBit15 : 1, mBit16 : 1, mBit17 : 1, mBit18 : 1, mBit19 : 1,
               mBit20 : 1, mBit21 : 1, mBit22 : 1, mBit23 : 1, mBit24 : 1, mBit25 : 1,
               mBit26 : 1, mBit27 : 1, mBit28 : 1, mBit29 : 1, mBit30 : 1, mBit31 : 1;
};
struct StimuliContainer {
  uint pad0_5fc[0x5fc / 4];
  unsigned int mFlags5fc;                   // +0x5fc
};
struct CB {
  char pad0[0x110];
  unsigned int mFlags;                      // +0x110
  char pad114[0x137 - 0x114];
  unsigned char mb137;                      // +0x137
  char pad138[0x5a8 - 0x138];
  char mStim5a8[0x38];                      // +0x5a8
  float m_5e0;                              // +0x5e0
  char pad5e4[0xb20 - 0x5e4];
  void* mpSpecies;                          // +0xb20
  char padb24[0xb4c - 0xb24];
  StimuliContainer* mp_b4c;                 // +0xb4c
  char padb50[0xb58 - 0xb50];
  union {
    unsigned int mGeneralFlags;             // +0xb58
    GeneralFlagsB58 mFlagBitsB58;           // +0xb58
  };
  char padb5c[0xb5e - 0xb5c];
  unsigned char mbDead;                     // +0xb5e

  char* GetStim5a8() { return mStim5a8; }        // inline accessor

  void* __thiscall Get();                        // 00c04590
  int   __thiscall GetSpeciesProfile();          // 00c0bbd0
  void* __thiscall GetTargetAsCreature();        // 00c0ee70
  void  __thiscall ClampHunger(float);           // 00c0b9d0
  bool  __thiscall Prox(void*, float, float);    // 00c0d560
  bool  __thiscall AnimationFinished(int);       // 00c123f0
  bool  __thiscall AnimationFinishedX(int);      // 00c12400
  int   __thiscall InterruptAnimation(int, int, int);  // 00c12310
  void  __thiscall Sub01(int);                   // 00c14750
  bool  __thiscall CheckA(void*);                // 00c0b860
  bool  __thiscall CheckB(void*);                // 00c0b8a0
};
struct St {
  char pad0[4];
  int m4;                                   // +4
  unsigned char m8;                         // +8
  char pad9[0xc - 9];
  int mc;                                   // +0xc
  unsigned char m10;                        // +0x10
  unsigned char m11;                        // +0x11
  unsigned char m12;                        // +0x12
};
#define BS(cb) ((BStim*)((char*)(cb)->mp_b4c + 8))
// ---- items of slice s00d7a5c0 end

// ---- items of slice s00d7b550 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float g_kOne;            // 0x01485720 1.0f
extern float g_kOneHalf;        // 0x01485548 1.5f
extern float g_kTwo;            // 0x01470f1c 2.0f
extern float g_kThree;          // 0x013eb95c 3.0f
extern float g_kFive;           // 0x01486110 5.0f
extern float g_kSixty;          // 0x013ebc4c 60.0f
extern float g_kTiny;           // 0x0147c034 1.52587890625e-05f
extern float    g_fIdleHold;    // 0x01582e9c idle hold time handed to the behaviour context
extern uint32_t g_nGameTime;    // 0x01582e24 game clock, milliseconds
void* __cdecl GetAnimalFromStimulus(void* pStimulus);           // 0x00d99980
void* __cdecl WatchMemoryBlock(void* pStimulus);                // 0x00d999d0
void* __stdcall FUN_00d539d0(void* pCreature);                  // 0x00d539d0 (cPosseSimulator::Instance)
struct Vector3 {
    float x;                    // +0x00
    float y;                    // +0x04
    float z;                    // +0x08
};
class cSPCreatureBase;
class cNearNoun;
class cRandomLinearCongruential {
public:
    uint32_t RandomUint32Uniform(uint32_t nRange);              // 0x00a68fb0
};
extern cRandomLinearCongruential g_mathRandom;                  // 0x01601760
class cSpatialObject {
public:
    virtual void*     v00();            // +0x00
    virtual void*     v04();            // +0x04
    virtual void*     v08();            // +0x08
    virtual void*     v0c();            // +0x0c
    virtual void*     v10();            // +0x10
    virtual void*     v14();            // +0x14
    virtual void*     v18();            // +0x18
    virtual void*     v1c();            // +0x1c
    virtual void*     v20();            // +0x20
    virtual void*     v24();            // +0x24
    virtual void*     v28();            // +0x28
    virtual Vector3*  v2c();            // +0x2c position
    virtual void*     v30();            // +0x30
    virtual float     v34();            // +0x34
    virtual void*     v38();            // +0x38
    virtual void*     v3c();            // +0x3c
    virtual void*     v40();            // +0x40
    virtual void*     v44();            // +0x44
    virtual void*     v48();            // +0x48
    virtual void*     v4c();            // +0x4c
    virtual void*     v50();            // +0x50
    virtual void*     v54();            // +0x54
    virtual float     v58();            // +0x58
    virtual void*     v5c();            // +0x5c
    virtual void*     v60();            // +0x60
    virtual void*     v64();            // +0x64
    virtual void*     v68();            // +0x68
    virtual void*     v6c();            // +0x6c
    virtual void*     v70();            // +0x70
    virtual float     v74();            // +0x74
    virtual void*     v78();            // +0x78
    virtual void*     v7c();            // +0x7c
    virtual void*     v80();            // +0x80
    virtual void*     v84();            // +0x84
    virtual void*     v88();            // +0x88
    virtual void*     v8c();            // +0x8c
    virtual void*     v90();            // +0x90
    virtual void*     v94();            // +0x94
    virtual void*     v98();            // +0x98
    virtual void*     v9c();            // +0x9c
    virtual void*     va0();            // +0xa0
    virtual void*     va4();            // +0xa4
    virtual void*     va8();            // +0xa8
    virtual void*     vac();            // +0xac
    virtual void*     vb0();            // +0xb0
    virtual void*     vb4();            // +0xb4
    virtual void*     vb8();            // +0xb8
    virtual void*     vbc();            // +0xbc
    virtual void*     vc0();            // +0xc0
    virtual void*     vc4();            // +0xc4
    virtual void*     vc8();            // +0xc8
    virtual void*     vcc();            // +0xcc
    virtual void*     vd0();            // +0xd0
    virtual void*     vd4();            // +0xd4
    virtual void*     vd8();            // +0xd8
    virtual void*     vdc();            // +0xdc
    virtual void*     ve0();            // +0xe0
    virtual void*     ve4();            // +0xe4
    virtual void*     ve8();            // +0xe8
    virtual void      vec();            // +0xec
    virtual void*     vf0();            // +0xf0
    virtual void*     vf4();            // +0xf4
    virtual bool      vf8();            // +0xf8

    bool IsNearGoal();                  // 0x00c42e20
};
class cSpatialObjectRanged {
public:
    virtual void*     v00();            // +0x00
    virtual void*     v04();            // +0x04
    virtual void*     v08();            // +0x08
    virtual void*     v0c();            // +0x0c
    virtual void*     v10();            // +0x10
    virtual void*     v14();            // +0x14
    virtual void*     v18();            // +0x18
    virtual void*     v1c();            // +0x1c
    virtual void*     v20();            // +0x20
    virtual void*     v24();            // +0x24
    virtual void*     v28();            // +0x28
    virtual Vector3*  v2c(float fRadius, float fDistance);  // +0x2c
};
class cCombatant {
public:
    virtual void*     v00();            // +0x00
    virtual void*     v04();            // +0x04
    virtual void*     v08();            // +0x08
    virtual void*     v0c();            // +0x0c
    virtual void*     v10();            // +0x10
    virtual void*     v14();            // +0x14
    virtual void*     v18();            // +0x18
    virtual void*     v1c();            // +0x1c
    virtual void*     v20();            // +0x20
    virtual void*     v24();            // +0x24
    virtual void*     v28();            // +0x28
    virtual void*     v2c();            // +0x2c
    virtual void*     v30();            // +0x30
    virtual void*     v34();            // +0x34
    virtual void*     v38();            // +0x38
    virtual void*     v3c();            // +0x3c
    virtual void*     v40();            // +0x40
    virtual void*     v44();            // +0x44
    virtual void*     v48();            // +0x48
    virtual void*     v4c();            // +0x4c
    virtual void*     v50();            // +0x50
    virtual void*     v54();            // +0x54
    virtual float     v58();            // +0x58 health

    void PartialRepair(float fAmount);              // 0x00bfd1a0
    void FUN_00bfc430(int32_t nFlag);               // 0x00bfc430
};
class tStimulus {
public:
    uint32_t mn00;              // +0x00
    uint32_t mn04;              // +0x04
    float    mf08;              // +0x08 timestamp
    int32_t  mn0c;              // +0x0c animation / interaction id
};
class behavior_stimuli {
public:
    void* Play(uint32_t nFlagsA, uint32_t nFlagsB);             // 0x00bc96a0
    void  ClearAll(uint32_t nFlags, int32_t nMask);             // 0x00bc98f0
};
class cBehaviorTree {
public:
    uint32_t        mPad00[2];          // +0x000
    behavior_stimuli mStimuli;          // +0x008

    void FUN_00bcb430();                // 0x00bcb430
};
class cNearNoun {
public:
    Vector3* GetPosition();             // 0x00c6acc0
};
class cAnimalNoun {
public:
    uint32_t       mnVtable;            // +0x000
    uint8_t        mPad04[0x30];        // +0x004
    cSpatialObject mSpatial;            // +0x034
};
class cGameNounManager_s00d7_b550 {
public:
    cSPCreatureBase* GetAvatar();       // 0x00b1fdb0
};
class cPlanetModel {
public:
    void MakeRandomWorldPosition(Vector3* pOut, Vector3* pIn);  // 0x00b81780
};
cPlanetModel* __cdecl PlanetModel(Vector3* pOut, Vector3* pIn); // 0x00b3d350
class cPosseSimulator {
public:
    void RemovePosseSlot();                                     // 0x00d53330
};
class cSPCreatureBase {
public:
virtual void* v00();
virtual void* v04();
virtual void* v08();
virtual void* v0c();
virtual void* v10();
virtual void* v14();
virtual void* v18();
virtual void* v1c();
virtual void* v20();
virtual void* v24();
virtual void* v28();
virtual void* v2c();
virtual void* v30();
virtual void* v34();
virtual void* v38();
virtual void* v3c();
virtual void* v40();
virtual void* v44();
virtual void* v48();
virtual void* v4c();
virtual void* v50();
virtual void* v54();
virtual void* v58();
virtual void* v5c();
virtual void* v60();
virtual void* v64();
virtual void* v68();
virtual void* v6c();
virtual void* v70();
virtual void* v74();
virtual void* v78();
virtual void* v7c();
    virtual void* v80();                                        // +0x080
    virtual void  v84(void* pObject, int32_t nA, int32_t nB);   // +0x084
virtual void* v88();
virtual void* v8c();
virtual void* v90();
virtual void* v94();
virtual void* v98();
virtual void* v9c();
virtual void* va0();
virtual void* va4();
virtual void* va8();
virtual void* vac();
virtual void* vb0();
    virtual int32_t vb4(int32_t nAnimation);                    // +0x0b4
virtual void* vb8();
virtual void* vbc();
    virtual bool  vc0(void* pTarget, float fA, float fB);       // +0x0c0
virtual void* vc4();
virtual void* vc8();
virtual void* vcc();
    virtual bool  vd0();                                        // +0x0d0
    virtual void* vd4();
    virtual void* vd8();                                        // +0x0d8

    uint8_t        mPad04[0xbc];            // +0x004
    cSpatialObject mLoco;                   // +0x0c0 locomotion
    uint8_t        mPadc4[0x4e4];           // +0x0c4
    cCombatant     mCombatant;              // +0x5a8
    uint8_t        mPad5ac[0x34];           // +0x5ac
    float          mf5e0;                   // +0x5e0 previous health
    uint8_t        mPad5e4[0x53c];          // +0x5e4
    int32_t        mnB20;                   // +0xb20 noun id used to match creatures
    uint8_t        mPadb24[0x28];           // +0xb24
    cBehaviorTree* mpBehaviorTree;          // +0xb4c
    uint8_t        mPadb50[0x08];           // +0xb50
    uint32_t       mnFlags;                 // +0xb58 behaviour flags
    uint8_t        mPadb5c[0x02];           // +0xb5c
    bool           mbB5e;                   // +0xb5e
    uint8_t        mPadb5f[0x2d9];          // +0xb5f
    bool           mbE38;                   // +0xe38
    uint8_t        mPade39[0x17f];          // +0xe39
    bool           mbFB8;                   // +0xfb8 resting
    bool           mbFB9;                   // +0xfb9 greeting
    uint8_t        mPadfba[0x66a];          // +0xfba
    void*          mp1624;                  // +0x1624 animation request queue

    bool     FUN_00c0c130();                                        // 0x00c0c130
    int32_t  CountValid();                                          // 0x00c0f570
    uint32_t FUN_00c0ee60(int32_t nA, int32_t nB);                  // 0x00c0ee60
    void     FUN_00c0cff0(int32_t nObject);                         // 0x00c0cff0
    int32_t  InterruptAnimation(uint32_t nAnim, int32_t nA, int32_t nB); // 0x00c12310
    bool     WaitForAnimEventOrEnd(uint32_t nEvent, int32_t* pnOut, int32_t nA,
                                   int32_t nB, int32_t nC);         // 0x00c14ef0
    void     FUN_00c1d460(uint32_t nKeyA, uint32_t nKeyB);          // 0x00c1d460
    int32_t  PlayAnimation(uint32_t nAnim, int32_t nA, int32_t nB); // 0x00c12190
    void     FUN_00c1d5e0(int32_t nA, uint32_t nKeyA, uint32_t nKeyB); // 0x00c1d5e0
    void     FUN_00c17350(uint32_t nKey, int32_t nFlag);            // 0x00c17350
    void     FUN_00c14750(bool bFlag);                              // 0x00c14750
    void     FUN_00c0ba10();                                        // 0x00c0ba10
    void     FUN_00c0d0c0(uint32_t nMode, int32_t nFlag);           // 0x00c0d0c0
    void     FUN_00c122c0(int32_t nAnim, float fA, float fB);       // 0x00c122c0
    void     MoveToPointAtSpeed(int32_t nMode, Vector3* pPoint, float fA, float fB); // 0x00c1c1d0
    bool     IsAnimFinished(uint32_t nAnim);                        // 0x00c12400
    bool     AnimationFinished(uint32_t nAnim);                     // 0x00c123f0
    bool     FUN_00c0d560(void* pTarget, float fA, float fB);       // 0x00c0d560
    void*    GetTargetAsCreature();                                 // 0x00c0ee70
    cNearNoun* FUN_00c04590(float fRadius, float fDistance);        // 0x00c04590
    void     PlayAnimationWithTarget(uint32_t nAnim, void* pTarget, int32_t nA,
                                     int32_t nB);                   // 0x00c14940
};
class cCreatureNotify {
public:
virtual void* v00();
virtual void* v04();
virtual void* v08();
virtual void* v0c();
virtual void* v10();
virtual void* v14();
virtual void* v18();
virtual void* v1c();
virtual void* v20();
virtual void* v24();
virtual void* v28();
virtual void* v2c();
virtual void* v30();
virtual void* v34();
virtual void* v38();
virtual void* v3c();
virtual void* v40();
virtual void* v44();
virtual void* v48();
virtual void* v4c();
virtual void* v50();
virtual void* v54();
virtual void* v58();
virtual void* v5c();
virtual void* v60();
virtual void* v64();
virtual void* v68();
virtual void* v6c();
virtual void* v70();
virtual void* v74();
virtual void* v78();
virtual void* v7c();
    virtual void* v80();                                        // +0x080
    virtual void  v84(void* pArgument);                         // +0x084
};
class cAnimRequests {
public:
    void FUN_00bc9d40(uint32_t nChannel, float fTime, void* pTarget, int32_t nFlag); // 0x00bc9d40
    bool FUN_00bc9a00(uint32_t nChannel);                                            // 0x00bc9a00
};
class cCreatureIterator {
public:
    bool             AtBegin() const;       // 0x00bc9b50
    cSPCreatureBase* FUN_00bc9b10();        // 0x00bc9b10
};
class tIdleCtx {
public:
    int32_t mn00;               // +0x00 animation id
    float   mf04;               // +0x04 idle hold time
    bool    mb08;               // +0x08 startled
    bool    mb09;               // +0x09 has valid offspring
    uint8_t mPad0a[0x02];       // +0x0a
    float   mf0c;               // +0x0c idle hold reset
};
class tAnimCtx {
public:
    int32_t mn00;               // +0x00 state
    int32_t mn04;               // +0x04 animation id
    int32_t mn08;               // +0x08
};
class tConfusedCtx {
public:
    float   mf00;               // +0x00 countdown
    Vector3 mPos;               // +0x04 target position
    int32_t mn10;               // +0x10 animation id
};
class tGreetCtx {
public:
    bool    mb00;               // +0x00
    uint8_t mPad01[0x03];       // +0x01
    float   mf04;               // +0x04
    int32_t mn08;               // +0x08
    Vector3 mPos;               // +0x0c avatar position
    int32_t mn18;               // +0x18
};
class tFindEntry {
public:
    uint32_t mn00;              // +0x00
    bool     mb04;              // +0x04 entry holds a name
    uint8_t  mPad05[0x03];      // +0x05
    int32_t  mn08;              // +0x08 key
};
class tFindTable {
public:
    uint8_t     mPad00[0x18];   // +0x000
    uint32_t    mnCount;        // +0x018
    tFindEntry  mEntries[1];    // +0x01c first entry of the trailing array
};
// ---- items of slice s00d7b550 end

// ---- items of slice s00d7c3e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
float sinf(float fValue);
class cSPVector3_s00d7_c3e0 {
public:
    float mx;
    float my;
    float mz;
};
class cBehaviorStimuli {
public:
    void ClearAll(int32_t nA, int32_t nFlags);  // 0x00bc98f0
    void* Play(int32_t nA, int32_t nFlags);     // 0x00bc96a0

    uint8_t mPad000[0x1c0];                     // 0x000
    uint32_t mnField1C0;                        // 0x1c0
};
class cBehaviorTree_s00d7_c3e0 {
public:
    uint8_t mPad000[0x08];                      // 0x000
    cBehaviorStimuli mStimuli;                  // 0x008
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
    virtual float* GetPosition();               // 0x02c
virtual void v30();
virtual void v34();
virtual void v38();
virtual void v3c();
    virtual void SetSpeed(float fSpeed);        // 0x040
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
virtual void vdc();
virtual void ve0();
virtual void ve4();
virtual void ve8();
virtual void vec();
virtual void vf0();
    virtual void vf4();
    virtual bool IsMoving();                    // 0x0f8

    bool IsNearGoal();                          // 0x00c42e20
    float* GetVelocity();                       // 0x00d20610
};
class cCombatant_s00d7_c3e0 {
public:
    int32_t GetFileCount();                     // 0x008e7f80
    float GetTargetDistance();                  // 0x00bfc490

    uint8_t mPad000[0x38];                      // 0x000
    float mfHealth;                             // 0x038
    uint8_t mPad03c[0x04];                      // 0x03c
    int32_t mnAnimId;                           // 0x040
    uint8_t mPad044[0x534];                     // 0x044
};
class cCreatureData {
public:
    uint8_t mPad000[0x5e8];                     // 0x000
    int32_t mnAnimId;                           // 0x5e8
};
class cCreaturePart {
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
    virtual void EnterToolMode(void* pTool);    // 0x054
    virtual void ExitToolMode(void* pTool);     // 0x058

    void SetStimulusTarget(const void* pTarget);    // 0x00c41d60

    uint8_t mPad004[0x73];                      // 0x004
    uint8_t mbField077;                         // 0x077
    uint8_t mPad078[0x178];                     // 0x078
    int32_t mnField1F0;                         // 0x1f0
    uint8_t mPad1F4[0x74];                      // 0x1f4
    uint8_t mbField268;                         // 0x268
};
class cMessageServer {
public:
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
    virtual void v10();
    virtual void Send(int32_t nId, int32_t nA, int32_t nB);   // 0x014
};
class cCreatureBase {
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
    virtual void* v2c();                        // 0x02c
virtual void v30();
virtual void v34();
virtual void v38();
virtual void v3c();
virtual void v40();
virtual void v44();
    virtual void AbortAnimation(int32_t nTime); // 0x048
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
    virtual void SetAnimState(cCombatant_s00d7_c3e0* pTarget, int32_t nA, int32_t nB);   // 0x084
virtual void v88();
virtual void v8c();
virtual void v90();
    virtual void AddWalkSpeed(float fSpeed);    // 0x094
virtual void v98();
virtual void v9c();
virtual void va0();
virtual void va4();
virtual void va8();
virtual void vac();
virtual void vb0();
virtual void vb4();
    virtual void* FindPart(uint32_t nPartId);   // 0x0b8
virtual void vbc();
virtual void vc0();
virtual void vc4();
    virtual void StopMove(int32_t nA);          // 0x0c8
virtual void vcc();
virtual void vd0();
virtual void vd4();
virtual void vd8();
virtual void vdc();
virtual void ve0();
    virtual void SetFocusTarget(const void* pTarget);   // 0x0e4

    bool HasAnimation(int32_t nId);             // 0x00c0e0c0
    bool Flag388();                             // 0x00c0c0e0
    bool FUN_00c0b770();                        // 0x00c0b770
    void FUN_00c0b370(int32_t nA);              // 0x00c0b370
    void FUN_00c0d950(int32_t nA);              // 0x00c0d950
    bool FUN_00c0e2c0(uint32_t hAnim);          // 0x00c0e2c0
    bool AnimationFinished(uint32_t hAnim);     // 0x00c12400
    bool AnimationFinishedById(int32_t nAnim);  // 0x00c123f0
    void* InterruptAnimation(int32_t nId, int32_t nA, int32_t nB);   // 0x00c12310
    void* PlayAnimation(int32_t nId, int32_t nA, int32_t nB);        // 0x00c12190
    void Hover(int32_t nA);                     // 0x00c13a30
    void FUN_00c14750(int32_t nA);              // 0x00c14750
    void FUN_00c17350(uint32_t nBitsA, int32_t nB);   // 0x00c17350
    void FUN_00c1d460(uint32_t nBitsA, uint32_t nBitsB);   // 0x00c1d460
    void MoveToPointAtSpeed(int32_t nMode, float* pPoint);           // 0x00c1c1d0
    void SetStealthed(int32_t nA, int32_t nB);  // 0x00c1aed0
    bool WaitForAnimEventOrEnd(int32_t nEvent, uint32_t* phAnim,
                               int32_t nA, int32_t nB, int32_t nC);  // 0x00c14ef0
    void* Get();                                // 0x00c04590
    void* GetInRange(float fA, float fB);       // 0x00c04590
    void* GetFocusTarget();                     // 0x00c04750
    cCreatureBase* ApplyCombatTarget();         // 0x00c0ee90

    uint8_t mPad004[0x4c];                      // 0x004
    uint32_t mnFlags050;                        // 0x050
    uint8_t mPad054[0x23];                      // 0x054
    uint8_t mbField077;                         // 0x077
    uint8_t mPad078[0x48];                      // 0x078
    cLocomotiveObject mLocomotive;              // 0x0c0
    uint8_t mPad0C4[0x4c];                      // 0x0c4
    uint32_t mnFlags110;                        // 0x110
    uint8_t mPad114[0x23];                      // 0x114
    uint8_t mbField137;                         // 0x137
    uint8_t mPad138[0x470];                     // 0x138
    cCombatant_s00d7_c3e0 mCombatant;                      // 0x5a8
    cCreatureData* mpData;                      // 0xb20
    uint8_t mPadB24[0x24];                      // 0xb24
    void* mpFieldB48;                           // 0xb48
    cBehaviorTree_s00d7_c3e0* mpBehaviorTree;              // 0xb4c
    uint8_t mPadB50[0x0e];                      // 0xb50
    uint8_t mbFieldB5E;                         // 0xb5e
    uint8_t mPadB5F[0xb0e];                     // 0xb5f
    uint8_t mbField166D;                        // 0x166d
    uint8_t mPad166E[0x2e];                     // 0x166e
    float mfRadius169C;                         // 0x169c
};
class cGameModeObject {
public:
    uint8_t mPad000[4];
};
class cGameStateObject {
public:
    uint8_t mPad000[0x78];                      // 0x000
    void* mpField078;                           // 0x078
    uint8_t mPad07C[0x50];                      // 0x07c
    int32_t mnField0CC;                         // 0x0cc
};
class cToolController {
public:
    void OnToolEnter(void* pTool, void* pPart);     // 0x00f1aff0
    void OnToolExit(void* pTool, void* pPart);      // 0x00f1b180
};
class cGameNounManager_s00d7_c3e0 {
public:
    void* GetAvatar();                          // 0x00b1fdb0
};
class cOrderNode {
public:
    uint8_t mPad000[0x10];                      // 0x000
    uint32_t mnField10;                         // 0x010
};
class cOrderManager {
public:
    cOrderNode* FindNode();                     // 0x00bca620
};
class cAnimFilter {
public:
    bool Accept(uint8_t* pEntry);               // 0x00c02650

    uint8_t mPad000[0x18];                      // 0x000
};
class cAnimIterator {
public:
    cAnimIterator* Advance();

    uint8_t** mppCurrent;                       // 0x000
    uint8_t** mppEnd;                           // 0x004
    cAnimFilter mFilter;                        // 0x008
};
class cForageList {
public:
    uint8_t mPad000[0x68];                      // 0x000
    uint8_t* mpBegin;                           // 0x068
    uint8_t* mpEnd;                             // 0x06c
    uint8_t mPad070[0x10];                      // 0x070
    uint32_t mnIndex;                           // 0x080
};
class cPlanetModel_s00d7_c3e0 {
public:
    cSPVector3_s00d7_c3e0* GetPosition();                  // 0x00b81630
};
class cStateBlock {
public:
    float mfField000;                           // 0x000
    float mfField004;                           // 0x004
    float mfField008;                           // 0x008
    float mfField00C;                           // 0x00c
    uint32_t mhAnimation;                       // 0x010
    uint8_t mbField014;                         // 0x014
    uint8_t mPad015[0x03];                      // 0x015
};
cGameModeObject g_gameMode;
cGameStateObject* g_pGameState = nullptr;
cSPVector3_s00d7_c3e0 g_vStimulusPosition;
float g_fCelebrateStretch = 1.0f;
float g_fCelebrateRate = 1.0f;
float g_fCelebratePhase = 1.0f;
float g_fCelebrateFreq = 6.2831855f;
float g_fCelebrateMinScale = 1.0f;
float g_fCelebrateMaxScale = 1.0f;
float g_fZero = 0.0f;
float g_fMineAlertRadius = 20.0f;
float g_fMineSpeedThreshold = 0.5f;
float g_fMineNearRadius = 5.0f;
float g_fMineInteractRadius = 3.0f;
void* GetCurrentGameMode();                     // 0x00b5b800
void* __stdcall FUN_00bc9b00(uint32_t nId, void* pFn, void* pArg);   // 0x00bc9b00
void* FUN_00d995c0(int32_t nA, int32_t nB, void* pArg);    // 0x00d995c0
cGameNounManager_s00d7_c3e0* NounManager_s00d7_c3e0();                // 0x00b3d300
cMessageServer* MessageServer();                // 0x0067dcc0
void* __stdcall PlanetModel(void* pOut, const void* pElement);   // 0x00b3d350
// ---- items of slice s00d7c3e0 end

// ---- items of slice s00d7d370 begin (TODO(rewrite): local stubs, replace by canonical classes)
#pragma warning(disable : 4100)
namespace SP {
struct IPositionVtbl {
virtual void p00();
virtual void p04();
virtual void p08();
virtual void p0c();
virtual void p10();
virtual void p14();
virtual void p18();
virtual void p1c();
virtual void p20();
virtual void p24();
virtual void p28();
    virtual float* GetPosition();                      // +0x2c
virtual void p30();
virtual void p34();
virtual void p38();
virtual void p3c();
virtual void p40();
virtual void p44();
virtual void p48();
virtual void p4c();
virtual void p50();
virtual void p54();
virtual void p58();
virtual void p5c();
virtual void p60();
virtual void p64();
virtual void p68();
virtual void p6c();
    virtual void p70();
    virtual float GetRadius();                         // +0x74
};
}
namespace SP {
struct cLocation_s00d7_d370 {
    IPositionVtbl* mpVtbl;                             // +0x00
};
}
namespace SP {
struct cCreatureBase_s00d7_d370 {
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
virtual void vec();
virtual void vf0();
virtual void vf4();
virtual void vf8();
virtual void vfc();
virtual void v100();
virtual void v104();
virtual void v108();
virtual void v10c();
virtual void v110();
virtual void v114();
virtual void v118();
virtual void v11c();
virtual void v120();
virtual void v124();
virtual void v128();
virtual void v12c();
virtual void v130();
virtual void v134();
virtual void v138();
virtual void v13c();
virtual void v140();
virtual void v144();
virtual void v148();
virtual void v14c();
virtual void v150();
virtual void v154();
virtual void v158();
virtual void v15c();
virtual void v160();
virtual void v164();
virtual void v168();
virtual void v16c();
virtual void v170();
virtual void v174();
virtual void v178();
virtual void v17c();
virtual void v180();
virtual void v184();
virtual void v188();
virtual void v18c();
virtual void v190();
virtual void v194();
virtual void v198();
virtual void v19c();
virtual void v1a0();
virtual void v1a4();
virtual void v1a8();
virtual void v1ac();
virtual void v1b0();
virtual void v1b4();
virtual void v1b8();
virtual void v1bc();
virtual void v1c0();
virtual void v1c4();
virtual void v1c8();
virtual void v1cc();
virtual void v1d0();
virtual void v1d4();
virtual void v1d8();
virtual void v1dc();
virtual void v1e0();
virtual void v1e4();
virtual void v1e8();
virtual void v1ec();
virtual void v1f0();
virtual void v1f4();
virtual void v1f8();
virtual void v1fc();
virtual void v200();
virtual void v204();
    virtual void* QueryInterface(uint32_t iid);        // +0x208 (slot 0x5c region used by callers)

    uint8_t     pad000[0xb20];                         // +0x000
    int32_t     mId;                                   // +0xb20
    uint8_t     padb24[0x4];                           // +0xb24
    uint8_t     mHoldingState[0xb28 - 0xb24];          // +0xb28 shared holding block
    uint8_t     padb4c[0xb4c - 0xb28];                 // +0xb4c
    cLocation_s00d7_d370*  mpLocomotive;                          // +0xb4c
    cCreatureBase_s00d7_d370* mpHolder;                           // +0xb50
    uint8_t     padb54[0x4];                           // +0xb54
    int32_t     mpOrnamentData;                        // +0xb54
    uint32_t    mFlags58;                              // +0xb58
    uint8_t     padb5c[0xb5e - 0xb5c];                 // +0xb5e
    uint8_t     mbDead;                                // +0xb5e
    cLocation_s00d7_d370*  mpPosition;                            // +0xc0
    uint8_t     padc4[0x1004 - 0xc4];                  // +0x1004
    void*       mpTarget;                              // +0x1004

    // called on the sub-object at +0xb4c (the locomotion component)
    uint32_t PlayIdleAnimation(uint32_t anim, int mode);
};
}
namespace SP {
struct behavior_stimuli_s00d7_d370 {
    uint8_t  pad00[0x0c];
    float    mDirectionX;                              // +0x0c
    float    mDirectionY;                              // +0x10
    float    mDirectionZ;                              // +0x14
    float    mRadius;                                   // +0x18
    uint8_t  pad1c[0x4];
    uint8_t  mPointers[8];                             // +0x20 (pointer array: [3] and [4] used)

    void GetAny(void* pOther);  // 0x00d997e0 (SP::behavior_stimuli::GetAny)
};
}
namespace SP {
float    __cdecl GravityRadius();                       // DAT_01582e04
}
namespace SP {
int      __cdecl FUN_00c0f510(uint32_t index);
}
namespace SP {
bool     __cdecl FUN_00d7d020(cCreatureBase_s00d7_d370* pCreature); // declared below
}
namespace SP {
void*    __cdecl NounManager();                          // 0x00c04590
}
namespace SP {
void*    __cdecl FUN_00b23a40(void* pManager);
}
namespace SP {
void*    __cdecl FUN_00c04590();
}
namespace SP {
void*    __cdecl FUN_00c6acc0();
}
namespace SP {
void*    __cdecl FUN_004df420();
}
namespace SP {
void     __cdecl FUN_00401090();
}
namespace SP {
void*    __cdecl FUN_00d99420(void* pBlock, int kind);
}
namespace SP {
void*    __cdecl FUN_00d99500(void* pInterface);
}
namespace SP {
void*    __cdecl FUN_00d99470(void* pInterface);
}
namespace SP {
void     __cdecl FUN_00b3d4c0(void* pBlock, void* pSelf, void* pOther);
}
namespace SP {
int      __cdecl FUN_00ba3f90(void* pBlock, void* pSelf, void* pOther);
}
namespace SP {
void     __cdecl FUN_00c0b9d0(void* pAnim);
}
namespace SP {
bool     __cdecl FUN_00c0b770();
}
namespace SP {
void*    __cdecl FUN_00c0ee90();
}
namespace SP {
void*    __cdecl FUN_00436ce0(void* a, void* b);
}
namespace SP {
void     __cdecl MoveToPointAtSpeed(cCreatureBase_s00d7_d370* pCreature, int mode, float* pPos, float speed, float turn);
}
namespace SP {
void*    __cdecl WatchMemoryBlock(uint32_t id);
}
namespace SP {
extern uint8_t gLastAnimationBlock[];                    // 0x01687a0c
}
namespace SP {
struct cCommunity_s00d7_d370 {
    void* GetLeader();  // 0x00c00650 (SP::cCommunity::GetLeader)
};
}
namespace SP {
struct cGameNounManager_s00d7_d370 {
    void* GetAvatar();  // 0x00b1fdb0 (SP::cGameNounManager::GetAvatar)
};
}
namespace SP {
template <int N, class B> struct VPad : VPad<N - 1, B> { virtual void vp() {} };
}
namespace SP {
template <class B> struct VPad<0, B> : B {};
}
namespace SP {
struct IEmpty {};
}
namespace SP {
struct ICombatant : VPad<46, IEmpty> {               // slot +0xb8 queries the creature interface
    virtual void* QueryInterface(uint32_t iid);      // +0xb8
};
}
namespace SP {
struct cCombatantList {
    uint32_t     FindFirstValid();                    // 0x00c0f780
    ICombatant*  GetAt(uint32_t index);               // 0x00c0f8a0
    float        FUN_00d7dca0();                      // @0xd7dca0
};
}
// ---- items of slice s00d7d370 end

// ---- items of slice s00d7e290 begin (TODO(rewrite): local stubs, replace by canonical classes)
void*  FUN_00d99420(void* a, uint32_t key);
extern float DAT_013ec4b8;
extern float DAT_013f08c0;
extern float DAT_01470f1c;
extern float DAT_01473c70;
extern float DAT_01486110;
extern float DAT_01485720;
extern float DAT_01572070;
extern float DAT_01582ec0;
#pragma pack(push, 1)
#pragma pack(pop)
struct B00 { virtual void a00() {} };
struct B01 : B00 { virtual void a01() {} };
struct B02 : B01 { virtual void a02() {} };
struct B03 : B02 { virtual void a03() {} };
struct B04 : B03 { virtual void a04() {} };
struct B05 : B04 { virtual void a05() {} };
struct B06 : B05 { virtual void a06() {} };
struct B07 : B06 { virtual void a07() {} };
struct B08 : B07 { virtual void a08() {} };
struct B09 : B08 { virtual void a09() {} };
struct B10 : B09 { virtual void a10() {} };
struct B11 : B10 { virtual void a11() {} };
struct B12 : B11 { virtual void a12() {} };
struct B13 : B12 { virtual void a13() {} };
struct B14 : B13 { virtual void a14() {} };
struct B15 : B14 { virtual void a15() {} };
struct B16 : B15 { virtual void a16() {} };
struct B17 : B16 { virtual void a17() {} };
struct B18 : B17 { virtual void a18() {} };
struct B19 : B18 { virtual void a19() {} };
struct B20 : B19 { virtual void a20() {} };
struct B21 : B20 { virtual void a21() {} };
struct B22 : B21 { virtual void a22() {} };
struct B23 : B22 { virtual void a23() {} };
struct B24 : B23 { virtual void a24() {} };
struct B25 : B24 { virtual void a25() {} };
struct B26 : B25 { virtual void a26() {} };
struct B27 : B26 { virtual void a27() {} };
struct B28 : B27 { virtual void a28() {} };
struct B29 : B28 { virtual void a29() {} };
struct B30 : B29 { virtual void a30() {} };
struct B31 : B30 { virtual void a31() {} };
struct B32 : B31 { virtual void a32() {} };
struct B33 : B32 { virtual void a33() {} };
struct B34 : B33 { virtual void a34() {} };
struct B35 : B34 { virtual void a35() {} };
struct B36 : B35 { virtual void a36() {} };
struct B37 : B36 { virtual void a37() {} };
struct B38 : B37 { virtual void a38() {} };
struct B39 : B38 { virtual void a39() {} };
struct B40 : B39 { virtual void a40() {} };
struct B41 : B40 { virtual void a41() {} };
struct B42 : B41 { virtual void a42() {} };
struct B43 : B42 { virtual void a43() {} };
struct B44 : B43 { virtual void a44() {} };
struct B45 : B44 { virtual void a45() {} };
struct cVec3 { float x, y, z; };
enum
{
    TAG_CREATURE_TARGET = 0x0ce9f6639,
    TAG_ANIM_TARGET     = 0x137e8e0,
    TAG_SOCIAL_ANIM     = 0x03a25119,
    TAG_ANIM_STATE      = 0x0915f7deb,
    TAG_INTERRUPT_ANIM  = 0x2481db0,
    TAG_LIST_STATE      = 0x2d852f3
};
struct cGameObj;                    // arg1 of every predicate; laid out below
struct cBehaviorMgr;                // the per-creature behaviour/stimuli block (cGameObj::mpB4c)
struct cHolder;                     // the per-creature speed holder (cGameObj::mpB54)
struct cSelf
{
    // behaviour stimuli block helpers (ecx = &cBehaviorMgr::mStimuli)
    void*  FUN_00bc96a0(int a, int b);
    void   FUN_00bc98f0(int a, int b);
    void   FUN_00bc97f0(int a, int b, float c, void* d);

    // noun / object services
    cGameObj* FUN_00c04590();
    void*     FUN_00c6acc0();
    uint8_t   FUN_00c6ac40();
    void*     FUN_00ca71d0();
    cGameObj* FUN_00b1fdb0();
    void*     FUN_00b81630(void* a, void* b);

    // creature actions
    void    FUN_00c12310(int a, int b, void* c);
    void    FUN_00c1c5c0(int a, void* b);
    uint8_t FUN_00c0e0c0(int a);
    void    FUN_00c12190(int a, int b, int c);
    uint8_t FUN_00c42e20();
    uint8_t FUN_00c0b860(void* a);
    void    FUN_00c14750(int a);
    int     FUN_00c0f570();
    void*   FUN_00c0f780();
    void*   FUN_00c0f8a0(void* a);

    // out-record release helper (ecx = the record's first object)
    void FUN_00d997e0();
};
void*  FUN_00b3d350();                 // noun manager accessor used by the goal conversion
void*  FUN_00d99470(void* a);
float  FUN_00d99a60(int a);            // heading-distance readback
void*  FUN_00ae6740(void* a);
void*  FUN_00d2ec30(void* a);
struct cBehaviorMgr
{
    uint8_t  pad000[0x08];
    uint8_t  mStimuli;              // +0x008  idle/social animation stimulus block
    uint8_t  pad009[0x1d0 - 0x09];
    uint8_t  mLookup;               // +0x1d0  keyed lookup table root
    uint8_t  pad1d1[0x1d8 - 0x1d1];
    uint32_t mKind;                 // +0x1d8  behaviour-tree kind id
};
struct cHolder
{
    uint8_t pad000[0x80];
    float   mSpeed;                 // +0x080  movement speed driven by the root predicate
};
struct cOutRec
{
    void*    mpCur;                 // +0x00  object the record used to hold (cleared on success)
    void*    mpNew;                 // +0x04  object produced by the predicate
    void*    mpAux;                 // +0x08  auxiliary handle of the produced object
    uint8_t  pad00c[0x18 - 0x0c];
    int32_t  m18;                   // +0x18  result scalar (flag or truncated distance)
    uint32_t m1c;                   // +0x1c  record kind
    uint32_t m20;                   // +0x20  record payload
};
struct cKeySrc
{
    uint8_t  pad000[0x2d];
    uint32_t mKey;                  // +0x2d
};
struct cBodyC0 : public B28                                    // +0x0c0
{
    virtual float v74(void* a, float b) { (void)a; (void)b; return 0.0f; }
};
struct cBody5a8 : public B02                                   // +0x5a8
{
    virtual void* v0c() { return 0; }
};
struct cGameObj
{
    uint8_t  pad000[0x40];
    int32_t  mListBegin040;         // +0x040  action list begin (byte address)
    int32_t  mListEnd044;           // +0x044  action list end (byte address)
    uint8_t  pad048[0x0c0 - 0x48];
    cBodyC0  mC0;                   // +0x0c0  creature sub-object (vptr first)
    uint8_t  pad0c4[0x135 - 0xc4];
    uint8_t  mFlag135;              // +0x135  "has a weapon/prop attached"
    uint8_t  pad136[0x15c - 0x136];
    int32_t  mAction15c;            // +0x15c  current action/animation state id
    uint8_t  pad160[0x164 - 0x160];
    void*    mpOwner164;            // +0x164  owning game object (back pointer)
    void*    mpLink168;             // +0x168  intrusive list link; == &mpLink168 when unlinked
    uint8_t  pad16c[0x5a8 - 0x16c];
    cBody5a8 m5a8;                  // +0x5a8  reported target sub-object (vptr first)
    uint8_t  pad5ac[0xb20 - 0x5ac];
    uint32_t mIdB20;                // +0xb20  unique object id
    uint8_t  padB24[0xb4c - 0xb24];
    cBehaviorMgr* mpB4c;            // +0xb4c
    uint8_t  padB50[0xb54 - 0xb50];
    cHolder* mpB54;                 // +0xb54
    uint8_t  padB58[0xb5e - 0xb58];
    uint8_t  mFlagB5e;              // +0xb5e  "movement locked"
    uint8_t  padB5f[0xb88 - 0xb5f];
    int32_t  mStageB88;             // +0xb88  development stage
    uint8_t  padB8c[0x1698 - 0xb8c];
    void*    mp1698;                // +0x1698  behaviour-tree root of this creature
};
struct cOwnerLink
{
    cGameObj* mpOwner;              // +0x00  owning game object
    void*     mpLink;               // +0x04  intrusive link; == its own address while unlinked
};
struct cGameObjB
{
    uint32_t  pad000[0x59];         // +0x000 .. +0x163
    cOwnerLink mOwnerLink;          // +0x164  (same bytes as cGameObj::mpOwner164)
};
struct cSlotObj
{
    uint8_t pad000[0x77];
    uint8_t mHasGoal;               // +0x077  non-zero = the goal slot is already resolved
};
struct cTargetInfo
{
    void*   mpObj;                  // +0x00  described object
    uint8_t pad004[0x10 - 0x04];
    int32_t mKind;                  // +0x10  descriptor kind (1 = approachable object)
};
struct cVtV08  : B01 { virtual cSlotObj* v08() { return 0; } };                       // +0x08
struct cVtV0c  : B02 { virtual void* v0c() { return 0; } };                           // +0x0c
struct cVtV2cP : B10 { virtual cVec3* v2c() { return 0; } };                          // +0x2c (0 args)
struct cVtV2c1 : B10 { virtual int v2c(float a) { (void)a; return 0; } };             // +0x2c (1 arg)
struct cVtV2c3 : B10 { virtual cVec3* v2c(cVec3* a, float b, float c)
                       { (void)a; (void)b; (void)c; return 0; } };                    // +0x2c (3 args)
struct cVtV2cB : B10 { virtual uint8_t v2c() { return 0; } };                         // +0x2c (bool)
struct cVtV5c  : B22 { virtual cGameObj* v5c(int a) { (void)a; return 0; } };         // +0x5c (id)
struct cVtV5cV : B22 { virtual cVec3* v5c(cVec3* a) { (void)a; return 0; } };         // +0x5c (vec)
struct cVtV74I : B28 { virtual float v74(int a) { (void)a; return 0.0f; } };          // +0x74 (1 arg)
struct cVtV74B : B28 { virtual float v74(void* a, float b)
                       { (void)a; (void)b; return 0.0f; } };                          // +0x74 (2 args)
struct cVtV74F : B28 { virtual float v74() { return 0.0f; } };                        // +0x74 (0 args)
struct cVtVb8  : B45 { virtual void* vb8(int a) { (void)a; return 0; } };             // +0xb8
// ---- items of slice s00d7e290 end

// ---- items of slice s00d7f790 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace SP {
struct Vec3 {
    float x, y, z;
    Vec3() {}
    Vec3(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    Vec3(const Vec3& o) : x(o.x), y(o.y), z(o.z) {}
};
}
namespace SP {
struct Box {
    Vec3 lo, hi;
};
}
namespace SP {
template <int N, class B> struct VPad_s00d7_f790 : VPad_s00d7_f790<N - 1, B> { virtual void vpad(VPad_s00d7_f790<N, B>*) {} };
}
namespace SP {
template <class B> struct VPad_s00d7_f790<0, B> : B {};
}
namespace SP {
struct SpatialObj0 {
virtual void a0();
virtual void a1();
virtual void a2();
virtual void a3();
virtual void a4();
virtual void a5();
virtual void a6();
virtual void a7();
virtual void a8();
virtual void a9();
virtual void a10();
    virtual const Vec3* GetPosition();                      // 0x2c
};
}
namespace SP {
struct SpatialObj1 : VPad_s00d7_f790<15, SpatialObj0> {
    virtual const Box* GetBoundingBox(Box* tmp);            // 0x6c
};
}
namespace SP {
struct SpatialObj : VPad_s00d7_f790<18, SpatialObj1> {
    virtual void* QueryInterface(uint32_t id);              // 0xb8
};
}
namespace SP {
struct AnimTarget {
virtual void a0();
virtual void a1();
    virtual SpatialObj* GetTarget();                        // 0x08
    uint8_t pad04[0x38 - 4];
    float   mWeight;                                        // +0x38
};
}
namespace SP {
struct Loco0 {
virtual void a0();
virtual void a1();
virtual void a2();
virtual void a3();
virtual void a4();
virtual void a5();
virtual void a6();
virtual void a7();
virtual void a8();
virtual void a9();
virtual void a10();
    virtual const Vec3* GetPosition();                      // 0x2c
};
}
namespace SP {
struct Loco1 : VPad_s00d7_f790<11, Loco0> {
    virtual const Vec3* GetForward(Vec3* tmp);              // 0x5c
};
}
namespace SP {
struct Loco2 : VPad_s00d7_f790<5, Loco1> {
    virtual float GetHeight();                              // 0x74
};
}
namespace SP {
struct Loco : VPad_s00d7_f790<24, Loco2> {
    virtual float GetSpeed();                               // 0xd8
    bool IsNearGoal();                                      // 0xc42e20
    const Vec3* GetVelocity();                              // 0xd20610
};
}
namespace SP {
struct AnimMgr {
    AnimTarget* PlayIdleAnimation(int a, int b);            // 0xbc96a0 (ret 8)
};
}
namespace SP {
struct AnimOwner {
    uint8_t pad00[8];
    AnimMgr mgr;                                            // +8
};
}
namespace SP {
struct InteractableSub {
    void Notify(void* timer);                               // 0xae6690 (ret 4)
};
}
namespace SP {
class cInteractableObject_s00d7_f790 { public:
    uint8_t pad00[0x10c];
    InteractableSub mSub;                                   // +0x10c
};
}
namespace SP {
class cPlanetModel_s00d7_f790 { public:
    void DirectionToSurfacePosition(Vec3* out, const Vec3* pos);    // 0xb815a0 (ret 8)
    float GetRadius();                                              // 0xb7e490
};
}
namespace SP {
struct cImpulseSystem {                                             // singleton at 0xb3d310
    uint8_t pad00[0x20];
    int     mField20;                                               // +0x20
    void ApplyImpulse(SpatialObj* target, const Vec3* impulse, int flag);   // 0xb452f0 (ret 0xc)
    void Follow(Loco* loco, SpatialObj* target, float t);                   // 0xb4c600 (ret 0xc)
};
}
namespace SP {
class cSPCreatureBase_s00d7_f790 { public:
    uint8_t     pad00[0xc0];
    Loco        mLoco;                                      // +0xc0
    uint8_t     pad_c4[0x137 - 0xc4];
    bool        mbCanMove;                                  // +0x137
    uint8_t     pad_138[0x5a8 - 0x138];
    uint32_t    mNoAttackTimer[4];                          // +0x5a8
    uint8_t     pad_5b8[0xb4c - 0x5b8];
    AnimOwner*  mpAnimOwner;                                // +0xb4c
    bool        IsCreature();                                               // 0xc0c0e0
    bool        WaitForAnimEventOrEnd(uint32_t ev, float* t, uint32_t anim, int a, int b);   // 0xc14ef0 (ret 0x14)
    void        FUN_00c15d50(SpatialObj* target, int a, int b);             // 0xc15d50 (ret 0xc)
    void        PlayAnimationWithTarget(uint32_t anim, const Vec3* pos, int arg);       // 0xc14910 (ret 0xc)
    void        MoveToPointAndFacingAtSpeed(int mode, const Vec3* pos, const Vec3* facing, float speed, float arg);   // 0xc1c5c0
    bool        AnimationFinished(uint32_t anim);                           // 0xc123f0
};
}
namespace SP {
template <class T> struct AutoRefCount {
    T* mpObject;
};
}
namespace SP {
struct ThrowState {
    int      mState;                                        // +0x00
    bool     mbDone;                                        // +0x04
    uint8_t  pad05[3];
    AutoRefCount<SpatialObj> mTarget;                       // +0x08
    bool     mbAlt;                                         // +0x0c
    uint8_t  pad0d[3];
    int      mArg;                                          // +0x10
};
}
namespace SP {
extern Vec3     g_defaultThrowPos;                          // 0x169f03c
}
namespace SP {
extern uint32_t g_throwEvent;                               // 0x1590c2c
}
namespace SP {
cPlanetModel_s00d7_f790*   PlanetModel();                              // 0xb3d350
}
namespace SP {
cImpulseSystem* GetImpulseSystem();                         // 0xb3d310
}
namespace SP {
SpatialObj*     FUN_00d998d0_s00d7_f790(AnimTarget* h, uint32_t id);   // cdecl
}
namespace SP {
AnimTarget*     FUN_00d99a10_s00d7_f790(AnimTarget* h);                // cdecl
}
namespace SP {
void*           FUN_00ad2670(AutoRefCount<SpatialObj>* r);  // cdecl
}
namespace SP {
void            FUN_00f20ba0(void* a, cSPCreatureBase_s00d7_f790* c);  // cdecl
}
namespace SP {
cInteractableObject_s00d7_f790* InterfaceCast(AutoRefCount<SpatialObj>* r);   // 0xd7cf90 cdecl
}
namespace SP {
void            ManageInteractiveOrnamentEventSFX(void* iface, cSPCreatureBase_s00d7_f790* c);   // 0xd7d4a0
}
namespace SP {
Vec3*           normalized_safe(Vec3* out, const Vec3* in); // 0x449c20 cdecl
}
namespace SP {
float           VectorLength(const Vec3* v);                // 0x40ae50 cdecl
}
namespace SP {
template <class T> inline const T& max(const T& a, const T& b) { return a < b ? b : a; }
}
namespace SP {
template <class T> inline const T& min(const T& a, const T& b) { return b < a ? b : a; }
}
namespace SP {
inline float Clamp(float x, float lo, float hi)
{
    __asm {
        movss xmm0, x
        maxss xmm0, lo
        minss xmm0, hi
        movss x, xmm0
    }
    return x;
}
}
namespace SP {
inline uint32_t ThrowAnimID(const ThrowState* st)
{
    return (st->mbAlt ? 0x1485642 : 0) + 0x3ab8894;
}
}
// ---- items of slice s00d7f790 end

// ---- items of slice s00d7ff20 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace nSPBehaviorTree {
 struct behavior_memory_block_s00d7_ff20 { uint32_t Data[32]; }; 
}
using nSPBehaviorTree::behavior_memory_block_s00d7_ff20;
namespace SP {
struct Vector3_s00d7_ff20 {
    float x, y, z;
    Vector3_s00d7_ff20() {}
    Vector3_s00d7_ff20(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    Vector3_s00d7_ff20(const Vector3_s00d7_ff20& v) : x(v.x), y(v.y), z(v.z) {}
    static const Vector3_s00d7_ff20 ZERO;                                   // 0x169f03c
};
}
namespace SP {
inline Vector3_s00d7_ff20 operator-(const Vector3_s00d7_ff20& a, const Vector3_s00d7_ff20& b) { return Vector3_s00d7_ff20(a.x - b.x, a.y - b.y, a.z - b.z); }
}
namespace SP {
inline float Dot(const Vector3_s00d7_ff20& a, const Vector3_s00d7_ff20& b) { return a.x * b.x + a.y * b.y + a.z * b.z; }
}
namespace SP {
inline bool NotEqual(const Vector3_s00d7_ff20& a, const Vector3_s00d7_ff20& b) { return a.x != b.x || a.y != b.y || a.z != b.z; }
}
namespace SP {
bool  Vector3_NotEqual(const Vector3_s00d7_ff20& a, const Vector3_s00d7_ff20& b);      // 0x41dd30
}
namespace SP {
float Dot3(const Vector3_s00d7_ff20& a, const Vector3_s00d7_ff20& b);                   // 0x455cc0
}
namespace SP {
Vector3_s00d7_ff20* Vector3_Normalize(Vector3_s00d7_ff20* out, const Vector3_s00d7_ff20* in);     // 0x436ce0
}
namespace SP {
Vector3_s00d7_ff20* normalized_safe(Vector3_s00d7_ff20* out, const Vector3_s00d7_ff20* in);       // 0x449c20
}
namespace SP {
struct ATTACK_memory_block {
    uint32_t mAttackIdx;      // +0x0
    float    mTimer;          // +0x4
    bool     mAttackRoar;     // +0x8
    bool     mDropItems;      // +0x9
    float    mChaseDistance;  // +0xc
};
}
namespace SP {
struct cLocomotionGoal { uint32_t pad[0x5c / 4]; int mState; };   // +0x5c
}
namespace SP {
#define PV(n) virtual void pv##n();
}
namespace SP {
class cSpatialObject_s00d7_ff20 { public:
    PV(00) PV(01) PV(02) PV(03) PV(04) PV(05) PV(06) PV(07) PV(08) PV(09) PV(0a)
    virtual const Vector3_s00d7_ff20& GetPosition();                         // 0x2c
    PV(0c) PV(0d) PV(0e) PV(0f) PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16)
    virtual Vector3_s00d7_ff20 GetDirection();                               // 0x5c
    PV(18) PV(19) PV(1a) PV(1b) PV(1c)
    virtual float GetFootprintRadius();                           // 0x74
};
}
namespace SP {
class cLocomotiveObject_s00d7_ff20 : public cSpatialObject_s00d7_ff20 { public:
    const Vector3_s00d7_ff20& GetVelocity();                                 // 0xd20610
    bool IsNearGoal();                                            // 0xc42e20
    cLocomotionGoal* GetGoal();                                   // 0xc41ec0
};
}
namespace SP {
class cCombatant_s00d7_ff20 { public:
    PV(00) PV(01)
    virtual cSpatialObject_s00d7_ff20* ToSpatialObject();                    // 0x08
};
}
namespace SP {
class cCreatureAbility_s00d7_ff20 { public:
    uint32_t pad00[2];
    int   mType;              // +0x08
    uint32_t pad0c[(0xa8 - 0xc) / 4];
    float mRange;             // +0xa8
    uint32_t padac[(0xf4 - 0xac) / 4];
    float mRushingRange;      // +0xf4
    float GetBound(bool b);                                       // 0x4d3d70 (TuningObj::GetBound)
};
}
namespace SP {
struct BehaviorNode { uint32_t pad[3]; uint32_t mAttackIdx; };  // +0xc
}
namespace SP {
struct cBehaviorTree_s00d7_ff20 { BehaviorNode* PlayIdleAnimation(uint32_t mask, uint32_t b); };   // 0xbc96a0
}
namespace SP {
struct cBehaviorTreeData_s00d7_ff20 { uint32_t pad[2]; cBehaviorTree_s00d7_ff20 mTree; };                    // +8
}
namespace SP {
class cSPTimer_s00d7_ff20 { public: uint64_t GetElapsedTime(); };                   // 0xbc3190
}
namespace SP {
class cSPCreatureBase_s00d7_ff20 { public:
    PV(00) PV(01) PV(02) PV(03) PV(04) PV(05) PV(06) PV(07) PV(08) PV(09) PV(0a) PV(0b) PV(0c) PV(0d) PV(0e)
    PV(0f) PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19) PV(1a) PV(1b) PV(1c) PV(1d)
    PV(1e) PV(1f) PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26) PV(27) PV(28) PV(29) PV(2a) PV(2b) PV(2c)
    virtual cCreatureAbility_s00d7_ff20* GetAbility(int index);              // 0xb4

    uint32_t pad004[(0xc0 - 0x4) / 4];
    cLocomotiveObject_s00d7_ff20 mLoco;                                      // +0xc0
    uint32_t pad0c4[(0xb4c - 0xc4) / 4];
    cBehaviorTreeData_s00d7_ff20* mpBehaviorTreeData;                        // +0xb4c
    uint32_t padb50[2];
    uint32_t mGeneralFlags;                                       // +0xb58
    uint32_t padb5c[(0xb78 - 0xb5c) / 4];
    float mNoAttackTimer;                                         // +0xb78
    uint32_t padb7c[(0xe8c - 0xb7c) / 4];
    uint32_t mCurrentAttackIdx;                                   // +0xe8c
    uint32_t pade90[(0xfc0 - 0xe90) / 4];
    cSPTimer_s00d7_ff20 mAttackTimer;                                        // +0xfc0

    cCombatant_s00d7_ff20* GetTarget();                                      // 0xc0ee60
    cSPCreatureBase_s00d7_ff20* GetTargetAsCreature();                       // 0xc0ee70
    float FUN_00c0cfa0(int a, int b);                             // 0xc0cfa0
    void MoveToPointAndFacingAtSpeed(int mode, const Vector3_s00d7_ff20* p, const Vector3_s00d7_ff20* facing, float a, float b);  // 0xc1c5c0
    void PlayAnimation(uint32_t id, int a, int b);                // 0xc12190
    bool AnimationFinished(uint32_t id);                          // 0xc123f0
    bool WaitForAnimEventOrEnd(uint32_t ev, void* p, int a, int b, int c);   // 0xc14ef0
    void FUN_00c19940(int a);                                     // 0xc19940
    void FUN_00c14750(int a);                                     // 0xc14750
    void Attack(uint32_t idx, int* outAnim);                      // 0xc1e460
};
}
namespace SP {
class cPlanetModel_s00d7_ff20 { public: Vector3_s00d7_ff20* FUN_00b81630(Vector3_s00d7_ff20* out, const Vector3_s00d7_ff20* p); };   // 0xb81630
}
namespace SP {
cPlanetModel_s00d7_ff20* PlanetModel_s00d7_ff20();                                      // 0xb3d350
}
namespace SP {
void* FUN_00d99470(cSPCreatureBase_s00d7_ff20* c);                           // 0xd99470
}
namespace SP {
float FUN_00d38a30(int which, cSPCreatureBase_s00d7_ff20* c);                // 0xd38a30
}
namespace SP {
float FUN_00d99a60(const Vector3_s00d7_ff20& a, float ra, const Vector3_s00d7_ff20& b, float rb, bool f);   // 0xd99a60
}
namespace SP {
cSPCreatureBase_s00d7_ff20* WatchMemoryBlock(BehaviorNode* n);               // 0xd999d0
}
namespace SP {
extern uint32_t g_AttackDropEvent;                                // 0x1590c30
}
namespace SP {
extern float g_AttackRoarDelay;                                   // 0x1687a34
}
namespace SP {
inline bool TestBit(uint32_t v, uint32_t n) { return (v >> n) & 1; }
}
namespace SP {
inline const float& Max(const float& a, const float& b) { return a < b ? b : a; }
}
// ---- items of slice s00d7ff20 end

// ---- items of slice s00d81940 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int   u32;
typedef int            s32;
typedef unsigned char  u8;
struct Vec3_s00d8_1940 { float x, y, z; };
struct Quat { float x, y, z, w; };
struct cNearNoun_s00d8_1940;
struct cSPCreatureBase_s00d8_1940;
struct cLocomotiveObject_s00d8_1940;
struct BehaviorEnv;
struct LOUNGE_Node;
struct VignetteDef;
struct VignetteRange;
struct VignetteMgr;
struct VignetteList;
struct cPlanetModel_s00d8_1940;
struct Archetype;
struct LayoutMgr_s00d8_1940;
struct cNearNoun_s00d8_1940 {
  u8    pad00[0x88];
  u32   mField_88;             // +0x088
  u8    pad8c[0xf0 - 0x8c];
  u32   mField_f0;             // +0x0f0
  u8    padf4[0x10c - 0xf4];
  s32   mCount_10c;            // +0x10c
  u32   mWorld_110;            // +0x110
  u8    pad114[0x160 - 0x114];
  void* mpField_160;           // +0x160
  u8    pad164[0x20c - 0x164];
  Vec3_s00d8_1940  mWateringHole_20c;     // +0x20c

  bool UnbrokenEggsInNest();   // 0x00c6ac40
  const Vec3_s00d8_1940* GetPosition();   // 0x00c6acc0
  Vec3_s00d8_1940* FUN_00c6bdc0();        // 0x00c6bdc0
};
struct cLocomotiveObject_s00d8_1940 {
  void** mpVtable;             // +0x00
  bool IsNearGoal();           // 0x00c42e20
};
struct LOUNGE_HandleTimer {
  s32   mHandle;               // +0x00
  float mTimer;                // +0x04
};
struct LOUNGE_Node {
  u8    pad00[0x10];
  s32   mState10;              // +0x010
  u8    pad14[0x1a4 - 0x14];
  LOUNGE_HandleTimer mHandleTimer; // +0x1a4
};
struct BehaviorEnv {
  u8    pad00[0x600];
  LOUNGE_Node* mpNode_600;     // +0x600
  u8    pad604[0x60c - 0x604];
  void* mpOrderHead_60c;       // +0x60c

  void FUN_00bcb430();                                            // 0x00bcb430
  void FUN_00bcb480(LOUNGE_Node* node, cSPCreatureBase_s00d8_1940* c, int a, int b); // 0x00bcb480
};
struct cSPCreatureBase_s00d8_1940 {
  u8   pad00[0xc0];
  cLocomotiveObject_s00d8_1940 mLoco;     // +0x0c0
  u8   padc4[0x330 - 0xc4];
  u8   mFlags_330;             // +0x330
  u8   pad331[0xb4c - 0x331];
  BehaviorEnv* mpEnv_0b4c;     // +0xb4c
  u8   padb50[0xb58 - 0xb50];
  u32  mFlags_b58;             // +0xb58
  u8   padb5c[0xb5e - 0xb5c];
  u8   mbB5e;                  // +0xb5e
  u8   padb5f[0xf90 - 0xb5f];
  u8   mDrinkFlag_f90;         // +0xf90
  u8   padf91[0x1674 - 0xf91];
  cNearNoun_s00d8_1940* mpNoun_1674;      // +0x1674

  cNearNoun_s00d8_1940* Get();                                                // 0x00c04590
  Archetype* FUN_00c0c1a0();                                       // 0x00c0c1a0
  void MoveToPointAtSpeed(int mode, Vec3_s00d8_1940* target, float a, float b); // 0x00c1c1d0
  void FUN_00c14750(bool b);                                       // 0x00c14750
  bool AnimationFinished(u32 anim);                                // 0x00c123f0
  void FUN_00c14990(u32 anim, const Vec3_s00d8_1940* target, int a);          // 0x00c14990
  void PlayAnimationWithTarget(u32 anim, const Vec3_s00d8_1940* target, int a); // 0x00c14910
  u8   FUN_00c0e0c0(u32 anim);                                     // 0x00c0e0c0
};
struct Archetype {
  u8    pad00[0x394];
  float mLo_394;               // +0x394
  float mHi_398;               // +0x398
};
struct cPlanetModel_s00d8_1940 {
  Vec3_s00d8_1940* FUN_00b81630(Vec3_s00d8_1940* out, const Vec3_s00d8_1940* in);                       // 0x00b81630
  void  FindClosestWater(Vec3_s00d8_1940* pos, float maxDist, Vec3_s00d8_1940* out);          // 0x00b8bb70
  void  MakeRandomWorldPosition(Vec3_s00d8_1940* out, Vec3_s00d8_1940* center, float r0, float r1); // 0x00b81780
  Quat* BuildSurfaceOrientation(Quat* out, const Vec3_s00d8_1940* pos);            // 0x00b7f190
  void  RayCast(Vec3_s00d8_1940* a, float dist, Vec3_s00d8_1940* b, float c, int d, int e);  // 0x00b88770
};
struct VignetteDef {
  u8  pad00[4];
  s32 mField_04;               // +0x04 (insert key / radius multiplier)
  u8  pad08[0x7b4 - 8];
};
struct VignetteRange {
  VignetteDef* mpBegin;        // +0x00
  VignetteDef* mpEnd;          // +0x04
};
struct VignetteMgr {
  VignetteRange* Find(u32 key, int a);                              // 0x00bc7610 (ret 8)
  int  FUN_00bc3db0(int id);                                        // 0x00bc3db0 (ret 4)
  u8   FUN_00bc3df0(int id);                                        // 0x00bc3df0 (ret 4)
  u8   FUN_00bc4900(int id, cSPCreatureBase_s00d8_1940* c, int a);             // 0x00bc4900 (ret 0xc)
  void FUN_00bc52a0(int id, cSPCreatureBase_s00d8_1940* c);                    // 0x00bc52a0 (ret 8)
  int  FUN_00bc65f0(const VignetteDef* def, const Vec3_s00d8_1940* a, const Vec3_s00d8_1940* b); // 0x00bc65f0 (ret 0xc)
};
struct VignetteList {
  LOUNGE_Node* Insert(u32 key, s32 id, const char* tag, const char* name); // 0x00bcb0b0 (ret 0x10)
  LOUNGE_Node* FindItem(u32 key, void* pred, void* ctx);              // 0x00bca620 (ret 0xc)
};
struct LayoutMgr_s00d8_1940 {
  bool LookupA(void* p, int a, float* b); // 0x00af0af0
};
struct LOUNGE_Mem {
  LOUNGE_Node* mpNode;         // +0x000
  u8   pad04[0x18 - 4];
  s32  mVignetteIndex;         // +0x018
  u32  mTableKey;              // +0x01c
};
struct DRINK_Mem {
  s32   mState;                // +0x00
  float mTimer;                // +0x04
  Vec3_s00d8_1940  mTarget;               // +0x08
  Vec3_s00d8_1940  mTarget2;              // +0x14
};
cPlanetModel_s00d8_1940* PlanetModel_s00d8_1940();                          // 0x00b3d350
VignetteMgr*  FUN_00b3d4e0();                         // 0x00b3d4e0
VignetteList* FUN_00bc9b00();                         // 0x00bc9b00
LayoutMgr_s00d8_1940*    CreateLayoutManager_s00d8_1940();                  // 0x00af13b0
float         RandomFloatRange(float lo, float hi);   // 0x00572a10
void          FUN_0059aed0(Vec3_s00d8_1940* out, const Quat* a, const Quat* b); // 0x0059aed0
extern Vec3_s00d8_1940  g_DefaultSurf;                           // 0x0169f03c
typedef void  (__thiscall* VoidSlot)(void*);
typedef float (__thiscall* FloatSlot)(void*);
typedef Vec3_s00d8_1940* (__thiscall* Vec3Slot)(void*);
typedef Vec3_s00d8_1940* (__thiscall* Vec3OutSlot)(void*, Vec3_s00d8_1940*);
typedef bool  (__thiscall* BoolSlot)(void*);
#define VSLOT(T, p, off) ((T)((*(void***)(p))[(off) / 4]))
// ---- items of slice s00d81940 end

// ---- items of slice s00d824a0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace SP {
struct Vec3_s00d8_24a0 { float x, y, z; };
}
namespace SP {
__forceinline float Clamp_s00d8_24a0(float value, float minValue, float maxValue)
{
    __asm {
        movss xmm0, value
        maxss xmm0, minValue
        minss xmm0, maxValue
        movss value, xmm0
    }
    return value;
}
}
namespace SP {
static inline const float& Min(const float& a, const float& b) { return (b < a) ? b : a; }
}
namespace SP {
struct LocoState {
    char pad00[0x5c];
    int  mHasPath;                                     // +0x5c
    const Vec3_s00d8_24a0* GetGoal();                             // 0xc423c0
};
}
namespace SP {
struct Loco_s00d8_24a0 {
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
    virtual const Vec3_s00d8_24a0* GetPosition();                 // +0x2c
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
    virtual const Vec3_s00d8_24a0* GetFacing(Vec3_s00d8_24a0* out);          // +0x5c
virtual void s24();
virtual void s25();
virtual void s26();
virtual void s27();
    virtual void s28();
    virtual float GetRadius();                         // +0x74
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
virtual void s44();
virtual void s45();
virtual void s46();
virtual void s47();
virtual void s48();
virtual void s49();
virtual void s50();
virtual void s51();
virtual void s52();
virtual void s53();
virtual void s54();
virtual void s55();
virtual void s56();
virtual void s57();
virtual void s58();
virtual void s59();
virtual void s60();
virtual void s61();
    virtual bool SlotF8();                             // +0xf8
    const Vec3_s00d8_24a0& GetVelocity();                         // cLocomotiveObject::GetVelocity 0xd20610
    LocoState* GetState();                             // 0xc41ec0
    bool IsNearGoal();                                 // cLocomotiveObject::IsNearGoal 0xc42e20
};
}
namespace SP {
struct Sub5a8 { float FUN_00bfc490(); };              // 0xbfc490
}
namespace SP {
struct CreatureTuning {                                // creature + 0xb20
    char  pad00[0x54c];
    float mHoverSpeed;                                 // +0x54c
    char  pad550[0x61c - 0x550];
    uint32_t mCanHover;                                // +0x61c
};
}
namespace SP {
class cSPCreatureBase_s00d8_24a0 { public:
    char      pad00[0xc0];
    Loco_s00d8_24a0      mLoco;                                   // +0xc0
    char      padC4[0x110 - 0xc4];
    uint32_t  mFlags;                                  // +0x110
    char      pad114[0x137 - 0x114];
    bool      mbFlying;                                // +0x137
    char      pad138[0x5a8 - 0x138];
    Sub5a8    m5a8;                                    // +0x5a8
    char      pad5a9[0xb20 - 0x5a9];
    CreatureTuning* mpTuning;                          // +0xb20

    int  FUN_00c029b0();                                                  // 0xc029b0
    int  FUN_00c0b750();                                                  // 0xc0b750
    int  PlayAnimation(uint32_t id, int a, int b);                        // 0xc12190
    void InterruptAnimation(uint32_t id, int a, int b);                   // 0xc12310
    bool AnimationFinished(uint32_t id);                                  // 0xc123f0
    bool AnimationFinished(int handle);                                   // 0xc12400
    void Hover(bool b);                                                   // 0xc13a30
    void FUN_00c14750(bool b);                                            // 0xc14750
    void TryJumpToTarget(int a, const Vec3_s00d8_24a0* p, const Vec3_s00d8_24a0* d, float f, int b);  // 0xc190e0
    void MoveToPointAtSpeed(int mode, const Vec3_s00d8_24a0* p, float speed, float f);     // 0xc1c1d0
};
}
namespace SP {
class cGameNounManager_s00d8_24a0 { public: cSPCreatureBase_s00d8_24a0* GetAvatar(); };   // 0xb1fdb0
}
namespace SP {
class cPlanetModel_s00d8_24a0 { public:
    float GetRadiusAt(const Vec3_s00d8_24a0* p);                            // 0xb7ef70
    const Vec3_s00d8_24a0* FUN_00b82b40(Vec3_s00d8_24a0* out, const Vec3_s00d8_24a0* p, int a);   // 0xb82b40 (surface snap)
};
}
namespace SP {
class cPosseSimulator_s00d8_24a0 { public:
    static cPosseSimulator_s00d8_24a0* Instance();                          // 0xd539d0
    void* FUN_00d53b50(cSPCreatureBase_s00d8_24a0* c, Vec3_s00d8_24a0* outPos);         // 0xd53b50
};
}
namespace SP {
void* __cdecl GetCurrentGameMode();                              // 0xb5b800
}
namespace SP {
cGameNounManager_s00d8_24a0* __cdecl NounManager_s00d8_24a0();                         // 0xb3d300
}
namespace SP {
cPlanetModel_s00d8_24a0* __cdecl PlanetModel_s00d8_24a0();                             // 0xb3d350
}
namespace SP {
float __cdecl FUN_00d99ac0(Loco_s00d8_24a0* a, Loco_s00d8_24a0* b, bool c);           // 0xd99ac0
}
namespace SP {
float __cdecl FUN_00c29530(const Vec3_s00d8_24a0* p, const Vec3_s00d8_24a0* v, float s);   // 0xc29530
}
namespace SP {
extern char g_GameModeCreature;                                  // 0x1654c10
}
namespace SP {
extern float g_PosseFollowDist;                                  // 0x1582e04
}
namespace SP {
extern float g_PosseMaxFollowDist;                               // 0x1582e0c
}
namespace SP {
extern float g_PosseHoverDist;                                   // 0x1582fc0
}
namespace SP {
extern float g_PosseIdleChance;                                  // 0x1687a14
}
namespace SP {
extern Vec3_s00d8_24a0 g_JumpDefault;                                       // 0x169f03c
}
namespace SP {
struct POSSE_IDLE_memory_block {
    bool  mbFollowing;      // +0x00
    float mTimer;           // +0x04
    cSPCreatureBase_s00d8_24a0** mpSlot;  // +0x08 (posse slot; first field is the member)
    Vec3_s00d8_24a0  mAvatarPos;       // +0x0c
    int   mAnimHandle;      // +0x18
};
}
namespace SP {
static __forceinline float InvLen(float lsq) { return 1.0f / sqrtf(lsq + 1e-8f); }
}
// ---- items of slice s00d824a0 end

// ---- items of slice s00d83a60 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Vec3_s00d8_3a60 { float x, y, z; };
#define AT(T, p, off) (*(T*)((char*)(p) + (off)))
struct IdleNode {
    char pad00[0xc];
    int kind;                 // +0x0c (also read as a float radius by one handler)
    Vec3_s00d8_3a60 pt;                  // +0x10
    void* hasPt;              // +0x1c
};
struct BTreePad8 { char pad[8]; };
struct Behaviors {            // behavior tree at creature + 0xb4c (+ 8)
    IdleNode* PlayIdleAnimation(int a, int mask);          // 0xbc96a0
    IdleNode* FUN_00bc97f0(int a, int b, float f, void* o);  // 0xbc97f0
    void ClearAll(int a, int mask);                        // 0xbc98f0
};
struct BTree : BTreePad8, Behaviors {};
struct Loco_s00d8_3a60 {                 // locomotion sub-object at creature + 0xc0 (has its own vtable)
    void** vt;
    bool IsNearGoal();        // 0xc42e20
};
struct Creature;
struct Creature {
    char pad00[0xc0];
    Loco_s00d8_3a60 loco;                // +0xc0
    char pad04[0xb4c - 0xc0 - sizeof(Loco_s00d8_3a60)];
    BTree* mpBehavior;        // +0xb4c

    void PlayAnimation(unsigned id, int a, int b);                         // 0xc12190
    bool AnimationFinished(unsigned id);                                   // 0xc123f0
    bool AnimationFinished2(int handle);                                   // 0xc12400
    int FUN_00c0f570();                                                    // 0xc0f570
    int FUN_00c0f8f0(int id);                                              // 0xc0f8f0
    bool FUN_00c0e0c0(unsigned id);                                        // 0xc0e0c0
    bool WaitForAnimEventOrEnd(int g, void* pc, unsigned id, int a, int b);  // 0xc14ef0
    int PlayAnimationWithTarget(unsigned id, void* center, int handle);    // 0xc14910
    int PlayAnimationWithTarget2(unsigned id, void* tgt, int a, int b);    // 0xc14940
    void MoveToPointAtSpeed(int mode, const Vec3_s00d8_3a60* p, float speed, float f);        // 0xc1c1d0
    void MoveToPointAndFacingAtSpeed(int mode, const Vec3_s00d8_3a60* p, const Vec3_s00d8_3a60* d, float speed, float f);  // 0xc1c5c0
    bool FUN_00c15d50(void* p, int a, int b);                              // 0xc15d50
    void FUN_00c19940(int a);                                              // 0xc19940
    void FUN_00c15150(unsigned id, int a);                                 // 0xc15150
    bool FUN_00c159c0(void* p, int a, int b);                              // 0xc159c0
    void FUN_00c14750(int a);                                              // 0xc14750
    void* FUN_00c04590();                                                  // 0xc04590
    void SetStealthed(int a, int b);                                       // 0xc1aed0
    Creature* GetTargetAsCreature();                                       // 0xc0ee70
    bool FUN_00c0d560(void* obj, float a, float b);                        // 0xc0d560
    bool FUN_00c0b7a0();                                                   // 0xc0b7a0
};
struct S1 { int state; int target; };
// ---- items of slice s00d83a60 end

// ---- items of slice s00d84c50 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float g_kZero;       // 0x01485378 _HK_REAL_ZERO 0.0f
extern float g_kMax;        // 0x0147c030 FLT_MAX
extern float g_kQuarter;    // 0x013eb8a0 0.25f
extern float g_kEps;        // 0x013ec4b8 1e-08f
extern float g_kTwenty;     // 0x013eecd8 20.0f
extern float g_kThirty;     // 0x014853bc 30.0f
extern uint32_t g_1590c3c;  // 0x01590c3c animation event key handed to WaitForAnimEventOrEnd
void* __cdecl FUN_00d51660();                                   // 0x00d51660
int32_t __fastcall FUN_008e7f80(void* pCombatant);               // 0x008e7f80 damage state
class behavior_stimuli_s00d8_4c50 {
public:
    uint32_t mPad00;                                                    // +0x00
    void FUN_00bc97f0(int32_t nA, int32_t nB, float fC, int32_t nD);   // 0x00bc97f0
    void ClearAll(int32_t nFlags, int32_t nMask);                       // 0x00bc98f0
};
class cBehaviorTree_s00d8_4c50 {
public:
    uint32_t         mPad00[2];         // +0x000
    behavior_stimuli_s00d8_4c50  mStimuli;         // +0x008
    uint8_t          mPad0c[0x1d8 - 0x00c];
    int32_t          mn1d8;             // +0x1d8 interaction state
};
class tLoudnessStim {
public:
    float   mf00;               // +0x00 loudness this tick
    float   mf04;               // +0x04 loudness rate
    float   mf08;               // +0x08 loudness cap
    float   mf0c;               // +0x0c current loudness
    uint8_t mPad10[0x2c];       // +0x10
    void*   mpObj3c;            // +0x3c loudness source object
};
class tHeldStim {
public:
    float   mf00;               // +0x00 remaining alpha
    uint8_t mPad04[0x3c];       // +0x04
    void*   mpObj40;            // +0x40 held object
};
static const uint32_t kCreatureClassId = 0xd0036e08u;
static inline void* GetComponent(void* pObj)
{
    if (pObj == 0)
        return 0;
    return ((void* (__thiscall*)(void*, uint32_t))((*(void***)pObj)[0x0c / 4]))(
        pObj, kCreatureClassId);
}
class cSpatialObject_s00d8_4c50 {
public:
    virtual void*     v00();            // +0x00
    virtual void*     v04();            // +0x04
    virtual void*     v08();            // +0x08
    virtual void*     v0c();            // +0x0c
    virtual void*     v10();            // +0x10
    virtual void*     v14();            // +0x14
    virtual void*     v18();            // +0x18
    virtual void*     v1c();            // +0x1c
    virtual void*     v20();            // +0x20
    virtual void*     v24();            // +0x24
    virtual void*     v28();            // +0x28
    virtual Vector3*  v2c();            // +0x2c position
    virtual void*     v30();            // +0x30
    virtual void*     v34();            // +0x34
    virtual void*     v38();            // +0x38
    virtual void*     v3c();            // +0x3c
    virtual void*     v40();            // +0x40
    virtual void*     v44();            // +0x44
    virtual bool      v48();            // +0x48
    virtual void*     v4c();            // +0x4c
    virtual void*     v50();            // +0x50
    virtual void*     v54();            // +0x54
    virtual void*     v58();            // +0x58
    virtual Vector3*  v5c(Vector3* pOut);// +0x5c orientation
    virtual void*     v60();            // +0x60
    virtual void*     v64();            // +0x64
    virtual void*     v68();            // +0x68
    virtual void*     v6c();            // +0x6c
    virtual void*     v70();            // +0x70
    virtual float     v74();            // +0x74 radius
    virtual void*     v78();            // +0x78
    virtual void*     v7c();            // +0x7c
    virtual void*     v80();            // +0x80
    virtual void*     v84();            // +0x84
    virtual void*     v88();            // +0x88
    virtual void*     v8c();            // +0x8c
    virtual void*     v90();            // +0x90
    virtual void*     v94();            // +0x94
    virtual void*     v98();            // +0x98
    virtual void*     v9c();            // +0x9c
    virtual void*     va0();            // +0xa0
    virtual void*     va4();            // +0xa4
    virtual void*     va8();            // +0xa8
    virtual void*     vac();            // +0xac
    virtual void*     vb0();            // +0xb0
    virtual void*     vb4();            // +0xb4
    virtual void*     vb8();            // +0xb8
    virtual void*     vbc();            // +0xbc
    virtual void*     vc0();            // +0xc0
    virtual void*     vc4();            // +0xc4
    virtual void*     vc8();            // +0xc8
    virtual void*     vcc();            // +0xcc
    virtual void*     vd0();            // +0xd0
    virtual void*     vd4();            // +0xd4
    virtual void*     vd8();            // +0xd8
    virtual void*     vdc();            // +0xdc
    virtual void*     ve0();            // +0xe0
    virtual void*     ve4();            // +0xe4
    virtual void*     ve8();            // +0xe8
    virtual void      vec();            // +0xec
    virtual void*     vf0();            // +0xf0
    virtual void*     vf4();            // +0xf4
    virtual bool      vf8();            // +0xf8
};
struct cCombatant_s00d8_4c50 {
    uint32_t mVtable;                   // +0x00
};
class cSpatialHolder {
public:
virtual void*    v00();
virtual void* v04();
virtual void* v08();
virtual void* v0c();
virtual void*    v10();
virtual void* v14();
virtual void* v18();
virtual void* v1c();
virtual void*    v20();
virtual void* v24();
virtual void* v28();
    virtual Vector3* v2c();             // +0x2c
};
class cBehaviorObj {
public:
    virtual void*    v00();             // +0x00
    virtual void*    v04();             // +0x04
    virtual void*    v08();             // +0x08
    virtual void*    v0c();             // +0x0c
    virtual int32_t  v10();             // +0x10
};
class cGameNounManager_s00d8_4c50 {
public:
    void* GetAvatar();                  // 0x00b1fdb0
    void* FUN_00b25f40(uint32_t nId);   // 0x00b25f40
};
class cNearNoun_s00d8_4c50 {
public:
    uint8_t mPad00[0x160];              // +0x00
    void*   mpSubObj160;                // +0x160
};
cNearNoun_s00d8_4c50* __fastcall FUN_00c04590(void* pThis);    // 0x00c04590
class cSPCreatureBase_s00d8_4c50 {
public:
virtual void*   v00();
virtual void* v04();
virtual void* v08();
virtual void* v0c();
virtual void*   v10();
virtual void* v14();
virtual void* v18();
virtual void* v1c();
virtual void*   v20();
virtual void* v24();
virtual void* v28();
virtual void* v2c();
virtual void*   v30();
virtual void* v34();
virtual void* v38();
virtual void* v3c();
virtual void*   v40();
virtual void* v44();
    virtual void    v48(void* pArg);                            // +0x048
virtual void*   v4c();
virtual void* v50();
virtual void* v54();
virtual void* v58();
virtual void*   v5c();
virtual void* v60();
virtual void* v64();
virtual void* v68();
virtual void*   v6c();
virtual void* v70();
virtual void* v74();
virtual void* v78();
virtual void*   v7c();
virtual void* v80();
    virtual void    v84(void* pArg, int32_t nA, int32_t nB);    // +0x084
    virtual void*   v88();
    virtual void    v8c();                                      // +0x08c
virtual void*   v90();
virtual void* v94();
virtual void* v98();
virtual void* v9c();
virtual void*   va0();
virtual void* va4();
virtual void* va8();
virtual void* vac();
    virtual void*   vb0();
    virtual int32_t vb4(int32_t nIdx);                          // +0x0b4
    virtual void*   vb8();
    virtual void*   vbc();
    virtual bool    vc0(void* pTarget, float fA, float fB);     // +0x0c0
    virtual void*   vc4();
    virtual void    vc8(int32_t nFlag);                         // +0x0c8
virtual void*   vcc();
virtual void* vd0();
virtual void* vd4();
virtual void* vd8();
virtual void*   vdc();
virtual void* ve0();
    virtual void    ve4(void* pArg);                            // +0x0e4
virtual void*   ve8();
virtual void* vec();
virtual void* vf0();
virtual void* vf4();
virtual void*   vf8();
virtual void* vfc();
virtual void* v100();
virtual void* v104();

    uint8_t        mPad004[0x0c0 - 0x004];  // +0x004
    cSpatialObject_s00d8_4c50 mLoco;                   // +0x0c0 spatial/placement sub-object
    uint8_t        mPad0c4[0x130 - 0x0c4];  // +0x0c4
    void*          mpPropHolder130;         // +0x130 property holder
    uint8_t        mPad134[0x5a8 - 0x134];  // +0x134
    cCombatant_s00d8_4c50     mCombatant;              // +0x5a8
    uint8_t        mPad5ac[0x5e0 - 0x5ac];  // +0x5ac
    float          mf5e0;                   // +0x5e0 previous health
    uint8_t        mPad5e4[0xb48 - 0x5e4];  // +0x5e4
    void*          mpAgentOrderB48;         // +0xb48 agent order manager
    cBehaviorTree_s00d8_4c50* mpBehaviorTreeB4c;       // +0xb4c behaviour tree (its stimuli set sits at +8)
    uint8_t        mPadb50[0xe40 - 0xb50];  // +0xb50
    void*          mpArrayE40;              // +0xe40 lookup array, stride 36 bytes
    uint8_t        mPade44[0x1000 - 0xe44]; // +0xe44
    float          mf1000;                  // +0x1000 accumulated loudness
    uint8_t        mPad1004[0x1698 - 0x1004];
    void*          mpField1698;             // +0x1698 behaviour context object
    float          mf169c;                  // +0x169c

    void*    FUN_00c04590();                                    // 0x00c04590
    int32_t  FUN_00c0c140();                                    // 0x00c0c140
    uint32_t FUN_00c0f780();   // FindFirstValid                 // 0x00c0f780
    void*    FUN_00c0f8a0(uint32_t nIdx);  // GetAt               // 0x00c0f8a0
    void     FUN_00c0d950(int32_t nFlag);                       // 0x00c0d950
    void     FUN_00c0b370(uint32_t nKey);                       // 0x00c0b370
    void     FUN_00c14750(bool bFlag);                          // 0x00c14750
    void     FUN_00c17350(uint32_t nKey, int32_t nFlag);        // 0x00c17350
    int32_t  PlayAnimation(uint32_t nAnim, int32_t nA, int32_t nB);   // 0x00c12190
    void     PlayAnimationWithTarget(uint32_t nAnim, void* pTarget, int32_t nA,
                                     int32_t nB);               // 0x00c14940
    bool     WaitForAnimEventOrEnd(uint32_t nEvent, int32_t* pnOut, int32_t nA,
                                   int32_t nB, int32_t nC);     // 0x00c14ef0
    bool     AnimationFinished(uint32_t nAnim);                 // 0x00c123f0
    bool     IsAnimFinished(uint32_t nAnim);                    // 0x00c12400
    bool     FUN_00c0d560(void* pTarget, float fA, float fB);   // 0x00c0d560
    bool     FUN_00c0c130();                                    // 0x00c0c130
    void*    GetTargetAsCreature();                             // 0x00c0ee70
    void     MoveToPointAtSpeed(int32_t nMode, Vector3* pPoint, float fA, float fB); // 0x00c1c1d0
    void     MoveToPointAndFacingAtSpeed(int32_t nMode, Vector3* pPoint, Vector3* pDir,
                                         float fA, float fB);  // 0x00c1c5c0
};
class tEpicCtx {
public:
    int32_t mn00;               // +0x00 fired animation handle
    bool    mb04;               // +0x04 started
    uint8_t mPad05[0x03];       // +0x05
    int32_t mn08;               // +0x08 valid index
};
// ---- items of slice s00d84c50 end

// ---- items of slice s00d85ad0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const float kOne;          // 0x01485720  1.0
extern const float kTwo;          // 0x01470f1c  2.0
extern const float kThree;        // 0x013eb95c  3.0
extern const float kFive;         // 0x01486110  5.0
extern const float kTen;          // 0x01473c70  10.0
extern const float kFifteen;      // 0x014007f4  15.0
extern const float kSixty;        // 0x013ebc4c  60.0
extern const float kFifty;        // 0x013f1cac  50.0
extern const float kPointNine;    // 0x013ec4b4  0.9
extern const float kHalf;         // 0x01471064  0.5
extern const float kFloatMax;     // 0x0147c030  FLT_MAX
extern const float kZero;         // 0x01485378  0.0
extern const float kPropDefault;  // 0x014853bc  default death time
extern const float kEffect14;     // 0x0169f03c
extern const float kEffect18;     // 0x0169f040
extern const float kEffect1c;     // 0x0169f044
extern const float kSpec04;       // 0x0169f0d4
extern const float kSpec08;       // 0x0169f0d8
extern const float kSpec0c;       // 0x0169f0dc
extern const float kRadiusScale;  // 0x01582e7c
extern const float kEvolveSpeed;  // 0x015d9c6c
extern const char  gModeCreatureA;  // 0x01654c10  (creature-mode sentinel)
extern const char  gModeCreatureB;  // 0x01654c01
extern const char  gModeCreatureC;  // 0x01654c02
extern const char  gSpecMatrix;     // 0x0169f0b0  (Matrix33 source)
extern void*       gPropertyList;   // 0x01581288
#define PV_s00d8_5ad0(n) virtual void pv##n();
struct Vec3_s00d8_5ad0 { float x, y, z; };
class cInteractableObject_s00d8_5ad0;
class cObj {
public:
    virtual void AddRef();                        // +0x00
    virtual void Release();                       // +0x04
    virtual void vf08(int a);                     // +0x08
    PV_s00d8_5ad0(3) PV_s00d8_5ad0(4) PV_s00d8_5ad0(5)
    virtual void vf18(void* p);                   // +0x18
    PV_s00d8_5ad0(7)
    virtual void vf20(void* p);                   // +0x20
    PV_s00d8_5ad0(9) PV_s00d8_5ad0(10)
    virtual const Vec3_s00d8_5ad0* GetPosition();            // +0x2c
    PV_s00d8_5ad0(12) PV_s00d8_5ad0(13) PV_s00d8_5ad0(14) PV_s00d8_5ad0(15) PV_s00d8_5ad0(16) PV_s00d8_5ad0(17) PV_s00d8_5ad0(18) PV_s00d8_5ad0(19) PV_s00d8_5ad0(20) PV_s00d8_5ad0(21) PV_s00d8_5ad0(22) PV_s00d8_5ad0(23)
    PV_s00d8_5ad0(24) PV_s00d8_5ad0(25) PV_s00d8_5ad0(26) PV_s00d8_5ad0(27) PV_s00d8_5ad0(28)
    virtual float GetRadius();                    // +0x74
    PV_s00d8_5ad0(30) PV_s00d8_5ad0(31) PV_s00d8_5ad0(32) PV_s00d8_5ad0(33) PV_s00d8_5ad0(34) PV_s00d8_5ad0(35) PV_s00d8_5ad0(36) PV_s00d8_5ad0(37) PV_s00d8_5ad0(38) PV_s00d8_5ad0(39) PV_s00d8_5ad0(40) PV_s00d8_5ad0(41)
    PV_s00d8_5ad0(42) PV_s00d8_5ad0(43) PV_s00d8_5ad0(44) PV_s00d8_5ad0(45)
    virtual cObj* Query(uint32_t id);             // +0xb8
    virtual void AddRefBundle();                  // +0xbc
    virtual void ReleaseBundle();                 // +0xc0
};
class cNoun {
public:
    virtual void AddRef();                        // +0x00
    virtual void Release();                       // +0x04
    PV_s00d8_5ad0(2) PV_s00d8_5ad0(3) PV_s00d8_5ad0(4) PV_s00d8_5ad0(5) PV_s00d8_5ad0(6) PV_s00d8_5ad0(7) PV_s00d8_5ad0(8) PV_s00d8_5ad0(9) PV_s00d8_5ad0(10)
    virtual bool IsFinished();                    // +0x2c
};
class cLoco {
public:
    PV_s00d8_5ad0(0) PV_s00d8_5ad0(1) PV_s00d8_5ad0(2) PV_s00d8_5ad0(3) PV_s00d8_5ad0(4) PV_s00d8_5ad0(5) PV_s00d8_5ad0(6) PV_s00d8_5ad0(7) PV_s00d8_5ad0(8) PV_s00d8_5ad0(9) PV_s00d8_5ad0(10)
    virtual const Vec3_s00d8_5ad0* GetPosition();            // +0x2c
    PV_s00d8_5ad0(12) PV_s00d8_5ad0(13) PV_s00d8_5ad0(14) PV_s00d8_5ad0(15)
    virtual void vf40(float f);                   // +0x40
    PV_s00d8_5ad0(17) PV_s00d8_5ad0(18) PV_s00d8_5ad0(19) PV_s00d8_5ad0(20) PV_s00d8_5ad0(21) PV_s00d8_5ad0(22) PV_s00d8_5ad0(23) PV_s00d8_5ad0(24) PV_s00d8_5ad0(25) PV_s00d8_5ad0(26) PV_s00d8_5ad0(27) PV_s00d8_5ad0(28)
    virtual float GetRadius();                    // +0x74
    PV_s00d8_5ad0(30) PV_s00d8_5ad0(31) PV_s00d8_5ad0(32) PV_s00d8_5ad0(33) PV_s00d8_5ad0(34) PV_s00d8_5ad0(35) PV_s00d8_5ad0(36) PV_s00d8_5ad0(37) PV_s00d8_5ad0(38) PV_s00d8_5ad0(39) PV_s00d8_5ad0(40) PV_s00d8_5ad0(41)
    PV_s00d8_5ad0(42) PV_s00d8_5ad0(43) PV_s00d8_5ad0(44) PV_s00d8_5ad0(45) PV_s00d8_5ad0(46) PV_s00d8_5ad0(47) PV_s00d8_5ad0(48) PV_s00d8_5ad0(49) PV_s00d8_5ad0(50) PV_s00d8_5ad0(51) PV_s00d8_5ad0(52) PV_s00d8_5ad0(53)
    PV_s00d8_5ad0(54)
    virtual void PlayEffectSpec(void* spec);      // +0xdc
    PV_s00d8_5ad0(56) PV_s00d8_5ad0(57) PV_s00d8_5ad0(58) PV_s00d8_5ad0(59) PV_s00d8_5ad0(60) PV_s00d8_5ad0(61)
    virtual bool vfF8();                          // +0xf8
    float __thiscall FUN_00c887c0();              // 0x00c887c0, ret 0
};
class BehaviorTreeHead {
public:
    cObj* __thiscall Play(unsigned id, int flags);      // 0x00bc96a0, ret 8
    void  __thiscall ClearAll(unsigned a, unsigned mask);  // 0x00bc98f0, ret 8
};
struct nSPBehaviorTree_s00d8_5ad0 {
    uint32_t pad00[2];                            // +0x00..+0x07
    BehaviorTreeHead mHead;                       // +0x08
};
class cAnimNode {
public:
    uint32_t pad00[3];                            // +0x00
    int      mKind;                               // +0x0c
    int      m10;                                 // +0x10
    int      mAnim14;                             // +0x14
    int      mAnim18;                             // +0x18
    uint32_t pad1c[4];                            // +0x1c..+0x2b
    cObj*    mpBundle2c;                          // +0x2c
};
class cB54 {
public:
    uint32_t pad00[0x80 / 4];                     // +0x00..+0x7f
    float    mf80;                                // +0x80
};
class Citizen;
class cGameNounManager_s00d8_5ad0 {
public:
    uint32_t pad00[0x54 / 4];                     // +0x000
    Citizen* mpAvatar;                            // +0x054
    uint32_t pad58[(0x70 - 0x58) / 4];            // +0x058
    void*    mpPlayer;                            // +0x070
    void* __thiscall GetAvatar();                 // 0x00b1fdb0, ret 0
    void* __thiscall GetPlayerTribe();            // 0x00bfc5f0, ret 0
    void  __thiscall RemoveNoun(void* noun);      // 0x00b225d0, ret 4
};
class cCreatureSettings {
public:
    uint32_t pad00[0x504 / 4];                    // +0x000
    Vec3_s00d8_5ad0     mPos504;                             // +0x504
    uint32_t pad510[(0x590 - 0x510) / 4];         // +0x510..+0x58f
    float    mf590;                               // +0x590
    uint32_t pad594[(0x73c - 0x594) / 4];         // +0x594..+0x73b
    cObj**   mpBegin73c;                          // +0x73c
    cObj**   mpEnd740;                            // +0x740
};
class cFoodTarget {
public:
    uint32_t pad00[2];                            // +0x00..+0x07
    int      mType08;                             // +0x08  0x1b = edible corpse
    uint32_t pad0c[0x100 / 4];                    // +0x0c..+0x10b
    float    mf10c;                               // +0x10c  freshness / value
    uint32_t pad110[8];                           // +0x110..+0x12f
    void*    mpProps130;                          // +0x130
};
class Citizen {
public:
    PV_s00d8_5ad0(0) PV_s00d8_5ad0(1) PV_s00d8_5ad0(2) PV_s00d8_5ad0(3) PV_s00d8_5ad0(4) PV_s00d8_5ad0(5) PV_s00d8_5ad0(6) PV_s00d8_5ad0(7) PV_s00d8_5ad0(8) PV_s00d8_5ad0(9) PV_s00d8_5ad0(10) PV_s00d8_5ad0(11) PV_s00d8_5ad0(12) PV_s00d8_5ad0(13)
    PV_s00d8_5ad0(14) PV_s00d8_5ad0(15) PV_s00d8_5ad0(16) PV_s00d8_5ad0(17) PV_s00d8_5ad0(18)
    virtual int   vf4c();                         // +0x4c
    PV_s00d8_5ad0(20) PV_s00d8_5ad0(21) PV_s00d8_5ad0(22) PV_s00d8_5ad0(23) PV_s00d8_5ad0(24) PV_s00d8_5ad0(25) PV_s00d8_5ad0(26) PV_s00d8_5ad0(27) PV_s00d8_5ad0(28) PV_s00d8_5ad0(29) PV_s00d8_5ad0(30) PV_s00d8_5ad0(31)
    virtual float vf80(int a);                    // +0x80
    virtual void  vf84(void* obj, int a, int b);  // +0x84
    PV_s00d8_5ad0(34)
    virtual void  vf8c();                         // +0x8c
    uint8_t  pad04[0xc0 - 4];                     // +0x04..+0xbf (vptr first)
    cLoco    mLoco;                               // +0xc0
    uint32_t padC4[(0x110 - 0xc4) / 4];           // +0xc4..+0x10f
    uint32_t mFlags110;                           // +0x110
    uint8_t  pad114[0x12f - 0x114];               // +0x114..+0x12e
    uint8_t  mb12f;                               // +0x12f
    uint8_t  pad130[1];                           // +0x130
    uint8_t  mb131;                               // +0x131
    uint8_t  pad132[0x137 - 0x132];               // +0x132..+0x136
    uint8_t  mb137;                               // +0x137
    uint8_t  pad138[0xb20 - 0x138];               // +0x138..+0xb1f
    cCreatureSettings* mpSettings;                // +0xb20
    uint8_t  padB24[0xb4c - 0xb24];               // +0xb24..+0xb4b
    nSPBehaviorTree_s00d8_5ad0*   mpBehavior;                // +0xb4c
    uint8_t  padB50[0xb54 - 0xb50];               // +0xb50..+0xb53
    cB54*    mpB54;                               // +0xb54
    union {
        volatile uint32_t mFlagsB58;              // +0xb58..+0xb5b
        struct {
            uint16_t mB58lo;                      // +0xb58
            uint8_t  mbB5a;                       // +0xb5a
            uint8_t  mB58hi;                      // +0xb5b
        } mB58;
    };
    uint8_t  padB5c[0xb5e - 0xb5c];               // +0xb5c..+0xb5d
    uint8_t  mbB5e;                               // +0xb5e
    uint8_t  padB5f[0xb7c - 0xb5f];               // +0xb5f..+0xb7b
    float    mfB7c;                               // +0xb7c
    uint8_t  padB80[0xbbc - 0xb80];               // +0xb80..+0xbbb
    float    mfBbc;                               // +0xbbc
    uint8_t  padBC0[0x1004 - 0xbc0];              // +0xbc0..+0x1003
    Vec3_s00d8_5ad0     mVec1004;                            // +0x1004
    uint8_t  pad1010[0x1674 - 0x1010];            // +0x1010..+0x1673
    void*    mpPlayer;                            // +0x1674

    float __thiscall GetFood();                   // 0x00c0b9c0, ret 0
    void  __thiscall SetFood(float f);            // 0x00c0b9d0, ret 4
    bool  __thiscall Flag388();                   // 0x00c0c0e0, ret 0
    void* __thiscall GetPlayer();                 // 0x00c04590, ret 0
    void* __thiscall GetGameData();               // 0x00c04750, ret 0
    void* __thiscall GetFoodPos();                // 0x00c0bc00, ret 0
    void  __thiscall FUN_00c0bbe0();              // 0x00c0bbe0, ret 0
    void  __thiscall FUN_00c0d240();              // 0x00c0d240, ret 0
    void  __thiscall FUN_00c14750(int a);         // 0x00c14750, ret 4
    void  __thiscall FUN_00c15bd0(int a, int b, int c);  // 0x00c15bd0, ret 0xc
    bool  __thiscall FUN_00c13c60(void* obj, int a, int b);  // 0x00c13c60, ret 0xc
    bool  __thiscall FUN_00c0f5f0();              // 0x00c0f5f0, ret 0
    int   __thiscall FUN_00c0f8f0(void* obj);     // 0x00c0f8f0, ret 4
    int   __thiscall FUN_00c0f4f0();              // 0x00c0f4f0, ret 0
    void  __thiscall FUN_00c19940(int a);         // 0x00c19940, ret 4
    void  __thiscall SetStealthed(int a, int b);  // 0x00c1aed0, ret 8
    int   __thiscall InterruptAnimation(unsigned id, int a, int b);  // 0x00c12310, ret 0xc
    int   __thiscall PlayAnimation(unsigned id, int a, int b);       // 0x00c12190, ret 0xc
    void* __thiscall GetTargetAsCreature();       // 0x00c0ee70, ret 0
    void  __thiscall MoveToPointAtSpeed(int mode, const Vec3_s00d8_5ad0* p, float f1, float f2);  // 0x00c1c1d0
    void  __thiscall MoveToPointAndFacingAtSpeed(int mode, const Vec3_s00d8_5ad0* p, const Vec3_s00d8_5ad0* dir,
                                                 float f1, float f2);  // 0x00c1c5c0, ret 0x14
    void* __thiscall SpecQuery(int a);            // 0x00c1d290, ret 4
};
void* __cdecl PlanetModel_s00d8_5ad0();                              // 0x00b3d350
void* __cdecl FUN_00b3d310();                             // 0x00b3d310
void  __cdecl FUN_00b453a0();                             // 0x00b453a0 (reads ecx + stack slot)
void  __cdecl FUN_00b57bf0(void* bundleA, void* bundleB, float f);  // 0x00b57bf0
void  __cdecl FUN_00b54300(void* bundleA, void* obj);     // 0x00b54300
void  __cdecl FUN_00b530e0(void* obj, int a);             // 0x00b530e0
cObj* __cdecl FUN_00d998d0_s00d8_5ad0(cAnimNode* node, unsigned id); // 0x00d998d0
cObj* __cdecl FUN_00d7cf70(void* holder);                 // 0x00d7cf70, ret 4
cObj* __cdecl FUN_00d7cf90(void* holder);                 // 0x00d7cf90, ret 4
void  __cdecl FUN_00d2e8a0(float value);                  // 0x00d2e8a0
void  __cdecl FUN_00f47380(void* p);                      // 0x00f47380 operator delete[]
float __cdecl FUN_004e1c70(void* props, unsigned id, float def);  // 0x004e1c70
bool  __cdecl FUN_0064f350(void* props, unsigned id, int unused);  // 0x0064f350
bool  __fastcall FUN_00c8e870(void* p);            // 0x00c8e870
class cPlanetModel_s00d8_5ad0 {
public:
    Vec3_s00d8_5ad0* __thiscall MakeRandomWorldPosition(Vec3_s00d8_5ad0* out, const Vec3_s00d8_5ad0* pos, float near, float range);  // 0x00b81780 (cPlanetModel::MakeRandomWorldPosition)
};
class cMatrix3 {
public:
    void __thiscall Assign(const void* src);      // 0x0041cb40, ret 4
};
class cCreatureModeStrategy {
public:
    uint32_t pad00[0xb4 / 4];                     // +0x000..+0x0b3
    cObj*    mpB4;                                // +0x0b4
    void __thiscall SignalCreatureEvent(unsigned id);  // 0x00d3cdc0
};
cCreatureModeStrategy* __cdecl FUN_00d38840();    // 0x00d38840
struct StateDeath {                                // 0x00d85c00
    float    mf0;                                  // +0x00  time/death duration
    float    mf4;                                  // +0x04
    float    mf8;                                  // +0x08
    float    mfc;                                  // +0x0c
    int      mEffect10;                            // +0x10  effect/anim key
    uint8_t  mb14;                                 // +0x14
    uint8_t  mb15;                                 // +0x15
    uint8_t  mb16;                                 // +0x16  corpse flag
    uint8_t  mb17;                                 // +0x17  eaten-by-avatar flag
};
struct StateSit {                                  // 0x00d86130
    uint32_t pad00[4];                             // +0x00..+0x0f
    float    mf10;                                 // +0x10
    uint32_t pad14[3];                             // +0x14..+0x1f
    cNoun*   mp20;                                 // +0x20
};
struct StateEvolve {                               // 0x00d85f20
    int      m0;                                   // +0x00
    int      m4;                                   // +0x04
    int      m8;                                   // +0x08
    float    mf0c;                                 // +0x0c  evolve duration
    float    mf10;                                 // +0x10
    Vec3_s00d8_5ad0     mPos;                                 // +0x14
    cObj*    m20;                                  // +0x20
};
struct StateSitHead {                              // 0x00d86240
    int      m0;                                   // +0x00
    int      m4;                                   // +0x04
    uint8_t  mb08;                                 // +0x08
    uint8_t  pad09[3];                             // +0x09..+0x0b
    int      m0c;                                  // +0x0c
    uint8_t  mb10;                                 // +0x10
    uint8_t  mb11;                                 // +0x11
    uint8_t  mb12;                                 // +0x12
};
struct StateItemOnHead {                           // 0x00d86410 / 0x00d865c0
    int      m0;                                   // +0x00
    int      m4;                                   // +0x04
    int      m8;                                   // +0x08
    cObj*    mp0c;                                 // +0x0c
    cObj*    mp10;                                 // +0x10
    uint8_t  mb14;                                 // +0x14
};
struct StateReceive {                              // 0x00d86690 / 0x00d86850
    cObj*    mp0;                                  // +0x00
    int      m4;                                   // +0x04
    cObj*    mp8;                                  // +0x08
    int      m0c;                                  // +0x0c
};
struct StateReact {                                // 0x00d86810
    cObj*    mp0;                                  // +0x00
};
struct StateDig {                                  // 0x00d86940
    int      m0;                                   // +0x00
    uint32_t pad04;                                // +0x04
    cInteractableObject_s00d8_5ad0* mp8;                      // +0x08
};
struct RefHolder {
    cObj* mp;
    void  __thiscall Assign(cObj* p);             // 0x00c70110, ret 4
};
struct AutoRef {
    cObj* mp;
    AutoRef& __thiscall operator=(cObj* p);       // 0x00b5f950, ret 4
};
class cOrnament_s00d8_5ad0 {
public:
    uint32_t pad00[(0x108 - 0) / 4];              // +0x000
    cObj*    mp108;                                // +0x108
    uint32_t pad10c[(0x16c - 0x10c) / 4];         // +0x10c
    int      mState16c;                            // +0x16c
};
class cInteractiveOrnament {
public:
    uint32_t pad00[(0x238 - 0) / 4];              // +0x000
    uint32_t mFlags238;                            // +0x238
    void __thiscall SetLifetime(float lifetime, int flag);  // 0x00c40830, ret 8
};
class cInteractableObject_s00d8_5ad0 {
public:
    virtual void AddRef();                        // +0x00
    virtual void Release();                       // +0x04
    PV_s00d8_5ad0(2) PV_s00d8_5ad0(3) PV_s00d8_5ad0(4) PV_s00d8_5ad0(5) PV_s00d8_5ad0(6) PV_s00d8_5ad0(7) PV_s00d8_5ad0(8) PV_s00d8_5ad0(9) PV_s00d8_5ad0(10)
    PV_s00d8_5ad0(11) PV_s00d8_5ad0(12) PV_s00d8_5ad0(13) PV_s00d8_5ad0(14) PV_s00d8_5ad0(15) PV_s00d8_5ad0(16) PV_s00d8_5ad0(17) PV_s00d8_5ad0(18) PV_s00d8_5ad0(19) PV_s00d8_5ad0(20) PV_s00d8_5ad0(21) PV_s00d8_5ad0(22)
    PV_s00d8_5ad0(23) PV_s00d8_5ad0(24) PV_s00d8_5ad0(25) PV_s00d8_5ad0(26) PV_s00d8_5ad0(27) PV_s00d8_5ad0(28) PV_s00d8_5ad0(29) PV_s00d8_5ad0(30) PV_s00d8_5ad0(31) PV_s00d8_5ad0(32) PV_s00d8_5ad0(33) PV_s00d8_5ad0(34)
    PV_s00d8_5ad0(35) PV_s00d8_5ad0(36) PV_s00d8_5ad0(37) PV_s00d8_5ad0(38) PV_s00d8_5ad0(39) PV_s00d8_5ad0(40) PV_s00d8_5ad0(41) PV_s00d8_5ad0(42) PV_s00d8_5ad0(43) PV_s00d8_5ad0(44) PV_s00d8_5ad0(45)
    virtual cOrnament_s00d8_5ad0* Query(uint32_t id);        // +0xb8
    virtual void AddRefBundle();                  // +0xbc
    virtual void ReleaseBundle();                 // +0xc0
    uint8_t  pad04[0x70 - 4];                     // +0x04..+0x6f
    uint8_t  mb70;                                // +0x70
    uint8_t  pad71[0x108 - 0x71];                 // +0x71..+0x107
    cObj*    mp108;                               // +0x108
    uint8_t  pad10c[0x16c - 0x10c];               // +0x10c..+0x16b
    int      mState16c;                            // +0x16c
};
struct Mat33 { float m[9]; };
struct EffectSpecSmall {                          // 0x00d85e40: 0x38 bytes
    short    m00;                                  // +0x00
    short    m02;                                  // +0x02
    float    mf04;                                 // +0x04
    float    mf08;                                 // +0x08
    float    mf0c;                                 // +0x0c
    float    mf10;                                 // +0x10
    Mat33    mMat;                                 // +0x14
};
struct EffectSpec {                                // 0x00d86240: 0x78 bytes
    void*    mpData;                               // +0x00
    void*    mpEnd;                                // +0x04
    void*    mpCap;                                // +0x08
    uint32_t m0c;                                  // +0x0c
    float    mf10;                                 // +0x10
    float    mf14;                                 // +0x14
    float    mf18;                                 // +0x18
    float    mf1c;                                 // +0x1c
    float    mf20;                                 // +0x20
    uint32_t m24;                                  // +0x24
    int      m28;                                  // +0x28
    uint8_t  pad2c[0x50 - 0x2c];                   // +0x2c..+0x4f
    uint8_t  mb50;                                 // +0x50
    uint8_t  pad51[3];                             // +0x51..+0x53
    float    mf54;                                 // +0x54
    float    mf58;                                 // +0x58
    float    mf5c;                                 // +0x5c
    float    mf60;                                 // +0x60
    float    mf64;                                 // +0x64
    uint32_t m68;                                  // +0x68
    float    mf6c;                                 // +0x6c
    float    mf70;                                 // +0x70
    int      m74;                                  // +0x74
};
class cB4Obj {
public:
    PV_s00d8_5ad0(0) PV_s00d8_5ad0(1) PV_s00d8_5ad0(2) PV_s00d8_5ad0(3) PV_s00d8_5ad0(4) PV_s00d8_5ad0(5) PV_s00d8_5ad0(6) PV_s00d8_5ad0(7) PV_s00d8_5ad0(8)
    virtual bool Query(uint32_t id, void** out);  // +0x24
};
struct Variant {
    uint32_t m0;                                   // +0x00  value or pointer
    uint8_t  mFlags10;                             // +0x10  bit 0x30 = by reference
    uint8_t  pad11;                                // +0x11
    uint16_t mType12;                              // +0x12  0x0d/0x10 = numeric
};
class cPlayerNear {
public:
    uint8_t pad00[0x34];                           // +0x00..+0x33
    cLoco   mBundle;                               // +0x34
};
class cPlayerData {
public:
    uint8_t pad00[0x160];                          // +0x000..+0x15f
    cPlayerNear* mpNear160;                        // +0x160
    const Vec3_s00d8_5ad0* __thiscall GetPosition();          // 0x00c6acc0, ret 0
};
class cGlobalMgr {
public:
    void __thiscall FUN_00b453a0(void* loco);      // 0x00b453a0, ret 4
};
// ---- items of slice s00d85ad0 end

// ---- items of slice s00d86a30 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void* g1590c40;
typedef signed int s32_s00d8_6a30;
typedef float f32;
#define VT(p) (*(void***)(p))
#define MOPS(p) ((COps*)(p))
struct COps;
struct cSub34 { void* mVtbl; };
struct cNodeState {
    u32 m0;                         // +0x00
    union U4 { void* p; u32 u; u8 b; } m4;       // +0x04
    union U8 { void* p; u32 u; } m8;             // +0x08
    union UC { void* p; u32 u; u8 b; } mC;       // +0x0c
    union U10 { u32 u; f32 f; u8 b; u8 pad[3]; } m10; // +0x10
    union U14 { u32 u; f32 f; } m14;             // +0x14
    union U18 {
        u32 u;
        f32 f;
        struct { u8 b18; u8 b19; u8 pad[2]; } bytes;
    } m18;                           // +0x18
    union U1C { void* p; u8 b; } m1C; // +0x1c
    u32 m20;                         // +0x20
    u8 m24;                          // +0x24
    u8 pad25[3];
    union U28 { void* p; u32 u; } m28; // +0x28
    u8 m2C;                          // +0x2c
    u8 pad2D[3];
    u32 m30;                         // +0x30
};
struct cCreatureEntry {
    u32 mId;                         // +0x00
    u32 pad04[7];                    // +0x04
    void* mObj20;                    // +0x20
};
struct cB20 {
    u8 pad0[0x590];
    f32 m590;                        // +0x590
};
struct cStimuli { u8 pad0[8]; };
struct cBehaviorTree_s00d8_6a30 {
    u32 pad0[2];
    cStimuli mStimuli;               // +0x08
};
struct cCreatureSub { void* mVtbl; };
struct cCreature {
    u8 pad000[0xC0];
    cCreatureSub mC0;                // +0xc0
    u8 padC4[0x108 - 0xC4];
    void* m108;                      // +0x108
    u8 pad10C[0xB20 - 0x10C];
    cB20* mB20;                      // +0xb20
    u8 padB24[0xB4C - 0xB24];
    cBehaviorTree_s00d8_6a30* mB4C;             // +0xb4c
    u8 padB50[0xB58 - 0xB50];
    u32 mB58;                        // +0xb58
    u8 mB5C;                         // +0xb5c
    u8 padB5D[0xE40 - 0xB5D];
    cCreatureEntry* mE40;            // +0xe40
};
struct cAnimObj {
    void* mVtbl;                     // +0x00
    u32 pad04[2];
    u32 m0C;                         // +0x0c
    u32 m10;                         // +0x10
    u32 pad14[6];
    void* m2C;                       // +0x2c
    u32 pad30;
    cSub34 m34;                      // +0x34
    u8 pad38[0x68 - 0x38];
    void* m68;                       // +0x68
    u8 pad6C[0xA3 - 0x6C];
    u8 mA3;                          // +0xa3
    u8 padA4[0xA9 - 0xA4];
    u8 mA9;                          // +0xa9
    u8 padAA[0x108 - 0xAA];
    void* m108;                      // +0x108
    u8 pad10C[0x148 - 0x10C];
    u8 m148;                         // +0x148
    u8 pad149[0x16C - 0x149];
    u32 m16C;                        // +0x16c
};
struct cHolder_s00d8_6a30 {
    u8 pad0[0x160];
    cAnimObj* m160;                  // +0x160
};
struct COps {
    u32 FUN_00c0f780();
    void FUN_00bc98f0(u32 a, u32 b);
    void* FUN_00bc96a0(u32 a, u32 b);
    void FUN_00c14750(u32 a);
    u8 FUN_00c14ef0(u32 a, void* b, u32 c, u32 d, u32 e);
    u8 FUN_00c12400(u32 a);
    s32_s00d8_6a30 FUN_00c40200();
    void* FUN_00b5f950(void* obj);
    u32 FUN_00c0ee60(u32 a, u32 b);
    void* FUN_00c04590();
    void FUN_00c15d50(void* a, u32 b, u32 c);
    void FUN_00b225d0(void* noun);
    s32_s00d8_6a30 FUN_00c0f4f0();
    u8 FUN_00c0f5f0();
    void FUN_00c15bd0(u32 a, u32 b, u32 c);
    void FUN_00c1c5c0(u32 a, void* b, u32 c);
    u8 FUN_00c42e20();
    u32 FUN_00c14990(u32 a, void* b, s32_s00d8_6a30 c);
    void FUN_00d39360(u32 a, void* b);
};
void* __cdecl FUN_00ad2670(void* arg);
void* __cdecl FUN_00d38840_s00d8_6a30();
void* __cdecl FUN_0067dcc0();
f32 __cdecl FUN_00572a10(f32 a, f32 b);
void* __stdcall FUN_00b3d300(void* noun);
void __cdecl FUN_00d7d2c0(void* a, void* b);
void __cdecl FUN_00d85540(void* a);
u32 __cdecl FUN_00436ce0(void* out, void* in, f32 a, f32 b);
extern f32 g169f03c;
extern f32 g169f040;
extern f32 g169f044;
extern f32 g13ec4b4;
extern f32 g147c030;
static const f32 kZero_s00d8_6a30 = 0.0f;
static const f32 kHalf_s00d8_6a30 = 0.5f;
static const f32 kOne_s00d8_6a30 = 1.0f;
static const f32 kTwo_s00d8_6a30 = 2.0f;
static const f32 kFour = 4.0f;
static const f32 kTenth = 0.1f;
// ---- items of slice s00d86a30 end

// ---- items of slice s00d87620 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int   uintptr_t;
struct Vec3_s00d8_7620 { float x, y, z; };
struct SpatSub {
virtual void  pad00();
virtual void  pad01();
virtual void  pad02();
virtual void  pad03();
virtual void  pad04();
virtual void  pad05();
virtual void  pad06();
virtual void  pad07();
virtual void  pad08();
virtual void  pad09();
virtual void  pad0a();
virtual void  pad0b();
  virtual Vec3_s00d8_7620* GetPosition(Vec3_s00d8_7620* out);          // slot 11 (0x2c)
virtual void  pad0c();
virtual void  pad0d();
virtual void  pad0e();
virtual void  pad0f();
virtual void  pad10();
virtual void  pad11();
  virtual bool  Flag48();                        // slot 18 (0x48)
virtual void  pad13();
virtual void  pad14();
virtual void  pad15();
virtual void  pad16();
virtual void  pad17();
virtual void  pad18();
virtual void  pad19();
  virtual Vec3_s00d8_7620* GetBounds();                     // slot 26 (0x68)
  virtual void  pad1b();
  virtual float GetScale74();                    // slot 29 (0x74)
virtual void  pad1d();
virtual void  pad1e();
virtual void  pad1f();
virtual void  pad20();
virtual void  pad21();
virtual void  pad22();
virtual void  pad23();
virtual void  pad24();
virtual void  pad25();
virtual void  pad26();
virtual void  pad27();
virtual void  pad28();
virtual void  pad29();
virtual void  pad2a();
virtual void  pad2b();
virtual void  pad2c();
virtual void  pad2d();
virtual void  pad2e();
virtual void  pad2f();
virtual void  pad30();
virtual void  pad31();
virtual void  pad32();
virtual void  pad33();
virtual void  pad34();
virtual void  pad35();
virtual void  pad36();
virtual void  pad37();
virtual void  pad38();
virtual void  pad39();
virtual void  pad3a();
  virtual void  Notify();                        // slot 59 (0xec)
};
struct AnimSub {
virtual void  pad00();
virtual void  pad01();
virtual void  pad02();
virtual void  pad03();
virtual void  pad04();
virtual void  pad05();
virtual void  pad06();
virtual void  pad07();
virtual void  pad08();
virtual void  pad09();
virtual void  pad0a();
virtual void  pad0b();
virtual void  pad0c();
virtual void  pad0d();
virtual void  pad0e();
virtual void  pad0f();
  virtual void  SetFloat40(float v);             // slot 16 (0x40)
virtual void  pad11();
virtual void  pad12();
virtual void  pad13();
virtual void  pad14();
virtual void  pad15();
virtual void  pad16();
virtual void  pad17();
virtual void  pad18();
virtual void  pad19();
virtual void  pad1a();
  virtual Vec3_s00d8_7620* GetBox6c(Vec3_s00d8_7620* out);             // slot 27 (0x6c)
  virtual float GetF70();                        // slot 28 (0x70)
  virtual float GetDist74();                     // slot 29 (0x74)
};
struct TimerSub {
virtual void  pad00();
virtual void  pad01();
virtual void  pad02();
virtual void  pad03();
virtual void  pad04();
virtual void  pad05();
virtual void  pad06();
virtual void  pad07();
virtual void  pad08();
virtual void  pad09();
virtual void  pad0a();
virtual void  pad0b();
virtual void  pad0c();
virtual void  pad0d();
virtual void  pad0e();
virtual void  pad0f();
virtual void  pad10();
virtual void  pad11();
  virtual float GetElapsed58();                  // slot 22 (0x58)
};
struct RefCnt {
  virtual void  AddRef();
  virtual void  Release();
};
struct AutoRef_s00d8_7620 { RefCnt* mp; };
struct Creature_s00d8_7620 {
  RefCnt*  mpVtbl;                 // 0x000
  u8       pad004[0xc0 - 4];
  SpatSub  mSpatial;               // 0x0c0
  u8       pad0c4[0x5a8 - 0xc4];
  TimerSub mTimer;                 // 0x5a8
  u8       pad5ac[0x5e0 - 0x5ac];
  float    mF_5e0;                 // 0x5e0
  u8       pad5e4[0xb20 - 0x5e4];
  void*    mpProfile_5b20;         // 0xb20
  u8       padB24[0xb4c - 0xb24];
  void*    mpStimuliMgr;           // 0xb4c  (manager; +8 is the behaviour_stimuli)
  void*    mpAnimWorld_5b54;       // 0xb54  (creature animation instance)
  u32      mFlags_5b58;            // 0xb58  (bit 9 tested)
};
struct ActorSub {
  u8       pad000[0x34];
  AnimSub  mAnim;                  // 0x034
  u8       pad038[0x16c - 0x38];
  s32      mState_16c;             // 0x16c
};
struct Stimuli_s00d8_7620 {
  s32 pad[2];
  void ClearAll(int, int);              // 0xbc98f0
  void* Set(int, int, float, u32);      // 0xbc97f0
};
struct EatFruitNode {
  s32   mState;              // 0x00
  s32   mSub;                // 0x04
  RefCnt* mpActor;           // 0x08
  s32   mPad0c;              // 0x0c
  u32   mAnimKey;            // 0x10
  s32   mAnimHandle;         // 0x14
  u8    mbFlag18;            // 0x18
  u8    mPad19[3];
  RefCnt* mpInteract;        // 0x1c
  u32   mIndex;              // 0x20
  u8    mbFlag24;            // 0x24
  u8    mPad25[3];
  AutoRef_s00d8_7620 mTarget;           // 0x28
  u8    mbFlag2c;            // 0x2c
  u8    mPad2d[3];
  s32   mPartIndex;          // 0x30
};
struct PlanetModel_s00d8_7620 {
  Vec3_s00d8_7620* DirectionToSurfacePosition(Vec3_s00d8_7620* out, Vec3_s00d8_7620* in);   // 0x00b815a0
  Vec3_s00d8_7620* GetSurfacePos(Vec3_s00d8_7620* out, Vec3_s00d8_7620* in);                // 0x00b81630
};
void  __cdecl FUN_00b02b90(Vec3_s00d8_7620* out, u32 id);            // 0x00b02b90
u32   __cdecl FUN_00d998d0_s00d8_7620(u32, u32);                     // 0x00d998d0
void* __cdecl FUN_00c3e790();                             // 0x00c3e790
void* __cdecl FUN_00b2a690();                             // 0x00b2a690 (ecx=?)
bool  __cdecl FUN_00c0b7a0(Creature_s00d8_7620*);                    // 0x00c0b7a0
void  __cdecl FUN_00d85540(Creature_s00d8_7620*);                    // 0x00d85540
PlanetModel_s00d8_7620* __cdecl PlanetModel_Get();                   // 0x00b3d350
Vec3_s00d8_7620* __cdecl normalized_safe(Vec3_s00d8_7620* out, Vec3_s00d8_7620* in);       // 0x00449c20
void* __cdecl FUN_00401090_s00d8_7620();                             // 0x00401090
void  __cdecl FUN_00c15d50(Creature_s00d8_7620*, void*, u32, u32);   // 0x00c15d50
u32   __cdecl FUN_00d7d370(Creature_s00d8_7620*, Vec3_s00d8_7620*);             // 0x00d7d370
bool  __cdecl FUN_00c1ac70(Creature_s00d8_7620*, Vec3_s00d8_7620*, u32, u32, u32, u32, float); // 0x00c1ac70
struct CreatBase {
  bool  IsNearGoal();            // 0xc42e20
  bool  Flag48();                // vtable 0x48 of the base
  u32   MoveToPointFacing(u32, Vec3_s00d8_7620*, Vec3_s00d8_7620*, float, float); // 0xc1c5c0
  s32   WaitForAnimEventOrEnd(u32, s32*, s32, s32, s32);    // 0xc14ef0
  void* InterruptAnimationWithTarget(u32, void*, s32);      // 0xc149c0
  s32   PlayAnim(u32, void*, s32);                          // 0xc14990
  s32   GetBodyPartIndex(u32, s32);                         // 0xc17580
  bool  AnimationFinished(s32);                             // 0xc12400
  bool  IsEatingActive();                                   // 0xc0b770
};
// ---- items of slice s00d87620 end

// ---- items of slice s00d885a0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Vec3_s00d8_85a0 { f32 x, y, z; };
struct COps_s00d8_85a0 {
    void* FUN_00c04590();                        // 0x00c04590 Get()
    void* FUN_00b1fdb0();                        // 0x00b1fdb0 cGameNounManager::GetAvatar
    void* FUN_00c0ee70();                        // 0x00c0ee70 GetTargetAsCreature
    bool  FUN_00c0c130();                        // 0x00c0c130
    void  FUN_00c12310(u32, s32, u32);           // 0x00c12310 InterruptAnimation
    void  FUN_00c17350(u32, u32);                // 0x00c17350
    void  FUN_00c6ac90(u32);                     // 0x00c6ac90
    bool  FUN_00bc98f0(u32, u32);                // 0x00bc98f0 ClearAll
    void* FUN_00bc97f0(u32, u32, f32, void*);    // 0x00bc97f0 Set
    u32   FUN_00bc96a0(u32, u32);                // 0x00bc96a0 Play
    void  FUN_00c13a30(u32);                     // 0x00c13a30 Hover
    f32   FUN_009360d0();                        // 0x009360d0 RandomDoubleUniform
    bool  FUN_00c42e20();                        // 0x00c42e20 IsNearGoal
    bool  FUN_00c12400(u32);                     // 0x00c12400 AnimationFinished
    bool  FUN_00c0e0c0(s32);                     // 0x00c0e0c0
    void  FUN_00c14940(u32, void*, s32, s32);    // 0x00c14940 PlayAnimationWithTarget
    void  FUN_00c1c1d0(u32, Vec3_s00d8_85a0*, f32, f32);    // 0x00c1c1d0 MoveToPointAtSpeed
    bool  FUN_00c0d560(void*, f32, f32);         // 0x00c0d560
    void* FUN_00c41ec0();                        // 0x00c41ec0
    void* FUN_00ac9850();                        // 0x00ac9850 cLocomotionRequest ctor
    void  FUN_007a41a0();                        // 0x007a41a0 dtor
    Vec3_s00d8_85a0* FUN_00b815a0(Vec3_s00d8_85a0*, Vec3_s00d8_85a0*);            // 0x00b815a0 DirectionToSurfacePosition
    bool  FUN_00b7e3e0(void*);                   // 0x00b7e3e0
    void* FUN_0041cb40(void*);                   // 0x0041cb40 Matrix3::Assign
};
#define MOPS_s00d8_85a0(p) ((COps_s00d8_85a0*)(p))
void  __cdecl FUN_00d88c70(void* node, void* creature); // 0x00d88c70
void  __cdecl FUN_00d7d540(void*, f32, f32, void*);    // 0x00d7d540 StayBetween
f32   __cdecl FUN_00d99ac0_s00d8_85a0(void*, void*, u32);         // 0x00d99ac0
f32   __cdecl FUN_00d38a30_s00d8_85a0(u32, void*);                // 0x00d38a30
void* __cdecl FUN_0059aed0(void*, void*);              // 0x0059aed0
bool  __cdecl FUN_00b7e3e0(void*);                     // 0x00b7e3e0
struct Creature_s00d8_85a0 {
    u8    pad000[0xb4c];
    void* mpStimuliMgr;      // 0xb4c
    u8    padB50[0xb5c - 0xb50];
    u8    mbFlag5c;          // 0xb5c
};
struct AlertNode {
    f32   mF_00;             // 0x00
    f32   mF_04;             // 0x04
    u32   mU_08;             // 0x08
    u32   mU_0c;             // 0x0c
    u32   mU_10;             // 0x10
    void* mpTarget;          // 0x14
    u32   mU_18;             // 0x18
};
struct AvatarNode {
    f32   mRandom;           // 0x00
    void* mpTarget;          // 0x04
};
struct PosseNode {
    f32   mTimer;            // 0x00
    f32   mTimer2;           // 0x04
    f32   mRadius;           // 0x08
    u8    mB_0c;             // 0x0c
    u8    mFlagD;            // 0x0d
    u8    mFlagE;            // 0x0e
    u8    mPad0f;            // 0x0f
    u32   mAnim;             // 0x10
};
struct CreatureManager {
    u8    pad000[0x164];
    void* mpOwner;           // 0x164
    void* mpListHead;        // 0x168
};
struct SpatialQuery {
    void* mpResult;          // 0x00
    u32   mU_04;             // 0x04
    u32   mU_08;             // 0x08
    u32   mU_0c;             // 0x0c
    u32   mU_10;             // 0x10
    f32   mF_14;             // 0x14
    f32   mF_18;             // 0x18
    f32   mF_1c;             // 0x1c
    f32   mF_20;             // 0x20
    u32   mU_24;             // 0x24
    u8    mPad28[0x4c - 0x28]; // 0x28
    u8    mB_4c;             // 0x4c
    u8    mPad4d[0x50 - 0x4d]; // 0x4d
    f32   mF_50;             // 0x50
    f32   mF_54;             // 0x54
    f32   mF_58;             // 0x58
    u32   mU_5c;             // 0x5c
    f32   mF_60;             // 0x60
    f32   mF_64;             // 0x64
    f32   mF_68;             // 0x68
    f32   mF_6c;             // 0x6c
    u32   mU_70;             // 0x70
};
extern f32 gF_013eb95c;      // 0x013eb95c
extern f32 gF_01486110;      // 0x01486110
extern f32 gF_0169f03c;      // 0x0169f03c
extern f32 gF_0169f040;      // 0x0169f040
extern f32 gF_0169f044;      // 0x0169f044
extern f32 gF_1470f1c;       // 0x01470f1c
extern f32 gF_1485720;       // 0x01485720 (_HK_REAL_ONE)
extern f32 gF_13ec4b4;       // 0x013ec4b4 (0.9)
extern f32 gF_13ec4b8;       // 0x013ec4b8 (1e-8)
extern f32 gF_147c030;       // 0x0147c030 (FLT_MAX)
extern f32 gF_169f0ec;       // 0x0169f0ec
extern f32 gF_13eb8c8;       // 0x013eb8c8 (0.3)
extern f32 gF_1476b54;       // 0x01476b54 (350.0)
// ---- items of slice s00d885a0 end

// ---- items of slice s00d8a2a0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const double kTwoDouble;     // 0x013f1298  2.0 (double)
extern const float  kPointThree;    // 0x013eb8c8  0.3
extern const float  kPointZeroOne;  // 0x013eb960  0.01
extern const float  kFourHundred;   // 0x013f0e84  400.0
extern const float  kEatFoodRate;   // 0x01687a44
extern "C" void __cdecl OperatorDeleteArray(void* p);   // 0x00f47380
#define PV_s00d8_a2a0(n) virtual void pv##n();
struct Vec3_s00d8_a2a0 { float x, y, z; };
class cRefObject {
public:
    virtual void AddRef();                        // +0x00
    virtual void Release();                       // +0x04
    PV_s00d8_a2a0(2) PV_s00d8_a2a0(3) PV_s00d8_a2a0(4)
    virtual int  Query(uint32_t id);              // +0x14
    PV_s00d8_a2a0(6) PV_s00d8_a2a0(7) PV_s00d8_a2a0(8) PV_s00d8_a2a0(9) PV_s00d8_a2a0(10)
    virtual const Vec3_s00d8_a2a0* GetPosition();            // +0x2c
    PV_s00d8_a2a0(12) PV_s00d8_a2a0(13) PV_s00d8_a2a0(14) PV_s00d8_a2a0(15) PV_s00d8_a2a0(16) PV_s00d8_a2a0(17) PV_s00d8_a2a0(18) PV_s00d8_a2a0(19) PV_s00d8_a2a0(20) PV_s00d8_a2a0(21) PV_s00d8_a2a0(22)
    virtual int  vf5c(uint32_t id);               // +0x5c
    PV_s00d8_a2a0(24) PV_s00d8_a2a0(25) PV_s00d8_a2a0(26) PV_s00d8_a2a0(27)
    virtual float vf70();                         // +0x70
    virtual float GetRadius();                    // +0x74
    PV_s00d8_a2a0(30) PV_s00d8_a2a0(31) PV_s00d8_a2a0(32)
    virtual void vf84(void* obj, int a, int b);   // +0x84
    PV_s00d8_a2a0(34) PV_s00d8_a2a0(35) PV_s00d8_a2a0(36) PV_s00d8_a2a0(37) PV_s00d8_a2a0(38) PV_s00d8_a2a0(39) PV_s00d8_a2a0(40) PV_s00d8_a2a0(41) PV_s00d8_a2a0(42) PV_s00d8_a2a0(43) PV_s00d8_a2a0(44) PV_s00d8_a2a0(45) PV_s00d8_a2a0(46)
    virtual void AddRefBundle();                  // +0xbc
    virtual void ReleaseBundle();                 // +0xc0
};
class cSpatialObject_s00d8_a2a0 {
public:
    PV_s00d8_a2a0(0) PV_s00d8_a2a0(1) PV_s00d8_a2a0(2) PV_s00d8_a2a0(3) PV_s00d8_a2a0(4) PV_s00d8_a2a0(5) PV_s00d8_a2a0(6) PV_s00d8_a2a0(7) PV_s00d8_a2a0(8) PV_s00d8_a2a0(9) PV_s00d8_a2a0(10)
    virtual const Vec3_s00d8_a2a0* GetPosition();            // +0x2c
    PV_s00d8_a2a0(12) PV_s00d8_a2a0(13) PV_s00d8_a2a0(14) PV_s00d8_a2a0(15) PV_s00d8_a2a0(16) PV_s00d8_a2a0(17) PV_s00d8_a2a0(18) PV_s00d8_a2a0(19) PV_s00d8_a2a0(20) PV_s00d8_a2a0(21) PV_s00d8_a2a0(22) PV_s00d8_a2a0(23)
    PV_s00d8_a2a0(24) PV_s00d8_a2a0(25) PV_s00d8_a2a0(26) PV_s00d8_a2a0(27)
    virtual float vf70();                         // +0x70
    virtual float GetRadius();                    // +0x74
};
class cLocomotiveObject_s00d8_a2a0 : public cSpatialObject_s00d8_a2a0 {
public:
    PV_s00d8_a2a0(30) PV_s00d8_a2a0(31) PV_s00d8_a2a0(32) PV_s00d8_a2a0(33) PV_s00d8_a2a0(34) PV_s00d8_a2a0(35) PV_s00d8_a2a0(36) PV_s00d8_a2a0(37) PV_s00d8_a2a0(38) PV_s00d8_a2a0(39) PV_s00d8_a2a0(40) PV_s00d8_a2a0(41)
    PV_s00d8_a2a0(42) PV_s00d8_a2a0(43) PV_s00d8_a2a0(44) PV_s00d8_a2a0(45) PV_s00d8_a2a0(46) PV_s00d8_a2a0(47) PV_s00d8_a2a0(48) PV_s00d8_a2a0(49) PV_s00d8_a2a0(50) PV_s00d8_a2a0(51) PV_s00d8_a2a0(52) PV_s00d8_a2a0(53)
    PV_s00d8_a2a0(54)
    virtual void PlayEffectSpec(void* spec);      // +0xdc
    bool __thiscall IsNearGoal();                 // 0x00c42e20
    float __thiscall FUN_00c422c0();              // 0x00c422c0
};
class BehaviorTreeHead_s00d8_a2a0 {
public:
    cRefObject* __thiscall Play(unsigned id, int flags);   // 0x00bc96a0, ret 8
    void __thiscall ClearAll(unsigned a, unsigned mask);    // 0x00bc98f0, ret 8
};
struct nSPBehaviorTree_s00d8_a2a0 {
    uint32_t pad00[2];                             // +0x00..+0x07
    BehaviorTreeHead_s00d8_a2a0 mHead;                        // +0x08
};
class cAnimNode_s00d8_a2a0 {
public:
    uint32_t pad00[3];                            // +0x00
    union { int mKind; float mf0c; };             // +0x0c
    float    mf10;                                // +0x10
};
class cCreatureSettings_s00d8_a2a0 {
public:
    uint32_t pad00[0x590 / 4];                    // +0x000
    float    mf590;                               // +0x590
};
struct LocoEffectSpec {
    void*    mpData;                              // +0x00  owned heap buffer
    void*    mpEnd;                               // +0x04
    void*    mpCap;                               // +0x08
    uint32_t pad0c[2];                            // +0x0c..+0x13 (never touched)
    float    mf14;                                // +0x14
    float    mf18;                                // +0x18
    float    mf1c;                                // +0x1c
    float    mf20;                                // +0x20
    int      m24;                                 // +0x24
    uint32_t pad28[9];                            // +0x28..+0x4b
    uint8_t  mb4c;                                // +0x4c
    uint8_t  pad4d[3];                            // +0x4d..+0x4f
    float    mf50;                                // +0x50
    float    mf54;                                // +0x54
    float    mf58;                                // +0x58
    int      m5c;                                 // +0x5c
    float    mf60;                                // +0x60
    float    mf64;                                // +0x64
    float    mf68;                                // +0x68
    float    mf6c;                                // +0x6c
    int      m70;                                 // +0x70
};
inline void InitLocoEffectSpec(LocoEffectSpec* s)
{
    s->mpData = 0;
    s->mpEnd = 0;
    s->mpCap = 0;
    s->mf14 = kEffect14;
    s->mf18 = kEffect18;
    s->mf1c = kEffect1c;
    s->mf20 = kOne;
    s->m24 = 0;
    s->mb4c = 0;
    s->mf50 = 0.0f;
    s->mf54 = 0.0f;
    s->mf58 = 0.0f;
    s->m5c = 0;
    s->mf60 = kTwo;
    s->mf64 = kPointNine;
    s->mf68 = kFloatMax;
    s->mf6c = 0.0f;
    s->m70 = 0;
}
inline void FreeOwnedBuffer(void* p)
{
    if (p != 0 && *(int*)((char*)p - 4) != 0)
        OperatorDeleteArray(p);
}
struct Citizen_s00d8_a2a0 {
    PV_s00d8_a2a0(0) PV_s00d8_a2a0(1) PV_s00d8_a2a0(2) PV_s00d8_a2a0(3) PV_s00d8_a2a0(4) PV_s00d8_a2a0(5) PV_s00d8_a2a0(6) PV_s00d8_a2a0(7) PV_s00d8_a2a0(8) PV_s00d8_a2a0(9) PV_s00d8_a2a0(10) PV_s00d8_a2a0(11) PV_s00d8_a2a0(12) PV_s00d8_a2a0(13)
    PV_s00d8_a2a0(14) PV_s00d8_a2a0(15) PV_s00d8_a2a0(16) PV_s00d8_a2a0(17) PV_s00d8_a2a0(18) PV_s00d8_a2a0(19) PV_s00d8_a2a0(20) PV_s00d8_a2a0(21) PV_s00d8_a2a0(22) PV_s00d8_a2a0(23) PV_s00d8_a2a0(24) PV_s00d8_a2a0(25) PV_s00d8_a2a0(26)
    PV_s00d8_a2a0(27) PV_s00d8_a2a0(28) PV_s00d8_a2a0(29) PV_s00d8_a2a0(30) PV_s00d8_a2a0(31) PV_s00d8_a2a0(32)
    virtual void vf84(void* obj, int a, int b);   // +0x84
    uint32_t pad04[0xc0 / 4 - 1];                 // +0x04..+0xbf
    cLocomotiveObject_s00d8_a2a0   mLoco;                    // +0xc0 (vtable view, 4 bytes)
    uint32_t padLoco[(0x74 - 4) / 4];             // +0xc4..+0x133  rest of the locomotive object
    uint32_t pad1a0[(0xb20 - 0x134) / 4];         // +0x134..+0xb1f
    cCreatureSettings_s00d8_a2a0*  mpEatenState;             // +0xb20
    uint32_t padB24[(0xb4c - 0xb24) / 4];         // +0xb24..+0xb4b
    nSPBehaviorTree_s00d8_a2a0*    mpBehavior;               // +0xb4c
    uint32_t padB50[2];                           // +0xb50..+0xb57
    uint8_t  mbB58[6];                            // +0xb58..+0xb5d
    uint8_t  mbB5e;                               // +0xb5e

    bool __thiscall FUN_00c13c60(void* obj, int a, int b);            // 0x00c13c60, ret 0xc
    bool __thiscall FUN_00c0f5f0();                                   // 0x00c0f5f0, ret 0
    void __thiscall FUN_00c15bd0(int a, int b, int c);                // 0x00c15bd0, ret 0xc
    void __thiscall FUN_00c14750(int a);                              // 0x00c14750, ret 4
    void __thiscall FUN_00c0cff0(int a);                              // 0x00c0cff0, ret 4
    void __thiscall FUN_00c0d240();                                   // 0x00c0d240, ret 0
    void __thiscall SetStealthed(int a, int b);                       // 0x00c1aed0, ret 8
    void __thiscall Hover(int a);                                     // 0x00c13a30, ret 4
    void __thiscall InterruptAnimation(unsigned id, int a, int b);    // 0x00c12310, ret 0xc
    int  __thiscall PlayAnimation(unsigned id, int a, int b);         // 0x00c12190, ret 0xc
    bool __thiscall AnimationFinished(int handle);                    // 0x00c12400, ret 4
    int  __thiscall PlayAnimationWithTarget(unsigned id, const Vec3_s00d8_a2a0* p, int handle);  // 0x00c14910, ret 0xc
    void __thiscall MoveToPointAtSpeed(int mode, const Vec3_s00d8_a2a0* p, float f1, float f2);  // 0x00c1c1d0, ret 0x10
    void __thiscall MoveToPointAndFacingAtSpeed(int mode, const Vec3_s00d8_a2a0* p, const Vec3_s00d8_a2a0* facing,
                                               float f1, float f2);   // 0x00c1c5c0, ret 0x14
};
class cTargetObject {
public:
    virtual void AddRef();                        // +0x00
    virtual void Release();                       // +0x04
    PV_s00d8_a2a0(2) PV_s00d8_a2a0(3) PV_s00d8_a2a0(4)
    virtual int  Query(uint32_t id);              // +0x14
    PV_s00d8_a2a0(6) PV_s00d8_a2a0(7) PV_s00d8_a2a0(8) PV_s00d8_a2a0(9) PV_s00d8_a2a0(10)
    virtual bool IsFinished();                    // +0x2c
    PV_s00d8_a2a0(12) PV_s00d8_a2a0(13) PV_s00d8_a2a0(14) PV_s00d8_a2a0(15) PV_s00d8_a2a0(16) PV_s00d8_a2a0(17) PV_s00d8_a2a0(18) PV_s00d8_a2a0(19) PV_s00d8_a2a0(20) PV_s00d8_a2a0(21) PV_s00d8_a2a0(22)
    uint32_t pad04[0xc];                          // +0x04..+0x33
    cSpatialObject_s00d8_a2a0 mBundle;                       // +0x34 (vtable view, 4 bytes)
    uint32_t padAc[(0x108 - 0x38) / 4];           // +0x38..+0x107
    int      mState108;                           // +0x108  (2..4 = interactable)
    uint32_t pad10c[7];                           // +0x10c..+0x127
    cRefObject* mpSpot;                           // +0x128
    uint32_t pad12c[2];                           // +0x12c..+0x133
    float    mf134;                               // +0x134
};
class cGroup : public cRefObject {
public:
    uint32_t pad04[(0xc0 - 4) / 4];               // +0x04..+0xbf
    cSpatialObject_s00d8_a2a0 mLoco;                         // +0xc0
    void* __thiscall At(unsigned idx);            // 0x00c0f8a0, ret 4
    int   __thiscall IndexOf(const void* p);      // 0x00c0f8f0, ret 4
};
class cAsset : public cRefObject {                // ref-counted bundle asset (acts as behaviour target)
public:
    uint32_t pad04[0x34 / 4 - 1];                 // +0x04..+0x33
    cSpatialObject_s00d8_a2a0 mBundle;                       // +0x34
};
class cAutoRef {
public:
    cAsset* mp;
    void __thiscall Assign(cAsset* p);            // 0x00c70110, ret 4
};
class cSpotServer : public cRefObject {
public:
    uint32_t pad04[(0x260 - 4) / 4];              // +0x04..+0x25f
    cTargetObject* mp260;                         // +0x260
    void __thiscall FindSpot(int kind, int idx);  // 0x00c98750, ret 8
    const Vec3_s00d8_a2a0* __thiscall FUN_00c986d0(Vec3_s00d8_a2a0* out, int kind, Citizen_s00d8_a2a0* c);  // 0x00c986d0, ret 0xc
};
class cGameMgr {
public:
    cRefObject* __thiscall GetContainer();        // 0x00ac79d0 (only used as an identity token)
    float __thiscall FUN_00ac7d10(float f, void* spot, void* node);  // 0x00ac7d10, ret 0xc
};
class cPlanetModel_s00d8_a2a0 {
public:
    const Vec3_s00d8_a2a0* __thiscall DirectionToSurfacePosition(Vec3_s00d8_a2a0* out, const Vec3_s00d8_a2a0* p);  // 0x00b815a0, ret 8
};
cRefObject*  __cdecl FUN_00d998d0_s00d8_a2a0(const void* node, unsigned id);   // 0x00d998d0
cPlanetModel_s00d8_a2a0* __cdecl PlanetModel(Vec3_s00d8_a2a0* out, const Vec3_s00d8_a2a0* p);        // 0x00b3d350
Vec3_s00d8_a2a0* __cdecl normalized_safe_s00d8_a2a0(Vec3_s00d8_a2a0* out, const Vec3_s00d8_a2a0* in);           // 0x00449c20
float __cdecl FUN_00572a10(float lo, float hi);                     // 0x00572a10
void  __cdecl FUN_00bcbc80();                                       // 0x00bcbc80
cGameMgr* __cdecl FUN_00b3d2b0();                                   // 0x00b3d2b0
void  __cdecl EatFood(Citizen_s00d8_a2a0* c, float amount, unsigned id, unsigned flags);  // 0x00d85ad0
float __cdecl GetPropertyTf(void* props, unsigned id, float def);   // 0x004e1c70
class cRandomLC {
public:
    float __thiscall RandomDoubleUniform();       // 0x009360d0
};
extern cRandomLC g_Random;                        // 0x01601760
class cArchetypeOwner {
public:
    uint32_t pad00[0x130 / 4];                    // +0x000
    void*    mpProps;                             // +0x130
};
class cSpeciesArchetype {
public:
    uint32_t pad00[0x1c / 4];                     // +0x000
    cArchetypeOwner* mpOwner;                     // +0x01c
};
cSpeciesArchetype* __cdecl FUN_00d1e660();        // 0x00d1e660
struct StateReceiveItem {                          // 0xd8a2a0 / 0xd8a500
    int      m0;                                   // +0x00
    Vec3_s00d8_a2a0     mTarget;                              // +0x04
    float    mf10;                                 // +0x10
    uint8_t  mb14;                                 // +0x14
    uint8_t  pad15[3];                             // +0x15
    cGroup*  mp18;                                 // +0x18
    cAutoRef m1c;                                  // +0x1c
    uint8_t  mb20;                                 // +0x20
    uint8_t  pad21[3];                             // +0x21
    int      m24;                                  // +0x24
};
struct StateUfoClump {                             // 0xd8a750 / 0xd8a8c0
    int   m0;                                      // +0x00
    cAsset* mp4;                                   // +0x04
};
struct StateEnterSpot {                            // 0xd8aa40
    cTargetObject* mp0;                            // +0x00
    uint32_t pad04[2];                             // +0x04..+0x0b
    int      m0c;                                  // +0x0c
};
struct StateSneak {                                // 0xd8ab30
    cTargetObject* mp0;                            // +0x00
    float    mf04;                                 // +0x04
    int      m08;                                  // +0x08
    int      m0c;                                  // +0x0c
};
struct StateBundle {                               // 0xd8ac30 / 0xd8af20 / 0xd8b1a0
    cTargetObject* mp0;                            // +0x00
    int      m04;                                  // +0x04  animation handle
    int      m08;                                  // +0x08  phase
    float    mf0c;                                 // +0x0c  remaining amount
    float    mf10;                                 // +0x10  total amount
    int      m14;                                  // +0x14  spot index
};
struct TickOut {
    float mf0;                                     // +0x00
    int   m4;                                      // +0x04
};
// ---- items of slice s00d8a2a0 end

// ---- items of slice s00d8cbb0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const float gRunSpeed;           // 0x01470f1c
extern const float gEggSightRangeSq;    // 0x013ec4d0
extern const float gFleeDistanceSq;     // 0x01486110
extern const float gStartleTrigger;     // 0x014853bc
extern const float gDirectionEpsilon;   // 0x013ec4b8
extern const float gStartleStep;        // 0x014853e0
struct Vec3_s00d8_cbb0 {
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
struct Mat3 {
    float mElements[9];
};
class cCreature_s00d8_cbb0;
class cSpatial {
public:
    const Vec3_s00d8_cbb0* GetPosition() {
        return ((const Vec3_s00d8_cbb0* (__thiscall*)(cSpatial*))((void**)mpVtable)[0x2c / 4])(this);
    }
    const Vec4* GetOrientation() {
        return ((const Vec4* (__thiscall*)(cSpatial*))((void**)mpVtable)[0x30 / 4])(this);
    }

    void* mpVtable;                             // 0x00
};
class cAnimationChannel {
public:
    void* PlayAnimation(int nFlags, int nMode);                          // 0x00bc96a0
    void Play(uint32_t nFlags, int nA, float fValue, void* pTarget);     // 0x00bc97f0

    uint8_t mPad[0x1c8];
};
class cAnimator {
public:
    uint8_t mPad000[0x08];                      // 0x000
    cAnimationChannel mChannel;                 // 0x008
    uint32_t mThreatSet;                        // 0x1d0
    uint8_t mPad1d4[0x428];                     // 0x1d4
    uint32_t mnFlags;                           // 0x5fc
};
class cAnimationController {
public:
    char TestFlag(uint32_t nFlag);                                       // 0x00bc9a00
    void SetFlag(uint32_t nFlag, float fValue, int nA, int nB);          // 0x00bc9d40
};
struct cNeighbourEntry {
    void* mpOwnerKey;                           // 0x00
    uint8_t mbFlag4;                            // 0x04
    uint8_t mbFlag5;                            // 0x05
    uint8_t mPad006[0x02];                      // 0x06
    cCreature_s00d8_cbb0* mpCreature;                      // 0x08
};
class cNeighbourIterator {
public:
    char IsValid(cNeighbourEntry* pEntry);      // 0x00c02600
    void Advance();                             // 0x00b3d850

    void** mpCurrent;                           // 0x00
    void** mpEnd;                               // 0x04
};
class cAnimIterator_s00d8_cbb0 {
public:
    char IsValid(void* pEntry);                 // 0x00c02650
    cAnimIterator_s00d8_cbb0* Advance();                   // 0x00d7cf50

    void** mpCurrent;                           // 0x00
    void** mpEnd;                               // 0x04
};
class cProximityQuery {
public:
    int Count();                                // 0x00ba3f90

    uint8_t mData[0x24];
};
class cGameData {
public:
    uint8_t mPad000[0x15c];                     // 0x000
    uint32_t mnGameMode;                        // 0x15c
    void* mpLinkedObject;                       // 0x160
    void* mpActiveCreature;                     // 0x164
    void* mpCollisionList;                      // 0x168
    uint8_t mPad16c[0x4b8];                     // 0x16c
    uint32_t mnContextKey;                      // 0x624
};
class cBehaviorStimuli_s00d8_cbb0 {
public:
    void* GetAny();                             // 0x00d997e0

    void* mpReserved0;                          // 0x00
    void* mpTargetEntry;                        // 0x04
    uint8_t mPad008[0x14];                      // 0x08
    float mfStimulusValue;                      // 0x1c
};
class cStimulusContext {
public:
    uint8_t mPad000[0x2d];                      // 0x000
    uint8_t mnKey;                              // 0x02d
};
class cXformMsg {
public:
    cXformMsg();                                                // 0x00434040
    void SetPosition(const Vec3_s00d8_cbb0* pPosition);                    // 0x00571d40

    uint8_t mPad000[0x08];                      // 0x00
    uint16_t mnFlags;                           // 0x08
    uint16_t mnCount;                           // 0x0a
    uint8_t mPad00c[0x10];                      // 0x0c
    Mat3 mTransform;                            // 0x1c
};
class cVisualEffect {
public:
    void Send(const cXformMsg* pMessage);       // vtable 0x18
    void Release();                             // vtable 0x04
};
class cEffectManager {
public:
    char CreateEffect(uint32_t nEffectId, int nMode, cVisualEffect** ppEffect);   // vtable 0x2c
};
class cActionState {
public:
    int mnState;                                // 0x00
    cCreature_s00d8_cbb0* mpTarget;                        // 0x04
    int mnAnimation;                            // 0x08
    uint32_t mnAnimationId;                     // 0x0c
    int mnEvent;                                // 0x10
    uint8_t mPad014[0x08];                      // 0x14
    uint8_t mbReady;                            // 0x1c
};
class cCreature_s00d8_cbb0 {
public:
    cGameData* GetGameData();                                        // 0x00c04590
    uint32_t GetTypeId() {
        return ((uint32_t (__thiscall*)(cCreature_s00d8_cbb0*))((void**)mpVtable)[0x20 / 4])(this);
    }
    char IsScareable() {
        return ((char (__thiscall*)(cCreature_s00d8_cbb0*))((void**)mpVtable)[0xd0 / 4])(this);
    }
    char v2c() {
        return ((char (__thiscall*)(cCreature_s00d8_cbb0*))((void**)mpVtable)[0x2c / 4])(this);
    }
    char v0c0(cCreature_s00d8_cbb0* pOther, float fA, float fB) {
        return ((char (__thiscall*)(cCreature_s00d8_cbb0*, cCreature_s00d8_cbb0*, float, float))
                    ((void**)mpVtable)[0xc0 / 4])(this, pOther, fA, fB);
    }
    void* v084(void* pTarget, int nA, int nB) {
        return ((void* (__thiscall*)(cCreature_s00d8_cbb0*, void*, int, int))
                    ((void**)mpVtable)[0x84 / 4])(this, pTarget, nA, nB);
    }
    void SetLinkedObject(int nValue);                                // 0x00c69bb0
    void MoveToPointAtSpeed(int nMode, const Vec3_s00d8_cbb0* pPosition, float fA, float fB); // 0x00c1c1d0
    void MoveToPointAtSpeed(int nMode, const Vec3_s00d8_cbb0* pPosition);
    char IsNearGoal();                                               // 0x00c42e20
    int InterruptAnimation(uint32_t nAnimationId, int nFlags, int nMode); // 0x00c12310
    char AnimationFinished(int nAnimation);                          // 0x00c12400
    char WaitForAnimEventOrEnd(uint32_t nEventId, int* pOut, uint32_t nAnimationId,
                               int nAnimation, int nMode);           // 0x00c14ef0
    uint32_t GetSpeciesProfile();                                    // 0x00c0bbd0
    char Flag388();                                                  // 0x00c0c0e0
    char AcceptTarget(cCreature_s00d8_cbb0* pOther);                            // 0x00c0b860
    char IsProximityClose(cCreature_s00d8_cbb0* pOther, float fA, float fB);    // 0x00c0d560
    int FindNearby(cCreature_s00d8_cbb0* pOther, uint32_t nFilter, float fValue,
                   int nA, int nB, int nC, int nD);                  // 0x00c12410
    void PlayAnimation(uint32_t nAnimationId, int nA, int nFlags);    // 0x00c12190

    void* mpVtable;                             // 0x000
    uint8_t mPad004[0x30];                      // 0x004
    cSpatial mSpatial;                          // 0x034
    uint8_t mPad038[0x88];                      // 0x038
    cSpatial mLocomotive;                       // 0x0c0
    uint8_t mPad0c4[0x4e4];                     // 0x0c4
    int mStimulusTarget;                        // 0x5a8
    uint8_t mPad5ac[0x574];                     // 0x5ac
    uint32_t mnId;                              // 0xb20
    uint8_t mPadb24[0x04];                      // 0xb24
    cProximityQuery mProximityQuery;            // 0xb28
    cAnimator* mpAnimator;                      // 0xb4c
    uint8_t mPadb50[0x08];                      // 0xb50
    uint32_t mnFlags;                           // 0xb58
    uint8_t mPadb5c[0x02];                      // 0xb5c
    uint8_t mbHidden;                           // 0xb5e
    uint8_t mPadb5f[0x45a];                     // 0xb5f
    uint8_t mbStimulusCooldown;                 // 0xfb9
    uint8_t mPadfba[0x62];                      // 0xfba
    uint32_t mnBehaviourState;                  // 0x101c
    uint8_t mPad1020[0x104];                    // 0x1020
    void** mpNeighboursBegin;                   // 0x1124
    void** mpNeighboursEnd;                     // 0x1128
    uint8_t mPad112c[0x2a8];                    // 0x112c
    void** mpAnimEntriesBegin;                  // 0x13d4
    void** mpAnimEntriesEnd;                    // 0x13d8
    uint8_t mPad13dc[0x248];                    // 0x13dc
    cAnimationController* mpAnimationController; // 0x1624
};
class cPlanetModel_s00d8_cbb0;
float GetStimulusValue(int nSlot, cCreature_s00d8_cbb0* pCreature);    // 0x00d38a30
float GetDistance(cSpatial* pA, cSpatial* pB, int nMode);   // 0x00d99ac0
void* BehaviorSet_Get(void* pSet, int nKey);                // 0x00d99420
void* BehaviorSet_Lookup(void* pSet, cBehaviorStimuli_s00d8_cbb0* pStimuli); // 0x00d996e0
void* BehaviorSet_Resolve(void* pHandle);                   // 0x00d99470
void* Object_LookupByKey(void* pObject, uint32_t nKey);     // 0x00ac80d0
cProximityQuery* NeighbourVector_Find(cAnimIterator_s00d8_cbb0* pIterator, void** pVector,
                                      void* pFilter);       // 0x00b41a40
void ClaimNearbyNestForAvatar(cCreature_s00d8_cbb0* pCreature);        // 0x00d40cc0
void* GetClaimContext();                                    // 0x00d51660
int ClaimContext_GetValue(void* pThis);                     // 0x0113ae10
void* EffectsManagerPtr();                                  // 0x0067ddd0
cPlanetModel_s00d8_cbb0* PlanetModel(Vec3_s00d8_cbb0* pOut, const Vec3_s00d8_cbb0* pDirection, float fA,
                          float fB);                        // 0x00b3d350
void Matrix3FromQuaternion(Mat3* pOut, const Vec4* pQuaternion); // 0x0059c190
char IsValidNeighbourEntry(cNeighbourIterator* pIterator, cNeighbourEntry* pEntry); // 0x00c02600
class cPlanetModel_s00d8_cbb0 {
public:
    Vec3_s00d8_cbb0* DirectionToSurfacePosition(Vec3_s00d8_cbb0* pOut, const Vec3_s00d8_cbb0* pDirection); // 0x00b815a0
};
// ---- items of slice s00d8cbb0 end

// ---- items of slice s00d8d820 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const float  gHalfF_1471064;        // 0x01471064 (0.5f)
#define PVCAT2(a, b) a##b
#define PVCAT(a, b) PVCAT2(a, b)
#define PV_s00d8_d820 virtual void PVCAT(pv_, __COUNTER__)();
#define PV2 PV_s00d8_d820 PV_s00d8_d820
#define PV4 PV2 PV2
#define PV8 PV4 PV4
#define PV16 PV8 PV8
struct float3 { float x, y, z; };
struct Loco_s00d8_d820 {
    PV8 PV2 PV_s00d8_d820                                   // 0x00..0x28
    virtual float3* Slot2c();                    // 0x2c  (current position)
    PV16 PV_s00d8_d820                                      // 0x30..0x70
    virtual float   Slot74();                    // 0x74  (radius / scalar)
};
struct LOUNGE_memory_block {
    int32_t mState;                              // +0x00
    float3  mMyPosition;                         // +0x04
    void*   mAnimHandle;                         // +0x10
    uint8_t mbOnlyGuard;                         // +0x14
};
struct TextRunIterator;
struct LoungeGroup {
    uint8_t  pad00[8];
    uint32_t mTag;                               // +0x08
    uint8_t  pad0c[0x18 - 0x0c];
    int32_t  mInt18;                             // +0x18
    uint8_t  pad1c[0x1a0 - 0x1c];
    void*    mpRef;                              // +0x1a0 (ref-counted)
    uint8_t  pad1a4[0x224 - 0x1a4];
    void*    mpCallback;                         // +0x224
    void  FUN_00bc9bf0(int a, int b);            // 0x00bc9bf0
    void  FUN_00bc9b80(int a, const float3* v);  // 0x00bc9b80
    void  FUN_00bc9bc0(int a, float v);          // 0x00bc9bc0
    float FUN_00bc9bb0(int a);                   // 0x00bc9bb0
    void* FUN_00bc9b70(int a);                   // 0x00bc9b70
};
struct TextRunIterator {
    bool AtBegin();                              // 0x00bc9b50
};
struct GameData {
    virtual void AddRef();                                            // 0x00
    virtual void Release();                                           // 0x04
    uint8_t  pad04[0x88 - 0x04];
    void*    mp88;                                                    // +0x88
    uint8_t  pad8c[0xf0 - 0x8c];
    void*    mpF0;                                                    // +0xf0
    uint8_t  padf4[0x15c - 0xf4];
    int32_t  m15c;                                                    // +0x15c
    void*    mp160;                                                   // +0x160
    int   FUN_00c6b8e0(float dist, const float3* pos);                // 0x00c6b8e0
    float3* GetPosition();                                           // 0x00c6acc0
};
struct Archetype_s00d8_d820 {
    uint8_t pad00[0x37c];
    float   m37c;                                // +0x37c
    float   m380;                                // +0x380
    float   m384;                                // +0x384
};
struct OrderMgr;
struct cSPCreatureBase_s00d8_d820 {
    uint8_t   pad00[0xc0];
    Loco_s00d8_d820      mLoco;                             // +0xc0 (vptr only, 4 bytes)
    uint8_t   padC4[0xb4c - 0xc4];
    OrderMgr* mpOrder;                           // +0xb4c
    GameData* FUN_00c04590();                    // 0x00c04590
    Archetype_s00d8_d820* FUN_00c0c1a0();                   // 0x00c0c1a0
    void      MoveToPointAtSpeed(int a, const float3* pos, float b, float c);       // 0x00c1c1d0
    void      MoveToPointAndFacingAtSpeed(int a, const float3* pos, const float3* d,
                                          float b, float c);                        // 0x00c1c5c0
};
struct OrderMgr {
    void FUN_00bcb480(LoungeGroup* g, cSPCreatureBase_s00d8_d820* c, LOUNGE_memory_block* t, int z); // 0x00bcb480
    bool IsSourceAtEnd();                        // 0x00bca280
};
void*  __cdecl FUN_00d82040(void* creature, int onlyGuard); // 0x00d82040  FindGuardOrLoungeGroup
float3* __cdecl FUN_00449c20(float3* out, const float3* in); // 0x00449c20  normalized_safe
// ---- items of slice s00d8d820 end

// callees this slice defines outside this object (rewrite.py held_callee_protos)
bool __fastcall FUN_00d8d820(LOUNGE_memory_block* self, void* edx, cSPCreatureBase_s00d8_d820* creature, LoungeGroup* group);  // 0x00d8d820 (stays in the slice: not this object's)

// ---- items of slice s00d8e8d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl FUN_00b3d240();
extern "C" void  __cdecl FUN_00b3d4c0();
extern "C" void  __cdecl FUN_00b3d4e0(void* a, int b);
extern "C" void* __cdecl FUN_00bc7610(void* a, int b);
extern "C" void* __cdecl FUN_00bc30b0(void* a);
extern "C" void  __cdecl FUN_00d7a070(void* a, void* b);
extern "C" void  __stdcall FUN_00bf3420(void* a);
struct RandomLCG {
    u32    UniformU32(u32 n);            // 0x00a68fb0
    double UniformDouble();              // 0x009360d0
};
struct BehaviorStimuli {
    u32   mnStimulusID;      // +0x00
    u32   mn04;              // +0x04
    u8    mPad08[0x10];      // +0x08
    void* mp18;              // +0x18
    void* mp1C;              // +0x1c

    void GetAny();           // 0x00d997e0
};
struct BehaviorTree {
    int  Play(u32 flags, u32 arg);                    // 0x00bc96a0
    void Stim(u32 a, u32 b, float value, void* self); // 0x00bc97f0
    void ClearAll(u32 flags, u32 value);              // 0x00bc98f0
};
struct OrderManager {
    int  FindNode(u32 id, void* fn, void* arg);                       // 0x00bca620
    void Activate(int a, int b, void* c, float f, void* p, void* q);  // 0x00bca810
    int  FindSlot(int a, int b, int c, int d);                        // 0x00bca0c0
    void DeactivateSlot(int slot);                                    // 0x00bca040
};
struct BehaviorData {
    u8     mPad000[0x184];   // +0x000
    void** mpBegin;          // +0x184
    void** mpEnd;            // +0x188
    u8     mPad18C[0x4c];    // +0x18c
    u32    mn1D8;            // +0x1d8
    u32    mn1DC;            // +0x1dc
};
struct BtChild {
    u8     mPad00[0x24];     // +0x00
    void** mpBegin;          // +0x24
    void** mpEnd;            // +0x28
};
struct cCreature_s00d8_e8d0;
struct CreatureContext {                 // object returned by cCreature::Get()
    u8           mPad000[0x15c];  // +0x000
    u32          mn15C;           // +0x15c
    u8           mPad160[4];      // +0x160
    cCreature_s00d8_e8d0*   mp164;           // +0x164
    void*        mp168;           // +0x168
    u8           mPad16C[0x44];   // +0x16c

    void* GetPosition();          // 0x00c6acc0
};
struct TimeOfDay {
    int Get();                    // 0x00bc2b80
};
struct DramaMgr {
    void Trigger();               // 0x00d4d790
};
struct cCreature_s00d8_e8d0 {
    void*          mpVftable;      // +0x000
    u8             mPad004[0x09c]; // +0x004
    u32            mn0A0;          // +0x0a0
    u8             mPad0A4[4];     // +0x0a4
    float          mf0A8;          // +0x0a8
    u8             mPad0AC[0x14];  // +0x0ac
    u8             mSpatial[0x40]; // +0x0c0
    u8             mPad100[0xa20]; // +0x100
    void*          mpB20;          // +0xb20 (interaction target object)
    u8             mPadB24[0x24];  // +0xb24
    OrderManager*  mpOrderMgr;     // +0xb48
    BehaviorData*  mpBt;           // +0xb4c
    u8             mPadB50[8];     // +0xb50
    u32            mnFlags;        // +0xb58
    u8             mPadB5C[2];     // +0xb5c
    u8             mbB5E;          // +0xb5e
    u8             mPadB5F[0x21];  // +0xb5f
    float          mfTurnRate;     // +0xb80
    u8             mPadB84[0x40c]; // +0xb84
    u8             mbF90;          // +0xf90

    // thiscall helpers (resolved by the linker).
    void             FUN_c196a0(void* a, u32 b, u32 c);          // 0x00c196a0
    u32              InterruptAnimation(u32 guid, int a, u32 b); // 0x00c12310
    u8               AnimationFinished(u32 anim);                // 0x00c12400
    double           GetTime();                                  // 0x00c0e480
    void*            GetCurrentAnimationGUID();                  // 0x00c0e040
    void             PlayAnimation(u32 guid, int a, u32 b);      // 0x00c11e90
    void             SetStealthed(int a, int b);                 // 0x00c1aed0
    void             CreateBodyEffect(void* a, u32 b, u32 c);    // 0x00c1b0c0
    CreatureContext* Get();                                      // 0x00c04590
    void*            Drama();                                    // 0x00d51660
    void*            Drama(int a, int b);                        // 0x00d51660
    cCreature_s00d8_e8d0*       GetTargetAsCreature();                      // 0x00c0ee70
    u32*             FUN_c0bc00();                               // 0x00c0bc00
    bool             Flag388();                                  // 0x00c0c0e0
    bool             FUN_c0bb90();                               // 0x00c0bb90
    bool             FUN_c0b810(void* a);                        // 0x00c0b810
    bool             FUN_c0b770();                               // 0x00c0b770
    bool             FUN_c0b7a0();                               // 0x00c0b7a0
    bool             FUN_c0b780();                               // 0x00c0b780
    void*            FUN_c0c1a0();                               // 0x00c0c1a0
    bool             FUN_c0e8d0(void* a, int b);                 // 0x00c0e8d0
    void             FUN_c15150(void* a, int b);                 // 0x00c15150
};
struct TuningProfile {
    u8     mPad00[8];        // +0x00
    u32    mnType;           // +0x08
    u8     mPad0C[0x3c];     // +0x0c
    void** mpItemBegin;      // +0x48
    void** mpItemEnd;        // +0x4c
    u8     mPad50[0x50];     // +0x50
    float  mfA0;             // +0xa0
    u8     mPadA4[4];        // +0xa4
    float  mfA8;             // +0xa8
    u8     mPadAC[0x48];     // +0xac
    float  mfF4;             // +0xf4

    u32 GetAt(u32 index);    // 0x004d3cd0
};
struct SpatialVec {
    void** mpBegin;          // +0x00
    void** mpEnd;            // +0x04
    void** mpCap;            // +0x08
    void Destroy();          // 0x00ad92d0
};
struct IntVec16 {
    int* mpBegin;            // +0x00
    int* mpEnd;              // +0x04
    int* mpCap;              // +0x08
    int  mInline[16];        // +0x0c

    void push_back(int value); // 0x00422380
    void Release();            // 0x007a41a0
};
struct TickStatePlay {       // FUN_00d8e8d0 state
    void* mpOwner;           // +0x00
    u32   mnPhase;           // +0x04
    u32   mnAnim;            // +0x08
};
struct TickStateRelease {    // FUN_00d8f170 state
    u8          mPad00[0x0c]; // +0x00
    void*       mp0C;         // +0x0c
    void*       mp10;         // +0x10
    cCreature_s00d8_e8d0*  mp14;         // +0x14
    u32         mn18;         // +0x18
};
// ---- items of slice s00d8e8d0 end

// ---- items of slice s00d9bee0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct IEmpty_s00d9_bee0 {};
template <int N, class B> struct VPad_s00d9_bee0 : VPad_s00d9_bee0<N - 1, B> { virtual void vpad(VPad_s00d9_bee0<N, B>*) {} };
template <class B> struct VPad_s00d9_bee0<0, B> : B {};
struct Vec3_s00d9_bee0 {
    float x, y, z;
};
extern "C" void* __cdecl FUN_00b3d2b0(void* a, u32 b);
extern "C" void* __cdecl FUN_00b3d4c0_s00d9_bee0(int a, void* b, void* c);
struct cSPCreatureBase_s00d9_bee0;
struct IRefCount {
    virtual void AddRef();                               // +0x00 (slot 0)
    virtual void Release();                              // +0x04 (slot 1)
};
struct ICreatureNoun : VPad_s00d9_bee0<6, IRefCount> {              // slots 0x08..0x1c
    virtual u32 GetNounID();                             // +0x20 (slot 8)
};
struct ICreatureVerb : VPad_s00d9_bee0<24, ICreatureNoun> {         // slots 0x24..0x80
    virtual void* FUN_84(void* p, int a, int b);         // +0x84 (slot 33)
};
struct ICreatureCombat : VPad_s00d9_bee0<11, ICreatureVerb> {       // slots 0x88..0xb0
    virtual void* FUN_b4(int slot);                      // +0xb4 (slot 45)
};
struct ICreatureMisc : VPad_s00d9_bee0<7, ICreatureCombat> {        // slots 0xb8..0xd0
    virtual bool FUN_d4();                               // +0xd4 (slot 53)
};
struct ILocoPos : VPad_s00d9_bee0<11, IEmpty_s00d9_bee0> {
    virtual const Vec3_s00d9_bee0* GetPosition();                   // +0x2c (slot 11)
};
struct ILocoRadius : VPad_s00d9_bee0<17, ILocoPos> {
    virtual float GetRadius();                           // +0x74 (slot 29)
};
struct cLocomotiveObject_s00d9_bee0 : VPad_s00d9_bee0<29, ILocoRadius> {
    virtual void FUN_ec();                               // +0xec (slot 59)

    bool  IsNearGoal();                                  // 0x00c42e20
    void* FUN_00c41ec0();                                // 0x00c41ec0  -> object with flags at +0x70
};
struct cEatTarget : IRefCount {                          // EAT_BUNDLE target object
    u8                pad04[0x34 - 0x04];
    cLocomotiveObject_s00d9_bee0 mLoco_34;                          // +0x34
    u8                pad38[0x128 - 0x38];
    u32               mField_128;                        // +0x128
};
struct behavior_stimuli_s00d9_bee0 {
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
    cSPCreatureBase_s00d9_bee0* mpOwner;                            // +0x1ac
};
struct cBehaviorTree_s00d9_bee0 {
    void*            mpVtbl;                             // +0x00
    u8               pad04[0x04];
    behavior_stimuli_s00d9_bee0 mStimuli_08;                        // +0x08
    u8               pad09[0x600 - 0x09];
    cMemoryBlock*    mpBlock_600;                        // +0x600

    void PopFront();                                     // 0x00bcaf40
};
struct cCreatureCombatPart {                             // subobject at creature+0x34
    u8    pad00[0x01];
    void* FUN_00cee330();                                // 0x00cee330
};
struct cSPCreatureBase_s00d9_bee0 : ICreatureMisc {
    u8                  pad04[0x34 - 0x04];
    cCreatureCombatPart mCombatPart_34;                  // +0x34
    u8                  pad35[0xc0 - 0x35];
    cLocomotiveObject_s00d9_bee0   mLoco_c0;                        // +0xc0
    u8                  padc4[0xb4c - 0xc4];
    cBehaviorTree_s00d9_bee0*      mpTree_b4c;                      // +0xb4c
    u32                 padb50[0x02];
    u32                 mFlags_b58;                      // +0xb58
    u8                  padb5c[0xfc8 - 0xb5c];
    u32                 mStealthTime_fc8;                // +0xfc8

    void*                  ApplyCombatTarget();          // 0x00c0ee90
    cSPCreatureBase_s00d9_bee0*       GetTargetAsCreature();        // 0x00c0ee70
    void*                  GetSocialGoal();              // 0x00c0e6a0
    void                   MoveToPointAtSpeed(int mode, const Vec3_s00d9_bee0* p, float a, float b);       // 0x00c1c1d0
    void                   MoveToPointAndFacingAtSpeed(int mode, const Vec3_s00d9_bee0* p, const Vec3_s00d9_bee0* dir,
                                                        float a, float b);                        // 0x00c1c5c0
    void*                  PlayAnimation(u32 id, int a, int b);                                  // 0x00c12190
    bool                   AnimationFinished(void* h);                                            // 0x00c12400
    void*                  PlayAnimationWithTarget(u32 id, void* target, int a, int b);           // 0x00c14940
    void*                  PlayAnimationWithTargetPos(u32 id, const Vec3_s00d9_bee0* p, int a);              // 0x00c14910
    void*                  FindSlotByCombatant(int slot, u32* out);                                // 0x00c0fa10
    void                   ApplyWave(float f);                                                    // 0x00c15dc0
};
struct cAgentOrderManager {
    void FUN_00ac79e0();                                 // 0x00ac79e0  (result of FUN_00b3d2b0)
    void FUN_00ba48b0();                                 // 0x00ba48b0  (result of FUN_00b3d4c0)
};
struct EAT_BUNDLE_state {
    int              mState;                             // +0x00
    void*            mAnimHandle;                        // +0x04
    cEatTarget*      mpTarget;                           // +0x08
    u8               pad0c[0x0c];
    int              mCount_18;                          // +0x18
    int              mField_1c;                          // +0x1c
    int              mField_20;                          // +0x20

    void* GetAny();                                      // 0x00d997e0
};
// ---- items of slice s00d9bee0 end

// @ 0x00aee830
uint32_t* cUFOLocomotion::CalculateAvoidanceDestination(uint32_t* pOut, void* pTarget, void* pUnused, int nFilter)
{
    pOut[0] = 0;
    pOut[1] = 0;
    pOut[2] = 0;
    pOut[3] = 0;
    pOut[4] = 0;

    cGameNounManager* pNouns = (cGameNounManager*)NounManager();
    uint32_t* pPlayerCiv = (uint32_t*)pNouns->GetPlayerCivilization();

    if (pTarget != nullptr && pPlayerCiv != nullptr && pTarget != pPlayerCiv) {
        void* pCivA = pPlayerCiv;
        void* pCivB = pTarget;
        ((IRefCounted*)pCivA)->v10();
        ((IRefCounted*)pCivB)->v10();

        NounManager();
        void* pNounsB = GetPlayerAvatarNouns();
        int nLevel = GetCivilizationLevel(pTarget);
        if (nLevel < 2)
            pOut[0] |= 0x40;

        int nRelation = GetCivilizationDistance(pCivB, pCivA, 1);
        switch (nRelation) {
        case 0:
            pOut[1] |= 0x80000000;
            pOut[2] |= 0x380;
            break;
        case 1:
            pOut[2] |= 0x391;
            break;
        case 2:
            pOut[2] |= 0x332;
            break;
        case 3:
            pOut[2] |= 0x274;
            break;
        case 4:
            pOut[2] |= 0x78;
            break;
        default:
            break;
        }
        (void)pNounsB;
    }

    float fDistance = (float)pPlayerCiv[0x26];
    if (fDistance < 4000.0f)
        pOut[2] |= 0x400;
    if (fDistance < 2000.0f)
        pOut[2] |= 0x800;
    if (fDistance < 1000.0f)
        pOut[2] |= 0x1000;
    if (31999.998f < fDistance)
        pOut[2] |= 0x2000;
    if (23999.998f < fDistance)
        pOut[2] |= 0x4000;
    if (15999.999f < fDistance)
        pOut[2] |= 0x8000;
    if (7999.999f < fDistance)
        pOut[2] |= 0x10000;
    if (3999.999f < fDistance)
        pOut[2] |= 0x20000;

    if (pTarget == nullptr)
        return pOut;

    void* pCivilization = NounManager();
    int nType = GetContinentDistance(0, pCivilization, 1);
    if (nType == 0)
        pOut[2] |= 0x200000;
    else if (nType == 1)
        pOut[2] |= 0x400000;
    else if (nType == 2)
        pOut[2] |= 0x800000;

    cGameDataVector* pCities = (cGameDataVector*)GetPlayerAvatarNouns();
    uint32_t nCityCount = (uint32_t)(pCities->mpEnd - pCities->mpBegin);
    if (nCityCount < 4) {
        pOut[2] |= 0x1000000;
        if (nCityCount < 7) {
            if (1 < nCityCount)
                pOut[2] |= 0x8000000;
            if (9 < nCityCount)
                pOut[2] |= 0x10000000;
            goto checkFlags;
        }
    } else if (nCityCount < 7) {
        pOut[2] |= 0x2000000;
        if (1 < nCityCount)
            pOut[2] |= 0x8000000;
        if (9 < nCityCount)
            pOut[2] |= 0x10000000;
        goto checkFlags;
    }
    if (nCityCount < 10)
        pOut[2] |= 0x4000000;
    if (1 < nCityCount)
        pOut[2] |= 0x8000000;
    if (9 < nCityCount)
        pOut[2] |= 0x10000000;

checkFlags:
    if (((uint32_t*)pTarget)[0xab] != 0)
        pOut[2] |= 0x20000000;
    if (((uint32_t*)pTarget)[0xb4] != 0)
        pOut[2] |= 0x40000000;
    if (((uint32_t*)pTarget)[0xbe] != 0)
        pOut[2] |= 0x80000000;
    if (((uint8_t*)pTarget)[200] != 0)
        pOut[3] |= 1;
    if (((uint8_t*)pTarget)[0xd2] != 0)
        pOut[3] |= 2;
    if (((uint8_t*)pTarget)[0xdc] != 0)
        pOut[3] |= 4;
    if (((uint8_t*)pTarget)[0xe6] != 0)
        pOut[3] |= 8;
    if (((uint8_t*)pTarget)[0xf0] != 0)
        pOut[3] |= 0x10;

    cGameNounManager* pNouns2 = (cGameNounManager*)NounManager();
    cGameDataVector* pData = (cGameDataVector*)pNouns2->GetGameDataVector(
        (void*)&gAvoidanceFilterTable[0], (void*)&gAvoidanceFilterTable[1],
        (void*)&gAvoidanceFilterTable[2], (void*)&gAvoidanceFilterTable[3],
        (void*)&gBehaviorResourceBlock);

    int nCityDataCount = (int)(pData->mpEnd - pData->mpBegin);
    int nOtherCivs = 0;
    if (0 < nCityDataCount) {
        for (int i = 0; i < nCityDataCount; ++i) {
            cCity* pCity = (cCity*)pData->mpBegin[i];
            void* pCiv1 = pCity->GetCivilization();
            if (pCiv1 != pTarget) {
                void* pCiv2 = pCity->GetCivilization();
                if (pCiv2 != pPlayerCiv)
                    ++nOtherCivs;
            }
        }
    }

    uint32_t nBit = 0x65;
    do {
        int nIndex = (int)(nBit - 0x65);
        if (nIndex < nOtherCivs && nBit < 0x9a)
            pOut[nBit >> 5] |= 1 << (nBit & 0x1f);
        ++nBit;
    } while ((int)(nBit - 100) < 10);

    if (nFilter != 0) {
        int nCityDistance = GetDistanceToCity((void*)pPlayerCiv, nFilter);
        if ((float)nCityDistance <= fDistance)
            pOut[3] |= 0x8000;
    }

    if (IsCivilizationNomadic((void*)pPlayerCiv))
        pOut[4] |= 0x80000;
    return pOut;
}

// @ 0x00aeebe0
void FilterBehaviorResource(void* pKey)
{
    cPropertyList* pRecord = (cPropertyList*)LookupResource(pKey);
    if (pRecord != nullptr)
        ApplyBehaviorRecordFlags((uint8_t*)pRecord + 0x10, pKey);
    if (pRecord != nullptr)
        pRecord->Release();
}

// @ 0x00aeec90
uint32_t* GetBehaviorVectorFromResource(uint32_t* pOut, void* pKey, int a, int b, int c)
{
    cBehaviorTable* pTable = (cBehaviorTable*)LookupResourceRecord(pKey);
    if (pTable != nullptr) {
        GatherBehaviorValues((uint8_t*)pTable + 0x3c, pKey, a, b, c);
        GatherBehaviorVectors(&pTable->mnId24, pKey, (void*)b, a, c);
        pOut[0] = pTable->mnId18;
        pOut[1] = pTable->mnId1c;
        pOut[2] = pTable->mnId20;
        pOut[3] = pTable->mnId24;
        ((cPropertyList*)pTable)->Release();
        return pOut;
    }
    pOut[1] = 0;
    pOut[2] = 0;
    pOut[3] = 0;
    return pOut;
}

// @ 0x00aeeda0
uint8_t GetBehaviorUnlockFlag(void* pKey)
{
    cBehaviorTable* pTable = (cBehaviorTable*)LookupResourceRecord(pKey);
    if (pTable == nullptr)
        return 0;
    uint8_t nFlag = pTable->mbFlag14;
    ((cPropertyList*)pTable)->Release();
    return nFlag;
}

// @ 0x00aeee50
void GetBehaviorFlags(uint8_t* pFlags, void* pKey)
{
    cBehaviorTable* pTable = (cBehaviorTable*)LookupResourceRecord(pKey);
    if (pTable != nullptr) {
        pFlags[0] = pTable->mbFlag13;
        pFlags[1] = pTable->mbFlag10;
        pFlags[2] = pTable->mbFlag11;
        pFlags[3] = pTable->mbFlag12;
        ((cPropertyList*)pTable)->Release();
    }
}

// @ 0x00aeef00
int CountBehaviorSubRecords(void* pKey)
{
    int nCount = 0;
    cBehaviorTable* pTable = (cBehaviorTable*)LookupResourceRecord(pKey);
    if (pTable != nullptr) {
        cBehaviorSubRecord* pEntry = (cBehaviorSubRecord*)pTable->mnEntryBegin3c;
        if (pEntry != (cBehaviorSubRecord*)pTable->mnEntryEnd40) {
            do {
                if (MatchesBehaviorFilter(pEntry, pKey))
                    ++nCount;
                pEntry = (cBehaviorSubRecord*)((uint8_t*)pEntry + 0xc4);
            } while (pEntry != (cBehaviorSubRecord*)pTable->mnEntryEnd40);
        }
        ((cPropertyList*)pTable)->Release();
    }
    return nCount;
}

// @ 0x00aeefc0
uint32_t* GetBehaviorSubRecordValues(uint32_t* pOut, void* pKey, int nWanted, int a)
{
    int nIndex = 0;
    cBehaviorTable* pTable = (cBehaviorTable*)LookupResourceRecord(pKey);
    if (pTable != nullptr) {
        cBehaviorSubRecord* pEntry = (cBehaviorSubRecord*)pTable->mnEntryBegin3c;
        if (pEntry != (cBehaviorSubRecord*)pTable->mnEntryEnd40) {
            do {
                if (MatchesBehaviorFilter(pEntry, pKey)) {
                    if (nIndex == nWanted) {
                        if (a != 0)
                            GatherBehaviorValues((uint8_t*)pEntry + 0x60, pKey, 0, 0, a);
                        pOut[0] = pEntry->mnValue50;
                        pOut[1] = pEntry->mnValue54;
                        pOut[2] = pEntry->mnValue58;
                        pOut[3] = pEntry->mnValue5c;
                        ((cPropertyList*)pTable)->Release();
                        return pOut;
                    }
                    ++nIndex;
                }
                pEntry = (cBehaviorSubRecord*)((uint8_t*)pEntry + 0xc4);
            } while (pEntry != (cBehaviorSubRecord*)pTable->mnEntryEnd40);
        }
        ((cPropertyList*)pTable)->Release();
    }
    pOut[1] = 0;
    pOut[2] = 0;
    pOut[3] = 0;
    return pOut;
}

// @ 0x00aef0e0
void DEBUG_BEHAVIOR_Tick(void* pBehavior, uint32_t nAction, uint32_t* pOutA, uint32_t* pOutB)
{
    switch (nAction) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 7:
    case 8:
    case 9:
    case 0xb:
    case 0xe:
    case 0x12:
    case 10:
    case 0xf:
    case 0x11:
    case 0xc:
    case 0xd:
    case 0x10:
    default:
        break;
    }

    *pOutA = 0;
    *pOutB = 0;

    cBehaviorTable* pTable = (cBehaviorTable*)LookupResource((void*)&gRandomState);
    if (pTable != nullptr) {
        uint32_t nMaskCount = (pTable->mnId28 - pTable->mnId24) >> 2;
        if (0 < (int)nMaskCount) {
            uint32_t nIndex = 0;
            RandomUint32Uniform(&gRandomState, nMaskCount);
            *pOutA = *(uint32_t*)(pTable->mnId24 + nIndex * 4);
        }
        uint32_t nFilterCount = (pTable->mnId1c - pTable->mnId18) >> 2;
        if (0 < (int)nFilterCount) {
            uint32_t nIndex = 0;
            RandomUint32Uniform(&gRandomState, nFilterCount);
            *pOutB = *(uint32_t*)(pTable->mnId18 + nIndex * 4);
        }
        ((cPropertyList*)pTable)->Release();
    }
    (void)pBehavior;
}

// @ 0x00d7a5c0
float __cdecl FUN_00d7a5c0(void* p)
{
  if (!CreateLayoutManager()->LookupA(p, 1, 0)) return 1.0f;
  return 0.0f;
}

// @ 0x00d7a5e0
float __cdecl FUN_00d7a5e0(CB* p)
{
  if (CreateLayoutManager()->LookupA(p, 1, 0)) {
    p->ClampHunger(g_1687a0c);
    return 1.0f;
  }
  return 0.0f;
}

// @ 0x00d7a620
float __cdecl FUN_00d7a620(CB* p)
{
  return *(int*)((char*)p->Get() + 0x80) != -1 ? g_1485720 : 0.0f;
}

// @ 0x00d7a660
float __cdecl FUN_00d7a660(CB* cb)
{
  int r = BS(cb)->Play(0x40000, 0);
  if (r != 0) {
    CB* m = (CB*)FUN_00d999d0((void*)r);
    if (m != 0 && m->mbDead != 0 && m->mpSpecies != cb->mpSpecies)
      return 1.0f;
  }
  return 0.0f;
}

// @ 0x00d7a6b0
float __cdecl FUN_00d7a6b0(CB* cb)
{
  int r = BS(cb)->Play(0, 0x100);
  if (r != 0) {
    int* p = (int*)FUN_00d998d0((void*)r, 0x61494bd);
    if (p != 0 && p[0x108 / 4] >= 2 && p[0x108 / 4] <= 4) return 1.0f;
  }
  return 0.0f;
}

// @ 0x00d7a700
bool __cdecl FUN_00d7a700(void* a, CB* b)
{
  if (((Iter*)a)->AtBegin()) return false;
  b->Get();
  CB* c = (CB*)((Iter*)a)->Cur();
  if (c->mpSpecies != b->mpSpecies) return false;
  if (b->Prox(c, 1.0f, 0.0f) ||
      ((bool (__thiscall*)(CB*, void*, float, float))(*(void***)b)[0xc0 / 4])(b, c, 1.0f, 0.0f))
    return true;
  return false;
}

// @ 0x00d7a780
float __cdecl FUN_00d7a780(CB* cb)
{
  int r = (int)FUN_00d998f0(FUN_00d99a10((void*)BS(cb)->Play(0x400, 0)));
  if (r != 0) return 1.0f;
  BS(cb)->ClearAll(0x400, 0);
  return 0.0f;
}

// @ 0x00d7a7d0
float __cdecl FUN_00d7a7d0(CB* cb, int, int, uint flags, void* st, char* out)
{
  if (flags & 0x80000000) return 0.0f;
  int* p = (int*)BS(cb)->Play(0x400, 0);
  if (p != 0 && p[3] != 3) {
    void* v = FUN_00d998f0(FUN_00d99a10((void*)p));
    if (v != 0) {
      if (st != 0) ((Stimuli*)st)->GetAny();
      *out = 1;
      *(void**)((char*)st + 4) = v;
      return 1.0f;
    }
    BS(cb)->ClearAll(0x400, 0);
  }
  return 0.0f;
}

// @ 0x00d7a850
float __cdecl FUN_00d7a850(CB* cb, int, int, uint, void* st, char* out)
{
  int r = BS(cb)->Play(0x400, 0);
  if (r != 0) {
    CB* v = (CB*)FUN_00d99a10((void*)r);
    if (v != 0) {
      CB* w = (CB*)((void* (__thiscall*)(CB*))(*(void***)v)[0xc / 4])(v);
      if (w != 0) {
        void* t = ((void* (__thiscall*)(CB*))(*(void***)w)[0x20 / 4])(w);
        if (t == (void*)0x18eb45e) {
          if (w->mbDead != 0) return 0.0f;
        } else {
          CB* x = (CB*)FUN_00ac80d0(w, (void*)0x18eb4b7);
          if (x != 0) {
            if (x->mbDead != 0) return 0.0f;
          } else {
            if (FUN_00ac80d0(w, (void*)0x18c6de8) != 0) goto L;
            if (FUN_00ac80d0(w, (void*)0x436f342) != 0) goto L;
            if (FUN_00ac80d0(w, (void*)0x18ebadc) == 0) return 0.0f;
          }
        }
      L:
        if (st != 0) ((Stimuli*)st)->GetAny();
        *out = 1;
        *(void**)((char*)st + 4) = v;
        return 1.0f;
      }
    }
  }
  return 0.0f;
}

// @ 0x00d7a920
float __cdecl FUN_00d7a920(CB* cb, int, int, uint, void* st, char* out)
{
  int* p = (int*)BS(cb)->Play(0x80000, 0);
  if (p == 0) return 0.0f;
  bool eq1 = p[3] == 1;
  CB* v = (CB*)FUN_00d99980((void*)p);
  if (v == 0 || v->mbDead != 0 || eq1 || v->mpSpecies == cb->mpSpecies)
    return 0.0f;
  float d = FUN_00d38a30(1, cb);
  d = FUN_00d38a30(2, cb);
  if (!cb->Prox(v, d, 0.0f) &&
      !((bool (__thiscall*)(CB*, void*, float, float))(*(void***)cb)[0xc0 / 4])(cb, v, d, 0.0f))
    return 0.0f;
  float dd = FUN_00d99ac0((char*)v + 0xc0, (char*)cb + 0xc0, 1);
  float thr = FUN_00d38a30(5, cb);
  if (thr < dd) return 0.0f;
  if (st != 0) ((Stimuli*)st)->GetAny();
  *out = 1;
  *(void**)((char*)st + 4) = &v->mStim5a8;
  BS(cb)->ClearAll(0x80000, 0);
  return 1.0f;
}

// @ 0x00d7aa50
float __cdecl FUN_00d7aa50(CB* cb)
{
  CB* t = (CB*)cb->GetTargetAsCreature();
  if (t != 0) {
    float d1 = FUN_00d38a30(1, cb);
    float d2 = FUN_00d38a30(2, cb);
    CB* t2 = (CB*)cb->GetTargetAsCreature();
    if (!cb->Prox(t2, d2, 0.0f) &&
        !((bool (__thiscall*)(CB*, void*, float, float))(*(void***)cb)[0xc0 / 4])(cb, t2, d2, 0.0f))
      return 1.0f;
    return 0.0f;
  }
  return 1.0f;
}

// @ 0x00d7aad0
float __cdecl FUN_00d7aad0(CB* cb)
{
  int r = BS(cb)->Play(0, 0x4000);
  if (r != 0) {
    if ((int)FUN_00d998f0(FUN_00d99a10((void*)r)) != 0) return 1.0f;
  }
  return 0.0f;
}

// @ 0x00d7ab10
float __cdecl FUN_00d7ab10(CB* cb, int, int, uint, void* st, char* out)
{
  int pr = BS(cb)->Play(0, 0x4000);
  if (pr == 0) return 0.0f;
  int* v = (int*)FUN_00d998f0(FUN_00d99a10((void*)pr));
  if (v != 0) {
    void* p = ((void* (__thiscall*)(void*))(*(void***)v)[8 / 4])(v);
    float d = FUN_00d99ac0((char*)cb + 0xc0, p, 1);
    if (d <= g_1473c70) return 0.0f;
    if (st != 0) ((Stimuli*)st)->GetAny();
    *(float*)((char*)st + 8) = ((float (__thiscall*)(void*))(*(void***)v)[0xc / 4])(v);
    void* p2 = ((void* (__thiscall*)(void*))(*(void***)v)[8 / 4])(v);
    float a = ((float (__thiscall*)(void*))(*(void***)p2)[0x74 / 4])(p2);
    float b = ((float (__thiscall*)(void*))(*(void***)((char*)cb + 0xc0))[0x74 / 4])((char*)cb + 0xc0);
    long long q = (long long)(a + b + g_1486110);
    *(int*)((char*)st + 0x1c) = 1;
    *(int*)((char*)st + 0x20) = 0;
    *(int*)((char*)st + 0x18) = (int)q;
    *out = 1;
    return 1.0f;
  }
  return 0.0f;
}

// @ 0x00d7ac10
float __cdecl FUN_00d7ac10(CB* cb, int, int, uint, void* st, char* out)
{
  int p = BS(cb)->Play(0, 0x4000);
  if (p != 0) {
    int r = (int)FUN_00d998f0(FUN_00d99a10((void*)p));
    if (r != 0) {
      if (st != 0) ((Stimuli*)st)->GetAny();
      *out = 1;
      *(void**)((char*)st + 4) = (void*)r;
      return 1.0f;
    }
  }
  return 0.0f;
}

// @ 0x00d7ac70
bool __cdecl FUN_00d7ac70(CB* cb)
{
  ((void (__thiscall*)(void*))(*(void***)((char*)cb + 0xc0))[0xec / 4])((char*)cb + 0xc0);
  return true;
}

// @ 0x00d7ac90
float __cdecl FUN_00d7ac90(CB* cb, int, int, uint flags, void* st, char* out)
{
  int* p = (int*)BS(cb)->Play(0x200, 0);
  if (p != 0) {
    CB* a = (CB*)FUN_00d99980((void*)p);
    if (a != 0 && p[3] == 1) {
      CB* q = *(CB**)((char*)p + 0x10);
      if (q == 0) {
        q = (CB*)FUN_00d999d0((void*)BS(a)->Play(0x400, 0));
        if (q == 0) return 0.0f;
      }
      bool b = ((bool (__thiscall*)(void*))(*(void***)((char*)q + 0xc0))[0x58 / 4])((char*)q + 0xc0);
      if (b && (flags & 0x6000000) != 0) return 0.0f;
      if (cb == q) return 0.0f;
      if (q->mbDead != 0) return 0.0f;
      float d = FUN_00d38a30(1, cb);
      d = FUN_00d38a30(2, cb);
      if (!cb->Prox(q, d, 0.0f) &&
          !((bool (__thiscall*)(CB*, void*, float, float))(*(void***)cb)[0xc0 / 4])(cb, q, d, 0.0f))
        return 0.0f;
      if (st != 0) ((Stimuli*)st)->GetAny();
      *out = 1;
      *(void**)((char*)st + 4) = &q->mStim5a8;
      return 1.0f;
    }
  }
  return 0.0f;
}

// @ 0x00d7adc0
float __cdecl FUN_00d7adc0(CB* cb)
{
  float a = g_1687a00 * cb->m_5e0;
  float b = ((float (__thiscall*)(void*))(*(void***)((char*)cb + 0x5a8))[0x58 / 4])((char*)cb + 0x5a8);
  return a / b < g_1687a0c ? g_1485720 : 0.0f;
}

// @ 0x00d7ae20
float __cdecl FUN_00d7ae20(CB* cb, int, int, uint, void* st, char* out)
{
  CB* m = (CB*)FUN_00d999d0((void*)BS(cb)->Play(0x100, 0));
  if (m != 0) {
    if (st != 0) ((Stimuli*)st)->GetAny();
    *out = 1;
    *(void**)((char*)st + 4) = m->GetStim5a8();
    return 1.0f;
  }
  return 0.0f;
}

// @ 0x00d7ae80
float __cdecl FUN_00d7ae80(CB* cb, int, int, uint, void* st, char* out)
{
  CB* m = (CB*)FUN_00d999d0((void*)BS(cb)->Play(0, 8));
  if (m != 0) {
    if (st != 0) ((Stimuli*)st)->GetAny();
    *out = 1;
    *(void**)((char*)st + 4) = m->GetStim5a8();
    return 1.0f;
  }
  return 0.0f;
}

// @ 0x00d7aed0
float __cdecl FUN_00d7aed0(CB* cb, int, int, uint, void* st, char* out)
{
  CB* a = (CB*)FUN_00d99500((void*)FUN_00d99980((void*)BS(cb)->Play(0x80000000, 0)));
  if (a != 0) {
    float f2 = FUN_00d38a30(2, cb);
    float f1 = FUN_00d38a30(1, cb);
    float d = FUN_00d99ac0((char*)cb + 0xc0, (char*)a + 0xc0, 1);
    if (!cb->Prox(a, f1, d) &&
        !((bool (__thiscall*)(CB*, void*, float, float))(*(void***)cb)[0xc0 / 4])(cb, a, f2, d))
      return 0.0f;
    if (st != 0) ((Stimuli*)st)->GetAny();
    *out = 1;
    *(void**)((char*)st + 4) = &a->mStim5a8;
    return 1.0f;
  }
  return 0.0f;
}

// @ 0x00d7afb0
float __cdecl FUN_00d7afb0(CB* cb)
{
  unsigned int f = cb->mGeneralFlags;
  if (((f >> 8) & 1) == 0 && ((f >> 4) & 1) != 0) {
    CB* a = (CB*)FUN_00d99500((void*)FUN_00d99980((void*)BS(cb)->Play(0x800, 0)));
    if (a != 0) return 1.0f;
  }
  return 0.0f;
}

// @ 0x00d7b000
float __cdecl FUN_00d7b000(CB* cb)
{
  if (!cb->mFlagBitsB58.mBit8) {
    CB* a = (CB*)FUN_00d99500((void*)FUN_00d99980((void*)BS(cb)->Play(0x800, 0)));
    if (a != 0 && (a->mp_b4c->mFlags5fc & 0x1000) != 0)
      return 1.0f;
  }
  return 0.0f;
}

// @ 0x00d7b060
namespace SP {
float __cdecl CURIOUS_Deactivate(CB* cb, int, int, uint, void* st, char* out)
{
  CB* o = (CB*)FUN_00d99980((void*)BS(cb)->Play(0x800, 0));
  if (o != 0) {
    if (o->GetSpeciesProfile() != cb->GetSpeciesProfile()) {
      if (cb->Prox(o, 1.0f, 0.0f) && cb->CheckA(o)) {
        if (st != 0) ((Stimuli*)st)->GetAny();
        *out = 1;
        *(void**)((char*)st + 4) = &o->mStim5a8;
        BS(cb)->ClearAll(0x800, 0);
        return 1.0f;
      }
    }
  }
  return 0.0f;
}
}  // namespace SP

// @ 0x00d7b110
namespace SP {
float __cdecl FRIENDLY_Deactivate(CB* cb, int, int, uint, void* st, char* out)
{
  CB* o = (CB*)FUN_00d99980((void*)BS(cb)->Play(0x800, 0));
  if (o != 0) {
    if (o->GetSpeciesProfile() != cb->GetSpeciesProfile()) {
      if (cb->CheckB(o)) {
        if (st != 0) ((Stimuli*)st)->GetAny();
        *out = 1;
        *(void**)((char*)st + 4) = &o->mStim5a8;
        BS(cb)->ClearAll(0x800, 0);
        return 1.0f;
      }
    }
  }
  return 0.0f;
}
}  // namespace SP

// @ 0x00d7b1a0
namespace SP {
float __cdecl FUN_00d7b1a0(CB* cb)
{
  if (FUN_00c02c70(cb) <= 0) return 0.0f;
  void* a = FUN_00989360(FUN_00b3d300());
  if (cb->Get() != a) return 1.0f;
  void* te = FUN_00f67d90(FUN_00b3d300());
  if (te == 0) return 1.0f;
  int local = 0;
  if (((TerrainEditor*)te)->Sub(0x514a219, &local)) return 0.0f;
  return 1.0f;
}
}  // namespace SP

// @ 0x00d7b290
bool __cdecl FUN_00d7b290(void* a, CB* b)
{
  if (((Iter*)a)->AtBegin()) return false;
  CB* c = (CB*)((Iter*)a)->Cur();
  int d = (int)b->Get();
  int e = (int)c->Get();
  if (c->mpSpecies != b->mpSpecies) return false;
  if (e != d) return false;
  return true;
}

// @ 0x00d7b2e0
float __cdecl FUN_00d7b2e0(void* self, int, int, uint, void* st, char* out)
{
  if (st != 0) ((Stimuli*)st)->GetAny();
  *out = 1;
  *(void**)st = 0;
  return 1.0f;
}

// @ 0x00d7b310
bool __cdecl FUN_00d7b310(void* a, void* b)
{
  if (!((Iter*)a)->AtBegin()) {
    CB* c = (CB*)((Iter*)a)->Cur();
    return ((CB*)c)->Get() == ((CB*)b)->Get();
  }
  return false;
}

// @ 0x00d7b350
bool __cdecl FUN_00d7b350(CB* cb)
{
  bool r = ((bool (__thiscall*)(void*))(*(void***)((char*)cb + 0xc0))[0xf8 / 4])((char*)cb + 0xc0);
  cb->mGeneralFlags |= 4;
  cb->Sub01(r ? 0 : 1);
  int v = ((int (__thiscall*)(void*))(*(void***)((char*)cb + 0x58))[0x20 / 4])((char*)cb + 0x58);
  return v != 0;
}

// @ 0x00d7b3a0
void __cdecl FUN_00d7b3a0(CB* cb)
{
  cb->mGeneralFlags &= 0xfffffffb;
  ((void (__thiscall*)(void*))(*(void***)((char*)cb + 0x58))[0x34 / 4])((char*)cb + 0x58);
}

// @ 0x00d7b3c0
bool __cdecl FUN_00d7b3c0(CB* cb)
{
  if (cb->AnimationFinished(0x65d31ac)) {
    ((void (__thiscall*)(CB*, int))(*(void***)cb)[0xc8 / 4])(cb, 0);
  }
  return true;
}

// @ 0x00d7b3f0
void __cdecl FUN_00d7b3f0(CB* cb)
{
  cb->mGeneralFlags &= 0xfffffffb;
}

// @ 0x00d7b400
bool __cdecl FUN_00d7b400(CB* cb, int, int, uint, void*, St* st)
{
  if (BS(cb)->Play(0x1000, 0) != 0) {
    if (st->m12 != 0) {
      if (cb->mb137 != 0 || (cb->mFlags & 0x1000) != 0) {
        st->mc = cb->InterruptAnimation(0x2481e14, -1, 0);
        st->m12 = 0;
      }
      return true;
    }
    if (st->m8 != 0) {
      if (cb->AnimationFinished(st->m4)) {
        BS(cb)->ClearAll(0x1000, 0);
        return false;
      }
      return true;
    }
    if (st->m10 != 0 || st->m11 != 0) {
      if (cb->AnimationFinishedX(st->mc)) return false;
    }
    return true;
  }
  return false;
}

// @ 0x00d7b4c0
void __cdecl FUN_00d7b4c0(CB* cb, int, int, uint, void*, St* st)
{
  BS(cb)->ClearAll(0x1000, 0);
  if (st->m8 != 0) {
    cb->Sub01(0);
    return;
  }
  if (st->m10 == 0 && st->m11 == 0)
    cb->InterruptAnimation(0x74339a43, -1, 0);
}

// @ 0x00d7b510
bool __cdecl FUN_00d7b510(CB* cb)
{
  BS(cb)->ClearAll(0, 0x4000000);
  return false;
}

// @ 0x00d7b530
bool __cdecl FUN_00d7b530(CB* cb)
{
  BS(cb)->ClearAll(0x100000, 0);
  return false;
}

// @ 0x00d7b550
void __cdecl FUN_00d7b550(cSPCreatureBase* pCreature)
{
    pCreature->mpBehaviorTree->mStimuli.ClearAll(0x20000, 0);
}

// @ 0x00d7b570
bool __cdecl FUN_00d7b570(cSPCreatureBase* pCreature, uint32_t, uint32_t, uint32_t, uint32_t, tIdleCtx* pCtx)
{
    pCtx->mf04 = g_kFive;

    tStimulus* pStim = (tStimulus*)pCreature->mpBehaviorTree->mStimuli.Play(0x10, 0);
    if (pStim != 0)
    {
        pCtx->mn00 = pStim->mn0c;
        int32_t nStartled = ((pCreature->mnFlags >> 9) & 1) != 0 && !pCreature->FUN_00c0c130();
        pCtx->mb08 = nStartled != 0;
        pCtx->mb09 = nStartled != 0 && pCreature->CountValid() > 0;
        pCtx->mf0c = g_fIdleHold;

        pCreature->mnFlags |= 0x2000;
        pCreature->mCombatant.FUN_00bfc430(1);
        ((cCreatureNotify*)pCreature)->v84((void*)pCreature->FUN_00c0ee60(1, 1));
        return true;
    }
    return false;
}

// @ 0x00d7b6a0
bool __cdecl FUN_00d7b6a0(cSPCreatureBase* pCreature, uint32_t, uint32_t, uint32_t, uint32_t, tAnimCtx* pCtx)
{
    tStimulus* pStim = (tStimulus*)pCreature->mpBehaviorTree->mStimuli.Play(0x400000, 0);
    if (pStim != 0)
    {
        cSPCreatureBase* pAnimal = (cSPCreatureBase*)GetAnimalFromStimulus(pStim);
        if (pAnimal != 0)
        {
            pCreature->v84(&pAnimal->mCombatant, 1, 0);
            pCtx->mn00 = 0;
            pCtx->mn04 = pCreature->InterruptAnimation(0x35387528, -1, 0);
            return true;
        }
    }
    return false;
}

// @ 0x00d7b710
bool __cdecl FUN_00d7b710(cSPCreatureBase* pCreature, uint32_t, uint32_t, uint32_t, uint32_t, tAnimCtx* pCtx)
{
    int32_t nEvent;
    switch (pCtx->mn00)
    {
    case 0:
        {
            if (pCreature->WaitForAnimEventOrEnd(0xbfa50b5a, &nEvent, -1, pCtx->mn04, 1))
            {
                pCreature->FUN_00c1d460(0x4f26350b, 0x4f26350b);
                pCreature->mpBehaviorTree->mStimuli.ClearAll(0x400000, 0);
                pCtx->mn04 = pCreature->PlayAnimation(0xb346511c, 1, -1);
                pCtx->mn00 = 1;
            }
        }
        break;
    case 1:
        if (pCreature->IsAnimFinished(pCtx->mn04))
            return false;
        break;
    }
    return true;
}

// @ 0x00d7b7a0
bool __cdecl FUN_00d7b7a0(cSPCreatureBase* pCreature, uint32_t, uint32_t, uint32_t, uint32_t, tConfusedCtx*)
{
    tStimulus* pStim = (tStimulus*)pCreature->mpBehaviorTree->mStimuli.Play(0x20000, 0);
    cAnimalNoun* pNoun = 0;
    if (pStim != 0 && (pNoun = (cAnimalNoun*)FUN_00d998d0(pStim, 0x1b92b27)) != 0)
    {
        if ((pCreature->mnFlags >> 9) & 1)
        {
            pCreature->MoveToPointAtSpeed(2, pNoun->mSpatial.v2c(), g_kOne, g_kTwo);
        }
        else
        {
            cSPCreatureBase* pAvatar = ((cGameNounManager_s00d7_b550*)NounManager())->GetAvatar();
            float fReach = pCreature->mLoco.v74();
            if ((pCreature->mnFlags >> 8) & 1)
                fReach = pAvatar->mLoco.v74() + fReach;

            float fRadius = pNoun->mSpatial.v74() + pCreature->mLoco.v74() * g_kTwo;
            Vector3* pPoint = ((cSpatialObjectRanged*)&pNoun->mSpatial)
                                  ->v2c(pNoun->mSpatial.v74(), fRadius);
            Vector3 vSpot;
            PlanetModel(&vSpot, pPoint)->MakeRandomWorldPosition(&vSpot, pPoint);
            pCreature->MoveToPointAtSpeed(2, &vSpot, fReach * g_kOneHalf, fReach * g_kThree);
        }
    }
    else
    {
        float fRadius = pCreature->mLoco.v74();
        pCreature->MoveToPointAtSpeed(
            2, pCreature->FUN_00c04590(fRadius, fRadius * g_kTwo)->GetPosition(),
            fRadius, fRadius * g_kTwo);
    }

    if (pCreature->mLoco.IsNearGoal())
        return false;
    pCreature->mpBehaviorTree->mStimuli.ClearAll(0x400, 0);
    return true;
}

// @ 0x00d7b970
bool __cdecl FUN_00d7b970(cSPCreatureBase* pCreature, uint32_t, uint32_t, uint32_t, int32_t nObject, tAnimCtx*)
{
    if (pCreature->mLoco.IsNearGoal())
        return false;

    if (nObject != 0)
        pCreature->FUN_00c0cff0(nObject);

    tStimulus* pStim = (tStimulus*)pCreature->mpBehaviorTree->mStimuli.Play(0x400, 0);
    if (pStim != 0)
    {
        bool bTalked = false;
        tStimulus* pTalk = (tStimulus*)pCreature->mpBehaviorTree->mStimuli.Play(0x20000, 0);
        if (pTalk != 0)
            bTalked = pTalk->mn0c != 0;

        cSPCreatureBase* pWatcher = (cSPCreatureBase*)WatchMemoryBlock(pStim);
        if (!bTalked && pWatcher != 0 && !pWatcher->mbB5e)
            return false;
    }
    return true;
}

// @ 0x00d7ba00
bool __cdecl FUN_00d7ba00(cSPCreatureBase* pCreature, uint32_t, uint32_t, uint32_t, uint32_t, tAnimCtx* pCtx)
{
    pCreature->PlayAnimation(0x261fc45, 1, -1);
    pCtx->mn00 = 0;
    return true;
}

// @ 0x00d7baf0
void __cdecl FUN_00d7baf0(cSPCreatureBase* pCreature)
{
    pCreature->mbE38 = false;
    pCreature->mbFB8 = false;
    pCreature->PlayAnimation(0x261fc47, 1, -1);
}

// @ 0x00d7bb20
bool __cdecl FUN_00d7bb20(cSPCreatureBase* pCreature)
{
    pCreature->FUN_00c1d5e0(1, 0x6f623ffa, 0x12007c9a);
    return pCreature->AnimationFinished(0x52314083) ? false : true;
}

// @ 0x00d7bb50
void __cdecl FUN_00d7bb50(cSPCreatureBase* pCreature)
{
    pCreature->FUN_00c17350(0x12007c9a, 0);
    pCreature->v84((void*)0, 0, 0);
    pCreature->mpBehaviorTree->mStimuli.ClearAll(0, 8);
}

// @ 0x00d7bb90
bool __cdecl FUN_00d7bb90(cSPCreatureBase* pCreature)
{
    if (pCreature->AnimationFinished(0))
    {
        pCreature->mpBehaviorTree->mStimuli.ClearAll(0, 0x20);
        return false;
    }
    return true;
}

// @ 0x00d7bbc0
void __cdecl FUN_00d7bbc0(cSPCreatureBase* pCreature)
{
    pCreature->v84((void*)0, 0, 0);
}

// @ 0x00d7bbe0
bool __cdecl FUN_00d7bbe0(cSPCreatureBase* pCreature, uint32_t, uint32_t, uint32_t, uint32_t, tAnimCtx* pCtx)
{
    tStimulus* pStim = (tStimulus*)pCreature->mpBehaviorTree->mStimuli.Play(0, 0x8000000);
    if (pStim != 0)
    {
        cSPCreatureBase* pAnimal = (cSPCreatureBase*)GetAnimalFromStimulus(pStim);
        if (pAnimal != 0)
            pCreature->v84(&pAnimal->mCombatant, 1, 0);

        int32_t nAnim = pStim->mn0c;
        pCtx->mn00 = nAnim;
        pCreature->FUN_00c122c0(nAnim, 2.5f, 1.5f);
        return true;
    }
    return false;
}

// @ 0x00d7bc60
bool __cdecl FUN_00d7bc60(cSPCreatureBase* pCreature, uint32_t, uint32_t, uint32_t, uint32_t, tAnimCtx* pCtx)
{
    return pCreature->AnimationFinished(pCtx->mn00) ? false : true;
}

// @ 0x00d7bc80
void __cdecl FUN_00d7bc80(cSPCreatureBase* pCreature)
{
    pCreature->mpBehaviorTree->mStimuli.ClearAll(0, 0x8000000);
    pCreature->v84((void*)0, 0, 0);
}

// @ 0x00d7bcb0
int32_t __stdcall FUN_00d7bcb0(tFindTable* pTable, int32_t nKey)
{
    uint32_t nCount = pTable->mnCount;
    for (uint32_t i = 0; i < nCount; ++i)
    {
        tFindEntry* pEntry = &pTable->mEntries[i];
        if (nKey != pEntry->mn08 && pEntry->mb04 && pEntry->mn08 != 0)
            return pEntry->mn08;
    }
    return 0;
}

// @ 0x00d7bd00
void __cdecl FUN_00d7bd00(cSPCreatureBase* pCreature)
{
    pCreature->FUN_00c0d0c0(6, 0);
    pCreature->mpBehaviorTree->FUN_00bcb430();
    pCreature->mpBehaviorTree->mStimuli.ClearAll(0x40000000, 0);
}

// @ 0x00d7bd40
bool __cdecl FUN_00d7bd40(cSPCreatureBase* pCreature, uint32_t, uint32_t, uint32_t, uint32_t, tGreetCtx* pCtx)
{
    pCtx->mb00 = false;
    pCtx->mn08 = 0;

    cSPCreatureBase* pAvatar = ((cGameNounManager_s00d7_b550*)NounManager())->GetAvatar();
    pCtx->mPos = *pAvatar->mLoco.v2c();
    pCtx->mn18 = 0;
    pCtx->mf04 = 0.0f;

    pCreature->FUN_00c14750(true);
    return true;
}

// @ 0x00d7bda0
void __cdecl FUN_00d7bda0(cSPCreatureBase* pCreature)
{
    pCreature->FUN_00c14750(true);
    return ((cPosseSimulator*)FUN_00d539d0(pCreature))->RemovePosseSlot();
}

// @ 0x00d7bdc0
bool __cdecl FUN_00d7bdc0(cSPCreatureBase* pCreature, uint32_t, uint32_t, uint32_t, uint32_t, tConfusedCtx* pCtx)
{
    pCtx->mf00 = 0.0f;
    int32_t nTime = (int32_t)g_mathRandom.RandomUint32Uniform(10);
    pCtx->mPos.x = (float)(nTime + 5);
    pCreature->FUN_00c0ba10();
    return true;
}

// @ 0x00d7be00
void __cdecl FUN_00d7be00(cSPCreatureBase* pCreature)
{
    pCreature->FUN_00c14750(!pCreature->mLoco.vf8());
}

// @ 0x00d7be30
bool __cdecl FUN_00d7be30(cCreatureIterator* pIterator, cSPCreatureBase* pTarget)
{
    if (!pIterator->AtBegin())
    {
        cSPCreatureBase* pCreature = pIterator->FUN_00bc9b10();
        if (pCreature->mnB20 == pTarget->mnB20 &&
            (pTarget->FUN_00c0d560(pCreature, 1.0f, 0.0f) ||
             pTarget->vc0(pCreature, 1.0f, 0.0f)))
            return true;
    }
    return false;
}

// @ 0x00d7bea0
bool __cdecl FUN_00d7bea0(cCreatureIterator* pIterator, cSPCreatureBase* pTarget)
{
    if (!pIterator->AtBegin())
    {
        cSPCreatureBase* pCreature = pIterator->FUN_00bc9b10();
        if (pCreature->mnB20 == pTarget->mnB20)
            return true;
    }
    return false;
}

// @ 0x00d7bee0
bool __cdecl FUN_00d7bee0(cSPCreatureBase*, uint32_t, uint32_t, uint32_t, uint32_t, tAnimCtx* pCtx)
{
    pCtx->mn00 = 0;
    return true;
}

// @ 0x00d7bef0
bool __cdecl FUN_00d7bef0(cSPCreatureBase* pCreature, uint32_t, uint32_t, uint32_t, uint32_t, tAnimCtx* pCtx)
{
    if (pCtx->mn00 != 0 && pCreature->IsAnimFinished(pCtx->mn00))
        return false;

    tStimulus* pStim = (tStimulus*)pCreature->mpBehaviorTree->mStimuli.Play(0x2000, 0);
    if (pCtx->mn00 != 0)
        return true;
    if (pStim != 0)
    {
        float fElapsed = (float)g_nGameTime;
        if (pStim->mf08 <= 10.0f - fElapsed * 0.001f)
            return true;
    }
    pCtx->mn00 = pCreature->InterruptAnimation(0x2481df9, -1, 0);
    return true;
}

// @ 0x00d7bf80
void __cdecl FUN_00d7bf80(cSPCreatureBase* pCreature)
{
    pCreature->mpBehaviorTree->mStimuli.ClearAll(0x2000, 0);
}

// @ 0x00d7bfa0
bool __cdecl FUN_00d7bfa0(cSPCreatureBase* pCreature, uint32_t, uint32_t, uint32_t, uint32_t, tConfusedCtx* pCtx)
{
    tStimulus* pStim = (tStimulus*)pCreature->mpBehaviorTree->mStimuli.Play(0x1000000, 0);
    if (pStim == 0)
        return false;

    cSPCreatureBase* pTarget = (cSPCreatureBase*)FUN_00d99500(GetAnimalFromStimulus(pStim));
    if (pTarget != 0 && pTarget->FUN_00c0c130())
    {
        pCtx->mf00 = g_kThree;
        pCtx->mPos = *pTarget->mLoco.v2c();
        pCreature->FUN_00c1d460(0xc46ed8ab, 0xc46ed8ab);
        pCreature->MoveToPointAtSpeed(2, &pCtx->mPos, 1.0f, 2.0f);
        pCreature->v84(&pTarget->mCombatant, 0, 0);
        pCtx->mn10 = pCreature->PlayAnimation(0x3139a5d, 1, -1);
        return true;
    }
    return false;
}

// @ 0x00d7c090
void __cdecl FUN_00d7c090(cSPCreatureBase* pCreature)
{
    pCreature->mpBehaviorTree->mStimuli.ClearAll(0x1000000, 0);
    pCreature->FUN_00c17350(0xc46ed8ab, 0);
    pCreature->mLoco.vec();
    pCreature->FUN_00c14750(true);
    pCreature->v84((void*)0, 0, 0);
}

// @ 0x00d7c0f0
bool __cdecl FUN_00d7c0f0(cSPCreatureBase* pCreature, uint32_t, uint32_t, uint32_t, uint32_t, tConfusedCtx* pCtx, uint32_t, float fDelta)
{
    cSPCreatureBase* pTarget =
        (cSPCreatureBase*)FUN_00d99500(pCreature->GetTargetAsCreature());
    if (pTarget == 0)
        return false;

    float fA = FUN_00d38a30(1, pCreature);
    float fB = FUN_00d38a30(2, pCreature);
    if (pCreature->FUN_00c0d560(pTarget, fA, 0.0f))
        return false;
    if (pCreature->vc0(pTarget, fB, 0.0f))
        return false;

    if (pCreature->mLoco.IsNearGoal())
    {
        pCtx->mf00 -= fDelta;
        if (g_kTiny > pCtx->mf00)
            return false;
    }

    if (pCreature->IsAnimFinished(pCtx->mn10))
        pCtx->mn10 = pCreature->PlayAnimation(0x3139a5d, 1, -1);
    return true;
}

// @ 0x00d7c1d0
bool __cdecl FUN_00d7c1d0(cSPCreatureBase* pCreature)
{
    pCreature->PlayAnimation(0x915f7deb, 1, -1);
    return true;
}

// @ 0x00d7c1f0
bool __cdecl FUN_00d7c1f0(cSPCreatureBase* pCreature)
{
    cSPCreatureBase* pAvatar = ((cGameNounManager_s00d7_b550*)NounManager())->GetAvatar();
    if (pAvatar != 0)
    {
        ((cAnimRequests*)pCreature->mp1624)->FUN_00bc9d40(0x80, g_kSixty, pAvatar, 0);
        pCreature->mbFB9 = false;
        pCreature->v84(&pAvatar->mCombatant, 1, 0);
        pCreature->PlayAnimationWithTarget(0x5295983c, &pAvatar->mLoco, -1, -1);
        return true;
    }
    return false;
}

// @ 0x00d7c270
float __cdecl FUN_00d7c270(cSPCreatureBase* pCreature)
{
    cSPCreatureBase* pAvatar = ((cGameNounManager_s00d7_b550*)NounManager())->GetAvatar();
    if (pAvatar == 0 || pAvatar->mbB5e)
        return 0.0f;

    if (pAvatar->mpBehaviorTree->mStimuli.Play(0, 0x1000000) != 0)
        return 1.0f;

    if (pCreature->mbFB9)
    {
        if (((cAnimRequests*)pCreature->mp1624)->FUN_00bc9a00(0x80))
            pCreature->mbFB9 = false;
    }
    if (!((cAnimRequests*)pCreature->mp1624)->FUN_00bc9a00(0x80) && pCreature->mbFB9 &&
        pCreature->mpBehaviorTree->mStimuli.Play(0x4000000, 0) != 0)
        return 1.0f;
    return 0.0f;
}

// @ 0x00d7c310
bool __cdecl FUN_00d7c310(cSPCreatureBase* pCreature, uint32_t, uint32_t, uint32_t, uint32_t, tGreetCtx*)
{
    uint32_t nAnim = 0x5295983c;
    if (!pCreature->vd0())
        nAnim = 0x26f1f86;
    return pCreature->AnimationFinished(nAnim) ? false : true;
}

// @ 0x00d7c3e0
bool FUN_00d7c3e0(cCreatureBase* pCreature, int32_t nArg2, int32_t nArg3, int32_t nArg4, int32_t nArg5, cStateBlock* pState, float fDelta)
{
    if (pState->mhAnimation == 0) {
        pState->mhAnimation = (uint32_t)pCreature->InterruptAnimation(0x5405ea0, -1, 0);
    }
    else if (pCreature->AnimationFinished(pState->mhAnimation)) {
        cMessageServer* pServer = MessageServer();
        pServer->Send(0x445f729, 0, 0);
        return false;
    }

    if (pState->mbField014 == 0) {
        if (pCreature->WaitForAnimEventOrEnd(0x280852e4, &pState->mhAnimation, -1, 0, 1))
            pState->mbField014 = 1;
        else
            pState->mfField00C = pState->mfField00C - fDelta;

        if (pState->mbField014 == 0)
            return true;
    }

    float fProgress = pState->mfField008;
    float fTotal = pState->mfField00C;
    pState->mfField008 = fDelta + fProgress;

    float fFraction = fTotal - (fDelta + fProgress) * g_fCelebrateStretch;
    if (fFraction <= 0.0f)
        fFraction = 0.0f;
    if (fTotal <= fFraction)
        fFraction = fTotal;
    float fFractionRatio = fFraction / pState->mfField00C;

    float fPhase = g_fCelebratePhase - g_fCelebrateRate * pState->mfField008;
    if (fPhase <= 0.0f)
        fPhase = 0.0f;
    if (g_fCelebratePhase <= fPhase)
        fPhase = g_fCelebratePhase;

    float fInvTotal = 1.0f / pState->mfField00C;
    float fWave = -(sinf((pState->mfField008 * fInvTotal) * g_fCelebrateFreq * fPhase) *
                    fFractionRatio);

    float fScale = g_fCelebrateMinScale;
    if (fWave < g_fZero) {
        fScale = ((pState->mfField00C - pState->mfField008) * fInvTotal) *
                 g_fCelebrateMaxScale;
        if (fScale <= 0.1f)
            fScale = 0.1f;
        if (g_fCelebrateMaxScale <= fScale)
            fScale = g_fCelebrateMaxScale;
    }

    fScale = fScale * fWave;
    if (fFractionRatio <= 0.0f)
        fScale = g_fZero;

    pCreature->mLocomotive.SetSpeed((pState->mfField000 - pState->mfField004) * fScale +
                                    pState->mfField000);

    return true;
}

// @ 0x00d7cf50
cAnimIterator* cAnimIterator::Advance()
{
    do {
        mppCurrent = mppCurrent + 1;
        if (mppCurrent == mppEnd)
            break;
    } while (!mFilter.Accept(*mppCurrent));

    return this;
}

// @ 0x00d7cfb0
bool FindForageDestination(cCreatureBase* pCreature, cSPVector3_s00d7_c3e0* pOut)
{
    uint8_t aLocal[12];

    cForageList* pList = (cForageList*)pCreature->Get();
    if (pList != nullptr) {
        if (pList->mnIndex < (uint32_t)((int32_t)(pList->mpEnd - pList->mpBegin) / 12)) {
            uint8_t* pElement = pList->mpBegin + pList->mnIndex * 12;
            cPlanetModel_s00d7_c3e0* pModel = (cPlanetModel_s00d7_c3e0*)PlanetModel(aLocal, pElement);
            *pOut = *pModel->GetPosition();
            return true;
        }
    }

    return false;
}

// @ 0x00d7d020
bool FUN_00d7d020(cCreatureBase* pCreature)
{
    cCreatureBase* pAvatar = (cCreatureBase*)NounManager_s00d7_c3e0()->GetAvatar();
    if (pAvatar == nullptr)
        return false;

    float* pMinePosition = pCreature->mLocomotive.GetPosition();
    float* pAvatarPosition = pAvatar->mLocomotive.GetPosition();

    float fDx = pAvatarPosition[0] - pMinePosition[0];
    float fDy = pAvatarPosition[1] - pMinePosition[1];
    float fDz = pAvatarPosition[2] - pMinePosition[2];
    float fDistanceSq = fDz * fDz + fDx * fDx + fDy * fDy;

    if (!(fDistanceSq < g_fMineAlertRadius * g_fMineAlertRadius))
        return false;

    float* pVelocity = pAvatar->mLocomotive.GetVelocity();
    float fSpeedSq = pVelocity[2] * pVelocity[2] + pVelocity[1] * pVelocity[1] +
                     pVelocity[0] * pVelocity[0];

    bool bApproaching = false;
    if (fSpeedSq > g_fMineSpeedThreshold) {
        float fDot = pVelocity[2] * fDz + pVelocity[0] * fDx + pVelocity[1] * fDy;
        if (fDot > g_fZero)
            bApproaching = true;
    }

    bool bClose = (g_fMineNearRadius * g_fMineNearRadius) > fDistanceSq;

    if (!bApproaching || bClose)
        return true;
    return false;
}

// @ 0x00d7d160
bool FUN_00d7d160(cCreatureBase* pCreature)
{
    if (!FUN_00d7d020(pCreature))
        return false;

    cCreatureBase* pAvatar = (cCreatureBase*)NounManager_s00d7_c3e0()->GetAvatar();
    if (pAvatar == nullptr)
        return false;

    void* aQuery[2];
    aQuery[0] = (pCreature != nullptr) ? (void*)&pCreature->mCombatant : nullptr;
    aQuery[1] = nullptr;

    void* pManager = FUN_00bc9b00(0x60995fc, (void*)FUN_00d995c0, aQuery);
    cOrderNode* pNode = ((cOrderManager*)pManager)->FindNode();
    cCreatureBase* pTarget = pCreature->ApplyCombatTarget();

    if (pNode != nullptr) {
        float fDistance = pCreature->mCombatant.GetTargetDistance();
        if (fDistance < g_fMineInteractRadius) {
            if (pNode->mnField10 > 1)
                return false;
            if (pTarget != nullptr && pTarget->mCombatant.mfHealth > pCreature->mCombatant.mfHealth)
                return false;
        }
    }

    return true;
}

// @ 0x00d7d220
void FUN_00d7d220(cCreatureBase* pCreature, void* pTool)
{
    pCreature->mnFlags050 = pCreature->mnFlags050 | 0x100;
    pCreature->mbField077 = 0;

    cCreaturePart* pToolPart = (cCreaturePart*)pCreature->FindPart(0x398420d);
    if (pToolPart != nullptr)
        pToolPart->EnterToolMode(pTool);

    cCreaturePart* pHandPart = (cCreaturePart*)pCreature->FindPart(0x116dd1b);
    if (pHandPart != nullptr) {
        pHandPart->mbField268 = 0;
        pHandPart->SetStimulusTarget(&g_vStimulusPosition);
        pHandPart->mnField1F0 = 3;
    }

    if (GetCurrentGameMode() == &g_gameMode) {
        cCreaturePart* pFakePart = (cCreaturePart*)pCreature->FindPart(0x17f243b);
        if (pFakePart != nullptr)
            ((cToolController*)g_pGameState->mpField078)->OnToolEnter(pTool, pFakePart);
    }
}

// @ 0x00d7d2c0
void FUN_00d7d2c0(cCreatureBase* pCreature, void* pTool)
{
    pCreature->mnFlags050 = pCreature->mnFlags050 & 0xfffffeff;

    cCreaturePart* pToolPart = (cCreaturePart*)pCreature->FindPart(0x398420d);
    if (pToolPart != nullptr)
        pToolPart->ExitToolMode(pTool);

    cCreaturePart* pHandPart = (cCreaturePart*)pCreature->FindPart(0x116dd1b);
    if (pHandPart != nullptr) {
        if (pCreature->FindPart(0xce9f6639) == nullptr)
            pHandPart->mbField268 = 1;
        pHandPart->mbField077 = 0;
        pHandPart->mnField1F0 = 3;
    }

    if (GetCurrentGameMode() == &g_gameMode) {
        cCreaturePart* pFakePart = (cCreaturePart*)pCreature->FindPart(0x17f243b);
        if (pFakePart != nullptr)
            ((cToolController*)g_pGameState->mpField078)->OnToolExit(pTool, pFakePart);
    }
}

// @ 0x00d7d370
namespace SP {
uint32_t __cdecl FUN_00d7d370(cCreatureBase_s00d7_d370* pCreature, float* pPosition)
{
    uint32_t best = 0xffffffff;
    float bestDistance = 3.402823466e+38f;

    int count = (int)((char*)pCreature->mpHolder - (char*)pCreature->mHoldingState) / 0x24;
    for (int i = 0; i < count; ++i) {
        if (!FUN_00c0f510((uint32_t)i))
            continue;
        float position[3];
        uint32_t part = pCreature->PlayIdleAnimation(0, i);
        float dx = position[0] - pPosition[0];
        float dy = position[1] - pPosition[1];
        float dz = position[2] - pPosition[2];
        float distance = dx * dx + dy * dy + dz * dz;
        if (distance < bestDistance) {
            bestDistance = distance;
            best = part;
        }
    }
    return best;
}
}  // namespace SP

// @ 0x00d7d4a0
namespace SP {
void __cdecl ManageInteractiveOrnamentEventSFX(int* pEvent, uint8_t* pObject)
{
    if (!pEvent || !pObject)
        return;
    int32_t* pData = *(int32_t**)(pObject + 0xb54);
    if (!pData)
        return;

    switch (pEvent[0x110 / 4]) {
    case 1:
        pData[0x170 / 4] = 0x72776c66;
        return;
    case 2:
        pData[0x170 / 4] = 0x656e6f62;
        return;
    case 3:
        pData[0x170 / 4] = 0x6b697473;
        return;
    case 4:
        pData[0x170 / 4] = 0x69757266;
        return;
    case 5:
        pData[0x170 / 4] = 0x6b636f72;
        return;
    case 6:
        pData[0x170 / 4] = 0x6c6c6873;
        return;
    default:
        pData[0x170 / 4] = 0x746c6664;
        return;
    }
}
}  // namespace SP

// @ 0x00d7d540
namespace SP {
void StayBetween(cCreatureBase_s00d7_d370* pCreature, float distance, int* pFrom, int* pTo)
{
    cCommunity_s00d7_d370* pCommunity = (cCommunity_s00d7_d370*)FUN_00b23a40(NounManager());
    if (!pCommunity)
        return;
    cCreatureBase_s00d7_d370* pLeader = (cCreatureBase_s00d7_d370*)pCommunity->GetLeader();
    if (!pLeader || pLeader->mbDead)
        return;

    float* pLeaderPos = pLeader->mpPosition->mpVtbl->GetPosition();
    float* pSelfPos = pCreature->mpPosition->mpVtbl->GetPosition();
    float dx = pSelfPos[0] - pLeaderPos[0];
    float dy = pSelfPos[1] - pLeaderPos[1];
    float dz = pSelfPos[2] - pLeaderPos[2];
    float dist = dx * dx + dy * dy + dz * dz;
    if (distance * distance < dist)
        return;

    float target[3];
    target[0] = pLeaderPos[0];
    target[1] = pLeaderPos[1];
    target[2] = pLeaderPos[2];
    FUN_00436ce0(target, target);
    MoveToPointAtSpeed(pCreature, 2, target, 1.0f, 2.0f);
}
}  // namespace SP

// @ 0x00d7d720
namespace SP {
float __cdecl FUN_00d7d720(cCreatureBase_s00d7_d370* pCreature)
{
    if (FUN_00d7d020(pCreature))
        return 1.0f;
    return 0.0f;
}
}  // namespace SP

// @ 0x00d7d740
namespace SP {
float __cdecl FUN_00d7d740(int* pCreature, behavior_stimuli_s00d7_d370* pStimuli)
{
    cCommunity_s00d7_d370* pCommunity = (cCommunity_s00d7_d370*)FUN_00b23a40(NounManager());
    if (!pCommunity)
        return 0.0f;

    cCreatureBase_s00d7_d370* pLeader = (cCreatureBase_s00d7_d370*)pCommunity->GetLeader();
    if (!pLeader || pLeader->mbDead)
        return 0.0f;

    float radius = GravityRadius();
    float* pLeaderPos = pLeader->mpPosition->mpVtbl->GetPosition();
    float* pSelfPos = ((cCreatureBase_s00d7_d370*)pCreature)->mpPosition->mpVtbl->GetPosition();
    float dx = pSelfPos[0] - pLeaderPos[0];
    float dy = pSelfPos[1] - pLeaderPos[1];
    float dz = pSelfPos[2] - pLeaderPos[2];
    if (!(radius * radius < dx * dx + dy * dy + dz * dz))
        return 0.0f;

    if (pStimuli) {
        pStimuli->GetAny(pCreature);
        *((float*)pStimuli->mPointers + 3) = radius * 0.5f;
        *((int*)pStimuli->mPointers + 4) = 0;
    }
    return 1.0f;
}
}  // namespace SP

// @ 0x00d7d840
namespace SP {
float __cdecl FUN_00d7d840(cCreatureBase_s00d7_d370* pCreature)
{
    if (!pCreature->mpTarget)
        return 0.0f;

    cLocation_s00d7_d370* pLocation = pCreature->mpPosition;
    float radius = pLocation->mpVtbl->GetRadius();
    void* pOwner = NounManager();
    cCreatureBase_s00d7_d370* pHolder = (cCreatureBase_s00d7_d370*)pOwner;
    if (pOwner && *(void**)((char*)pOwner + 0x160) != 0) {
        void* pBlock = *(void**)((char*)pOwner + 0x160);
        radius = radius + (*(IPositionVtbl**)((char*)pBlock + 0x34))->GetRadius();
    }
    float* pTarget = (float*)FUN_00c6acc0();
    float* pSelf = pLocation->mpVtbl->GetPosition();
    float dx = pSelf[0] - pTarget[0];
    float dy = pSelf[1] - pTarget[1];
    float dz = pSelf[2] - pTarget[2];
    return (dx * dx + dy * dy + dz * dz < radius * radius) ? 1.0f : 0.0f;
}
}  // namespace SP

// @ 0x00d7d910
namespace SP {
float __cdecl FUN_00d7d910(int* pCreature)
{
    uint32_t id = ((cCreatureBase_s00d7_d370*)((char*)*(int**)((char*)pCreature + 0xb4c) + 8))->PlayIdleAnimation(0x40000, 0);
    cCreatureBase_s00d7_d370* pAnim = (cCreatureBase_s00d7_d370*)WatchMemoryBlock(id);
    if (pAnim && ((pAnim->mFlags58 >> 9) & 1) != 0 && pAnim->mId != pCreature[0xb20 / 4] &&
        (pAnim->mpHolder == 0 || pAnim->mpHolder == (cCreatureBase_s00d7_d370*)pCreature)) {
        FUN_00c0b9d0(gLastAnimationBlock);
        return 1.0f;
    }
    return 0.0f;
}
}  // namespace SP

// @ 0x00d7da70
namespace SP {
float HOLDING_CREATURE_Decide(void * pCreature, double a2, unsigned int a3, nSPBehaviorTree::behavior_memory_block * a4, bool & a5, nSPBehaviorTree::decider * a6, nSPBehaviorTree::decider_state * a7)
{
    int* pBlock = (int*)FUN_00d99420((char*)*(int**)((char*)pCreature + 0xb4c) + 0x1d0, 0);
    void* pInterface = 0;
    if (pBlock && *pBlock)
        pInterface = *(void**)*pBlock;

    cCreatureBase_s00d7_d370* pTarget = (cCreatureBase_s00d7_d370*)FUN_00d99500(pInterface);
    if (!pTarget)
        return 0.0f;

    FUN_00401090();
    void* pPlayerProfile = FUN_004df420();
    if ((void*)pTarget->mId != pPlayerProfile)
        return 0.0f;
    if (!FUN_00c0b770())
        return 0.0f;

    void* pHolding = (char*)pCreature + 0xb28;
    FUN_00b3d4c0(pHolding, pCreature, pTarget);
    int result = FUN_00ba3f90(pHolding, pCreature, pTarget);
    if (result != 2 && result != 5)
        return 0.0f;

    return 1.0f;
}
}  // namespace SP

// @ 0x00d7db30
namespace SP {
float __cdecl FUN_00d7db30(int* pCreature)
{
    cGameNounManager_s00d7_d370* pManager = (cGameNounManager_s00d7_d370*)NounManager();
    void* pAvatar = pManager->GetAvatar();
    cCreatureBase_s00d7_d370* pTarget = (cCreatureBase_s00d7_d370*)FUN_00d99500(pAvatar);
    if (!pTarget || pTarget->mbDead)
        return 0.0f;

    void* pOwner = FUN_00c04590();
    void* pBlock = *(void**)((char*)pOwner + 0x160);
    if (!pBlock)
        return 0.0f;
    int32_t kind = *(int32_t*)((char*)pTarget->mpLocomotive + 0x1d8);
    if (kind != 0x2d852f0 && kind != (int32_t)0xd23fe7cau)
        return 0.0f;

    float radius = (*(IPositionVtbl**)((char*)pBlock + 0x34))->GetRadius();
    float* pSelf = pTarget->mpPosition->mpVtbl->GetPosition();
    float* pOther = (float*)FUN_00c6acc0();
    float dx = pSelf[0] - pOther[0];
    float dy = pSelf[1] - pOther[1];
    float dz = pSelf[2] - pOther[2];
    if (dx * dx + dy * dy + dz * dz < radius * radius)
        return 1.0f;
    radius = pTarget->mpPosition->mpVtbl->GetRadius();
    return (dx * dx + dy * dy + dz * dz < radius * radius) ? 1.0f : 0.0f;
}
}  // namespace SP

// @ 0x00d7dca0
namespace SP {
float cCombatantList::FUN_00d7dca0()
{
    ICombatant* pCombatant = GetAt(FindFirstValid());
    if (!pCombatant)
        return 0.0f;
    if (pCombatant->QueryInterface(0xce9f6639))
        return 1.0f;
    return 0.0f;
}
}  // namespace SP

// @ 0x00d7dd00
namespace SP {
float __cdecl FUN_00d7dd00(cCreatureBase_s00d7_d370* pCreature)
{
    void* pOwner = FUN_00c04590();
    float limit = *(float*)((char*)pOwner + 0x108);
    if (((pCreature->mFlags58 >> 8) & 1) != 0 || !(0.0f < limit))
        return 0.0f;

    float* pOther = (float*)FUN_00c6acc0();
    float* pSelf = pCreature->mpPosition->mpVtbl->GetPosition();
    float dx = pSelf[0] - pOther[0];
    float dy = pSelf[1] - pOther[1];
    float dz = pSelf[2] - pOther[2];
    if (!(limit * limit < dx * dx + dy * dy + dz * dz))
        return 0.0f;

    cCreatureBase_s00d7_d370* pAnim = (cCreatureBase_s00d7_d370*)FUN_00c0ee90();
    if (!pAnim || ((pAnim->mFlags58 >> 9) & 1) == 0)
        return 1.0f;
    return 0.0f;
}
}  // namespace SP

// @ 0x00d7ddd0
namespace SP {
float __cdecl FUN_00d7ddd0(cCreatureBase_s00d7_d370* pCreature)
{
    uint32_t id = ((cCreatureBase_s00d7_d370*)((char*)*(int**)((char*)pCreature + 0xb4c) + 8))->PlayIdleAnimation(0x2000000, 0);
    behavior_stimuli_s00d7_d370* pStimuli = (behavior_stimuli_s00d7_d370*)WatchMemoryBlock(id);
    cCreatureBase_s00d7_d370* pAnim = (cCreatureBase_s00d7_d370*)FUN_00d99470(pStimuli);
    if (!pAnim || pAnim == pCreature)
        return 0.0f;

    float* pSelf = pCreature->mpPosition->mpVtbl->GetPosition();
    float dx = pStimuli->mDirectionX - pSelf[0];
    float dy = pStimuli->mDirectionY - pSelf[1];
    float dz = pStimuli->mDirectionZ - pSelf[2];
    float radius = pCreature->mpPosition->mpVtbl->GetRadius() + pStimuli->mRadius;
    if (dx * dx + dy * dy + dz * dz < radius * radius)
        return 1.0f;
    return 0.0f;
}
}  // namespace SP

// @ 0x00d7df00
namespace SP {
float __cdecl FUN_00d7df00(cCreatureBase_s00d7_d370* pCreature, int* pContext)
{
    if (!pCreature || pCreature->mbDead)
        return 0.0f;
    cCreatureBase_s00d7_d370* pHolder = pCreature->mpHolder;
    if (!pHolder || pHolder == pCreature)
        return 0.0f;

    float* pSelf = pCreature->mpPosition->mpVtbl->GetPosition();
    float* pOther = pHolder->mpPosition->mpVtbl->GetPosition();
    float dx = pSelf[0] - pOther[0];
    float dy = pSelf[1] - pOther[1];
    float dz = pSelf[2] - pOther[2];
    float radius = pCreature->mpPosition->mpVtbl->GetRadius() + pHolder->mpPosition->mpVtbl->GetRadius();
    if (dx * dx + dy * dy + dz * dz < radius * radius)
        return 1.0f;
    return 0.0f;
}
}  // namespace SP

// @ 0x00d7e090
namespace SP {
float __cdecl FUN_00d7e090(cCreatureBase_s00d7_d370* pCreature, int* pContext)
{
    if (!pCreature || pCreature->mbDead)
        return 0.0f;
    cCreatureBase_s00d7_d370* pTarget = pCreature->mpHolder;
    if (!pTarget || pTarget == pCreature)
        return 0.0f;
    if (pCreature->mId == pTarget->mId)
        return 0.0f;

    float* pSelf = pCreature->mpPosition->mpVtbl->GetPosition();
    float* pOther = pTarget->mpPosition->mpVtbl->GetPosition();
    float dx = pSelf[0] - pOther[0];
    float dy = pSelf[1] - pOther[1];
    float dz = pSelf[2] - pOther[2];
    float radius = pCreature->mpPosition->mpVtbl->GetRadius();
    if (dx * dx + dy * dy + dz * dz < radius * radius)
        return 1.0f;
    return 0.0f;
}
}  // namespace SP

// @ 0x00d7e290
float FUN_00d7e290(cGameObj* a1, void* a2, void* a3, void* a4, cOutRec* a5, uint8_t* a6, void* a7, cKeySrc* a8)
{
    void* slot = ((cSelf*)&a1->mpB4c->mStimuli)->FUN_00bc96a0(0x400, 0);

    cGameObj* found = (cGameObj*)FUN_00d998f0(FUN_00d99a10(slot));
    if (found != 0)
    {
        cGameObj* cur = ((cVtV5c*)found)->v5c(TAG_CREATURE_TARGET);
        if (cur != 0)
        {
            int32_t stage = a1->mStageB88;
            if (stage >= 5 || stage >= cur->mStageB88)
                return 0.0f;
        }

        ((cSelf*)&a1->mpB4c->mStimuli)->FUN_00bc98f0(0x400, 0);
        if (a5 != 0)
            ((cSelf*)a5)->FUN_00d997e0();
        *a6 = 1;
        a5->mpNew = found;
        return 1.0f;
    }

    ((cSelf*)&a1->mpB4c->mStimuli)->FUN_00bc98f0(0x400, 0);
    return 0.0f;
}

// @ 0x00d7e340
float FUN_00d7e340(cGameObj* a1, void* a2, void* a3, void* a4, cOutRec* a5, uint8_t* a6, void* a7, cKeySrc* a8)
{
    cGameObj* av = ((cSelf*)FUN_00b3d300())->FUN_00b1fdb0();
    if (av != 0)
    {
        cGameObj* idAv = ((cSelf*)av)->FUN_00c04590();
        if (idAv == ((cSelf*)a1)->FUN_00c04590())
        {
            void* slot = ((cSelf*)&av->mpB4c->mStimuli)->FUN_00bc96a0(0x400, 0);
            if (slot != 0)
            {
                float radius2 = DAT_01582ec0 * DAT_01582ec0;
                cVec3* ref = (cVec3*)((cSelf*)((cSelf*)av)->FUN_00c04590())->FUN_00c6acc0();

                cVec3* p1 = ((cVtV2cP*)&a1->mC0)->v2c();
                float d1x = p1->x - ref->x;
                float d1y = p1->y - ref->y;
                float d1z = p1->z - ref->z;

                cVec3* p2 = ((cVtV2cP*)&av->mC0)->v2c();
                float d2x = p2->x - ref->x;
                float d2y = p2->y - ref->y;
                float d2z = p2->z - ref->z;

                if (radius2 > d2x * d2x + d2y * d2y + d2z * d2z)   // avatar inside the radius
                {
                    if (radius2 > d1x * d1x + d1y * d1y + d1z * d1z)   // and so are we
                    {
                        cGameObj* target = (cGameObj*)FUN_00d99470(FUN_00d999d0(slot));
                        if (target != 0)
                        {
                            if (target->mIdB20 != a1->mIdB20)
                            {
                                if (a5 != 0)
                                    ((cSelf*)a5)->FUN_00d997e0();
                                *a6 = 1;
                                a5->mpNew = &target->m5a8;
                                return 1.0f;
                            }
                        }
                    }
                }
            }
        }
    }
    return 0.0f;
}

// @ 0x00d7e4e0
float FUN_00d7e4e0(cGameObj* a1, void* a2, void* a3, void* a4, cOutRec* a5, uint8_t* a6, void* a7, cKeySrc* a8)
{
    cGameObj* found = (cGameObj*)FUN_00d998f0(a1->mp1698);
    if (found != 0)
    {
        void* r = ((cVtV5c*)found)->v5c(TAG_ANIM_TARGET);
        if (r != 0)
        {
            cTargetInfo* info = (cTargetInfo*)((cSelf*)r)->FUN_00ca71d0();
            if (info->mKind == 1)
            {
                cGameObj* obj = (cGameObj*)info->mpObj;
                if (obj != 0)
                {
                    if (((cVtV2cB*)obj)->v2c() == 0)
                    {
                        if (obj != ((cVtV0c*)&a1->m5a8)->v0c())
                        {
                            if (a5 != 0)
                                ((cSelf*)a5)->FUN_00d997e0();
                            *a6 = 1;
                            a5->mpNew = FUN_00ae6740(info->mpObj);
                            return 1.0f;
                        }
                    }
                }
            }
        }
    }
    return 0.0f;
}

// @ 0x00d7e580
float FUN_00d7e580(cGameObj* a1, void* a2, void* a3, void* a4, cOutRec* a5, uint8_t* a6, void* a7, cKeySrc* a8)
{
    cGameObj* found = (cGameObj*)FUN_00d998f0(a1->mp1698);
    if (found != 0)
    {
        cSlotObj* v = ((cVtV08*)found)->v08();

        void* goal;
        if (v->mHasGoal != 0)
        {
            goal = (void*)((cVtV2cP*)v)->v2c();
        }
        else
        {
            uint32_t local = 0;
            void* q = (void*)((cVtV2cP*)v)->v2c();
            goal = ((cSelf*)FUN_00b3d350())->FUN_00b81630(&local, q);
        }

        cSlotObj* v2 = ((cVtV08*)found)->v08();
        float fv = ((cVtV74I*)v2)->v74(1);
        float fa = ((cVtV74B*)&a1->mC0)->v74(goal, fv);
        int32_t h = ((cVtV2c1*)&a1->mC0)->v2c(fa);
        if (FUN_00d99a60(h) > DAT_01572070 * 2.0f + DAT_013f08c0)
        {
            if (a5 != 0)
                ((cSelf*)a5)->FUN_00d997e0();

            a5->mpAux = (void*)((cVtV0c*)found)->v0c();

            cSlotObj* v3 = ((cVtV08*)found)->v08();

            // Accumulated left-to-right straight out of the v74 calls, exactly as retail's x87 does.
            a5->m18 = (int32_t)(((cVtV74F*)&a1->mC0)->v74() +
                                ((cVtV74F*)v3)->v74() + DAT_01486110);
            a5->m1c = 3;
            a5->m20 = 0;
            *a6 = 1;
            return 1.0f;
        }
    }
    return 0.0f;
}

// @ 0x00d7e6e0
bool FUN_00d7e6e0(cGameObj* a1, void* a2, void* a3, void* a4, cOutRec* a5, uint8_t* a6, void* a7, cKeySrc* a8)
{
    cGameObj* found = (cGameObj*)FUN_00d998f0(a1->mp1698);
    if (found != 0)
    {
        cSlotObj* node = ((cVtV08*)found)->v08();

        cVec3* pa = ((cVtV2cP*)&a1->mC0)->v2c();
        cVec3* pb = ((cVtV2cP*)node)->v2c();

        cVec3 dif;
        dif.x = pb->x - pa->x;
        dif.y = pb->y - pa->y;
        dif.z = pb->z - pa->z;

        float inv = 1.0f / sqrtf(dif.x * dif.x + dif.y * dif.y + dif.z * dif.z + DAT_013ec4b8);

        cVec3 nrm;
        nrm.x = dif.x * inv;
        nrm.y = dif.y * inv;
        nrm.z = dif.z * inv;

        cVec3* fwd = ((cVtV5cV*)&a1->mC0)->v5c(&dif);
        if (fwd->x * nrm.x + fwd->y * nrm.y + fwd->z * nrm.z < 0.0f)
        {
            ((cSelf*)a1)->FUN_00c12310(TAG_INTERRUPT_ANIM, -1, 0);
            cVec3* pt = ((cVtV2c3*)&a1->mC0)->v2c(&nrm, 1.0f, DAT_01470f1c);
            ((cSelf*)a1)->FUN_00c1c5c0(2, pt);
        }
    }

    if (((cSelf*)&a1->mC0)->FUN_00c42e20())
        if (!((cSelf*)a1)->FUN_00c0e0c0(TAG_ANIM_STATE))
            ((cSelf*)a1)->FUN_00c12190(TAG_ANIM_STATE, 1, -1);

    return true;
}

// @ 0x00d7e910
float FUN_00d7e910(cGameObj* a1, void* a2, void* a3, void* a4, cOutRec* a5, uint8_t* a6, void* a7, cKeySrc* a8)
{
    void* slot = ((cSelf*)&a1->mpB4c->mStimuli)->FUN_00bc96a0(0, 0x8000);
    if (slot != 0)
        return 1.0f;

    cGameObj* o = ((cSelf*)a1)->FUN_00c04590();
    if (o->mAction15c == 3 || o->mAction15c == 4)
    {
        if (((cSelf*)a1)->FUN_00c0f570() > 0)
        {
            void* e = ((cSelf*)a1)->FUN_00c0f8a0(((cSelf*)a1)->FUN_00c0f780());
            if (e != 0)
            {
                void* r = ((cVtVb8*)e)->vb8(TAG_SOCIAL_ANIM);
                if (r == 0)
                {
                    r = FUN_00d2ec30(e);
                    if (r == 0)
                        return 0.0f;
                    if (o->mAction15c != 4)
                        return 0.0f;
                }
                ((cSelf*)&a1->mpB4c->mStimuli)->FUN_00bc97f0(0, 0x8000, DAT_01473c70, r);
                return 1.0f;
            }
        }
    }
    return 0.0f;
}

// @ 0x00d7e9d0
float FUN_00d7e9d0(cGameObj* a1, void* a2, void* a3, void* a4, cOutRec* a5, uint8_t* a6, void* a7, cKeySrc* a8)
{
    cOwnerLink* link = &((cGameObjB*)((cSelf*)a1)->FUN_00c04590())->mOwnerLink;
    cGameObj* o = (cGameObj*)link->mpOwner;
    if (o != 0)
    {
        if (o->mpB4c->mKind == TAG_LIST_STATE)
        {
            if (a5 != 0)
                ((cSelf*)a5)->FUN_00d997e0();
            *a6 = 1;
            a5->mpCur = 0;
            return 1.0f;
        }
    }
    return 0.0f;
}

// @ 0x00d7ea20
float FUN_00d7ea20(cGameObj* a1, void* a2, void* a3, void* a4, cOutRec* a5, uint8_t* a6, void* a7, cKeySrc* a8)
{
    cGameObj* o = ((cSelf*)a1)->FUN_00c04590();

    if ((uint32_t)((o->mListEnd044 - o->mListBegin040) >> 2) > 1u)
    {
        if (((cSelf*)o)->FUN_00c6ac40())
        {
            if (a5 != 0)
                ((cSelf*)a5)->FUN_00d997e0();
            *a6 = 1;
            a5->mpCur = 0;
            return 1.0f;
        }
    }
    return 0.0f;
}

// @ 0x00d7ea70
void FUN_00d7ea70(cGameObj* a1, void* a2, void* a3, void* a4, cOutRec* a5, uint8_t* a6, void* a7, cKeySrc* a8)
{
    if (a1->mFlagB5e == 0 && a1->mFlag135 != 0)
        ((cSelf*)a1)->FUN_00c14750(0);

    cHolder* holder = a1->mpB54;
    if (holder != 0)
        holder->mSpeed = DAT_01485720;
}

// @ 0x00d7f790
namespace SP {
bool THROW_OBJECT_Tick(cSPCreatureBase_s00d7_f790* c, int, int, int, int, ThrowState* st)
{
    AnimTarget* idle = c->mpAnimOwner->mgr.PlayIdleAnimation(0, 0x40000);
    AutoRefCount<SpatialObj>* ref = &st->mTarget;
    if (!ref->mpObject)
        return false;

    SpatialObj* cast = 0;
    if (idle)
        cast = FUN_00d998d0_s00d7_f790(idle, 0x1186577);
    Vec3 pos = g_defaultThrowPos;

    if (cast && cast != ref->mpObject) {
        Box tmp;
        const Box* b = cast->GetBoundingBox(&tmp);
        Vec3 center((b->lo.x + b->hi.x) * 0.5f, (b->hi.y + b->lo.y) * 0.5f, (b->hi.z + b->lo.z) * 0.5f);
        pos = center;
    }
    else {
        bool found = false;
        if (c->IsCreature()) {
            AnimTarget* h2 = c->mpAnimOwner->mgr.PlayIdleAnimation(0x400, 0);
            if (h2) {
                AnimTarget* at = FUN_00d99a10_s00d7_f790(h2);
                if (at && at->mWeight > 0.0f) {
                    SpatialObj* cur = ref->mpObject;
                    if (cur != at->GetTarget()) {
                        const Vec3* p = at->GetTarget()->GetPosition();
                        pos.x = p->x;
                        pos.y = p->y;
                        pos.z = p->z;
                        found = true;
                    }
                }
            }
        }
        if (!found) {
            Loco* L = &c->mLoco;
            float h = L->GetHeight() + 50.0f;
            Vec3 ftmp;
            const Vec3* f = L->GetForward(&ftmp);
            float inv = 1.0f / sqrtf(f->x * f->x + f->y * f->y + f->z * f->z + 1e-8f);
            Vec3 off((inv * f->x) * h, (inv * f->y) * h, (inv * f->z) * h);
            const Vec3* lp = L->GetPosition();
            pos = Vec3(lp->x + off.x, lp->y + off.y, lp->z + off.z);
        }
    }

    switch (st->mState) {
    case 0:
        if (c->mbCanMove) {
            const Vec3* lp = c->mLoco.GetPosition();
            Vec3 cp(lp->x, lp->y, lp->z);
            Vec3 surf;
            PlanetModel()->DirectionToSurfacePosition(&surf, &pos);
            Vec3 d(surf.x - cp.x, surf.y - cp.y, surf.z - cp.z);
            Vec3 n;
            normalized_safe(&n, &d);
            Vec3 p2(n.x + cp.x, n.y + cp.y, n.z + cp.z);
            c->MoveToPointAndFacingAtSpeed(2, &p2, &n, 1.0f, 2.0f);
            st->mState = 1;
        }
        break;
    case 1:
        if (c->mLoco.IsNearGoal()) {
            c->PlayAnimationWithTarget(ThrowAnimID(st), &pos, st->mArg);
            st->mState = 2;
            return true;
        }
        break;
    case 2: {
        float evt;
        bool released = c->WaitForAnimEventOrEnd(g_throwEvent, &evt, ThrowAnimID(st), 0, 1);
        if (!st->mbDone && released) {
            FUN_00f20ba0(FUN_00ad2670(ref), c);
            c->FUN_00c15d50(ref->mpObject, 0, 0);
            cInteractableObject_s00d7_f790* io = InterfaceCast(ref);
            if (io)
                io->mSub.Notify(&c->mNoAttackTimer);
            float radius = PlanetModel()->GetRadius();
            Loco* L = &c->mLoco;
            float v = L->GetSpeed() * 0.05f;
            v = max(v, 10.0f);
            if (c->IsCreature()) {
                v = min(v, 20.0f);
            }
            else if (GetImpulseSystem()->mField20 == 0) {
                v = Clamp(v, 10.0f, 30.0f);
            }
            Box tmp1;
            const Box* b1 = ref->mpObject->GetBoundingBox(&tmp1);
            Vec3 c1((b1->lo.x + b1->hi.x) * 0.5f, (b1->hi.y + b1->lo.y) * 0.5f, (b1->hi.z + b1->lo.z) * 0.5f);
            Vec3 d(pos.x - c1.x, pos.y - c1.y, pos.z - c1.z);
            float len = sqrtf(d.z * d.z + d.y * d.y + d.x * d.x);
            float f = 1.0f / (len + 1.5258789e-05f);
            Vec3 dir(d.x * f, d.y * f, d.z * f);
            float speed = VectorLength(L->GetVelocity()) + v;
            float t = -(len / v * 0.5f * radius);
            float h = min(t, v);
            Box tmp2;
            const Box* b2 = ref->mpObject->GetBoundingBox(&tmp2);
            Vec3 c2((b2->lo.x + b2->hi.x) * 0.5f, (b2->hi.y + b2->lo.y) * 0.5f, (b2->hi.z + b2->lo.z) * 0.5f);
            Vec3 n2;
            const Vec3* nn = normalized_safe(&n2, &c2);
            Vec3 impulse(dir.x * speed + nn->x * h, dir.y * speed + nn->y * h, dir.z * speed + nn->z * h);
            GetImpulseSystem()->ApplyImpulse(ref->mpObject, &impulse, 1);
            GetImpulseSystem()->Follow(L, ref->mpObject, 0.5f);
            st->mbDone = true;
        }
        else {
            SpatialObj* t = ref->mpObject;
            if (t) {
                void* iface = t->QueryInterface(0x398420d);
                if (iface)
                    ManageInteractiveOrnamentEventSFX(iface, c);
            }
        }
        if (c->AnimationFinished(ThrowAnimID(st)))
            return false;
        break;
    }
    }
    return true;
}
}  // namespace SP

// @ 0x00d7ff20
namespace SP {
bool ATTACK_Tick(void* pSelf, double, uint32_t, uint32_t, behavior_memory_block_s00d7_ff20* pMemory, behavior_memory_block_s00d7_ff20*, float dt)
{
    cSPCreatureBase_s00d7_ff20* creature = (cSPCreatureBase_s00d7_ff20*)pSelf;
    // The memory block is always reached through the parameter (its address is taken below), so it is
    // re-read after every store, as in the original.
#define mem ((ATTACK_memory_block*)pMemory)

    cCombatant_s00d7_ff20* target = creature->GetTarget();
    if (!target) return false;
    cSPCreatureBase_s00d7_ff20* targetCreature = creature->GetTargetAsCreature();
    if (targetCreature && !FUN_00d99470(targetCreature)) return false;

    BehaviorNode* node = creature->mpBehaviorTreeData->mTree.PlayIdleAnimation(0x10, 0);
    if (node) mem->mAttackIdx = node->mAttackIdx;

    uint32_t attackIdx = mem->mAttackIdx;
    if (attackIdx == (uint32_t)-1) attackIdx = creature->mCurrentAttackIdx;
    cCreatureAbility_s00d7_ff20* ability = (attackIdx != (uint32_t)-1) ? creature->GetAbility(attackIdx) : 0;

    const Vector3_s00d7_ff20& targetPos = target->ToSpatialObject()->GetPosition();
    cLocomotiveObject_s00d7_ff20* loco = &creature->mLoco;
    const Vector3_s00d7_ff20& myPos = loco->GetPosition();
    float targetRadius = target->ToSpatialObject()->GetFootprintRadius();
    float myRadius = loco->GetFootprintRadius();
    float radiusSum = myRadius + targetRadius;
    float scale = FUN_00d38a30(0, creature);

    float minRange, maxRange, bound;
    if (ability) {
        bool b = TestBit(creature->mGeneralFlags, 9);
        maxRange = (ability->mRushingRange + ability->mRange) * scale;
        minRange = ability->mRange * scale;
        bound = ability->GetBound(b);
    } else {
        maxRange = 0.0f;
        minRange = 0.0f;
        bound = 0.0f;
    }
    float nearDist = minRange + radiusSum;
    float farDist = nearDist + myRadius;

    if (mem->mAttackIdx != (uint32_t)-1) {
        float dist = FUN_00d99a60(targetPos, targetRadius, myPos, myRadius, true);
        Vector3_s00d7_ff20 goal(targetPos);
        if (targetCreature) {
            float speed = creature->FUN_00c0cfa0(2, 0);
            if (speed > 1.5258789e-05f && dist <= FUN_00d38a30(5, creature)) {
                Vector3_s00d7_ff20 diff = targetPos - myPos;
                Vector3_s00d7_ff20 dir;
                normalized_safe(&dir, &diff);
                Vector3_s00d7_ff20 desired(dir.x * speed, dir.y * speed, dir.z * speed);
                const Vector3_s00d7_ff20& vel = targetCreature->mLoco.GetVelocity();
                Vector3_s00d7_ff20 rel(vel.x - desired.x, vel.y - desired.y, vel.z - desired.z);
                float len = sqrtf(rel.x * rel.x + rel.y * rel.y + rel.z * rel.z);
                if (len > 0.0f) {
                    float t = dist / len;
                    const Vector3_s00d7_ff20& v = targetCreature->mLoco.GetVelocity();
                    goal.x += v.x * t;
                    goal.y += v.y * t;
                    goal.z += v.z * t;
                }
            }
        }
        Vector3_s00d7_ff20 surface;
        goal = *PlanetModel_s00d7_ff20()->FUN_00b81630(&surface, &goal);

        Vector3_s00d7_ff20 toGoal = goal - myPos;
        float invLen = 1.0f / sqrtf(toGoal.x * toGoal.x + toGoal.y * toGoal.y + toGoal.z * toGoal.z + 1e-08f);
        Vector3_s00d7_ff20 facing(invLen * toGoal.x, toGoal.y * invLen, toGoal.z * invLen);
        creature->MoveToPointAndFacingAtSpeed(2, &goal, &facing, nearDist, farDist);

        if (targetCreature) {
            cLocomotiveObject_s00d7_ff20* targetLoco = &targetCreature->mLoco;
            if (NotEqual(targetLoco->GetVelocity(), Vector3_s00d7_ff20::ZERO)) {
                Vector3_s00d7_ff20 n;
                const Vector3_s00d7_ff20* pn = normalized_safe(&n, &targetLoco->GetVelocity());
                Vector3_s00d7_ff20 d = loco->GetDirection();
                if (Dot(d, *pn) > 0.0f)
                    loco->GetGoal()->mState = 2;
            }
        }

        Vector3_s00d7_ff20 toTarget = targetPos - myPos;
        float inv = 1.0f / sqrtf(toTarget.x * toTarget.x + toTarget.y * toTarget.y + toTarget.z * toTarget.z);
        Vector3_s00d7_ff20 fwd(inv * toTarget.x, toTarget.y * inv, toTarget.z * inv);
        facing = fwd;
        float invUp = 1.0f / sqrtf(myPos.x * myPos.x + myPos.y * myPos.y + myPos.z * myPos.z);
        Vector3_s00d7_ff20 up(myPos.x * invUp, myPos.y * invUp, myPos.z * invUp);
        float k = Dot(up, fwd);
        Vector3_s00d7_ff20 tangent(fwd.x - up.x * k, fwd.y - up.y * k, fwd.z - up.z * k);
        if (NotEqual(tangent, Vector3_s00d7_ff20::ZERO)) {
            Vector3_s00d7_ff20 t;
            facing = *Vector3_Normalize(&t, &tangent);
        }

        mem->mChaseDistance = Max(mem->mChaseDistance, minRange);

        if (mem->mDropItems) {
            if (creature->WaitForAnimEventOrEnd(g_AttackDropEvent, &pMemory, -1, 0, 1)
                || creature->AnimationFinished(0x3a74a0b))
                creature->FUN_00c19940(1);
            if (creature->AnimationFinished(0x3a74a0b)) {
                mem->mDropItems = false;
                creature->FUN_00c14750(0);
                return true;
            }
            creature->PlayAnimation(0x3a74a0b, 1, -1);
            return true;
        }

        if (dist <= maxRange && dist >= bound) {
            Vector3_s00d7_ff20 d = loco->GetDirection();
            if (Dot(d, facing) > 0.85f) {
                creature->Attack(mem->mAttackIdx, 0);
                mem->mAttackIdx = (uint32_t)-1;
                if (node) node->mAttackIdx = (uint32_t)-1;
                if (ability->mType == 0x1d) return false;
                return true;
            }
        }

        if (mem->mAttackRoar && creature->mNoAttackTimer <= 0.0f) {
            if ((float)creature->mAttackTimer.GetElapsedTime() * 0.001f > g_AttackRoarDelay) {
                if (creature->AnimationFinished(0x2481df9)) {
                    mem->mAttackRoar = false;
                    creature->FUN_00c14750(0);
                    return true;
                }
                creature->PlayAnimation(0x2481df9, 1, -1);
                return true;
            }
        }

        if (loco->IsNearGoal()) {
            creature->PlayAnimation(0x26ede51, 1, -1);
            return true;
        }
    } else {
        if (creature->mCurrentAttackIdx != (uint32_t)-1) {
            const Vector3_s00d7_ff20& tp = target->ToSpatialObject()->GetPosition();
            const Vector3_s00d7_ff20& mp = loco->GetPosition();
            Vector3_s00d7_ff20 diff = tp - mp;
            Vector3_s00d7_ff20 dir;
            creature->MoveToPointAndFacingAtSpeed(2, &tp, Vector3_Normalize(&dir, &diff), nearDist, farDist);
            if (!targetCreature) return true;
            cLocomotiveObject_s00d7_ff20* targetLoco = &targetCreature->mLoco;
            if (!Vector3_NotEqual(targetLoco->GetVelocity(), Vector3_s00d7_ff20::ZERO)) return true;
            Vector3_s00d7_ff20 n;
            if (Dot3(loco->GetDirection(), *normalized_safe(&n, &targetLoco->GetVelocity())) > 0.0f)
                loco->GetGoal()->mState = 2;
            return true;
        }

        BehaviorNode* watch = creature->mpBehaviorTreeData->mTree.PlayIdleAnimation(2, 0);
        if (node) {
            cSPCreatureBase_s00d7_ff20* watched = WatchMemoryBlock(watch);
            if (watched && watched == targetCreature) return false;
        }

        mem->mTimer -= dt;
        if (mem->mTimer < 0.0f) return false;

        if (creature->AnimationFinished(0) && creature->mCurrentAttackIdx == (uint32_t)-1) {
            if (loco->IsNearGoal())
                creature->PlayAnimation(0x26ede51, 1, -1);
            else
                creature->PlayAnimation(0x39e477b, 1, -1);
        }

        Vector3_s00d7_ff20 diff = targetPos - myPos;
        float chase = mem->mChaseDistance + radiusSum;
        float len = sqrtf(diff.x * diff.x + diff.y * diff.y + diff.z * diff.z);
        if ((len > chase && loco->GetGoal()->mState != 0)
            || (len > chase + 1.0f && loco->GetGoal()->mState == 0)) {
            float inv = 1.0f / len;
            Vector3_s00d7_ff20 facing(inv * diff.x + 1.5258789e-05f, diff.y * inv + 1.5258789e-05f, diff.z * inv + 1.5258789e-05f);
            creature->MoveToPointAndFacingAtSpeed(2, &targetPos, &facing, chase, chase);
        } else {
            return true;
        }
    }

    creature->PlayAnimation(0x39e477b, 1, -1);
    return true;
#undef mem
}
}  // namespace SP

// @ 0x00d81940
bool __cdecl FUN_00d81940(cSPCreatureBase_s00d8_1940* c, u32, u32, u32, u32, DRINK_Mem* mem)
{
  cNearNoun_s00d8_1940* noun = c->Get();
  mem->mState = 0;
  mem->mTimer = 0.0f;

  cPlanetModel_s00d8_1940* pm = PlanetModel_s00d8_1940();
  Vec3_s00d8_1940* center = noun->FUN_00c6bdc0();
  Vec3_s00d8_1940 pos;
  pm->MakeRandomWorldPosition(&pos, center, 3.0f, 10.0f);

  Vec3_s00d8_1940 water;
  pm->FindClosestWater(&pos, 1.0f, &water);

  Vec3_s00d8_1940* locoPos = VSLOT(Vec3Slot, &c->mLoco, 0x2c)(&c->mLoco);
  Vec3_s00d8_1940 delta;
  delta.x = water.x - locoPos->x;
  delta.y = water.y - locoPos->y;
  delta.z = water.z - locoPos->z;
  float inv = 1.0f / sqrtf(delta.x * delta.x + delta.y * delta.y + delta.z * delta.z + 1e-08f);
  delta.x *= inv;
  delta.y *= inv;
  delta.z *= inv;

  float radius = VSLOT(FloatSlot, &c->mLoco, 0x74)(&c->mLoco);
  Vec3_s00d8_1940 target;
  target.x = water.x + delta.x * radius;
  target.y = water.y + delta.y * radius;
  target.z = water.z + delta.z * radius;

  Vec3_s00d8_1940 surf;
  pm->FUN_00b81630(&surf, &target);

  mem->mTarget = surf;
  mem->mTarget2 = surf;
  pm->RayCast(&mem->mTarget, 10.0f, &mem->mTarget2, 1.0f, 0, 5);
  c->MoveToPointAtSpeed(2, &mem->mTarget2, 1.0f, 2.0f);
  c->FUN_00c14750(!VSLOT(BoolSlot, &c->mLoco, 0xf8)(&c->mLoco));
  return true;
}

// @ 0x00d81b60
bool __cdecl FUN_00d81b60(cSPCreatureBase_s00d8_1940* c, u32, u32, u32 flags, u32, DRINK_Mem* mem, u32, float dt)
{
  if (!CreateLayoutManager_s00d8_1940()->LookupA(c, 0, 0))
    return false;

  switch (mem->mState) {
  case 0:
    if (c->mLoco.IsNearGoal()) {
      mem->mState = 1;
      c->MoveToPointAtSpeed(2, &mem->mTarget, 1.0f, 2.0f);
      return true;
    }
    break;

  case 1:
    if (c->mLoco.IsNearGoal()) {
      mem->mState = 3;
      if (c->mDrinkFlag_f90 == 0 && (flags & 0x180000) == 0) {
        mem->mState = 2;
        return true;
      }
      c->mFlags_b58 |= 0x400;
      float radius = VSLOT(FloatSlot, &c->mLoco, 0x74)(&c->mLoco);
      Vec3_s00d8_1940 dir;
      VSLOT(Vec3OutSlot, &c->mLoco, 0x5c)(&c->mLoco, &dir);
      Vec3_s00d8_1940* pos = VSLOT(Vec3Slot, &c->mLoco, 0x2c)(&c->mLoco);
      Vec3_s00d8_1940 target;
      target.x = pos->x + dir.x * radius;
      target.y = pos->y + dir.y * radius;
      target.z = pos->z + dir.z * radius;
      Vec3_s00d8_1940 surf;
      PlanetModel_s00d8_1940()->FUN_00b81630(&surf, &target);
      c->FUN_00c14990(0x27079bb, &surf, -1);
      c->PlayAnimationWithTarget(0x27079c1, &surf, -1);
      return true;
    }
    break;

  case 2:
    if (c->mDrinkFlag_f90 == 0) {
      if ((flags & 0x180000) == 0)
        return true;
    }
    mem->mState = 1;
    break;

  case 3:
    if (c->AnimationFinished(0x27079bb)) {
      mem->mState = 4;
      mem->mTimer = RandomFloatRange(3.0f, 10.0f);
      if (c->FUN_00c0e0c0(0x27079c1) == 0) {
        float radius = VSLOT(FloatSlot, &c->mLoco, 0x74)(&c->mLoco);
        Vec3_s00d8_1940 dir;
        VSLOT(Vec3OutSlot, &c->mLoco, 0x5c)(&c->mLoco, &dir);
        Vec3_s00d8_1940* pos = VSLOT(Vec3Slot, &c->mLoco, 0x2c)(&c->mLoco);
        Vec3_s00d8_1940 target;
        target.x = pos->x + dir.x * radius;
        target.y = pos->y + dir.y * radius;
        target.z = pos->z + dir.z * radius;
        Vec3_s00d8_1940 surf;
        PlanetModel_s00d8_1940()->FUN_00b81630(&surf, &target);
        c->PlayAnimationWithTarget(0x27079c1, &surf, -1);
        return true;
      }
    }
    break;

  case 4:
    mem->mTimer -= dt;
    if (mem->mTimer < 0.0f) {
      mem->mState = 5;
      float radius = VSLOT(FloatSlot, &c->mLoco, 0x74)(&c->mLoco);
      Vec3_s00d8_1940 dir;
      VSLOT(Vec3OutSlot, &c->mLoco, 0x5c)(&c->mLoco, &dir);
      Vec3_s00d8_1940* pos = VSLOT(Vec3Slot, &c->mLoco, 0x2c)(&c->mLoco);
      Vec3_s00d8_1940 target;
      target.x = pos->x + dir.x * radius;
      target.y = pos->y + dir.y * radius;
      target.z = pos->z + dir.z * radius;
      Vec3_s00d8_1940 surf;
      PlanetModel_s00d8_1940()->FUN_00b81630(&surf, &target);
      c->PlayAnimationWithTarget(0x27079c3, &surf, -1);
      return true;
    }
    break;

  case 5:
    if (c->AnimationFinished(0x27079c3))
      mem->mState = 1;
    break;
  }
  return true;
}

// @ 0x00d821a0
void __cdecl SP_LOUNGE_VIGNETTE_Activate(cSPCreatureBase_s00d8_1940* c, u32, u32, u32, u32, u32, LOUNGE_Mem* mem)
{
  VSLOT(VoidSlot, &c->mLoco, 0xec)(&c->mLoco);

  LOUNGE_Node* node = mem->mpNode;
  if (!node) {
    cNearNoun_s00d8_1940* noun = c->Get();
    VignetteRange* range = FUN_00b3d4e0()->Find(mem->mTableKey, 0);
    VignetteDef* def = (VignetteDef*)((char*)range->mpBegin + mem->mVignetteIndex * 0x7b4);

    const Vec3_s00d8_1940* posPtr = noun->GetPosition();
    Vec3_s00d8_1940 pos = *posPtr;
    Vec3_s00d8_1940 surf = g_DefaultSurf;
    if (noun->mpField_160 == 0) {
      Quat q;
      PlanetModel_s00d8_1940()->BuildSurfaceOrientation(&q, &pos);
      FUN_0059aed0(&surf, (const Quat*)0x169f0e0, &q);
    } else {
      void* obj = (char*)noun->mpField_160 + 0x34;
      VSLOT(Vec3OutSlot, obj, 0x5c)(obj, &surf);
    }

    float r1 = VSLOT(FloatSlot, &c->mLoco, 0x74)(&c->mLoco);
    float r2 = VSLOT(FloatSlot, &c->mLoco, 0x74)(&c->mLoco);
    Vec3_s00d8_1940 out;
    PlanetModel_s00d8_1940()->MakeRandomWorldPosition(&out, &surf, r1, r2 * def->mField_04 + r1);

    node = FUN_00bc9b00()->Insert(0x564c368, def->mField_04, (const char*)0x18eb45e,
                                  (const char*)0x147c050);
    node->mHandleTimer.mHandle = -1;
    node->mHandleTimer.mHandle = FUN_00b3d4e0()->FUN_00bc65f0(def, &out, &surf);
    node->mHandleTimer.mTimer = 20.0f;
  }

  c->mpEnv_0b4c->FUN_00bcb480(node, c, 0, 0);
  FUN_00b3d4e0()->FUN_00bc4900(node->mHandleTimer.mHandle, c, 0);
}

// @ 0x00d823b0
void __cdecl FUN_00d823b0(cSPCreatureBase_s00d8_1940* c)
{
  LOUNGE_Node* node = c->mpEnv_0b4c->mpNode_600;
  if (node) {
    FUN_00b3d4e0()->FUN_00bc52a0(node->mHandleTimer.mHandle, c);
    if (node->mState10 == 1)
      node->mHandleTimer.mHandle = 0;
  }
  c->mpEnv_0b4c->FUN_00bcb430();
  if (c->mbB5e == 0)
    c->FUN_00c14750(1);
}

// @ 0x00d82410
bool __cdecl FUN_00d82410(cSPCreatureBase_s00d8_1940* c, u32, u32, u32, u32, u32, u32, float dt)
{
  LOUNGE_Node* node = c->mpEnv_0b4c->mpNode_600;
  LOUNGE_HandleTimer* ht = &node->mHandleTimer;
  if (ht->mHandle != -1) {
    VignetteMgr* mgr = FUN_00b3d4e0();
    if (mgr->FUN_00bc3db0(ht->mHandle)) {
      ht->mTimer -= dt;
      if (ht->mTimer < 0.0f)
        return false;
    }
    if (!c->mLoco.IsNearGoal() && (c->mFlags_330 & 1))
      return false;
    return mgr->FUN_00bc3df0(ht->mHandle) == 0;
  }
  return false;
}

// @ 0x00d824a0
namespace SP {
bool __cdecl POSSE_IDLE_Tick(cSPCreatureBase_s00d8_24a0* self, int, int, int, int, POSSE_IDLE_memory_block* mem, int, float dt)
{
    bool isCreatureGame = GetCurrentGameMode() == &g_GameModeCreature;
    cSPCreatureBase_s00d8_24a0* avatar = NounManager_s00d8_24a0()->GetAvatar();
    float dist = FUN_00d99ac0(avatar ? &avatar->mLoco : 0, self ? &self->mLoco : 0, true);
    Loco_s00d8_24a0* aloco = &avatar->mLoco;
    const Vec3_s00d8_24a0* avatarPos = aloco->GetPosition();
    float far2 = g_PosseFollowDist * 2.0f;
    float farDist = Min(far2, g_PosseMaxFollowDist) + 1.0f;

    const Vec3_s00d8_24a0& av = aloco->GetVelocity();
    if (av.x * av.x + av.y * av.y + av.z * av.z > 0.1f) {
        bool follow = mem->mbFollowing;
        if (!follow) {
            const Vec3_s00d8_24a0* p = aloco->GetPosition();
            float dz = p->z - mem->mAvatarPos.z;
            float dx = p->x - mem->mAvatarPos.x;
            float dy = p->y - mem->mAvatarPos.y;
            follow = (dz * dz + dx * dx) + dy * dy > 3.0f || !(dist < g_PosseFollowDist);
        }
        if (follow) {
            // Follow the moving avatar.
            mem->mbFollowing = true;
            self->FUN_00c14750(!self->mLoco.SlotF8());
            float t = mem->mTimer - dt;
            mem->mAnimHandle = 0;
            mem->mTimer = t;
            if (self->mLoco.GetState()->mHasPath != 0 && !(0.0f > mem->mTimer))
                return true;
            mem->mTimer = 0.5f;

            int mode = avatar->FUN_00c0b750();
            if (!(dist < g_PosseFollowDist))
                mode = 3;
            else if (mode == 0)
                mode = 2;

            const Vec3_s00d8_24a0& v = aloco->GetVelocity();
            Vec3_s00d8_24a0 dir;
            float inv = InvLen((v.x * v.x + v.y * v.y) + v.z * v.z);
            dir.x = v.x * inv;
            dir.y = inv * v.y;
            dir.z = inv * v.z;
            Vec3_s00d8_24a0 up;
            float invU = InvLen((avatarPos->x * avatarPos->x + avatarPos->y * avatarPos->y) +
                                avatarPos->z * avatarPos->z);
            up.x = avatarPos->x * invU;
            up.y = invU * avatarPos->y;
            up.z = invU * avatarPos->z;

            if (aloco->GetState()->mHasPath != 0) {
                const Vec3_s00d8_24a0* goal = aloco->GetState()->GetGoal();
                float gx = goal->x - avatarPos->x;
                float gz = goal->z - avatarPos->z;
                float gy = goal->y - avatarPos->y;
                float invG = InvLen((gx * gx + gz * gz) + gy * gy);
                dir.x = invG * gx;
                dir.y = invG * gy;
                dir.z = invG * gz;
            }

            // Side direction: the movement direction without its vertical part.
            float dp = (up.z * dir.z + up.y * dir.y) + up.x * dir.x;
            float tx = dir.x - dp * up.x;
            float tz = dir.z - dp * up.z;
            float ty = dir.y - dp * up.y;
            float lsq = (tz * tz + ty * ty) + tx * tx;
            if (lsq < 1.5258789e-05f)
                return true;
            float invS = InvLen(lsq);
            Vec3_s00d8_24a0 side;
            side.x = invS * tx;
            side.y = invS * ty;
            side.z = invS * tz;
            Vec3_s00d8_24a0 cr;
            cr.x = side.z * up.y - side.y * up.z;
            cr.y = side.x * up.z - up.x * side.z;
            cr.z = up.x * side.y - side.x * up.y;

            // Keep the perpendicular on the far side from the creature.
            const Vec3_s00d8_24a0* sp = self->mLoco.GetPosition();
            float ez = avatarPos->z - sp->z;
            float ey = avatarPos->y - sp->y;
            float ex = avatarPos->x - sp->x;
            float invE = InvLen((ez * ez + ey * ey) + ex * ex);
            if (((invE * ez) * cr.z + (invE * ey) * cr.y) + (invE * ex) * cr.x > 0.0f) {
                cr.x = cr.x * -1.0f;
                cr.y = cr.y * -1.0f;
                cr.z = cr.z * -1.0f;
            }

            float sideOff;
            float fwdOff;
            bool inSpace = false;
            if (isCreatureGame && !(avatar->mFlags & 0x1000)) {
                float len = sqrtf((avatarPos->x * avatarPos->x + avatarPos->y * avatarPos->y) +
                                  avatarPos->z * avatarPos->z);
                if (len > PlanetModel_s00d8_24a0()->GetRadiusAt(avatarPos)) {
                    sideOff = -aloco->GetRadius();
                    fwdOff = self->mLoco.GetRadius();
                    inSpace = true;
                }
            }
            if (!inSpace) {
                sideOff = 20.0f;
                float a = self->mLoco.GetRadius();
                fwdOff = aloco->GetRadius() + a + 1.0f;
            }

            bool hover;
            if (!avatar->mbFlying && !(avatar->mFlags & 0x1000) && self->mbFlying)
                hover = true;
            else
                hover = false;

            Vec3_s00d8_24a0 target;
            if (isCreatureGame && hover) {
                float hoverSpeed = avatar->mpTuning->mHoverSpeed;
                const Vec3_s00d8_24a0& hv = aloco->GetVelocity();
                float hdp = (hv.z * up.z + hv.x * up.x) + hv.y * up.y;
                Vec3_s00d8_24a0 lat;
                lat.x = hv.x - hdp * up.x;
                lat.y = hv.y - hdp * up.y;
                lat.z = hv.z - hdp * up.z;
                float k = FUN_00c29530(avatarPos, &aloco->GetVelocity(), hoverSpeed);
                float speed;
                if (hoverSpeed > 0.0f)
                    speed = g_PosseHoverDist;
                else
                    speed = sqrtf((lat.z * lat.z + lat.y * lat.y) + lat.x * lat.x);
                float off = Clamp_s00d8_24a0(speed * k, 2.0f, 10.0f);
                target.x = lat.x * off + avatarPos->x;
                target.y = avatarPos->y + off * lat.y;
                target.z = avatarPos->z + off * lat.z;
            } else {
                target.x = (side.x * sideOff + avatarPos->x) + cr.x * fwdOff;
                target.y = (avatarPos->y + side.y * sideOff) + cr.y * fwdOff;
                target.z = (avatarPos->z + side.z * sideOff) + cr.z * fwdOff;
            }
            Vec3_s00d8_24a0 snapped;
            Vec3_s00d8_24a0 dest = *PlanetModel_s00d8_24a0()->FUN_00b82b40(&snapped, &target, 0);

            if (hover) {
                if (avatar->mpTuning->mCanHover != 0 && self->mpTuning->mCanHover != 0) {
                    self->MoveToPointAtSpeed(mode, &dest, 1.0f, 2.0f);
                    self->Hover(true);
                    return true;
                }
                self->TryJumpToTarget(0, &dest, &g_JumpDefault, 0.0f, 0);
                return true;
            }
            self->Hover(false);
            self->MoveToPointAtSpeed(mode, &dest, 1.0f, 2.0f);
            return true;
        }
    }

    if (!mem->mbFollowing && !(dist > farDist) && (mem->mpSlot == 0 || *mem->mpSlot == self)) {
        // Settled at the slot: idle animations.
        if (!self->mLoco.IsNearGoal())
            return true;
        if (!self->mbFlying)
            return true;
        if (g_PosseIdleChance > self->m5a8.FUN_00bfc490() * 100.0f && self->AnimationFinished(0xd1dce195u)) {
            self->InterruptAnimation(0xd1dce195u, -1, 0);
            return true;
        }
        if (!self->AnimationFinished(mem->mAnimHandle))
            return true;
        switch (self->FUN_00c029b0()) {
        case 1:
            mem->mAnimHandle = self->PlayAnimation(0x2481e15, 1, -1);
            return true;
        case 2:
            mem->mAnimHandle = self->PlayAnimation(0x2481e16, 1, -1);
            return true;
        case 3:
            mem->mAnimHandle = self->PlayAnimation(0x2481e17, 1, -1);
            return true;
        }
        return true;
    }

    // (Re)join the posse: walk to the slot the posse simulator assigns, or behind the avatar.
    mem->mbFollowing = false;
    mem->mAvatarPos = *aloco->GetPosition();
    self->FUN_00c14750(!self->mLoco.SlotF8());
    mem->mTimer = 0.0f;
    mem->mAnimHandle = 0;
    int mode = 2;
    if (!(dist < g_PosseFollowDist))
        mode = 3;

    Vec3_s00d8_24a0 dest;
    mem->mpSlot = (cSPCreatureBase_s00d8_24a0**)cPosseSimulator_s00d8_24a0::Instance()->FUN_00d53b50(self, &dest);
    if (mem->mpSlot == 0) {
        float a = self->mLoco.GetRadius();
        float r = aloco->GetRadius() + a;
        r = r + r;
        Vec3_s00d8_24a0 facingBuf;
        const Vec3_s00d8_24a0* f = aloco->GetFacing(&facingBuf);
        float inv = InvLen((f->x * f->x + f->y * f->y) + f->z * f->z);
        Vec3_s00d8_24a0 target;
        target.x = avatarPos->x + r * (f->x * inv);
        target.y = avatarPos->y + (f->y * inv) * r;
        target.z = avatarPos->z + (f->z * inv) * r;
        Vec3_s00d8_24a0 snapped;
        dest = *PlanetModel_s00d8_24a0()->FUN_00b82b40(&snapped, &target, 0);
    }

    if (isCreatureGame && !(avatar->mFlags & 0x1000)) {
        float len = sqrtf((avatarPos->x * avatarPos->x + avatarPos->y * avatarPos->y) +
                          avatarPos->z * avatarPos->z);
        if (len > PlanetModel_s00d8_24a0()->GetRadiusAt(avatarPos)) {
            float dz = dest.z - avatarPos->z;
            float dy = dest.y - avatarPos->y;
            float dx = dest.x - avatarPos->x;
            float inv = InvLen((dz * dz + dy * dy) + dx * dx);
            Vec3_s00d8_24a0 n;
            n.x = inv * dx;
            n.y = dy * inv;
            n.z = dz * inv;
            float a = self->mLoco.GetRadius();
            float r = aloco->GetRadius() + a;
            dest.x = avatarPos->x + r * n.x;
            dest.y = avatarPos->y + r * n.y;
            dest.z = avatarPos->z + r * n.z;
        }
    }

    if (!avatar->mbFlying && !(avatar->mFlags & 0x1000) && aloco->GetState()->mHasPath != 0) {
        self->TryJumpToTarget(0, &dest, &g_JumpDefault, 0.0f, 0);
        return true;
    }
    self->MoveToPointAtSpeed(mode, &dest, 1.0f, 2.0f);
    return true;
}
}  // namespace SP

// @ 0x00d83a60
bool __cdecl OFFER_ITEM_Tick(Creature* c, void* a2, void* a3, void* a4, void* a5, S1* st)
{
    IdleNode* r = c->mpBehavior->PlayIdleAnimation(0, 0x40000);
    if (r != 0 && st->target != 0 && r->kind == 1) {
        switch (st->state) {
        case 0:
            if (c->FUN_00c0f570() == 0) {
                st->state = 3;
                return false;
            } else {
                unsigned f = (unsigned)-1;
                int idx = c->FUN_00c0f8f0(st->target);
                if (idx != -1)
                    f = AT(unsigned, AT(void*, c, 0xe40), idx * 0x24);
                c->PlayAnimation(0x3a8a036, 1, f);
                st->state = 1;
                return true;
            }
        case 1:
            if (c->FUN_00c0f570() == 0 || !c->FUN_00c0e0c0(0x3a8a036))
                st->state = 3;
            if (c->AnimationFinished(0x3a8a036))
                st->state = 2;
            return true;
        case 2:
            return false;
        case 3:
            return false;
        }
    }
    return false;
}

// @ 0x00d84d70
bool __cdecl EPIC_BITE_HELD_CREATURE_Activate(cSPCreatureBase_s00d8_4c50* pCreature, uint32_t, uint32_t, uint32_t, uint32_t, tEpicCtx* pCtx)
{
    uint32_t nIdx = pCreature->FUN_00c0f780();
    pCtx->mn08 = (int32_t)nIdx;

    int32_t nAnim = -1;
    if (nIdx != 0xffffffffu)
        nAnim = *(int32_t*)((char*)pCreature->mpArrayE40 + nIdx * 36);

    pCtx->mn00 = pCreature->PlayAnimation(0x4bc0476, 1, nAnim);
    pCtx->mb04 = false;
    return true;
}

// @ 0x00d84dc0
bool __cdecl FUN_00d84dc0(cSPCreatureBase_s00d8_4c50* pCreature, uint32_t, uint32_t, uint32_t, uint32_t, tEpicCtx* pCtx)
{
    bool bResult = !pCreature->IsAnimFinished((uint32_t)pCtx->mn00);

    if (pCtx->mb04)
        return bResult;

    int32_t nEvent = 0;
    if (!pCreature->WaitForAnimEventOrEnd(g_1590c3c, &nEvent, -1, 0, 1))
        return bResult;

    pCtx->mb04 = true;

    void* pObj = pCreature->FUN_00c0f8a0((uint32_t)pCtx->mn08);
    if (pObj == 0)
        return bResult;

    void* pDamage = ((void*(__thiscall*)(void*, uint32_t))(
                        (*(void***)pObj)[0xb8 / 4]))(pObj, 0x13f94d4);
    if (pDamage == 0)
        return bResult;

    void* pSim = (pCreature != 0) ? (void*)((char*)pCreature + 0x5a8) : 0;

    Vector3 vDir;
    pCreature->mLoco.v5c(&vDir);

    Vector3 vNeg;
    vNeg.x = -vDir.x;
    vNeg.y = -vDir.y;
    vNeg.z = -vDir.z;

    float fDamage = ((float(__thiscall*)(void*, int32_t, int32_t, Vector3*, void*))(
                        (*(void***)pDamage)[0x58 / 4]))(pDamage, -1, 2, &vNeg, pSim);
    ((void(__thiscall*)(void*, float))(
        (*(void***)pDamage)[0x18 / 4]))(pDamage, fDamage * g_kQuarter);

    return bResult;
}

// @ 0x00d84ec0
bool __cdecl FUN_00d84ec0(cSPCreatureBase_s00d8_4c50* pCreature)
{
    cBehaviorObj* pBehavior = (cBehaviorObj*)pCreature->mpField1698;
    if (pBehavior == 0)
        return false;

    void* pOther = pBehavior->v08();

    Vector3* pA = pCreature->mLoco.v2c();
    Vector3* pB = ((cSpatialHolder*)pOther)->v2c();

    float fDx = pB->x - pA->x;
    float fDy = pB->y - pA->y;
    float fDz = pB->z - pA->z;

    float fLen = sqrtf(fDx * fDx + fDy * fDy + fDz * fDz + g_kEps);
    float fInv = 1.0f / fLen;

    Vector3 vDir;
    vDir.x = fInv * fDx;
    vDir.y = fInv * fDy;
    vDir.z = fInv * fDz;

    pCreature->MoveToPointAndFacingAtSpeed(2, pCreature->mLoco.v2c(), &vDir, 1.0f, g_kTwo);

    int32_t nIdx = pBehavior->v10();
    pCreature->v48((void*)nIdx);

    void* pObj = ((cGameNounManager_s00d8_4c50*)NounManager())->FUN_00b25f40((uint32_t)nIdx);
    if (pObj != 0)
    {
        pCreature->ve4((void*)((char*)pObj + 0xc4));
        pCreature->FUN_00c0d950(1);
    }
    return true;
}

// @ 0x00d85000
bool __cdecl FUN_00d85000(cSPCreatureBase_s00d8_4c50* pCreature)
{
    cBehaviorObj* pBehavior = (cBehaviorObj*)pCreature->mpField1698;
    if (pBehavior == 0)
        return false;

    int32_t nIdx = pBehavior->v10();
    pCreature->v48((void*)nIdx);

    void* pObj = ((cGameNounManager_s00d8_4c50*)NounManager())->FUN_00b25f40((uint32_t)nIdx);
    if (pObj != 0)
    {
        pCreature->ve4((void*)((char*)pObj + 0xc4));
        pCreature->FUN_00c0d950(1);
    }
    return true;
}

// @ 0x00d85060
bool __cdecl FUN_00d85060(cSPCreatureBase_s00d8_4c50* pCreature)
{
    if (g_kZero < pCreature->mf169c)
    {
        void* pObj = FUN_00d998f0(pCreature->mpField1698);
        if (pObj != 0)
        {
            if (FUN_008e7f80(pObj) != 2)
                return true;
        }
    }
    return false;
}

// @ 0x00d851c0
bool __cdecl FUN_00d851c0(cSPCreatureBase_s00d8_4c50* pCreature)
{
    void* pInfo = FUN_00d51660();
    if (((char*)pInfo)[0x10] == 0)
    {
        pCreature->mpBehaviorTreeB4c->mStimuli.ClearAll(0, 0x80000000);
        return false;
    }

    cSPCreatureBase_s00d8_4c50* pAvatar = (cSPCreatureBase_s00d8_4c50*)((cGameNounManager_s00d8_4c50*)NounManager())->GetAvatar();

    Vector3* pA = pCreature->mLoco.v2c();
    Vector3* pB = pAvatar->mLoco.v2c();

    float fDx = pB->x - pA->x;
    float fDy = pB->y - pA->y;
    float fDz = pB->z - pA->z;

    float fTotal = pAvatar->mLoco.v74() + pCreature->mLoco.v74() + g_kThree;

    if (fDx * fDx + fDy * fDy + fDz * fDz > fTotal + g_kTwo)
    {
        Vector3 vOri;
        pAvatar->mLoco.v5c(&vOri);

        Vector3* pPos = pAvatar->mLoco.v2c();
        Vector3 vOut;
        vOut.x = pPos->x + vOri.x * fTotal;
        vOut.y = pPos->y + vOri.y * fTotal;
        vOut.z = pPos->z + vOri.z * fTotal;

        pCreature->MoveToPointAtSpeed(2, &vOut, g_kOne, g_kTwo);
    }
    return true;
}

// @ 0x00d85370
bool __cdecl AddLoudness(tLoudnessStim* pStim)
{
    cSPCreatureBase_s00d8_4c50* pComp = (cSPCreatureBase_s00d8_4c50*)GetComponent(pStim->mpObj3c);
    if (pComp != 0)
    {
        pComp->mf1000 = pComp->mf1000 + pStim->mf00;
        return true;
    }
    return false;
}

// @ 0x00d853b0
bool __cdecl RemoveLoudness(tLoudnessStim* pStim)
{
    cSPCreatureBase_s00d8_4c50* pComp = (cSPCreatureBase_s00d8_4c50*)GetComponent(pStim->mpObj3c);
    if (pComp != 0)
    {
        pComp->mf1000 = pComp->mf1000 - (pStim->mf0c + pStim->mf00);
        return true;
    }
    return false;
}

// @ 0x00d85400
bool __cdecl UpdateLoudness(tLoudnessStim* pStim, float fDelta)
{
    cSPCreatureBase_s00d8_4c50* pComp = (cSPCreatureBase_s00d8_4c50*)GetComponent(pStim->mpObj3c);
    if (pComp != 0)
    {
        float fCur = pStim->mf0c;
        float fTmp = pStim->mf04 * fDelta + fCur;
        float fMax = pStim->mf08;
        float* pfVal = (fMax < fTmp) ? &fMax : &fTmp;
        float fVal = *pfVal;
        pStim->mf0c = fVal;
        pComp->mf1000 = pComp->mf1000 + (fVal - fCur);
        return true;
    }
    return false;
}

// @ 0x00d85480
bool __cdecl AddHeldObject(tHeldStim* pStim)
{
    if (pStim->mpObj40 != 0)
    {
        cSPCreatureBase_s00d8_4c50* pComp = (cSPCreatureBase_s00d8_4c50*)GetComponent(pStim->mpObj40);

        pComp->mpBehaviorTreeB4c->mStimuli.FUN_00bc97f0(0, 0x4000000, g_kMax, 0);
        pComp->mpBehaviorTreeB4c->mStimuli.ClearAll(0x400000, 0);
        pComp->FUN_00c17350(0x4f26350b, 0);
        return true;
    }
    return false;
}

// @ 0x00d854f0
bool __cdecl AddAlphaFade(tHeldStim* pStim, float fDelta)
{
    cSPCreatureBase_s00d8_4c50* pComp = (cSPCreatureBase_s00d8_4c50*)GetComponent(pStim->mpObj40);
    if (pComp != 0)
    {
        pStim->mf00 = pStim->mf00 - fDelta;
        if (0.0f <= pStim->mf00 || pComp->mpBehaviorTreeB4c->mn1d8 == 0x341bd4be)
            return true;
    }
    return false;
}

// @ 0x00d856e0
bool __cdecl FUN_00d856e0(cSPCreatureBase_s00d8_4c50* pCreature)
{
    cSPCreatureBase_s00d8_4c50* pAvatar = (cSPCreatureBase_s00d8_4c50*)((cGameNounManager_s00d8_4c50*)NounManager())->GetAvatar();

    Vector3* pA = pCreature->mLoco.v2c();
    Vector3* pB = pAvatar->mLoco.v2c();

    float fDx = pB->x - pA->x;
    float fDy = pB->y - pA->y;
    float fDz = pB->z - pA->z;

    float fLen = sqrtf(fDx * fDx + fDy * fDy + fDz * fDz);
    Vector3 vDir;
    vDir.x = fDx; vDir.y = fDy; vDir.z = fDz;
    if (fLen > g_kTiny)
    {
        float fInv = g_kOne / fLen;
        vDir.x = fDx * fInv;
        vDir.y = fDy * fInv;
        vDir.z = fDz * fInv;
    }

    if (fLen > g_kThirty && !pCreature->mLoco.v48())
    {
        pCreature->v8c();
        pCreature->vc8(0);
        return true;
    }

    Vector3* pPos = pCreature->mLoco.v2c();
    Vector3 vOut;
    vOut.x = pPos->x - vDir.x * g_kTwenty;
    vOut.y = pPos->y - vDir.y * g_kTwenty;
    vOut.z = pPos->z - vDir.z * g_kTwenty;

    pCreature->MoveToPointAtSpeed(2, &vOut, g_kOne, g_kTwo);
    return true;
}

// @ 0x00d85ad0
namespace SP {
void __cdecl EatFood(Citizen* c, float amount, unsigned id, int flag)
{
    if (c == 0)
        return;
    c->SetFood(c->GetFood() + amount);
    if (((unsigned char)(c->mFlagsB58 >> 9) & 1) == 0)
        return;
    if (GetCurrentGameMode() != &gModeCreatureA) {
        cCreatureModeStrategy* strategy = FUN_00d38840();
        strategy->SignalCreatureEvent(0xd35dd8c3);
    }
    if (flag == 0)
        return;
    cFoodTarget* best = 0;
    cObj** it = c->mpSettings->mpBegin73c;
    cObj** end = c->mpSettings->mpEnd740;
    while (it != end) {
        cFoodTarget* t = (cFoodTarget*)*it;
        if (t->mType08 == 0x1b) {
            bool hasA = FUN_0064f350(t->mpProps130, 0x23705bcc, 0);
            bool hasB = FUN_0064f350(t->mpProps130, 0x3d9ae5b3, 0);
            bool ok;
            if (id == 0x333b8596)
                ok = hasA;
            else if (id == 0xd33b8593)
                ok = hasB;
            else
                ok = true;
            if (ok && (best == 0 || t->mf10c > best->mf10c))
                best = t;
        }
        ++it;
    }
    if (best != 0)
        FUN_00d2e8a0(best->mf10c);
}
}  // namespace SP

// @ 0x00d85c00
namespace SP {
bool __cdecl DEATH_Activate(Citizen* c, void*, void*, void*, void*, StateDeath* st)
{
    st->mb16 = c->mbB5e;
    st->mb17 = 0;
    c->vf8c();
    c->mfB7c = kOne;
    c->mpB54->mf80 = kOne;
    void* mode = GetCurrentGameMode();
    if (GetCurrentGameMode() == &gModeCreatureC) {
        void* tribe = ((cGameNounManager_s00d8_5ad0*)NounManager())->GetPlayerTribe();
        if (tribe == 0)
            st->mf0 = kFifteen;
        else if (FUN_00c8e870(tribe) && c->vf4c() == -1)
            st->mf0 = FUN_004e1c70(gPropertyList, 0x7c399e92, kSixty);
        else
            st->mf0 = FUN_004e1c70(gPropertyList, 0xdef7dd75, kPropDefault);
    } else if (mode == &gModeCreatureB) {
        st->mf0 = kSixty;
    } else if (mode == &gModeCreatureA) {
        char* data = (char*)c->GetGameData();
        if (data != 0 && data[2] != 0) {
            st->mf0 = kFloatMax;
            st->mb17 = 1;
        } else {
            st->mf0 = kFifteen;
        }
    } else {
        st->mf0 = kFifteen;
    }
    st->mf4 = kThree;
    st->mf8 = kThree;
    st->mfc = kOne;
    st->mb14 = 0;
    st->mb15 = 0;
    cAnimNode* node = (cAnimNode*)c->mpBehavior->mHead.Play(0x400, 0);
    int kind = 2;
    if (node != 0)
        kind = node->mKind;
    if (kind == 5)
        st->mEffect10 = 0x54ac179;
    else if (kind == 0x11)
        st->mEffect10 = 0x60db981;
    else if (kind == 0x12)
        st->mEffect10 = 0x779e183;
    else
        st->mEffect10 = 0xf14faa46;
    if (st->mb16 == 0 && st->mb17 == 0) {
        if ((unsigned char)(c->mFlagsB58 >> 9) & 1)
            c->GetFood();
        if (c->mLoco.FUN_00c887c0() > kFifty)
            st->mEffect10 = 0x92aa59ce;
        if (c->Flag388()) {
            char* data = (char*)c->GetPlayer();
            int n = *(int*)(data + 0xf4) - 1;
            float f = (float)n;
            if (f < 0.0f)
                f = 0.0f;
            *(int*)(data + 0xf4) = (int)f;
        }
    } else {
        st->mEffect10 = 0x5807346 - (c->Flag388() ? 1 : 0);
    }
    return true;
}
}  // namespace SP

// @ 0x00d85e40
namespace SP {
bool __cdecl FUN_00d85e40(Citizen* c)
{
    cObj* fx = (cObj*)c->SpecQuery(0xf6ceaad6);
    if (fx != 0) {
        EffectSpecSmall spec;
        spec.m00 = 0;
        spec.m02 = 0;
        spec.mf04 = kSpec04;
        spec.mf08 = kSpec08;
        spec.mf0c = kSpec0c;
        spec.mf10 = kOne;
        ((cMatrix3*)&spec.mMat)->Assign(&gSpecMatrix);
        fx->vf20(&spec);
        spec.mf10 = c->mLoco.GetRadius() * kRadiusScale;
        spec.m02++;
        fx->vf18(&spec);
        fx->vf08(0);
    }
    c->InterruptAnimation(0x65d31ac, -1, 0);
    c->mFlagsB58 |= 4;
    return true;
}
}  // namespace SP

// @ 0x00d85f20
namespace SP {
bool __cdecl EVOLVE_Activate(Citizen* c, void*, void*, void*, void*, StateEvolve* st)
{
    if (st != 0)
        st->m20 = 0;
    bool instant = (c->mB58.mbB5a & 1) != 0;
    st->m8 = 0x37048f6;
    cCreatureModeStrategy* strategy = FUN_00d38840();
    Variant* info = 0;
    float speed;
    if (strategy->mpB4 != 0 && ((cB4Obj*)strategy->mpB4)->Query(0xc4f054b6, (void**)&info)) {
        if (info->mType12 == 0xd || info->mType12 == 0x10) {
            if ((info->mFlags10 & 0x30) != 0)
                speed = *(float*)info->m0;
            else
                speed = *(float*)&info->m0;
        } else {
            speed = kEvolveSpeed;
        }
    } else {
        speed = kSixty;
    }
    st->mf0c = speed;
    st->mf10 = 0;
    st->mPos = *c->mLoco.GetPosition();
    st->m4 = 0;
    if (instant) {
        st->m0 = 2;
        c->mb131 = 1;
        c->mb12f = 0;
        Citizen* avatar = (Citizen*)((cGameNounManager_s00d8_5ad0*)NounManager())->GetAvatar();
        if (avatar != 0 && avatar->GetTargetAsCreature() == c)
            avatar->vf84(0, 0, 0);
    } else {
        float near = kFive;
        float range = kTen;
        st->m0 = 0;
        cPlayerData* player = (cPlayerData*)c->GetPlayer();
        if (player->mpNear160 != 0) {
            near = player->mpNear160->mBundle.GetRadius();
            range = c->mLoco.GetRadius() * kTwo + player->mpNear160->mBundle.GetRadius();
        }
        Vec3_s00d8_5ad0 out;
        Vec3_s00d8_5ad0* r = ((cPlanetModel_s00d8_5ad0*)PlanetModel_s00d8_5ad0())->MakeRandomWorldPosition(
                      &out, player->GetPosition(), near, range);
        st->mPos = *r;
        c->MoveToPointAtSpeed(2, &st->mPos, kOne, kTwo);
    }
    c->FUN_00c14750(0);
    c->mFlagsB58 |= 4;
    return true;
}
}  // namespace SP

// @ 0x00d86130
void __cdecl FUN_00d86130(Citizen* c, void*, void*, void*, void*, StateSit* st)
{
    Vec3_s00d8_5ad0* food = (Vec3_s00d8_5ad0*)c->GetFoodPos();
    if (*(int*)&c->mVec1004.x == *(int*)&food->x &&
        *(int*)&c->mVec1004.y == *(int*)&food->y &&
        *(int*)&c->mVec1004.z == *(int*)&food->z) {
        *(int*)&c->mVec1004.x = 0;
        if (st->mf10 != kZero) {
            c->mLoco.vf40(st->mf10);
            c->FUN_00c0bbe0();
        }
    } else {
        c->mLoco.vf40(c->vf80(0));
        c->FUN_00c0bbe0();
    }
    ((cGlobalMgr*)FUN_00b3d310())->FUN_00b453a0(&c->mLoco);
    c->mb131 = 0;
    c->mb12f = 1;
    c->FUN_00c14750(0);
    c->mFlagsB58 &= 0xfffefffb;
    if (st->mp20 != 0) {
        if (!st->mp20->IsFinished())
            ((cGameNounManager_s00d8_5ad0*)NounManager())->RemoveNoun(st->mp20);
    }
    if (st->mp20 != 0)
        st->mp20->Release();
}

// @ 0x00d86240
bool __cdecl FUN_00d86240(Citizen* c, void*, void*, void*, void*, void*, void*, StateSitHead* st)
{
    cAnimNode* node = (cAnimNode*)c->mpBehavior->mHead.Play(0x1000, 0);
    if (node == 0)
        return false;
    st->mb10 = FUN_00d998d0_s00d8_5ad0(node, 0x3a25119) != 0;
    st->m0c = 0;
    st->mb08 = node->mKind == 1;
    st->mb12 = 0;
    st->mb11 = node->mKind == 2;
    if (st->mb08) {
        st->m0 = node->mAnim14;
        st->m4 = node->mAnim18;
        c->InterruptAnimation(st->m0, -1, 0);
        c->PlayAnimation(st->m4, 1, -1);
    } else if (st->mb11) {
        st->m0c = c->InterruptAnimation(0x63bfcaa, -1, 0);
    } else if (st->mb10) {
        st->m0c = c->InterruptAnimation(0x61c2bfe, -1, 0);
    } else if (c->mb137 == 0 && (c->mFlags110 & 0x1000) == 0) {
        st->mb12 = 1;
    } else {
        st->m0c = c->InterruptAnimation(0x2481e14, -1, 0);
    }
    c->SetStealthed(0, 0);
    EffectSpec spec;
    spec.mf14 = kEffect14;
    spec.mf18 = kEffect18;
    spec.mf1c = kEffect1c;
    spec.mf20 = kOne;
    *(volatile float*)&spec.mf60 = kTwo;
    spec.mf64 = kPointNine;
    spec.mpData = 0;
    spec.mpEnd = 0;
    spec.mpCap = 0;
    spec.m28 = 0;
    spec.mb50 = 0;
    spec.mf54 = 0;
    spec.mf58 = 0;
    spec.mf5c = 0;
    spec.mf60 = 0;
    spec.mf6c = kFloatMax;
    spec.mf70 = 0;
    spec.m74 = 0;
    c->mLoco.PlayEffectSpec(&spec);
    if (spec.mpData != 0 && *(int*)((char*)spec.mpData - 4) != 0)
        FUN_00f47380(spec.mpData);
    return true;
}

// @ 0x00d86410
bool __cdecl FUN_00d86410(Citizen* c, void*, void*, void*, void*, StateItemOnHead* st)
{
    if (st != 0) {
        st->mp0c = 0;
        st->mp10 = 0;
    }
    st->m0 = 0;
    st->m4 = -1;
    st->m8 = -1;
    st->mb14 = 0;
    cAnimNode* node = (cAnimNode*)c->mpBehavior->mHead.Play(0, 0x40000);
    if (node == 0 || node->mKind != 4)
        return false;
    if (!c->FUN_00c0f4f0()) {
        c->mpBehavior->mHead.ClearAll(0, 0x40000);
        return false;
    }
    ((RefHolder*)&st->mp0c)->Assign(FUN_00d998d0_s00d8_5ad0(node, 0x1186577));
    ((AutoRef*)&st->mp10)->operator=(FUN_00d998d0_s00d8_5ad0(node, 0x2c9cc8e));
    if (st->mp0c != 0 && c->FUN_00c0f8f0(st->mp0c) != -1)
        return false;
    if (c->FUN_00c0f5f0()) {
        c->FUN_00c15bd0(0, 0, 0);
        if (c->FUN_00c0f5f0())
            return false;
    }
    if (c->mpSettings->mf590 == 0.0f)
        st->mb14 = 1;
    if (st->mp0c != 0) {
        if (!c->FUN_00c13c60(st->mp0c, 0, 0))
            return false;
        cInteractableObject_s00d8_5ad0* obj = (cInteractableObject_s00d8_5ad0*)FUN_00d7cf70(&st->mp0c);
        if (obj != 0 && obj->mState16c != 2)
            return false;
        cInteractableObject_s00d8_5ad0* p = (cInteractableObject_s00d8_5ad0*)FUN_00d7cf90(&st->mp0c);
        if (p != 0) {
            if (p->mp108 != 0 && p->mp108 != (cObj*)c && ((unsigned char)(c->mFlagsB58 >> 9) & 1) == 0)
                return false;
            ((AutoRef*)&p->mp108)->operator=((cObj*)c);
        }
    } else {
        if (st->mp10 != 0 && ((cInteractableObject_s00d8_5ad0*)st->mp10)->mState16c != 0)
            return false;
    }
    if (!c->mLoco.vfF8())
        c->FUN_00c14750(1);
    c->vf84(0, 0, 0);
    return true;
}

// @ 0x00d865c0
void __cdecl FUN_00d865c0(Citizen* c, void*, void*, void*, void*, StateItemOnHead* st)
{
    c->mpBehavior->mHead.ClearAll(0, 0x40000);
    if (st->mp0c != 0) {
        if (st->m0 == 2 || st->m0 == 0) {
            if (st->mp0c != 0) {
                cOrnament_s00d8_5ad0* o = (cOrnament_s00d8_5ad0*)st->mp0c->Query(0x398420d);
                if (o != 0) {
                    if (o->mp108 == (cObj*)c) {
                        if (cObj* old = o->mp108) {
                            o->mp108 = 0;
                            old->Release();
                        }
                    }
                }
            }
        }
    }
    cObj* p = st->mp0c;
    if (p != 0) {
        st->mp0c = 0;
        p->ReleaseBundle();
    }
    p = st->mp10;
    if (p != 0) {
        st->mp10 = 0;
        p->Release();
    }
    c->FUN_00c14750(0);
    if (st->mp10 != 0)
        st->mp10->Release();
    if (st->mp0c != 0)
        st->mp0c->ReleaseBundle();
}

// @ 0x00d86690
bool __cdecl FUN_00d86690(Citizen* c, void*, void*, void*, void*, StateReceive* st)
{
    if (st != 0)
        st->mp0 = 0;
    cAnimNode* node = (cAnimNode*)c->mpBehavior->mHead.Play(0, 0x40000);
    cObj* p = FUN_00d998d0_s00d8_5ad0(node, 0x1186577);
    cObj* old = st->mp0;
    if (p != old) {
        if (p != 0)
            p->AddRefBundle();
        st->mp0 = p;
        if (old != 0)
            old->ReleaseBundle();
    }
    st->m4 = node->m10;
    Vec3_s00d8_5ad0 pos = *st->mp0->GetPosition();
    float r = st->mp0->GetRadius();
    const Vec3_s00d8_5ad0* cp = c->mLoco.GetPosition();
    float dx = pos.x - cp->x;
    float dy = pos.y - cp->y;
    float dz = pos.z - cp->z;
    float inv = 1.0f / sqrtf(dx * dx + dy * dy + dz * dz);
    Vec3_s00d8_5ad0 dir;
    dir.x = dx * inv;
    dir.y = dy * inv;
    dir.z = dz * inv;
    c->MoveToPointAndFacingAtSpeed(2, &pos, &dir, r, r + kFive);
    return true;
}

// @ 0x00d86810
namespace SP {
void __cdecl REACT_TO_AVATAR_Deactivate(Citizen* c, void*, void*, void*, void*, StateReact* st)
{
    c->mpBehavior->mHead.ClearAll(0, 0x40000);
    if (st != 0 && st->mp0 != 0)
        st->mp0->ReleaseBundle();
}
}  // namespace SP

// @ 0x00d86850
bool __cdecl FUN_00d86850(Citizen* c, void*, void*, void*, void*, StateReceive* st)
{
    if (st != 0)
        st->mp8 = 0;
    st->mp0 = 0;
    st->m4 = -1;
    st->m0c = 0;
    cAnimNode* node = (cAnimNode*)c->mpBehavior->mHead.Play(0, 0x40000);
    if (node == 0 || node->mKind != 5)
        return false;
    ((RefHolder*)&st->mp8)->Assign(FUN_00d998d0_s00d8_5ad0(node, 0x1186577));
    if (st->mp8 == 0)
        return false;
    c->FUN_00c19940(0);
    if (st->mp8 == 0)
        return false;
    cInteractableObject_s00d8_5ad0* obj = (cInteractableObject_s00d8_5ad0*)st->mp8->Query(0x398420d);
    if (obj == 0)
        return false;
    if (obj->mp108 != 0 && obj->mp108 != (cObj*)c && ((unsigned char)(c->mFlagsB58 >> 9) & 1) == 0)
        return false;
    cLoco* loco = &c->mLoco;
    FUN_00b57bf0(loco, (char*)obj + 0x34, kFloatMax);
    ((AutoRef*)&obj->mp108)->operator=((cObj*)c);
    return true;
}

// @ 0x00d86940
void __cdecl FUN_00d86940(Citizen* c, void*, void*, void*, void*, StateDig* st)
{
    c->mpBehavior->mHead.ClearAll(0, 0x40000);
    if (st->m0 == 2) {
        FUN_00b530e0(st->mp8, 0);
        st->mp8->mb70 = 0;
        if (st->mp8 != 0) {
            cInteractiveOrnament* o = (cInteractiveOrnament*)st->mp8->Query(0x3a25119);
            if (o != 0)
                o->SetLifetime(kHalf, 1);
        }
    } else {
        FUN_00b54300(&c->mLoco, st->mp8);
    }
    c->FUN_00c14750(0);
    if (st->mp8 != 0) {
        cInteractableObject_s00d8_5ad0* o = (cInteractableObject_s00d8_5ad0*)st->mp8->Query(0x398420d);
        if (o != 0) {
            if (o->mp108 == (cObj*)c) {
                if (cObj* old = o->mp108) {
                    o->mp108 = 0;
                    old->Release();
                }
            }
        }
    }
    cInteractableObject_s00d8_5ad0* p = st->mp8;
    if (p != 0) {
        st->mp8 = 0;
        p->ReleaseBundle();
    }
    if (st->mp8 != 0)
        st->mp8->ReleaseBundle();
}

// @ 0x00d86a30
u8 FUN_00d86a30(cCreature* creature, u32 a2, u32 a3, void** a4, void** a5, cNodeState* state)
{
    if (state->m8.p == 0)
        return 0;

    cAnimObj* ornament = (cAnimObj*)((void* (__thiscall*)(void*, u32))VT(state->m8.p)[0xb8 / 4])(state->m8.p, 0x3a25119);
    if (ornament == 0)
        return 0;

    cCreature* old = (cCreature*)ornament->m108;
    if (old != 0 && old != creature && ((creature->mB58 >> 9) & 1) == 0)
        return 0;

    if (creature != old) {
        if (creature)
            ((void (__thiscall*)(void*))VT(creature)[0 / 4])(creature);
        ornament->m108 = creature;
        if (old)
            ((void (__thiscall*)(void*))VT(old)[4 / 4])(old);
    }

    void* obj = *a5;
    f32 f44 = g169f044;
    f32 f40 = g169f03c;
    f32 f3c = g169f040;
    f32 f38 = g169f044;
    if (obj == 0)
        return 0;

    f32 f4 = ((f32 (__thiscall*)(void*))VT(obj)[0x74 / 4])(obj);
    f32* pf = (f32*)((void* (__thiscall*)(void*, void*))VT(obj)[0x6c / 4])(obj, &f4);
    f44 = (pf[0] + pf[3]) * kHalf_s00d8_6a30;
    f40 = (pf[4] + pf[1]) * kHalf_s00d8_6a30;
    f3c = (pf[5] + pf[2]) * kHalf_s00d8_6a30;
    f38 = f44;
    f32 f34 = f40;
    f32 f30 = f3c;

    f32* pf2 = (f32*)((void* (__thiscall*)(void*))VT(obj)[0x2c / 4])(obj);
    f32 f11 = pf2[0];
    f32 f2 = pf2[1];
    f32 f3 = pf2[2];

    u32 st = state->m0;
    if (st == 0) {
        cCreatureSub* cs = &creature->mC0;
        f32 f9 = ((f32 (__thiscall*)(void*))VT(cs)[0x74 / 4])(cs);
        f4 = f9 + f4 + kTenth;
        f32* pf3 = (f32*)((void* (__thiscall*)(void*))VT(cs)[0x2c / 4])(cs);
        f32 f13 = f4 + kOne_s00d8_6a30;
        f38 = f11 - pf3[0];
        f34 = f2 - pf3[1];
        f30 = f3 - pf3[2];
        u32 n = FUN_00436ce0(&f44, &f38, f4, f13);
        MOPS(creature)->FUN_00c1c5c0(2, &f44, n);
        if (MOPS(cs)->FUN_00c42e20()) {
            if (*a4)
                *(u8*)((u8*)*a4 + 0x71) = 1;
            state->m4.u = 0x3df6dff;
            state->mC.u = MOPS(creature)->FUN_00c14990(0x3df6dff, &f44, -1);
            FUN_00d85540(creature);
            state->m0 = 1;
        }
    }
    else if (st == 1) {
        if (!MOPS(creature)->FUN_00c14ef0((u32)(size_t)g1590c40, &f4, state->m4.u, 0, 1) &&
            !MOPS(creature)->FUN_00c12400(state->mC.u))
            return 1;
        MOPS(ornament)->FUN_00c40200();
        ornament->mA3 = 0;
        state->m0 = 2;
        u32 u = (u32)(size_t)FUN_00ad2670(a4);
        (void)u;
        void* inst = FUN_00d38840_s00d8_6a30();
        MOPS(inst)->FUN_00d39360(0xd3353638, &f44);
    }
    else if (st == 2) {
        return 0;
    }
    return 1;
}

// @ 0x00d86d30
u8 FUN_00d86d30(cCreature* creature, u32 a2, u32 a3, u32 a4, u32 a5, cNodeState* state)
{
    if (state)
        state->m8.p = 0;
    state->m0 = 0;
    void* p = state->m8.p;
    if (p) {
        state->m8.p = 0;
        ((void (__thiscall*)(void*))VT(p)[0xc0 / 4])(p);
    }
    state->m4.b = 0;
    state->mC.b = 0;
    state->m10.u = 0xffffffff;
    u32 idx = MOPS(creature)->FUN_00c0f780();
    if (idx == 0xffffffff)
        return 0;
    cCreatureEntry* e = &creature->mE40[idx];
    state->m10.u = e->mId;
    void* obj = e->mObj20;
    if (obj == 0)
        return 0;
    void* prev = state->m8.p;
    if (obj != prev) {
        ((void (__thiscall*)(void*))VT(obj)[0xbc / 4])(obj);
        state->m8.p = obj;
        if (prev)
            ((void (__thiscall*)(void*))VT(prev)[0xc0 / 4])(prev);
    }
    f32 f = creature->mB20->m590;
    if (f == kZero_s00d8_6a30)
        state->mC.b = 1;
    return 1;
}

// @ 0x00d86df0
void FUN_00d86df0(cCreature* creature, u32 a2, u32 a3, u32 a4, u32 a5, cNodeState* state)
{
    void* p = state->m8.p;
    if (p) {
        state->m8.p = 0;
        ((void (__thiscall*)(void*))VT(p)[0xc0 / 4])(p);
    }
    MOPS(&creature->mB4C->mStimuli)->FUN_00bc98f0(0, 0x40000);
    MOPS(creature)->FUN_00c14750(0);
    if (state && state->m8.p) {
        void* q = state->m8.p;
        return ((void (__thiscall*)(void*))VT(q)[0xc0 / 4])(q);
    }
}

// @ 0x00d86e50
u8 FUN_00d86e50(cCreature* creature, u32 a2, u32 a3, u32 a4, u32 a5, cNodeState* state)
{
    if (state) {
        state->m4.u = 0;
        state->mC.u = 0;
    }
    cAnimObj* anim = (cAnimObj*)MOPS(&creature->mB4C->mStimuli)->FUN_00bc96a0(0x20, 0);
    if (anim == 0)
        return 0;
    state->m10.b = 0;
    state->m0 = anim->m0C;
    if (anim->m2C) {
        void* obj = ((void* (__thiscall*)(void*, u32))VT(anim->m2C)[0xc / 4])(anim->m2C, 0x2c9cc8e);
        if (obj) {
            void* prev = state->mC.p;
            if (obj != prev) {
                ((void (__thiscall*)(void*))VT(obj)[0 / 4])(obj);
                state->mC.p = obj;
                if (prev)
                    ((void (__thiscall*)(void*))VT(prev)[4 / 4])(prev);
            }
            ((void (__thiscall*)(void*, u32, u32, u32))VT(creature)[0x84 / 4])(creature, 0, 0, 0);
            return 1;
        }
    }
    if (anim->m2C) {
        void* obj = ((void* (__thiscall*)(void*, u32))VT(anim->m2C)[0xc / 4])(anim->m2C, 0x581147f);
        if (obj) {
            MOPS(&state->m4.p)->FUN_00b5f950(obj);
            state->m8.u = anim->m10;
            ((void (__thiscall*)(void*, u32, u32, u32))VT(creature)[0x84 / 4])(creature, 0, 0, 0);
            return 1;
        }
    }
    if ((creature->mB58 >> 9) & 1) {
        cAnimObj* v = (cAnimObj*)((void* (__thiscall*)(void*, u32))VT(creature)[0xb4 / 4])(creature, state->m0);
        if (v) {
            u32 r = 0;
            if (v->m0C == 1)
                r = 1;
            else if (v->m0C == 0)
                r = 2;
            u32 arg = MOPS(creature)->FUN_00c0ee60(1, r);
            ((void (__thiscall*)(void*, u32))VT(creature)[0x84 / 4])(creature, arg);
        }
    }
    return 1;
}

// @ 0x00d86f90
void FUN_00d86f90(cCreature* creature, u32 a2, u32 a3, u32 a4, u32 a5, cNodeState* state)
{
    struct Local {
        u32 m0;
        u32 m4;
        u32 m8;
        f32 mC;
        f32 m10;
        f32 m14;
        f32 m18;
        f32 m1C;
        f32 m20;
        u32 m24;
        u32 m28;
        u8 pad2C[0x20];
        u8 m4C;
        u8 pad4D[3];
        f32 m50;
        f32 m54;
        f32 m58;
        u32 m5C;
        f32 m60;
        f32 m64;
        f32 m68;
        f32 m6C;
        u32 m70;
    } local;
    local.m0 = 0;
    local.m4 = 0;
    local.m8 = 0;
    local.m10 = g169f03c;
    local.m18 = g169f040;
    local.m1C = g169f044;
    local.m20 = kOne_s00d8_6a30;
    local.m24 = 0;
    local.m4C = 0;
    local.m50 = 0.0f;
    local.m54 = 0.0f;
    local.m58 = 0.0f;
    local.m5C = 0;
    local.m60 = kTwo_s00d8_6a30;
    local.m64 = g13ec4b4;
    local.m68 = g147c030;
    local.m6C = 0.0f;
    local.m70 = 0;
    ((void (__thiscall*)(void*, void*))VT(&creature->mC0)[0xdc / 4])(&creature->mC0, &local);
    void* p = *(void**)((u8*)&local + 0);
    if (p) {
        if (((u32*)p)[-1] != 0)
            FUN_00f47380(p);
    }
    MOPS(&creature->mB4C->mStimuli)->FUN_00bc98f0(0x20, 0);
    if (state) {
        if (state->mC.p)
            ((void (__thiscall*)(void*))VT(state->mC.p)[4 / 4])(state->mC.p);
        if (state->m4.p) {
            void* q = state->m4.p;
            return ((void (__thiscall*)(void*))VT(q)[4 / 4])(q);
        }
    }
}

// @ 0x00d870b0
u8 FUN_00d870b0(cCreature* creature, u32 a2, u32 a3, u32 a4, u32 a5, cNodeState* state)
{
    if (state) {
        state->m4.u = 0;
        state->m10.u = 0;
        state->m14.u = 0;
        state->m18.u = 0;
    }
    state->m0 = 0;
    void* p = state->m4.p;
    if (p) {
        state->m4.p = 0;
        ((void (__thiscall*)(void*))VT(p)[4 / 4])(p);
    }
    state->m8.u = 0;
    state->mC.u = 0x53ecd29;
    state->m1C.b = 0;
    cAnimObj* anim = (cAnimObj*)MOPS(&creature->mB4C->mStimuli)->FUN_00bc96a0(0x200000, 0);
    if (anim == 0)
        return 0;
    cAnimObj* obj = (cAnimObj*)FUN_00d998d0(anim, 0x1b92b27);
    if (obj == 0)
        return 0;
    if (obj->mA9 == 0)
        return 0;
    if (((u8 (__thiscall*)(void*))VT(obj)[0x2c / 4])(obj))
        return 0;
    if (MOPS(creature)->FUN_00c04590() == 0)
        return 0;
    cHolder_s00d8_6a30* h = (cHolder_s00d8_6a30*)MOPS(creature)->FUN_00c04590();
    if (h->m160 == 0)
        return 0;
    MOPS(&state->m4.p)->FUN_00b5f950(obj);
    cHolder_s00d8_6a30* h2 = (cHolder_s00d8_6a30*)MOPS(creature)->FUN_00c04590();
    cAnimObj* o = h2->m160;
    f32* pos = (f32*)((void* (__thiscall*)(void*))VT(&o->m34)[0x98 / 4])(&o->m34);
    state->m10.f = pos[0];
    state->m14.f = pos[1];
    state->m18.f = pos[2];
    return 1;
}

// @ 0x00d871a0
void FUN_00d871a0(cCreature* creature, u32 a2, u32 a3, u32 a4, u32 a5, cNodeState* state)
{
    void* p = state->m4.p;
    if (p) {
        state->m4.p = 0;
        ((void (__thiscall*)(void*))VT(p)[4 / 4])(p);
    }
    MOPS(&creature->mB4C->mStimuli)->FUN_00bc98f0(0x200000, 0);
    void* ms = FUN_0067dcc0();
    ((void (__thiscall*)(void*, u32, u32, u32))VT(ms)[0x14 / 4])(ms, 0x445f729, 0, 0);
    if (state && state->m4.p) {
        void* q = state->m4.p;
        return ((void (__thiscall*)(void*))VT(q)[4 / 4])(q);
    }
}

// @ 0x00d87200
u8 FUN_00d87200(cCreature* creature, u32 a2, u32 a3, u32 a4, u32 a5, cNodeState* state)
{
    if (state)
        state->m4.u = 0;
    state->m0 = 0;
    void* p = state->m4.p;
    if (p) {
        state->m4.p = 0;
        ((void (__thiscall*)(void*))VT(p)[4 / 4])(p);
    }
    state->m8.u = 0;
    state->mC.u = 0x53ecd2a;
    cAnimObj* anim = (cAnimObj*)MOPS(&creature->mB4C->mStimuli)->FUN_00bc96a0(0x200000, 0);
    if (anim == 0)
        return 0;
    cAnimObj* obj = (cAnimObj*)FUN_00d998d0(anim, 0x1b92b27);
    if (obj == 0)
        return 0;
    if (obj->mA9 == 0)
        return 0;
    if (((u8 (__thiscall*)(void*))VT(obj)[0x2c / 4])(obj))
        return 0;
    MOPS(&state->m4.p)->FUN_00b5f950(obj);
    cAnimObj* o = (cAnimObj*)state->m4.p;
    f32 f = ((f32 (__thiscall*)(void*))VT(&o->m34)[0x74 / 4])(&o->m34);
    state->m10.f = FUN_00572a10(f + f, kFour * f);
    return 1;
}

// @ 0x00d872d0
void FUN_00d872d0(cCreature* creature, u32 a2, u32 a3, u32 a4, u32 a5, cNodeState* state)
{
    void* p = state->m4.p;
    if (p) {
        state->m4.p = 0;
        ((void (__thiscall*)(void*))VT(p)[4 / 4])(p);
    }
    MOPS(&creature->mB4C->mStimuli)->FUN_00bc98f0(0x200000, 0);
    if (state && state->m4.p) {
        void* q = state->m4.p;
        return ((void (__thiscall*)(void*))VT(q)[4 / 4])(q);
    }
}

// @ 0x00d87320
u8 FUN_00d87320(cCreature* creature, u32 a2, u32 a3, u32 a4, u32 a5, cNodeState* state)
{
    if (state) {
        state->m8.p = 0;
        state->m1C.p = 0;
        state->m28.p = 0;
    }
    state->m4.u = 0x10;
    void* p = state->m8.p;
    if (p) {
        state->m8.p = 0;
        ((void (__thiscall*)(void*))VT(p)[4 / 4])(p);
    }
    state->m10.u = 0xffffffff;
    state->m18.bytes.b18 = 0;
    state->m18.bytes.b19 = 0;
    state->m14.u = 0;
    state->m20 = 0xffffffff;
    state->m2C = 0;
    state->m30 = 0xffffffff;
    cAnimObj* anim = (cAnimObj*)MOPS(&creature->mB4C->mStimuli)->FUN_00bc96a0(1, 0);
    if (anim) {
        cAnimObj* o1 = (cAnimObj*)FUN_00d998d0(anim, 0x2c9cc8e);
        void* prev = state->m8.p;
        if (o1 != prev) {
            if (o1)
                ((void (__thiscall*)(void*))VT(o1)[0 / 4])(o1);
            state->m8.p = o1;
            if (prev)
                ((void (__thiscall*)(void*))VT(prev)[4 / 4])(prev);
        }
        if (state->m8.p == 0) {
            cAnimObj* o2 = (cAnimObj*)FUN_00d998d0(anim, 0x581147f);
            void* prev2 = state->m1C.p;
            if (o2 != prev2) {
                if (o2)
                    ((void (__thiscall*)(void*))VT(o2)[0 / 4])(o2);
                state->m1C.p = o2;
                if (prev2)
                    ((void (__thiscall*)(void*))VT(prev2)[4 / 4])(prev2);
            }
            state->m20 = anim->m0C;
        }
    }
    void** slot;
    if (state->m8.p)
        slot = (void**)((u8*)state->m8.p + 0x108);
    else if (state->m1C.p)
        slot = (void**)((u8*)state->m1C.p + 0x68);
    else
        return 0;
    if (!(((creature->mB58 >> 9) & 1) || *slot == 0 || *slot == creature))
        return 0;
    void* old = *slot;
    if (creature != old) {
        ((void (__thiscall*)(void*))VT(creature)[0 / 4])(creature);
        *slot = creature;
        if (old)
            ((void (__thiscall*)(void*))VT(old)[4 / 4])(old);
    }
    state->m0 = 0;
    creature->mB5C = 0;
    if (MOPS(creature)->FUN_00c0f4f0() == 0)
        return 0;
    if (MOPS(creature)->FUN_00c0f4f0() > 0) {
        if (MOPS(creature)->FUN_00c0f5f0()) {
            MOPS(creature)->FUN_00c15bd0(0, 0, 0);
            if (MOPS(creature)->FUN_00c0f5f0())
                return 0;
        }
    }
    if (state->m8.p && ((creature->mB58 >> 9) & 1)) {
        state->m24 = 0;
        return 1;
    }
    state->m24 = 1;
    return 1;
}

// @ 0x00d874e0
void FUN_00d874e0(cCreature* creature, u32 a2, u32 a3, u32 a4, u32 a5, cNodeState* state)
{
    cAnimObj* anim = (cAnimObj*)MOPS(&creature->mB4C->mStimuli)->FUN_00bc96a0(1, 0);
    cAnimObj* obj = anim ? (cAnimObj*)FUN_00d998d0(anim, 0x2c9cc8e) : 0;
    if (state->m1C.p != 0 || obj == 0 || obj == (cAnimObj*)state->m8.p)
        MOPS(&creature->mB4C->mStimuli)->FUN_00bc98f0(1, 0);

    if (state->m18.bytes.b18) {
        if (state->m8.p) {
            cAnimObj* o = (cAnimObj*)state->m8.p;
            MOPS(creature)->FUN_00c15d50(&o->m34, 0, 0);
            if (o->m148 & 1) {
                void* nm = FUN_00b3d300(o);
                MOPS(nm)->FUN_00b225d0(o);
            }
        }
        state->m18.bytes.b18 = 0;
    }

    void** slot;
    if (state->m8.p)
        slot = (void**)((u8*)state->m8.p + 0x108);
    else if (state->m1C.p)
        slot = (void**)((u8*)state->m1C.p + 0x68);
    else
        goto after_slot;
    if (*slot == creature && *slot != 0) {
        void* old = *slot;
        *slot = 0;
        ((void (__thiscall*)(void*))VT(old)[4 / 4])(old);
    }

after_slot:
    if (state->m0 != 5 && state->m8.p && ((cAnimObj*)state->m8.p)->m16C == 3)
        FUN_00d7d2c0(&((cAnimObj*)state->m8.p)->m34, creature);

    void* p = state->m8.p;
    if (p) {
        state->m8.p = 0;
        ((void (__thiscall*)(void*))VT(p)[4 / 4])(p);
    }
    void* q = state->m28.p;
    if (q) {
        state->m28.p = 0;
        ((void (__thiscall*)(void*))VT(q)[4 / 4])(q);
    }
    if (state->m28.p)
        ((void (__thiscall*)(void*))VT(state->m28.p)[4 / 4])(state->m28.p);
    if (state->m1C.p)
        ((void (__thiscall*)(void*))VT(state->m1C.p)[4 / 4])(state->m1C.p);
    if (state->m8.p) {
        void* r = state->m8.p;
        return ((void (__thiscall*)(void*))VT(r)[4 / 4])(r);
    }
}

// @ 0x00d87620
int __cdecl EAT_FRUIT_Tick(Creature_s00d8_7620* pCreature, u32 a2, u32 a3, u32 flags, u32 a5, EatFruitNode* pNode)
{
  (void)a2; (void)a3; (void)a5;

  AutoRef_s00d8_7620* pRef;        // local_118: address of an AutoRefCount member
  RefCnt*  pOld;        // local_110: previous pointer of that member
  u32      anim;        // Play() result / animation handle
  Vec3_s00d8_7620     vA, vB, vC;  // scratch vector slots on the stack
  float    fDist;       // local_118 reinterpreted as float
  float    fExtra;      // local_110 reinterpreted as float
  float    fSpeed;

  ActorSub* pActor = (ActorSub*)pNode->mpActor;

  if (pNode->mpActor == 0) {
    if (pNode->mpInteract == 0)
      return 0;
    pRef = (AutoRef_s00d8_7620*)((u8*)pNode->mpInteract + 0x68);
  } else {
    if (pActor->mState_16c == 6)
      return 0;
    pRef = (AutoRef_s00d8_7620*)((u8*)pNode->mpActor + 0x108);
  }

  if (((pCreature->mFlags_5b58 >> 9) & 1) != 0 || pRef->mp == 0) {
    pOld = pRef->mp;
    if (pOld != (RefCnt*)pCreature) {
      pCreature->mpVtbl->AddRef();
      pRef->mp = (RefCnt*)pCreature;
      if (pOld != 0)
        pOld->Release();
    }
  }

  anim = (u32)((CreatBase*)pCreature)->PlayAnim(1, 0, 1);
  if (anim == 0)
    anim = 0;
  else
    anim = FUN_00d998d0_s00d8_7620(anim, 0x2c9cc8e);

  fDist = 0.0f;
  fExtra = 0.0f;

  switch (pNode->mState) {
  case 0: {
    if (anim != 0 && (u32)pNode->mpActor != anim) {
      pNode->mState = 7;
      return 0;
    }
    vA.x = vB.x = vC.x = (*(float*)0x169f03c);
    vA.y = vB.y = vC.y = (*(float*)0x169f040);
    vA.z = vB.z = vC.z = (*(float*)0x169f044);
    fDist = 0.0f;
    if (pNode->mpInteract == 0) {
      if (pNode->mpActor != 0) {
        Vec3_s00d8_7620* pBox = pActor->mAnim.GetBox6c(&vC);
        vB.x = (pBox[0].x + pBox[1].x) * 0.5f;   // .x of first/second element
        vB.y = (pBox[1].y + pBox[0].y) * 0.5f;
        vB.z = (pBox[1].z + pBox[0].z) * 0.5f;
        Vec3_s00d8_7620* pSurf = PlanetModel_Get()->GetSurfacePos(&vA, &vB);
        vC.x = pSurf[0].x; vC.y = pSurf[0].y; vC.z = pSurf[0].z;
        Vec3_s00d8_7620* pPos = pCreature->mSpatial.GetPosition(&vA);
        vA.x = pPos[0].x - vC.x;
        vA.y = pPos[0].y - vC.y;
        vA.z = pPos[0].z - vC.z;
        Vec3_s00d8_7620* pN = normalized_safe(&vC, &vA);
        vB.x = pN[0].x; vB.y = pN[0].y; vB.z = pN[0].z;
        fDist = pActor->mAnim.GetDist74();
      }
    } else {
      FUN_00b02b90(&vB, pNode->mTarget.mp ? (u32)(uintptr_t)pNode->mTarget.mp : 0);
      Vec3_s00d8_7620* pDir = PlanetModel_Get()->DirectionToSurfacePosition(&vA, &vB);
      vC.x = pDir[0].x; vC.y = pDir[0].y; vC.z = pDir[0].z;
      fDist = vC.y - *(float*)((u8*)pNode->mpInteract + 0x14);
      fExtra = vC.z - *(float*)((u8*)pNode->mpInteract + 0x18);
      vA.x = vC.x - *(float*)((u8*)pNode->mpInteract + 0x10);
      (void)normalized_safe(&vB, &vA);
      vB.x = vB.x; // placeholder, filled below
      float dy = vC.z - *(float*)((u8*)pNode->mpInteract + 0x18);
      float dx = vC.x - *(float*)((u8*)pNode->mpInteract + 0x10);
      float dz = vC.y - *(float*)((u8*)pNode->mpInteract + 0x14);
      (void)dy; (void)dz;
      vA.x = dx * dx + dy * dy + dz * dz;
      fSpeed = *(float*)((u8*)pNode->mpInteract + 0x6c);
      if (fSpeed * fSpeed <= vA.x)
        fDist = 0.0f;
      else
        fDist = fSpeed - sqrtf(vA.x);
    }
    fExtra = pCreature->mSpatial.GetScale74() + fExtra + fDist;
    if (PlanetModel_Get() != 0) {
      vB.x = vB.x * fExtra + vC.x;
      vB.y = vB.y * fExtra + vC.y;
      vB.z = vB.z * fExtra + vC.z;
      Vec3_s00d8_7620* pSurf = PlanetModel_Get()->GetSurfacePos(&vA, &vB);
      vC.x = pSurf[0].x; vC.y = pSurf[0].y; vC.z = pSurf[0].z;
    }
    if (pNode->mbFlag24) {
      if (pNode->mpInteract != 0)
        pNode->mbFlag24 = 0;
      if (((pCreature->mFlags_5b58 >> 9) & 1) == 0) {
        *(u32*)&vA.x = *(u32*)&vB.x ^ 0x80000000u;
        vA.y = -vB.y;
        vA.z = -vB.z;
        ((CreatBase*)pCreature)->MoveToPointFacing(2, &vA, &vC, 0.2f, 0.5f);
      } else {
        Vec3_s00d8_7620* pPos = pCreature->mSpatial.GetPosition(&vC);
        Vec3_s00d8_7620* pSurf = PlanetModel_Get()->GetSurfacePos(&vA, &vB);
        vB.x = pSurf[0].x - pPos[0].x;
        vB.y = pSurf[0].y - pPos[0].y;
        vB.z = pSurf[0].z - pPos[0].z;
        (void)normalized_safe(&vA, &vB);
        fSpeed = pCreature->mSpatial.GetScale74() + 0.01f;
        ((CreatBase*)pCreature)->MoveToPointFacing(2, &vA, &vA, fSpeed, fSpeed);
      }
    }
    if (!((CreatBase*)&pCreature->mSpatial)->IsNearGoal())
      return 1;
    {
      void* pAvatar = FUN_00401090_s00d8_7620();
      (void)pAvatar;
      float food = *(float*)((u8*)pCreature->mpProfile_5b20 + 0x590);
      if (food == 0.0f || !((CreatBase*)pCreature)->IsEatingActive())
        pNode->mSub = 2;
      else
        pNode->mSub = 0xb;
    }
    if (pNode->mpInteract == 0) {
      if (pNode->mpActor != 0) {
        pNode->mState = 2;
        s32 h = -1;
        if (((CreatBase*)&pCreature->mSpatial)->Flag48() && (flags & 0x100000))
          h = (s32)FUN_00d7d370(pCreature, &vC);
        if (pNode->mSub == 0xb) pNode->mAnimKey = 0x4eea0d5;
        else                    pNode->mAnimKey = 0x4eea0d2;
        s32 r = ((CreatBase*)pCreature)->PlayAnim(pNode->mAnimKey, &vC, h);
        pNode->mAnimHandle = r;
      }
    } else {
      Vec3_s00d8_7620* pDir = PlanetModel_Get()->DirectionToSurfacePosition(&vA, &vB);
      vC.x = vB.x - pDir[0].x;
      fDist = vB.y - pDir[0].y;
      fExtra = vB.z - pDir[0].z;
      Vec3_s00d8_7620* pExt = pActor->mAnim.GetBox6c(&vA);
      float d = (*(float*)((u8*)pExt + 0x14) - *(float*)((u8*)pExt + 8)) * 1.75f;
      bool bNear = FUN_00c1ac70(pCreature, &vB, pNode->mSub, 0xffffffff, 0, 0, 0x3e4ccccd);
      (void)bNear;
      if ((fExtra * fExtra + fDist * fDist) + vC.x * vC.x <= d * d) {
        pNode->mState = 1;
        if (pNode->mSub == 0xb) pNode->mAnimKey = 0x4eea0d6;
        else                    pNode->mAnimKey = 0x4eea0d3;
        (void)d; (void)pExt;
      } else {
        pNode->mState = 6;
        if (pNode->mSub == 0xb) pNode->mAnimKey = 0x4eea0d7;
        else                    pNode->mAnimKey = 0x4eea0d4;
        s32 h = -1;
        if (((CreatBase*)&pCreature->mSpatial)->Flag48() && (flags & 0x100000))
          h = (s32)FUN_00d7d370(pCreature, &vC);
        pNode->mAnimHandle = ((CreatBase*)pCreature)->PlayAnim(pNode->mAnimKey, &vC, h);
      }
    }
    break;
  }
  case 1:
  case 2: {
    if (pNode->mpActor != 0 && pActor->mState_16c != 0 &&
        pActor->mState_16c != 2 && pActor->mState_16c != 3) {
      pNode->mState = 5;
      ((Stimuli_s00d8_7620*)((u8*)pCreature->mpStimuliMgr + 8))->ClearAll(1, 0);
      return 0;
    }
    s32 h = -1;
    u32 key = (pNode->mSub == 0xb) ? 0xb9ce16b9 : 0x68629eb3;
    u8 done = (u8)((CreatBase*)pCreature)->WaitForAnimEventOrEnd(key, &h, -1, pNode->mAnimHandle, 1);
    pNode->mbFlag18 = done;
    if (done) {
      if (pNode->mbFlag2c && pNode->mTarget.mp != 0 && pNode->mTarget.mp != (RefCnt*)0xffffffff) {
        void* pMgr = FUN_00c3e790();
        if (pMgr != 0) { (void)pMgr; }
      }
      if (pNode->mpInteract != 0) {
        pNode->mpInteract = pNode->mpInteract;
        (void)FUN_00b2a690();
      }
      if (pNode->mpActor == 0) {
        pNode->mState = 5;
        ((Stimuli_s00d8_7620*)((u8*)pCreature->mpStimuliMgr + 8))->ClearAll(1, 0);
        return 0;
      }
      pNode->mState = 3;
    }
    return 1;
  }
  case 3: {
    if (!pNode->mbFlag18) {
      s32 h = -1;
      if (((CreatBase*)pCreature)->WaitForAnimEventOrEnd(0x9cd2c8df, &h, pNode->mAnimHandle, 0, 1)) {
        pNode->mState = 4;
        FUN_00d85540(pCreature);
        if (pActor->mState_16c == 3) {
          if (pNode->mbFlag18) {
            FUN_00c15d50(pCreature, 0, 0, 0);
            pNode->mbFlag18 = 0;
          }
        }
        (void)FUN_00c0b7a0(pCreature);
      }
    }
    break;
  }
  case 6: {
    if (((CreatBase*)pCreature)->AnimationFinished(pNode->mAnimHandle)) {
      pNode->mState = 4;
      return 0;
    }
    break;
  }
  default:
    return 0;
  }
  return 1;
}

// @ 0x00d885a0
u8 __cdecl FUN_00d885a0(void* p1, u32 a2, u32 a3, u32 a4, u32 a5, PosseNode* node, u32 a7, f32 dt)
{
    CreatureManager* gm = (CreatureManager*)MOPS_s00d8_85a0(p1)->FUN_00c04590();
    if (p1 == gm->mpOwner) {
        gm = (CreatureManager*)MOPS_s00d8_85a0(p1)->FUN_00c04590();
        if (gm->mpListHead != (void*)((u8*)gm + 0x168))
            node->mFlagE = 1;
    }
    node->mTimer -= dt;
    if (node->mAnim != 0)
        return (u8)(!MOPS_s00d8_85a0(p1)->FUN_00c12400(node->mAnim));

    void* t = FUN_00d99470(MOPS_s00d8_85a0(p1)->FUN_00c0ee70());
    if (t == 0)
        return 0;
    if (MOPS_s00d8_85a0(p1)->FUN_00c0c130()) {
        MOPS_s00d8_85a0((u8*)((Creature_s00d8_85a0*)p1)->mpStimuliMgr + 8)->FUN_00bc97f0(0x1000000, 0, 10.0f, t);
        return 0;
    }
    ((Creature_s00d8_85a0*)p1)->mbFlag5c = 1;
    if (node->mRadius != 0.0f)
        FUN_00d7d540(p1, 1.0f, node->mRadius, (u8*)t + 0xc0);
    if (!MOPS_s00d8_85a0(p1)->FUN_00c0e0c0(0x2481dfc))
        MOPS_s00d8_85a0(p1)->FUN_00c14940(0x2481dfc, (u8*)t + 0xc0, -1, -1);

    FUN_00d99ac0_s00d8_85a0((u8*)p1 + 0xc0, (u8*)t + 0xc0, 1);

    if (node->mTimer >= 0.0f) {
        if (node->mFlagD != 0) {
            void* r = MOPS_s00d8_85a0(p1)->FUN_00c41ec0();
            if (((u32*)r)[0x17] != 0) {
                f32* pf = (f32*)((u8*)r + 0x14);
                if (*(u32*)r != ((u32*)r)[1])
                    pf = (f32*)(((u32*)r)[1] - 0x3c);
                Vec3_s00d8_85a0* tp = (Vec3_s00d8_85a0*)((Vec3_s00d8_85a0* (__thiscall*)(void*))VT((u8*)t + 0xc0)[0x2c / 4])((u8*)t + 0xc0);
                f32 d2 = (tp->z - pf[2]) * (tp->z - pf[2])
                       + (tp->y - pf[1]) * (tp->y - pf[1])
                       + (tp->x - pf[0]) * (tp->x - pf[0]);
                f32 thr = ((f32 (__thiscall*)(void*))VT((u8*)t + 0xc0)[0x74 / 4])((u8*)t + 0xc0);
                if (d2 <= thr)
                    return 1;
            }
            if (node->mFlagE != 0)
                return 1;
            Vec3_s00d8_85a0* tp = (Vec3_s00d8_85a0*)((Vec3_s00d8_85a0* (__thiscall*)(void*))VT((u8*)t + 0xc0)[0x2c / 4])((u8*)t + 0xc0);
            MOPS_s00d8_85a0(p1)->FUN_00c1c1d0(2, tp, 1.0f, 2.0f);
        }
        return 1;
    }

    node->mTimer2 -= dt;
    f32 near1 = FUN_00d38a30_s00d8_85a0(1, p1);
    f32 near2 = FUN_00d38a30_s00d8_85a0(2, p1);
    Vec3_s00d8_85a0* sp = (Vec3_s00d8_85a0*)((Vec3_s00d8_85a0* (__thiscall*)(void*))VT((u8*)p1 + 0xc0)[0x2c / 4])((u8*)p1 + 0xc0);
    Vec3_s00d8_85a0* tp = (Vec3_s00d8_85a0*)((Vec3_s00d8_85a0* (__thiscall*)(void*))VT((u8*)t + 0xc0)[0x2c / 4])((u8*)t + 0xc0);
    f32 dx = tp->x - sp->x, dy = tp->y - sp->y, dz = tp->z - sp->z;
    f32 dist = sqrtf(dx * dx + dy * dy + dz * dz);
    if (dist < 0.0f)
        dist = 0.0f;
    u8 hit = (u8)MOPS_s00d8_85a0(p1)->FUN_00c0d560(t, near1, dist);
    if (!hit)
        hit = (u8)((bool (__thiscall*)(void*, void*, f32, f32))VT(p1)[0xc0 / 4])(p1, t, near2, dist);
    if (node->mTimer2 < 0.0f) {
        u8 req[0x74];
        MOPS_s00d8_85a0(req)->FUN_00ac9850();
        ((void (__thiscall*)(void*, void*))VT((u8*)t + 0xc0)[0xdc / 4])((u8*)t + 0xc0, req);
        MOPS_s00d8_85a0(req)->FUN_007a41a0();
        return 0;
    }
    return hit;
}

// @ 0x00d888b0
u8 __cdecl FUN_00d888b0(void* p1, u32 a2, u32 a3, u32 a4, u32 a5, AlertNode* node, void* ctx)
{
    u8 result = 0;
    if (node != 0)
        node->mpTarget = 0;
    void* creature = *(void**)((u8*)ctx + 4);
    if (creature != 0) {
        void* target = ((void* (__thiscall*)(void*, u32))VT(creature)[0x5c / 4])(creature, 0xce9f6639);
        if (target != 0) {
            void* old = node->mpTarget;
            if (target != old) {
                ((void (__thiscall*)(void*))VT(target)[0])(target);
                node->mpTarget = target;
                if (old != 0)
                    ((void (__thiscall*)(void*))VT(old)[1])(old);
            }
            Vec3_s00d8_85a0* pos = (Vec3_s00d8_85a0*)((Vec3_s00d8_85a0* (__thiscall*)(void*))VT((u8*)target + 0xc0)[0x2c / 4])((u8*)target + 0xc0);
            node->mU_08 = *(u32*)&pos->x;
            node->mU_0c = *(u32*)&pos->y;
            node->mU_10 = *(u32*)&pos->z;
            node->mF_00 = gF_013eb95c;
            node->mF_04 = gF_01486110;
            node->mU_18 = 0;
            ((void (__thiscall*)(void*))VT((u8*)p1 + 0xc0)[0xec / 4])((u8*)p1 + 0xc0);
            result = 1;
        }
    }
    return result;
}

// @ 0x00d88970
void __cdecl FUN_00d88970(void* p1, u32 a2, u32 a3, u32 a4, u32 a5, void* node)
{
    if (node != 0) {
        void* obj = *(void**)((u8*)node + 0x14);
        if (obj != 0)
            ((void (__thiscall*)(void*))VT(obj)[1])(obj);
    }
    ((void (__thiscall*)(void*))VT((u8*)p1 + 0xc0)[0xec / 4])((u8*)p1 + 0xc0);
    MOPS_s00d8_85a0(p1)->FUN_00c17350(0x12007c90, 0);
}

// @ 0x00d88c10
u8 __cdecl FUN_00d88c10(void* p1)
{
    if (*(void**)((u8*)p1 + 0x1a0) != 0) {
        u32 idx = *(u32*)((u8*)p1 + 0x1b0);
        void* o = *(void**)((u8*)p1 + 0x1a0);
        if (o != 0) {
            void* r = ((void* (__thiscall*)(void*, u32))VT(o)[0xc / 4])(o, 0x52aa6117);
            if (r != 0 && idx != 0xffffffff) {
                if (!((bool (__thiscall*)(void*))VT(r)[0x2c / 4])(r)) {
                    MOPS_s00d8_85a0(r)->FUN_00c6ac90(idx);
                    return 1;
                }
            }
        }
    }
    return 0;
}

// @ 0x00d88c70
void __cdecl FUN_00d88c70(void* node, void* creature)
{
    void* target = *(void**)((u8*)node + 4);
    if (target == 0)
        return;
    Vec3_s00d8_85a0* p = (Vec3_s00d8_85a0*)((Vec3_s00d8_85a0* (__thiscall*)(void*))VT((u8*)target + 0xc0)[0x2c / 4])((u8*)target + 0xc0);
    f32 nx = p->x, ny = p->y, nz = p->z;
    f32 inv = 1.0f / sqrtf(nx * nx + ny * ny + nz * nz + gF_13ec4b8);
    nx *= inv;
    ny *= inv;
    nz *= inv;
    f32 ang = (*(f32*)node * gF_169f0ec) * 0.5f;
    f32 s = sinf(ang);
    f32 c = cosf(ang);
    f32 q[4];
    q[0] = nx * s;
    q[1] = ny * s;
    q[2] = nz * s;
    q[3] = c;
    Vec3_s00d8_85a0 axis;
    void* rot = ((void* (__thiscall*)(void*, void*, Vec3_s00d8_85a0*))VT((u8*)target + 0xc0)[0x5c / 4])((u8*)target + 0xc0, &axis, (Vec3_s00d8_85a0*)q);
    Vec3_s00d8_85a0* r = (Vec3_s00d8_85a0*)FUN_0059aed0((u8*)q + 0x10, rot);
    f32 tx = ((r->x - nx) * gF_13eb8c8 + nx) * gF_1476b54;
    f32 ty = ((r->y - ny) * gF_13eb8c8 + ny) * gF_1476b54;
    f32 tz = ((r->z - nz) * gF_13eb8c8 + nz) * gF_1476b54;
    Vec3_s00d8_85a0* sp = (Vec3_s00d8_85a0*)((Vec3_s00d8_85a0* (__thiscall*)(void*))VT((u8*)creature + 0xc0)[0x2c / 4])((u8*)creature + 0xc0);
    Vec3_s00d8_85a0 dest;
    dest.x = tx + sp->x;
    dest.y = ty + sp->y;
    dest.z = tz + sp->z;
    MOPS_s00d8_85a0(creature)->FUN_00c1c1d0(3, &dest, 1.0f, 2.0f);
}

// @ 0x00d88e50
u8 __cdecl FUN_00d88e50(void* p1, u32 a2, u32 a3, u32 a4, u32 a5, AvatarNode* node)
{
    if (node != 0)
        node->mpTarget = 0;
    Creature_s00d8_85a0* c = (Creature_s00d8_85a0*)p1;
    u32 anim = MOPS_s00d8_85a0((u8*)c->mpStimuliMgr + 8)->FUN_00bc96a0(0, 4);
    if (anim == 0)
        return 0;
    void* ref = FUN_00d999d0((void*)anim);
    if (ref == 0)
        return 0;
    node->mRandom = MOPS_s00d8_85a0((void*)0x1601760)->FUN_009360d0();
    void* old = node->mpTarget;
    if (ref != old) {
        ((void (__thiscall*)(void*))VT(ref)[0])(ref);
        node->mpTarget = ref;
        if (old != 0)
            ((void (__thiscall*)(void*))VT(old)[1])(old);
    }
    MOPS_s00d8_85a0(p1)->FUN_00c13a30(1);
    MOPS_s00d8_85a0(p1)->FUN_00c12310(0x724e4024, -1, 0);
    FUN_00d88c70(node, p1);
    return 1;
}

// @ 0x00d88ef0
void __cdecl FUN_00d88ef0(void* p1, u32 a2, u32 a3, u32 a4, u32 a5, void* node)
{
    void* mgr = *(void**)((u8*)p1 + 0xb4c);
    MOPS_s00d8_85a0((u8*)mgr + 8)->FUN_00bc98f0(0, 4);
    if (node != 0) {
        void* obj = *(void**)((u8*)node + 4);
        if (obj != 0)
            ((void (__thiscall*)(void*))VT(obj)[1])(obj);
    }
}

// @ 0x00d88f20
u8 __cdecl FUN_00d88f20(void* p1, u32 a2, u32 a3, u32 a4, u32 a5, void* p6)
{
    if (MOPS_s00d8_85a0((u8*)p1 + 0xc0)->FUN_00c42e20())
        FUN_00d88c70(p6, p1);
    return 1;
}

// @ 0x00d88f50
u8 __cdecl FUN_00d88f50(void* p1)
{
    SpatialQuery q;
    q.mpResult = 0;
    q.mU_04 = 0;
    q.mU_08 = 0;
    q.mF_14 = gF_0169f03c;
    q.mF_18 = gF_0169f040;
    q.mF_1c = gF_0169f044;
    q.mF_20 = gF_1485720;
    q.mU_24 = 0;
    q.mB_4c = 0;
    q.mF_50 = 0.0f;
    q.mF_54 = 0.0f;
    q.mF_58 = 0.0f;
    q.mU_5c = 0;
    q.mF_60 = gF_1470f1c;
    q.mF_64 = gF_13ec4b4;
    q.mF_68 = gF_147c030;
    q.mF_6c = 0.0f;
    q.mU_70 = 0;
    ((void (__thiscall*)(void*, SpatialQuery*))VT((u8*)p1 + 0xc0)[0xdc / 4])((u8*)p1 + 0xc0, &q);
    if (q.mpResult != 0 && *(u32*)((u8*)q.mpResult - 4) != 0)
        FUN_00f47380(q.mpResult);
    return 1;
}

// @ 0x00d8a2a0
bool __cdecl FUN_00d8a2a0(Citizen_s00d8_a2a0* c, void*, void*, void*, void*, StateReceiveItem* st)
{
    if (st != 0) {
        st->mp18 = 0;
        st->m1c.mp = 0;
    }
    cAnimNode_s00d8_a2a0* node = (cAnimNode_s00d8_a2a0*)c->mpBehavior->mHead.Play(0, 0x40000);
    if (node == 0 || node->mKind != 7)
        return false;

    unsigned index = (unsigned)node->mf10;
    cGroup* grp = (cGroup*)FUN_00d998d0_s00d8_a2a0(node, 0xd0036e08);
    cGroup* old = st->mp18;
    if (grp != old) {
        if (grp != 0)
            grp->AddRef();
        st->mp18 = grp;
        if (old != 0)
            old->Release();
    }
    st->m1c.Assign((cAsset*)st->mp18->At(index));

    if (st->mp18 == 0 || st->m1c.mp == 0)
        return false;
    if (!c->FUN_00c13c60(st->m1c.mp, 1, 0))
        return false;
    if (c->FUN_00c0f5f0()) {
        c->FUN_00c15bd0(0, 0, 0);
        if (c->FUN_00c0f5f0())
            return false;
    }
    if (st->mp18->IndexOf(st->m1c.mp) == -1)
        return false;

    const Vec3_s00d8_a2a0* pos = st->m1c.mp->GetPosition();
    Vec3_s00d8_a2a0 tmp;
    cPlanetModel_s00d8_a2a0* planet = PlanetModel(&tmp, pos);
    st->mTarget = *planet->DirectionToSurfacePosition(&tmp, pos);

    float speed = c->mLoco.GetRadius() * kPointThree;
    speed = c->mLoco.GetRadius() + speed;
    speed = st->mp18->mLoco.GetRadius() + speed;

    Vec3_s00d8_a2a0 diff;
    Vec3_s00d8_a2a0 facing;
    const Vec3_s00d8_a2a0* lp = c->mLoco.GetPosition();
    diff.x = st->mTarget.x - lp->x;
    diff.y = st->mTarget.y - lp->y;
    diff.z = st->mTarget.z - lp->z;
    c->MoveToPointAndFacingAtSpeed(2, &st->mTarget, normalized_safe_s00d8_a2a0(&facing, &diff), speed, kTwo);
    c->FUN_00c14750(1);
    c->vf84(0, 0, 0);
    st->mf10 = 0.0f;
    st->mb14 = 0;
    st->mb20 = (c->mpEatenState->mf590 == 0.0f);
    st->m24 = 0;
    st->m0 = 0;
    return true;
}

// @ 0x00d8a500
void __cdecl FUN_00d8a500(Citizen_s00d8_a2a0* c, void*, void*, void*, void*, StateReceiveItem* st)
{
    c->mpBehavior->mHead.ClearAll(0, 0x40000);
    if (st != 0) {
        cAsset* asset = st->m1c.mp;
        if (asset != 0)
            asset->ReleaseBundle();
        cGroup* grp = st->mp18;
        if (grp != 0)
            grp->Release();
    }
}

// @ 0x00d8a550
void __cdecl FUN_00d8a550(Citizen_s00d8_a2a0* c)
{
    c->mpBehavior->mHead.ClearAll(0, 0x2000000);
    if (c->mbB5e != 0)
        return;
    LocoEffectSpec spec;
    InitLocoEffectSpec(&spec);
    c->mLoco.PlayEffectSpec(&spec);
    FreeOwnedBuffer(spec.mpData);
    c->FUN_00c0cff0(0);
    c->FUN_00c14750(0);
}

// @ 0x00d8a660
bool __cdecl FUN_00d8a660(Citizen_s00d8_a2a0* c)
{
    c->InterruptAnimation(0x48601c0, -1, 0);
    LocoEffectSpec spec;
    InitLocoEffectSpec(&spec);
    c->mLoco.PlayEffectSpec(&spec);
    FreeOwnedBuffer(spec.mpData);
    return true;
}

// @ 0x00d8a750
bool __cdecl FUN_00d8a750(Citizen_s00d8_a2a0* c, void*, void*, void*, void*, TickOut* out, StateUfoClump* st)
{
    if (st == 0 || st->mp4 == 0)
        return false;
    c->vf84(st->mp4, 1, 0);
    if (st->mp4 != 0 && st->mp4->vf5c(0x1186577) != 0)
        c->InterruptAnimation(0x2481de5, -1, 0);

    out->mf0 = FUN_00572a10(kOne, kTwo);
    out->m4 = 0;

    LocoEffectSpec spec;
    InitLocoEffectSpec(&spec);
    c->mLoco.PlayEffectSpec(&spec);
    FreeOwnedBuffer(spec.mpData);
    return true;
}

// @ 0x00d8a8c0
bool __cdecl FUN_00d8a8c0(Citizen_s00d8_a2a0* c, void*, void*, void*, void*, TickOut* out, StateUfoClump* st)
{
    if (st->mp4 == 0)
        return false;
    c->vf84(st->mp4, 1, 0);
    if (st->mp4 != 0 && st->mp4->vf5c(0x1186577) != 0)
        c->InterruptAnimation(0x2481de5, -1, 0);

    float v = g_Random.RandomDoubleUniform() + 1.0f;
    if (v < (float)kTwoDouble) {
        if (v <= kOne)
            v = kOne;
    } else {
        v = (float)kTwoDouble;
    }
    out->mf0 = v;
    out->m4 = 0;

    LocoEffectSpec spec;
    InitLocoEffectSpec(&spec);
    c->mLoco.PlayEffectSpec(&spec);
    FreeOwnedBuffer(spec.mpData);
    c->Hover(1);
    return true;
}

// @ 0x00d8aa40
bool __cdecl FUN_00d8aa40(Citizen_s00d8_a2a0* c, void*, void*, void*, void*, StateEnterSpot* st)
{
    if (st != 0)
        st->mp0 = 0;
    bool ok = false;
    cAnimNode_s00d8_a2a0* node = (cAnimNode_s00d8_a2a0*)c->mpBehavior->mHead.Play(0, 0x100);
    if (node != 0) {
        cTargetObject* tgt = (cTargetObject*)FUN_00d998d0_s00d8_a2a0(node, 0x61494bd);
        cTargetObject* old = st->mp0;
        if (tgt != old) {
            if (tgt != 0)
                tgt->AddRef();
            st->mp0 = tgt;
            if (old != 0)
                old->Release();
        }
        if (st->mp0 != 0) {
            int state = st->mp0->mState108;
            if (state >= 2 && state <= 4) {
                float radius = c->mLoco.GetRadius();
                // Retail computes this approach speed and then discards it.
                float speed = radius + st->mp0->mBundle.vf70() + kPointZeroOne;
                (void)speed;
                st->m0c = 0;
                c->FUN_00c14750(0);
                c->MoveToPointAtSpeed(2, st->mp0->mBundle.GetPosition(), radius, radius);
                ok = true;
            }
        }
    }
    return ok;
}

// @ 0x00d8ab30
bool __cdecl FUN_00d8ab30(Citizen_s00d8_a2a0* c, void*, void*, void*, void*, StateSneak* st, void*, float dt)
{
    if (st->mp0 == 0
        || st->mp0->IsFinished()
        || st->mp0->mState108 < 2
        || st->mp0->mState108 > 4)
        return false;

    switch (st->m0c) {
    case 0:
        if (c->mLoco.IsNearGoal()) {
            st->mf04 = GetPropertyTf(FUN_00d1e660()->mpOwner->mpProps, 0x62dca9c8, kTen);
            c->SetStealthed(0, 0);
            st->m0c = 1;
        }
        break;

    case 1:
        st->mf04 = st->mf04 - dt;
        if (st->mf04 <= 0.0f) {
            st->m08 = 0;
            FUN_00bcbc80();
        }
        if (c->AnimationFinished(st->m08)) {
            st->m08 = c->PlayAnimation(0x65d1437, 1, -1);
            return true;
        }
        break;

    default:
        return false;
    }
    return true;
}

// @ 0x00d8ac30
void __cdecl FUN_00d8ac30(Citizen_s00d8_a2a0* c, void*, void*, void*, void*, StateBundle* st)
{
    if (st != 0 && st->mp0 != 0)
        st->mp0->Release();
    if (c->mbB5e == 0) {
        c->FUN_00c0d240();
        c->FUN_00c14750(0);
        c->SetStealthed(0, 0);
    }
}

// @ 0x00d8af20
bool __cdecl FUN_00d8af20(Citizen_s00d8_a2a0* c, void*, void*, void*, void*, StateBundle* st, void*, float dt)
{
    cTargetObject* tgt = st->mp0;
    if (tgt == 0 || tgt->IsFinished()) {
        c->mpBehavior->mHead.ClearAll(0, 0x100);
        return false;
    }
    cRefObject* container = FUN_00b3d2b0()->GetContainer();
    if (st->mp0->mpSpot != container) {
        cRefObject* spot0 = st->mp0->mpSpot;
        if (spot0 == 0 || spot0->Query(0x4f396a66) == 0) {
            c->mpBehavior->mHead.ClearAll(0, 0x100);
            return false;
        }
    }
    cSpotServer* spot = 0;
    if (st->mp0->mpSpot != 0)
        spot = (cSpotServer*)st->mp0->mpSpot->Query(0x4f396a66);

    switch (st->m08) {
    case 0:
        if (c->mLoco.FUN_00c422c0() <= kFourHundred)
            c->SetStealthed(1, 0);
        if (c->mLoco.IsNearGoal())
            st->m08 = 1;
        break;

    case 1: {
        c->SetStealthed(0, 0);
        float ratio = st->mf0c / st->mf10;
        EatFood(c, kEatFoodRate * ratio * dt, 0x133b8599, 0);
        cTargetObject* node = st->mp0;
        float before = node->mf134;
        float delta = ratio * dt;
        st->mf0c = st->mf0c - delta;
        st->mf10 = st->mf10 - dt;
        cGameMgr* mgr = FUN_00b3d2b0();
        mgr->FUN_00ac7d10(delta, node->mpSpot, node);
        if (before - delta <= 0.0f || st->mf0c <= 0.0f) {
            st->m08 = 2;
            return true;
        }
        if (st->m04 != 0 && !c->AnimationFinished(st->m04))
            return true;
        unsigned id = (spot != 0) ? 0x6568320 : 0x6568374;
        st->m04 = c->PlayAnimationWithTarget(id, node->mBundle.GetPosition(), -1);
        break;
    }

    case 2:
        if (st->mp0 != 0) {
            if (spot != 0)
                spot->FindSpot(0xd, st->m14);
            st->m14 = -1;
            cTargetObject* ref = st->mp0;
            if (ref != 0) {
                st->mp0 = 0;
                ref->Release();
            }
        }
        if (st->m04 != 0 && !c->AnimationFinished(st->m04))
            return true;
        c->mpBehavior->mHead.ClearAll(0, 0x100);
        return false;

    default:
        break;
    }
    return true;
}

// @ 0x00d8b1a0
void __cdecl FUN_00d8b1a0(Citizen_s00d8_a2a0* c, void*, void*, void*, void*, StateBundle* st)
{
    if (st != 0 && st->mp0 != 0)
        st->mp0->Release();
    if (st->mp0 != 0) {
        cRefObject* spot0 = st->mp0->mpSpot;
        if (spot0 != 0) {
            cSpotServer* spot = (cSpotServer*)spot0->Query(0x4f396a66);
            if (spot != 0)
                spot->FindSpot(0xd, st->m14);
        }
        st->m14 = -1;
    }
    if (c->mbB5e == 0) {
        c->FUN_00c0d240();
        c->FUN_00c14750(0);
        c->SetStealthed(0, 0);
    }
}

// @ 0x00d8cde0
float StimulusProbe_SelfState(cCreature_s00d8_cbb0* pCreature, int nUnused1, int nUnused2, int nUnused3, cBehaviorStimuli_s00d8_cbb0* pStimuli, uint8_t* pbFlag, int nUnused4, cStimulusContext* pContext)
{
    cGameData* pGameData = pCreature->GetGameData();
    if (pCreature == pGameData->mpActiveCreature
        && pGameData->mpCollisionList != &pGameData->mpCollisionList)
        return 0.0f;

    if (pStimuli != 0)
        pStimuli->GetAny();
    *pbFlag = 1;

    void* pSet = BehaviorSet_Get(&pCreature->mpAnimator->mThreatSet, pContext->mnKey);
    BehaviorSet_Lookup(pSet, pStimuli);

    cCreature_s00d8_cbb0* pOther = 0;
    if (pStimuli->mpTargetEntry != 0)
        pOther = (cCreature_s00d8_cbb0*)BehaviorSet_Resolve(
            ((void* (__thiscall*)(void*, uint32_t))
                ((void**)((void**)pStimuli->mpTargetEntry)[0])[0x5c / 4])
                (pStimuli->mpTargetEntry, 0xce9f6639));

    if (pOther == 0)
        return 0.0f;

    float fFirst = GetStimulusValue(2, pCreature);
    float fSecond = GetStimulusValue(1, pCreature);
    float fDistance = GetDistance(&pCreature->mLocomotive, &pOther->mLocomotive, 1);

    uint32_t nFilter[3] = {0, 0, 0};
    for (uint32_t i = 0; i < 3; ++i)
        nFilter[i] = ~nFilter[i];
    nFilter[2] &= 0xffffff;
    if (pCreature->Flag388())
        nFilter[0] &= 0x7fffffff;

    if (pCreature->AcceptTarget(pOther)) {
        if (pCreature->FindNearby(pOther, nFilter[0], fDistance, 0, 0, 0, 0) != -1
            || fDistance <= GetStimulusValue(5, pCreature)
            || pCreature->IsProximityClose(pOther, fSecond, fDistance)
            || pCreature->v0c0(pOther, fFirst, fDistance))
            return 1.0f;
    }
    return 0.0f;
}

// @ 0x00d8cf80
float NEARBY_ENEMY_EGG_Decide(cCreature_s00d8_cbb0* pCreature)
{
    void* pAnimation = pCreature->mpAnimator->mChannel.PlayAnimation(0x80, 0);
    cCreature_s00d8_cbb0* pEgg = (cCreature_s00d8_cbb0*)BehaviorSet_Resolve(pAnimation);
    if (pEgg != 0 && pEgg->mnBehaviourState != 4 && pEgg->mnFlags == 0)
        return 1.0f;

    cAnimIterator_s00d8_cbb0 iterator;
    iterator.mpCurrent = pCreature->mpAnimEntriesBegin;
    iterator.mpEnd = pCreature->mpAnimEntriesEnd;
    if (iterator.mpCurrent == iterator.mpEnd)
        return 0.0f;
    if (!iterator.IsValid(*iterator.mpCurrent))
        iterator.Advance();

    for (;;) {
        cNeighbourEntry* pEntry = (cNeighbourEntry*)*iterator.mpCurrent;
        cCreature_s00d8_cbb0* pOther = pEntry->mpCreature;
        if (pOther != 0 && pOther->mnId != 0) {
            cCreature_s00d8_cbb0* pNearby = (cCreature_s00d8_cbb0*)pEntry->mpOwnerKey;
            if (pNearby != 0 && pNearby->GetSpeciesProfile() != pCreature->GetSpeciesProfile()
                && pEntry->mbFlag4 != 0 && pOther->mnBehaviourState != 4) {
                const Vec3_s00d8_cbb0* pOtherPos = pNearby->mSpatial.GetPosition();
                const Vec3_s00d8_cbb0* pPos = pOther->mSpatial.GetPosition();
                float fX = pPos->mX - pOtherPos->mX;
                float fY = pPos->mY - pOtherPos->mY;
                float fZ = pPos->mZ - pOtherPos->mZ;
                float fDistanceSq = fZ * fZ + fY * fY + fX * fX;
                if (fDistanceSq > gEggSightRangeSq && pOther->mnFlags == 0) {
                    pCreature->mpAnimator->mChannel.Play(0x80, 0, 100.0f, pOther);
                    return 1.0f;
                }
            }
        }
        do {
            ++iterator.mpCurrent;
            if (iterator.mpCurrent == iterator.mpEnd)
                return 0.0f;
        } while (!iterator.IsValid(*iterator.mpCurrent));
    }
}

// @ 0x00d8d300
int CLAIM_NEST_Tick(int nUnused, cCreature_s00d8_cbb0* pCreature, int nUnused1, int nUnused2, int nUnused3, cActionState* pState)
{
    cCreature_s00d8_cbb0* pTarget = pState->mpTarget;
    if (pTarget == 0 || !*(uint8_t*)&pTarget->mnBehaviourState)
        return 0;
    if (pTarget->v2c())
        return 0;

    switch (pState->mnState) {
    case 0:
        pCreature->MoveToPointAtSpeed(2, pTarget->mSpatial.GetPosition(), 1.0f, gRunSpeed);
        if (pCreature->IsNearGoal())
            pState->mnState = 1;
        return 1;

    case 1:
        if (pState->mnAnimation == 0) {
            pState->mnAnimation =
                pCreature->InterruptAnimation(pState->mnAnimationId, -1, 0);
            return 1;
        }
        if (pCreature->AnimationFinished(pState->mnAnimation) && pState->mbReady == 1) {
            pState->mnState = 3;
            return 1;
        }
        {
            int nEvent = -1;
            char bDone = pCreature->WaitForAnimEventOrEnd(0xed41b225, &nEvent,
                                                          pState->mnAnimationId,
                                                          pState->mnAnimation, 1);
            if (pState->mbReady != 0 || !bDone)
                return 1;

            pState->mbReady = 1;
            cGameData* pGameData = pCreature->GetGameData();
            ((cCreature_s00d8_cbb0*)pGameData->mpLinkedObject)->SetLinkedObject(0);
            ClaimNearbyNestForAvatar(pTarget);
            void* pContext = GetClaimContext();
            pTarget->SetLinkedObject(ClaimContext_GetValue(pContext));

            cProximityQuery query;
            NeighbourVector_Find((cAnimIterator_s00d8_cbb0*)&query, pCreature->mpNeighboursBegin,
                                 &query);
            cNeighbourIterator iterator;
            iterator.mpCurrent = pCreature->mpNeighboursBegin;
            iterator.mpEnd = pCreature->mpNeighboursEnd;
            if (iterator.mpCurrent != iterator.mpEnd) {
                if (!IsValidNeighbourEntry(&iterator,
                                           (cNeighbourEntry*)*iterator.mpCurrent))
                    iterator.Advance();
                while (iterator.mpCurrent != iterator.mpEnd) {
                    cNeighbourEntry* pEntry = (cNeighbourEntry*)*iterator.mpCurrent;
                    cCreature_s00d8_cbb0* pNearby =
                        (cCreature_s00d8_cbb0*)Object_LookupByKey(pEntry->mpCreature, 0x018eb45e);
                    if (pNearby != 0 && ((pNearby->mnFlags >> 9) & 1) == 0
                        && pNearby->IsScareable())
                        pNearby->mpAnimator->mChannel.Play(0x200000, 0, gFleeDistanceSq,
                                                           pState->mpTarget);
                    iterator.Advance();
                }
            }

            cEffectManager* pEffects = (cEffectManager*)EffectsManagerPtr();
            cVisualEffect* pEffect = 0;
            if (pEffects->CreateEffect(0x7a33577b, 0, &pEffect)) {
                cXformMsg message;
                message.SetPosition(pTarget->mSpatial.GetPosition());
                Matrix3FromQuaternion(&message.mTransform, pTarget->mSpatial.GetOrientation());
                message.mnFlags |= 2;
                ++message.mnCount;
                pEffect->Send(&message);
                pCreature->SetLinkedObject(0);
            }
            if (pEffect != 0)
                pEffect->Release();
            return 1;
        }

    case 3:
        return 0;
    }
    return 1;
}

// @ 0x00d8d5b0
int STARTLED_RESPONSE_Activate(cCreature_s00d8_cbb0* pCreature, int nUnused1, int nUnused2, int nUnused3, int nUnused4, int nUnused5, cActionState* pState)
{
    if (pState->mpTarget == 0)
        return 0;
    cCreature_s00d8_cbb0* pThreat = (cCreature_s00d8_cbb0*)BehaviorSet_Resolve(
        ((void* (__thiscall*)(void*, uint32_t))((void**)((void**)pState->mpTarget)[0])[0x5c / 4])
            (pState->mpTarget, 0xce9f6639));
    if (pThreat == 0)
        return 0;

    pCreature->v084(&pThreat->mStimulusTarget, 1, 0);
    pThreat->mnFlags = 0;

    if (!pCreature->AcceptTarget(pThreat))
        goto finish;

    {
        const Vec3_s00d8_cbb0* pThreatPos = pThreat->mLocomotive.GetPosition();
        const Vec3_s00d8_cbb0* pOwnPos = pCreature->mLocomotive.GetPosition();
        float fX = pThreatPos->mX - pOwnPos->mX;
        float fY = pThreatPos->mY - pOwnPos->mY;
        float fZ = pThreatPos->mZ - pOwnPos->mZ;
        float fScale = 1.0f / (fY * fY + (fX * fX + fZ * fZ) + gDirectionEpsilon);

        Vec3_s00d8_cbb0 aim;
        aim.mX = pOwnPos->mX + (fScale * fX) * gStartleStep;
        aim.mY = pOwnPos->mY + (fScale * fY) * gStartleStep;
        aim.mZ = pOwnPos->mZ + (fScale * fZ) * gStartleStep;

        Vec3_s00d8_cbb0 surface;
        cPlanetModel_s00d8_cbb0* pPlanet = PlanetModel(&surface, &aim, 1.0f, gRunSpeed);
        pCreature->MoveToPointAtSpeed(3, pPlanet->DirectionToSurfacePosition(&surface, &aim));

        cNeighbourIterator iterator;
        iterator.mpCurrent = pCreature->mpNeighboursBegin;
        iterator.mpEnd = pCreature->mpNeighboursEnd;
        if (iterator.mpCurrent != iterator.mpEnd) {
            if (!IsValidNeighbourEntry(&iterator, (cNeighbourEntry*)*iterator.mpCurrent))
                iterator.Advance();
            while (iterator.mpCurrent != iterator.mpEnd) {
                cNeighbourEntry* pEntry = (cNeighbourEntry*)*iterator.mpCurrent;
                cCreature_s00d8_cbb0* pNearby = pEntry->mpCreature;
                if (pNearby != 0 && pNearby->GetTypeId() == 0x018eb45e
                    && pNearby->GetSpeciesProfile() == pCreature->GetSpeciesProfile())
                    pNearby->mpAnimator->mChannel.Play(0, 0x40, gStartleTrigger, pThreat);
                do {
                    ++iterator.mpCurrent;
                    if (iterator.mpCurrent == iterator.mpEnd)
                        goto finish;
                } while (!IsValidNeighbourEntry(&iterator,
                                                (cNeighbourEntry*)*iterator.mpCurrent));
            }
        }
    }

finish:
    pCreature->InterruptAnimation(0x92314082, -1, 0);
    pCreature->PlayAnimation(0x52314083, 1, -1);
    return 1;
}

// @ 0x00d8db70
bool __cdecl FUN_00d8db70(void* p1, void* p2, void* p3, void* p4, int onlyGuard, LOUNGE_memory_block* block, void** iter)
{
    (void)p2; (void)p3; (void)p4;
    void* g = *iter;
    block->mbOnlyGuard = (onlyGuard != 0);
    if (!(g != 0 && !((TextRunIterator*)g)->AtBegin()))
        g = FUN_00d82040(p1, block->mbOnlyGuard);
    if (g != 0) {
        if (FUN_00d8d820(block, 0, (cSPCreatureBase_s00d8_d820*)p1, (LoungeGroup*)g)) {
            block->mAnimHandle = 0;
            cSPCreatureBase_s00d8_d820* cr = (cSPCreatureBase_s00d8_d820*)p1;
            Loco_s00d8_d820* loco = &cr->mLoco;
            if (((LoungeGroup*)g)->mTag == 0x4472a59) {
                GameData* gd = cr->FUN_00c04590();
                float3 p = *gd->GetPosition();
                float3 d;
                d.x = block->mMyPosition.x - p.x;
                d.y = block->mMyPosition.y - p.y;
                d.z = block->mMyPosition.z - p.z;
                float r = loco->Slot74();
                float speed = r * gHalfF_1471064;
                float3 out;
                float3* n = FUN_00449c20(&out, &d);
                cr->MoveToPointAndFacingAtSpeed(2, &block->mMyPosition, n, speed, r);
                return true;
            }
            float r = loco->Slot74();
            float speed = r * gHalfF_1471064;
            cr->MoveToPointAtSpeed(2, &block->mMyPosition, speed, r);
            return true;
        }
    }
    return false;
}

// @ 0x00d8e8d0
bool __cdecl FUN_00d8e8d0(cCreature_s00d8_e8d0* c, u32 a2, u32 a3, u32 a4, u32 a5, TickStatePlay* st)
{
    if (st->mnPhase == 0) {
        TuningProfile* prof = (TuningProfile*)
            ((u32(__fastcall*)(cCreature_s00d8_e8d0*, void*))(*(void***)c)[0xb4 / 4])(c, st->mpOwner);
        c->FUN_c196a0(st->mpOwner, 1, 0);

        int count = (int)((char*)prof->mpItemEnd - (char*)prof->mpItemBegin) >> 2;
        u32 pick;
        if (count > 0)
            pick = ((RandomLCG*)0x01601760)->UniformU32((u32)count);
        else
            pick = 0;
        u32 guid = prof->GetAt(pick);
        st->mnAnim = c->InterruptAnimation(guid, -1, 0);
        st->mnPhase = 2;

        SpatialVec vec;
        void* inlineBuf[8];
        vec.mpBegin = (void**)inlineBuf;
        vec.mpEnd   = (void**)inlineBuf;
        vec.mpCap   = (void**)inlineBuf + 8;

        u32 kind = prof->mnType;
        if (kind == 0x31 || kind == 0x32) {
            FUN_00b3d4c0();
            u32* holder = (u32*)FUN_00b3d240();
            void* mgr = (void*)*holder;
            float radius = prof->mfF4 + prof->mfA8;
            u32 handle = ((u32(__fastcall*)(void*, float, SpatialVec*, int, void*, cCreature_s00d8_e8d0*))
                          (*(void***)c->mSpatial)[0x2c / 4])(c->mSpatial, radius, &vec,
                                                            0, (void*)0x00d9a9c0, c);
            ((void(__fastcall*)(void*, u32))(*(void***)mgr)[0x48 / 4])(mgr, handle);

            u32 n = (u32)(vec.mpEnd - vec.mpBegin);
            for (u32 i = 0; i < n; ++i) {
                void* sp = vec.mpBegin[i];
                if (sp == 0)
                    continue;
                cCreature_s00d8_e8d0* cr = (cCreature_s00d8_e8d0*)
                    ((void*(__fastcall*)(void*, u32))(*(void***)sp)[0xb8 / 4])(sp, 0xd0036e08);
                if (cr == 0)
                    continue;

                if (kind == 0x31) {
                    if (((u8(__fastcall*)(void*))(*(void***)cr->mSpatial)[0x58 / 4])(cr->mSpatial))
                        continue;
                    if (cr->mbB5E != 0)
                        continue;
                    if (cr->mpB20 == c->mpB20)
                        continue;
                    if (cr->Flag388())
                        continue;
                    ((BehaviorTree*)((char*)cr->mpBt + 8))->Stim(0, 0x4000000, 3.402823466e38F, c);
                    cr->mpOrderMgr->Activate(1, 1, 0, prof->mfA0, 0, cr);
                    ((BehaviorTree*)((char*)cr->mpBt + 8))->ClearAll(0x400, 0);
                    int slot = cr->mpOrderMgr->FindSlot(2, 1, 0, 0);
                    if (slot != -1)
                        cr->mpOrderMgr->DeactivateSlot(slot);
                } else {
                    if (((u8(__fastcall*)(void*))(*(void***)cr->mSpatial)[0x58 / 4])(cr->mSpatial) == 0 &&
                        cr->mbB5E == 0 &&
                        cr->mpB20 != c->mpB20 &&
                        cr->Flag388() == 0) {
                        ((BehaviorTree*)((char*)cr->mpBt + 8))->Stim(0, 0x4000000, 3.402823466e38F, c);
                        ((BehaviorTree*)((char*)cr->mpBt + 8))->Stim(0x400000, 0, 3.402823466e38F, c);
                        ((BehaviorTree*)((char*)cr->mpBt + 8))->Stim(0, 0x10000, 5.0f, c);
                        FUN_00d7a070(cr, c->mpB20);
                        float tmp = 0.0f;
                        cr->mpOrderMgr->Activate(2, 1, 0, 3.402823466e38F, &tmp, cr);
                        ((BehaviorTree*)((char*)cr->mpBt + 8))->ClearAll(0x400, 0);
                        int slot = cr->mpOrderMgr->FindSlot(1, 1, 0, 0);
                        if (slot != -1)
                            cr->mpOrderMgr->DeactivateSlot(slot);
                    } else if (cr->mpB20 == c->mpB20) {
                        ((BehaviorTree*)((char*)cr->mpBt + 8))->Stim(0, 0x10000, 5.0f, 0);
                        FUN_00d7a070(cr, 0);
                    }
                }
            }
            vec.Destroy();
            return true;
        }

        if (kind - 0x33 == 0) {
            DramaMgr* drama = (DramaMgr*)c->Drama(8, 0);
            drama->Trigger();
        }
        vec.Destroy();
        return true;
    }

    if (st->mnPhase == 2) {
        if (c->AnimationFinished(st->mnAnim))
            st->mnPhase = 3;
        return true;
    }
    if (st->mnPhase == 3)
        return false;
    return true;
}

// @ 0x00d8f170
void __cdecl FUN_00d8f170(cCreature_s00d8_e8d0* c, u32 a2, u32 a3, u32 a4, u32 a5, TickStateRelease* st)
{
    c->mpOrderMgr->DeactivateSlot(st->mn18);

    if (st->mp10 != 0) {
        c->FUN_c15150(st->mp0C, 0);
        void* obj = st->mp10;
        if (obj != 0) {
            st->mp10 = 0;
            ((void(__fastcall*)(void*))(*(void***)obj)[1])(obj);
        }
    }

    if (st->mp14 != 0) {
        BehaviorData* bt = st->mp14->mpBt;
        if (bt != 0 && bt->mn1D8 == 0x2d852ed) {
            int idx = (int)bt->mn1DC * 0xac;
            BtChild* child = (BtChild*)((char*)bt + idx + 0x160);
            if (child->mpBegin != child->mpEnd) {
                void** it = child->mpBegin;
                do {
                    if ((cCreature_s00d8_e8d0*)*it == c)
                        break;
                    ++it;
                } while (it != child->mpEnd);
                if (it != child->mpEnd)
                    FUN_00bf3420(it);
            }
        }
    }

    void* guid = c->GetCurrentAnimationGUID();
    if (guid == (void*)0x265d18b || c->GetCurrentAnimationGUID() == (void*)0x265d18c)
        c->PlayAnimation(0x265d18d, 1, -1);

    if (st->mp10 != 0)
        ((void(__fastcall*)(void*))(*(void***)st->mp10)[1])(st->mp10);
}

// @ 0x00d8f560
float __cdecl FUN_00d8f560(cCreature_s00d8_e8d0* c, u32 a2, u32 a3, u32 flags, BehaviorStimuli* bs, u8* out)
{
    if (c->mbF90 == 0 || (flags & 0x40000) != 0)
        return 0.0f;

    const u32 kId = 0x564c368;
    void* mgr = FUN_00bc9b00(kId, (void*)0x00d7b310, c);
    int node = ((OrderManager*)mgr)->FindNode(kId, (void*)0x00d7b310, c);
    if (node != 0) {
        if (bs != 0)
            bs->GetAny();
        *out = 1;
        bs->mnStimulusID = (u32)node;
        return 1.0f;
    }

    double r = ((RandomLCG*)0x01601760)->UniformDouble();
    if (r <= 0.25) {
        CreatureContext* ctx = c->Get();
        void* set = (void*)(((ctx->mn15C != 7) ? 0u : 0x26u) + 0x564c4afu);
        FUN_00b3d4e0(set, 0);
        int* vec = (int*)FUN_00bc7610(set, 0);
        if (vec[0] != vec[1]) {
            void* pos = ctx->GetPosition();
            void* tod = FUN_00bc30b0(pos);
            int height = ((TimeOfDay*)tod)->Get();
            u32 hi = *(u32*)((char*)ctx + 0x44);
            u32 lo = *(u32*)((char*)ctx + 0x40);
            u32 mask = c->FUN_c0b7a0() ? 1u : 0u;
            if (c->FUN_c0b780())
                mask |= 2u;

            int n = (vec[1] - vec[0]) / 0x7b4;
            IntVec16 cand;
            cand.mpBegin = cand.mInline;
            cand.mpEnd   = cand.mInline;
            cand.mpCap   = cand.mInline + 16;
            for (int i = 0; i < n; ++i) {
                int entry = i * 0x7b4 + vec[0];
                if ((*(int*)(entry + 0x7a0) == 0 ||
                     *(int*)(entry + 0x7a0) == 2 - (height != 0 ? 1 : 0)) &&
                    *(int*)(entry + 4) <= (int)((hi - lo) >> 2) &&
                    (*(u32*)(entry + 0x7a8) == 0 ||
                     (mask & *(u32*)(entry + 0x7a8)) != 0)) {
                    cand.push_back(i);
                }
            }

            if (cand.mpBegin != cand.mpEnd) {
                u32 cnt = (u32)(cand.mpEnd - cand.mpBegin);
                u32 pick = ((RandomLCG*)0x01601760)->UniformU32(cnt);
                void* chosen = (void*)cand.mpBegin[pick];
                if (bs != 0)
                    bs->GetAny();
                bs->mp18 = chosen;
                bs->mp1C = set;
                *out = 1;
                cand.Release();
                return 1.0f;
            }
            cand.Release();
        }
        return 0.0f;
    }
    return 0.0f;
}

// @ 0x00d9c9c0
bool __cdecl EAT_BUNDLE_Tick(cSPCreatureBase_s00d9_bee0* c, int, int, int, int, EAT_BUNDLE_state* s, bool* out)
{
    switch (s->mState) {
    case 0:
        if (c->mLoco_c0.IsNearGoal()) {
            void* t = s->mpTarget ? (void*)((u8*)s->mpTarget + 0x34) : 0;
            s->mAnimHandle = c->PlayAnimationWithTarget(0x7204469e, t, -1, -1);
            s->mState = 1;
        }
        break;
    case 1:
        if (c->AnimationFinished(s->mAnimHandle)) {
            void* t = s->mpTarget ? (void*)((u8*)s->mpTarget + 0x34) : 0;
            s->mAnimHandle = c->PlayAnimationWithTarget(0x720446a7, t, -1, -1);
            s->mState = 2;
            return true;
        }
        break;
    case 2:
        if (c->AnimationFinished(s->mAnimHandle)) {
            Vec3_s00d9_bee0 pos = *s->mpTarget->mLoco_34.GetPosition();
            ((cAgentOrderManager*)FUN_00b3d2b0(s->mpTarget, s->mpTarget->mField_128))->FUN_00ac79e0();
            if (s->mpTarget != 0) {
                cEatTarget* old = s->mpTarget;
                s->mpTarget = 0;
                old->Release();
            }
            ((cAgentOrderManager*)FUN_00b3d4c0_s00d9_bee0(3, (u8*)c + 0xb28, c))->FUN_00ba48b0();
            s->mAnimHandle = c->PlayAnimationWithTargetPos(0xd20446b0, &pos, -1);
            s->mState = 3;
            return true;
        }
        break;
    case 3:
        if (c->AnimationFinished(s->mAnimHandle)) {
            s->mState = 4;
            return true;
        }
        break;
    case 4:
        return false;
    }
    return true;
}
