// Decompiled slice s00d65250 -- combat / creature strategy helpers.
// Reconstructed from the shipped binary; helper addresses noted per call.
#include "types.h"

// ---------------------------------------------------------------------------
// shared shapes
// ---------------------------------------------------------------------------
struct IRef {
  virtual void AddRef();      // +0x00
  virtual void Release();     // +0x04
  void* Get(IRef** out);      // 0x00c04590
};

struct ListNode {
  ListNode* mpNext;           // +0x00
  ListNode* mpPrev;           // +0x04
  IRef* mpObject;             // +0x08
};

struct IntrusiveList {
  ListNode mHead;             // +0x00 (sentinel)
  uint32_t mPad0c[3];         // +0x0c
  ListNode* mpFree;           // +0x18

  void Remove(IRef** object);
};

struct Manager {
  uint8_t mPad00[0x168];
  IntrusiveList mList;        // +0x168
};

struct FreeListAlloc {
  uint8_t mPad00[0x10];       // +0x00
  void* mpFree;               // +0x10
  bool AddCore(void* core, uint32_t count);
};

struct PoolBlock {
  uint32_t mPad00[2];         // +0x00
  IRef* mpObject;             // +0x08
};

struct Pool {
  uint8_t mPad00[8];          // +0x00
  FreeListAlloc mAlloc;       // +0x08

  void* Alloc(IRef** object);
};

struct Variant {
  int mField[6];

  void CopyFrom(const int* src);
  void AssignFrom(const int* src);
};

struct RecordArray {
  uint32_t* mpData;           // +0x00
  int FindNext(int index);
};

struct RNG {
  uint32_t Uniform(uint32_t max);
};

struct StrategyCtx {
  int mField0;
  int mField1;
  int mField2;
  int mPad0c[3];
};

struct CreatureStrategy {
  void Invoke();
};

struct PlanetModel {
  void DirectionToSurfacePosition(int a, int b);
};

struct GameObject {
  uint8_t mPad00[0xc0];
  void** mpVtable;            // +0xc0
  uint8_t mPadC4[0xf90 - 0xc4];
  uint8_t mFlagF90;           // +0xf90
};

typedef int (__thiscall* FnI)(void*);
typedef int (__thiscall* FnIi)(void*, int);
typedef float (__thiscall* FnF)(void*);

// ---------------------------------------------------------------------------
// external helpers (defined in other translation units)
// ---------------------------------------------------------------------------
void*  FUN_00c04590(IRef** out);                       // 0x00c04590
void*  FUN_00c04590_obj();                             // placeholder
void   FUN_00d99e20(int value);                        // 0x00d99e20
void   FUN_00d99ac0(void* a, void* b, int c);          // 0x00d99ac0
void   FUN_00c14750(int flag);                         // 0x00c14750
void*  FUN_00d99500(uint32_t handle);                  // 0x00d99500
void*  FUN_00c04590_ctx(void);                         // 0x00c04590
void   FUN_00d7d160(void* x);                          // 0x00d7d160
void   FUN_00c0b8a0(void* x);                          // 0x00c0b8a0
void   FUN_00c0c130(void* x);                          // 0x00c0c130
void   FUN_00c0b860(void* x);                          // 0x00c0b860
void   FUN_00c0b780(void* x);                          // 0x00c0b780
int    FUN_00d39360();                                 // 0x00d39360 (thiscall)
void*  FUN_00c13c60(int a, int b, int c);              // 0x00c13c60
int    FUN_00c0f8f0(int x);                            // 0x00c0f8f0
int    FUN_00bc97f0(int a, int b, int c, void* d);     // 0x00bc97f0
char   FUN_00c0c0e0();                                 // 0x00c0c0e0
char   FUN_00c0d560(void* a, int b, float c);          // 0x00c0d560
void*  SP_NounManager();                               // SP::NounManager
void*  SP_PlanetModel(int a, int b);                   // 0xb3d350
void*  SP_GetPlayerEmpire();                           // 0x01021300
void*  FUN_00ac80d0(void* a, void* b);                 // 0x00ac80d0
int    FUN_00c30c60(void* x);                          // 0x00c30c60
void*  FUN_00b3d2a0(void* x);                          // 0xb3d2a0

CreatureStrategy* __stdcall CreatureStrategy_Instance(uint32_t id, StrategyCtx* ctx); // 0xd38840

