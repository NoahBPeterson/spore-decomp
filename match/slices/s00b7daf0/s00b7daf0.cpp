// Slice s00b7daf0 — SP::cPlanetModel / terrain / continent union-find helpers.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"
#include <math.h>

// ---- free callees --------------------------------------------
void* __cdecl SP_GetUniverseContext();                    // 0x1021080
void* __cdecl SP_GetActivePlanet();                       // 0x1021260
void* __cdecl SP_PropertyManager();                       // 0x67de30
void* __cdecl SP_PlanetModel();                           // 0xb3d350
void* __cdecl SP_TerrainEditor();                         // 0xf48a70
void* __cdecl SP_MessageServer();                         // 0x67dcc0
void* __cdecl SP_App();                                   // 0x67dd10
void* __cdecl SP_GetCurrentGameMode();                    // 0xb5b800
void  __cdecl FUN_00572660(void*);                        // 0x572660
void  __cdecl SP_GetPropertyAsKey(void*, uint32_t, void*);// 0x6a1250
uint32_t __cdecl FUN_00c713e0();                          // 0xc713e0
void* __cdecl FUN_00d61ce0(void*, void*, void*, void*);   // 0xd61ce0
void  __stdcall FUN_007a4420(int,int,int,int);            // 0x7a4420
bool  __cdecl FUN_00f678a0();                             // 0xf678a0
bool  __cdecl FUN_00f678c0();                             // 0xf678c0
void  __cdecl FUN_00f6bc10();                             // 0xf6bc10
void  __cdecl FUN_00f67890(int);                          // 0xf67890
void  __cdecl FUN_00f678b0(int);                          // 0xf678b0
void  __cdecl FUN_00b8c0f0();                             // 0xb8c0f0
void* __cdecl operator_new(unsigned, const char*, int, int, const char*, int); // 0xf473a0
void  __cdecl operator_delete__(void*);                   // 0xf47380
void  __cdecl Memset32(void*, int, unsigned);             // 0x92cb00
void  __cdecl FUN_00a16f40(void*, int);                   // 0xa16f40
void  __cdecl FUN_00b7d710(void*);                        // 0xb7d710
void  __cdecl FUN_00b7d750(void*, void*);                 // 0xb7d750

struct RandomLCG { uint32_t mnSeed; };
double __cdecl EA_RandomUniform(RandomLCG*);              // 0x9360d0
extern RandomLCG gMathRandom;                             // 0x1601760

extern char  gMode_1654c10;   // 0x1654c10
extern float gF_1688270;      // 0x1688270
extern float gF_156b5d4;      // 0x156b5d4
extern float gF_1465414;      // 0x1465414 = 500.0f
extern void* g_156b588;       // 0x156b588
extern void* g_16c9e5c;       // 0x16c9e5c

struct S15ddc84 { void __thiscall FUN_007a4420(int,int,int,int); };
extern S15ddc84 g_15ddc84;    // 0x15ddc84
extern uint8_t DAT_014653b9[]; // 0x14653b9
extern uint8_t DAT_014653ba[]; // 0x14653ba

// =======================================================================
struct cTerrainMapSet;
struct ISphere {
  virtual void a(); virtual void b(); virtual void c();
  virtual cTerrainMapSet* GetMap();          // slot 0xc
};
struct cTerrainMapSet {
  char  pad00[0x34];
  float mRadius;      // +0x34
  float mMaxHeight;   // +0x38
  float mWaterHeight; // +0x3c
  float __thiscall GetHeightAt(float* p);    // 0xf927c0
  void  __thiscall ComputeHeight(int a, int b); // 0xf92c20
};

struct cPlanetModel {
  char  pad00[0x20];
  void*    mpSphere;      // +0x20
  ISphere* mpISphere;     // +0x24
  void*    mpEffectSurface;// +0x28
  float    mWaterFraction;// +0x2c
  uint32_t mKey0;         // +0x30
  uint32_t mKey4;         // +0x34
  uint32_t mKey8;         // +0x38
  char  pad3c[0x10];
  uint32_t* mContinentMap;// +0x4c
  char  pad50[0x2c];
  uint8_t*  mBits;        // +0x7c

