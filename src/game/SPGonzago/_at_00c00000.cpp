// src/game/SPGonzago/_at_00c00000.cpp -- migrated from slice(s) s00c0ddb0, s00c053b0, s00c045a0, s00c035f0, s00bffad0 by tools/migrate/rewrite.py
// Object file: SPGonzago/_at_00c00000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cSPCreatureBase.h"
#include "SP/cVarListSerializer.h"
#include <math.h>
#include <intrin.h>
#include "SP/cPlanetModel.h"

// unnamed retail callees and globals (address in the comment)
extern uint32_t g_168d248;              // 0x0168d248  application mode (0..4)

// ---- items of slice s00bffad0 begin (TODO(rewrite): local stubs, replace by canonical classes)
void*    SP_GameTimeManager();                                          // 0x00b3d380
extern uint32_t g_168d248;              // 0x0168d248  application mode (0..4)
void  SP_Eapd_sys_gui();                // 0x00c2e4e0  empty in this build
struct cGameTimeMgr {                   // 0x00b316c0  Ticks() (thiscall, returns edx:eax)
    uint64_t Ticks();
};
// ---- items of slice s00bffad0 end

// ---- items of slice s00c035f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
int   __fastcall FUN_00bc9980(void*, float);             // 0xbc9980
uint64_t __fastcall FUN_00b316c0(void*);                 // 0xb316c0
void  __cdecl FUN_00d995f0(float, double, int, void*, void*, int, unsigned, int); // 0xd995f0
float __cdecl FUN_00d38a30(int, void*);                  // 0xd38a30
struct CreatureBase {
  char raw[0x1a00];

  // unnamed retail callees (bodies not needed: chk compiles to .obj only)
  void  FUN_00c222f0(void* p);                           // 0xc222f0
  void  SetB65(char v);                                  // 0xc0d950
  void  FUN_00c13eb0();                                  // 0xc13eb0
  void  FUN_00c21090();                                  // 0xc21090
  bool  FUN_00c0b770();                                  // 0xc0b770
  bool  FUN_00c0c130();                                  // 0xc0c130
  void* FUN_00c0ee60();                                  // 0xc0ee60
  void* FUN_00c0ee90();                                  // 0xc0ee90
  void  FUN_00c0cf50();                                  // 0xc0cf50
  void  FUN_00c0b710();                                  // 0xc0b710
  float FUN_00c0e4f0();                                  // 0xc0e4f0
  float FUN_00c0c010();                                  // 0xc0c010
  float FUN_00c0c040();                                  // 0xc0c040
  int   FUN_00c0b8d0();                                  // 0xc0b8d0
  void  FUN_00c0b370(int v);                             // 0xc0b370
  bool  FUN_00c0b780();                                  // 0xc0b780
  bool  FUN_00c0b7a0();                                  // 0xc0b7a0
  bool  Flag388();                                       // 0xc0c0e0
  void  FUN_00c0d240();                                  // 0xc0d240
  bool  SubACh(float f);                                 // 0xc1cc80 (funcACh overload, float)
  void  FUN_00c0bf10(int, int, int, int, float, int, int, int, int, unsigned, int); // 0xc0bf10
  bool  FUN_00c0bc20(void* stream);                      // 0xc0bc20

  // this slice's targets
  bool  func37C0(void* p, int unused, int flag);
  bool  funcC0h(void* other, float fA, float fB);
  bool  funcACh(float f);
  int   func3C20(int param);
  void  SetCreatureTarget(void* p, bool flag, int val);
  void  func70h(int unused);
  void  func3EC0(float f);
  void  func3F90();
  float GetBaseMaxHitPoints();
  float func4140(int boolFlag);
  bool  Write(void* stream);
  void  func42E0();
};
// ---- items of slice s00c035f0 end

// ---- items of slice s00c045a0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void* g_16c7aa4;
extern float gF_150c8d0, gF_150c8d4, gF_150c8cc_, gF_1582df0, gF_15d992c, gF_15d9930;
void* __cdecl SP_GetCurrentGameMode();                  // 0xb5b800
void* __cdecl SP_NounManager();                         // 0xb3d300
void* __cdecl FUN_00401090();                           // 0x401090
void* __cdecl FUN_004df420();                           // 0x4df420
float __cdecl FUN_00572a10(float lo, float hi);         // 0x572a10
void  __cdecl operator_delete_(void*);                  // 0xf47380
float __cdecl FUN_00c0b440(void*);                      // 0xc0b440
float __cdecl FUN_00d2e800(void*);                      // 0xd2e800
void* __cdecl FUN_00d1e660();                           // 0xd1e660
void* __cdecl FUN_00c032c0(void*, void*, void*, void*); // 0xc032c0
struct GameDataStub { int GetObjectData(); };
struct ThingMgrStub { int GetThing(); };
struct Vec3 { float x, y, z; };
static __forceinline bool GetBit(uint32_t v, int n) { return ((v >> n) & 1) != 0; }
struct CreatureBase_s00c0_45a0 {
  void*    mpVtbl;          // +0x000
  char     pad004[0xb20-0x004];
  void*    mpSpeciesProfile;// +0xb20
  char     padb24[0xb34-0xb24];
  int      mB34;            // +0xb34
  char     padb38[0xb58-0xb38];
  unsigned mFlags0b58;      // +0xb58
  char     padb5c[0xe84-0xb5c];
  void*    mpE84;           // +0xe84
  char     pade88[0x1674-0xe88];
  void*    mpHerd1674;      // +0x1674
  char     pad1678[0x1688-0x1678];
  int      mState1688;      // +0x1688
  char     pad168c[0x1690-0x168c];
  float    mDepth1690;      // +0x1690

