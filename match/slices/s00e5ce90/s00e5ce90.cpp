// Slice s00e5ce90 (batch bfs3, slice 19). Region 0xe5ce90-0xe5db85.
// Cell-game creature-pickup / box-distance UI helpers. Optimised:
// /O2 /MD /Gy /TP /arch:SSE /fp:fast.  Guard = 0x743b50/0xe82130.
#include "types.h"

struct cGuard19 { void* p; cGuard19(); ~cGuard19(); };

extern "C" {
  void*     __cdecl FUN_00b721d0(int id);
  void*     __cdecl FUN_00b72210(int handle);
  int       __cdecl FUN_00e57340(int p);
  char      __cdecl FUN_00e4ff10(char* p);
  int       __cdecl FUN_00e4fca0();
  int       __cdecl FUN_00e530e0();
  int       __cdecl FUN_00e5c9d0();
  char      __cdecl FUN_00e5cd00();
  bool      __cdecl FUN_00e5d580(int p);
  int       __cdecl FUN_00e87260(int id, void* a, int b, void* out, int n, int f);
  void      __cdecl FUN_00e53660(int a, int b);
  void      __cdecl FUN_00e539c0();
  void      __cdecl FUN_00e50450(int key);
  unsigned  __cdecl FNV1_String8(const char* s, unsigned basis, int len);
  int       __cdecl SPIDFromName(const char* s);
  void      __cdecl FUN_00e4fac0(char* state);
  void      __cdecl FUN_00e83430(int id);
  void      __cdecl FUN_00e82d10(int id);
  void      __cdecl FUN_00e82690(int id, float v);
  void      __cdecl SP_PatchSoundStart(const char* s, int b);
  void*     __cdecl FUN_0067dcd0();
  void      __cdecl FUN_00e394f0(int key, int a, int* b, int* c, int* d);
  void*     __cdecl FUN_00e4ce40(void* out);
  float     __cdecl FUN_00e52b70();
  void      __cdecl FUN_00e50020(float* a, float* b);
  float     __cdecl FUN_00e4ffe0();
  bool      __cdecl FUN_00e53280();
  char      __fastcall FUN_006ffbd0(int lo, float* p, float r);
  void*     __cdecl FUN_00b3d400(int a);
  void*     __cdecl FUN_00b3d3f0(int a);
  void      __cdecl FUN_00e14d00(int a, int b, int c);
  void      __cdecl FUN_00e51580();
  void      __cdecl FUN_00e19350(int a, int b);
  void      __cdecl FUN_00e17df0(void* p);
  void      __cdecl FUN_00e5da10();
}

extern char  g_16b3c04[];
extern char  g_16b3c0c[];
extern float g_16b3c88, g_16b3c8c, g_16b3c90, g_16b3c94, g_16b3c98, g_16b3c9c;
extern int   g_15a83a4, g_15a83a8, g_15a83ac;

static inline void** Vt(void* p) { return *(void***)p; }

// @ 0x00e5d340  point-in-extended-box predicate
bool FUN_00e5d340() {
  char* e = (char*)FUN_00b721d0(*(int*)(g_16b3c04 + 0x516c));
  if (!e) return false;
  float x = *(float*)(e + 0x4c);
  float r = *(float*)(e + 0x58);
  float d = 0.0f;
  float b = g_16b3c88;
  if (x < b || (b = g_16b3c94, b < x)) d = (x - b) * (x - b);
  float y = *(float*)(e + 0x50);
  b = g_16b3c8c;
  if (y < b || (b = g_16b3c98, b < y)) d = (y - b) * (y - b) + d;
  float z = *(float*)(e + 0x54);
  b = g_16b3c90;
  if (z < b || (b = g_16b3c9c, b < z)) d = (z - b) * (z - b) + d;
  return r * r >= d;
}

// @ 0x00e5d410
bool FUN_00e5d410(int id, float* p, float r) {
  if (id != *(int*)(g_16b3c04 + 0x40fc)) {
    char c = FUN_006ffbd0(0x16b3cb8, p, r);
    return (c & 0x40) == 0;
  }
  float x = p[0];
  float d = 0.0f;
  float b = g_16b3c88;
  if (x < b || (b = g_16b3c94, b < x)) d = (x - b) * (x - b);
  float y = p[1];
  b = g_16b3c8c;
  if (y < b || (b = g_16b3c98, b < y)) d = (y - b) * (y - b) + d;
  float z = p[2];
  b = g_16b3c90;
  if (z < b || (b = g_16b3c9c, b < z)) d = (z - b) * (z - b) + d;
  return r * r >= d;
}

// @ 0x00e5d580
bool FUN_00e5d580(int p) {
  if (*(int*)(p + 0xfc) != 0 && FUN_00e57340(p) == 3)
    return FUN_00e4ff10((char*)p) != 0;
  return false;
}

