// Slice s00e4f860 (batch bfs3, slice 16). Region 0xe4f860-0xe507ff.
// Cell-game collectable / mission-card UI helpers in SP::.  Optimised:
// /O2 /MD /Gy /TP /arch:SSE /fp:fast.  The recurring `lea ecx,[esp+N]; call
// 0x743b50; ...; call 0xe82130` is a small scope guard (modelled by cGuard16).
// 0xe4cc40 (thunk_FUN_00e823a0) looks an object up from a handle.
#include "types.h"

struct cGuard16 { void* p; cGuard16(); ~cGuard16(); };

extern "C" {
  void*     __cdecl FUN_00e4ce40(void* out);
  void*     __cdecl FUN_00e823a0(int handle, void* out);   // thunk @0xe4cc40
  unsigned  __cdecl FNV1_String8(const char* s, unsigned basis, int len);   // 0x00932e80 (equiv t2)
  int       __cdecl FUN_00e4cce0(int id);
  void      __cdecl FUN_00e83430(int id);
  void      __cdecl FUN_00c2fd20(unsigned key);
  void      __cdecl FUN_007c4180(void*, void*);
  void      __cdecl FUN_00e82d50(void*, void*);
  void      __cdecl FUN_00809db0(void*, void*);
  void*     __cdecl SP_ConfigManager();
  void*     __cdecl SP_App();
  void*     __cdecl SP_MessageServer(); // 0x0067dcc0
  void*     __cdecl SP_CheatManager();
  void*     __cdecl FUN_0067dd20();
  void*     __cdecl FUN_0067de90(int);
  void      __cdecl FUN_007ebce0(void*);
  void      __cdecl SPUI_GetMainWindowArea(void*);
  float     __cdecl FUN_01041cd0(float, float, float);
  void      __cdecl FUN_00e663b0(int, int);
  void*     __cdecl FUN_00e11e073e(void*, int, unsigned);
  void*     __cdecl FUN_00b3d400(void*);
  void      __cdecl FUN_00e18200(void*, int, int, int);
  void      __cdecl FUN_00b3d4d0(int);
  void      __cdecl FUN_00ad7e40(void*);
  unsigned  __cdecl FUN_00593980(void* mgr, ...);
  void      __cdecl FUN_00596da0(unsigned, int);
  void      __cdecl FUN_00596e10(unsigned);
  void      __cdecl FUN_00597a20(void*);
  void      __cdecl FUN_00599440(int, int, void*);
  void      __cdecl FUN_00598db0(int, int, int, int, int, int, int, int, int);
  void      __cdecl FUN_005942e0(void*);
}

extern char g_16b3c0c[];
extern char g_16b3c04[];
extern void* g_150d6d8;

static inline void** Vt(void* p) { return *(void***)p; }

// ---------------------------------------------------------------- guard getters
// @ 0x00e4fca0
int FUN_00e4fca0() {
  cGuard16 g;
  char* r = (char*)FUN_00e4ce40(&g);
  return *(int*)(r + 0xdc);
}

// @ 0x00e4ffe0
float FUN_00e4ffe0() {
  cGuard16 g;
  char* r = (char*)FUN_00e4ce40(&g);
  return *(float*)(r + 0xec);
}

// @ 0x00e50060
float FUN_00e50060() {
  cGuard16 g;
  char* r = (char*)FUN_00e4ce40(&g);
  return *(float*)(r + 0xf0);
}

// @ 0x00e50020
void FUN_00e50020(float* a, float* b) {
  cGuard16 g;
  char* r = (char*)FUN_00e4ce40(&g);
  *a = *(float*)(r + 0xf4);
  *b = *(float*)(r + 0xf8);
}

// @ 0x00e4ff10
char FUN_00e4ff10(char* p) {
  cGuard16 g;
  char* r = (char*)FUN_00e823a0(*(int*)(p + 0x108), &g);
  return *(char*)(r + 0x318);
}

// @ 0x00e503a0
float FUN_00e503a0(int which) {
  cGuard16 g;
  char* r = (char*)FUN_00e4ce40(&g);
  if (which == 2) return *(float*)(r + 0x104);
  if (which == 4) return *(float*)(r + 0x108);
  return 10.0f;
}

// @ 0x00e507d0
unsigned FUN_00e507d0(float a, float b) {
  float f = (a / b) * 2.0f;
  int i = (int)f;
  if (f < (float)i) i--;
  return (unsigned)i & 1;
}

