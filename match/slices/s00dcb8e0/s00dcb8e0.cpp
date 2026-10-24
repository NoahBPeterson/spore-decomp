// Decompiled slice s00dcb8e0 -- vehicle-tree behaviour helpers.
// Reconstructed from the shipped binary; helper addresses noted per call.
#include "types.h"

// ---------------------------------------------------------------------------
// generic vtable helpers (all calls below are resolved from the live vtable)
// ---------------------------------------------------------------------------
typedef int    (__thiscall* FnI)(void*);
typedef int    (__thiscall* FnIi)(void*, int);
typedef float* (__thiscall* FnFP)(void*);
typedef void*  (__thiscall* FnVP)(void*, int);

struct VTable { void* p[64]; };

static inline int CallV(void* obj, int slot)
{
  return ((FnI)(*(VTable**)obj)->p[slot / 4])(obj);
}

static inline int CallVBool(void* obj, int slot)
{
  return ((FnI)(*(VTable**)obj)->p[slot / 4])(obj) & 1;
}

static inline int CallVArg(void* obj, int slot, int arg)
{
  return ((FnIi)(*(VTable**)obj)->p[slot / 4])(obj, arg);
}

static inline float* CallVPos(void* obj, int slot)
{
  return ((FnFP)(*(VTable**)obj)->p[slot / 4])(obj);
}

static inline void* CallVArgP(void* obj, int slot, int arg)
{
  return ((FnVP)(*(VTable**)obj)->p[slot / 4])(obj, arg);
}

extern "C" float sqrtf(float);

// ---------------------------------------------------------------------------
// shared shapes
// ---------------------------------------------------------------------------
struct Vector24 {
  uint8_t   mPad00[0x24];
  uint32_t* mpBegin;          // +0x24
  uint32_t* mpEnd;            // +0x28
  uint32_t* mpCap;            // +0x2c

  void PushUnique(uint32_t value);
};

struct Locomotive {
  virtual void v00();         // +0x00 (vptr lives here)

  bool IsNearGoal();          // 0x00c42e20
};

struct Stimuli {
  void ClearAll(int flags, int mode);   // 0x00bc98f0
};

struct VectorErase {
  void* mpBegin;              // +0x00
  void* mpEnd;                // +0x04
  void* mpCap;                // +0x08

  void erase(void* first, void* last);  // 0x00b48e40
};

struct Brain {
  void*    mpObj0;            // +0x00
  uint8_t  mPad04[0x0c];      // +0x04
  int      mMode10;           // +0x10
};

struct NounManagerObj {
  void RemoveNoun(uint32_t noun);       // 0x00b225d0
};

struct BehaviorObj {
  uint8_t   mPad00[0x10];     // +0x000
  uint32_t* mpNouns;          // +0x010
  uint32_t* mpNounsEnd;       // +0x014
  uint8_t   mPad18[0x0c];     // +0x018
  uint32_t* mpVec24;          // +0x024
  uint32_t* mpVec24End;       // +0x028
  uint32_t* mpVec24Cap;       // +0x02c
  uint8_t   mPad30[0x04];     // +0x030
  Locomotive mLoco;           // +0x034
  VectorErase mVec38;         // +0x038
  uint8_t   mPad44[0x0c];     // +0x044
  uint32_t* mpVec50;          // +0x050
  uint32_t* mpVec50End;       // +0x054
  uint32_t* mpVec50Cap;       // +0x058
  uint8_t   mPad5c[0x34];     // +0x05c
  int       mField90;         // +0x090
  uint8_t   mPad94[0x210];    // +0x094
  uint32_t  mFlags2a4;        // +0x2a4
  uint8_t   mPad2a8[0x260];   // +0x2a8
  void*     mpObj508;         // +0x508
  uint8_t   mPad50c[0x5e4];   // +0x50c
  void*     mpObjAf0;         // +0xaf0
  uint8_t   mPadAf4[0x0c];    // +0xaf4
  int       mFieldB00;        // +0xb00
  uint32_t  mFieldB04;        // +0xb04
  uint32_t  mFieldB08;        // +0xb08
  uint8_t   mPadB0c[0x14];    // +0xb0c
  int       mFieldB20;        // +0xb20
  uint8_t   mPadB24[0x04];    // +0xb24
  int       mFieldB28;        // +0xb28
  uint8_t   mPadB2c[0x2c];    // +0xb2c
  float     mFieldB58;        // +0xb58
  uint8_t   mPadB5c[0x20];    // +0xb5c
  void*     mpObjB7c;         // +0xb7c