  bool  Flag388();
  bool  __declspec(noinline) SubB770();
  void  Sub4dd0(int);
  void  Sub4e50(float);
  void* Sub4750();
  int   Sub4790();
  int   Sub47d0();
  bool  Flag04710();
  void  SetHerd(void*);
  int   GetAbilitiesCount();
  int   GetAbility(unsigned);
  float CalculateScale(char, float);
  void  OnJumpLand();
  void  OnStartSwimming();
  void  Sub50b0();
};
bool  __thiscall CreatureBase_s00c0_45a0::Flag388()
{
  void* p = *(void**)((char*)this + 0xe84);
  return p != 0 && *(char*)((char*)p + 0x388) != 0;
}
bool __declspec(noinline) __thiscall CreatureBase_s00c0_45a0::SubB770()
{
  return mB34 == 1;
}
template <typename T> struct AutoRef { T* mpObject; };
struct SpeciesProfile {
  char pad000[0x554];
  Vec3 aabb_extents;        // +0x554
  char pad560[0x6d4-0x560];
  int* mAbilityBegin;       // +0x6d4
  int* mAbilityEnd;         // +0x6d8
};
struct HerdObj {
  virtual int AddRef();     // slot 0
  virtual int Release();    // slot 1
  void OnAnimalRemoved(void*);
  char pad008[0x150 - 0x8];
  float mF150;              // +0x150
  char pad154[0x164 - 0x154];
  void* mpAnimal;           // +0x164
};
struct GameThing { void* GetProfile(); };   // avatar, slot 0xd8
struct cGameNounManagerStub { void* GetAvatar(); };
typedef void  (__thiscall *FnVoid)(void*);
float __cdecl FUN_00c0c1c0(void*, char);                // 0xc0c1c0 (Speed1)
bool  __cdecl FUN_00c0c2d0(void*);                      // 0xc0c2d0 (IsDefaultSpecies)
// ---- items of slice s00c045a0 end

// ---- items of slice s00c053b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float gF_1582ea0;   // 0x01582ea0  1.5f
extern float gF_1582ea4;   // 0x01582ea4  3.0f
extern float gF_1582ea8;   // 0x01582ea8  3.0f
extern float gF_1582ecc;   // 0x01582ecc  10.0f
extern float gF_1582ed0;   // 0x01582ed0  10.0f
extern float gF_1582e80;   // 0x01582e80  1.0f
extern float gF_1582f50;   // 0x01582f50  1.0f
extern float gF_150c888;   // 0x0150c888  0.25f
extern float gF_1485378;   // 0x01485378  0.0f
extern float gF_1471064;   // 0x01471064  0.5f
extern float gF_15716c0;   // 0x015716c0  0.1f
extern float gF_15716b8;   // 0x015716b8  0.75f
extern float gF_15716bc;   // 0x015716bc  10.0f
extern float gF_1485720;   // 0x01485720  1.0f
extern float gF_168d830;   // 0x0168d830  1.0471976f (pi/3, computed once)
extern uint32_t g_168d834; // 0x0168d834  computed-once guard
extern char   g_169e37f;   // 0x0169e37f  flag byte
extern float gF_169e388;   // 0x0169e388
extern float gF_169e38c;   // 0x0169e38c
extern float gF_169e390;   // 0x0169e390
extern void* g_168d838;    // 0x0168d838  cLocomotionStrategy template cache
void* __cdecl FUN_00b18530(void*);                           // 0x00b18530
int   __cdecl FUN_00f3c0e0(void*);                           // 0x00f3c0e0
void  __cdecl FUN_00bc9c90(void*);                           // 0x00bc9c90
void  __cdecl FUN_00c04870(void);                            // 0x00c04870
void  __cdecl FUN_00c048c0(void*, void*);                    // 0x00c048c0
void  __cdecl FUN_00ac4060(void*, int, int, int);            // 0x00ac4060 (vector reserve)
void* __cdecl operator_new_eastl(size_t, const char*, int, int, int, int); // 0x00f473a0
void  __cdecl operator_delete__(void*);                      // 0x00f47380
void* __cdecl RotateVector(void* out, const void* v, const void* q); // 0x0059aed0
void* __cdecl FUN_0059ab70(const void* v);                   // 0x0059ab70
void  __cdecl FUN_00c0d1e0(void* v);                         // 0x00c0d1e0 (SetPosition)
void  __cdecl FUN_00c1bbd0(void*);                           // 0x00c1bbd0
void* __cdecl FUN_00b532b0(void*);                           // 0x00b532b0
void* __cdecl FUN_00bca0c0(void*, int, int, int, int);       // 0x00bca0c0 FindSlot
void* __cdecl FUN_00c06000();                                 // 0x00c06000
struct Vector3_s { float x, y, z; };
struct FnC200  { void  __thiscall f(float); };            // 0x00c0c200
struct FnTimer { char  __thiscall IsRunning(); unsigned long long __thiscall Elapsed(); void __thiscall Stop(); }; // 0x00feba90/0x00bc3190/0x00bc3110
struct Fn4e50  { void  __thiscall f(float); };            // 0x00c04e50
struct Fn17de0 { void  __thiscall f(float); };            // 0x00c17de0
struct Fn20610 { void* __thiscall f(); };                 // 0x00d20610
struct Fn64a00 { int   __thiscall f(); };                 // 0x00a64a00
struct Fnef390 { void  __thiscall f(int, float); };       // 0x00aef390
struct Fnc120  { int   __thiscall f(); };                 // 0x00c0c120
struct Fnc130  { int   __thiscall f(); };                 // 0x00c0c130
struct Fnc070  { float __thiscall f(); };                 // 0x00c0c070
struct Fnb750  { int   __thiscall f(); };                 // 0x00c0b750
struct Fnc770  { int   __thiscall f(); };                 // 0x00c0b770
struct Fnc0e0  { int   __thiscall f(int); };              // 0x00c0c0e0
struct Fn17cc0 { void  __thiscall f(int, int, int, int, int); };  // 0x00c17cc0
struct Fn201a0 { void  __thiscall f(int, int, int); };    // 0x00c201a0
struct Fn1d5e0 { int*  __thiscall f(int, int, int); };    // 0x00c1d5e0
struct Fn434040 { void __thiscall ctor(); };              // 0x00434040 XformMsg::XformMsg
struct XformMsg { char b[0x30]; };
struct Fn22470 { char  __thiscall f(int); };              // 0x00c22470
struct Fn37c0  { char  __thiscall f(void*, int, int); };  // 0x00c037c0
struct Fn21090 { void  __thiscall f(); };                 // 0x00c21090
struct Fn42e0  { void  __thiscall f(); };                 // 0x00c042e0
void* __cdecl GetSetting9(void*);                         // 0x00401090
void* __cdecl GetProfile(void*);                          // 0x004df550
struct CB {
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
struct NodePool {
    uint32_t*  mpBlocksBegin;    // 0x00
    int        mBlockCount;      // 0x04
    uint8_t*   mpPoolCur;        // 0x08
    uint8_t*   mpPoolAllocEnd;   // 0x0c
    uint8_t*   mpPoolEnd;        // 0x10
    uint32_t** mppFreeListCur;   // 0x14
    uint8_t*   mpPoolBegin;      // 0x18
    uint8_t*   mpBlockCur;       // 0x1c
    uint8_t*   mpBlockEnd;       // 0x20
    uint32_t** mppFreeListEnd;   // 0x24

