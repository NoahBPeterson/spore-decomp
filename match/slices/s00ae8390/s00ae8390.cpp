// Slice s00ae8390 (gold4 #126) -- the Spore space "comm screen" host object and its
// neighbouring comm-screen/front-end helpers.
//
// The host methods (FUN_00ae8390/8510/8820/8970/8d00/8ea0) drive two parallel display
// slots on an object with paired refcounted members at +0x24/0x28 (handles +0x2c/0x30),
// sprite objects at +0x34/0x38, renderer handles at +0x1c/0x20, per-slot scalars/flags
// at +0x7c..0x92 and the environment id at +0x94 (0x2ccd1d2 == space).
//
// FUN_00ae9000/9150/9170/9330/9390 are small cSPUICommScreen layout/init/query helpers,
// FUN_00ae9040 is a star/mission predicate, FUN_00ae90d0 configures the audio "comm"
// channel, and FUN_00ae93f0 is a vector search on the comm-entry list.
//
// Every function is written as a member of one dummy type `Host` so MSVC emits the
// `ecx`-based (thiscall / fastcall) calling convention the original uses; the raw-offset
// macros stand in for the partially recovered class layout.
//
// Flags: default VS2008 (/O2 /MD /Gy /EHsc /TP).
#include "types.h"

typedef unsigned int   u32;
typedef unsigned char  u8;
typedef signed   int   i32;
typedef unsigned short u16;

#define PI(p, off) (*(int*)((char*)(p) + (off)))
#define PU(p, off) (*(u32*)((char*)(p) + (off)))
#define PB(p, off) (*(u8*)((char*)(p) + (off)))
#define PF(p, off) (*(float*)((char*)(p) + (off)))
#define PP(p, off) ((void**)((char*)(p) + (off)))
#define PS(p, off) ((char*)(p) + (off))

// ---- externals (named FUN_<va>; difftest resolves relocations by hex) -------
void* FUN_0080d5f0(u32 x);                 // 0x80d5f0
u32   FUN_0080d610();                      // 0x80d610
void* FUN_0080db70();                      // 0x80db70
void* FUN_0080db90();                      // 0x80db90
void* FUN_00401010();                      // 0x401010
void  FUN_00478db0(u32 x);                 // 0x478db0
void  FUN_007c53d0(u32 x);                 // 0x7c53d0
void  FUN_007c4d00(void* x);               // 0x7c4d00
void  FUN_007c4b50(float x);               // 0x7c4b50
int   FUN_009b2340(void* out, int b, u32 p, void* c, int d, int e);   // 0x9b2340
int   FUN_00b3d490();                      // 0xb3d490
int   FUN_00a04c80(int x);                 // 0xa04c80
void  FUN_00a02b00(int x);                 // 0xa02b00
void  FUN_00a02c30();                      // 0xa02c30
int   FUN_00aed4d0();                      // 0xaed4d0
u32   FUN_00b3d2a0(u32 a);                 // 0xb3d2a0  SP_StarManager
u32   FUN_00ba6dc0(u32 a);                 // 0xba6dc0
u32   FUN_00ba9370(u32 a);                 // 0xba9370  cStarManager::GetEmpireByID
int   FUN_00feb9f0(u32 a);                 // 0xfeb9f0  SP::GetMissionManager
int   FUN_00fee190(u32 a);                 // 0xfee190
int   FUN_0100e730(u32 a, u32 b);          // 0x100e730
int   FUN_0102bd0();                       // 0x1002bd0  SP::SpaceGameGet
int   FUN_01075500(int ecx);               // 0x1075500  (thiscall, ecx = game obj)
int   FUN_010666a0();                      // 0x10666a0
int   FUN_01068350(void* ecx);             // 0x1068350  (thiscall)
void* FUN_00a206f0();                      // 0xa206f0  EA::Audio::GetSystemAT
void* SP_LightingManager();                // SP::LightingManager
void* FUN_0069b440(void* out, const float* dir, const void* up);   // Matrix3FromFacingAndUp
void  FUN_0041cb40(void* m, const void* src);                       // Matrix3::Assign
void  FUN_00692f90_ctor(void* obj, void* p1, void* p2, u32 p3);  // cVarListSerializer ctor
int   FUN_00692900(void* obj, void* stream);   // cVarListSerializer::Serialize
int   FUN_0093aa70(void* s, const u32* p, int n, int flags);      // EA::IO::WriteUint32
void* FUN_00dd1ca0(const void* desc);         // 0xdd1ca0 cSPUILayout::cSPUILayout
void* FUN_00dd1ca0_2(int a, int b);           // 2-arg form
void  FUN_00dd4260(void* obj, const void* desc);  // SP::cSPUICommScreen::Init

