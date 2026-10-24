// Slice s00e56820 (batch spcg1, slice 0) — SPGonzago/SPCellGame.obj.
// Cell-game grid/cell pool fill helpers, level-range predicates, curve lookup and
// cell filtering. Optimised: /O2 /MD /Gy /TP /arch:SSE /fp:fast.
#include "types.h"
#include <math.h>

// ---- globals ----
extern "C" char  gspCellGame_16b3c04[];   // holds SP::cCellGame*
extern "C" char  g_16b3c0c[];             // SPUI layout manager global (pointer)
extern "C" void* g_16b3c10;
extern float g_16b3c28, g_16b3c2c, g_16b3c30;
extern float g_15a7c4c, g_15a7c50, g_15a7c54, g_15a7c58;
extern float gUp_15a7c40[3];               // 0x015a7c40 world up axis (x, y, z)
extern "C" float g_1483f08;
extern "C" int   gLvlTableA[];            // 0x01483c14, stride 7 dwords
extern "C" int   gLvlTableB[];            // 0x01483c34
extern "C" int   gLvlTable1000[];         // 0x01483e60
extern "C" void* g_15a842c;               // PTR_015a842c
extern "C" float g_1485720;               // 1.0f
extern "C" float g_148554c;               // 127.999985
extern "C" float g_1485548;               // 1.5f

#define G (*(char**)gspCellGame_16b3c04)

// ---- pool helpers (thiscall members) ----
struct Pool {
  void* Alloc();            // 0x00b72160
  void* Get(unsigned id);   // 0x00b72210, ret 4
  void* GetValid(int id);   // 0x00b721d0, ret 4
};

static inline Pool& CellsPool() { return *(Pool*)(G + 0x1c); }
static inline Pool& GridPool()  { return *(Pool*)(G + 0x54); }

// intrusive-ptr temp used by the resource lookups
struct Ref {
  void* p;
  void Init();      // 0x00743b50
  void Release();   // 0x00e82130
};

// ---- external callees ----
extern "C" void* __cdecl thunk_FUN_00e823a0(int id, Ref* out);      // 0x00e4cc40
extern "C" char* __cdecl FUN_00e4ce40(Ref* out);                    // 0x00e4ce40
extern "C" void  __cdecl FUN_00e82130_rel();                        // unused placeholder
extern "C" unsigned __cdecl FNV1_String8(const char* s, unsigned seed, int mode); // 0x00932e80
extern "C" void  __cdecl config_0e50450(unsigned key, void* val);   // 0x00e50450
extern "C" void  __cdecl apply_0e504b0(void* w, float a);           // 0x00e504b0
extern "C" void  __cdecl toggle_0e53660(int a, int b);              // 0x00e53660
extern "C" float __cdecl curve_0e56700(const void* tbl, int n, float x, float z); // 0x00e56700
extern "C" int   __cdecl FUN_00e87260(int a, int b, float c, int* out, int max, int fl); // 0x00e87260
extern "C" float __cdecl FUN_00e4f9d0(void* guard);                 // 0x00e4f9d0
extern "C" char* __cdecl FUN_00e52910(void* e);                     // 0x00e52910
extern "C" float __cdecl FUN_00e837c0(int a, float b);              // 0x00e837c0
extern "C" float __cdecl FUN_00e513d0(float a, float b, float c, float d, float e); // 0x00e513d0
extern "C" void* __cdecl QuaternionFromFacingAndUp(float* a, float* b, void* c);    // 0x0069b600
extern "C" double __cdecl eaftol_floor(double);                     // 0x011e0906 (iat floor)

struct Layout { void* FindWindowByID(unsigned id, char flag); };    // 0x008105b0, ret 8
namespace SP { int __fastcall sGetSourceLevel(void* unused, int level); } // 0x00e4ee60

static inline int* LevelEntry(int level) {
  if (level == 1000) return gLvlTable1000;
  int i = 0;
  if (level >= 0) {
    int* p = gLvlTableB;
    do { p += 7; ++i; } while (level >= *p);
  }
  return &gLvlTableA[i * 7];
}

static inline float SqrtF(float x) {
  return (float)sqrt((double)x);
}

