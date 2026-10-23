// Slice s00e58730 (batch spcg1, slice 1) — SPGonzago/SPCellGame.obj.
// Cell-game UI update, cell-pair transitions, plane clipping, level-entry lookup and a
// family of cell state setters. Optimised: /O2 /MD /Gy /TP /arch:SSE /fp:fast.
#include "types.h"

// ---- globals ----
extern "C" char  gspCellGame_16b3c04[];   // holds SP::cCellGame*
extern "C" char  g_16b3c0c[];             // SPUI layout manager global (pointer)
extern "C" int   gLvlTableA[];            // 0x01483c14, stride 7 dwords
extern "C" int   gLvlTableB[];            // 0x01483c34
extern "C" int   gLvlTable1000[];         // 0x01483e60
extern "C" float k1440f84;                // 0x01440f84  0.16666667f
extern "C" float k1471064;                // 0x01471064  0.5f
extern "C" float k1485378;                // 0x01485378  0.0f
extern "C" float k1488874;                // 0x01488874  0.1f
extern "C" float k13eb8b0;                // 0x013eb8b0  -0.0f

#define G (*(char**)gspCellGame_16b3c04)

// ---- pool helpers (thiscall members) ----
struct Pool {
  void* Alloc();            // 0x00b72160
  void* Get(unsigned id);   // 0x00b72210, ret 4
  void* GetValid(int id);   // 0x00b721d0, ret 4
  void* Next(int* out);     // 0x00b72230, ret 4
  int   Begin();            // 0x00e31100, ret 0
  void  Remove(int id);     // 0x00b72260, ret 4
};

static inline Pool& CellsPool() { return *(Pool*)(G + 0x1c); }
static inline Pool& SecPool()   { return *(Pool*)(G + 0x8c); }
static inline Pool& UiPool()    { return *(Pool*)(*(char**)g_16b3c0c + 0x9c); }

// intrusive-ptr temp used by the resource lookups
struct Ref {
  void* p;
  void Init();      // 0x00743b50
  void Release();   // 0x00e82130
};

struct Layout { void* FindWindowByID(unsigned id, char flag); };   // 0x008105b0, ret 8

// ---- external callees ----
extern "C" void* __cdecl FUN_00e823a0(int id, void* out);          // 0x00e4cc40
extern "C" void  __cdecl FUN_00e57a10(void* cell, int a);          // 0x00e57a10
extern "C" void  __cdecl FUN_00e560d0(void* cell, float* v);       // 0x00e560d0
extern "C" void  __cdecl FUN_00e582c0(void* cell, float t);        // 0x00e582c0
extern "C" int   __cdecl FUN_00e57340(void* cell);                 // 0x00e57340
extern "C" float __cdecl FUN_00e513d0(float a, float b, float c, float d, float e); // 0x00e513d0

static inline int* LevelEntry(int level) {
  if (level == 1000) return gLvlTable1000;
  int i = 0;
  if (level >= 0) {
    int* p = gLvlTableB;
    do { p += 7; ++i; } while (level >= *p);
  }
  return &gLvlTableA[i * 7];
}

// ---- window vtable accessors ----
typedef void* (__thiscall *PFN_GetChild)(void*, unsigned, char);
typedef void* (__thiscall *PFN_GetBox)(void*);
typedef void  (__thiscall *PFN_SetSize)(void*, float, float);
#define VT(w) (*(void***)(w))

// @ 0x00e58730  SP::sUpdateHealthUIs
void sUpdateHealthUIs(float dt) {
  int cur = *(int*)(G + 0x411c);
  char* cell = (char*)CellsPool().GetValid(cur);
  void* mgr = *(void**)(*(char**)g_16b3c0c + 0x90);
  void* w = ((Layout*)mgr)->FindWindowByID(0x18ac46e, 1);
  if (cell != 0) {
    float s = (float)*(int*)(cell + 0x244) * k1440f84;
    if (w != 0) {
      void* child = ((PFN_GetChild)VT(w)[0xf0 / 4])(w, 0x665fe90, 0);
      if (child != 0) {
        float* box = (float*)((PFN_GetBox)VT(child)[0x38 / 4])(child);
        float h = box[3] - box[1];
        float width = (box[2] - box[0]) * s;
        ((PFN_SetSize)VT(w)[0x74 / 4])(w, width, h);
      }
    }
  } else {
    if (w != 0) {
      void* child = ((PFN_GetChild)VT(w)[0xf0 / 4])(w, 0x665fe90, 0);
      if (child != 0) {
        float* box = (float*)((PFN_GetBox)VT(child)[0x38 / 4])(child);
        float h = box[3] - box[1];
        float width = (box[2] - box[0]) * k1485378;
        ((PFN_SetSize)VT(w)[0x74 / 4])(w, width, h);
      }
    }
  }
  int it = UiPool().Begin();
  char* c = (char*)UiPool().Next(&it);
  while (c != 0) {
    FUN_00e582c0(c, dt);
    c = (char*)UiPool().Next(&it);
  }
}