  void  __thiscall FUN_00b7e1a0();
  void  __thiscall FUN_00b7e1d0(uint32_t mask);
  void  __thiscall FUN_00b7e360(int arg);
  void  __thiscall FUN_00b7dec0();
  void  __thiscall FUN_00b7daf0();
  float __thiscall GetWaterHeight();
  uint32_t __thiscall FUN_00b7e3b0(uint32_t a, uint32_t b);
  bool  __thiscall FUN_00b7e3e0(float* p);
  float __thiscall FUN_00b7e430(float* p, char clamp);
  float __thiscall FUN_00b7e4d0();
  float __thiscall FUN_00b7e500();
  uint32_t __thiscall GetAverageRadius(float* p);
};

// @ 0x00b7e390
float __thiscall cPlanetModel::GetWaterHeight() {
  if (mpISphere != 0) {
    cTerrainMapSet* t = mpISphere->GetMap();
    return t->mWaterHeight * t->mMaxHeight + t->mRadius;
  }
  return 0.0f;
}

// @ 0x00b7e3b0
uint32_t __thiscall cPlanetModel::FUN_00b7e3b0(uint32_t a, uint32_t b) {
  mpISphere->GetMap()->ComputeHeight(a, b);
  return a;
}

// @ 0x00b7e3e0
bool __thiscall cPlanetModel::FUN_00b7e3e0(float* p) {
  if (mpISphere != 0) {
    float h = mpISphere->GetMap()->GetHeightAt(p);
    cTerrainMapSet* t2 = mpISphere->GetMap();
    if (h < t2->mWaterHeight * t2->mMaxHeight + t2->mRadius)
      return true;
  }
  return false;
}

// @ 0x00b7e430
float __thiscall cPlanetModel::FUN_00b7e430(float* p, char clamp) {
  cTerrainMapSet* t = mpISphere->GetMap();
  if (mpISphere != 0 && t != 0) {
    float h = t->GetHeightAt(p);
    float d = (t->mWaterHeight * t->mMaxHeight + t->mRadius) - h;
    if (clamp == 0) return d;
    if (d > 0.0f) return d;
  }
  return 0.0f;
}

// @ 0x00b7e4d0
float __thiscall cPlanetModel::FUN_00b7e4d0() {
  if (mpISphere != 0) {
    if (mpISphere->GetMap() != 0)
      return mpISphere->GetMap()->mRadius;
  }
  return 500.0f;
}

// @ 0x00b7e500
float __thiscall cPlanetModel::FUN_00b7e500() {
  float r = 500.0f;
  if (mpISphere != 0 && mpISphere->GetMap() != 0)
    r = mpISphere->GetMap()->mRadius;
  return r + r;
}

// @ 0x00b7e360
void __thiscall cPlanetModel::FUN_00b7e360(int arg) {
  if (mpISphere != 0)
    (*(void(__thiscall*)(void*, int))((*(void***)mpISphere)[0xbc / 4]))(mpISphere, arg);
}

// @ 0x00b7e1a0
void __thiscall cPlanetModel::FUN_00b7e1a0() {
  Memset32(mBits, 0, 0x3000);
  unsigned* p = mContinentMap;
  for (int i = 0; i < 0x18000; ++i)
    p[i] &= 0xc3ffffff;
}

// @ 0x00b7e840
uint32_t __thiscall cPlanetModel::GetAverageRadius(float* p) {
  float f1 = p[0], f2 = p[1], f3 = p[2];
  float a1 = f1 < 0 ? -f1 : f1;
  float a2 = f2 < 0 ? -f2 : f2;
  float a3 = f3 < 0 ? -f3 : f3;
  int i7, i8, i9;
  if (a3 < a1 || a3 < a2) {
    if (a2 < a1) {
      i7 = (int)((f2 / f1 + 1.0f) * 64.0f);
      i8 = (int)((f3 / a1 + 1.0f) * 64.0f);
      i9 = (f1 < 0.0f) ? 3 : 2;
    } else {
      i7 = (int)((f3 / f2 + 1.0f) * 64.0f);
      i8 = (int)((f1 / a2 + 1.0f) * 64.0f);
      i9 = (f2 < 0.0f) ? 5 : 4;
    }
  } else {
    i7 = (int)((f1 / f3 + 1.0f) * 64.0f);
    i8 = (int)((f2 / a3 + 1.0f) * 64.0f);
    i9 = (f3 < 0.0f) ? 1 : 0;
  }
  if (i7 == 0x80) i7 = 0x7f;
  if (i8 == 0x80) i8 = 0x7f;
  return mContinentMap[((i9 * 0x80 + i8) * 0x80 + i7)];
}

