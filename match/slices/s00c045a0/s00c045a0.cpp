// match/slices/s00c045a0/s00c045a0.cpp
// Object file: SPGonzago/SPCreatureBase.obj (VS2008 SP1).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /Isrc/game/include
//
// Local stub class for SP::cSPCreatureBase, re-laid to the retail offsets the
// disassembly shows (the canonical header under src/game/include carries the
// same members but is being migrated to these offsets piecemeal).

#include "game/types.h"
#include <math.h>

// ---- unnamed retail callees and globals (address in the comment) ----
void* __cdecl SP_GetCurrentGameMode();                  // 0xb5b800
void* __cdecl SP_NounManager();                         // 0xb3d300
void* __cdecl FUN_00401090();                           // 0x401090
void* __cdecl FUN_004df420();                           // 0x4df420
float __cdecl FUN_00572a10(float lo, float hi);         // 0x572a10
void  __cdecl operator_delete_(void*);                  // 0xf47380
float __cdecl FUN_00c0b440(void*);                      // 0xc0b440
float __cdecl FUN_00d2e800(void*);                      // 0xd2e800
void  __cdecl FUN_00d2e580(void*);                      // 0xd2e580
int   __cdecl FUN_00d51660(int);                        // 0xd51660
void* __cdecl FUN_00d1e660();                           // 0xd1e660
void  __cdecl FUN_00d4d5c0(int);                        // 0xd4d5c0
void  __cdecl FUN_00c0d3a0(void*);                      // 0xc0d3a0
void  __cdecl FUN_00c035f0(void*);                      // 0xc035f0
void  __cdecl FUN_00c1d400(unsigned, unsigned);         // 0xc1d400
void  __cdecl FUN_00c22210(void*, int);                 // 0xc22210
void* __cdecl FUN_00c032c0(void*, void*, void*, void*); // 0xc032c0
void  __cdecl FUN_00c0bbe0(void*);                      // 0xc0bbe0
void  __cdecl FUN_00c17350(void*, unsigned, int);       // 0xc17350
// 0xb18530 is SP::cGameData::GetObjectData(): a __thiscall that returns the
// linked game record at [this+0x70] base.
struct GameDataStub { int GetObjectData(); };
// 0xf3c0e0 reads a global, but the call site loads ecx first: a __thiscall
// member of the object at [g_16c7aa4+0x74].
struct ThingMgrStub { int GetThing(); };
void  __cdecl SP_EffectsManager();                      // 0x67ddd0
void* __cdecl SP_PlanetModel();                         // 0xb3d350
extern void* g_16c7aa4;

extern float gF_150c8d0, gF_150c8d4, gF_150c8cc_, gF_1582df0, gF_15d992c, gF_15d9930;
void  __cdecl FUN_00c042e0(void*);                      // 0xc042e0

// cLocomotionRequest block: [0] is a refcounted request object (deleted when its
// refcount field at [-4] is non-zero).
struct LocomotionRequest { void* mpData; char pad[0x48]; };

// ---- helper types ----
struct Vec3 { float x, y, z; };
static __forceinline bool GetBit(uint32_t v, int n) { return ((v >> n) & 1) != 0; }

// A refcounted engine object with a vtable: only slots we call are named.
struct IVTableObj {
  virtual void s0();
  virtual void s1();
  virtual void s2();     // +0x8
  virtual void s3();     // +0xc
  virtual int  s4();     // +0x10
  virtual void s5();
  virtual void s6();     // +0x18
  virtual void s7();
  virtual void s8();     // +0x20
  virtual void s9();
  virtual void s10();
  virtual void s11(void*);   // +0x2c
};