// @ 0x00e58890  SP::sCellPairInit
bool FUN_00e58890(int id1, int id2, int a) {
  char* c1 = (char*)CellsPool().GetValid(id1);
  if (!c1) return false;
  char* c2 = (char*)CellsPool().GetValid(id2);
  if (!c2) return false;
  c1[0x18a] = 1;
  c1[0x17f] = 1;
  c1[0x17c] = 1;
  c1[0x17b] = 1;
  c1[0x17e] = 1;
  *(int*)(c2 + 0x190) = id1;
  c2[0x17f] = 1;
  c2[0x178] = 1;
  c2[0x17c] = 1;
  FUN_00e57a10(c2, a);
  switch (*(int*)(c1 + 0x18c)) {
    case 0: case 1: case 0x12: case 0x13: case 0x14: case 0x15:
    case 0x16: case 0x1d: case 0x30:
      *(int*)(c1 + 0x18c) = 0x1e;
      FUN_00e57a10(c1, a);
  }
  return true;
}

// @ 0x00e58980  SP::sGetPairRelation
int FUN_00e58980(int* a, int* b) {
  if (*a == *(int*)(G + 0x411c)) {
    switch (FUN_00e57340(b)) {
      case 0: case 1: return 6;
      case 2: return (*(int*)(*(int*)(G + 0x5190) + 0x7c) != 2) + 2;
      case 3: case 4: return 1;
      default: return 0;
    }
  }
  if (*b != *(int*)(G + 0x411c)) {
    int local_64[25] = {
      0, 0, 0, 0, 0,
      6, 2, 1, 0, 0,
      6, 6, 2, 0, 0,
      6, 6, 6, 2, 0,
      6, 6, 6, 6, 2
    };
    int i = FUN_00e57340(a);
    int j = FUN_00e57340(b);
    return local_64[i * 5 + j];
  }
  switch (FUN_00e57340(a)) {
    case 0: case 1: return 1;
    case 2: return 2;
    case 3: return 3;
    case 4: return 6;
    default: return 0;
  }
}

// @ 0x00e58b60  health-bar scale
float FUN_00e58b60(float a, float b) {
  if (0.5f > a) return FUN_00e513d0(0.0f, 0.5f, a, 0.0f, 1.0f);
  if (a > b - 0.5f) return FUN_00e513d0(b - 0.5f, b, a, 1.0f, 0.0f);
  return 1.0f;
}

// @ 0x00e58bf0
bool FUN_00e58bf0(int id, float a, float b) {
  char* c = (char*)CellsPool().GetValid(id);
  if (!c) return false;
  if (*(int*)(c + 0x248) != 0) {
    float r = FUN_00e58b60(a, b);
    *(float*)(c + 0xa0) = r;
    *(float*)(c + 0xa4) = r;
  }
  return true;
}

// @ 0x00e58c50  follow the cell's child link to the root
char* FUN_00e58c50(char* p) {
  char* r = (char*)CellsPool().GetValid(*(int*)(p + 0x36c));
  while (r != 0) {
    p = r;
    int child = *(int*)(r + 0x36c);
    r = (char*)CellsPool().GetValid(child);
  }
  return p;
}

// @ 0x00e58c90  clip a plane against two cell lines
bool FUN_00e58c90(char* p) {
  char* c1 = (char*)CellsPool().GetValid(*(int*)(p + 4));
  char* c2 = (char*)CellsPool().GetValid(*(int*)(p + 8));
  if (!c1 || !c2) return false;
  c1 = FUN_00e58c50(c1);
  c2 = FUN_00e58c50(c2);
  float old = *(float*)(p + 0x28);
  float dist = (*(float*)(p + 0x38) -
                ((*(float*)(c2 + 0x98) - *(float*)(c1 + 0x98)) * *(float*)(p + 0x20) +
                 (*(float*)(c2 + 0x94) - *(float*)(c1 + 0x94)) * *(float*)(p + 0x1c) +
                 (*(float*)(c2 + 0x90) - *(float*)(c1 + 0x90)) * *(float*)(p + 0x18))) *
               *(float*)(p + 0x30) + old;
  dist = (0.0f > dist) ? 0.0f : dist;
  *(float*)(p + 0x28) = dist;
  float d = dist - old;
  float vx = *(float*)(p + 0x18) * d;
  float vy = *(float*)(p + 0x1c) * d;
  float vz = *(float*)(p + 0x20) * d;
  if (*(float*)(p + 0x18) * vx + *(float*)(p + 0x1c) * vy + *(float*)(p + 0x20) * vz >= 0.0f) {
    float neg[3];
    neg[0] = -vx; neg[1] = -vy; neg[2] = -vz;
    FUN_00e560d0(c1, neg);
    float pos[3];
    pos[0] = vx; pos[1] = vy; pos[2] = vz;
    FUN_00e560d0(c2, pos);
  }
  return true;
}