  Brain* GetBrain();                            // 0x00ca71d0
  void*  GetNearby();                           // 0x00c9fee0
  void   FUN_00cacbe0();                        // 0x00cacbe0
  void   RemoveNouns();                         // 0x00dcc2c0
  void   AddFeedback(void* event);              // 0x00dcc350
};

struct CombatCtx {
  void* mpTarget;             // +0x00
  float mPosX;                // +0x04
  float mPosY;                // +0x08
  float mPosZ;                // +0x0c
  float mTimer;               // +0x10
};

struct TimerCtx {
  float   mTimer;             // +0x00
  uint8_t mFlag;              // +0x04
};

struct StateCtx {
  uint8_t mPad00[0x20];       // +0x00
  uint8_t mFlag20;            // +0x20
  uint8_t mFlag21;            // +0x21
};

struct TradeCtx {
  int     mField0;            // +0x00
  int     mField4;            // +0x04
  uint8_t mFlag8;             // +0x08
};

// ---------------------------------------------------------------------------
// external helpers (defined in other translation units)
// ---------------------------------------------------------------------------
void*  AllocSimObject(uint32_t size, const char* name, int a, int b, int c, int d);
void*  __stdcall VectorInsertU32(uint32_t* pos, uint32_t* value); // 0x004558a0
void*  __fastcall SimSingleton_ctor(void* mem);         // 0x00dc7d70
void*  SP_GetCurrentGameMode();                         // 0x00??????
void*  FUN_00dc9680(BehaviorObj* self);                 // 0x00dc9680
void*  FUN_00dc5050(BehaviorObj* self, void* city);     // 0x00dc5050
void   FUN_00ca7250(BehaviorObj* self, const char* msg); // 0x00ca7250
void   FUN_00caa900(BehaviorObj* self);                 // 0x00caa900
void   FUN_00ca80e0(BehaviorObj* self, int value);      // 0x00ca80e0
void   FUN_00cacbe0(BehaviorObj* self);                 // 0x00cacbe0
void   AttemptRepark(BehaviorObj* self);                // 0x00dc9430
void   FUN_00dc4ed0(float* a, float* b, BehaviorObj* self, void* obj); // 0x00dc4ed0
void   FUN_00ca97a0(float* pos, float a, float b);      // 0x00ca97a0
void   FUN_00c9fb40(float x, float y, float z, float a, float b); // 0x00c9fb40
float  FUN_00f264b0(BehaviorObj* self);                 // 0x00f264b0
float  FUN_00bfc400();                                  // 0x00bfc400
int    FUN_00c9f1c0();                                  // 0x00c9f1c0
int    FUN_00c41ec0();                                  // 0x00c41ec0
float* FUN_00c421f0();                                  // 0x00c421f0
int    __fastcall GetDamageState(void* combatant);      // SP::cCombatant
char   __fastcall Flag388(void* obj);                   // 0x00c0c0e0
NounManagerObj* NounManager(uint32_t noun);             // 0x00b3d300
void*  FUN_00dcc440(BehaviorObj* self, int specialty, void* exclude); // 0x00dcc440
uint8_t FUN_00dcc0a0(BehaviorObj* self, StateCtx* ctx, float dt); // 0x00dcc0a0
void   FUN_00dcc610(BehaviorObj* self);                 // 0x00dcc610
uint8_t StandardVehicleMoveTick(BehaviorObj* self);     // anonymous namespace

