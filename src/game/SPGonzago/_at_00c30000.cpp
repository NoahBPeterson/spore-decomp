// src/game/SPGonzago/_at_00c30000.cpp -- migrated from slice(s) s00c3ee20, s00c3daa0, s00c368c0, s00c35810 by tools/migrate/rewrite.py
// Object file: SPGonzago/_at_00c30000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cGameData.h"
#include "SP/cSpatialObject.h"
#include "SP/cVarListSerializer.h"
#include "SP/cEmpire.h"
#include "SP/cGameBundle.h"

// unnamed retail callees and globals (address in the comment)
extern float g_Zero15812d0;      // 0x015812d0
extern float g_Zero15812d4;      // 0x015812d4
extern float g_Zero15812d8;      // 0x015812d8
extern float g_Zero15812dc;      // 0x015812dc
extern float g_Zero15812e0;      // 0x015812e0
extern float g_kThreeTenths;     // 0x013eb8c8   0.3
extern float g_kTwoHundredths;   // 0x013ef580   0.02
extern float g_kSixTenths;       // 0x013ec4b0   0.6
extern float g_kFive;            // 0x01486110   5.0
extern float g_kTen;             // 0x01473c70   10.0
extern float g_kTwentyFive;      // 0x013ebc5c   25.0
extern float g_kFifty;           // 0x013f1cac   50.0
extern float g_kOne;             // 0x01485720   1.0
extern float g_f168df38;         // 0x0168df38
extern float g_f168df3c;         // 0x0168df3c
extern float g_f168df40;         // 0x0168df40
extern float g_f1581338;         // 0x01581338
extern float g_f15812f4;         // 0x015812f4
extern float g_f15812f8;         // 0x015812f8
extern float g_f13ec4b8;         // 0x013ec4b8  (epsilon)
extern float g_f13ec5b4;         // 0x013ec5b4
extern void* g_p157a1f8;         // 0x0157a1f8
extern void* g_p1573038;         // 0x01573038
extern uint8_t g_p146b998[];     // 0x0146b998  vtbl cGameBundle
extern uint8_t g_p146b984[];     // 0x0146b984
extern uint8_t g_p146b8c0[];     // 0x0146b8c0
extern uint8_t g_p146b8a0[];     // 0x0146b8a0
extern uint8_t g_p146ba68[];     // 0x0146ba68
extern uint8_t g_p146ba58[];     // 0x0146ba58
extern uint8_t g_p146bac0[];     // 0x0146bac0
extern void* g_p15816b8;         // 0x015816b8
extern const wchar_t g_wcGameBundleContainer[];  // 0x0146b874
extern uint8_t g_p16dda8c[];     // 0x016dda8c  background-sim manager global
extern float g_f168df28;         // 0x0168df28
extern float g_f168df2c;         // 0x0168df2c
extern float g_f168df30;         // 0x0168df30
#include <math.h>
#include "SP/cBehaviorTreeData.h"
#include "SP/cCombatant.h"
#include "SP/cLocomotiveObject.h"
#include "SP/cPlanetModel.h"
#include "SP/cSPGameDataUFO.h"
#include <stdlib.h>

// ---- items of slice s00c35810 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float g_Zero15812d0;      // 0x015812d0
extern float g_Zero15812d4;      // 0x015812d4
extern float g_Zero15812d8;      // 0x015812d8
extern float g_Zero15812dc;      // 0x015812dc
extern float g_Zero15812e0;      // 0x015812e0
extern float g_kThreeTenths;     // 0x013eb8c8   0.3
extern float g_kTwoHundredths;   // 0x013ef580   0.02
extern float g_kSixTenths;       // 0x013ec4b0   0.6
extern float g_kFive;            // 0x01486110   5.0
extern float g_kTen;             // 0x01473c70   10.0
extern float g_kTwentyFive;      // 0x013ebc5c   25.0
extern float g_kFifty;           // 0x013f1cac   50.0
extern float g_kOne;             // 0x01485720   1.0
extern float g_f168df38;         // 0x0168df38
extern float g_f168df3c;         // 0x0168df3c
extern float g_f168df40;         // 0x0168df40
extern float g_f1581338;         // 0x01581338
extern float g_f15812f4;         // 0x015812f4
extern float g_f15812f8;         // 0x015812f8
extern float g_f13ec4b8;         // 0x013ec4b8  (epsilon)
extern float g_f13ec5b4;         // 0x013ec5b4
extern void* g_p157a1f8;         // 0x0157a1f8
extern void* g_p1573038;         // 0x01573038
extern uint8_t g_p146b998[];     // 0x0146b998  vtbl cGameBundle
extern uint8_t g_p146b984[];     // 0x0146b984
extern uint8_t g_p146b8c0[];     // 0x0146b8c0
extern uint8_t g_p146b8a0[];     // 0x0146b8a0
extern uint8_t g_p146ba68[];     // 0x0146ba68
extern uint8_t g_p146ba58[];     // 0x0146ba58
extern uint8_t g_p146bac0[];     // 0x0146bac0
extern float g_f168df38;         // 0x0168df38
extern float g_f168df3c;         // 0x0168df3c
extern float g_f168df40;         // 0x0168df40
extern void* g_p15816b8;         // 0x015816b8
extern const wchar_t g_wcGameBundleContainer[];  // 0x0146b874
extern uint8_t g_p16dda8c[];     // 0x016dda8c  background-sim manager global
extern float g_f168df28;         // 0x0168df28
extern float g_f168df2c;         // 0x0168df2c
extern float g_f168df30;         // 0x0168df30
uint32_t __cdecl FUN_01021090();                     // 0x01021090 (GetPlayerEmpireID)
void*   __cdecl FUN_0067dcc0();                      // 0x0067dcc0 (MessageServer)
uint32_t __cdecl FUN_00b3d2a0();                     // 0x00b3d2a0 (StarManager)
uint32_t __cdecl FUN_00b3d2b0();                     // 0x00b3d2b0
uint32_t __cdecl FUN_00b3d300();                     // 0x00b3d300 (NounManager)
uint32_t __cdecl FUN_00ac8730(void* p);              // 0x00ac8730
uint32_t __cdecl FUN_00baf630(uint32_t a);           // 0x00baf630
uint32_t __cdecl FUN_00ba5bc0(void* a, uint32_t b);  // 0x00ba5bc0
uint32_t __cdecl FUN_00c70150(void* obj, void* emp, uint32_t c); // 0x00c70150
uint32_t __cdecl FUN_00c34ee0(void* a, uint32_t b);  // 0x00c34ee0
uint32_t __cdecl FUN_00c316c0(void* self, void* planet); // 0x00c316c0
uint32_t __stdcall FUN_00b3d350(uint32_t a, uint32_t b); // 0x00b3d350 (PlanetModel)
void*    __cdecl FUN_00f473a0(uint32_t size, const char* tag, uint32_t a, uint32_t b, uint32_t c, uint32_t d); // 0x00f473a0 operator new
void*    __cdecl FUN_0067ddd0();                      // 0x0067ddd0 (EffectsManagerPtr)
void     __cdecl FUN_00c36300(void* self);            // 0x00c36300
class cEmpire {
public:
    uint8_t  pad00[0x70];
    uint32_t* mAlliesBegin;   // +0x70
    uint32_t* mAlliesEnd;     // +0x74
    uint8_t  pad78[0x84 - 0x78];
    uint32_t mEmpireId;       // +0x84
    uint32_t* mStarsBegin;    // +0x88
    uint32_t* mStarsEnd;      // +0x8c
    uint8_t  pad90[0xb0 - 0x90];
    uint32_t mFieldB0;        // +0xb0
    uint32_t mCommContext;    // +0xb4