// @ 0x00e58e30  level-entry lookup (returns a scalar)
int FUN_00e58e30() {
  int result = 0;
  Ref t; t.Init();
  char* list = (char*)FUN_00e823a0(*(int*)(G + 0x4114), &t);
  int lvl = *(int*)(*(char**)(G + 0x5190) + 0x1c);
  int v = *LevelEntry(lvl);
  int n = *(int*)(list + 8);
  char* p = *(char**)(list + 0xc);
  for (int i = 0; i < n; ++i, p += 0x18) {
    if (*(int*)(p + 4) == v + 1) {
      t.Release();
      return *(int*)(p + 0x14);
    }
    if (*(int*)(p + 4) == -1) result = *(int*)(p + 0x14);
  }
  t.Release();
  return result;
}

// @ 0x00e58ef0  level-entry lookup (fills an entry)
int FUN_00e58ef0(int* out0, float* out1, float* out2, float* out3) {
  int result = 0;
  Ref t; t.Init();
  char* list = (char*)FUN_00e823a0(*(int*)(G + 0x4114), &t);
  int lvl = *(int*)(*(char**)(G + 0x5190) + 0x1c);
  int v = *LevelEntry(lvl);
  int n = *(int*)(list + 8);
  if (n > 0) {
    for (int i = 0; i < n; ++i) {
      char* e = *(char**)(list + 0xc) + i * 0x18;
      if (*(int*)(e + 4) == v) {
        *out0 = *(int*)(e);
        *out1 = *(float*)(e + 8);
        *out2 = *(float*)(e + 0xc);
        *out3 = *(float*)(e + 0x10);
        t.Release();
        return *(int*)(e + 0x14);
      }
      if (*(int*)(e + 4) == -1) {
        *out0 = *(int*)(e);
        *out1 = *(float*)(e + 8);
        *out2 = *(float*)(e + 0xc);
        *out3 = *(float*)(e + 0x10);
        result = *(int*)(e + 0x14);
      }
    }
  }
  t.Release();
  return result;
}

// @ 0x00e59010  cell state transition driven by a direction vector
bool FUN_00e59010(int id, int a, int b, char flag, float f, float* v) {
  char* c = (char*)CellsPool().GetValid(id);
  if (!c) return false;
  c[0x17c] = 1;
  c[0x178] = 1;
  c[0x188] = 1;
  if (flag) {
    switch (*(int*)(c + 0x18c)) {
      case 0: case 1: case 2: case 3: case 4: case 5: case 0xb: case 0xc:
      case 0xd: case 0x12: case 0x13: case 0x14: case 0x15: case 0x16: case 0x18:
      case 0x19: case 0x1c: case 0x1e: case 0x28: case 0x2f: case 0x30: case 0x31:
        switch (b) {
          case 1: case 2:
            if (k1488874 > f) *(int*)(c + 0x190) = a;
            *(int*)(c + 0x18c) = 0xe;
            break;
          case 3:
            *(int*)(c + 0x18c) = 0xf;
            return true;
          case 4:
            *(int*)(c + 0x18c) = 0x10;
            break;
          case 5:
            *(int*)(c + 0x18c) = 0x11;
            break;
          default:
            return true;
        }
        *(float*)(c + 0x1a8) = -v[2];
        *(float*)(c + 0x1a4) = -v[1];
        *(float*)(c + 0x1a0) = -v[0];
    }
  }
  return true;
}

// @ 0x00e59150
void FUN_00e59150(int id) {
  char* c = (char*)CellsPool().GetValid(id);
  if (c) c[0x112] = 1;
}

// @ 0x00e59170
bool FUN_00e59170(int id) {
  char* c = (char*)CellsPool().GetValid(id);
  if (!c) return false;
  c[0x16c] = 1;
  c[0x178] = 1;
  c[0x17c] = 1;
  c[0x188] = 1;
  *(int*)(c + 0x18c) = 7;
  return true;
}