// cSPCreatureBase, retail layout (offsets read off the disassembly).
struct CreatureBase {
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
bool  __thiscall CreatureBase::Flag388()
{
  void* p = *(void**)((char*)this + 0xe84);
  return p != 0 && *(char*)((char*)p + 0x388) != 0;
}
// The original calls 0xc0b770 out of line from every site in this slice.
bool __declspec(noinline) __thiscall CreatureBase::SubB770()
{
  return mB34 == 1;
}
// the base-class helpers called by name
void  __cdecl FUN_00c14cb0(void*);                      // 0xc14cb0 (base OnJumpLand)
void  __cdecl FUN_00c14e10(void*);                      // 0xc14e10 (base OnStartSwimming)
int   __cdecl FUN_00c0be70(int);                        // 0xc0be70
int   __cdecl FUN_00c0bea0(int);                        // 0xc0bea0
struct AnimGUIDHolder { unsigned GetCurrentAnimationGUID(); };  // 0xc0e040
void* __cdecl FUN_00d1e660_p();                         // 0xd1e660

// AutoRefCount<T>-shaped slot ([0x1674]): one pointer.
template <typename T> struct AutoRef { T* mpObject; };

// SP::cSpeciesProfile fields we read (retail offsets 0x554..0x6d8).
struct SpeciesProfile {
  char pad000[0x554];
  Vec3 aabb_extents;        // +0x554
  char pad560[0x6d4-0x560];
  int* mAbilityBegin;       // +0x6d4
  int* mAbilityEnd;         // +0x6d8
};

// ---- the SP::cHerd slant: slot [0x1674] holds an AutoRefCount<SP::cHerd>;
//      index 0x164 of the herd follows the animal it belongs to.
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

// vtable call helpers, so the original's `mov edx,[eax+N]; call edx` shows up as
// a virtual dispatch rather than a function-pointer cast.
typedef void  (__thiscall *FnVoid)(void*);
typedef float (__thiscall *FnFloat)(void*);
typedef void  (__thiscall *FnFloatArg)(void*, float);
typedef void* (__thiscall *FnPtr)(void*);
typedef int   (__thiscall *FnInt)(void*);

static inline FnVoid Vt(void* o, int off) { return *(FnVoid*)(*(char**)o + off); }

// @ 0x00c045a0
void __thiscall CreatureBase::SetHerd(void* p)
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
int __thiscall CreatureBase::GetAbilitiesCount()
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
int __thiscall CreatureBase::GetAbility(unsigned index)
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
bool __thiscall CreatureBase::Flag04710()
{
  if ((mFlags0b58 & 0x4000) != 0)
    return true;
  if (SubB770())
    return false;
  HerdObj* h = (HerdObj*)mpHerd1674;
  if (h == 0) return false;
  CreatureBase* a = (CreatureBase*)*(void**)((char*)h + 0x164);
  if (a == 0) return false;
  if ((a->mFlags0b58 & 0x4000) != 0)
    return true;
  return false;
}

// @ 0x00c04750
void* __thiscall CreatureBase::Sub4750()
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
int __thiscall CreatureBase::Sub4790()
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
int __thiscall CreatureBase::Sub47d0()
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

// @ 0x00c048c0
void* __fastcall FUN_00c048c0(void* dst, int, const void* src)
{
  *(int*)  ((char*)dst + 0)  = *(int*)  ((char*)src + 0);
  *(char*) ((char*)dst + 4)  = *(char*) ((char*)src + 4);
  *(char*) ((char*)dst + 5)  = *(char*) ((char*)src + 5);
  *(int*)  ((char*)dst + 8)  = *(int*)  ((char*)src + 8);
  *(int*)  ((char*)dst + 8)  = *(int*)  ((char*)src + 8);
  *(int*)  ((char*)dst + 8)  = *(int*)  ((char*)src + 8);
  *(int*)  ((char*)dst + 8)  = *(int*)  ((char*)src + 8);
  void** o3 = (void**)((char*)src + 0xc);
  *(void**)((char*)dst + 0xc) = *o3;
  if (*o3)
    (*(FnVoid)(*(char**)*o3 + 0))(*o3);
  void** o4 = (void**)((char*)src + 0x10);
  *(void**)((char*)dst + 0x10) = *o4;
  if (*o4)
    (*(FnVoid)(*(char**)*o4 + 0))(*o4);
  return dst;
}

// @ 0x00c04960
void __cdecl FUN_00c04960(void** heap, int root, int i, void* value)
{
  int child = 2 * i + 2;
  while (child < root) {
    void* a = heap[child];
    void* b = heap[child - 1];
    if (*(float*)a <= *(float*)b)
      --child;
    heap[i] = heap[child];
    i = child;
    child = 2 * child + 2;
  }
  if (child == root) {
    heap[i] = heap[child - 1];
    i = child - 1;
  }
  if (i <= 0) {
    heap[i] = value;
    return;
  }
  float v = *(float*)value;
  int parent = (i - 1) >> 1;
  while (i > parent) {
    void* p = heap[parent];
    if (v < *(float*)p) break;
    heap[i] = p;
    i = parent;
    parent = (i - 1) >> 1;
  }
  heap[i] = value;
}

float __cdecl FUN_00c0c1c0(void*, char);                // 0xc0c1c0 (Speed1)
bool  __cdecl FUN_00c0c2d0(void*);                      // 0xc0c2d0 (IsDefaultSpecies)

// @ 0x00c049f0
float __thiscall CreatureBase::CalculateScale(char param_2, float param_3)
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

bool __cdecl FUN_00c0c2d0(void*);                       // 0xc0c2d0 (IsDefaultSpecies)

// @ 0x00c04b50
void __thiscall CreatureBase::OnJumpLand()
{
  unsigned guid = ((AnimGUIDHolder*)this)->GetCurrentAnimationGUID();
  bool b = FUN_00c0be70(guid) != 0;
  bool c = false;
  if (!b)
    c = FUN_00c0bea0(guid) != 0;
  FUN_00c14cb0(this);
  if (*(int*)((char*)this + 0x310) != 0 && (b || c)) {
    char* loco = (char*)this + 0xc0;
    Vec3* vp = (Vec3*)(*(FnPtr)(*(char**)loco + 0x2c))(loco);
    Vec3 d;
    d.x = *(float*)((char*)this + 0x2c8) - vp->x;
    d.y = *(float*)((char*)this + 0x2cc) - vp->y;
    d.z = *(float*)((char*)this + 0x2d0) - vp->z;
    (*(FnVoid)(*(char**)loco + 0x5c))(loco);
    float dot = vp->z * d.z + vp->y * d.y + vp->x * d.x;
    if (0.0f < dot)
      return;
    LocomotionRequest req;
    (*(FnVoid)(*(char**)loco + 0xdc))(loco);
    if (req.mpData && *(int*)((char*)req.mpData - 4) != 0)
      operator_delete_(req.mpData);
  }
  if ((((unsigned)mFlags0b58 >> 9) & 1) != 0)
    FUN_00d2e580(this);
}

// @ 0x00c04c90
void __thiscall CreatureBase::OnStartSwimming()
{
  unsigned guid = ((AnimGUIDHolder*)this)->GetCurrentAnimationGUID();
  bool b = FUN_00c0be70(guid) != 0;
  bool c = false;
  if (!b)
    c = FUN_00c0bea0(guid) != 0;
  if (b || c)
    FUN_00c14e10(this);
  if (*(int*)((char*)this + 0x310) != 0 && (b || c)) {
    char* loco = (char*)this + 0xc0;
    Vec3* vp = (Vec3*)(*(FnPtr)(*(char**)loco + 0x2c))(loco);
    Vec3 d;
    d.x = *(float*)((char*)this + 0x2c8) - vp->x;
    d.y = *(float*)((char*)this + 0x2cc) - vp->y;
    d.z = *(float*)((char*)this + 0x2d0) - vp->z;
    (*(FnVoid)(*(char**)loco + 0x5c))(loco);
    float dot = vp->z * d.z + vp->y * d.y + vp->x * d.x;
    if (0.0f < dot)
      return;
    LocomotionRequest req;
    (*(FnVoid)(*(char**)loco + 0xdc))(loco);
    if (req.mpData && *(int*)((char*)req.mpData - 4) != 0)
      operator_delete_(req.mpData);
  }
  if ((((unsigned)mFlags0b58 >> 9) & 1) != 0)
    FUN_00d2e580(this);
}

// @ 0x00c04dd0
void __thiscall CreatureBase::Sub4dd0(int mode)
{
  if (SP_GetCurrentGameMode() == (void*)0x1654c10) {
    FUN_00c22210(this, mode);
    return;
  }
  if (mB34 == mode)
    return;
  if (mode == 1) {
    if (mState1688 != 0)
      return;
    mState1688 = 1;
    return;
  }
  FUN_00c22210(this, mode);
  if ((((unsigned)mFlags0b58 >> 9) & 1) == 0) {
    FUN_00c0d3a0(this);
    FUN_00c042e0(this);
  }
  FUN_00c035f0(this);
}

// @ 0x00c04e50
void __thiscall CreatureBase::Sub4e50(float dt)
{
  switch (mState1688) {
  case 1: {
    FUN_00c1d400(0x3a616fee, 0x715fb4a7);
    float a = (*(FnFloat)(*(char**)this + 0x80))(this);
    float b = (*(FnFloat)(*(char**)this + 0x80))(this);
    mState1688 = 2;
    mDepth1690 = a + (b - a) * 0.5f;
    return;
  }
  case 2: {
    char* loco = (char*)this + 0xc0;
    float cur = (*(FnFloat)(*(char**)loco + 0x34))(loco);
    float* tgt = &mDepth1690;
    if (cur < *tgt) {
      float nv = cur + gF_150c8d4 * dt;
      if (nv > *tgt)
        nv = *tgt;
      (*(FnFloatArg)(*(char**)loco + 0x40))(loco, nv);
      return;
    }
    FUN_00c22210(this, 1);
    char* herd = (char*)this + 0x5a8;
    (*(FnVoid)(*(char**)herd + 0x2c))(herd);
    (*(FnFloatArg)(*(char**)loco + 0x40))(loco, *tgt);
    mState1688 = 3;
    if ((((unsigned)mFlags0b58 >> 9) & 1) != 0)
      FUN_00d4d5c0(FUN_00d51660(4));
    if ((((unsigned)mFlags0b58 >> 9) & 1) == 0 && (((unsigned)mFlags0b58 >> 8) & 1) == 0) {
      FUN_00c0d3a0(this);
      FUN_00c042e0(this);
      FUN_00c035f0(this);
    }
    return;
  }
  case 3: {
    char* loco = (char*)this + 0xc0;
    float cur = (*(FnFloat)(*(char**)loco + 0x34))(loco);
    float want = (*(FnFloat)(*(char**)this + 0x80))(this);
    if (want < cur) {
      float nv = cur + gF_150c8d4 * dt;
      if (nv > want)
        nv = want;
      (*(FnFloatArg)(*(char**)loco + 0x40))(loco, nv);
      return;
    }
    mState1688 = 4;
    return;
  }
  default: {
    char* loco = (char*)this + 0xc0;
    float v = (*(FnFloat)(*(char**)this + 0x80))(this);
    (*(FnFloatArg)(*(char**)loco + 0x40))(loco, v);
    FUN_00c0bbe0(this);
    FUN_00c17350(this, 0x715fb4a7, 0);
    mState1688 = 0;
    return;
  }
  }
}

// ---- c050b0: water-reflection transform notify ----
// Calls into the effects manager; the message type is a shared XformMsg.
struct Matrix33T { float m[9]; };
struct Quaternion { float x, y, z, w; };
struct XformMsg {
  unsigned short mFlags;    // +0x0
  unsigned short mSeq;      // +0x2
  XformMsg();
  void SetMatrix(Matrix33T const&);
  void SetPosition(Vec3 const&);
  float mPos[3];            // +0x4  (filled after the notify)
  Matrix33T mMat;           // +0x10
};
void* __cdecl SP_EffectsManagerI();                     // 0x67ddd0
Matrix33T& __cdecl Matrix3FromQuaternion(Matrix33T&, Quaternion const&); // 0x59c190
struct PlanetModelStub {
  Quaternion& BuildSurfaceOrientation(Quaternion& q, Vec3 const& v);  // 0xb7f190
  void SnapA(Vec3& out, unsigned flags, Vec3 const& in);              // 0xb82b40
};
extern void* g_168d828;                                 // cached reflection object
extern unsigned g_168d82c;                              // its init guard
void  __cdecl FUN_013c34a0();                           // 0x13c34a0 (atexit fn)

// @ 0x00c050b0
void CreatureBase::Sub50b0()
{
  if (*(char*)((char*)this + 0x137) != 0)
    (*(FnVoid)(*(char**)this + 0x58))(this);
  if (SP_GetCurrentGameMode() != (void*)0x1654c10)
    return;
  if ((((unsigned)mFlags0b58 >> 9) & 1) == 0)
    return;

  char* loco = (char*)this + 0xc0;
  Vec3* p = (Vec3*)(*(FnPtr)(*(char**)loco + 0x2c))(loco);
  Vec3 a;
  a.x = p->x; a.y = p->y; a.z = p->z;
  Vec3 b;
  ((PlanetModelStub*)SP_PlanetModel())->SnapA(b, 0, a);
  bool far = 49.0f < (a.z - b.z) * (a.z - b.z) + (a.y - b.y) * (a.y - b.y) + (a.x - b.x) * (a.x - b.x);

  if ((g_168d82c & 1) == 0) {
    g_168d82c |= 1;
    g_168d828 = 0;
    atexit(FUN_013c34a0);
  }

  if (g_168d828 == 0) {
    if (!far)
      return;
    void* em = SP_EffectsManagerI();
    if (g_168d828 != 0) {
      g_168d828 = 0;
      (*(FnVoid)(*(char**)em + 4))(em);
    }
    (*(FnVoid)(*(char**)em + 0x2c))(em);   // Create(...)
    if (g_168d828 == 0)
      return;
    XformMsg msg;
    (*(FnVoid)(*(char**)g_168d828 + 0x20))(g_168d828);
    Quaternion q;
    ((PlanetModelStub*)SP_PlanetModel())->BuildSurfaceOrientation(q, a);
    Matrix33T* m = &Matrix3FromQuaternion(*(Matrix33T*)&msg.mMat, q);
    (*(FnVoid)(*(char**)loco + 0x74))(loco);
    (*(FnVoid)(*(char**)g_168d828 + 0x18))(g_168d828);
    (*(FnVoid)(*(char**)g_168d828 + 8))(g_168d828);
    (void)m;
    return;
  }
  if (!far) {
    (*(FnVoid)(*(char**)g_168d828 + 0xc))(g_168d828);
    if (g_168d828 != 0) {
      g_168d828 = 0;
      (*(FnVoid)(*(char**)g_168d828 + 4))(g_168d828);
    }
    return;
  }
  if ((*(FnInt)(*(char**)g_168d828 + 0x10))(g_168d828) == 0)
    (*(FnVoid)(*(char**)g_168d828 + 8))(g_168d828);
  XformMsg msg;
  (*(FnVoid)(*(char**)g_168d828 + 0x20))(g_168d828);
  Quaternion q;
  ((PlanetModelStub*)SP_PlanetModel())->BuildSurfaceOrientation(q, a);
  Matrix3FromQuaternion(*(Matrix33T*)&msg.mMat, q);
  (*(FnVoid)(*(char**)g_168d828 + 0x18))(g_168d828);
}