    uint32_t Remove(void* planet);   // 0x00c35810
};
class cGameBundle {
public:
    void*    mpVtbl;       // +0x00
    void*    mpVtbl2;      // +0x04
    uint8_t  pad08[0x2c - 0x08];
    void*    mpOwner;      // +0x2c  (owned object with vtbl[1] dtor)
    uint8_t  pad30[0x34 - 0x30];
    uint8_t  mSpatial[0x108 - 0x34];   // cSpatialObject at +0x34
    uint8_t  mInteract[0x120 - 0x108]; // cInteractionTarget at +0x108
    void*    mpField120;   // +0x120
    uint8_t  mField124;    // +0x124
    uint8_t  pad125[3];
    void*    mpField128;   // +0x128
    uint32_t mField12c;    // +0x12c
    uint32_t mField130;    // +0x130
    float    mField134;    // +0x134
    uint8_t  mField138;    // +0x138

    cGameBundle* Ctor();                                   // 0xc35dc0
    void  Dtor();                                          // 0xc35f70
    void  Write(uint32_t s);                               // 0xc35c60
    void  Read(uint32_t s);                                // 0xc35cb0
    uint32_t GetFieldValues(uint32_t s);                   // 0xc35e70
    void  Reset128And2c();                                 // 0xc35fe0
    void  Set12c134(uint32_t a, float f);                  // 0xc35b20
    uint32_t ComputeState();                               // 0xc35b60
    bool  IsState0Or4();                                   // 0xc35d20
    bool  IsState234();                                    // 0xc35d40
    void* CastTo(uint32_t key);                            // 0xc35ad0
};
class cGameBundleGroundContainer {
public:
    void*    mpVtbl;       // +0x00
    void*    mpVtbl2;      // +0x04
    uint8_t  pad08[0x2c - 0x08];
    void*    mpOwner2c;    // +0x2c  (owned object with vtbl[1] dtor)
    uint8_t  pad30[0x34 - 0x30];
    uint8_t  mSpatial[0x58 - 0x34]; // embedded object at +0x34
    float    mField58;     // +0x58
    void*    mpField5c;    // +0x5c

    cGameBundleGroundContainer* Ctor();                    // 0xc36510
    void*  CastTo(uint32_t key);                           // 0xc36560
    void   Init(uint32_t obj);                             // 0xc365a0
    void   Dtor2c();                                       // 0xc36690
    bool   Write(void* stream);                            // 0xc366c0
    bool   Read(void* stream);                             // 0xc36740
};
class cGameObj64 {
public:
    uint8_t pad00[0x64];
    void*   mpField64;     // +0x64
};
bool     __cdecl FUN_00c36870(cGameObj64* self, void* b);   // 0xc36870
bool     __cdecl FUN_00c364e0(void* a, void* b);          // 0xc364e0
void*    __stdcall FUN_00c365e0(void* param1, void* param2); // 0xc365e0
struct BaseGameData {                                   // SP::cGameData at +0
    void  Ctor();                                       // 0xb18660
    void  Dtor();                                       // 0xb184c0
    void  Write(uint32_t s);                            // 0xb18590
    void  Read(uint32_t s);                             // 0xb18600
    uint32_t WriteAsText(uint32_t s);                   // 0xb18420
    void  GetFieldValues(uint32_t s);                   // 0xb18550
};
struct BaseSpatial {                                    // SP::cSpatialObject at +0x34
    void  Ctor();                                       // 0xc89630
    void  Dtor();                                       // 0xc8a420
    void  Write(uint32_t s);                            // 0xc88a90
    void  Read(uint32_t s);                             // 0xc88b00
    void  Exit();                                       // 0xc8b2e0
    void  SetFloat(float f);                            // 0xc884a0
};
struct BaseInteract {                                   // SP::cInteractionTarget at +0x108
    void  Ctor();                                       // 0xac03d0
    void  Dtor();                                       // 0xac0450
    void  Reset();                                      // 0xac0520
};
struct GroundBase {                                     // embedded at ground +0x34
    void  Ctor();                                       // 0xcee630
    void  Dtor();                                       // 0xcee7e0
    bool  WriteObj(uint32_t stream);                    // 0xcee3d0
    bool  ReadObj(uint32_t stream);                     // 0xcee440
    uint32_t SetObj(uint32_t obj);                      // 0xcee250
    uint32_t InitObj(uint32_t obj, uint32_t a, float b, float c, int d); // 0xcee2c0
    float* GetDir();                                    // slot 11 (+0x2c)
    float* GetPos();                                    // slot 12 (+0x30)
    void   SetDir(const float* v);                      // slot 14 (+0x38)
    float  GetScalar();                                 // slot 13 (+0x34)
};
struct CallTarget0320 { void* Func(uint32_t key); };  // 0x00ac0320
struct CallTargetB18460 { void* Func(uint32_t key); }; // 0x00b18460
struct CallTargetC884f0 { void* Func(uint32_t key); }; // 0x00c884f0
struct CallTargetCEE250 { void* Func(uint32_t key); }; // 0x00cee250
struct VObj {
    virtual void v0();
    virtual void v1();   // slot 1 (+0x04)
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();   // slot 7 (+0x1c)
};
struct SerObj {
    void     Ctor(void* self, void* nameTbl, uint32_t hash);   // 0x692f90
    void     Serialize(uint32_t stream);                       // 0x692900
    void     Read(uint32_t stream);                            // 0x693e10
    uint32_t GetFields(uint32_t vec);                          // 0x695960
};
struct PlanetModelT { void DirToSurface(); };
struct C0B7C0 { uint8_t Pick(void* b); };   // 0x00c0b7c0 thiscall helper
struct C0AC79D0 { uint32_t Get(); };         // 0x00ac79d0 thiscall on FUN_00b3d2b0()
struct C0B25C30 { uint32_t Get(); };         // 0x00b25c30 thiscall on NounManager()
struct C0BFC5F0 { uint32_t Get(); };         // 0x00bfc5f0 thiscall on NounManager()
struct C0C88870 { void Base(); };            // 0x00c88870 thiscall base func
struct C0C90460 { uint32_t Test(); };        // 0x00c90460 thiscall test
struct Obj274 { uint8_t pad[0x274]; void* p274; };  // object exposing +0x274
struct C0EB0EA0 { void* Ctor(); };           // 0x00eb0ea0 cPlayerCityMusic ctor
struct C0EAB410 { void* Ctor(uint32_t kind); }; // 0x00eab410 ctor
struct C0C35320 { void PickRandomPersonality(); }; // 0x00c35320
struct C0B7F1F0 { void* Build(); };          // 0x00b7f1f0 BuildSurfaceOrientation
struct TagTarget { uint32_t Tag(void* obj, void* global, const wchar_t* name); }; // 0x00695b40
struct FF367E0 {
    void Apply(void* obj);
};
struct FF36030 {
    bool Test();   // 0x00c36030
};
struct FF360F0 {
    void Push();   // 0x00c360f0
};
struct FF359A0 {
    void Setup(void* star, uint8_t flag);   // 0x00c359a0
};
struct NounMgr {
    uint32_t ClassifyById(uint32_t id);   // 0x00b20790
    void*    GetFeedback(uint32_t id);    // 0x00b20750
};
struct StarMgr {
    void* GetPlayerStar();                // 0x00885c90
};
struct C0B8DE30v { uint32_t Run(); };        // thiscall on planet
struct C0BBA790v { uint32_t* Get(); };       // thiscall on star
struct C0CE6950v { uint32_t GetComm(); };    // thiscall GetCommContext
struct C01021AB0 { void Notify(void* obj); };// 0x01021ab0 thiscall on global
struct MsgSrv {
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
    void Emit4(uint32_t a, uint32_t b, uint32_t c, uint32_t d);  // slot 6 (+0x18)
};
struct EffMgr {
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
    uint8_t Acquire(uint32_t key, void** out, uint32_t c);  // slot 11 (+0x2c)
};
struct Spatial34 {
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
    float* GetPos();     // slot 11 (+0x2c)
    float* GetDir();     // slot 12 (+0x30)  -- direction quat
    float  GetScalar();  // slot 13 (+0x34)
    void   SetVal(const void*);  // slot 14 (+0x38)
};
struct Acquired {
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
    void Push(const void* v);   // slot 6 (+0x18)
};
// ---- items of slice s00c35810 end