// @ 0x00b7e1d0
void __thiscall cPlanetModel::FUN_00b7e1d0(uint32_t mask) {
  mask &= 0x3c000000;
  uint8_t m = (uint8_t)~((mask >> 0x1a) | (mask >> 0x16));
  for (int i = 0; i < 0xc000; ++i)
    mBits[i] &= m;
  uint32_t nm = ~mask;
  for (int i = 0; i < 0x18000; ++i)
    mContinentMap[i] &= nm;
}

// =======================================================================
// union-find over uint16_t array
// =======================================================================
struct UF {
  uint16_t* mParent;  // +0
  uint16_t* mEnd;     // +4
  void __thiscall FUN_00b7e150(uint32_t a, uint16_t b);
  uint16_t __thiscall FUN_00b7e6f0(uint32_t a, uint32_t b);
  void __thiscall FUN_00b7e790(int limit, uint16_t seed);
};

// @ 0x00b7e150
void __thiscall UF::FUN_00b7e150(uint32_t a, uint16_t b) {
  uint16_t* p = mParent;
  uint32_t ia = a & 0xffff;
  while (p[ia] != b) {
    uint16_t n = p[ia];
    p[ia] = b;
    ia = n;
    p = mParent;
  }
}

// @ 0x00b7e6f0
uint16_t __thiscall UF::FUN_00b7e6f0(uint32_t a, uint32_t b) {
  uint16_t* p = mParent;
  uint32_t x = a & 0xffff;
  uint32_t y = b & 0xffff;
  while (p[y] < y) y = p[y];
  while (p[x] < x) x = p[x];
  uint16_t r = (x <= y) ? (uint16_t)x : (uint16_t)y;
  FUN_00b7e150(a, r);
  FUN_00b7e150(b, r);
  return r;
}

// @ 0x00b7e790
void __thiscall UF::FUN_00b7e790(int limit, uint16_t seed) {
  int span = (int)(((char*)mEnd - (char*)mParent) >> 1);
  int n = span < limit ? span : limit;
  for (int i = 0; i < n; ++i) {
    uint16_t* p = mParent;
    uint16_t v = p[i];
    while (p[v] < v) v = p[v];
    p[i] = v;
  }
  uint16_t c = 0;
  for (int j = 0; j < n; ++j) {
    uint16_t* p = mParent;
    uint16_t v;
    if (p[j] == j) { v = seed & c; ++c; }
    else v = p[p[j]];
    p[j] = v;
  }
}

// =======================================================================
// misc
// =======================================================================
// @ 0x00b7e6c0
struct Misc6c0 {
  char pad00[8];
  void* mpObj;   // +8
  void __thiscall FUN_00b7e6c0();
};
void __thiscall Misc6c0::FUN_00b7e6c0() {
  void* p = mpObj;
  if (p != 0) {
    mpObj = 0;
    (*(void(__thiscall*)(void*))((*(void***)p)[2]))(p);
  }
  g_15ddc84.FUN_007a4420(0, 3, 4, 0x400);
}

// @ 0x00b7e4b0
struct GameModeFlags {
  char pad00[0xe8];
  bool fE8;   // +0xe8
  bool fE9;   // +0xe9
  bool fEA;   // +0xea
  void __thiscall FUN_00b7e4b0();
};
void __thiscall GameModeFlags::FUN_00b7e4b0() {
  bool b = true;
  fE8 = b;
  fE9 = b;
  fEA = b;
}

// @ 0x00b7ea30
struct cVecObj {
  char  pad00[0x80];
  char* mBegin;   // +0x80
  char* mEnd;     // +0x84
  char  pad88[0x20];
  char* mDirty;   // +0xa8
  void __thiscall FUN_00b7ea30(uint32_t idx, char v);
};
void __thiscall cVecObj::FUN_00b7ea30(uint32_t idx, char v) {
  if ((int)idx > 0 &&
      idx < (unsigned)((mEnd - mBegin) / 0x18)) {
    char* p = mBegin + 0x11 + idx * 0x18;
    if (*p != v) {
      *p = v;
      mDirty[0xc] = 1;
    }
  }
}

// @ 0x00b7e490
float FUN_00b7e490() {
  if (SP_GetCurrentGameMode() == &gMode_1654c10)
    return gF_1688270;
  return gF_156b5d4;
}

// @ 0x00b7e680
uint16_t FUN_00b7e680(float v) {
  int n = (int)(v * 32767.0f) + 0x8000;
  int z = 0;
  uint16_t* p = n > 0 ? (uint16_t*)&n : (uint16_t*)&z;
  return *p;
}