extern uint32_t gRandomMax;        // 0x01582ec8
extern int      gRandomBase;       // 0x01582ec4
extern const float kScale001;      // 0x013f9428
extern const float kScaleTwo;      // 0x01470f1c

// ===========================================================================
// 0x00d65250 -- remove an object from the manager's intrusive list
// ===========================================================================
// @ 0x00d65250
void IntrusiveList::Remove(IRef** object)
{
  ListNode* node = mHead.mpNext;
  while (node != &mHead) {
    IRef* obj = node->mpObject;
    node = node->mpNext;
    if (obj == *object) {
      ListNode* curr = node->mpPrev;
      curr->mpPrev->mpNext = curr->mpNext;
      curr->mpNext->mpPrev = curr->mpPrev;
      if (curr->mpObject != 0)
        curr->mpObject->Release();
      curr->mpNext = mpFree;
      mpFree = curr;
    }
  }
}

// ===========================================================================
// 0x00d652a0 -- pop a block from the pool free list, or grow the pool
// ===========================================================================
// @ 0x00d652a0
void* Pool::Alloc(IRef** object)
{
  FreeListAlloc* alloc = &mAlloc;
  void* block;
  for (;;) {
    if (alloc->mpFree != 0) {
      block = alloc->mpFree;
      alloc->mpFree = *(void**)block;
      break;
    }
    if (!alloc->AddCore(0, 0)) {
      block = 0;
      break;
    }
  }

  PoolBlock* b = (PoolBlock*)block;
  if ((int*)b + 2 != 0) {
    IRef* o = *object;
    b->mpObject = o;
    if (o != 0)
      o->AddRef();
  }
  return block;
}

// ===========================================================================
// 0x00d652f0 -- detach an object from its manager and release it
// ===========================================================================
// @ 0x00d652f0
void FUN_00d652f0(IRef* object)
{
  if (object != 0)
    object->AddRef();

  Manager* mgr = (Manager*)object->Get(&object);
  mgr->mList.Remove(&object);

  if (object != 0)
    object->Release();
}

// ===========================================================================
// 0x00d65330 -- choose the closest target and hand it to the combat system
// ===========================================================================
struct AimObject {
  uint8_t mPad00[0xc0];
  void** mpVtable;            // +0xc0
};

struct AimResult {
  uint8_t mValid;             // +0x00
  uint8_t mPad01[3];
  int mField04;               // +0x04
  int mField08;               // +0x08
  int mField0c;               // +0x0c
};

// @ 0x00d65330
uint32_t FUN_00d65330(int* self, uint32_t arg2, uint32_t arg3,
                      int arg4, uint32_t arg5, AimResult* out)
{
  void* ctx = FUN_00b3d2a0(0);
  int* world = (int*)((uint8_t*)ctx + 0x164);
  void* handle = FUN_00d99500((uint32_t)world);
  if (handle == 0)
    return 0;

  int* anchor = (int*)((uint8_t*)world + 0xc0);
  out->mValid = 0;
  int* pos = (int*)((FnI)(*(void***)anchor)[0x2c / 4])(anchor);
  *(int*)&out->mField04 = pos[0];
  *(int*)&out->mField08 = pos[1];
  *(int*)&out->mField0c = pos[2];

  char ok = (char)((FnI)(*(void***)((uint8_t*)self[0x30] + 0))[0xf8 / 4])((void*)self[0x30]);
  if (ok == 0)
    FUN_00c14750(1);

  FUN_00d99ac0(anchor, self + 0x30, 1);

  float* a = (float*)((FnI)(*(void***)anchor)[0x2c / 4])(anchor);
  int* list = (int*)((uint8_t*)ctx + 0x168);
  (void)list;
  (void)a;
  (void)arg2; (void)arg3; (void)arg4; (void)arg5;
  return 0;
}

// ===========================================================================
// 0x00d65500 -- invoke the creature-mode strategy with a three-word context
// ===========================================================================
// @ 0x00d65500
void FUN_00d65500(int param)
{
  StrategyCtx ctx;
  ctx.mField0 = 0;
  ctx.mField1 = 0;
  ctx.mField2 = param;

  CreatureStrategy* s = CreatureStrategy_Instance(0xd3353637, &ctx);
  s->Invoke();
}

