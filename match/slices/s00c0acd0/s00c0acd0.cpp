// Slice s00c0acd0 -- Simulator creature update/serialization helpers.
// Flags: /O2 /MD /Gy /EHsc /TP

#include <stddef.h>
#include <algorithm>
#include "SP/cVarListSerializer.h"
#include "SP/cLocomotiveObject.h"
#include "SP/cField.h"

typedef unsigned int uint;
typedef unsigned char uchar;
typedef unsigned long long uint64;

// ---- globals ---------------------------------------------------------------
extern float g_1485378;         // 0.0f
extern float g_13f9428;         // 0.001f
extern float g_13f4fd0;         // 4294967296.0f
extern float g_146a32c;         // FLT_MAX
extern float g_150c8e4, g_150c8e8, g_150c8ec, g_150c8f0;
extern float g_150c8f4, g_150c8f8, g_150c8fc;
extern float g_150c888, g_150c88c;
extern float g_1687a00, g_1687a04, g_1687a0c, g_1687a10, g_1687a14;
extern float g_1687a2c, g_1687a30, g_169e288;
extern int   g_168d900;
extern uchar g_168db6c;
extern int   g_168d9bc, g_168da00, g_168da44, g_168da88, g_168dacc, g_168db10;

struct AllocRec { char pad[0x40]; };
extern AllocRec g_168d998;

// ---- opaque services -------------------------------------------------------
namespace EA { namespace Random {
class RandomLinearCongruential {
 public:
  unsigned int RandomUint32Uniform(unsigned int);
  float RandomDoubleUniform();
};
} }
#define GRAND ((EA::Random::RandomLinearCongruential*)0x1601760)

bool __cdecl SP_GetPropertyAsUint32Array(unsigned int prop, unsigned int arg,
                                         int* count, int** data);
int  __cdecl SP_GetCurrentGameMode();

struct AgentOrderManager {
  void __thiscall Tick(float);
  void __thiscall Activate(int, int, void*, float, void*, void*);
};
struct ModifiersCtorHelper {
  void* __thiscall Exist(AllocRec*);
};

void* __cdecl operator new(size_t, const char*, int, int, int, int);
void* __cdecl EAAllocate(size_t, const char*, int, int, int, int);

// Serialization stream helpers.
bool __cdecl WriteUint32(void* stream, const void* data, int count, int flags);
bool __cdecl WriteUint64(void* stream, const void* data, int count, int flags);
bool __cdecl ReadUint64(void* stream, void* data, int count, int flags);
bool __cdecl ReadInt32(void* stream, void* data, int count, int flags);
bool __cdecl ReadBool(void* stream, void* data);
void __cdecl StreamWriteBool(void* stream, const void* data, int count);

struct IStreamObj {
  virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
  virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
  virtual void* GetInner();                 // +0x20
  virtual void v24();
};
struct IInnerObj {
  virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
  virtual void v10(); virtual void v14();
  virtual void* GetStream();                // +0x18
};

// ---- raw creature layout ---------------------------------------------------
namespace Simulator {

struct SpeciesData {
  char pad0[0x58c];
  float mAge;                               // +0x58c
  char pad1[0x608 - 0x590];
  unsigned int m608;
  unsigned int m60c;
};

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
  SpeciesData* mpSpecies;                   // +0xb20
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
  int m_b88;                                // +0xb88
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
  int  TimerDelta(cCreatureBase*);
  void ClampHunger(float);
  void SetHunger(float);
  void ResetHunger();
  void TickCooldowns();
};

}  // namespace Simulator

typedef Simulator::cCreatureBase CB;
typedef Simulator::SpeciesData SpeciesData;

