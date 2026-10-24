// Slice s00d81940 -- lounge / drink behavior helpers.
//
//   0x00d81940  unnamed            -- pick a water point near the herd's watering
//                                     hole, project it, ray-cast it and walk there.
//   0x00d81b60  SP::DRINK_Tick     -- six-state drink behavior.
//   0x00d82040  SP::FindGuardOrLoungeGroup -- find/create the guard or lounge group.
//   0x00d821a0  SP::LOUNGE_VIGNETTE_Activate -- start a lounge vignette.
//   0x00d823b0  unnamed            -- deactivate the lounge vignette.
//   0x00d82410  unnamed            -- lounge vignette countdown; true while it runs.
//
// The raw offsets from the disassembly are named here.  The lounge memory block
// used by the two vignette entries carries the node at +0x00, the table index
// at +0x18 and the table key at +0x1c.  The drink memory block carries state
// +0x00, timer +0x04, target +0x08 and a second position +0x14.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS-

#include "types.h"
#include <math.h>

typedef unsigned int   u32;
typedef int            s32;
typedef unsigned char  u8;

struct Vec3 { float x, y, z; };
struct Quat { float x, y, z, w; };

// ---------------------------------------------------------------------------
// Named layouts
// ---------------------------------------------------------------------------

struct cNearNoun;
struct cSPCreatureBase;
struct cLocomotiveObject;
struct BehaviorEnv;
struct LOUNGE_Node;
struct VignetteDef;
struct VignetteRange;
struct VignetteMgr;
struct VignetteList;
struct cPlanetModel;
struct Archetype;
struct SpeciesMgr;
struct LayoutMgr;

struct cNearNoun {
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
  Vec3  mWateringHole_20c;     // +0x20c

  bool UnbrokenEggsInNest();   // 0x00c6ac40
  const Vec3* GetPosition();   // 0x00c6acc0
  Vec3* FUN_00c6bdc0();        // 0x00c6bdc0
};

struct cLocomotiveObject {
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
  void FUN_00bcb480(LOUNGE_Node* node, cSPCreatureBase* c, int a, int b); // 0x00bcb480
};

struct cSPCreatureBase {
  u8   pad00[0xc0];
  cLocomotiveObject mLoco;     // +0x0c0
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
  cNearNoun* mpNoun_1674;      // +0x1674

  cNearNoun* Get();                                                // 0x00c04590
  Archetype* FUN_00c0c1a0();                                       // 0x00c0c1a0
  void MoveToPointAtSpeed(int mode, Vec3* target, float a, float b); // 0x00c1c1d0
  void FUN_00c14750(bool b);                                       // 0x00c14750
  bool AnimationFinished(u32 anim);                                // 0x00c123f0
  void FUN_00c14990(u32 anim, const Vec3* target, int a);          // 0x00c14990
  void PlayAnimationWithTarget(u32 anim, const Vec3* target, int a); // 0x00c14910
  u8   FUN_00c0e0c0(u32 anim);                                     // 0x00c0e0c0
};

struct Archetype {
  u8    pad00[0x394];
  float mLo_394;               // +0x394
  float mHi_398;               // +0x398
};

struct SpeciesMgr {
  Archetype* GetSpeciesArchetype(u32 a, u32 b); // 0x004e0050
};

struct cPlanetModel {
  Vec3* FUN_00b81630(Vec3* out, const Vec3* in);                       // 0x00b81630
  void  FindClosestWater(Vec3* pos, float maxDist, Vec3* out);          // 0x00b8bb70
  void  MakeRandomWorldPosition(Vec3* out, Vec3* center, float r0, float r1); // 0x00b81780
  Quat* BuildSurfaceOrientation(Quat* out, const Vec3* pos);            // 0x00b7f190
  void  RayCast(Vec3* a, float dist, Vec3* b, float c, int d, int e);  // 0x00b88770
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
  u8   FUN_00bc4900(int id, cSPCreatureBase* c, int a);             // 0x00bc4900 (ret 0xc)
  void FUN_00bc52a0(int id, cSPCreatureBase* c);                    // 0x00bc52a0 (ret 8)
  int  FUN_00bc65f0(const VignetteDef* def, const Vec3* a, const Vec3* b); // 0x00bc65f0 (ret 0xc)
};

struct VignetteList {
  LOUNGE_Node* Insert(u32 key, s32 id, const char* tag, const char* name); // 0x00bcb0b0 (ret 0x10)
  LOUNGE_Node* FindItem(u32 key, void* pred, void* ctx);              // 0x00bca620 (ret 0xc)
};

struct LayoutMgr {
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
  Vec3  mTarget;               // +0x08
  Vec3  mTarget2;              // +0x14
};