// @ 0x00b7e560
void SP_RandomDirection3(float* out) {
  float x, y, z, d;
  do {
    x = (float)EA_RandomUniform(&gMathRandom);
    x = x + x - 1.0f;
    if (x < 1.0f) { if (x < -1.0f) x = -1.0f; }
    y = (float)EA_RandomUniform(&gMathRandom);
    y = y + y - 1.0f;
    if (y < 1.0f) { if (y < -1.0f) y = -1.0f; }
    z = (float)EA_RandomUniform(&gMathRandom);
    z = z + z - 1.0f;
    if (z < 1.0f) { if (z < -1.0f) z = -1.0f; }
    d = z * z + x * x + y * y;
  } while (d > 1.0f || d < 0.0001f);
  float inv = 1.0f / sqrtf(d);
  out[0] = inv * x;
  out[1] = inv * y;
  out[2] = inv * z;
}

// =======================================================================
// game-mode class (MI: IHandlerRC + cGonzagoSubsystem) and helpers
// =======================================================================
extern void* gVt_a; extern void* gVt_b; extern void* gVt_c; extern void* gVt_d;
struct CGZSub {
  void __thiscall CGZSubInit();
  void __thiscall CGZSubDtor();
};
struct Gm {
  void*    vt0;       // +0x00
  char     sub[0x1c]; // +0x04 cGonzagoSubsystem
  void*    listNext;  // +0x20
  void*    listPrev;  // +0x24
  int      f28;       // +0x28
  int      f2c;       // +0x2c
  char     f30;       // +0x30
  uint8_t  f31;       // +0x31
  char     pad32[2];
  void*    f34;       // +0x34
  Gm*  __thiscall ctor();
  void __thiscall dtor(char del);
  void __thiscall FUN_00b7dec0();
};
struct GmSec { void __thiscall FUN_00b7e070(); };

// @ 0x00b7df80
Gm* __thiscall Gm::ctor() {
  *(void**)this = &gVt_a;
  ((CGZSub*)((char*)this + 4))->CGZSubInit();
  *(void**)this = &gVt_b;
  *(void**)((char*)this + 4) = &gVt_c;
  *(void**)((char*)this + 8) = &gVt_d;
  listNext = (char*)this + 0x20;
  listPrev = (char*)this + 0x20;
  f2c = 0;
  f31 = 0;
  f34 = 0;
  void* local = 0;
  void* pm = SP_PropertyManager();
  (*(void(__thiscall*)(void*, int, int, void**))((*(void***)pm)[0x2c / 4]))(pm, 0x5f848353, 0x243ad2b, &local);
  if (local) (*(void(__thiscall*)(void*))((*(void***)local)[1]))(local);
  return this;
}

// @ 0x00b7e010
void __thiscall Gm::dtor(char del) {
  *(void**)this = &gVt_b;
  *(void**)((char*)this + 4) = &gVt_c;
  *(void**)((char*)this + 8) = &gVt_d;
  if (f34) (*(void(__thiscall*)(void*))((*(void***)f34)[0xc0 / 4]))(f34);
  FUN_00b7d710((char*)this + 0x20);
  ((CGZSub*)((char*)this + 4))->CGZSubDtor();
  *(void**)this = &gVt_a;
  if (del & 1) operator_delete__(this);
}

// @ 0x00b7dec0
void __thiscall Gm::FUN_00b7dec0() {
  void* pm = SP_PlanetModel();
  void* edi = *(void**)((char*)pm + 0x24);
  if (FUN_00f678a0() || FUN_00f678c0()) {
    SP_TerrainEditor(); FUN_00f6bc10();
    SP_TerrainEditor(); FUN_00f67890(0);
    SP_TerrainEditor(); FUN_00f678b0(0);
  }
  void* c = edi ? edi : g_16c9e5c;
  if (c) (*(void(__thiscall*)(void*))((*(void***)c)[0x40 / 4]))(c);
  f2c = 0;
  if (f34 != 0) {
    void* p = f34;
    f34 = 0;
    (*(void(__thiscall*)(void*))((*(void***)p)[0xc0 / 4]))(p);
  }
  if (f31 != 0) FUN_00b8c0f0();
  f31 = 0;
  FUN_00b7d710((char*)this + 0x20);
  listNext = (char*)this + 0x20;
  listPrev = (char*)this + 0x20;
}

// @ 0x00b7e070
void __thiscall GmSec::FUN_00b7e070() {
  Gm* b = (Gm*)((char*)this - 4);
  b->FUN_00b7dec0();
  void* ms = SP_MessageServer();
  (*(void(__thiscall*)(void*, void*, int, int))((*(void***)ms)[0x2c / 4]))(ms, b, 0x29ffa8d, 0xffffd8f1);
}