// @ 0x00e4fde0
unsigned FUN_00e4fde0(int kind) {
  switch (kind) {
    case 1: return 0x77d5cbac;
    case 4: return FNV1_String8("Cell_EatAnimal", 0x811c9dc5, 1);
    case 5: return FNV1_String8("Cell_EatOmnivore", 0x811c9dc5, 1);
    default: return FNV1_String8("Cell_EatPlant", 0x811c9dc5, 1);
  }
}

// @ 0x00e4ff50
char FUN_00e4ff50(char* p) {
  char c = 0;
  if (*(int*)(p + 0x108) == FUN_00e4cce0(0x14)) {
    if (*(char*)(p + 0x390) == 0) c = 1;
    if (*(char*)(p + 0x391) == 0) c++;
  } else if (*(int*)(p + 0x108) == FUN_00e4cce0(0x18)) {
    if (*(char*)(p + 0x392) == 0) c = 1;
    if (*(char*)(p + 0x393) == 0) c++;
    if (*(char*)(p + 0x394) == 0) c++;
    if (*(char*)(p + 0x395) == 0) c++;
    if (*(char*)(p + 0x396) == 0) c++;
    if (*(char*)(p + 0x397) == 0) c++;
  } else {
    return 0;
  }
  return c;
}

// @ 0x00e505f0
bool FUN_00e505f0(int* arr, int n, int key) {
  for (int i = 0; i < n; ++i)
    if (arr[i] == key) return true;
  return false;
}

// @ 0x00e50540
bool FUN_00e50540(char* p) {
  unsigned a = FNV1_String8("cell_EggkidSmall", 0x811c9dc5, 1);
  if (*(int*)(*(int*)(p + 0x108)) == (int)a) return true;
  unsigned b = FNV1_String8("cell_Eggkid", 0x811c9dc5, 1);
  return *(int*)(*(int*)(p + 0x108)) == (int)b;
}

// @ 0x00e50730
bool FUN_00e50730() {
  void* cm = SP_ConfigManager();
  int r = (*(int(__thiscall**)(void*, int))((char*)Vt(cm) + 0x30))(cm, 0x679b833);
  return r != 0;
}

// ---------------------------------------------------------------- loops / tables
struct cState16 { int f90; int level(); };

// @ 0x00e4fd80  (this in ECX)
int cState16::level() {
  switch (f90) {
    default: return 5;
    case 1:  return 6;
  }
}

// @ 0x00e4fbb0  (table pointer arrives in EAX)
void FUN_00e4fbb0(int* table) {
  int* p = (int*)0x1483ea0;
  do {
    if (table[p[-2]] == 2) table[p[-2]] = 1;
    if (table[p[0]] == 2) table[p[0]] = 1;
    if (table[p[2]] == 2) table[p[2]] = 1;
    if (table[p[4]] == 2) table[p[4]] = 1;
    if (table[p[6]] == 2) table[p[6]] = 1;
    if (table[p[8]] == 2) table[p[8]] = 1;
    p += 0xc;
  } while ((int)p < 0x1483f00);
}

// @ 0x00e4fe50
void FUN_00e4fe50() {
  char* p = (char*)0x16b3de8;
  int i = 0;
  do {
    *(int*)(p + 0x90) = i;
    FUN_00c2fd20(FUN_00e4fde0(i));
    p += 0x98;
    ++i;
  } while ((int)p < 0x16b4178);
}

// @ 0x00e4fcd0
void FUN_00e4fcd0(char* p) {
  FUN_00e11e073e(p, 0, 0x34);
  *(int*)(p + 0x2c) = 1;
  *(int*)(p + 0x24) = 1;
  *(int*)(p + 0xc) = 1;
  *(int*)(p + 8) = 1;
  int* q = (int*)0x1483e9c;
  do {
    if (*(int*)(p + q[-1] * 4) == 1) FUN_00e83430(q[0]);
    q += 2;
  } while ((int)q < 0x1483efc);
}

// @ 0x00e50750
void FUN_00e50750(int a, float* outx, float* outy) {
  float local[1];
  void* app = SP_App();
  (*(void(__thiscall**)(void*, float*, int))((char*)Vt(app) + 0x58))(app, local, a);
  FUN_007c4180(local, (void*)a);
  float area[4];
  SPUI_GetMainWindowArea(area);
  *outx = ((local[0] + 1.0f) * area[2]) * 0.5f;
  *outy = ((1.0f - local[1]) * area[3]) * 0.5f;
}