// ---- items of slice s00c368c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int   u32;
typedef unsigned char  u8;
extern u32*        g_pBucketArr;   // 0x0152d6a0
extern u32         g_nBuckets;     // 0x0152d6a4
void*  __cdecl FUN_00f473a0(u32 size, const char* name, u32 a, u32 b, u32 c, u32 d);
void   __cdecl FUN_00f47380(void* p);
struct WStr {
  u32* mBegin;   // +0x00
  u32* mEnd;     // +0x04
  u32* mCap;     // +0x08
  void assign(u32* first, u32* last);            // 0x00423650
  void range_initialize(const wchar_t* str);     // 0x00579a90
};
WStr* __cdecl PathPick(WStr* out, WStr* prefix, WStr* suffix);   // 0x00688f00
void  __cdecl WStrFormat(WStr* out, const wchar_t* fmt, void* arg); // 0x0041e050
struct PtrVec {
  u32* mBegin;   // +0x00
  u32* mEnd;     // +0x04
  u32* mCap;     // +0x08
};
struct Loco {
  void* vtbl;              // +0x00  (ufo+0x34)
  void* Find(u32 key);                       // 0x00c41d00
  void  Set(void* p);                        // 0x00c421b0
  u8    Write(void* stream);                 // 0x00c448a0
};
struct Combat {
  void* vtbl;              // +0x00  (ufo+0x508)
  void* Find2(u32 key);                      // 0x00bfc380
  u8    Write(void* stream);                 // 0x00bfc4a0
};
struct Timer {
  u8 data[0x3c];                             // 0x00c37b8 sized subobject
  void Restart();                            // 0x00bc3130
};
struct Ufo {
  void*  vtbl;                 // +0x000
  u8     pad004[0x30];         // +0x004
  Loco   loco;                 // +0x034
  u32*   p38;                  // +0x038
  u8     pad03c[0x1c];         // +0x03c
  float  f58;                  // +0x058
  u32    idx5c;                // +0x05c
  u8     pad060[0x1a8];        // +0x060
  void*  p208;                 // +0x208
  u8     pad20c[0x2fc];        // +0x20c
  Combat combat;               // +0x508
  u8     pad50c[0x34];         // +0x50c
  float  f540;                 // +0x540
  u8     pad544[0x184];        // +0x544
  void*  p6c8;                 // +0x6c8
  u8     pad6cc[0x14];         // +0x6cc
  u32    u6e0;                 // +0x6e0
  u8     pad6e4[0x30];         // +0x6e4
  u32    state714;             // +0x714
  u8     pad718[0x4c];         // +0x718
  void*  p764;                 // +0x764
  u8     pad768[0x14];         // +0x768
  u8     b77c;                 // +0x77c
  u8     b77d;                 // +0x77d
  u8     b77e;                 // +0x77e
  u32    k780;                 // +0x780
  u32    k784;                 // +0x784
  u32    k788;                 // +0x788
  u8     b78c;                 // +0x78c
  u8     b78d;                 // +0x78d
  u8     pad78e[0x0a];         // +0x78e
  void*  p798;                 // +0x798
  void*  p79c;                 // +0x79c
  void*  p7a0;                 // +0x7a0
  void*  p7a4;                 // +0x7a4
  u8     pad7a8[0x08];         // +0x7a8
  void*  p7b0;                 // +0x7b0
  u8     pad7b4[0x04];         // +0x7b4
  Timer  timer;                // +0x7b8
  float  f7f4;                 // +0x7f4
  float  f7f8;                 // +0x7f8
};
struct ParamObj {
  void*  vtbl;                 // +0x000  (vtable of the source object)
  PtrVec vec;                  // +0x004
};
struct Big2 {
  void* init(void* owner);                // 0x00694e60
};
struct GroundContainer {
  u8     pad00[0x18];
  PtrVec list;                 // +0x018
  u8     pad24[0x08];          // +0x024
  WStr   name;                 // +0x02c
};
struct EAIter {
  u32 p0;                      // +0x00
  u32 p1;                      // +0x04
  u32 p2;                      // +0x08
  u32 p3;                      // +0x0c
};
struct EAHash {
  EAIter find(const u32& key);            // 0x00645ed0
};
void __stdcall WaitingList1_Insert(void* pos, void* value);   // 0x00690b80
void __stdcall FUN_00695b40(void* a, void* b, const wchar_t* c); // 0x00695b40
// ---- items of slice s00c368c0 end

// ---- items of slice s00c3daa0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float gF_13ec488;   // 0x013ec488  0.5f
extern float gF_1485720;   // 0x01485720  1.0f
extern float gF_13eb1bc;   // 0x013eb1bc  -1.0f
extern void* g_168e568;    // 0x0168e568
extern int   g_168e56c;    // 0x0168e56c
extern int   g_168e570;    // 0x0168e570
extern int   g_168e57c;    // 0x0168e57c  (dword guard, tested as byte)
void  __cdecl FUN_00c41d00(void*, int);                        // 0x00c41d00
void* __cdecl FUN_00b18460(int);                               // 0x00b18460
struct FnB184c0 { void __thiscall f(); };                      // 0x00b184c0 cGameData::~cGameData
struct FnA05270 { void __thiscall f(); };                      // 0x00a05270 cAnimatingCreature::Release
struct FnAbfec0 { void __thiscall f(); };                      // 0x00abfec0
struct FnBfcd00 { void __thiscall f(); };                      // 0x00bfcd00
struct FnAc0520 { void __thiscall f(); };                      // 0x00ac0520
struct FnC432e0 { void __thiscall f(); };                      // 0x00c432e0
struct FnA02c30 { void __thiscall f(); };                      // 0x00a02c30 cAnimatingCreature::AddRef
void* __cdecl FUN_00b18660(void*);                             // 0x00b18660 cGameData::cGameData
void  __cdecl FUN_00c43860(void*);                             // 0x00c43860
void  __cdecl FUN_00ac03d0(void*);                             // 0x00ac03d0 cInteractionTarget::cInteractionTarget
void  __cdecl FUN_00bfd4e0(void*);                             // 0x00bfd4e0 cCombatant::cCombatant
void  __cdecl FUN_00abfe50(void*);                             // 0x00abfe50
void* __cdecl FUN_00b18420(void*, void*);                      // 0x00b18420 cGameData::WriteAsText
void  __cdecl FUN_00692f90(void*, void*, void*, int);          // 0x00692f90 cVarListSerializer::cVarListSerializer
int   __cdecl FUN_00695960(void*, void*);                      // 0x00695960 cVarListSerializer::GetFields
bool  __cdecl FUN_00693e10(void*, void*);                      // 0x00693e10 Serialize(in)
bool  __cdecl FUN_00692900(void*, void*);                      // 0x00692900 Serialize(out)
void* __cdecl FUN_00b18600(void*, void*);                      // 0x00b18600 cGameData::Read
void* __cdecl FUN_00b18590(void*, void*);                      // 0x00b18590 cGameData::Write
void* __cdecl FUN_00c88a90(void*, void*);                      // 0x00c88a90 cSpatialObject::Write
void* __cdecl FUN_00c88b00(void*, void*);                      // 0x00c88b00
bool  __cdecl FUN_0093a780(void*, void*, int, int);            // 0x0093a780 ReadInt32
bool  __cdecl FUN_0093aa70(void*, void*, int, int);            // 0x0093aa70 WriteUint32
void* __cdecl FUN_00401090(void*);                             // 0x00401090 GetSetting
void* __cdecl FUN_004df440(void*);                             // 0x004df440 GetPlantProfile
struct C3eac0 { void* f(void* other); };                       // 0x00c3eac0
struct C3e510 { void* f(); };                                  // 0x00c3e510
struct C3e700 { void f(); };                                   // 0x00c3e700
struct C3e800 { void f(void* p); };                            // 0x00c3e800
struct C3e8e0 { void f(int* p); };                             // 0x00c3e8e0
struct Fn3e8e0 { void __thiscall f(void*); };                  // 0x00c3e8e0
// ---- items of slice s00c3daa0 end