// ---------------------------------------------------------------------------
// Helper functions
// ---------------------------------------------------------------------------

cPlanetModel* PlanetModel();                          // 0x00b3d350
VignetteMgr*  FUN_00b3d4e0();                         // 0x00b3d4e0
VignetteList* FUN_00bc9b00();                         // 0x00bc9b00
LayoutMgr*    CreateLayoutManager();                  // 0x00af13b0
SpeciesMgr*   FUN_00401090();                         // 0x00401090
float         RandomFloatRange(float lo, float hi);   // 0x00572a10
bool          FUN_00d7b290(void* a, void* b);         // 0x00d7b290
void          FUN_0059aed0(Vec3* out, const Quat* a, const Quat* b); // 0x0059aed0

extern float g_HiDefault;                             // 0x01473c70
extern float g_LoDefault;                             // 0x01486110
extern Vec3  g_DefaultSurf;                           // 0x0169f03c

typedef void  (__thiscall* VoidSlot)(void*);
typedef float (__thiscall* FloatSlot)(void*);
typedef Vec3* (__thiscall* Vec3Slot)(void*);
typedef Vec3* (__thiscall* Vec3OutSlot)(void*, Vec3*);
typedef bool  (__thiscall* BoolSlot)(void*);

#define VSLOT(T, p, off) ((T)((*(void***)(p))[(off) / 4]))

template <class T>
static const T& MaxRef(const T& a, const T& b)
{
  return a > b ? a : b;
}

// ===========================================================================
// @ 0x00d81940
// ===========================================================================
bool __cdecl FUN_00d81940(cSPCreatureBase* c, u32, u32, u32, u32, DRINK_Mem* mem)
{
  cNearNoun* noun = c->Get();
  mem->mState = 0;
  mem->mTimer = 0.0f;

  cPlanetModel* pm = PlanetModel();
  Vec3* center = noun->FUN_00c6bdc0();
  Vec3 pos;
  pm->MakeRandomWorldPosition(&pos, center, 3.0f, 10.0f);

  Vec3 water;
  pm->FindClosestWater(&pos, 1.0f, &water);

  Vec3* locoPos = VSLOT(Vec3Slot, &c->mLoco, 0x2c)(&c->mLoco);
  Vec3 delta;
  delta.x = water.x - locoPos->x;
  delta.y = water.y - locoPos->y;
  delta.z = water.z - locoPos->z;
  float inv = 1.0f / sqrtf(delta.x * delta.x + delta.y * delta.y + delta.z * delta.z + 1e-08f);
  delta.x *= inv;
  delta.y *= inv;
  delta.z *= inv;

  float radius = VSLOT(FloatSlot, &c->mLoco, 0x74)(&c->mLoco);
  Vec3 target;
  target.x = water.x + delta.x * radius;
  target.y = water.y + delta.y * radius;
  target.z = water.z + delta.z * radius;

  Vec3 surf;
  pm->FUN_00b81630(&surf, &target);

  mem->mTarget = surf;
  mem->mTarget2 = surf;
  pm->RayCast(&mem->mTarget, 10.0f, &mem->mTarget2, 1.0f, 0, 5);
  c->MoveToPointAtSpeed(2, &mem->mTarget2, 1.0f, 2.0f);
  c->FUN_00c14750(!VSLOT(BoolSlot, &c->mLoco, 0xf8)(&c->mLoco));
  return true;
}