// opaque thiscall externals (member names carry the VA so difftest maps them)
struct ThAnim2  { void FUN_00a05270(); };                       // SP::cAnimatingCreature::Release
struct ThModels2{ void FUN_0080dfc0(); int FUN_0080df80(); };   // dtor / Release
struct ThViewer { void FUN_007c4b50(float); };                  // cViewer::FUN_007c4b50
struct ThLayout2 { void FUN_00dd2780(); };                      // layout step at 0xdd2780
struct ThCtor   { void* FUN_00dd1ca0(const void* d); void* FUN_00dd1ca0b(int a, int b); };  // 0xdd1ca0
struct ThSerial { void FUN_00692f90(void* p1, void* p2, u32 p3); int FUN_00692900(void* stream); };  // cVarListSerializer
struct ThInit   { void FUN_00dd4260(); };                       // 0xdd4260 Init

struct Host {
  static void animRelease(int o) { ((ThAnim2*)(void*)o)->FUN_00a05270(); }
  static void modelsDtor(int o) { ((ThModels2*)(void*)o)->FUN_0080dfc0(); }
  static void modelsRelease(int o) { ((ThModels2*)(void*)o)->FUN_0080df80(); }
  void FUN_00ae9000(int a);
  void FUN_00ae9150(int a, int b);
  int FUN_00ae9040(int a, int b, u32* out1, u32* out2);
  void FUN_00ae90d0();
  int FUN_00ae9390();
  void FUN_00ae9330();
  void FUN_00ae9170(int* stream);
  int FUN_00ae93f0(int a2, int a3, int a4, int a5, int a6);
  void FUN_00ae8ea0();
  void FUN_00ae8390();
  int FUN_00ae8820(u32* a2, float a3, int a4, int a5, int a6);
  void FUN_00ae8d00(int a2, int a3, float f4, float f5, int* idx);
  void FUN_00ae8970(int idx);
  void FUN_00ae8510(int dtMs);
};