// ---- items of slice s00c3ee20 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const void* sHitSphereFields;
typedef unsigned int uint;
#define nullptr 0
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
    virtual void* Query(const void* pType);   // 0x0c
    virtual void v10();
};
class IOStream {
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
    virtual IOStream* GetStream();         // 0x20
    virtual void GetStream2();             // 0x24
    virtual void ReadBlock(void* pDest, uint nCount);   // 0x34
};
class ISerializer {
public:
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void v0c();
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual void v1c();
    virtual bool Serialize(void* pData);
    virtual int GetFields(int nFlags);
    virtual IOStream* GetStream();
    virtual void ReadBlock(void* pDest, int nCount);
};
void WriteUint32(IOStream* pStream, void* pSource, int nCount, int bFlag);
class cVarListSerializer {
public:
    cVarListSerializer(void* pOwner, const void* pFields, int nFlags);
    bool Serialize(void* pData);
    int GetFields(int nFlags);
    uint8_t mPad00[0x414];
};
class cSpatialObject : public IRefCounted {
public:
    virtual void v14();
    virtual void v18();
    virtual void v1c();
    virtual void v20();
    virtual void v24();
    virtual void v28();
    virtual Vec3* GetPosition();          // 0x2c
    virtual Vec3* GetDirection();         // 0x30
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
    virtual void va8(int nState, int bA, int bB);   // 0xac
    virtual void* GetModel();                        // 0xb0
    virtual void vb4();
    virtual void vb8();
    virtual void vbc(int a);
    virtual void vc0();
    virtual bool vc4();

    Vec3 mPosition;                 // 0x04
    uint8_t mPad10[0x24];           // 0x10
    Vec3 mLocalExtentsMin;          // 0x34
    Vec3 mLocalExtentsMax;          // 0x40
    Vec3 mOriginalExtentsLower;     // 0x4c
    Vec3 mOriginalExtentsUpper;     // 0x58
    float mFootprintRadius;         // 0x64
    uint8_t mPad68[0x20];           // 0x68
    uint32_t mFlags;                // 0x88
    uint8_t mPad8c[0x18];           // 0x8c
    uint8_t mVisible;               // 0xa4
    uint8_t mHidden;                // 0xa5
    uint8_t mPadA6[0x87];           // 0xa6
    uint8_t mModelStateIndex;       // 0x12d
    uint8_t mPad12e[0x02];          // 0x12e
    uint8_t mModelReady;            // 0x130

    bool LoadModel(void* pModel);
    bool Write(void* pData);
};
class cGameData : public cSpatialObject {
public:
    bool Read(void* pData);
    bool Write(void* pData);
    bool Init(void* pData, int a, int b);
    int GetFieldValues(int nFlags);
    void RemoveOwner();
};
struct ModelKey {
    uint32_t typeID;                // 0x00
    uint32_t instanceID;            // 0x04
    uint32_t groupID;               // 0x08
};
class cOrnament : public cGameData {
public:
    uint8_t mPad54[0x1c0];
};
class cHitSphere : public cOrnament {
public:
    float mRadius;                  // 0x214
    float mMaxScreenSize;           // 0x218
    float mMinScreenSize;           // 0x21c
    float mMinDistance;             // 0x220
    float mMaxDistance;             // 0x224
    cGameData* mpDelegate;          // 0x228
    uint8_t mbKeepPinnedToPlanet;   // 0x22c

    cHitSphere();
    bool Write(void* pData);
    void* Cast(void* pType);
    int GetDelegateLowerBound(int nOffset);
};
class cSolarHitSphere : public cHitSphere {
public:
    ModelKey mModelKey;             // 0x230
    cSolarHitSphere();
};
class cGameplayMarker : public cGameData {
public:
    uint8_t mType;                  // 0x134
    uint8_t mPad135[0x03];          // 0x135
    uint32_t mId;                   // 0x138
    uint32_t mDefinitionId;         // 0x13c
    uint8_t mPad140[0x08];          // 0x140
    uint8_t mNounData[0xa00];       // 0x148
    uint8_t mPadB48[0x20];          // 0xb48
    IRefCounted* mpTriggerA;        // 0xb68
    IRefCounted* mpTriggerB;        // 0xb6c
    IRefCounted* mpUseNounTriggers; // 0xb70
    IRefCounted* mpNextMarker;      // 0xb74

    cGameplayMarker();
    void Destroy(int bDelete);
    void Shutdown();
    bool Read(void* pData);
    bool InitFromDefinition(void* pData, int a, int b);
};
class cInteractableObject : public cGameData {
public:
    uint8_t mPad134[0x50];          // 0x134
    uint64_t mDefinitionWord;       // 0x184
    uint32_t mModelId;              // 0x18c
    uint32_t mOrnamentId;           // 0x190
    float mScale;                   // 0x194
    uint8_t mPad198[0x14];          // 0x198
    IRefCounted* mpOwner;           // 0x1ac
    uint32_t mEffectState;          // 0x1b0
    uint8_t mPad1b4[0x08];          // 0x1b4

    cInteractableObject();
    bool Write(void* pData);
    bool Read(void* pData);
    int GetFieldValues(int nFlags);
    void SetEffectId(int nEffectId);
    bool LoadModelChecked(void* pModel);
    void SetModelState(int nState, bool bForce);
    bool InitFromDefinition(void* pData, int a, uint flags);
    void Destroy(int bDelete);
    void Shutdown();
    void AttachEffect(void* pEffect);
    void ClearEffectState();
};
void* CastOrnamentBase(void* pObject);
void RemoveOwnerExtra();
void operator_delete__(void* pMemory);
void ResetOrnamentList(void* pOwner);
void ResetInteractableState(void* pOwner);
void FreeGameDataMembers();
void FreeInteractableInherited();
// ---- items of slice s00c3ee20 end

// @ 0x00c35810
uint32_t cEmpire::Remove(void* planet)
{
    if (planet == 0)
        return 0;
    if (mEmpireId == FUN_01021090())
        ((C01021AB0*)g_p16dda8c)->Notify(planet);

    uint32_t star = ((C0B8DE30v*)planet)->Run();
    uint32_t found = 0;
    uint32_t* vec = ((C0BBA790v*)star)->Get();
    int32_t n = (int32_t)(((int32_t)vec[1] - (int32_t)vec[0]) >> 2);
    if (n > 0)
    {
        uint32_t* data = (uint32_t*)vec[0];
        for (int32_t i = 0; i < n; i++)
        {
            uint32_t c = data[i];
            if (c != (uint32_t)planet && c != 0 &&
                FUN_00c70150((void*)(uint32_t)c, this, 0))
            {
                found = c;
                break;
            }
        }
    }

    uint32_t ctx = ((C0CE6950v*)planet)->GetComm();
    if (ctx == mCommContext)
    {
        if (found == 0 &&
            (uint32_t)(((char*)mStarsEnd - (char*)mStarsBegin)) == 4)
            FUN_00ba5bc0(this, 6);
        mCommContext = (uint32_t)-1;
        mFieldB0 = (uint32_t)-1;
        typedef uint32_t (__cdecl* FnSM)(uint32_t, uint32_t);
        uint32_t sm = ((FnSM)FUN_00b3d2a0)(mEmpireId, 0);
        FUN_00baf630(sm);
        MsgSrv* ms = (MsgSrv*)FUN_0067dcc0();
        ms->Emit4(0x43f2586, 0, 0, 0);
    }

    uint32_t pid = FUN_01021090();
    int32_t an = (int32_t)(((int32_t)mAlliesEnd - (int32_t)mAlliesBegin) >> 2);
    if (an > 0)
    {
        for (int32_t k = 0; k < an; k++)
        {
            if (mAlliesBegin[k] == pid)
            {
                MsgSrv* ms = (MsgSrv*)FUN_0067dcc0();
                ms->Emit4(0x43f2585, 0, 0, 0);
                break;
            }
        }
    }

    if (found != 0)
    {
        if (mCommContext == (uint32_t)-1)
            FUN_00c316c0(this, (void*)(uint32_t)found);
        return 1;
    }
    return FUN_00c34ee0(this, 1);
}