// @ 0x00e56820
bool FUN_00e56820(float a, float b) {
  float r = curve_0e56700(&g_1483f08, 4, a, b);
  void* layout = *(void**)(*(char**)g_16b3c0c + 0x90);
  void* w = ((Layout*)layout)->FindWindowByID(0x5af4ae5, 1);
  apply_0e504b0(w, r);
  return true;
}

// @ 0x00e56870
void FUN_00e56870(void) {
  unsigned id = (unsigned)GridPool().Alloc();
  char* e = (char*)GridPool().Get(id);
  int neg = -1;
  *(float*)(e + 0x1c) = 5.0f;
  *(float*)(e + 0x20) = 5.0f;
  *(int*)(e + 0x28) = 0;
  *(int*)(e + 0x2c) = 0;
  *(int*)(e + 0x38) = 0;
  *(int*)(e + 0x3c) = 0;
  *(int*)(e + 0x24) = 0x2c;
  *(int*)(e + 0x30) = neg;
  *(int*)(e + 0x34) = neg;
  *(float*)(e + 0x40) = 0.0f;
  *(float*)(e + 0x44) = 0.0f;
  *(int*)(e + 0x48) = *(int*)&g_16b3c28;
  *(int*)(e + 0x4c) = *(int*)&g_16b3c2c;
  *(int*)(e + 0x50) = *(int*)&g_16b3c30;
  *(int*)(e + 0x54) = *(int*)&g_16b3c28;
  *(int*)(e + 0x58) = *(int*)&g_16b3c2c;
  *(int*)(e + 0x5c) = *(int*)&g_16b3c30;
  *(int*)(e + 0x60) = *(int*)&g_15a7c4c;
  *(int*)(e + 0x64) = *(int*)&g_15a7c50;
  *(int*)(e + 0x68) = *(int*)&g_15a7c54;
  *(int*)(e + 0x6c) = *(int*)&g_15a7c58;
  *(int*)(e + 0x70) = 0;
  *(char*)(e + 0x74) = 0;
  *(int*)(e + 0x78) = 0;
  *(int*)(e + 0x04) = 0;
  *(char*)(e + 0x08) = 0;
  g_16b3c10 = (void*)id;
  GridPool().Get(id);
}

// @ 0x00e56950
void FUN_00e56950(void) {
  toggle_0e53660(2, 1);
  *(char*)(*(char**)g_16b3c0c + 0x938) = 1;
  config_0e50450(FNV1_String8("CAllout_CLG_Opening", 0x811c9dc5, 1), 0);
  config_0e50450(FNV1_String8("CAllout_CLG_ProgressBar", 0x811c9dc5, 1), &g_15a842c);
}

// @ 0x00e569b0
bool FUN_00e569b0(void) {
  int id = *(int*)(G + 0x411c);
  Pool* p = (Pool*)(G + 0x1c);
  char* e = (char*)p->GetValid(id);
  if (!e) return false;
  e[0x17c] = 1;
  e[0x17b] = 1;
  e[0x17f] = 1;
  e[0x178] = 1;
  e[0x17a] = 1;
  e[0x17e] = 1;
  e[0x188] = 1;
  e[0x16c] = 1;
  e[0x189] = 1;
  return true;
}

// @ 0x00e56a10
bool FUN_00e56a10(void) {
  unsigned id = (unsigned)GridPool().Alloc();
  char* e = (char*)GridPool().Get(id);
  *(float*)(e + 0x1c) = 0.75f;
  *(float*)(e + 0x20) = 0.75f;
  *(int*)(e + 0x24) = 0x31;
  *(int*)(e + 0x28) = 0;
  *(int*)(e + 0x2c) = 0;
  *(int*)(e + 0x30) = -1;
  *(int*)(e + 0x34) = -1;
  *(int*)(e + 0x38) = 0;
  *(int*)(e + 0x3c) = 0;
  *(float*)(e + 0x40) = 0.0f;
  *(float*)(e + 0x44) = 0.0f;
  *(int*)(e + 0x48) = *(int*)&g_16b3c28;
  *(int*)(e + 0x4c) = *(int*)&g_16b3c2c;
  *(int*)(e + 0x50) = *(int*)&g_16b3c30;
  *(int*)(e + 0x54) = *(int*)&g_16b3c28;
  *(int*)(e + 0x58) = *(int*)&g_16b3c2c;
  *(int*)(e + 0x5c) = *(int*)&g_16b3c30;
  *(int*)(e + 0x60) = *(int*)&g_15a7c4c;
  *(int*)(e + 0x64) = *(int*)&g_15a7c50;
  *(int*)(e + 0x68) = *(int*)&g_15a7c54;
  *(int*)(e + 0x6c) = *(int*)&g_15a7c58;
  *(int*)(e + 0x70) = 0;
  *(char*)(e + 0x74) = 0;
  *(int*)(e + 0x78) = 0;
  *(int*)(e + 0x04) = 0;
  *(char*)(e + 0x08) = 0;
  return FUN_00e569b0();
}