struct AnimCreature {
  int __thiscall GetSomeCount();
};
struct TimerThing {
  void __thiscall Func(float);
};
struct RefHolder {
  void* mpObject;
  void __thiscall Release();
};
struct TuningObj {
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

// generic accessor callees
int  __fastcall FUN_00b3d4c0(CB*);
void* __fastcall FUN_00b3d310(CB*);
int  __fastcall FUN_008e7f80(void*);
bool __fastcall FUN_00c0e420(CB*);
int  __fastcall FUN_00a02ba0(void*);
bool __fastcall FUN_00c0bb90(CB*);
extern "C" {
void  __cdecl FUN_00bc9cc0(void*, float);
void  __fastcall FUN_00c050b0(CB*);
void  __fastcall FUN_00c09410(CB*, float);
void  __fastcall FUN_00c03f90(CB*);
void  __fastcall FUN_00c05810(CB*, float);
void  __fastcall FUN_00c03ec0(CB*, float);
void  __fastcall FUN_00c1cdd0(CB*, unsigned int);
void  __fastcall FUN_00c1aad0(CB*, unsigned int);
void  __fastcall FUN_00c05a80(CB*, float);
void  __fastcall FUN_00c14750(CB*, int);
int   __cdecl FUN_00d998f0(void*);
float __fastcall FUN_00bfc490(void*);
void  __fastcall FUN_00c0d0c0(CB*, int, int);
bool  __cdecl FUN_00b18590(CB*, void*);
bool  __cdecl FUN_00cee3d0(void*, void*);
bool  __cdecl FUN_00c448a0(void*, void*);
bool  __cdecl FUN_00bfc4a0(void*, void*);
bool  __cdecl FUN_00bc9a80(void*, void*);
void  __fastcall FUN_00ae6670(RefHolder*);
}

extern char g_146a334[];      // "Simulator/cModifiers"
extern char g_1571798[];
extern char g_157a1f8[];
extern char g_1574258[];

// @ 0x00c0acd0
void Simulator::cCreatureBase::Update(unsigned int delta)
{
  if (this->mp_1674 == 0) return;
  if (this->mb_b63) {
    (*(void (__thiscall**)(CB*, int))(*(void***)this)[0xc8 / 4])(this, 1);
    return;
  }
  if (this->m_1670 > delta)
    this->m_1670 -= delta;
  else
    this->m_1670 = 0;

  float dt = (float)delta * g_13f9428;
  (*(void (__thiscall**)(CB*, int))(*(void***)this)[0xac / 4])(this, 0);

  if (((this->mGeneralFlags >> 9) & 1) == 0 && this->m_eac == 2)
    FUN_00c0d0c0(this, 1, FUN_00c0bb90(this));

  if (!this->mbDead) {
    FUN_00bc9cc0(this->mp_1624, dt);
    (*(void (__thiscall**)(CB*, float))(*(void***)this)[0x88 / 4])(this, dt);
  }

  this->mpOrders->Tick(dt);

  if (FUN_008e7f80((char*)this + 0x5a8) != 2 && this->mState == 3 &&
      ((this->mFlags & 0x1000) == 0 || !this->mb_137))
    FUN_00c050b0(this);

  if (((this->mGeneralFlags >> 9) & 1) == 0)
    FUN_00c09410(this, dt);

  if ((*(bool (__thiscall**)(CB*))(*(void***)this)[0x2c / 4])(this))
    return;
  if (this->mbCasted && !this->mb_135)
    return;

  FUN_00c03f90(this);
  if (FUN_008e7f80((char*)this + 0x5a8) == 2) {
    this->m_b80 = 0.0f;
  } else {
    FUN_00c05810(this, dt);
    if (!this->mbDead && FUN_00c0e420(this) && this->mpAnimCreature != 0 &&
        FUN_00a02ba0(this->mpAnimCreature) < 1)
      FUN_00c14750(this, 0);
  }

  (*(void (__thiscall**)(CB*, float))(*(void***)this)[0x70 / 4])(this, dt);
  if (((this->mGeneralFlags >> 9) & 1) != 0)
    FUN_00c03ec0(this, dt);
  (*(void (__thiscall**)(CB*, float))(*(void***)this)[0x64 / 4])(this, dt);
  (*(void (__thiscall**)(CB*, float))(*(void***)this)[0x68 / 4])(this, dt);
  FUN_00c1cdd0(this, delta);
  FUN_00c1aad0(this, delta);
  FUN_00c05a80(this, dt);
  (*(void (__thiscall**)(CB*, unsigned int))(*(void***)this)[0x6c / 4])(this, delta);

  if (this->m_169c != 0.0f) {
    if (dt <= this->m_169c && FUN_00d998f0(this->mp_1698) != 0) {
      this->m_169c -= dt;
    } else {
      this->m_169c = 0.0f;
      ((RefHolder*)((char*)this + 0x1698))->Release();
    }
  }

  if (this->mpAnimCreature != 0)
    *(int*)((char*)this->mpAnimCreature + 0x14c) = 0;
  *(int*)((char*)this + 0xf80) += delta;
}

// @ 0x00c0af90
int SP::cLocomotiveObject::GetFieldValues(eastl::vector<SP::cField, eastl::sp_vector_allocator>& fields)
{
  SP::cVarListSerializer first(this, (SP::cDataSerializerGeneric*)g_157a1f8, 0x1a80d26);
  int n = first.GetFields(fields);
  SP::cVarListSerializer second(this, (SP::cDataSerializerGeneric*)g_1574258, 0x1a80d26);
  return second.GetFields(fields) + n;
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
  void* inner = (*(void* (__thiscall**)(void*))(*(void***)stream)[0x20 / 4])(stream);
  uint64 v = *(uint64*)(data + 8);
  void* s = (*(void* (__thiscall**)(void*))(*(void***)inner)[0x18 / 4])(inner);
  WriteUint64(s, &v, 1, 0);

  inner = (*(void* (__thiscall**)(void*))(*(void***)stream)[0x20 / 4])(stream);
  float u = *(float*)(data + 4);
  s = (*(void* (__thiscall**)(void*))(*(void***)inner)[0x18 / 4])(inner);
  WriteUint32(s, &u, 1, 0);

  inner = (*(void* (__thiscall**)(void*))(*(void***)stream)[0x20 / 4])(stream);
  s = (*(void* (__thiscall**)(void*))(*(void***)inner)[0x18 / 4])(inner);
  bool b = *data != 0;
  StreamWriteBool(s, &b, 1);

  inner = (*(void* (__thiscall**)(void*))(*(void***)stream)[0x20 / 4])(stream);
  s = (*(void* (__thiscall**)(void*))(*(void***)inner)[0x18 / 4])(inner);
  b = data[1] != 0;
  StreamWriteBool(s, &b, 1);
  return stream;
}

// @ 0x00c0b100
int* __cdecl FUN_00c0b100(int* stream, char* data)
{
  void* inner = (*(void* (__thiscall**)(void*))(*(void***)stream)[0x20 / 4])(stream);
  void* s = (*(void* (__thiscall**)(void*))(*(void***)inner)[0x18 / 4])(inner);
  ReadUint64(s, data + 8, 1, 0);

  inner = (*(void* (__thiscall**)(void*))(*(void***)stream)[0x20 / 4])(stream);
  s = (*(void* (__thiscall**)(void*))(*(void***)inner)[0x18 / 4])(inner);
  ReadInt32(s, data + 4, 1, 0);

  inner = (*(void* (__thiscall**)(void*))(*(void***)stream)[0x20 / 4])(stream);
  s = (*(void* (__thiscall**)(void*))(*(void***)inner)[0x18 / 4])(inner);
  ReadBool(s, data);

  inner = (*(void* (__thiscall**)(void*))(*(void***)stream)[0x20 / 4])(stream);
  s = (*(void* (__thiscall**)(void*))(*(void***)inner)[0x18 / 4])(inner);
  ReadBool(s, data + 1);
  return stream;
}

// @ 0x00c0b190
bool __cdecl FUN_00c0b190(CB* self, int* info)
{
  if (self == 0) return false;
  if (((self->mGeneralFlags >> 9) & 1) != 0 && info[2] == 0x3d) return false;
  return info[0x120 / 4] != -1;
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
bool __stdcall FUN_00c0b220(unsigned int arg, unsigned int* out)
{
  int mode = SP_GetCurrentGameMode();
  if (mode < 0x1654c00) return false;
  if (mode >= 0x1654c07 && mode != 0x1654c10) return false;
  int index = mode - 0x1654c00;
  if (mode == 0x1654c10) index = 6;
  return FUN_00c0b1c0(arg, out, ((int*)g_168d900)[index]);
}

// @ 0x00c0b270
bool __stdcall FUN_00c0b270(unsigned int arg, unsigned int* out)
{
  int mode = SP_GetCurrentGameMode();
  unsigned int index = (unsigned int)(mode - 0x1654c00);
  if (index > 6) return false;
  int count = 0;
  int* data = 0;
  if (!SP_GetPropertyAsUint32Array(((int*)g_168d900)[index], arg, &count, &data) ||
      count <= 0)
    return false;
  *out = GRAND->RandomUint32Uniform((unsigned int)count);
  return true;
}

// @ 0x00c0b2f0
bool __stdcall FUN_00c0b2f0(unsigned int arg, unsigned int index, unsigned int* out)
{
  int mode = SP_GetCurrentGameMode();
  unsigned int idx = (unsigned int)(mode - 0x1654c00);
  if (idx > 6) return false;
  int count = 0;
  int* data = 0;
  if (!SP_GetPropertyAsUint32Array(((int*)g_168d900)[idx], arg, &count, &data) ||
      count <= 0 || index >= (unsigned int)count)
    return false;
  *out = data[index];
  return true;
}

// @ 0x00c0b380
void* __cdecl FUN_00c0b380(CB* self, TuningObj* tuning)
{
  void* result = tuning->GetAt(0);
  switch (*(int*)((char*)tuning + 8)) {
  case 0x1e: return (void*)0x4bc047d;
  case 0x1f: return (void*)0x4bc0481;
  case 0x20: return (void*)0x5b6db0a;
  case 0x21:
    result = (void*)0x4bc0485;
    if (*(float*)((char*)self->mpSpecies + 0x58c) > 0.0f &&
        GRAND->RandomUint32Uniform(100) < 0x32)
      result = (void*)0x4c074c7;
    break;
  }
  return result;
}

// @ 0x00c0b410
bool __cdecl FUN_00c0b410()
{
  return g_169e288 >= GRAND->RandomDoubleUniform();
}

// @ 0x00c0b440
float __cdecl FUN_00c0b440(unsigned int which)
{
  float value = 1.0f;
  switch (which & ((int)which < 0 ? 0xffffffffu : 0u)) {
  case 0: return g_150c8e4;
  case 1: return g_150c8e8;
  case 2: return g_150c8ec;
  case 3: return g_150c8f0;
  case 4: return g_150c8f4;
  case 5: return g_150c8f8;
  case 6: value = g_150c8fc; break;
  }
  return value;
}

// @ 0x00c0b510
void __cdecl SP_AddSetAnimationTargetModifierA(CB* self, void* target,
                                               void* owner, void* extra)
{
  if (target == 0) return;
  int local[8];
  local[0] = (int)target;
  local[1] = 0;
  local[2] = (int)extra;
  local[3] = ++self->mAnimTargetCounter;
  self->mpOrders->Activate(3, 0, self, g_146a32c, local, owner);
}

// @ 0x00c0b570
void __cdecl SP_AddSetAnimationTargetModifierB(CB* self, void* target,
                                               float* position)
{
  if (target == 0) return;
  int local[8];
  local[0] = (int)target;
  local[1] = 0;
  local[2] = -1;
  local[3] = ++self->mAnimTargetCounter;
  ((float*)&local[4])[0] = position[0];
  ((float*)&local[4])[1] = position[1];
  ((float*)&local[4])[2] = position[2];
  self->mpOrders->Activate(3, 0, self, g_146a32c, local, 0);
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
  self->m_b8c = (int)(g_1687a30 * 1000.0f);
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
  if (self->mpSpecies->m60c > 0 && ((F_c35d20*)target)->f())
    return true;
  if (self->mpSpecies->m608 > 0 && ((F_c35d40*)target)->f())
    return true;
  return false;
}

// @ 0x00c0b810
bool __thiscall CB::CheckTargetB(void* argp)
{
  CB* self = this;
  unsigned int arg = (unsigned int)(size_t)argp;
  int base = FUN_00b3d4c0(self);
  if (base == 0) return false;
  int r = ((F_ba3f90*)base)->f((char*)self + 0xb28, self, arg);
  return r == 2 || r == 5 || r == 3 || r == 4;
}

// @ 0x00c0b860
bool __thiscall CB::CheckTargetC(void* argp)
{
  CB* self = this;
  unsigned int arg = (unsigned int)(size_t)argp;
  int base = FUN_00b3d4c0(self);
  if (base == 0) return false;
  int r = ((F_ba3f90*)base)->f((char*)self + 0xb28, self, arg);
  return r == 2 || r == 5;
}

// @ 0x00c0b8a0
bool __thiscall CB::CheckTargetD(void* argp)
{
  CB* self = this;
  unsigned int arg = (unsigned int)(size_t)argp;
  int base = FUN_00b3d4c0(self);
  if (base == 0) return false;
  return ((F_ba3f90*)base)->f((char*)self + 0xb28, self, arg) == 1;
}

// @ 0x00c0b8e0
int __thiscall CB::TimerDelta(CB* other)
{
  CB* self = this;
  return self->m_b88 - other->m_b88;
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

// @ 0x00c0b9d0
void __thiscall CB::ClampHunger(float value)
{
  value = std::min(std::max(value, g_1687a04), g_1687a00);
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
  if (self->m_b34 == 1) {
    if ((self->mGeneralFlags & 1) == 1)
      value = g_150c88c * value;
  } else {
    value = g_150c888 * value;
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

// @ 0x00c0bc20
namespace SP {
class cSPCreatureBase {
 public:
  bool Write(void* stream) const;
};
}

bool SP::cSPCreatureBase::Write(void* stream) const
{
  CB* self = (CB*)this;
  void* inner = (*(void* (__thiscall**)(void*))(*(void***)stream)[0x20 / 4])(stream);
  void* s = (*(void* (__thiscall**)(void*))(*(void***)inner)[0x18 / 4])(inner);
  unsigned int sig = 0xce9f6639;
  WriteUint32(s, &sig, 1, 0);

  bool ok = FUN_00b18590(self, stream);
  if (ok)
    ok = FUN_00cee3d0((char*)self + 0x34, stream);
  if (ok)
    ok = FUN_00c448a0((char*)self + 0xc0, stream);
  if (ok)
    FUN_00bfc4a0((char*)self + 0x5a8, stream);

  inner = (*(void* (__thiscall**)(void*))(*(void***)stream)[0x20 / 4])(stream);
  s = (*(void* (__thiscall**)(void*))(*(void***)inner)[0x18 / 4])(inner);
  unsigned int b = self->mb_bd ? 1 : 0;
  WriteUint32(s, &b, 1, 0);

  if (self->mpSpecies == 0) {
    self->mPosX = 0.0f;
    self->mPosY = 0.0f;
    self->mPosZ = 0.0f;
  } else {
    if (!self->mb_135 &&
        !(*(bool (__thiscall**)(void*))(*(void***)((char*)self + 0xc0))[0x58 / 4])((char*)self + 0xc0)) {
      self->mPosX = 0.0f;
      self->mPosY = 0.0f;
      self->mPosZ = 0.0f;
    } else {
      self->mPosX = *(float*)((char*)self->mpSpecies + 0x504);
      self->mPosY = *(float*)((char*)self->mpSpecies + 0x508);
      self->mPosZ = *(float*)((char*)self->mpSpecies + 0x50c);
    }
  }

  FUN_00bc9a80(*(void**)((char*)self + 0xb4c), stream);

  SP::cVarListSerializer serializer(self, (SP::cDataSerializerGeneric*)g_1571798, 0x1a80d26);
  serializer.Serialize(*(SP::cIObjectDatabaseOStream*)stream);
  return true;
}