// @ 0x00c359a0
void FF359A0::Setup(void* star, uint8_t flag)
{
    *(void**)((char*)this + 0x84) = star;
    NounMgr* nm = (NounMgr*)FUN_00b3d300();

    void* picked = 0;
    if (flag)
    {
        if (nm->ClassifyById((uint32_t)star) == 4)
        {
            void* fb = nm->GetFeedback((uint32_t)star);
            if (fb)
            {
                typedef void* (__thiscall* FnCast)(void*, uint32_t);
                void* o = ((FnCast)(*(void***)fb)[3])(fb, 0x901f1362);
                picked = *(void**)((char*)o + 0x274);
            }
            else
            {
                picked = ((Obj274*)0)->p274;
            }
        }
        else
        {
            void* p = FUN_00f473a0(0x220, "Simulator", 0, 0, 0, 0);
            if (p)
                picked = ((C0EB0EA0*)p)->Ctor();
        }
    }
    else
    {
        void* pl = ((StarMgr*)FUN_00b3d2a0())->GetPlayerStar();
        if (pl == *(void**)((char*)this + 0x84))
        {
            void* p = FUN_00f473a0(0x28, "Simulator", 0, 0, 0, 0);
            if (p)
                picked = ((C0EAB410*)p)->Ctor(4);
        }
        else
        {
            void* p = FUN_00f473a0(0x28, "Simulator", 0, 0, 0, 0);
            if (p)
                picked = ((C0EAB410*)p)->Ctor(3);
        }
    }

    void* old = *(void**)((char*)this + 0x104);
    if (picked != old)
    {
        if (picked)
            ((VObj*)picked)->v0();
        *(void**)((char*)this + 0x104) = picked;
        if (old)
            ((VObj*)old)->v1();
    }
    *(uint32_t*)((char*)this + 0x50) |= 0x10;
    if (flag)
    {
        *(uint32_t*)((char*)this + 0x50) |= 0x44;
        *(uint32_t*)((char*)this + 0x58) = 0x11;
        return;
    }
    ((C0C35320*)this)->PickRandomPersonality();
}

// @ 0x00c35ad0
void* cGameBundle::CastTo(uint32_t key)
{
    if (key == 0x4ffcdeda)
        return this;
    void* r = ((CallTarget0320*)mInteract)->Func(key);
    if (r)
        return r;
    r = ((CallTargetB18460*)this)->Func(key);
    if (r)
        return r;
    return ((CallTargetC884f0*)mSpatial)->Func(key);
}

// @ 0x00c35b20
void cGameBundle::Set12c134(uint32_t a, float f)
{
    mField12c = a;
    mField134 = f;
}

// @ 0x00c35b60
uint32_t cGameBundle::ComputeState()
{
    if (mField130 == 0)
    {
        float base = g_Zero15812d0;
        switch (mField12c)
        {
        case 1: base = g_Zero15812d4; break;
        case 2: base = g_Zero15812d8; break;
        case 3: base = g_Zero15812dc; break;
        case 4: base = g_Zero15812e0; break;
        }
        float v = mField134;
        if (base * g_kThreeTenths <= v)
        {
            if (base * g_kSixTenths <= v)
                return 3;
            return 2;
        }
        if (base * g_kTwoHundredths <= v)
            return 1;
        return 0;
    }
    if (mField124 != 0)
        return 6;
    float v = mField134;
    if (g_kFive <= v)
    {
        if (g_kTen <= v)
        {
            if (g_kTwentyFive <= v)
            {
                if (g_kFifty <= v)
                    return 5;
                return 4;
            }
            return 3;
        }
        return 2;
    }
    return 1;
}

// @ 0x00c35c60
void cGameBundle::Write(uint32_t s)
{
    char buf[0xa14];
    ((BaseSpatial*)mSpatial)->Write(s);
    ((BaseGameData*)this)->Write(s);
    ((SerObj*)buf)->Ctor(this, &g_p1573038, 0x1a80d26);
    ((SerObj*)buf)->Serialize(s);
}

// @ 0x00c35cb0
void cGameBundle::Read(uint32_t s)
{
    char buf[0xa14];
    ((BaseSpatial*)mSpatial)->Read(s);
    ((BaseGameData*)this)->Read(s);
    ((SerObj*)buf)->Ctor(this, &g_p1573038, 0x1a80d26);
    ((SerObj*)buf)->Serialize(s);
}

// @ 0x00c35d20
bool cGameBundle::IsState0Or4()
{
    int32_t s = (int32_t)mField12c;
    return (s >= 0 && (s <= 1 || s == 4)) ? true : false;
}

// @ 0x00c35d40
bool cGameBundle::IsState234()
{
    return (uint32_t)(mField12c - 2) <= 2U;
}

// @ 0x00c35d90
bool FUN_00c35d90(void* self, void** obj)
{
    if (*obj)
        ((TagTarget*)self)->Tag(*obj, &g_p15816b8, g_wcGameBundleContainer);
    return true;
}

// @ 0x00c35dc0
cGameBundle* cGameBundle::Ctor()
{
    ((BaseGameData*)this)->Ctor();
    ((BaseSpatial*)mSpatial)->Ctor();
    ((BaseInteract*)mInteract)->Ctor();
    mpVtbl   = g_p146b998;
    mpVtbl2  = g_p146b984;
    *(void**)mSpatial  = g_p146b8c0;
    *(void**)mInteract = g_p146b8a0;
    mpField120 = 0;
    mField124  = 0;
    mpField128 = 0;
    mField130  = 0;
    mField138  = 0;
    *(uint8_t*)((char*)this + 0xa4) = 0;
    ((BaseSpatial*)mSpatial)->SetFloat(g_f1581338);
    return this;
}

// @ 0x00c35e70
uint32_t cGameBundle::GetFieldValues(uint32_t s)
{
    struct Ser { uint8_t b[0xa14]; };

    uint32_t a = ((BaseGameData*)this)->WriteAsText(s);
    Ser serHi;
    Ser serLo;
    ((SerObj*)&serHi)->Ctor(mSpatial, &g_p157a1f8, 0x1a80d26);
    a += ((SerObj*)&serHi)->GetFields(s);
    ((SerObj*)&serLo)->Ctor(this, &g_p1573038, 0x1a80d26);
    uint32_t c = ((SerObj*)&serLo)->GetFields(s);
    return c + a;
}

// @ 0x00c35f70
void cGameBundle::Dtor()
{
    mpVtbl  = g_p146b998;
    mpVtbl2 = g_p146b984;
    *(void**)mSpatial  = g_p146b8c0;
    *(void**)mInteract = g_p146b8a0;
    void* p128 = mpField128;
    if (p128)
        ((VObj*)p128)->v7();
    if (mpField120)
        ((VObj*)mpField120)->v1();
    ((BaseInteract*)mInteract)->Reset();
    ((BaseSpatial*)mSpatial)->Dtor();
    ((BaseGameData*)this)->Dtor();
}

// @ 0x00c35fe0
void cGameBundle::Reset128And2c()
{
    if (mpField128)
    {
        void* p = mpField128;
        mpField128 = 0;
        ((VObj*)p)->v7();
    }
    ((BaseInteract*)mInteract)->Dtor();
    if (mpOwner)
    {
        void* p = mpOwner;
        mpOwner = 0;
        ((VObj*)p)->v1();
    }
    ((BaseSpatial*)mSpatial)->Exit();
}

// @ 0x00c36030
bool FF36030::Test()
{
    void* p = *(void**)((char*)this + 0xf4);
    if (p == 0)
        return false;
    void* q = *(void**)((char*)p + 0x18);
    if (q == 0)
        return false;
    typedef uint8_t (__thiscall* FnA)(void*);
    if (((FnA)(*(void***)q)[11])(q) != 0)
        return false;

    void* p2 = *(void**)((char*)this + 0xf4);
    if (p2 == (void*)(uint32_t)((C0AC79D0*)FUN_00b3d2b0())->Get())
        return true;

    void* owned = *(void**)((char*)p + 0x18);
    typedef void* (__thiscall* FnC)(void*, uint32_t);
    void* t = owned ? ((FnC)(*(void***)owned)[3])(owned, 0xee9b2232) : 0;
    void* u = (void*)(uint32_t)((C0B25C30*)FUN_00b3d300())->Get();
    if (t != 0 && u != 0)
        return t == u;

    void* owned2 = *(void**)((char*)p + 0x18);
    void* g = (void*)(uint32_t)FUN_00ac8730(owned2);
    void* h = (void*)(uint32_t)((C0BFC5F0*)FUN_00b3d300())->Get();
    if (g != 0 && h != 0)
        return g == h;
    return false;
}

