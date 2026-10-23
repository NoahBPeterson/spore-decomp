// match/slices/s00c035f0/s00c035f0.cpp
// Object file: SPGonzago/SPCreatureBase.obj (VS2008 SP1).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS- /Isrc/game/include
//   /GS- matters: the retail object has no __security_cookie even in Write (0xa10-byte
//   cVarListSerializer local); with the default /GS the added cookie/shift accounted for
//   most of Write's diff bytes.
//
// Local stub class for SP::cSPCreatureBase, re-laid to the retail offsets the
// disassembly shows (the canonical header under src/game/include carries other
// offsets; the retail object is cCreatureAnimal-sized and uses 0xb20 /
// 0x1624 / 0x1674 members).  All the unnamed callees are declared here; because
// chk.py only compiles to .obj, a declaration is enough for the call to appear.

#include "game/types.h"
#include <math.h>

// ---- float / int globals read from absolute addresses ----
extern int   g_1582f4c;                                  // 0x1582f4c
extern float g_1583338;                                  // 0x1583338
extern float g_158333c;                                  // 0x158333c
extern float g_1583340;                                  // 0x1583340
extern float g_1582e28;                                  // 0x1582e28
extern float g_1582e2c;                                  // 0x1582e2c
extern float g_150c890;                                  // 0x150c890
extern float g_150c8a0;                                  // 0x150c8a0

extern "C" float g_1469e30;                              // 0x1469e30 == FLT_MAX (fld)

// ---- free (non-member) callees ----
void* __cdecl SP_GetCurrentGameMode();                   // 0xb5b800
void* __cdecl SP_NounManager();                          // 0xb3d300
void* __cdecl SP_GameTimeManager();                      // 0xb3d380
void* __cdecl FUN_00401090();                            // 0x401090 (GetSetting9)
void* __cdecl FUN_00d37cb0();                            // 0xd37cb0
void* __cdecl FUN_00d539d0();                            // 0xd539d0 (PosseSim::Instance)
void* __cdecl FUN_00d38840();                            // 0xd38840 (ModeStrategy::Instance)
void* __fastcall FUN_004df420(void*);                    // 0x4df420 (GetAvatarProfile)
void* __fastcall FUN_004e0050(void*, int, int);          // 0x4e0050 (GetSpeciesArchetype)
void* __fastcall FUN_00b1fdb0(void*);                    // 0xb1fdb0 (NounManager::GetAvatar)

void  __fastcall FUN_00bc30f0(void*);                    // 0xbc30f0 (cSPTimer::Start)
void  __fastcall FUN_00cee2c0(void*, void*, int, float, float, int); // 0xcee2c0 (ret 0x14)
int   __fastcall FUN_008e7f80(void*);                    // 0x8e7f80 (GetDamageState)
void  __fastcall FUN_00bfcae0(void*);                    // 0xbfcae0
void  __fastcall FUN_00bfd2b0(void*);                    // 0xbfd2b0
int   __fastcall FUN_00bc9980(void*, float);             // 0xbc9980
void  __fastcall FUN_00bcb660(void*, char*);             // 0xbcb660
uint64_t __fastcall FUN_00b316c0(void*);                 // 0xb316c0
void  __cdecl FUN_00d995f0(float, double, int, void*, void*, int, unsigned, int); // 0xd995f0
float __cdecl FUN_00d38a30(int, void*);                  // 0xd38a30
float __cdecl FUN_00c03440(int);                         // 0xc03440
float __cdecl FUN_004d12a0(unsigned);                    // 0x4d12a0
void __cdecl RGBToHSL(float, float, float, float*, float*, float*);  // 0x67ff30 (returns void)
float* __cdecl HSLToRGB(float*, float, float, float);    // 0x67fe30
float __cdecl Clamp01(float);                            // 0x5a6e00
bool  __cdecl FUN_0093aa70(void*, const unsigned*, unsigned, int);    // 0x93aa70
void  __cdecl FUN_00c035f0(void*);                       // 0xc035f0 (this slice)