extern uint8_t  DAT_01654c10;              // current-game-mode marker
extern void*    gVehicleTicker;            // 0x01699ab8
extern uint32_t gVehicleServiceTable708;   // 0x0147c708
extern uint32_t gVehicleServiceTable714;   // 0x0147c714

// ===========================================================================
// 0x00dcb8e0 -- steer a vehicle toward a combat target
// ===========================================================================
// @ 0x00dcb8e0
uint32_t FUN_00dcb8e0(BehaviorObj* self, CombatCtx* ctx, float dt)
{
  int myId = CallV(&self->mLoco, 0x4c);
  if (myId != -1) {
    void* target = ctx->mpTarget;
    void* targetObj = (void*)CallV(target, 0x0c);
    int targetId = CallV(targetObj, 0x4c);
    int selfId = CallV(&self->mLoco, 0x4c);
    if (targetId == selfId &&
        (((uint32_t*)self->mpObjAf0)[0x1c8 / 4] & 0x2000) == 0)
      return 0;
  }

  if (GetDamageState(ctx->mpTarget) == 2)
    return 0;

  void* posObj = (void*)CallV(ctx->mpTarget, 0x08);
  float* targetPos = CallVPos(posObj, 0x2c);
  float tx = targetPos[0];
  float ty = targetPos[1];
  float tz = targetPos[2];
  float* selfPos = CallVPos(&self->mLoco, 0x2c);
  float dx = tx - selfPos[0];
  float dy = ty - selfPos[1];
  float dz = tz - selfPos[2];
  float dist = sqrtf(dx * dx + dy * dy + dz * dz);
  float limit = 0.0f;

  void* mode = SP_GetCurrentGameMode();
  if (mode == &DAT_01654c10) {
    limit = FUN_00f264b0(self);
    if (dist <= limit) {
      ctx->mTimer = 0.0f;
    } else {
      ctx->mTimer = ctx->mTimer + dt;
      if (ctx->mTimer > 5.0f) {
        CallV(self->mpObj508, 0x50);
      }
    }
  }

  float reach = FUN_00bfc400();
  if (dist < reach) {
    ctx->mPosX = tx;
    ctx->mPosY = ty;
    ctx->mPosZ = tz;
    float a = dist - 1.0f;
    float b = dist * 0.75f;
    void* obj = (void*)CallV(ctx->mpTarget, 0x08);
    FUN_00dc4ed0(&a, &b, self, obj);
    FUN_00ca97a0(&tx, a, b);
    FUN_00c9fb40(tx, ty, tz, a, b);
  }
  return 1;
}

// ===========================================================================
// 0x00dcbe00 -- advance the wander timer and fire the completion callback
// ===========================================================================
// @ 0x00dcbe00
uint32_t FUN_00dcbe00(BehaviorObj* self, TimerCtx* ctx, float dt)
{
  ctx->mTimer = ctx->mTimer + dt;

  float threshold;
  if (SP_GetCurrentGameMode() == &DAT_01654c10)
    threshold = 0.0f;
  else
    threshold = 3.0f;

  if (threshold < ctx->mTimer && ctx->mFlag == 0) {
    ctx->mFlag = 1;
    FUN_00dc9680(self);
  }
  return 1;
}

// ===========================================================================
// 0x00dcbeb0 -- vehicle wander tick: repark or resume
// ===========================================================================
// @ 0x00dcbeb0
uint32_t FUN_00dcbeb0(BehaviorObj* self)
{
  if (self->mLoco.IsNearGoal()) {
    ((Stimuli*)((uint8_t*)self->mpObjAf0 + 8))->ClearAll(0x1000, 0);
    return 0;
  }
  if ((self->mFlags2a4 & 2) != 0) {
    AttemptRepark(self);
    return 1;
  }
  if ((self->mFlags2a4 & 4) != 0)
    FUN_00cacbe0(self);
  return 1;
}