// @ 0x00c360f0
void FF360F0::Push()
{
    typedef float* (__thiscall* FnDir)(void*);
    typedef void  (__thiscall* FnSet)(void*, const float*);

    ((C0C88870*)this)->Base();   // 0x00c88870

    void* owned = *(void**)((char*)this + 0xf4);
    if (owned == 0)
        return;
    typedef void* (__thiscall* FnCast)(void*, uint32_t);
    void* obj = ((FnCast)(*(void***)owned)[5])(owned, 0x4f396a66);
    if (obj == 0)
        return;

    float scale = g_f15812f4;
    if (((C0C90460*)obj)->Test() != 0)
        scale = g_f15812f8;
    else
    {
        typedef uint32_t (__thiscall* FnId)(void*);
        uint32_t e = ((FnId)(*(void***)obj)[19])(obj);
        if (e == FUN_01021090())
            scale = g_f15812f8;
    }

    float* d = ((FnDir)(*(void***)this)[11])(this);
    float inv = (float)(1.0 / sqrt((double)(d[0] * d[0] + d[1] * d[1] + d[2] * d[2] + g_f13ec4b8)));
    float sx = d[0] * inv * scale;
    float sy = d[1] * inv * scale;
    float sz = d[2] * inv * scale;
    float* pos = ((FnDir)(*(void***)this)[11])(this);
    float out[3];
    out[0] = pos[0] + sx;
    out[1] = pos[1] + sy;
    out[2] = pos[2] + sz;
    ((FnSet)(*(void***)this)[14])(this, out);
}

// @ 0x00c36300
void FUN_00c36300(void* self)
{
    void* held = 0;
    EffMgr* em = (EffMgr*)FUN_0067ddd0();
    if (held)
    {
        void* p = held;
        held = 0;
        ((VObj*)p)->v1();
    }
    if (em->Acquire(0xd6276f0c, &held, 0) == 0)
    {
        if (held)
            ((VObj*)held)->v2();
        return;
    }

    Spatial34* base = (Spatial34*)((char*)self + 0x34);
    float* q = base->GetDir();
    float quat[4];
    quat[0] = q[0]; quat[1] = q[1]; quat[2] = q[2]; quat[3] = q[3];
    float* pf = base->GetPos();
    float pos[3];
    pos[0] = pf[0]; pos[1] = pf[1]; pos[2] = pf[2];

    void* pm = (void*)FUN_00b3d350((uint32_t)pos, (uint32_t)quat);
    void* orient = ((C0B7F1F0*)pm)->Build();
    (void)orient;
    float scalar = base->GetScalar();
    (void)scalar;

    // build the surface vector record and hand it to the acquired sink
    float rec[6];
    rec[0] = g_f168df28;
    rec[1] = g_f168df2c;
    rec[2] = g_f168df30;
    rec[3] = g_kOne;
    rec[4] = scalar;
    rec[5] = 0.0f;
    ((Acquired*)held)->Push(rec);
    if (held)
        ((VObj*)held)->v2();
}

// @ 0x00c364e0
bool FUN_00c364e0(void* a, void* b)
{
    uint32_t v = 0;
    void* p = *(void**)b;
    if (p != 0)
    {
        typedef uint32_t (__thiscall* Fn)(void*, uint32_t);
        v = ((Fn)(*(void***)p)[5])(p, 0x179c807);
    }
    typedef void (__thiscall* Fn2)(void*, uint32_t);
    ((Fn2)(*(void***)a)[11])(a, v);
    return true;
}

// @ 0x00c36510
cGameBundleGroundContainer* cGameBundleGroundContainer::Ctor()
{
    ((BaseGameData*)this)->Ctor();
    ((GroundBase*)mSpatial)->Ctor();
    *(void**)mSpatial = g_p146bac0;
    mpVtbl  = g_p146ba68;
    mpVtbl2 = g_p146ba58;
    mField58 = 0.0f;
    mpField5c = 0;
    return this;
}

// @ 0x00c36560
void* cGameBundleGroundContainer::CastTo(uint32_t key)
{
    void* r = this;
    if (key != 0xeef202b7)
    {
        r = ((CallTargetB18460*)this)->Func(key);
        if (!r)
            r = ((CallTargetCEE250*)mSpatial)->Func(key);
    }
    return r;
}

// @ 0x00c365a0
void cGameBundleGroundContainer::Init(uint32_t obj)
{
    ((GroundBase*)mSpatial)->InitObj(obj, 1000, g_f13ec5b4, 0.0f, 1);
    ((BaseGameData*)this)->GetFieldValues(obj);
}

// @ 0x00c365e0
void* __stdcall FUN_00c365e0(void* param1, void* param2)
{
    typedef float* (__thiscall* FnDir)(void*);
    void* base = (char*)param2 + 0x34;
    float* p = ((FnDir)(*(void***)base)[11])(base);
    void* pm = (void*)FUN_00b3d350((uint32_t)param1, (uint32_t)p);
    ((PlanetModelT*)pm)->DirToSurface();
    return param1;
}

// @ 0x00c36690
void cGameBundleGroundContainer::Dtor2c()
{
    ((GroundBase*)mSpatial)->Dtor();
    if (mpOwner2c)
    {
        void* p = mpOwner2c;
        mpOwner2c = 0;
        ((VObj*)p)->v1();
    }
}

// @ 0x00c367e0
void FF367E0::Apply(void* obj)
{
    typedef float* (__thiscall* FnDir)(void*);
    typedef void (__thiscall* FnSet)(void*, const float*);
    void* base = (char*)obj + 0x34;
    float* f = ((FnDir)(*(void***)base)[11])(base);
    if (f[0] == g_f168df38 && f[1] == g_f168df3c && f[2] == g_f168df40)
    {
        float v[3];
        v[0] = g_kOne;
        v[1] = 0.0f;
        v[2] = 0.0f;
        ((FnSet)(*(void***)base)[14])(base, v);
    }
    typedef void (__thiscall* Fn30)(void*, void*);
    ((Fn30)(*(void***)this)[12])(this, obj);
}

// @ 0x00c36870
bool FUN_00c36870(cGameObj64* a, void* b)
{
    if (a->mpField64 && (C0B7C0*)a->mpField64)
    {
        typedef void* (__thiscall* Fn)(void*, uint32_t);
        void* r = ((Fn)(*(void***)a->mpField64)[3])(a->mpField64, 0xd0036e08);
        if (r && *(uint8_t*)((char*)r + 0xb5e) == 0 &&
            *(uint8_t*)((char*)r + 0x135) != 0 && b)
        {
            if (((C0B7C0*)r)->Pick(b))
                return true;
        }
    }
    return false;
}