// ===========================================================================
// 0x00d65530 -- random float in [base, base + 1), optionally doubled
// ===========================================================================
// @ 0x00d65530
long double FUN_00d65530(float base, char doubled)
{
  RNG* rng = (RNG*)0x1601760;
  uint32_t r = rng->Uniform(gRandomMax);
  float value = (float)(gRandomBase + (int)r) * 0.001f + base;
  if (doubled)
    value = value * 2.0f;
  return value;
}

// ===========================================================================
// 0x00d65580 -- project a position onto the planet surface
// ===========================================================================
// @ 0x00d65580
int FUN_00d65580(int param1, int param2, int param3)
{
  PlanetModel* pm = (PlanetModel*)SP_PlanetModel(param1, param3);
  pm->DirectionToSurfacePosition(param1, param3);

  GameObject* go = (GameObject*)param2;
  if (go->mFlagF90 != 0) {
    void** vt = go->mpVtable;
    int r = ((FnIi)vt[0x2c / 4])(&go->mpVtable, param1);
    FUN_00d99e20(r);
  }
  return param1;
}

// ===========================================================================
// 0x00d655d0 -- pick the nearest valid interactable
// ===========================================================================
// @ 0x00d655d0
int FUN_00d655d0(int* self, void* target, uint32_t arg3, uint32_t arg4)
{
  if (target == 0)
    return 0;

  uint8_t* t = (uint8_t*)target;
  void** tvt = *(void***)(t + 0xc0);
  char usable = (char)((FnI)tvt[0x58 / 4])(t + 0xc0);
  if (!usable)
    return 0;

  float* a = (float*)((FnI)(*(void***)((uint8_t*)self[0x30] + 0))[0x2c / 4])
                 ((uint8_t*)self[0x30]);
  float* b = (float*)((FnI)tvt[0x2c / 4])(t + 0xc0);
  float dx = a[0] - b[0];
  float dy = a[1] - b[1];
  float dz = a[2] - b[2];
  float best = dx * dx + dy * dy + dz * dz;

  uint32_t flags = *(uint32_t*)(t + 0xb58);
  if ((flags >> 9) & 1) {
    int found = 0;
    uint32_t* items = (uint32_t*)SP_NounManager();
    (void)items;
    (void)arg3; (void)arg4;
    return found;
  }

  void* avatar = (void*)FUN_00c30c60(SP_NounManager());
  void* rec = FUN_00d99500((uint32_t)avatar);
  if (rec != 0) {
    void** vt = *(void***)((uint8_t*)rec + 0xc0);
    float* c = (float*)((FnI)vt[0x2c / 4])((uint8_t*)rec + 0xc0);
    float ex = a[0] - c[0];
    float ey = a[1] - c[1];
    float ez = a[2] - c[2];
    float d = ex * ex + ey * ey + ez * ez;
    if (d < best)
      return (int)rec;
  }
  return 0;
}

// ===========================================================================
// 0x00d65850 -- true when the object at +0x28/+0xb4c/+0x600 is the known type
// ===========================================================================
// @ 0x00d65850
bool __fastcall FUN_00d65850(int* self)
{
  int* p = *(int**)(*(int**)(*(int**)((uint8_t*)self + 0x28) + 0xb4c) + 0x600);
  bool result = false;
  if (p != 0)
    result = p[2] == 0x060995fc;
  return result;
}

// ===========================================================================
// 0x00d659e0 -- decide whether a combatant should keep fighting
// ===========================================================================
// @ 0x00d659e0
uint32_t FUN_00d659e0(int self, void* creature, uint8_t flags, void* combatant,
                      int* param5)
{
  if (combatant == 0)
    return 1;

  void** cvt = *(void***)combatant;
  int data = ((FnI)cvt[8 / 4])(combatant);
  if (*(char*)(data + 0x75) == 0)
    return 1;

  void* obj = (void*)((FnI)cvt[0xc / 4])(combatant);
  void** ovt = *(void***)obj;
  char c = (char)((FnI)ovt[0x2c / 4])(obj);
  if (c != 0)
    return 1;

  if (param5 == 0)
    return 0;
  (void)creature; (void)flags; (void)self;
  return 0;
}