    void Free();                 // 0x00c05df0
    void Pop();                  // 0x00c05ea0
    void Reset();                // 0x00c05ee0
    uint8_t* Cur();              // 0x00c05e80
    void AllocChunk(void* key);  // 0x00c06070
};
static void ReleaseRef(void* p)
{
    if (p) (*(void(__thiscall**)(void*))((*(void***)p)[1]))(p);
}
// ---- items of slice s00c053b0 end

// ---- items of slice s00c0ddb0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct F_64     { char  __thiscall f(); };            // 0x00c887e0 cCommunity::func64h
struct F_a02bd0 { int   __thiscall f(); };            // 0x00a02bd0
struct CCMInner {
    uint32_t pad_00[0x17c / 4];  // +0x000
    void*    mpTable_17c;        // +0x17c  lookup object (find by id)
};
#define G32(a)  (*(uint32_t*)(a))
struct CCM {
    void  __thiscall ddb0(float*);
    char  __thiscall de30();
    void  __thiscall de60(int, int);
    bool  __thiscall dee0(int, int*, char);
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

    uint32_t pad_a94[0xa94 / 4];                 // +0x000 .. +0xa93
    void*    mpGraspObj_a94;                     // +0xa94  grasped/sound object
    uint32_t pad_b54[(0xb54 - 0xa94 - 4) / 4];   // +0xa98 .. +0xb53
    CCMInner* mpInner_b54;                       // +0xb54  animation/creature table
};
// ---- items of slice s00c0ddb0 end

// @ 0x00c004a0
void FUN_00c004a0()
{
    if (g_168d248 != 2 && g_168d248 != 1 && g_168d248 == 4) {
        SP_Eapd_sys_gui();
    }
}

// @ 0x00c004c0
bool __fastcall FUN_00c004c0(void* ecx_this, void* edx, int idx)
{
    uint64_t now = ((cGameTimeMgr*)SP_GameTimeManager())->Ticks();
    return now > 20000 && now - ((uint64_t*)((char*)ecx_this + 0x98))[idx] < 20000;
}

// @ 0x00c00510
void __fastcall FUN_00c00510(void* ecx_this, void* edx, int idx)
{
    ((uint64_t*)((char*)ecx_this + 0x98))[idx] = 0;
}

// @ 0x00c03b70
bool CreatureBase::funcACh(float f)
{
  if (!SubACh(f))
    return false;
  FUN_00c0cf50();
  FUN_00c0b710();
  float a = FUN_00d38a30(1, this);
  float v1 = FUN_00c0e4f0() * a;
  float b = FUN_00d38a30(1, this);
  float v2 = FUN_00c0c040() * b;
  float n = FUN_00d38a30(9, this);
  float r = (v2 > v1) ? v2 : v1;
  float m = (r > n) ? n : r;
  *(float*)((char*)this + 0x32c) = m;
  return true;
}

// @ 0x00c03ec0
void CreatureBase::func3EC0(float f)
{
  *(int*)((char*)this + 0xeac) = 2;
  unsigned a = *(unsigned*)((char*)this + 0x110);
  char* bt = *(char**)((char*)this + 0xb4c);
  unsigned fl = (((a & 0x100) != 0x100) ? 0xffffe000u : 0u) + 0x2000u;
  fl |= *(unsigned*)(bt + 0x5fc);
  fl |= 0x100000u;
  int ebx = FUN_00bc9980(bt + 8, f);
  uint64_t t = FUN_00b316c0(SP_GameTimeManager());
  double d = (double)t * 0.001f;
  FUN_00d995f0(f, d, *(int*)bt, this, bt + 0x1d0, *(int*)(bt + 0x5e8), fl, ebx);
}

// @ 0x00c045a0
void __thiscall CreatureBase_s00c0_45a0::SetHerd(void* p)
{
  AutoRef<HerdObj>& slot = *(AutoRef<HerdObj>*)((char*)this + 0x1674);
  if (slot.mpObject)
    slot.mpObject->OnAnimalRemoved(this);
  HerdObj* old = slot.mpObject;
  if ((HerdObj*)p != old) {
    if (p)
      ((HerdObj*)p)->AddRef();
    slot.mpObject = (HerdObj*)p;
    if (old)
      old->Release();
  }
}

// @ 0x00c045f0
int __thiscall CreatureBase_s00c0_45a0::GetAbilitiesCount()
{
  SpeciesProfile* sp = (SpeciesProfile*)mpSpeciesProfile;
  int n = (int)((char*)sp->mAbilityEnd - (char*)sp->mAbilityBegin) >> 2;
  void* gm = SP_GetCurrentGameMode();
  if (GetBit(mFlags0b58, 9) && gm == (void*)0x1654c01)
    return n + 3;
  int add = 0;
  if (Flag388() && (gm == (void*)0x1654c04 || gm == (void*)0x1654c05))
    add = 2;
  else if (Flag388() && gm == (void*)0x1654c10)
    add = 2;
  return n + add;
}

// @ 0x00c04670
int __thiscall CreatureBase_s00c0_45a0::GetAbility(unsigned index)
{
  if (index == 0xffffffff)
    return 0;
  SpeciesProfile* sp = (SpeciesProfile*)mpSpeciesProfile;
  int n = (int)((char*)sp->mAbilityEnd - (char*)sp->mAbilityBegin) >> 2;
  if (index < (unsigned)n)
    return sp->mAbilityBegin[index];
  unsigned k = index - n;
  if (GetBit(mFlags0b58, 9)) {
    if (k >= 3) return 0;
    return *(int*)((char*)FUN_00d1e660() + k * 4);
  }
  if (SP_GetCurrentGameMode() == (void*)0x1654c10) {
    if (k >= 2) return 0;
    return *(int*)((char*)FUN_00d1e660() + 0x14 + k * 4);
  }
  if (k >= 2) return 0;
  return *(int*)((char*)FUN_00d1e660() + 0xc + k * 4);
}

// @ 0x00c04710
bool __thiscall CreatureBase_s00c0_45a0::Flag04710()
{
  if ((mFlags0b58 & 0x4000) != 0)
    return true;
  if (SubB770())
    return false;
  HerdObj* h = (HerdObj*)mpHerd1674;
  if (h == 0) return false;
  CreatureBase_s00c0_45a0* a = (CreatureBase_s00c0_45a0*)*(void**)((char*)h + 0x164);
  if (a == 0) return false;
  if ((a->mFlags0b58 & 0x4000) != 0)
    return true;
  return false;
}

// @ 0x00c04750
void* __thiscall CreatureBase_s00c0_45a0::Sub4750()
{
  void* p = 0;
  if (SP_GetCurrentGameMode() == (void*)0x1654c10) {
    int g = ((GameDataStub*)this)->GetObjectData();
    if (g != 0) {
      int idx = ((ThingMgrStub*)*(int*)((char*)g_16c7aa4 + 0x74))->GetThing();
      p = (void*)(idx * 0x4e0 + *(int*)((char*)g + 0x70));
    }
  }
  return p;
}

// @ 0x00c04790
int __thiscall CreatureBase_s00c0_45a0::Sub4790()
{
  unsigned f = mFlags0b58;
  if (((f >> 8) & 1) != 0) return 2;
  if (((f >> 9) & 1) != 0) return 2;
  void* p = Sub4750();
  if (p == 0) return 0;
  p = Sub4750();
  return *(int*)((char*)p + 0x4a8);
}

// @ 0x00c047d0
int __thiscall CreatureBase_s00c0_45a0::Sub47d0()
{
  int r = 2;
  if (SP_GetCurrentGameMode() == (void*)0x1654c10) {
    int g = ((GameDataStub*)this)->GetObjectData();
    if (g != 0) {
      int idx = ((ThingMgrStub*)*(int*)((char*)g_16c7aa4 + 0x74))->GetThing();
      void* p = (void*)(idx * 0x4e0 + *(int*)((char*)g + 0x70));
      if (p != 0 && *(char*)((char*)p + 0x4c8) == 0)
        r = *(int*)((char*)p + 0x4ac);
    }
  }
  return r;
}

// @ 0x00c04820
void* __cdecl FUN_00c04820(void** first, void** last, bool (__cdecl* pred)(void*))
{
  void** p = first;
  while (p != last) {
    if (pred(*p))
      break;
    ++p;
  }
  if (p == last)
    return p;
  return FUN_00c032c0(p + 1, last, p, (void*)pred);
}

// @ 0x00c04870
void __fastcall FUN_00c04870(void** p)
{
  if (p[7])
    operator_delete_(p[7]);
  void** q = (void**)((char*)p[9] - 4);
  p[9] = q;
  void* v = *q;
  p[7] = v;
  p[8] = (void*)((char*)v + 0xa0);
  p[6] = (void*)((char*)v + 0x8c);
  void** a = *(void***)((char*)v + 0x9c);
  if (a)
    (*(FnVoid)(*(char**)a + 4))(a);
  void** b = *(void***)((char*)v + 0x98);
  if (b)
    (*(FnVoid)(*(char**)b + 4))(b);
}

// @ 0x00c049f0
float __thiscall CreatureBase_s00c0_45a0::CalculateScale(char param_2, float param_3)
{
  float v = FUN_00c0c1c0(this, param_2);
  if (FUN_00c0c2d0(this)) {                              // IsDefaultSpecies
    v = FUN_00d2e800(this);
  } else {
    void* e = mpE84;
    if (e != 0) {
      float d = *(float*)((char*)e + 0x33c);
      if (d > 0.0f) {
        SpeciesProfile* sp = (SpeciesProfile*)mpSpeciesProfile;
        float x = sp->aabb_extents.x, y = sp->aabb_extents.y, z = sp->aabb_extents.z;
        v = d / (float)sqrt((double)(z * z + y * y + x * x));
      }
    }
  }
  if (SubB770() || param_2 != 0) {
    if ((((unsigned)mFlags0b58 >> 9) & 1) == 0)
      v = v * (float)FUN_00572a10(gF_15d992c, gF_15d9930);
    char* h = (char*)mpHerd1674;
    if (h != 0)
      v = *(float*)(h + 0x150) * v;
    if ((mFlags0b58 & 1) != 0)
      v = gF_150c8d0 * v;
  }
  FUN_00401090();
  if ((void*)mpSpeciesProfile == FUN_004df420()) {
    cGameNounManagerStub* nm = (cGameNounManagerStub*)SP_NounManager();
    GameThing* av = (GameThing*)nm->GetAvatar();
    if (av != 0)
      return v * FUN_00c0b440(av->GetProfile()) * gF_1582df0;
  }
  return v * gF_1582df0;
}

// @ 0x00c053b0
void CB::func74h(int param_2, int param_3)
{
    void* body = (char*)this + 0xc0;
    float* p = (float*)(*(void*(__thiscall**)(void*))((*(void***)body)[0x2c / 4]))(body);
    float px = p[0], py = p[1], pz = p[2];

    Vector3_s pos, dir;
    if (((mGeneralFlags >> 9) & 1) && g_169e37f) {
        (*(void(__thiscall**)(void*, void*))((*(void***)body)[0x5c / 4]))(body, &pos);
        (*(void(__thiscall**)(void*, void*))((*(void***)body)[0x60 / 4]))(body, &dir);
        if (!(g_168d834 & 1)) {
            g_168d834 |= 1;
            gF_168d830 = 1.0471976f;
        }
        float d = dir.x * (dir.z * gF_169e388 - dir.y * gF_169e390) +
                  dir.y * (dir.x * gF_169e390 - dir.z * gF_169e388) +
                  dir.z * (dir.y * gF_169e388 - dir.x * gF_169e390);
        if (d > gF_1485378) {
            float a = gF_168d830 * gF_1471064;
            float s = (float)sin(a);
            float c = (float)cos(a);
            Vector3_s v;
            v.x = px * s; v.y = py * s; v.z = pz * s;
            (void)c;
            RotateVector(&v, &v, &a);
        } else {
            float a = -(gF_168d830 * gF_1471064);
            float s = (float)sin(a);
            float c = (float)cos(a);
            Vector3_s v;
            v.x = px * s; v.y = py * s; v.z = pz * s;
            (void)c;
            RotateVector(&v, &v, &a);
        }
    } else {
        pos.x = *(float*)(param_3 + 0x14) - px;
        pos.y = *(float*)(param_3 + 0x18) - py;
        pos.z = *(float*)(param_3 + 0x1c) - pz;
        float len = (float)sqrt((double)(pos.z * pos.z + pos.y * pos.y) + (double)(pos.x * pos.x));
        if (len > gF_15716c0) {
            float inv = 1.0f / len;
            pos.x = pos.x * inv;
            pos.y = pos.y * inv;
            pos.z = pos.z * inv;
        } else {
            pos.x = -gF_169e388;
            pos.y = -gF_169e38c;
            pos.z = -gF_169e390;
            Vector3_s res;
            RotateVector(&res, &pos, (char*)this + 0x164);
            if (!FUN_0059ab70(&res))
                ;
        }
    }
    float w = gF_15716bc;
    float k = gF_1485720 - gF_15716b8;
    void* ac = mpStrat;
    Vector3_s out;
    out.x = (*(float*)((char*)ac + 0x164) * gF_15716b8) + (pos.x * w + px) * k;
    out.y = (*(float*)((char*)ac + 0x168) * gF_15716b8) + (pos.y * w + py) * k;
    out.z = (*(float*)((char*)ac + 0x16c) * gF_15716b8) + (pos.z * w + pz) * k;
    FUN_00c0d1e0(&out);
}

// @ 0x00c05810
void CB::func58h(float dt)
{
    char* self = (char*)this;
    ((FnC200*)self)->f(dt);
    char* timer = self + 0x1628;
    if (((FnTimer*)timer)->IsRunning()) {
        unsigned long long t = ((FnTimer*)timer)->Elapsed();
        if (t > (unsigned long long)*(uint32_t*)0x150c884)
            ((FnTimer*)timer)->Stop();
    }
    if (SP_GetCurrentGameMode() != (void*)0x1654c10)
        ((Fn4e50*)self)->f(dt);
    ((Fn17de0*)self)->f(dt);
    if (*(int*)(self + 0xeac) == 2) {
        char* body = self + 0xc0;
        void* loco = FUN_00b532b0(body);
        if (loco) {
            float* vel = (float*)((Fn20610*)body)->f();
            float vx = vel[0], vy = vel[1], vz = vel[2];
            float* sp = (float*)(*(void*(__thiscall**)(void*))((*(void***)body)[0xd8 / 4]))(body);
            float speed = (float)sqrt((double)((vx * vx + vy * vy) + vz * vz)) * (*sp);
            unsigned char b;
            if ((*(char*)(self + 0x137) != 0) && speed >= gF_1582ecc &&
                ((Fnc120*)self)->f())
                b = 1;
            else if (*(int*)(self + 0xe8c) != -1 &&
                     (*(int*(__thiscall**)(void*, int))((*(void***)self)[0xb4 / 4]))(self, *(int*)(self + 0xe8c))[2] == 0x1f)
                b = 1;
            else
                b = 0;
            if ((char)((Fn64a00*)loco)->f() != (char)b)
                ((Fnef390*)loco)->f(b, gF_1582ed0);
        }
    }
    if (*(int*)(self + 0xeac) < 2) {
        if (((Fnc130*)self)->f()) {
            *(float*)(self + 0xb80) = 0.0f;
            return;
        }
    } else {
        int q = *(int*)(self + 0xb4c);
        if (q != 0 && *(int*)(q + 0x1d8) == 0x2d852e6) {
            *(float*)(self + 0xb80) =
                ((Fnc070*)self)->f() * gF_1582ea8 + *(float*)(self + 0x1000);
            return;
        }
        if (((Fnc130*)self)->f()) {
            *(float*)(self + 0xb80) = 0.0f;
            return;
        }
        if (((Fnc120*)self)->f()) {
            if (*(char*)(self + 0x137) != 0 || (*(uint32_t*)(self + 0x110) & 0x1000))
                goto L_a46;
        } else {
            uint32_t k = (uint32_t)((Fnb750*)self)->f();
            if (k < 4) {
                switch (k) {
                case 0: case 2:
                    if (*(char*)(self + 0x137) != 0 || (*(uint32_t*)(self + 0x110) & 0x1000)) {
                        *(float*)(self + 0xb80) =
                            ((Fnc070*)self)->f() * gF_1582ea0 + *(float*)(self + 0x1000);
                        return;
                    }
                    goto L_e6;
                case 1:
                    *(float*)(self + 0xb80) = 0.0f;
                    return;
                case 3:
                    break;
                }
            }
            if (*(char*)(self + 0x137) != 0 || (*(uint32_t*)(self + 0x110) & 0x1000))
                goto L_a46;
        }
    }
L_e6:
    *(float*)(self + 0xb80) = ((Fnc070*)self)->f() + *(float*)(self + 0x1000);
    return;
L_a46:
    *(float*)(self + 0xb80) = ((Fnc070*)self)->f() * gF_1582ea4 + *(float*)(self + 0x1000);
}

// @ 0x00c05a80
void CB::func5a8h(int param_2)
{
    char* self = (char*)this;
    void* gm = SP_GetCurrentGameMode();
    if (gm == (void*)0x1654c01) {
        char* body = self + 0xc0;
        typedef char (__thiscall *VtFn)(void*);
        VtFn vt0 = (VtFn)((*(void***)body)[0x58 / 4]);
        VtFn vt1 = (VtFn)((*(void***)body)[0x48 / 4]);
        if (vt0(body) && *(int*)(self + 0xeac) >= 1) {
            char f = vt1(body);
            char v;
            if (*(char*)(self + 0xfb8) != 0 && f != 0) v = 1; else v = 0;
            ((Fn17cc0*)self)->f(v, 0, (int)0xe1a4bd93, (int)0xf20c24d8, 0);
            ((Fn201a0*)self)->f((char)((Fnc120*)self)->f(), (int)0xe55dc391, (int)0x35052b7);
        }
        char b;
        if (*(char*)(self + 0xb5e) == 0 &&
            FUN_00bca0c0(*(void**)(self + 0xb48), 1, 1, 0, 0) != (void*)-1)
            b = 1;
        else
            b = 0;
        ((Fn1d5e0*)self)->f(b, (int)0xdc5ed5b9, (int)0xdc5ed5b9);
        return;
    }
    uint32_t m = (uint32_t)gm + 0xfe9ab3fc;
    if (m > 1) return;
    float f = *(float*)(self + 0x169c);
    int e = f > gF_1485378;
    char g = (char)((Fnc0e0*)self)->f(0x1f750af4);
    int arg = g ? 0x1f750af4 : 0x1f750af4 - 0x9f7f1be0;
    int* piVar5 = ((Fn1d5e0*)self)->f(e, arg, 0x1f750af4);
    if (!piVar5) return;
    XformMsg msg;
    ((Fn434040*)&msg)->ctor();
    (*(void(__thiscall**)(int*, void*))((*(void***)piVar5)[0x20 / 4]))(piVar5, &msg);
    (*(float(__thiscall**)(void*))((*(void***)(self + 0xc0))[0x34 / 4]))(self + 0xc0);
    *(uint16_t*)((char*)&msg + 2) += 1;
    (*(void(__thiscall**)(int*, void*))((*(void***)piVar5)[0x18 / 4]))(piVar5, &msg);
}

// @ 0x00c05bf0
float CB::func5bf0()
{
    char* self = (char*)this - 0x5a8;
    float base = (*(float(__thiscall**)(void*))((*(void***)self)[0x7c / 4]))(self);
    void* gm = SP_GetCurrentGameMode();
    if (gm != (void*)0x1654c10) {
        float f = gF_1582e80;
        if (!((*(uint32_t*)((char*)this + 0x5b0) >> 9) & 1))
            f = gF_1485720;
        char c = (char)((Fnc770*)self)->f();
        if (c == 0)
            f = gF_150c888 * f;
        else if ((*(uint8_t*)((char*)this + 0x5b0) & 1) != 0)
            f = gF_1582f50 * f;
        return f * base;
    }
    if (SP_GetCurrentGameMode() == (void*)0x1654c10) {
        void* gd = FUN_00b18530(self);
        if (gd) {
            int* e = (int*)(FUN_00f3c0e0(*(void**)((char*)g_16c7aa4 + 0x74)) * 0x4e0 + *(int*)((char*)gd + 0x70));
            if (e) {
                float v = *(float*)((char*)e + 0x48c) * base;
                int i = (int)v;
                if ((float)i < v) i = i + 1;
                return (float)i;
            }
        }
    }
    float v = *(float*)(*(int*)(*(int*)((char*)g_16c7aa4 + 0x74) + 0x10) + 0x170) * base;
    int i = (int)v;
    if ((float)i < v) i = i + 1;
    return (float)i;
}

// @ 0x00c05d40
char CB::func5d40(int param_2)
{
    char* self = (char*)this;
    void* key = self + 0xb28;
    void* prof = GetProfile(GetSetting9(key));
    void* ecx = *(void**)(self + 0x1674);
    if (ecx)
        (*(void(__thiscall**)(void*, int))((*(void***)ecx)[0x3c / 4]))(ecx, param_2);
    char bl = ((Fn22470*)self)->f(param_2);
    if (bl) {
        if (*(void**)key != 0) {
            void* prof2 = GetProfile(GetSetting9(key));
            bl = ((Fn37c0*)self)->f(prof2, 0, 1);
            if (prof != prof2) {
                ((Fn21090*)self)->f();
                void* p = *(void**)(self + 0x1674);
                *(uint32_t*)(self + 0xb58) &= 0xffffff7f;
                if (p) *(uint8_t*)((char*)p + 0x191) = 0;
            }
        }
        if (bl) {
            ((Fn42e0*)self)->f();
            (*(void(__thiscall**)(void*))((*(void***)self)[0x54 / 4]))(self);
        }
    }
    return bl;
}

// @ 0x00c05df0
void NodePool::Free()
{
    uint8_t* cur = mpPoolCur;
    uint8_t* blkCur = mpPoolEnd;
    uint32_t** fl = mppFreeListCur;
    if (cur != mpPoolBegin) {
        do {
            ReleaseRef(*(void**)(cur + 0x10));
            ReleaseRef(*(void**)(cur + 0xc));
            cur += 0x14;
            if (cur == blkCur) {
                blkCur = (uint8_t*)fl[1];
                fl += 1;
                mppFreeListCur = fl;
                mpPoolEnd = blkCur;
            }
        } while (cur != mpPoolBegin);
    }
    if (mpBlocksBegin) {
        uint8_t** p = (uint8_t**)mpPoolEnd;
        uint8_t** q = (uint8_t**)((char*)mppFreeListEnd + 4);
        if (p < q) {
            do {
                if (*p) operator_delete__(*p);
                p += 1;
            } while (p < q);
        }
        if (mpBlocksBegin) operator_delete__(mpBlocksBegin);
    }
}

// @ 0x00c05e80
uint8_t* NodePool::Cur()
{
    uint8_t*   a = mpPoolBegin;
    uint8_t*   b = mpBlockCur;
    uint32_t** c = mppFreeListEnd;
    if (a != b)
        return a - 0x14;
    return (uint8_t*)c[-1] + 0x8c;
}

// @ 0x00c05ea0
void NodePool::Pop()
{
    uint8_t* cur = mpPoolBegin;
    if (cur == mpBlockCur) {
        FUN_00c04870();
        return;
    }
    uint8_t* esi = cur - 0x14;
    mpPoolBegin = esi;
    ReleaseRef(*(void**)(esi + 0x10));
    ReleaseRef(*(void**)(esi + 0xc));
}

// @ 0x00c05ee0
void NodePool::Reset()
{
    uint8_t* poolCur = mpPoolCur;
    uint32_t** fl = mppFreeListCur;
    if (fl == mppFreeListEnd) {
        if (poolCur < mpPoolBegin) {
            do {
                ReleaseRef(*(void**)(poolCur + 0x10));
                ReleaseRef(*(void**)(poolCur + 0xc));
                poolCur += 0x14;
            } while (poolCur < mpPoolBegin);
        }
    } else {
        if (poolCur < mpPoolAllocEnd) {
            do {
                ReleaseRef(*(void**)(poolCur + 0x10));
                ReleaseRef(*(void**)(poolCur + 0xc));
                poolCur += 0x14;
            } while (poolCur < mpPoolAllocEnd);
        }
        poolCur = mpBlockCur;
        if (poolCur < mpPoolBegin) {
            do {
                ReleaseRef(*(void**)(poolCur + 0x10));
                ReleaseRef(*(void**)(poolCur + 0xc));
                poolCur += 0x14;
            } while (poolCur < mpPoolBegin);
        }
        if (mpBlockCur) operator_delete__(mpBlockCur);
    }
    uint32_t** q = mppFreeListCur + 1;
    if (q < mppFreeListEnd) {
        do {
            uint8_t* e = (uint8_t*)*q;
            uint8_t* end = e + 0xa0;
            if (e < end) {
                do {
                    ReleaseRef(*(void**)(e + 0x10));
                    ReleaseRef(*(void**)(e + 0xc));
                    e += 0x14;
                } while (e < end);
            }
            if (*q) operator_delete__(*q);
            q += 1;
        } while (q < mppFreeListEnd);
    }
    mpPoolBegin = mpPoolCur;
    mpBlockCur = mpPoolAllocEnd;
    mpBlockEnd = mpPoolEnd;
    mppFreeListEnd = mppFreeListCur;
    mpPoolEnd = (uint8_t*)mppFreeListCur;
}

// @ 0x00c06000
void* __cdecl FUN_00c06000()
{
    if (g_168d838 == 0) {
        void* p = operator_new_eastl(0x10, "Simulator/LocomotionStrategy_Template", 0, 0, 0, 0);
        if (p) {
            *(void**)((char*)p + 8) = (void*)0x13ec458;
            *(void**)((char*)p + 0xc) = 0;
            *(void**)p = (void*)0x1469e38;
            *(void**)((char*)p + 8) = (void*)0x1475114;
            g_168d838 = p;
            (*(void(__thiscall**)(void*))*(void**)p)(p);
            return g_168d838;
        }
        g_168d838 = 0;
        (*(void(__thiscall**)(void*))0)(0);
    }
    return g_168d838;
}

// @ 0x00c06070
void NodePool::AllocChunk(void* param_2)
{
    uint8_t scratch[0x14];
    FUN_00c048c0(param_2, &scratch[0]);
    int n = (((int)mppFreeListEnd - (int)mpBlocksBegin) >> 2) + 1;
    if (n >= mBlockCount)
        FUN_00ac4060(this, 1, 1, 0);
    void* blk = operator_new_eastl(0xa0, "Simulator", 0, 0, 0x13ebb38, 0xd1);
    *(void**)((char*)mppFreeListEnd + 4) = blk;
    if (mpPoolBegin) FUN_00c048c0(&scratch[0], 0);
    uint32_t** fl = mppFreeListEnd;
    mppFreeListEnd = fl + 1;
    uint8_t* nb = (uint8_t*)fl[1];
    mpBlockCur = nb;
    mpBlockEnd = nb + 0xa0;
    mpPoolBegin = mpBlockCur;
    ReleaseRef(*(void**)(scratch + 0xc));
    ReleaseRef(*(void**)(scratch + 0x4));
}

// @ 0x00c061b0
void __fastcall FUN_00c061b0(void* self)
{
    void* edi = *(void**)((char*)self + 0x1624);
    *(void**)self = (void*)0x146a0e0;
    *(void**)((char*)self + 4) = (void*)0x146a0cc;
    *(void**)((char*)self + 0x34) = (void*)0x146a088;
    *(void**)((char*)self + 0x58) = (void*)0x146a020;
    *(void**)((char*)self + 0xc0) = (void*)0x1469f20;
    *(void**)((char*)self + 0x194) = (void*)0x1469f14;
    *(void**)((char*)self + 0x590) = (void*)0x1469ef8;
    *(void**)((char*)self + 0x5a8) = (void*)0x1469e90;
    *(void**)((char*)self + 0x670) = (void*)0x1469e74;
    if (edi) {
        FUN_00bc9c90(edi);
        operator_delete__(edi);
    }
    void* p = *(void**)((char*)self + 0x1698);
    if (p) (*(void(__thiscall**)(void*))((*(void***)p)[0x64 / 4]))(p);
    p = *(void**)((char*)self + 0x1674);
    if (p) (*(void(__thiscall**)(void*))((*(void***)p)[4 / 4]))(p);
    ((SP::cGonzagoTimer*)((char*)self + 0x1628))->~cGonzagoTimer();
    p = *(void**)((char*)self + 0x140c);
    if (p && *(int*)((char*)p - 4)) operator_delete__(p);
    p = *(void**)((char*)self + 0x13d4);
    if (p && *(int*)((char*)p - 4)) operator_delete__(p);
    p = *(void**)((char*)self + 0x133c);
    if (p && *(int*)((char*)p - 4)) operator_delete__(p);
    p = *(void**)((char*)self + 0x1124);
    if (p && *(int*)((char*)p - 4)) operator_delete__(p);
    p = *(void**)((char*)self + 0x108c);
    if (p && *(int*)((char*)p - 4)) operator_delete__(p);
    ((NodePool*)((char*)self + 0x1060))->Free();
    ((NodePool*)((char*)self + 0x1034))->Free();
    p = *(void**)((char*)self + 0x1020);
    if (p && *(int*)((char*)p - 4)) operator_delete__(p);
    ((SP::cGonzagoTimer*)((char*)self + 0xfe0))->~cGonzagoTimer();
    ((SP::cGonzagoTimer*)((char*)self + 0xfc0))->~cGonzagoTimer();
    FUN_00c1bbd0(self);
}

// @ 0x00c06340
void CB::RankForward(int param_2)
{
    typedef void (__thiscall* Fn)(CB*, int);
    volatile Fn fn = (Fn)(*(void***)this)[0x3c / 4];
    fn(this, param_2);
}

// @ 0x00c0de30
char __thiscall CCM::de30()
{
    char* p = *(char**)((char*)this + 0xa94);
    if (p != 0) {
        if (*(char*)((char*)this + 0xed0) != 0) {
            if (((F_a02bd0*)p)->f() != 0) return 1;
        }
        return 0;
    }
    return ((F_64*)this)->f();
}

// @ 0x00c0dee0
bool __thiscall CCM::dee0(int param_2, int* param_3, char param_4)
{
    *param_3 = -1;
    char* base = *(char**)((char*)this + 0xb54);
    unsigned n = G32(base + 0x14c);
    unsigned i = 0;
    if (n == 0) return 0;
    int* p = (int*)(base + 0x8c);
    while (*p != param_2) {
        ++i;
        p += 3;
        if (n <= i) return 0;
    }
    *param_3 = *(int*)(base + (i * 3 + 0x24) * 4);
    if (param_4 != 0) {
        base = *(char**)((char*)this + 0xb54);
        --G32(base + 0x14c);
        if (i < G32(base + 0x14c)) {
            char* e = base + i * 0xc;
            do {
                *(int*)(e + 0x8c) = *(int*)(e + 0x98);
                *(int*)(e + 0x90) = *(int*)(e + 0x9c);
                *(int*)(e + 0x94) = *(int*)(e + 0xa0);
                ++i;
                e += 0xc;
                base = *(char**)((char*)this + 0xb54);
            } while (i < G32(base + 0x14c));
        }
    }
    return 1;
}