// @ 0x00e56ae0
bool FUN_00e56ae0(char* p, float dt) {
  float dx = *(float*)(p + 0x4c) - *(float*)(p + 0x08);
  float dy = *(float*)(p + 0x50) - *(float*)(p + 0x0c);
  float dz = *(float*)(p + 0x54) - *(float*)(p + 0x10);
  float dist = SqrtF(dy * dy + (dz * dz + dx * dx));
  if (dist < 1.0f) *(float*)(p + 0x368) = 0.0f;
  if (dist < 3.0f) return false;
  if (*(float*)(p + 0x368) > 1.5f) return false;
  *(float*)(p + 0x368) = *(float*)(p + 0x368) + dt;
  return true;
}

// @ 0x00e56b50
float FUN_00e56b50(char* p, unsigned flags, float x) {
  Ref t; t.Init();
  char* o = FUN_00e4ce40(&t);
  if (flags & 2) {
    float r = FUN_00e837c0(0x38ec9850, *(float*)(p + 0x154)) * *(float*)(o + 0xb0);
    t.Release();
    return r;
  }
  if ((flags & 9) == 0) {
    float r = *(float*)(o + 0xb4);
    t.Release();
    return r;
  }
  float r = FUN_00e513d0(*(float*)(o + 0xa0), *(float*)(o + 0xa4), x,
                         *(float*)(o + 0xa8), *(float*)(o + 0xac));
  t.Release();
  return r;
}

// @ 0x00e56c30
void FUN_00e56c30(float tile, float* in, int* outA, int* outB) {
  float inv = 1.0f / tile;
  float scale = inv * 127.999985f;
  // The original evaluates x's quotient and remainder in x87 double precision (the floor()
  // argument is the unrounded double product in[0]*inv), but z's floor argument is the
  // float-rounded fz = inv*in[1] -- so a quotient that rounds across an integer boundary
  // keeps its original band on each axis independently.
  float fz = inv * in[1];
  float ax = (float)(((double)in[0] - (double)tile * eaftol_floor((double)in[0] * (double)inv)) *
                     (double)scale);
  int ix = (int)ax;
  // The original decrements on the unordered (NaN) case too (ucomiss + cmovb), so the guard
  // is !(ax >= ix), not (ax < ix): a NaN tile (tile==0 -> inf*0) must still yield 0x7fffffff.
  if (!(ax >= (float)ix)) ix = ix - 1;
  *outA = ix;
  float az = (float)(((double)in[1] - (double)tile * eaftol_floor((double)fz)) * (double)scale);
  int iz = (int)az;
  if (!(az >= (float)iz)) iz = iz - 1;
  *outB = iz;
  int a = *outA;
  if (a < 1) a = 0;
  if (a > 0x80) a = 0x80;
  *outA = a;
  int b = *outB;
  if (b < 1) b = 0;
  if (b > 0x80) b = 0x80;
  *outB = b;
}

// @ 0x00e56d40
void FUN_00e56d40(float* out, float* in) {
  int l4, l8;
  FUN_00e56c30(*(float*)(G + 4), in, &l4, &l8);
  int idx = l8 * 0x80 + l4;
  char* g = G;
  float* tbl = *(float**)(*(int*)g + 0x18);
  float scale = *(float*)(g + 8);
  out[0] = tbl[idx * 3] * scale;
  out[1] = tbl[idx * 3 + 1] * scale;
  out[2] = scale * 0.0f;
}