// ---- helper types ----
struct Vec3 { float x, y, z; };
struct Ser  {                                            // cVarListSerializer (0xa14)
  char raw[0xa14];
  void* FUN_00692f90(void*, void*, unsigned);            // 0x692f90 (thiscall, 3 stack args)
  bool  FUN_00692900(void*);                             // 0x692900 (thiscall, 1 stack arg)
};
struct PosseSim { void FUN_00d52e90(int, int); };        // 0xd52e90 (ecx=this, ret 8)

// NB: these are pointer-to-function-pointer typedefs: `(*(FnVoid)(vt + off))(this)`
// casts the vtable-slot ADDRESS to a slot pointer, dereferences it to load the
// function pointer stored there, then calls it (i.e. `call [vt + off]`).
typedef void  (__thiscall **FnVoid)(void*);
typedef void  (__thiscall **FnVoidI)(void*, int);
typedef void  (__thiscall **FnVoidIII)(void*, int, int, int);
typedef void  (__thiscall **FnVoidP)(void*, void*);
typedef float (__thiscall **FnFloat)(void*);
typedef float (__thiscall **FnFloatI)(void*, int);
typedef void  (__thiscall **FnFloatArg)(void*, float);
typedef int   (__thiscall **FnInt)(void*);
typedef int   (__thiscall **FnIntI)(void*, int);
typedef unsigned (__thiscall **FnUInt)(void*);
typedef void* (__thiscall **FnPtr)(void*);
typedef void* (__thiscall **FnPtrP)(void*, void*);
typedef bool  (__thiscall **FnBool)(void*);

// cSPCreatureBase, retail layout (offsets read off the disassembly).
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

// @ 0x00c035f0
void __cdecl FUN_00c035f0(void* pv)
{
  char* p = (char*)pv;
  if (p == 0)
    return;
  if (*(int*)(p + 0xb54) == 0)
    return;
  unsigned f = *(unsigned*)(p + 0xb58);
  if (((f >> 9) & 1) != 0 || *(int*)(p + 0xb34) != 1 || (f & 1) == 0) {
    (*(FnVoidP)(*(char**)p + 0xe4))(p, (void*)0x157126c);
    ((CreatureBase*)p)->SetB65(0);
    return;
  }
  int idx = g_1582f4c * 3 + 0x138;
  char* prof = *(char**)(p + 0xb20);
  float r = *(float*)(prof + idx * 4);
  char* base = prof + idx * 4;
  float g = *(float*)(base + 4);
  float b = *(float*)(base + 8);
  float h, s, l;
  RGBToHSL(r, g, b, &h, &s, &l);
  float hue = g_1583338 * 360.0f + h;
  if (hue > 360.0f)
    hue -= 360.0f;
  if (hue < 0.0f)
    hue += 360.0f;
  s = Clamp01(g_158333c * s);
  l = Clamp01(g_1583340 * l);
  float rgb[3];
  float* rp = HSLToRGB(rgb, hue, s, l);
  float res[3];
  res[0] = rp[0];
  res[1] = rp[1];
  res[2] = rp[2];
  (*(FnVoidP)(*(char**)p + 0xe4))(p, res);
  ((CreatureBase*)p)->SetB65(1);
  float v = (*(FnFloatI)(*(char**)p + 0x80))(p, 0);
  char* loco = p + 0xc0;
  (*(FnFloatArg)(*(char**)loco + 0x40))(loco, v);
}