// @ 0x00ae9000
void Host::FUN_00ae9000(int a) {
  u32 local[3];
  (void)a;
  local[0] = 0x85498e7d;
  local[1] = 0x0510a95b;
  local[2] = 0x40464100;
  void* lay = ((ThCtor*)(void*)this)->FUN_00dd1ca0(local);
  ((ThInit*)(void*)lay)->FUN_00dd4260();
}
// @ 0x00ae9150
void Host::FUN_00ae9150(int a, int b) {
  void* lay = ((ThCtor*)(void*)this)->FUN_00dd1ca0b(a, b);
  ((ThLayout2*)(void*)lay)->FUN_00dd2780();
}
// @ 0x00ae9040
int Host::FUN_00ae9040(int a, int b, u32* out1, u32* out2) {
  FUN_00b3d2a0((u32)b);
  u32 m = FUN_00ba6dc0((u32)b);
  FUN_00feb9f0(m);
  if (FUN_00fee190(m) != 0) { *out1 = 0xc8fbf7d7; *out2 = 0x143c2229; return 1; }
  FUN_00b3d2a0((u32)a);
  int emp = FUN_00ba9370((u32)a);
  if (emp != 0 && FUN_0100e730(m, (u32)emp) != 0) { *out1 = 0xc8fbf7d7; *out2 = 0x57d35c53; return 1; }
  return 0;
}
// @ 0x00ae90d0
void Host::FUN_00ae90d0() {
  int* sys = (int*)FUN_00a206f0();
  u32 v = 0;
  if (sys != 0) v = (u32)((int(__thiscall*)(void*))(*(void***)sys)[0x20 / 4])(sys);
  sys = (int*)FUN_00a206f0();
  if (sys != 0) {
    ((void(__thiscall*)(void*, int))(*(void***)sys)[0x38 / 4])(sys, 0x3475365);
    ((void(__thiscall*)(void*, int, u32))(*(void***)sys)[0x40 / 4])(sys, 0x3475381, 0xef113cb4);
    ((void(__thiscall*)(void*, int, u32))(*(void***)sys)[0x40 / 4])(sys, 0x3475385, v);
    ((void(__thiscall*)(void*))(*(void***)sys)[0x58 / 4])(sys);
  }
}
// @ 0x00ae9390
int Host::FUN_00ae9390() {
  if (PI(this, 0x20) != 0) return 1;
  int g = FUN_0102bd0();
  if (g != 0 && PI(FUN_0102bd0(), 0x18) != 0) {
    FUN_0102bd0();
    if (FUN_01075500(0) != 0) return 1;
  }
  int q = FUN_010666a0();
  if (q != 0 && FUN_01068350((void*)FUN_010666a0()) != 0) return 1;
  return 0;
}
// @ 0x00ae9330
void Host::FUN_00ae9330() {
  int* o = (int*)PP(this, 0x20);
  if (o != 0) {
    PI(this, 0x20) = 0;
    ((void(__thiscall*)(void*, int))(*(void***)o)[1])(o, 0);
  }
  int g = FUN_00aed4d0();
  ((void(__thiscall*)(void*))(*(void***)g)[0])((void*)g);
  u32 local[3];
  local[0] = 0x85498e7d;
  local[1] = 0x40464100;
  local[2] = 0x510a95b;
  void* s = FUN_00dd1ca0(local);
  FUN_00dd4260(s, local);
}
// @ 0x00ae9170
void Host::FUN_00ae9170(int* stream) {
  int* p = (int*)((void*(__thiscall*)(void*))(*(void***)stream)[0x20 / 4])(stream);
  u32 v = 0x37abb4b;
  void* out = ((void*(__thiscall*)(void*))(*(void***)p)[0x18 / 4])(p);
  FUN_0093aa70(out, &v, 1, 0);
  struct SerBuf { u32 w[0xa16 / 4]; } ser;
  ((ThSerial*)&ser)->FUN_00692f90(this, (void*)0x01566cf8, 0x1a80d26);
  ((ThSerial*)&ser)->FUN_00692900(stream);
}
// @ 0x00ae93f0
int Host::FUN_00ae93f0(int a2, int a3, int a4, int a5, int a6) {
  int best = 0, bestv = -1;
  int* v = (int*)PI(this, 0x24);
  int n = (PI(this, 0x28) - PI(this, 0x24)) >> 2;
  int cur = 0;
  for (int i = 0; i < n; ++i) {
    cur = v[i];
    if (((PI(cur, 0x18) == a2 || a2 == -1 || PI(cur, 0x18) == -1) &&
         (PI(cur, 0x34) == a3 || a3 == -1) &&
         (PI(cur, 0x40) == a4 || a4 == 0) &&
         (PI(cur, 0x38) == a5 || a5 == -1) &&
         (PI(cur, 0x3c) == a6 || a6 == -1) &&
         bestv < PI(cur, 0x44))) {
      bestv = PI(cur, 0x44);
      best = cur;
    }
  }
  return best;
}
// @ 0x00ae8ea0
void Host::FUN_00ae8ea0() {
  PB(this, 0x7c) = 0;
  PB(this, 0x7d) = 0;
  {
    int* o = (int*)PP(this, 0x80);
    if (o != 0) {
      ((void(__thiscall*)(void*, int))(*(void***)o)[0xc / 4])(o, 0);
      int* p = (int*)PP(this, 0x80);
      if (p != 0) { PI(this, 0x80) = 0; ((void(__thiscall*)(void*, int))(*(void***)p)[1])(p, 0); }
    }
  }
  {
    int* o = (int*)PP(this, 0x84);
    if (o != 0) {
      ((void(__thiscall*)(void*, int))(*(void***)o)[0xc / 4])(o, 0);
      int* p = (int*)PP(this, 0x84);
      if (p != 0) { PI(this, 0x84) = 0; ((void(__thiscall*)(void*, int))(*(void***)p)[1])(p, 0); }
    }
  }
  int* sp = (int*)PP(this, 0x34);
  PB(this, 0x90) = 0;
  PB(this, 0x91) = 0;
  PU(this, 0x88) = 0;
  PU(this, 0x8c) = 0;
  if (sp != 0) {
    ((void(__thiscall*)(void*, int))(*(void***)sp)[0x16c / 4])(sp, 0);
    int* q = (int*)PP(this, 0x34);
    if (q != 0) {
      PI(this, 0x34) = 0;
      if (PI(q, 0x40) < 2) ((void(__thiscall*)(void*, int))(*(void***)q)[0x170 / 4])(q, (int)(PU(q, 4) >> 0x1f));
      else PU(q, 0x40) = PU(q, 0x40) - 1;
    }
  }
  {
    int* q = (int*)PP(this, 0x38);
    if (q != 0) {
      ((void(__thiscall*)(void*, int))(*(void***)q)[0x16c / 4])(q, 0);
      int* r = (int*)PP(this, 0x38);
      if (r != 0) {
        PI(this, 0x38) = 0;
        if (PI(r, 0x40) < 2) ((void(__thiscall*)(void*, int))(*(void***)r)[0x170 / 4])(r, (int)(PU(r, 4) >> 0x1f));
        else PU(r, 0x40) = PU(r, 0x40) - 1;
      }
    }
  }
  if (PI(this, 0x2c) != 0) { FUN_00a02b00(1); PU(this, 0x44) = 0; PU(this, 0x3c) = 0; }
  if (PI(this, 0x30) != 0) { FUN_00a02b00(1); PU(this, 0x48) = 0; PU(this, 0x40) = 0; }
}
// @ 0x00ae8390
void Host::FUN_00ae8390() {
  if (PB(this, 0x92) == 0) return;
  PB(this, 0x92) = 0;
  {
    void* a = *(void**)PP(this, 0x24);
    void* b = *(void**)PP(this, 0x28);
    ((void(__thiscall*)(void*, int))(*(void***)a)[0x3c / 4])(a, PI(this, 0x2c));
    ((void(__thiscall*)(void*, int))(*(void***)b)[0x3c / 4])(b, PI(this, 0x30));
    ((void(__thiscall*)(void*))(*(void***)a)[0x20 / 4])(a);
    ((void(__thiscall*)(void*))(*(void***)b)[0x20 / 4])(b);
  }
  {
    int* pv = (int*)PP(this, 0x34);
    int o = *pv;
    if (o != 0) {
      *pv = 0;
      if (PI(o, 0x40) < 2) ((void(__thiscall*)(void*, int))(*(void***)o)[0x170 / 4])((void*)o, (int)(PU(o, 4) >> 0x1f));
      else PU(o, 0x40) = PU(o, 0x40) - 1;
    }
  }
  {
    int* pv = (int*)PP(this, 0x38);
    int o = *pv;
    if (o != 0) {
      *pv = 0;
      if (PI(o, 0x40) < 2) ((void(__thiscall*)(void*, int))(*(void***)o)[0x170 / 4])((void*)o, (int)(PU(o, 4) >> 0x1f));
      else PU(o, 0x40) = PU(o, 0x40) - 1;
    }
  }
  if (PI(this, 0x2c) != 0) { int o = PI(this, 0x2c); PI(this, 0x2c) = 0; animRelease(o); }
  if (PI(this, 0x30) != 0) { int o = PI(this, 0x30); PI(this, 0x30) = 0; animRelease(o); }
  { int o = PI(this, 0x24); if (o) { PI(this, 0x24) = 0; ((void(__thiscall*)(void*, int))(*(void***)o)[1])((void*)o, 0); } }
  { int o = PI(this, 0x28); if (o) { PI(this, 0x28) = 0; ((void(__thiscall*)(void*, int))(*(void***)o)[1])((void*)o, 0); } }
  { int o = PI(this, 0x1c); modelsDtor(o); }
  { int o = PI(this, 0x20); modelsDtor(o); }
  if (PI(this, 0x1c) != 0) { int o = PI(this, 0x1c); PI(this, 0x1c) = 0; modelsRelease(o); }
  if (PI(this, 0x20) != 0) { int o = PI(this, 0x20); PI(this, 0x20) = 0; modelsRelease(o); }
  PU(this, 0x88) = 0;
  PU(this, 0x8c) = 0;
  { int o = PI(this, 0x80); if (o) { PI(this, 0x80) = 0; ((void(__thiscall*)(void*, int))(*(void***)o)[1])((void*)o, 0); } }
  { int o = PI(this, 0x84); if (o) { PI(this, 0x84) = 0; ((void(__thiscall*)(void*, int))(*(void***)o)[1])((void*)o, 0); } }
}
// @ 0x00ae8820
int Host::FUN_00ae8820(u32* a2, float a3, int a4, int a5, int a6) {
  int i = a6;
  int* pv = (int*)PP(this, 0x34 + i * 4);
  if (*pv != 0) {
    ((void(__thiscall*)(void*, int))(*(void***)*pv)[0x16c / 4])((void*)*pv, 0);
    int o = *pv;
    if (o != 0) {
      *pv = 0;
      if (PI(o, 0x40) < 2) ((void(__thiscall*)(void*, int))(*(void***)o)[0x170 / 4])((void*)o, (int)(PU(o, 4) >> 0x1f));
      else PU(o, 0x40) = PU(o, 0x40) - 1;
    }
  }
  void* g = FUN_0080db70();
  u32 u = ((u32(__thiscall*)(void*, u32, u32, int))(*(void***)g)[0xc / 4])(g, a2[0], a2[2], 0);
  FUN_00478db0(u);
  int o = *pv;
  PI(o, 0x4c) = a4;
  PI(o, 0x50) = a5;
  *(void**)PS(o, 0x54) = a2;
  PU(o, 4) = PU(o, 4) & 0xfffff7ff;
  {
    int c = PI(this, 0x2c + i * 4);
    if (c != 0) {
      int q = **(int**)PS(c, 0x17c);
      float v = a3;
      if (PF(q, 0x368) <= PF(q, 0x36c)) v = a3;
      v = v * 0.5f;
      if (v >= 1.0f) v = 1.0f;
      int o2 = *pv;
      u16* t = (u16*)((char*)o2 + 10);
      *t = *t + 1;
      PF(o2, 0x18) = v;
    }
  }
  void* lm = SP_LightingManager();
  int* li = (int*)((void*(__thiscall*)(void*, int))(*(void***)lm)[0x1c / 4])(lm, i + 0x4a4de35);
  if (li != 0) ((void(__thiscall*)(void*, float))(*(void***)li)[0x30 / 4])(li, a3);
  return 0;
}
// @ 0x00ae8d00
void Host::FUN_00ae8d00(int a2, int a3, float f4, float f5, int* idx) {
  int i = (int)idx;
  PB(this, 0x7c + i) = 1;
  {
    void* a = *(void**)PP(this, 0x24 + i * 4);
    ((void(__thiscall*)(void*, int))(*(void***)a)[0x3c / 4])(a, PI(this, 0x2c + i * 4));
  }
  if (idx != 0) {
    int* p = idx;
    u32 r = FUN_0080d610();
    ((void(__thiscall*)(void*, u32))(*(void***)p)[0x88 / 4])(p, r);
    float* fr = (float*)((void*(__thiscall*)(void*))(*(void***)p)[0x38 / 4])(p);
    f4 = fr[2] - fr[0];
    int q = ((int(__thiscall*)(void*))(*(void***)p)[0x38 / 4])(p);
    f5 = f5 / (PF(q, 0xc) - PF(q, 4));
    FUN_0080d5f0((u32)f5);
    FUN_007c4b50(f5);
  }
  {
    void* a = *(void**)PP(this, 0x24 + i * 4);
    void* creature = ((void*(__thiscall*)(void*, float, int, void*, void*))(*(void***)a)[0x30 / 4])(
        a, f4, 2, (void*)0x0167ac44, (void*)0x01566be0);
    int old = PI(this, 0x2c + i * 4);
    if (creature != (void*)old) {
      if (creature != 0) FUN_00a02c30();
      PI(this, 0x2c + i * 4) = (int)creature;
      if (old != 0) animRelease(old);
    }
  }
  {
    void* a = *(void**)PP(this, 0x24 + i * 4);
    ((void(__thiscall*)(void*, int, int, int))(*(void***)a)[0x40 / 4])(a, PI(this, 0x2c + i * 4), 2, 1);
  }
  FUN_00a04c80(6);
  {
    int c = PI(this, 0x2c + i * 4);
    PB(**(int**)PS(c, 0x17c), 0x270) = 0;
    *(void**)PS(c, 0x170) = (void*)0;
    PI(c, 0x74) = 1;
    PI(c, 0x78) = 0;
    PI(c, 0x7c) = 0;
    PF(c, 0x80) = 1.0f;
    PB(c, 0x84) = 1;
    ((void(__thiscall*)(void*, int, int))(*(void***)c)[4 / 4])((void*)c, 0x2481de5, 0);
  }
  FUN_00ae8970(i);
}
// @ 0x00ae8970
void Host::FUN_00ae8970(int idx) {
  int i = idx;
  bool space = (PU(this, 0x94) == 0x2ccd1d2);

  int c0 = **(int**)PS(PI(this, 0x2c + i * 4), 0x17c);
  float A = PF(c0, 0x368);
  float B = PF(c0, 0x36c);
  float lo = (A <= 1.2f) ? 0.8f : A;
  float hi = (lo <= B) ? B : lo;
  float scale = hi * 3.0f;
  float lim = (B * 0.7f <= 0.8f) ? 0.8f : B * 0.7f;

  FUN_0080d5f0(0x41500000);
  FUN_007c53d0(0x41500000);
  int stride = i * 0xc;
  PI(this, 100 + stride) = 0;
  PI(this, 0x68 + stride) = 0;
  float* pf = (float*)PS(this, (i * 3 + 0x1b) * 4);
  float* q = (float*)PS(this, (i * 3 + 0x15) * 4);
  if (space) {
    *pf = B * 0.5f;
    PF(this, 0x4c + stride) = scale;
    PF(this, 0x50 + stride) = -scale;
    *q = scale;
  } else {
    PF(this, 0x4c + stride) = -0.1f;
    *pf = lim;
    PF(this, 0x50 + stride) = -scale;
    *q = lim;
    if (i == 1) PU(this, 0x58) = PU(this, 0x58) ^ 0x80000000;
  }
  if (!space) {
    float dir[3] = { 0.0f, 0.0f, 0.0f };
    float out[3] = { 0.0f, 0.0f, 0.0f };
    int hit = FUN_009b2340(out, 1, **(u32**)PS(PI(this, 0x2c + i * 4), 0x17c), dir, 0, 0);
    if (hit != 0) {
      int g = (int)out[0] * 700 + PI(**(int**)PS(PI(this, 0x2c + i * 4), 0x17c), 0x2e4);
      if (g != 0) {
        float h = PF(g, 0x18);
        *pf = h * 0.8f;
        float v = (h <= 2.0f) ? 2.0f : h;
        *q = v * 0.8f;
      }
    }
  }

  float hdr[4];
  hdr[0] = 0.0f; hdr[1] = 0.0f; hdr[2] = 0.0f; hdr[3] = 1.0f;
  char mat[0x24];
  FUN_0041cb40(mat, (const void*)0x0167ac88);
  int a = FUN_00b3d490();
  float* base = (float*)PS(a, 0x4c + stride);
  int b = FUN_00b3d490();
  float d[3];
  d[0] = PF(b, 100 + stride) - base[0];
  d[1] = PF(b, 0x68 + stride) - base[1];
  d[2] = PF(b, 0x6c + stride) - base[2];
  float* m = (float*)FUN_0069b440(d, d, (const void*)0x01566bd4);
  for (int k = 0; k < 9; ++k) ((float*)mat)[k] = m[k];
  int b2 = FUN_00b3d490();
  hdr[0] = PF(b2, 0x4c + stride);
  hdr[1] = PF(b2, 0x50 + stride);
  hdr[2] = PF(b2, 0x54 + stride);
  int b3 = FUN_00b3d490();
  (void)b3;
}
// @ 0x00ae8510
void Host::FUN_00ae8510(int dtMs) {
  float dt = (float)dtMs * 0.001f;
  if (dt <= 0.2f) dt = 0.2f;
  for (int i = 0; i < 2; ++i) {
    if (PB(this, 0x7c + i) != 0) {
      void* anim = *(void**)PP(this, 0x24 + i * 4);
      u32 v = FUN_0080d610();
      ((void(__thiscall*)(void*, float, u32))(*(void***)anim)[0x24 / 4])(anim, dt, v);
    }
    int* slot = (int*)PP(this, 0x80 + i * 4);
    float* fade = (float*)PS(this, 0x88 + i * 4);
    if (*slot != 0) {
      if (PB(this, 0x7c + i) != 0) {
        if (*fade > 0.0f) {
          ((void(__thiscall*)(void*, int, float*, int))(*(void***)*slot)[0x44 / 4])((void*)*slot, 4, fade, 1);
          *fade = *fade - dt * 0.33333334f;
        }
        if (*fade == 0.0f && PB(this, 0x90 + i) == 0) {
          void* q = FUN_00401010();
          int c = PI(this, 0x2c + i * 4);
          int p = **(int**)PS(c, 0x17c);
          float tmp[3] = { PF(p, 0x318), PF(p, 0x31c), PF(p, 0x320) };
          if (((int(__thiscall*)(void*, float*, int))(*(void***)q)[0x1c / 4])(q, tmp, 0) != 0) *fade = 1.0f;
        }
        if (*fade <= 0.0f && *fade != 0.0f) {
          ((void(__thiscall*)(void*, int))(*(void***)*slot)[0xc / 4])((void*)*slot, 1);
          int o = *slot;
          if (o != 0) { *slot = 0; ((void(__thiscall*)(void*, int))(*(void***)o)[1])((void*)o, 0); }
          *fade = 0.0f;
        }
      }
    } else if (PB(this, 0x7c + i) != 0) {
      if (PU(this, 0x94) != 0x2ccd1d2 && PB(this, 0x90 + i) == 0) {
        int skip = 0;
        void* q = FUN_00401010();
        int c = PI(this, 0x2c + i * 4);
        int p = **(int**)PS(c, 0x17c);
        float tmp[3] = { PF(p, 0x318), PF(p, 0x31c), PF(p, 0x320) };
        if (((int(__thiscall*)(void*, float*, int))(*(void***)q)[0x1c / 4])(q, tmp, 0) != 0) skip = 1;
        if (!skip) {
          void* r = FUN_0080db90();
          int o = *slot;
          if (o != 0) { *slot = 0; ((void(__thiscall*)(void*, int))(*(void***)o)[1])((void*)o, 0); }
          if (((int(__thiscall*)(void*, int, int, int*))(*(void***)r)[8 / 4])(r, 0x78e87b80, 0, slot) != 0) {
            ((void(__thiscall*)(void*, int))(*(void***)*slot)[8 / 4])((void*)*slot, 1);
          }
        }
        if (i == 1) PB(this, 0x91) = 0;
      }
    }
    if (PI(this, 0x1c + i * 4) != 0) {
      char buf[0x4c];
      void* r = FUN_0080db90();
      ((void(__thiscall*)(void*, float, float, void*))(*(void***)r)[0x3c / 4])(r, dt, dt, buf);
    }
  }
}