// @ 0x00e56dc0
bool FUN_00e56dc0(int* ids, int count, int excl, char flag) {
  for (int i = 0; i < count; ++i) {
    int id = ids[i];
    if (id == excl) continue;
    Pool* p = (Pool*)(G + 0x1c);
    char* e = (char*)p->Get(id);
    Ref t; t.Init();
    char* o = (char*)thunk_FUN_00e823a0(*(int*)(e + 0x108), &t);
    if (*(int*)(o + 0xb4) == 5 && flag == 0) {
      t.Release();
      continue;
    }
    t.Release();
    return false;
  }
  return true;
}

// @ 0x00e56e50
unsigned FUN_00e56e50(int want, int slot, int a, int b, float c) {
  int ids[512];
  int n = FUN_00e87260(a, b, c, ids, 0x200, 0);
  for (int i = 0; i < n; ++i) {
    unsigned id = (unsigned)ids[i];
    Pool* p = (Pool*)(G + 0x1c);
    char* e = (char*)p->Get(id);
    if (*(int*)(e + 0x358) != slot) continue;
    Ref t; t.Init();
    char* o = (char*)thunk_FUN_00e823a0(*(int*)(e + 0x108), &t);
    if (*(int*)(o + 0xb4) == want) {
      t.Release();
      return id;
    }
    t.Release();
  }
  return 0;
}

// @ 0x00e56f20
bool FUN_00e56f20(int idx) {
  int level = *(int*)(*(char**)(G + 0x5190) + 0x1c);
  int v = *LevelEntry(level);
  int lo = v - 1;
  int hi = v + 3;
  if (idx < lo || idx > hi) return false;
  return true;
}

// @ 0x00e56f80
void FUN_00e56f80(char* p, float* to) {
  char* e = (char*)CellsPool().GetValid(*(int*)(p + 0x170));
  float n[3];   // facing vector handed to QuaternionFromFacingAndUp (must be contiguous)
  if (!e) {
    n[0] = to[0] - *(float*)(p + 0x4c);
    n[1] = to[1] - *(float*)(p + 0x50);
    n[2] = to[2] - *(float*)(p + 0x54);
    float inv = 1.0f / SqrtF((n[0] * n[0] + n[1] * n[1] + n[2] * n[2]) + 1e-08f);
    n[0] = inv * n[0];
    n[1] = n[1] * inv;
    n[2] = n[2] * inv;
  } else {
    n[0] = *(float*)(e + 0x4c) - *(float*)(p + 0x4c);
    n[1] = *(float*)(e + 0x50) - *(float*)(p + 0x50);
    n[2] = *(float*)(e + 0x54) - *(float*)(p + 0x54);
    float inv = 1.0f / SqrtF((n[0] * n[0] + n[1] * n[1] + n[2] * n[2]) + 1e-08f);
    n[0] = inv * n[0];
    n[1] = n[1] * inv;
    n[2] = n[2] * inv;
  }
  if (n[0] * n[0] + n[1] * n[1] + n[2] * n[2] < 1.5258789e-05f) {
    *(char*)(p + 4) = 1;
    return;
  }
  if (*(int*)(p + 0x174) == 0) {
    float neg[3];
    neg[0] = -n[0];
    neg[1] = -n[1];
    neg[2] = -n[2];
    float* q = (float*)QuaternionFromFacingAndUp(n, neg, gUp_15a7c40);
    *(int*)(p + 0x14) = ((int*)q)[0];
    *(int*)(p + 0x18) = ((int*)q)[1];
    *(int*)(p + 0x1c) = ((int*)q)[2];
    *(int*)(p + 0x20) = ((int*)q)[3];
  }
  *(float*)(p + 8) = to[0];
  *(float*)(p + 0x0c) = to[1];
  *(float*)(p + 0x10) = to[2];
  *(char*)(p + 4) = 0;
}