// @ 0x00c037c0
bool CreatureBase::func37C0(void* p, int unused, int flag)
{
  char b = (char)flag;
  if (b == 0)
    *(char*)((char*)this + 0xb5e) = 0;
  FUN_00c222f0(p);
  char* prof = *(char**)((char*)this + 0xb20);
  if (b == 0 || prof == 0) {
    FUN_00c21090();
  } else {
    int n = (*(int*)((char*)this + 0xe44) - *(int*)((char*)this + 0xe40)) / 0x24;
    float fn = (float)n;
    if (n < 0)
      fn = fn + 4294967296.0f;
    bool match = (*(float*)(prof + 0x590) == fn);
    if (!match) {
      int n2 = (*(int*)((char*)this + 0xe44) - *(int*)((char*)this + 0xe40)) / 0x24;
      float fn2 = (float)n2;
      if (n2 < 0)
        fn2 = fn2 + 4294967296.0f;
      match = (*(float*)(prof + 0x594) == fn2);
    }
    if (match)
      FUN_00c13eb0();
    else
      FUN_00c21090();
  }
  FUN_00cee2c0((char*)this + 0x34, 0, 1, g_1469e30, 0.0f, 1);
  if (b == 0) {
    *(unsigned*)((char*)this + 0xb58) &= 0xfffeff7f;
    float v = (*(FnFloatI)(*(char**)this + 0x80))(this, 0);
    char* loco = (char*)this + 0xc0;
    (*(FnFloatArg)(*(char**)loco + 0x40))(loco, v);
  }
  (*(FnVoidI)(*(char**)this + 0xac))(this, b == 0);
  (*(FnVoidI)(*(char**)this + 0xcc))(this, flag);
  if (!FUN_00c0b770() && ((*(unsigned*)((char*)this + 0xb58) >> 9) & 1) == 0) {
    void* gm = SP_GetCurrentGameMode();
    if (gm == (void*)0x1654c01 || SP_GetCurrentGameMode() == (void*)0x1654c02)
      FUN_00bc30f0((char*)this + 0x1628);
  }
  return *(int*)((char*)this + 0xb20) != 0;
}