// @ 0x00c368c0
u8 __fastcall FUN_00c368c0(Ufo* self, void* dummy, ParamObj* param)
{
  (void)dummy;
  u32 key = (u32)self;
  EAIter it = ((EAHash*)0x0152d69c)->find(key);
  if (it.p0 == g_pBucketArr[g_nBuckets]) {
    GroundContainer* gc;
    Big2* raw = (Big2*)FUN_00f473a0(0x74, "Simulator", 0, 0, 0, 0);
    if (raw == 0) gc = 0;
    else gc = (GroundContainer*)raw->init(self);

    WStr fmt;
    fmt.mBegin = (u32*)0x01667bac;
    fmt.mEnd = (u32*)0x01667bac;
    fmt.mCap = (u32*)0x01667bae;
    WStrFormat(&fmt, L" @ 0x%08x", self);

    WStr name;
    name.mBegin = 0;
    name.mEnd = 0;
    name.mCap = 0;
    name.range_initialize(L"cGameBundleGroundContainer");

    WStr path;
    path.mBegin = 0;
    path.mEnd = 0;
    path.mCap = 0;
    WStr* picked = PathPick(&path, &name, &fmt);
    if (picked != &gc->name) {
      gc->name.assign(picked->mBegin, picked->mEnd);
    }
    if ((((u32)path.mEnd - (u32)path.mBegin) & ~1u) > 2 && path.mBegin)
      FUN_00f47380(path.mBegin);
    if ((((u32)name.mEnd - (u32)name.mBegin) & ~1u) > 2 && name.mBegin)
      FUN_00f47380(name.mBegin);

    u32 v = (u32)param;
    if (gc->list.mEnd < gc->list.mCap) {
      *gc->list.mEnd = v;
      gc->list.mEnd++;
    } else {
      WaitingList1_Insert(gc->list.mEnd, &v);
    }

    u32 w = (u32)gc;
    if (param->vec.mEnd < param->vec.mCap) {
      *param->vec.mEnd = w;
      param->vec.mEnd++;
    } else {
      WaitingList1_Insert(param->vec.mEnd, &w);
    }

    if ((((u32)fmt.mEnd - (u32)fmt.mBegin) & ~1u) > 2 && fmt.mBegin)
      FUN_00f47380(fmt.mBegin);
  } else {
    u32* slot = (u32*)it.p0 + 1;
    u32 a = *slot;
    u32 v = (u32)a;
    if (param->vec.mEnd < param->vec.mCap) {
      *param->vec.mEnd = v;
      param->vec.mEnd++;
    } else {
      WaitingList1_Insert(param->vec.mEnd, &v);
    }
    GroundContainer* gc = (GroundContainer*)a;
    u32 w = (u32)param;
    if (gc->list.mEnd < gc->list.mCap) {
      *gc->list.mEnd = w;
      gc->list.mEnd++;
    } else {
      WaitingList1_Insert(gc->list.mEnd, &w);
    }
  }
  FUN_00695b40(self, (void*)0x01567e48, L"cGameData");
  FUN_00695b40(&self->loco, (void*)0x015816b8, L"cGameBundleContainer");
  return 1;
}

// @ 0x00c3e2c0
void* __cdecl FUN_00c3e2c0(void* self, int type)
{
    if ((unsigned)type < 0x11c0ba4) {
        if (type != 0x11c0ba3) {
            if (type == (int)0xaeb336b4 || type == (int)0xee3f516e) {
                return self;
            }
        } else {
            if (self != 0) return (char*)self + 0x5e8;
            return 0;
        }
    } else if (type == 0x13f94d4) {
        if (self != 0) return (char*)self + 0x520;
        return 0;
    } else if (type == 0x102a041a) {
        if (self != 0) return (char*)self + 0x504;
        return 0;
    }
    void* r = FUN_00b18460(type);
    if (r != 0) return r;
    FUN_00c41d00((char*)self + 0x34, type);
    return 0;
}

// @ 0x00c3e350
void __fastcall FUN_00c3e350(char* self)
{
    typedef void(__fastcall* Vf)(void*);
    ((Vf)(*(void**)(*(char**)(self + 0x34) + 0x2c)))(self + 0x34);
}

// @ 0x00c3e3b0
char __cdecl FUN_00c3e3b0(char* self, void* stream)
{
    char buf[8];
    char ser[0x18];  // cVarListSerializer (>=0x14)
    typedef void* (__thiscall* M0)(void*);
    void* s2 = ((M0)(*(void**)(*(char**)stream + 0x20)))(stream);
    typedef void* (__thiscall* M1)(void*);
    void* s3 = ((M1)(*(void**)(*(char**)s2 + 0x18)))(s2);
    *(int*)buf = (int)0xaeb336b4;
    FUN_0093aa70(s3, buf, 1, 0);
    char ok = (char)FUN_00b18590(self, stream);
    if (ok) {
        ok = (char)FUN_00c88a90(self + 0x34, stream);
        if (ok) ok = 1; else ok = 0;
    } else {
        ok = 0;
    }
    FUN_00692f90(ser, self, (void*)0x1573a60, 0x1a80d26);
    if (ok) {
        if (FUN_00692900(ser, stream)) {
            return 1;
        }
    }
    return 0;
}

// @ 0x00c3e460
float __fastcall FUN_00c3e460(char* self)
{
    float v = *(float*)(self + 0x640);
    if (v >= 0.0f) return v;
    return *(float*)(self + 0x5c);
}

// @ 0x00c3e490
int __cdecl FUN_00c3e490(char* self, void* stream)
{
    char serA[0x14];
    char serB[0x1414];
    int n = (int)FUN_00b18420(self, stream);
    FUN_00692f90(serA, self + 0x34, (void*)0x157a1f8, 0x1a80d26);
    n += FUN_00695960(serA, stream);
    FUN_00692f90(serB, self, (void*)0x1573a60, 0x1a80d26);
    n += FUN_00695960(serB, stream);
    return n;
}

// @ 0x00c3e510
void* C3e510::f()
{
    char* self = (char*)this;
    FUN_00b18660(self);
    char* p34 = self + 0x34;
    FUN_00c43860(p34);
    char* p504 = self + 0x504;
    FUN_00ac03d0(p504);
    char* p520 = self + 0x520;
    FUN_00bfd4e0(p520);
    FUN_00abfe50(self + 0x5e8);

    *(int*)(self) = 0x146c308;
    *(int*)(self + 4) = 0x146c2f4;
    *(int*)(p34) = 0x146c1f8;
    *(int*)(self + 0x108) = 0x146c1ec;
    *(int*)(p504) = 0x146c1d0;
    *(int*)(p520) = 0x146c168;
    *(int*)(self + 0x5e8) = 0x146c100;

    *(int*)(self + 0x650) = 0;
    *(int*)(self + 0x654) = 0;
    *(int*)(self + 0x658) = 0;
    *(int*)(self + 0x65c) = *(int*)0x168e5b0;
    *(int*)(self + 0x660) = *(int*)0x168e5b4;
    *(int*)(self + 0x668) = 0;
    *(int*)(self + 0x664) = *(int*)0x168e5b8;
    *(float*)(self + 0x66c) = gF_1485720;
    *(int*)(self + 0x670) = 0;
    *(uint8_t*)(self + 0xa3) = 0;
    *(float*)(self + 0x674) = gF_13eb1bc;
    *(float*)(self + 0x678) = gF_1485720;
    *(int*)(self + 0x88) = 2;
    *(uint8_t*)(self + 0xa5) = 1;
    return self;
}

// @ 0x00c3e700
void C3e700::f()
{
    char* self = (char*)this;
    char* p34 = self + 0x34;
    char* p504 = self + 0x504;
    char* p520 = self + 0x520;
    *(int*)(self) = 0x146c308;
    *(int*)(self + 4) = 0x146c2f4;
    *(int*)(p34) = 0x146c1f8;
    *(int*)(self + 0x108) = 0x146c1ec;
    *(int*)(p504) = 0x146c1d0;
    *(int*)(p520) = 0x146c168;
    *(int*)(self + 0x5e8) = 0x146c100;

    void* p = *(void**)(self + 0x670);
    if (p != 0) ((FnA05270*)p)->f();
    ((FnAbfec0*)(self + 0x5e8))->f();
    ((FnBfcd00*)p520)->f();
    ((FnAc0520*)p504)->f();
    ((FnC432e0*)p34)->f();
    ((FnB184c0*)self)->f();
}

// @ 0x00c3e800
void C3e800::f(void* p2)
{
    char* self = (char*)this;
    char* q = (char*)p2;
    char* old = *(char**)(self + 0x670);
    if (q != old) {
        if (q != 0) ((FnA02c30*)q)->f();
        *(char**)(self + 0x670) = q;
        if (old != 0) ((FnA05270*)old)->f();
    }
    if (q != 0) {
        float f = *(float*)(q + 0x3c);
        void* pIdx = *(void**)(q + 0x17c);
        void* v = *(void**)pIdx;
        float buf[6];
        buf[0] = (*(float*)((char*)v + 0x364) * f) * gF_13ec488;
        buf[1] = (*(float*)((char*)v + 0x368) * f) * gF_13ec488;
        buf[2] = 0.0f;
        buf[3] = -buf[0];
        buf[4] = -buf[1];
        buf[5] = *(float*)((char*)v + 0x36c) * f;

        char* sp = self + 0x34;
        void* sub = *(void**)sp;
        typedef float(__thiscall* G)(void*);
        float r = ((G)(*(void**)((char*)sub + 0x34)))(sp);
        typedef void(__thiscall* Vf)(void*, void*, float);
        ((Vf)(*(void**)((char*)sub + 0x64)))(sp, buf, r);
    }
}