// ===========================================================================
// @ 0x00d81b60  SP::DRINK_Tick
// ===========================================================================
bool __cdecl FUN_00d81b60(cSPCreatureBase* c, u32, u32, u32 flags, u32,
                          DRINK_Mem* mem, u32, float dt)
{
  if (!CreateLayoutManager()->LookupA(c, 0, 0))
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
      Vec3 dir;
      VSLOT(Vec3OutSlot, &c->mLoco, 0x5c)(&c->mLoco, &dir);
      Vec3* pos = VSLOT(Vec3Slot, &c->mLoco, 0x2c)(&c->mLoco);
      Vec3 target;
      target.x = pos->x + dir.x * radius;
      target.y = pos->y + dir.y * radius;
      target.z = pos->z + dir.z * radius;
      Vec3 surf;
      PlanetModel()->FUN_00b81630(&surf, &target);
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
        Vec3 dir;
        VSLOT(Vec3OutSlot, &c->mLoco, 0x5c)(&c->mLoco, &dir);
        Vec3* pos = VSLOT(Vec3Slot, &c->mLoco, 0x2c)(&c->mLoco);
        Vec3 target;
        target.x = pos->x + dir.x * radius;
        target.y = pos->y + dir.y * radius;
        target.z = pos->z + dir.z * radius;
        Vec3 surf;
        PlanetModel()->FUN_00b81630(&surf, &target);
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
      Vec3 dir;
      VSLOT(Vec3OutSlot, &c->mLoco, 0x5c)(&c->mLoco, &dir);
      Vec3* pos = VSLOT(Vec3Slot, &c->mLoco, 0x2c)(&c->mLoco);
      Vec3 target;
      target.x = pos->x + dir.x * radius;
      target.y = pos->y + dir.y * radius;
      target.z = pos->z + dir.z * radius;
      Vec3 surf;
      PlanetModel()->FUN_00b81630(&surf, &target);
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

// ===========================================================================
// @ 0x00d82040  SP::FindGuardOrLoungeGroup
// ===========================================================================
LOUNGE_Node* __cdecl FindGuardOrLoungeGroup(cSPCreatureBase* c, u8 onlyGuard)
{
  LOUNGE_Node* result = 0;
  if (c) {
    cNearNoun* noun = c->Get();
    if (noun->UnbrokenEggsInNest())
      return FUN_00bc9b00()->Insert(0x4472a59, noun->mWorld_110,
                                    (const char*)0x18eb45e, (const char*)0x147c048);

    if (noun->mCount_10c > 0) {
      result = FUN_00bc9b00()->FindItem(0x4472a59, (void*)&FUN_00d7b290, c);
      if (result)
        return result;
    }
    if (onlyGuard)
      return result;

    result = FUN_00bc9b00()->FindItem(0x439e33e, (void*)&FUN_00d7b290, c);
    if (result)
      return result;

    Archetype* arch = FUN_00401090()->GetSpeciesArchetype(
        c->Get()->mField_88, c->Get()->mField_f0);
    if (!arch)
      arch = c->FUN_00c0c1a0();

    float f;
    if (arch)
      f = RandomFloatRange(arch->mLo_394, arch->mHi_398);
    else
      f = RandomFloatRange(g_LoDefault, g_HiDefault);

    int n = (int)f;
    n = MaxRef(n, 1);
    return FUN_00bc9b00()->Insert(0x439e33e, n, (const char*)0x18eb45e,
                                  (const char*)0x147c040);
  }
  return result;
}

// ===========================================================================
// @ 0x00d821a0  SP::LOUNGE_VIGNETTE_Activate
// ===========================================================================
void __cdecl SP_LOUNGE_VIGNETTE_Activate(cSPCreatureBase* c, u32, u32, u32, u32, u32,
                                         LOUNGE_Mem* mem)
{
  VSLOT(VoidSlot, &c->mLoco, 0xec)(&c->mLoco);

  LOUNGE_Node* node = mem->mpNode;
  if (!node) {
    cNearNoun* noun = c->Get();
    VignetteRange* range = FUN_00b3d4e0()->Find(mem->mTableKey, 0);
    VignetteDef* def = (VignetteDef*)((char*)range->mpBegin + mem->mVignetteIndex * 0x7b4);

    const Vec3* posPtr = noun->GetPosition();
    Vec3 pos = *posPtr;
    Vec3 surf = g_DefaultSurf;
    if (noun->mpField_160 == 0) {
      Quat q;
      PlanetModel()->BuildSurfaceOrientation(&q, &pos);
      FUN_0059aed0(&surf, (const Quat*)0x169f0e0, &q);
    } else {
      void* obj = (char*)noun->mpField_160 + 0x34;
      VSLOT(Vec3OutSlot, obj, 0x5c)(obj, &surf);
    }

    float r1 = VSLOT(FloatSlot, &c->mLoco, 0x74)(&c->mLoco);
    float r2 = VSLOT(FloatSlot, &c->mLoco, 0x74)(&c->mLoco);
    Vec3 out;
    PlanetModel()->MakeRandomWorldPosition(&out, &surf, r1, r2 * def->mField_04 + r1);

    node = FUN_00bc9b00()->Insert(0x564c368, def->mField_04, (const char*)0x18eb45e,
                                  (const char*)0x147c050);
    node->mHandleTimer.mHandle = -1;
    node->mHandleTimer.mHandle = FUN_00b3d4e0()->FUN_00bc65f0(def, &out, &surf);
    node->mHandleTimer.mTimer = 20.0f;
  }

  c->mpEnv_0b4c->FUN_00bcb480(node, c, 0, 0);
  FUN_00b3d4e0()->FUN_00bc4900(node->mHandleTimer.mHandle, c, 0);
}

// ===========================================================================
// @ 0x00d823b0
// ===========================================================================
void __cdecl FUN_00d823b0(cSPCreatureBase* c)
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

// ===========================================================================
// @ 0x00d82410
// ===========================================================================
bool __cdecl FUN_00d82410(cSPCreatureBase* c, u32, u32, u32, u32, u32, u32, float dt)
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