// ===========================================================================
// 0x00dcc0a0 -- vehicle movement / wander state machine
// ===========================================================================
// @ 0x00dcc0a0
uint8_t FUN_00dcc0a0(BehaviorObj* self, StateCtx* ctx, float dt)
{
  float px = 0.0f, py = 0.0f, pz = 0.0f;

  if ((self->mFlags2a4 & 8) != 0) {
    ctx->mFlag21 = 1;
    float* pos = CallVPos(&self->mLoco, 0x2c);
    px = pos[0]; py = pos[1]; pz = pos[2];
    float heading = (float)CallV(&self->mLoco, 0x74);
    CallVArgP(&self->mLoco, 0xe4, *(int*)&heading);
    FUN_00c9fb40(px, py, pz, 0.0f, (float)CallV(&self->mLoco, 0x74));
    return 1;
  }

  if (ctx->mFlag20 == 0) {
    if (!self->mLoco.IsNearGoal() && dt <= 120.0f) {
      ctx->mFlag20 = 1;
      return StandardVehicleMoveTick(self);
    }
    ctx->mFlag20 = 1;
    if (ctx->mFlag21 != 0) {
      ctx->mFlag21 = 0;
      return 1;
    }
  }
  return 1;
}

// ===========================================================================
// 0x00dcc2c0 -- drop every noun held by this behaviour
// ===========================================================================
// @ 0x00dcc2c0
void BehaviorObj::RemoveNouns()
{
  mVec38.erase(mVec38.mpBegin, mVec38.mpEnd);

  int count = (int)(mpNounsEnd - mpNouns);
  for (int i = 0; i < count; ++i) {
    uint32_t noun = mpNouns[i];
    NounManager(noun)->RemoveNoun(noun);
  }
}

// ===========================================================================
// 0x00dcc300 -- append a value to a uint vector unless it is already present
// ===========================================================================
// @ 0x00dcc300
void Vector24::PushUnique(uint32_t value)
{
  uint32_t** v = &mpBegin;
  uint32_t* end = v[1];
  uint32_t* p = v[0];

  if (p != end) {
    do {
      if (*p == value)
        break;
      ++p;
    } while (p != end);
  }
  if (p != end)
    return;

  if (end < v[2]) {
    uint32_t* slot = end;
    v[1] = slot + 1;
    if (slot != 0) {
      *slot = value;
      return;
    }
  } else {
    VectorInsertU32(end, &value);
  }
}

// ===========================================================================
// 0x00dcc350 -- register a feedback event once
// ===========================================================================
// @ 0x00dcc350
void BehaviorObj::AddFeedback(void* event)
{
  if (event != 0)
    CallV(event, 0x00);

  uint32_t* p = mpVec50;
  while (p != mpVec50End) {
    if ((void*)*p == event)
      break;
    ++p;
  }
  if (p != mpVec50End)
    return;

  if (event != 0)
    CallV(event, 0x00);

  if (mpVec50End < mpVec50Cap) {
    uint32_t* slot = mpVec50End;
    mpVec50End = slot + 1;
    if (slot != 0)
      *slot = (uint32_t)event;
  } else {
    VectorInsertU32(mpVec50End, (uint32_t*)&event);
  }

  if (event != 0)
    CallV(event, 0x04);
}

// ===========================================================================
// 0x00dcc440 -- choose a city for a trade order
// ===========================================================================
// @ 0x00dcc440
void* FUN_00dcc440(BehaviorObj* self, int specialty, void* exclude)
{
  if (self->mpObj508 == 0)
    return 0;

  int handle = CallV(self->mpObj508, 0x10);
  NounManagerObj* nm = NounManager((uint32_t)handle);
  if (nm == 0)
    return 0;

  void* first = 0;
  (void)specialty;
  (void)exclude;
  return first;
}