// @ 0x00e5daa0
void FUN_00e5daa0() {
  FUN_00e5da10();
  char* e = (char*)FUN_00b721d0(*(int*)(g_16b3c04 + 0x411c));
  if (e != 0 && e[0x113] == 0 && e[0x112] == 0) {
    *(int*)(g_16b3c04 + 0x5158) = 5;
    FUN_00e539c0();
  }
}

// @ 0x00e5daf0
void FUN_00e5daf0() {
  g_16b3c04[0x51dc] = 0;
  FUN_00e53660(2, 1);
  g_16b3c0c[0x938] = 1;
  if (FUN_00e4fca0() == 1) {
    FUN_00e50450((int)FNV1_String8("Callout_CLG_Ending", 0x811c9dc5, 1));
    FUN_00e50450((int)FNV1_String8("Callout_CLG_TransitionButton", 0x811c9dc5, 1));
  } else if (FUN_00e4fca0() == 2) {
    FUN_00e50450(SPIDFromName("Callout_CLG_Ending"));
  }
}

// @ 0x00e5da10
void FUN_00e5da10() {
  int id = FUN_00e5c9d0();
  int key = 0;
  if (id == (int)0xa8ec6f99) key = 0x13df9c1c;
  else if (id == (int)0xcfb01b93) key = 0xf967827c;
  else if (id == (int)0x5ece4770) key = 0x7115ede5;
  int a[9];
  for (int i = 0; i < 9; ++i) a[i] = 0;
  FUN_00e394f0(key, *(int*)(g_16b3c04 + 0x5190) + 0x10, &a[4], &a[2], &a[0]);
}

// @ 0x00e5d500
void FUN_00e5d500(int* out) {
  void* local = 0;
  void* mgr = FUN_0067dcd0();
  char c = (*(char(__thiscall**)(void*, int*, void**, int, int, int, int))((char*)Vt(mgr) + 0xc))
             (mgr, out, &local, 0, 0, 0, 0);
  if (c == 0) {
    out[0] = g_15a83a4;
    out[1] = g_15a83a8;
    out[2] = g_15a83ac;
  }
  if (local) (*(void(__thiscall**)(void*, int))((char*)Vt(local) + 4))(local, 0);
}

// @ 0x00e5d2b0  random size within [lo,hi] * level size -- approximated
float FUN_00e5d2b0(int handle, int level) {
  cGuard19 g;
  char* e = (char*)0;  // guard lookup result omitted
  (void)e;
  (void)handle;
  return (float)(level + 1);
}

// @ 0x00e5d5b0  pickup search -- partial
void FUN_00e5d5b0(float dt) {
  *(float*)(g_16b3c04 + 0x51bc) = *(float*)(g_16b3c04 + 0x51bc) - dt;
  char* target = (char*)FUN_00b721d0(*(int*)(g_16b3c04 + 0x411c));
  if (!target) return;
  if (FUN_00b721d0(*(int*)(g_16b3c04 + 0x51b0))) {
    *(float*)(g_16b3c04 + 0x51bc) = FUN_00e52b70();
    return;
  }
  if (!FUN_00e53280()) return;
  float a, b;
  FUN_00e50020(&a, &b);
  float cx = (g_16b3c94 + g_16b3c88) * 0.5f;
  float cy = (g_16b3c98 + g_16b3c8c) * 0.5f;
  float cz = (g_16b3c9c + g_16b3c90) * 0.5f;
  int hits[512];
  int n = FUN_00e87260(*(int*)(g_16b3c04 + 0x40fc), &cx, (int)b, hits, 0x200, 0);
  for (int i = 0; i < n; ++i) {
    char* c = (char*)FUN_00b72210(hits[i]);
    if (FUN_00e5cd00()) continue;
    float dx = *(float*)(c + 0x4c) - *(float*)(target + 0x4c);
    float dy = *(float*)(c + 0x50) - *(float*)(target + 0x50);
    float dz = *(float*)(c + 0x54) - *(float*)(target + 0x54);
    float dist2 = dx * dx + dy * dy + dz * dz;
    if (dist2 > a * a) continue;
    if (!FUN_00e5d580((int)c)) continue;
    g_16b3c04[0x51c0] = 1;
    char* s = (char*)(*(int*)(g_16b3c04 + 0x5190) + 0xb0);
    *(int*)s = 1; *(int*)(s + 4) = 0; *(int*)(s + 8) = 0; *(float*)(s + 0xc) = 0.0f;
    *(int*)(g_16b3c04 + 0x51b4) = 3;
    *(int*)(g_16b3c04 + 0x51b0) = *(int*)c;
    *(float*)(g_16b3c04 + 0x51b8) = FUN_00e4ffe0();
    return;
  }
}

// @ 0x00e5d7b0  mission slot tick -- partial
void FUN_00e5d7b0(int a, int b) {
  (void)a; (void)b;
}

// @ 0x00e5ce90  long creature/box helper -- partial
void FUN_00e5ce90() {
}