// @ 0x00c3e8e0
void C3e8e0::f(int* p)
{
    char* self = (char*)this;
    if (*p != 0) {
        void* prof = FUN_004df440(FUN_00401090(p));
        *(void**)(self + 0x668) = prof;
        if (prof != 0) {
            char* pr = (char*)prof;
            float s = *(float*)(self + 0x66c);
            float x = (*(float*)(pr + 0x554) * 0.5f) * s;
            float y = (*(float*)(pr + 0x558) * 0.5f) * s;
            float buf[6];
            buf[0] = x;
            buf[1] = y;
            buf[2] = 0.0f;
            buf[3] = -y;
            buf[4] = -x;
            buf[5] = *(float*)(pr + 0x55c) * s;

            char* sp = self + 0x34;
            void* sub = *(void**)sp;
            typedef void(__thiscall* Vf)(void*, void*, float);
            ((Vf)(*(void**)((char*)sub + 0x64)))(sp, buf, 1.0f);
        }
    }
    *(int*)(self + 0x650) = p[0];
    *(int*)(self + 0x654) = p[1];
    *(int*)(self + 0x658) = p[2];
}

// @ 0x00c3e9d0
char __cdecl FUN_00c3e9d0(char* self, void* stream)
{
    char buf[4];
    char ser[0x18];
    typedef void* (__thiscall* M0)(void*);
    void* s2 = ((M0)(*(void**)(*(char**)stream + 0x20)))(stream);
    typedef void* (__thiscall* M1)(void*);
    void* s3 = ((M1)(*(void**)(*(char**)s2 + 0x18)))(s2);
    FUN_0093a780(s3, buf, 1, 0);

    char bl;
    if ((char)FUN_00b18600(self, stream)) {
        if ((char)FUN_00c88b00(self + 0x34, stream)) bl = 1;
        else bl = 0;
    } else bl = 0;

    FUN_00692f90(ser, self, (void*)0x1573a60, 0x1a80d26);
    if (bl) {
        if (FUN_00693e10(ser, stream)) bl = 1; else bl = 0;
    } else bl = 0;
    ((Fn3e8e0*)self)->f(self + 0x650);
    return bl;
}

// @ 0x00c3ea80
void* __cdecl FUN_00c3ea80()
{
    int one = 1;
    if (((char)g_168e57c & one) == 0) {
        g_168e57c |= one;
        g_168e568 = 0;
        g_168e56c = 0;
        g_168e570 = 0;
        atexit((void(__cdecl*)(void))0x13c3880);
    }
    return &g_168e568;
}

// @ 0x00c3eac0
void* C3eac0::f(void* other_)
{
    char* self = (char*)this;
    char* other = (char*)other_;
    *(int*)(self + 0x108) = *(int*)(other + 0x108);
    *(int*)(self + 0x10c) = *(int*)(other + 0x10c);
    *(int*)(self + 0x110) = *(int*)(other + 0x110);

    int* src = (int*)(other + 0x114);
    int* dst = (int*)(self + 0x114);
    for (int i = 0x22; i != 0; i--) *dst++ = *src++;

    char* oSub = *(char**)(other + 0x34);
    char* sSub = *(char**)(self + 0x34);
    typedef void* (__thiscall* G)(void*);
    typedef void  (__thiscall* S)(void*, void*);
    void* a = ((G)(*(void**)(oSub + 0x2c)))(other + 0x34);
    ((S)(*(void**)(sSub + 0x38)))(self + 0x34, a);
    oSub = *(char**)(other + 0x34);
    sSub = *(char**)(self + 0x34);
    void* b = ((G)(*(void**)(oSub + 0x30)))(other + 0x34);
    ((S)(*(void**)(sSub + 0x3c)))(self + 0x34, b);
    return self;
}

// @ 0x00c3f160
void cInteractableObject::SetEffectId(int nEffectId)
{
    ((void (*)(int))*(void**)(*(uint32_t*)((uint8_t*)this + 0x70) + 0x38))(nEffectId);
    *(uint32_t*)((uint8_t*)this + 0x238) = (uint32_t)nEffectId;
}

// @ 0x00c3f1d0
void* cGameplayMarkerCast(void* pObject, int nType)
{
    if (nType != 0x32f9777 && nType != 0x2e71a5a)
        return CastOrnamentBase(pObject);
    return pObject;
}

// @ 0x00c3f1f0
void cGameplayMarker::Destroy(int bDelete)
{
    if (mpNextMarker != nullptr)
        mpNextMarker->Release();
    if (mpUseNounTriggers != nullptr)
        mpUseNounTriggers->Release();
    if (mpTriggerB != nullptr)
        mpTriggerB->Release();
    if (mpTriggerA != nullptr)
        mpTriggerA->Release();
    if ((bDelete & 1) != 0)
        operator_delete__(this);
}

// @ 0x00c3f250
void cInteractableObject::Shutdown()
{
    ResetInteractableState(this);
    ResetOrnamentList(this);
    *(uint32_t*)((uint8_t*)this + 0x144) = 0x1466c14;
    FreeInteractableInherited();
    *(uint32_t*)((uint8_t*)this + 0x34) = 0x146c56c;
    if (mpOwner != nullptr)
        mpOwner->Release();
    if (*(IRefCounted**)((uint8_t*)this + 0x54) != nullptr)
        (*(IRefCounted**)((uint8_t*)this + 0x54))->Release();
    if (*(IRefCounted**)((uint8_t*)this + 0x50) != nullptr)
        (*(IRefCounted**)((uint8_t*)this + 0x50))->Release();
    if (*(IRefCounted**)((uint8_t*)this + 0x4c) != nullptr)
        (*(IRefCounted**)((uint8_t*)this + 0x4c))->Release();
    FreeGameDataMembers();
}

// @ 0x00c3f310
void cGameData::RemoveOwner()
{
    IRefCounted* pOwner = *(IRefCounted**)((uint8_t*)this + 0x2c);
    if (pOwner != nullptr) {
        *(IRefCounted**)((uint8_t*)this + 0x2c) = nullptr;
        pOwner->Release();
    }
    RemoveOwnerExtra();
}

// @ 0x00c3f340
bool cHitSphere::Write(void* pData)
{
    IOStream* pStream = ((ISerializer*)pData)->GetStream();
    uint32_t nType = 0x2e71a5a;
    WriteUint32(pStream->GetStream(), &nType, 1, 0);

    bool bOk = cGameData::Write(pData);
    if (bOk)
        bOk = cSpatialObject::Write(pData);

    if (mpDelegate != nullptr) {
        if (mpDelegate->Query(nullptr) != nullptr) {
            cGameData* pOld = mpDelegate;
            mpDelegate = nullptr;
            pOld->Release();
        }
    }

    cVarListSerializer serializer(this, sHitSphereFields, 0x1a80d26);
    if (bOk)
        return serializer.Serialize(pData);
    return false;
}

// @ 0x00c3f4a0
cHitSphere::cHitSphere()
{
    mRadius = 1.0f;
    mMaxScreenSize = 1.0f;
    mMinScreenSize = 0.0f;
    mMinDistance = 0.0f;
    mMaxDistance = 3.4028234e+38f;
    mpDelegate = nullptr;
    mbKeepPinnedToPlanet = false;
}

// @ 0x00c3f560
int cHitSphere::GetDelegateLowerBound(int nOffset)
{
    if (nOffset != 0x34)
        return nOffset + 0x3c;
    return 0;
}

// @ 0x00c3f6f0
cSolarHitSphere::cSolarHitSphere()
{
    mModelKey.typeID = 0;
    mModelKey.instanceID = 0;
    mModelKey.groupID = 0;
}