// ===========================================================================
// 0x00dcc5c0 -- push the vehicle's service id into the ticker vector
// ===========================================================================
// @ 0x00dcc5c0
void FUN_00dcc5c0(BehaviorObj* self)
{
  int index = self->mFieldB20;

  if (gVehicleTicker == 0) {
    void* mem = AllocSimObject(0x58, "Simulator/SimSingleton", 0, 0, 0, 0);
    if (mem == 0)
      gVehicleTicker = 0;
    else
      gVehicleTicker = SimSingleton_ctor(mem);
  }

  ((Vector24*)gVehicleTicker)->PushUnique(
      (&gVehicleServiceTable708)[index]);
}

// ===========================================================================
// 0x00dcc610 -- choose the service slot and push it into the ticker vector
// ===========================================================================
// @ 0x00dcc610
void FUN_00dcc610(BehaviorObj* self)
{
  if (!CallV(&self->mLoco, 0x58))
    return;

  int mode = 0;
  Brain* brain = self->GetBrain();

  if (brain->mMode10 == 1) {
    void* nearby = self->GetNearby();
    if (nearby != 0) {
      void* p = CallVArgP(nearby, 0xb8, 0xd0036e08);
      if (p != 0 && Flag388(p))
        mode = 1;
    }
  } else if (brain->mMode10 == 8) {
    int r = CallV(brain->mpObj0, 0x20);
    mode = (r != 0x403df5c) + 2;
  }

  int index = self->mFieldB20;
  index = index + mode * 3;

  if (gVehicleTicker == 0) {
    void* mem = AllocSimObject(0x58, "Simulator/SimSingleton", 0, 0, 0, 0);
    void* obj;
    if (mem != 0)
      obj = SimSingleton_ctor(mem);
    else
      obj = 0;
    gVehicleTicker = obj;
  }

  ((Vector24*)gVehicleTicker)->PushUnique(
      (&gVehicleServiceTable714)[index]);
}

// ===========================================================================
// 0x00dcc6e0 -- retarget the nearby-record pointer and refresh the ticker
// ===========================================================================
// @ 0x00dcc6e0
bool FUN_00dcc6e0(BehaviorObj* self)
{
  Brain* brain = self->GetBrain();

  void* found;
  if (brain->mpObj0 != 0)
    found = CallVArgP(brain->mpObj0, 0x0c, 0x01186577);
  else
    found = 0;

  void* old = self->mpObjB7c;
  if (found != old) {
    if (found != 0)
      CallV(found, 0xbc);
    self->mpObjB7c = found;
    if (old != 0)
      CallV(old, 0xc0);
  }

  FUN_00dcc610(self);
  return true;
}

// ===========================================================================
// 0x00dcc750 -- SP::VehicleTree::TradeWithCityOrder_Activate
// ===========================================================================
// @ 0x00dcc750
uint32_t TradeWithCityOrder_Activate(BehaviorObj* self, int a2, int a3,
                                     int a4, int a5, TradeCtx* ctx)
{
  if (ctx != 0) {
    ctx->mField0 = 0;
    ctx->mFlag8 = 0;
  }

  if (self->mFieldB28 == 1 && self->mFieldB58 != 0.0f) {
    ctx->mField0 = 3;
    Brain* brain = self->GetBrain();
    if (brain->mpObj0 != 0) {
      void* city = CallVArgP(brain->mpObj0, 0x0c, 0xee9b2232);
      if (city != 0) {
        if (!CallVBool(city, 0x2c)) {
          FUN_00dc5050(self, city);
          FUN_00ca80e0(self, 0x14);
          return 1;
        }
      }
    }
    FUN_00ca7250(self, "(20) trade: no city");
    FUN_00caa900(self);
    return 0;
  }

  ctx->mField0 = 0;
  void* city = FUN_00dcc440(self, 2, 0);
  if (city == 0) {
    FUN_00ca7250(self, "(19) trade: no city");
    FUN_00caa900(self);
    return 0;
  }
  FUN_00dc5050(self, city);
  return 1;
}