// @ 0x00e50590
void FUN_00e50590(int* list1, int* count, int* list2, int n2) {
  for (int i = 0; i < *count; ++i) {
    int j = 0;
    for (; j < n2; ++j)
      if (list1[i] == list2[j]) break;
    if (j == n2) {
      list1[i] = list1[*count - 1];
      --*count;
      --i;
    }
  }
}

// @ 0x00e50620  remove first entry matching key from 0xc-stride table (+0x8c,+0x14c)
bool FUN_00e50620(char* self, int key, int* out) {
  int n = *(int*)(self + 0x14c);
  for (int i = 0; i < n; ++i) {
    char* e = self + 0x8c + i * 0xc;
    if (*(int*)e == key) {
      if (out) *out = *(int*)(e + 8);
      --*(int*)(self + 0x14c);
      char* last = self + 0x8c + *(int*)(self + 0x14c) * 0xc;
      *(int*)e = *(int*)last;
      *(int*)(e + 4) = *(int*)(last + 4);
      *(int*)(e + 8) = *(int*)(last + 8);
      return true;
    }
  }
  return false;
}

// ---------------------------------------------------------------- large / partial
// @ 0x00e4f860  collectable visibility refresh
void FUN_00e4f860(char* obj, int arg2) {
  cGuard16 g;
  char* list = (char*)FUN_00e823a0(*(int*)(obj + 0x14), &g);
  int count = *(int*)(list + 0x18);
  if (count > 0) {
    int* out = (int*)(obj + 0x2c);
    for (int i = 0, off = 0; i < count; ++i, off += 0x28) {
      char* e = *(char**)(list + 0x14) + off;
      if (*(int*)(e + 4) != 1) continue;
      int a = *(int*)(e + 0x18);
      int b = *(int*)(e + 0x14);
      int* v = (int*)out[i];
      if (b < 0) {
        if (a >= 0 && a < arg2)
          (*(void(__thiscall**)(int*, int))((char*)Vt(v) + 0xc))(v, 0);
        else if ((*(bool(__thiscall**)(int*))((char*)Vt(v) + 0x10))(v))
          (*(void(__thiscall**)(int*, int))((char*)Vt(v) + 8))(v, 0);
      } else if (a < 0) {
        if (b > arg2) {
          if (!(*(bool(__thiscall**)(int*))((char*)Vt(v) + 0x10))(v))
            (*(void(__thiscall**)(int*, int))((char*)Vt(v) + 0xc))(v, 0);
        }
      } else if (b < arg2 || arg2 <= a) {
        (*(void(__thiscall**)(int*, int))((char*)Vt(v) + 0xc))(v, 0);
      } else if (!(*(bool(__thiscall**)(int*))((char*)Vt(v) + 0x10))(v)) {
        (*(void(__thiscall**)(int*, int))((char*)Vt(v) + 8))(v, 0);
      }
    }
  }
}

// @ 0x00e4fc20  recursively grant a collectable index
void FUN_00e4fc20(int idx, int handle) {
  if (!handle) return;
  cGuard16 g;
  char* list = (char*)FUN_00e823a0(handle, &g);
  int count = *(int*)(list + 4);
  for (int i = 0, off = 0; i < count; ++i, off += 0x1c) {
    char* e = *(char**)list + off;
    if (*(int*)e == 1) FUN_00e663b0(idx, *(int*)(e + 4));
    else if (*(int*)e == 2) FUN_00e4fc20(idx, *(int*)(e + 8));
  }
}

// @ 0x00e50680  recursively set a byte flag
void FUN_00e50680(int handle, int idx) {
  cGuard16 g;
  char* list = (char*)FUN_00e823a0(handle, &g);
  int count = *(int*)(list + 4);
  for (int i = 0, off = 0; i < count; ++i, off += 0x1c) {
    char* e = *(char**)list + off;
    if (*(int*)e == 1) {
      cGuard16 g2;
      char* o = (char*)FUN_00e823a0(*(int*)(e + 4), &g2);
      if (*(int*)(o + 0xb8) > 0) *(char*)(*(int*)(o + 0xb8) + idx) = 1;
    } else if (*(int*)e == 2) {
      FUN_00e50680(*(int*)(e + 8), idx);
    }
  }
}