// @ 0x00e57170  (id passed in EAX by the original)
void FUN_00e57170_impl(int id, float scale) {
  char* e = (char*)CellsPool().Get(id);
  float v = (SqrtF(3.0f) / (*(float*)(G + 0x514c) / *(float*)(G + 0x5150))) * scale;
  *(float*)(e + 0xb4) = v;
  float s = FUN_00e4f9d0(*(void**)(e + 0x108));
  float r = (v * v) * s;
  *(float*)(e + 0xb8) = r;
  *(float*)(e + 0xbc) = 1.0f / r;
}

// @ 0x00e571f0
bool FUN_00e571f0(int id, int state) {
  char* e = (char*)CellsPool().GetValid(id);
  if (!e) return false;
  unsigned* p = (unsigned*)(e + 0x18c);
  unsigned old = *p;
  int r = 1;
  e[0x178] = (char)r;
  if (old <= 3) {
    switch (state) {
    case 2:
      *(int*)(e + 0x18c) = 2;
      break;
    case 3:
      *(int*)(e + 0x18c) = 1;
      break;
    case 4:
      *(int*)(e + 0x18c) = 3;
      break;
    }
  }
  return r != 0;
}

// @ 0x00e57260
void FUN_00e57260(int* p, int a1, float a2) {
  int id0 = *p;
  unsigned id = (unsigned)GridPool().Alloc();
  char* e = (char*)GridPool().Get(id);
  *(float*)(e + 0x1c) = a2;
  *(float*)(e + 0x20) = a2;
  *(int*)(e + 0x24) = 0x21;
  *(int*)(e + 0x28) = id0;
  *(float*)(e + 0x40) = 0.0f;
  *(float*)(e + 0x44) = 0.0f;
  *(int*)(e + 0x2c) = 0;
  *(int*)(e + 0x3c) = 0;
  *(int*)(e + 0x30) = -1;
  *(int*)(e + 0x34) = -1;
  *(int*)(e + 0x38) = a1;
  *(int*)(e + 0x48) = *(int*)&g_16b3c28;
  *(int*)(e + 0x4c) = *(int*)&g_16b3c2c;
  *(int*)(e + 0x50) = *(int*)&g_16b3c30;
  *(int*)(e + 0x54) = *(int*)&g_16b3c28;
  *(int*)(e + 0x58) = *(int*)&g_16b3c2c;
  *(int*)(e + 0x5c) = *(int*)&g_16b3c30;
  *(int*)(e + 0x60) = *(int*)&g_15a7c4c;
  *(int*)(e + 0x64) = *(int*)&g_15a7c50;
  *(int*)(e + 0x68) = *(int*)&g_15a7c54;
  *(int*)(e + 0x6c) = *(int*)&g_15a7c58;
  *(int*)(e + 0x70) = 0;
  *(char*)(e + 0x74) = 0;
  *(int*)(e + 0x78) = 0;
  *(int*)(e + 0x04) = 0;
  *(char*)(e + 0x08) = 0;
  FUN_00e571f0(*p, a1);
}

// @ 0x00e57340
int FUN_00e57340(char* cell) {
  int src = *(int*)(cell + 0x358);
  if (src == -1) {
    char* lvlObj = *(char**)(G + 0x5190);
    src = SP::sGetSourceLevel(lvlObj, *(int*)(lvlObj + 0x1c));
  }
  int level = *(int*)(*(char**)(G + 0x5190) + 0x1c);
  int v = (src - *LevelEntry(level)) + 2;
  return v < 1 ? 0 : (v > 4 ? 4 : v);
}

// @ 0x00e573e0
int FUN_00e573e0(char* a, char* b) {
  int la = *(int*)(a + 0x358);
  if (la == -1) {
    char* lvlObj = *(char**)(G + 0x5190);
    la = SP::sGetSourceLevel(lvlObj, *(int*)(lvlObj + 0x1c));
  }
  int lb = *(int*)(b + 0x358);
  if (lb == -1) {
    char* lvlObj = *(char**)(G + 0x5190);
    lb = SP::sGetSourceLevel(lvlObj, *(int*)(lvlObj + 0x1c));
  }
  int v = (lb - la) + 2;
  return v < 1 ? 0 : (v > 4 ? 4 : v);
}