// @ 0x00b7e0b0
void __cdecl FUN_00b7e0b0(void* self) {
  int v = 4;
  void* app = SP_App();
  int mode = (*(int(__thiscall*)(void*))((*(void***)app)[0x38 / 4]))(app);
  switch (mode) {
    case 0x1654c01: case 0x1654c06: case 0x1654c10: v = 0; break;
    case 0x1654c02: (*(void(__thiscall*)(void*, int))((*(void***)self)[0x1c / 4]))(self, 1); return;
    case 0x1654c04: (*(void(__thiscall*)(void*, int))((*(void***)self)[0x1c / 4]))(self, 2); return;
    case 0x1654c05: (*(void(__thiscall*)(void*, int))((*(void***)self)[0x1c / 4]))(self, 3); return;
  }
  (*(void(__thiscall*)(void*, int))((*(void***)self)[0x1c / 4]))(self, v);
}

// @ 0x00b7e220  (cube-map face/tile walker)
void __cdecl FUN_00b7e220(uint32_t param_1, int* param_2, int* param_3, int* param_4) {
  for (;;) {
    uint32_t uVar1 = (uint32_t)param_2[2];
    uint32_t uVar3 = (uVar1 & 1) - 1;
    uint32_t uVar2 = ~uVar3;
    int iVar4 = (int)uVar1 >> 1;
    int iVar6 = (int)((uVar2 & 2) - 1);
    if (!((int)uVar1 >> 2 <= *param_2)) {
      if (*param_2 > (int)(param_1 - ((int)uVar1 >> 2))) {
        param_2[2] = (uVar2 & 1) + (uint32_t)(uint8_t)(DAT_014653b9)[iVar4 * 4] * 2;
        iVar4 = *param_2;
        *param_2 = (int)(uVar2 & param_1) - param_2[1] * iVar6;
        param_2[1] = (iVar4 - (int)param_1) * iVar6 + (int)(uVar3 & param_1);
        if (param_3 != 0) {
          iVar4 = *param_3;
          *param_3 = -(*param_4 * iVar6);
          *param_4 = iVar4 * iVar6;
        }
        continue;
      }
      iVar4 = (iVar4 + 1) >> 1;
      if (param_2[1] < iVar4) {
        param_2[2] = (uint32_t)(uint8_t)(DAT_014653ba)[((int)uVar1 >> 1) * 4] * 2 + 1;
        iVar4 = param_2[1] + (int)param_1;
      } else {
        if (param_2[1] <= (int)(param_1 - iVar4)) return;
        param_2[2] = (uint32_t)(uint8_t)(DAT_014653ba)[((int)uVar1 >> 1) * 4] * 2;
        iVar4 = param_2[1] - (int)param_1;
      }
      int iVar5 = *param_2;
      iVar4 = iVar4 * iVar6 + (int)(uVar3 & param_1);
      *param_2 = iVar4;
      param_2[1] = (int)(uVar2 & param_1) - iVar5 * iVar6;
      if (param_3 != 0) {
        iVar4 = *param_3;
        *param_3 = *param_4 * iVar6;
        *param_4 = -(iVar4 * iVar6);
      }
      continue;
    }
    param_2[2] = (uVar3 & 1) + (uint32_t)(uint8_t)(DAT_014653b9)[iVar4 * 4] * 2;
    int iVar5 = *param_2 + (int)param_1;
    int iv = param_2[1] * iVar6 + (int)(uVar3 & param_1);
    *param_2 = iv;
    param_2[1] = (int)(uVar2 & param_1) - iVar5 * iVar6;
    if (param_3 != 0) {
      iVar4 = *param_3;
      *param_3 = *param_4 * iVar6;
      *param_4 = -(iVar4 * iVar6);
    }
  }
}

// @ 0x00b7daf0  (terrain/impostor property setup; large, partial translation)
void __thiscall cPlanetModel::FUN_00b7daf0() {
  // Translated control flow is incomplete; see partial.txt.
  void* ctx = SP_GetUniverseContext();
  if (ctx == 0) {
    if (SP_GetActivePlanet() == this) {
      void* pm = SP_PlanetModel();
      if (pm && *(void**)((char*)pm + 0x24))
        (*(void(__thiscall*)(void*))((*(void***)*(void**)((char*)pm + 0x24))[2]))(*(void**)((char*)pm + 0x24));
    }
  }
}
// --- equivalence checker address annotations

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
}