// @ 0x00e4f9d0  select a level float by (state,b)
float FUN_00e4f9d0(int handle) {
  cGuard16 g;
  char* r = (char*)FUN_00e823a0(handle, &g);
  int hi = *(int*)(r + 0xbc);
  int lo = *(int*)(r + 0xb4);
  char* o = (char*)FUN_00e4ce40(&g);
  int off;
  switch (hi) {
    case 0:
      switch (lo) {
        case 1:  off = 0x58; break;
        case 2: case 6: off = 0x5c; break;
        case 3: case 5: case 7: off = 0x60; break;
        case 4:  off = 100; break;
        default: return 1.0f;
      }
      break;
    case 1: off = 0x60; break;
    case 2: off = 100; break;
    case 3: off = 0x5c; break;
    case 4: off = 0x58; break;
    default: return 1.0f;
  }
  return *(float*)(o + off);
}

// @ 0x00e4fac0  configure collectable items for the current state
void FUN_00e4fac0(char* self, int* state) {
  FUN_00597a20(self);
  FUN_00599440(0, 0, g_150d6d8);
  *(char*)(self + 0xc) = 0;
  for (int* p = (int*)0x1483e9c; (int)p < 0x1483efc; p += 2) {
    int idx = p[-1];
    FUN_00598db0(p[0], 0, 0, 0, 0, 0, 0, 0, 0);
    int v = state[idx];
    if (v == 1) { unsigned k = FUN_00593980(g_150d6d8, p[0], 0); FUN_00596da0(k, 0); }
    else if (v == 0) { unsigned k = FUN_00593980(g_150d6d8, p[0]); FUN_00596e10(k); }
  }
  FUN_005942e0(self);
  for (int* p = (int*)0x1483e9c; (int)p < 0x1483efc; p += 2) {
    if (state[p[-1]] == 2) { unsigned k = FUN_00593980(g_150d6d8, p[0], 0); FUN_00596da0(k, 0); }
  }
}

// @ 0x00e4fe90  mission-card show/hide
void FUN_00e4fe90(int idx, int mode) {
  char* p = (char*)0x16b3de8 + idx * 0x98;
  if (mode == 1 || (mode == 2 && idx != 3)) {
    void* panel = FUN_00b3d400(p);
    if (!(*(bool(__thiscall**)(void*, char*))((char*)Vt(panel) + 0x0))(panel, p))
      FUN_00e18200(p, 1, 1, idx == 1);
  } else {
    void* panel = FUN_00b3d400(p);
    if ((*(bool(__thiscall**)(void*, char*))((char*)Vt(panel) + 0x0))(panel, p))
      (*(void(__thiscall**)(void*, char*))((char*)Vt(panel) + 4))(panel, p);
  }
}

// @ 0x00e500a0  UI notification handler (messages)
int FUN_00e500a0(char* self, int mode) {
  switch (mode) {
    case 0x5107b17:
      if (*(int*)(self + 8) == 0) {
        if (*(int*)(self + 4) == 0) { FUN_00809db0((void*)0x15a8400, (void*)0x15a83dc); return 0; }
        if (*(int*)(self + 4) == 1) { FUN_00809db0((void*)0x15a840c, (void*)0x15a83dc); return 0; }
      } else {
        g_16b3c0c[0x936] = 1;
        if (*(int*)(self + 4) == 0) {
          void* cm = SP_CheatManager();
          (*(void(__thiscall**)(void*, const char*))((char*)Vt(cm) + 0x20))(cm, "quit");
        } else if (*(int*)(self + 4) == 1) {
          void* cm = FUN_0067dd20();
          (*(void(__thiscall**)(void*))((char*)Vt(cm) + 0x40))(cm);
        }
      }
      break;
    case 0x5107b1a:
      {
        void* ms = SP_MessageServer();
        (*(void(__thiscall**)(void*, int, int, int))((char*)Vt(ms) + 0x14))(ms, 0x1cd20f0, 0, 0);
        g_16b3c0c[0x936] = 1;
        if (*(int*)(self + 4) == 0) *(int*)(g_16b3c04 + 0x51e0) = 2;
        else if (*(int*)(self + 4) == 1) *(int*)(g_16b3c04 + 0x51e0) = 1;
      }
      break;
  }
  return 0;
}