// @ 0x00e57460
bool FUN_00e57460(char* a, char* b) {
  if (*(int*)(a + 0x108) == *(int*)(b + 0x108)) return true;
  if (*(char*)(a + 0x112) == 1 || *(char*)(b + 0x112) == 1) return false;
  Ref t; t.Init();
  char* oa = (char*)thunk_FUN_00e823a0(*(int*)(a + 0x108), &t);
  if (*(char*)(oa + 0x301) == 1 && *(int*)b == *(int*)(G + 0x411c)) {
    if (FUN_00e57340(a) == 1) {
      t.Release();
      return true;
    }
  }
  if (*(char*)(oa + 0x300) == 1 && *(int*)b == *(int*)(G + 0x411c)) {
    t.Release();
    return true;
  }
  if (*(int*)(oa + 0x2fc) != 0) {
    Ref t2; t2.Init();
    char* ob = (char*)thunk_FUN_00e823a0(*(int*)(b + 0x108), &t2);
    if (*(int*)(ob + 0x2fc) != 0 && *(int*)(oa + 0x2fc) == *(int*)(ob + 0x2fc)) {
      t2.Release();
      t.Release();
      return true;
    }
    t2.Release();
  }
  t.Release();
  return false;
}

// @ 0x00e57560
bool FUN_00e57560(char* p) {
  Ref t; t.Init();
  char* def = (char*)thunk_FUN_00e823a0(*(int*)(p + 0x108), &t);
  int which = *(int*)(*(char**)(G + 0x5190) + 0x7c);
  int* q;
  if (which == 0) {
    q = (int*)(def + 0x248);
    if (*q == -1) q = (int*)(def + 0xe0);
  } else if (which == 2) {
    q = (int*)(def + 0x194);
    if (*q == -1) q = (int*)(def + 0xe0);
  } else {
    q = (int*)(def + 0xe0);
  }
  bool r;
  if (*q == 0 && *(int*)p != *(int*)(G + 0x411c)) r = false;
  else r = true;
  t.Release();
  return r;
}

// @ 0x00e575f0
void FUN_00e575f0(char* p, int v) {
  Ref t; t.Init();
  char* def = (char*)thunk_FUN_00e823a0(*(int*)(p + 0x108), &t);
  int which = *(int*)(*(char**)(G + 0x5190) + 0x7c);
  char* q;
  if (which == 0) {
    q = def + 0x248;
    if (*(int*)q == -1) q = def + 0xe0;
  } else if (which == 2) {
    q = def + 0x194;
    if (*(int*)q == -1) q = def + 0xe0;
  } else {
    q = def + 0xe0;
  }
  if (q[0x91] == 1) {
    char* s = FUN_00e52910(def);
    *(float*)(p + 0x21c) = *(float*)(s + 0x7c);
    *(int*)(p + 0x220) = v;
    *(int*)(p + 0x22c) = 0;
    *(float*)(p + 0x230) = 0.0f;
  } else {
    char* s = FUN_00e52910(def);
    if (s[0x8c] != 1) {
      t.Release();
      return;
    }
    char* s2 = FUN_00e52910(def);
    *(float*)(p + 0x230) = *(float*)(s2 + 0x84);
    *(int*)(p + 0x22c) = v;
    *(int*)(p + 0x220) = 0;
    *(float*)(p + 0x21c) = 0.0f;
  }
  *(int*)(p + 0x214) = 0;
  *(int*)(p + 0x208) = 0;
  *(float*)(p + 0x224) = 0.0f;
  t.Release();
}

// @ 0x00e576f0  (this in ESI by the original)
void FUN_00e576f0(char* p, int v) {
  Ref t; t.Init();
  char* def = (char*)thunk_FUN_00e823a0(*(int*)(p + 0x108), &t);
  int which = *(int*)(*(char**)(G + 0x5190) + 0x7c);
  char* q;
  if (which == 0) {
    q = def + 0x248;
    if (*(int*)q == -1) q = def + 0xe0;
  } else if (which == 2) {
    q = def + 0x194;
    if (*(int*)q == -1) q = def + 0xe0;
  } else {
    q = def + 0xe0;
  }
  if (*(int*)q == 0x1006) {
    FUN_00e575f0(p, v);
  }
  t.Release();
}