// @ 0x00c03950
bool CreatureBase::funcC0h(void* other, float fA, float fB)
{
  char* oth = (char*)other;
  if (((CreatureBase*)other)->FUN_00c0c130())
    return false;

  char* ts = (char*)this + 0xc0;
  char* os = oth + 0xc0;
  float* posOther = (float*)(*(FnPtr)(*(char**)os + 0x2c))(os);
  float* posThis = (float*)(*(FnPtr)(*(char**)ts + 0x2c))(ts);

  float dy = posOther[1] - posThis[1];
  float dz = posOther[2] - posThis[2];
  float dx = posOther[0] - posThis[0];
  float len = (float)sqrt((double)dy * dy + (double)dz * dz + (double)dx * dx + 1e-8f);

  float inv = 1.0f / len;
  float ny = dy * inv;
  float nz = dz * inv;
  float nx = dx * inv;

  float c10;
  float dist;
  if (1.5258789e-05f <= (float)fabs((double)fB)) {
    c10 = inv;
    dist = fB;
  } else {
    float footThis = (*(FnFloat)(*(char**)ts + 0x74))(ts);
    float footOther = (*(FnFloat)(*(char**)os + 0x74))(os);
    c10 = footThis;
    dist = len - (footThis + footOther);
  }

  if (SP_GetCurrentGameMode() == (void*)0x1654c10) {
    if (((*(unsigned*)((char*)this + 0xb58) >> 8) & 1) != 0)
      return true;
    if (*(float*)((char*)this + 0x32c) > dist)
      return true;
    return false;
  }

  float t = FUN_00c0e4f0() * fA;
  float cosine = (float)cos((double)FUN_00c0c010() * 0.008726646f);
  Vec3 dbuf;
  Vec3* dir = (Vec3*)(*(FnPtrP)(*(char**)ts + 0x5c))(ts, &dbuf);
  if (((CreatureBase*)other)->FUN_00c0c130())
    return false;
  if (t < dist)
    return false;
  float dot = dir->y * ny + dir->z * nz + dir->x * cosine;
  return dot >= c10;
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

// @ 0x00c03c20
int CreatureBase::func3C20(int param)
{
  void* c = FUN_00c0ee60();
  if (c != 0) {
    unsigned u = (*(FnUInt)(*(char**)c + 0xc))(c);
    FUN_00c0bf10(0x10, 0, 0x2788b9, 0x40049000, g_1469e30, 0x100000, 0,
                 param, 0, u, 0);
    ((PosseSim*)FUN_00d539d0())->FUN_00d52e90(0x10, 0);
  }
  return param;
}

// @ 0x00c03c90
void CreatureBase::SetCreatureTarget(void* p, bool flag, int val)
{
  *(char*)((char*)this + 0xb5c) = (char)flag;
  *(int*)((char*)this + 0xb74) = val;
  char* old = *(char**)((char*)this + 0xe7c);
  if (old == (char*)p)
    return;
  if (p != 0) {
    char* cur = *(char**)((char*)this + 0xe7c);
    if ((char*)p != cur) {
      (*(FnVoid)(*(char**)p + 0x60))(p);
      *(char**)((char*)this + 0xe7c) = (char*)p;
      if (cur != 0)
        (*(FnVoid)(*(char**)cur + 0x64))(cur);
    }
  } else {
    char* cur = *(char**)((char*)this + 0xe7c);
    if (cur != 0) {
      *(char**)((char*)this + 0xe7c) = 0;
      (*(FnVoid)(*(char**)cur + 0x64))(cur);
    }
    char* anim = *(char**)((char*)this + 0xb54);
    if (anim != 0 && *(int*)(anim + 0x154) == 0)
      FUN_00c0d240();
  }
  *(float*)((char*)this + 0x167c) = 0.0f;
  if (((*(unsigned*)((char*)this + 0xb58) >> 9) & 1) != 0 &&
      SP_GetCurrentGameMode() == (void*)0x1654c01) {
    void* q = FUN_00d37cb0();
    (*(FnVoidI)(*(char**)q + 0x28))(q, 0);
  }
}

// @ 0x00c03d60
void CreatureBase::func70h(int unused)
{
  void* c = FUN_00c0ee60();
  if (c == 0)
    return;
  if (((*(unsigned*)((char*)this + 0xb58) >> 9) & 1) != 0) {
    if (SP_GetCurrentGameMode() == (void*)0x1654c10) {
      if (FUN_008e7f80(c) != 2) {
        void* q = (*(FnPtr)(*(char**)c + 0xc))(c);
        if (!(*(FnBool)(*(char**)q + 0x2c))(q))
          goto LAB_3dc5;
      }
      (*(FnVoidIII)(*(char**)this + 0x84))(this, 0, 0, 0);
    } else {
      char* o = (char*)FUN_00c0ee90();
      if (o != 0 && (*(char*)(o + 0xb5e) != 0 || *(char*)(o + 0x135) == 0)) {
        char* s = (char*)FUN_00d38840();
        if (*(int*)(s + 0x68) != 0 || SP_GetCurrentGameMode() == (void*)0x1654c10)
          FUN_00bfcae0(c);
        if (*(char*)(o + 0x135) == 0) {
          (*(FnVoidIII)(*(char**)this + 0x84))(this, 0, 0, 0);
          return;
        }
      }
    }
  }
LAB_3dc5:
  void* q = (*(FnPtr)(*(char**)c + 8))(c);
  if (*(char*)((char*)q + 0x75) == 0) {
    (*(FnVoidIII)(*(char**)this + 0x84))(this, 0, 0, 0);
    if (((*(unsigned*)((char*)this + 0xb58) >> 9) & 1) != 0)
      FUN_00c0bf10(0x100000, 0, 0x2788b9, 0x40049000, g_1469e30, 0x100000, 0,
                   0, 0, 0, 0);
  } else {
    char* ts = (char*)this + 0xc0;
    if ((*(FnBool)(*(char**)ts + 0x58))(ts))
      FUN_00bfd2b0(c);
  }
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

// @ 0x00c03f90
void CreatureBase::func3F90()
{
  unsigned* base = *(unsigned**)((char*)this + 0x1624);
  if (*base == 0)
    return;
  unsigned acc = 0;
  unsigned off = 0;
  do {
    if (off >= 0xe0)
      return;
    int* obj = *(int**)((char*)base + off + 0x1c);
    int** slot = (int**)((char*)base + off + 0x1c);
    acc |= *(unsigned*)((char*)base + off + 4);
    if (obj != 0) {
      int* r = (int*)(*(FnIntI)(*(char**)obj + 0xc))(obj, 0xce9f6639);
      if (r != 0 && *(char*)((char*)r + 0xb5e) != 0) {
        *(unsigned*)((char*)base + off + 4) = 0;
        int* o2 = *slot;
        if (o2 != 0) {
          *slot = 0;
          (*(FnVoid)(*(char**)o2 + 4))(o2);
        }
      }
    }
    base = *(unsigned**)((char*)this + 0x1624);
    off += 0x1c;
  } while (*base != acc);
}

// @ 0x00c04010
float CreatureBase::GetBaseMaxHitPoints()
{
  float local_8 = 0.0f;
  if (SP_GetCurrentGameMode() == (void*)0x1654c10) {
    unsigned id = (*(FnUInt)(*(char**)this + 0xd8))(this);
    float hp = FUN_004d12a0(id);
    char* prof = *(char**)((char*)this + 0xb20);
    return hp + *(float*)(prof + 0x56c);
  }
  char* prof = *(char**)((char*)this + 0xb20);
  bool isAvatar = (prof == (char*)FUN_004df420(FUN_00401090()));
  float local_4;
  if (isAvatar) {
    void* av = FUN_00b1fdb0(SP_NounManager());
    if (av != 0) {
      unsigned id = (*(FnUInt)(*(char**)av + 0xd8))(av);
      local_8 = FUN_004d12a0(id);
    } else {
      local_8 = g_150c8a0;
    }
    local_4 = *(float*)(prof + 0x56c);
  } else {
    char* herd = *(char**)((char*)this + 0x1674);
    if (herd != 0 && *(float*)(herd + 0x154) > 0.0f) {
      local_4 = *(float*)(herd + 0x154);
    } else {
      char* e = *(char**)((char*)this + 0xe84);
      if (e != 0) {
        local_4 = *(float*)(e + 0x340);
      } else {
        local_8 = g_150c890;
        local_4 = *(float*)(prof + 0x56c);
      }
    }
  }
  if (local_4 < 1.5258789e-05f && !isAvatar) {
    local_4 = *(float*)(prof + 0x56c);
    local_8 = g_150c890;
  }
  return local_8 + local_4;
}

// @ 0x00c04140
float CreatureBase::func4140(int boolFlag)
{
  float local = 100.0f;
  char* herd = *(char**)((char*)this + 0x1674);
  if (herd != 0 && *(int*)(herd + 0x88) != 0) {
    char* arch = (char*)FUN_004e0050(FUN_00401090(), *(int*)(herd + 0x88),
                                     *(int*)(herd + 0xf0));
    if (arch != 0) {
      if (boolFlag)
        local = *(float*)(arch + 0x324);
      else
        local = *(float*)(arch + 0x320);
    }
  }
  if (!FUN_00c0b770())
    local = local * g_1582e28;
  else if ((*(unsigned char*)((char*)this + 0xb58) & 1) != 0)
    local = local * g_1582e2c;
  float x = FUN_00c03440(FUN_00c0b8d0());
  float r = x * local;
  float one = 1.0f;
  return (r > one) ? r : one;
}

// @ 0x00c04220
bool CreatureBase::Write(void* stream)
{
  void* p = (*(FnPtr)(*(char**)stream + 0x20))(stream);
  unsigned tmp = 0xd0036e08u;
  void* u = (*(FnPtr)(*(char**)p + 0x18))(p);
  FUN_0093aa70(u, &tmp, 1, 0);
  bool bl = FUN_00c0bc20(stream);
  char* herd = *(char**)((char*)this + 0x1674);
  if (herd != 0 && (*(FnBool)(*(char**)herd + 0x2c))(herd)) {
    herd = *(char**)((char*)this + 0x1674);
    if (herd != 0) {
      *(char**)((char*)this + 0x1674) = 0;
      (*(FnVoid)(*(char**)herd + 4))(herd);
    }
  }
  Ser ser;
  ser.FUN_00692f90(this, (void*)0x1571370, 0x1a80d26);
  if (bl) {
    if (ser.FUN_00692900(stream))
      return true;
  }
  return false;
}

// @ 0x00c042e0
void CreatureBase::func42E0()
{
  char* sub = (char*)this + 0x58;
  (*(FnVoidI)(*(char**)sub + 0x14))(sub, 1);

  unsigned f = *(unsigned*)((char*)this + 0xb58);
  char* str;
  if (((f >> 9) & 1) != 0) {
    *(int*)((char*)this + 0xeac) = 2;
    str = (char*)0x1590800;
  } else if (((f >> 8) & 1) != 0) {
    str = (char*)0x1590888;
  } else {
    char* herd = *(char**)((char*)this + 0x1674);
    if (herd != 0 && *(int*)(herd + 0x15c) == 9) {
      str = (char*)0x1590aa8;
    } else if ((f & 0x4000) != 0) {
      FUN_00bcb660(*(void**)((char*)this + 0xb4c), (char*)0x1590b30);
      FUN_00c0b370(0x609ea52);
      goto L42F8;
    } else {
      int st = (herd != 0) ? *(int*)(herd + 0x15c) : 0;
      if (st == 1)
        str = (char*)0x1590910;
      else if (st == 7)
        str = FUN_00c0b770() ? (char*)0x1590998 : (char*)0x1590a20;
      else if (st == 0xb)
        str = (char*)0x15aa9e8;
      else
        str = FUN_00c0b770() ? (char*)0x15906f0 : (char*)0x1590778;
    }
  }
  FUN_00bcb660(*(void**)((char*)this + 0xb4c), str);
L42F8:
  if (*(int*)((char*)this + 0xb20) != 0) {
    void* gm = SP_GetCurrentGameMode();
    *(int*)(*(char**)((char*)this + 0xb4c) + 0x5fc) = 0;
    if (FUN_00c0b780())
      *(unsigned*)(*(char**)((char*)this + 0xb4c) + 0x5fc) |= 2;
    if (FUN_00c0b7a0())
      *(unsigned*)(*(char**)((char*)this + 0xb4c) + 0x5fc) |= 4;
    if (Flag388())
      *(unsigned*)(*(char**)((char*)this + 0xb4c) + 0x5fc) |= 0x80;
    if (gm == (void*)0x1654c01)
      *(unsigned*)(*(char**)((char*)this + 0xb4c) + 0x5fc) |= 8;
    if (gm == (void*)0x1654c02)
      *(unsigned*)(*(char**)((char*)this + 0xb4c) + 0x5fc) |= 0x8000000;
    if (gm == (void*)0x1654c05)
      *(unsigned*)(*(char**)((char*)this + 0xb4c) + 0x5fc) |= 0x400;
    if (gm == (void*)0x1654c04)
      *(unsigned*)(*(char**)((char*)this + 0xb4c) + 0x5fc) |= 0x8000;
    if (*(int*)(*(char**)((char*)this + 0xb20) + 0x588) == 1)
      *(unsigned*)(*(char**)((char*)this + 0xb4c) + 0x5fc) |= 0x40;
    if (*(float*)(*(char**)((char*)this + 0xb20) + 0x590) > 0.0f)
      *(unsigned*)(*(char**)((char*)this + 0xb4c) + 0x5fc) |= 0x800;
    if (*(char**)((char*)this + 0xb20) == (char*)FUN_004df420(FUN_00401090()))
      *(unsigned*)(*(char**)((char*)this + 0xb4c) + 0x5fc) |= 0x1000;
  }
  if ((*(FnInt)(*(char**)this + 0xd8))(this) > 4)
    *(unsigned*)(*(char**)((char*)this + 0xb4c) + 0x5fc) |= 0x200;
}