// @ 0x00e591c0
bool FUN_00e591c0(int id) {
  char* c = (char*)CellsPool().GetValid(id);
  if (!c) return false;
  c[0x16c] = 1;
  c[0x178] = 1;
  c[0x17c] = 1;
  *(int*)(c + 0x18c) = 7;
  return true;
}

// @ 0x00e59200
void FUN_00e59200(int id) {
  char* e = (char*)SecPool().GetValid(id);
  if (e) {
    int cid = *(int*)(e + 0xc);
    char* c = (char*)CellsPool().GetValid(cid);
    if (c) {
      *(int*)(c + 0x370) = 0;
      *(int*)(c + 0x36c) = 0;
    }
    SecPool().Remove(id);
  }
}

// @ 0x00e59260
bool FUN_00e59260(int id) {
  char* c = (char*)CellsPool().GetValid(id);
  if (!c) return false;
  switch (*(int*)(c + 0x18c)) {
    case 0: case 1: case 4: case 5: case 0xb: case 0xc: case 0xe: case 0xf:
    case 0x10: case 0x11: case 0x12: case 0x15: case 0x16: case 0x28: case 0x2f:
    case 0x30:
      *(int*)(c + 0x18c) = 8;
  }
  c[0x178] = 1;
  c[0x17b] = 1;
  c[0x17c] = 1;
  return true;
}

// @ 0x00e592f0
bool FUN_00e592f0(int id, int a, int b, int c2, int* v) {
  char* c = (char*)CellsPool().GetValid(id);
  if (!c) return false;
  c[0x178] = 1;
  c[0x17f] = 1;
  switch (*(int*)(c + 0x18c)) {
    case 0: case 2: case 4: case 5: case 0x12: case 0x13: case 0x14: case 0x15:
    case 0x16: case 0x21: case 0x28: case 0x30: case 0x32: case 0x33:
      *(int*)(c + 0x18c) = 4;
      *(int*)(c + 0x1a0) = v[0];
      *(int*)(c + 0x1a4) = v[1];
      *(int*)(c + 0x1a8) = v[2];
      FUN_00e57a10(c, b);
  }
  return true;
}

// @ 0x00e593b0
bool FUN_00e593b0(int id, int a, int b, int* v) {
  char* c = (char*)CellsPool().GetValid(id);
  if (!c) return false;
  c[0x178] = 1;
  c[0x17f] = 1;
  switch (*(int*)(c + 0x18c)) {
    case 0: case 0x12: case 0x13: case 0x14: case 0x15: case 0x16: case 0x30:
      *(int*)(c + 0x18c) = 0x1c;
      *(int*)(c + 0x1a0) = v[0];
      *(int*)(c + 0x1a4) = v[1];
      *(int*)(c + 0x1a8) = v[2];
      FUN_00e57a10(c, b);
  }
  return true;
}

// @ 0x00e59470
bool FUN_00e59470(int id) {
  char* c = (char*)CellsPool().GetValid(id);
  if (!c) return false;
  if (c[0x112] != 0) return false;
  c[0x178] = 1;
  switch (*(int*)(c + 0x18c)) {
    case 0: case 0x12: case 0x15: case 0x16: case 0x1d: case 0x30:
      *(int*)(c + 0x18c) = 0x3d;
  }
  return true;
}

// @ 0x00e59500
bool FUN_00e59500(int id) {
  char* c = (char*)CellsPool().GetValid(id);
  if (!c) return false;
  c[0x16c] = 1;
  c[0x17c] = 1;
  c[0x17b] = 1;
  c[0x17f] = 1;
  c[0x178] = 1;
  c[0x179] = 1;
  c[0x188] = 1;
  *(int*)(c + 0x18c) = 9;
  return true;
}

// @ 0x00e59560  (id in EAX, direction vector in EDI by the original)
bool FUN_00e59560(int id, int other, int b, int* v) {
  char* c = (char*)CellsPool().GetValid(id);
  if (!c) return false;
  if (c[0x112] != 0) return false;
  switch (*(int*)(c + 0x18c)) {
    case 0: case 4: case 5: case 0x12: case 0x13: case 0x14: case 0x15:
    case 0x16: case 0x1c: case 0x30: case 0x32: case 0x33:
      *(int*)(c + 0x18c) = 5;
      *(int*)(c + 0x1a0) = v[0];
      *(int*)(c + 0x1a4) = v[1];
      *(int*)(c + 0x1a8) = v[2];
      FUN_00e57a10(c, b);
  }
  c[0x17f] = 1;
  c[0x178] = 1;
  char* c2 = (char*)CellsPool().GetValid(other);
  if (c2) c2[0x188] = 1;
  return true;
}