// ===========================================================================
// 0x00d65c40 -- SP::FIGHT_Tick
// ===========================================================================
// @ 0x00d65c40
uint32_t FIGHT_Tick(int self, void* creature, int* param3)
{
  if (*(int*)(self + 0x38) != 0) {
    char done = (char)((FnIi)(*(void***)((uint8_t*)creature + 0xc0))[0x48 / 4])
                    ((uint8_t*)creature + 0xc0, *(int*)(self + 0x38));
    if (done != 0) {
      ((FnIi)(*(void***)((uint8_t*)creature + 0))[0x40 / 4])
          (creature, 0x035ee245);
      *(int*)(self + 0x38) = 0;
    }
    return 1;
  }

  if (*(int*)(self + 0x3c) == 0) {
    char can = FUN_00c0c0e0();
    if (can != 0) {
      (void)param3;
      *(int*)(self + 0x40) = 0;
    }
  } else {
    char done = (char)((FnIi)(*(void***)((uint8_t*)creature + 0xc0))[0x48 / 4])
                    ((uint8_t*)creature + 0xc0, *(int*)(self + 0x3c));
    if (done == 0)
      return 1;
    *(int*)(self + 0x3c) = 0;
  }

  if (*(int*)(self + 0x34) == 0) {
    (void)param3;
  }

  if (*(char*)(self + 0x44) != 0 && FUN_00c0c0e0() == 0 &&
      *(int*)(self + 0x18) != 0) {
    return 0;
  }
  return 0;
}

// ===========================================================================
// 0x00d65fe0 -- SP::LOUNGE_VIGNETTE_Decide
// ===========================================================================
// @ 0x00d65fe0
uint32_t FUN_00d65fe0(int self, uint32_t arg2, int* actor, float lo, float hi)
{
  int data = ((FnI)(*(void***)actor)[8 / 4])(actor);
  char ok = FUN_00c0c0e0();
  if (ok != 0 && data != 0) {
    void* obj = (void*)FUN_00c13c60(data, 0, 1);
    if (obj != 0) {
      int picked = FUN_00c0f8f0((int)obj);
      if (picked < 0) {
        float mid = *(float*)(self + 0x1c);
        if (mid <= hi && lo <= mid) {
          void* v = (void*)((FnI)(*(void***)actor)[0xc / 4])(actor);
          int created = FUN_00bc97f0(0, 0x40000, 0x40a00000, v);
          if (created != 0) {
            *(int*)(created + 0xc) = 4;
            return 1;
          }
        }
      }
    }
    (void)arg2;
  }
  return 0;
}

// ===========================================================================
// 0x00d660a0 -- scan forward for the next valid 0x18-byte record
// ===========================================================================
// @ 0x00d660a0
int RecordArray::FindNext(int index)
{
  uint32_t* p = mpData + index * 6;
  uint32_t value = *p;
  if ((value >> 30) & 1)
    return 0x3fffffff;

  for (;;) {
    value = p[6];
    p += 6;
    ++index;
    if ((value >> 31) == 0)
      return index;
    if ((value >> 30) & 1)
      return 0x3fffffff;
  }
}

// ===========================================================================
// 0x00d660e0 -- copy a variant if the source holds a valid payload
// ===========================================================================
// @ 0x00d660e0
void Variant::CopyFrom(const int* src)
{
  int* dst = (int*)this;
  dst[0] = src[0];
  if ((((uint32_t)src[0] >> 31) & 1) == 0 && dst + 1 != 0) {
    dst[1] = src[1];
    dst[2] = src[2];
    dst[3] = src[3];
    dst[4] = src[4];
    dst[5] = src[5];
  }
}

// ===========================================================================
// 0x00d66120 -- assign a variant, discarding the old payload when necessary
// ===========================================================================
// @ 0x00d66120
void Variant::AssignFrom(const int* src)
{
  if ((((uint32_t)src[0] >> 31) & 1) == 0) {
    if ((((uint32_t)mField[0] >> 31) & 1) != 0) {
      int* d = &mField[1];
      if (d != 0) {
        d[0] = src[1];
        d[1] = src[2];
        d[2] = src[3];
        d[3] = src[4];
        d[4] = src[5];
        mField[0] = src[0];
        return;
      }
    } else {
      mField[1] = src[1];
      mField[2] = src[2];
      mField[3] = src[3];
      mField[4] = src[4];
      mField[5] = src[5];
    }
  }
  mField[0] = src[0];
}