// @ 0x00e501a0
void SP_sOnQuitDesktopButtonClick() {
  void* t = FUN_0067de90(-1);
  FUN_007ebce0(t);
  if (g_16b3c04[0x51da] == 0) { FUN_00809db0((void*)0x15a83e8, (void*)0x15a83d0); return; }
  void* cm = SP_CheatManager();
  (*(void(__thiscall**)(void*, const char*))((char*)Vt(cm) + 0x20))(cm, "quit");
}

// @ 0x00e501f0
void FUN_00e501f0() {
  if (g_16b3c04[0x51da] == 0) { FUN_00809db0((void*)0x15a83f4, (void*)0x15a83d0); return; }
  void* cm = FUN_0067dd20();
  (*(void(__thiscall**)(void*))((char*)Vt(cm) + 0x40))(cm);
}

// @ 0x00e50450
void FUN_00e50450(int* param) {
  int local[3];
  local[0] = (int)param;
  local[1] = 0xb1b104;
  local[2] = 0x3629f036;
  void* cfg = SP_ConfigManager();
  int r = (*(int(__thiscall**)(void*, int))((char*)Vt(cfg) + 0x30))(cfg, 0x4ea96cb);
  FUN_00e82d50(local, param);
  if (r == 0 && param != 0) (*(void(__thiscall**)(int*))((char*)Vt(param) + 0))(param);
}

// @ 0x00e504b0
void FUN_00e504b0(int* p, float a) {
  if (a == 0.0f) {
    if (!p) return;
    (*(void(__thiscall**)(int*, int))((char*)Vt(p) + 0x5c))(p, -1);
    (*(void(__thiscall**)(int*, int, int))((char*)Vt(p) + 0x7c))(p, 1, 0);
  } else {
    if (!p) return;
    (*(void(__thiscall**)(int*, int, int))((char*)Vt(p) + 0x7c))(p, 1, 1);
    int v = (int)(a * 255.0f);
    (*(void(__thiscall**)(int*, int))((char*)Vt(p) + 0x5c))(p, (v << 24) | 0xffffff);
  }
}

// @ 0x00e50220  piecewise normalized curve
float FUN_00e50220(float t, float* cp) {
  float a = cp[0];
  if (a == -1.0f) {
    if (cp[3] == -1.0f) return 1.0f;
    float r = FUN_01041cd0(a, cp[3], t);
    if (r < 0.0f) r = 0.0f;
    if (r > 1.0f) r = 1.0f;
    return 1.0f - r;
  }
  if (cp[3] == -1.0f) {
    float r = FUN_01041cd0(a, cp[1], t);
    if (r < 0.0f) r = 0.0f;
    if (r > 1.0f) r = 1.0f;
    return r;
  }
  if (t < a) return 0.0f;
  if (t < cp[1]) return FUN_01041cd0(a, cp[1], t);
  if (t < cp[2]) return 1.0f;
  if (t < cp[3]) return 1.0f - FUN_01041cd0(cp[2], cp[3], t);
  return 0.0f;
}

// @ 0x00e4f920  snap each component to a multiple of the period
void __fastcall FUN_00e4f920(void* unused, float* v, float period) {
  (void)unused;
  float inv = 1.0f / period;
  for (int i = 0; i < 3; ++i) {
    float f = v[i] * inv;
    int n = (int)f;
    if (f < (float)n) n--;
    v[i] = (float)n * period;
  }
}

// @ 0x00e4fd30  fill 13 bytes from a fixed 1/0 pattern
int FUN_00e4fd30(unsigned char* p) {
  for (int j = 0; j < 13; ++j) {
    int key = j - 2;
    int set = (key == 0 || key == 2 || key == 3 || key == 4 ||
               key == 5 || key == 6 || key == 8);
    p[j] = set ? 1 : 0;
  }
  return 13;
}

// @ 0x00e50400  reset collectables mode (self arrives in ESI)
void FUN_00e50400(void* self, char flag) {
  FUN_00b3d4d0(0);
  FUN_00ad7e40(0);
  g_16b3c0c[0x936] = 0;
  g_16b3c04[0x51db] = 0;
  if (flag) (*(void(__thiscall**)(void*, int))((char*)Vt(self) + 0xc))(self, 1);
  (*(void(__thiscall**)(void*))((char*)Vt(self) + 4))(self);
}
// --- equivalence checker address annotations

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
}

namespace __equiv_ann1 {   // address annotations for the equivalence checker; never referenced
struct cGuard16 {
    ~cGuard16();   // 0x00e82130 (equiv t3)
};
}
