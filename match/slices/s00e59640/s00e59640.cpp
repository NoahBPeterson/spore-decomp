// Slice s00e59640 (batch spcg1, slice 3). Object: SPGonzago/SPCellGame.obj
// SP::cCellGame cell-state helpers.  Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

// ---- globals (real names from the 2008 dev PDB) -------------------------
extern char* gspCellGfx;    // 0x016b3c08  SP::cCellGfx*

extern const float kf1485378;  // 0.0f
extern const float kf1485720;  // 1.0f
extern const float kf1470f1c;  // 2.0f
extern const float kf13eb8c8;  // 0.3f
extern const float kf1477fc0;  // 300.0f
extern const float kf15a7c34, kf15a7c38, kf15a7c3c;
extern const float kf13eb8b0;  // sign bit
extern const float kf15a7c40;
extern float g16b4434, g16b4438, g16b443c;
extern int   g16b4440;

// gCellGameExtents (SP::cSPBoundingBox) at 0x016b3c88
extern const float gExtentXMin;  // 0x016b3c88
extern const float gExtentYMin;  // 0x016b3c8c
extern const float gExtentXMax;  // 0x016b3c94
extern const float gExtentYMax;  // 0x016b3c98

// ---- callees ------------------------------------------------------------
struct CellPool { void* Get(unsigned int id); int Begin(); void* Next(int* out); };  // 0x00b721d0 / 0x00e31100 / 0x00b72230
struct IterPool { void* Next(int* out); };         // 0x00b72230 pool::Next
struct ResMap   { void* Find(unsigned int id); };  // 0x00b72210 map::Find
struct CellGame { char pad0[0x1c]; CellPool mCells; };
extern CellGame* gspCellGame;   // 0x016b3c04  SP::cCellGame*

void  FUN_00e57a10(void* cell, int x);             // 0x00e57a10
int   FUN_00e51430(void* o);                        // 0x00e51430
float FUN_00e51720(int a, int b);                   // 0x00e51720
void  FUN_00e4fac0(void* o);                        // 0x00e4fac0
void  FUN_00e84600(int, int, char, void*, float, char, int, int);  // 0x00e84600
void* __cdecl memset_thunk(void* p, int v, unsigned n);// 0x011e073e
int   FUN_00e50620(int a, int b);                   // 0x00e50620
int   FUN_00e57340(int a);                          // 0x00e57340
int   FUN_00e4cce0(int a);                          // 0x00e4cce0
void  FUN_00743b50(void* this_);                    // 0x00743b50
struct ObjHolder { void Init(); void Cleanup(); };  // 0x00743b50 / 0x00e82130  thiscall
int   FUN_00e823a0(int id, void* out);              // 0x00e4cc40
void  FUN_00e82130(void* this_);                    // 0x00e82130
void  FUN_00e51a40(int, int, void*, int);           // 0x00e51a40
float FUN_006994a0(float*, float*, const void*);    // 0x006994a0
void  FUN_00e56c30(float, float*, int*, int*);      // 0x00e56c30
struct CellSub { int Level(); };                    // 0x00e51430  thiscall
void  __cdecl FluidParticlesUpdate(void* p, float t);// 0x00e4ebe0
int   FUN_00e31100(void* this_);                    // 0x00e31100

// @ 0x00e59640
bool FUN_00e59640(int id, int a, int b, int state, int* v) {
  CellPool* pool = &gspCellGame->mCells;
  char* c = (char*)pool->Get(id);
  if (!c) return false;
  if (c[0x112]) return false;
  *(int*)(c + 0x184) = a;
  *(char*)(c + 0x178) = 1;
  switch (*(int*)(c + 0x18c)) {
    case 0: case 3: case 0xb: case 0xc: case 0xd: case 0x12:
    case 0x15: case 0x16: case 0x1a: case 0x1d: case 0x20: case 0x21:
    case 0x22: case 0x30:
      *(int*)(c + 0x18c) = state;
      *(int*)(c + 0x1a0) = v[0];
      *(int*)(c + 0x1a4) = v[1];
      *(int*)(c + 0x1a8) = v[2];
      c[4] = 1;
      FUN_00e57a10(c, b);
  }
  return true;
}

// @ 0x00e59710
bool FUN_00e59710(int id, int id2, int a, int b, float t) {
  char* c1;
  { CellPool* pool = &gspCellGame->mCells; c1 = (char*)pool->Get(id); }
  if (!c1) return false;
  if (c1[0x112]) return false;
  char* c2;
  { CellPool* pool = &gspCellGame->mCells; c2 = (char*)pool->Get(id2); }
  if (!c2) return false;
  if (c2[0x112]) return false;
  *(char*)(c1 + 0x178) = 1;
  *(int*)(c1 + 0x184) = *(int*)c2;
  *(char*)(c1 + 0x188) = 1;
  *(int*)(c2 + 0x184) = *(int*)c1;
  switch (*(int*)(c1 + 0x18c)) {
    case 0: case 0xb: case 0xc: case 0xd: case 0x12: case 0x13: case 0x14:
    case 0x15: case 0x16: case 0x1d: case 0x30: case 0x32: case 0x33:
      if (t > kf1485378) {
        *(int*)(c1 + 0x18c) = 0xd;
        FUN_00e57a10(c1, a);
      }
  }
  return true;
}

// @ 0x00e59800  SP::cCellMode::OnKeyDown candidate
#define GAME_P (*(char**)((char*)gspCellGame + 0x5190))
void FUN_00e59800(int param_1) {
  int iVar3 = ((CellSub*)*(void**)(GAME_P + 0x1c))->Level();
  int delta = iVar3 - *(int*)(GAME_P + 0x2c);
  float f = FUN_00e51720(2, *(int*)(GAME_P + 0x1c));
  FUN_00e4fac0(GAME_P + 0x34);
  int iVar2 = *(int*)(GAME_P + 0x1c);
  int* entry;
  if (iVar2 == 1000) {
    entry = (int*)0x1483e60;
  } else {
    int i = 0;
    if (iVar2 >= 0) {
      int* t = (int*)0x1483c34;
      do { t += 7; ++i; } while (*t <= iVar2);
    }
    entry = (int*)0x1483c14 + i * 7;
  }
  FUN_00e84600(param_1, entry[5], GAME_P[0xe2], GAME_P + 0x10, f,
               GAME_P[0x410c], *(int*)(GAME_P + 0x5164), delta);
}

// @ 0x00e598e0  static register-ABI helper (id in eax)
static bool FUN_00e598e0(int id, float t) {
  CellPool* pool = &gspCellGame->mCells;
  char* c = (char*)pool->Get(id);
  if (!c) return false;
  float d = t - kf1485720;
  c[0x16c] = 1;
  c[0x178] = 1;
  c[0x17f] = 1;
  c[0x180] = 1;
  c[0x17b] = 1;
  c[0x17c] = 1;
  c[0x188] = 1;
  if (d > kf1485378) {
    switch (*(int*)(c + 0x18c)) {
      case 0: case 7: case 8: case 9: case 0xb: case 0xc: case 0xd:
      case 0xf: case 0x10: case 0x12: case 0x1d: case 0x29: case 0x2b:
      case 0x2c: case 0x2d: case 0x2e: case 0x30: case 0x31: case 0x41:
      case 0x42:
        *(int*)(c + 0x18c) = 0x29;
    }
  }
  return true;
}

// @ 0x00e599b0  static register-ABI helper (id in eax)
static bool FUN_00e599b0(int id) {
  CellPool* pool = &gspCellGame->mCells;
  char* c = (char*)pool->Get(id);
  if (!c) return false;
  c[0x178] = 1;
  switch (*(int*)(c + 0x18c)) {
    case 7: case 8: case 9: case 0xb: case 0xc: case 0xd: case 0x21:
    case 0x22: case 0x29: case 0x2b: case 0x2c: case 0x2d: case 0x2e:
      break;
    default:
      *(int*)(c + 0x18c) = 0x1d;
  }
  return true;
}

// @ 0x00e59a30
bool FUN_00e59a30() {
  unsigned int id = *(unsigned int*)((char*)gspCellGame + 0x411c);
  CellPool* pool = &gspCellGame->mCells;
  char* c = (char*)pool->Get(id);
  if (!c) return false;
  *(int*)(c + 0x18c) = 0x2e;
  c[0x17c] = 1;
  c[0x17b] = 1;
  c[0x188] = 1;
  return true;
}

// @ 0x00e59a70  static register-ABI helper (arg in eax)
static bool FUN_00e59a70(int id) {
  CellPool* pool = &gspCellGame->mCells;
  char* c = (char*)pool->Get(id);
  if (!c) return false;
  c[0x178] = 1;
  c[0x17f] = 1;
  *(int*)(c + 0x18c) = 0x31;
  return true;
}

// @ 0x00e59ab0
void FUN_00e59ab0(int id) {
  CellPool* pool = &gspCellGame->mCells;
  char* c = (char*)pool->Get(id);
  if (c) {
    int src = *(int*)((char*)gspCellGame + 0x411c);
    float f = kf1477fc0;
    *(int*)(c + 0x220) = src;
    *(float*)(c + 0x21c) = f;
  }
}

// @ 0x00e59af0
bool FUN_00e59af0(int id, int a) {
  CellPool* pool = &gspCellGame->mCells;
  char* c = (char*)pool->Get(id);
  if (!c) return false;
  c[0x17c] = 1;
  c[0x178] = 1;
  c[0x16c] = 1;
  int s = *(int*)(c + 0x18c);
  if (s != 7 && s != 10) {
    *(int*)(c + 0x18c) = (a != 6) + 0x3f;
  }
  return true;
}

// @ 0x00e59b50
bool FUN_00e59b50(int id, int a, int* v) {
  CellPool* pool = &gspCellGame->mCells;
  char* c = (char*)pool->Get(id);
  if (!c) return false;
  c[0x16c] = 1;
  c[0x178] = 1;
  c[0x17f] = 1;
  switch (*(int*)(c + 0x18c)) {
    case 0: case 0x12: case 0x13: case 0x14: case 0x15: case 0x16: case 0x30:
      *(int*)(c + 0x18c) = 0x1c;
      *(int*)(c + 0x1a0) = v[0];
      *(int*)(c + 0x1a4) = v[1];
      *(int*)(c + 0x1a8) = v[2];
      FUN_00e57a10(c, a);
  }
  return true;
}

// @ 0x00e59c10
struct CbRec {
  char pad0[4];
  bool (*fn)(void* self, float x);  // +0x4
  char done;                        // +0x8
  char pad9[0x28 - 9];
  int  id;                          // +0x28
};

bool FUN_00e59c10(CbRec* p, float x) {
  CellPool* pool = &gspCellGame->mCells;
  char* c = (char*)pool->Get(p->id);
  if (c) {
    if (*(int*)(c + 0x248) != 0 && *(int*)(c + 0xfc) != 0) {
      void* q = ((ResMap*)(gspCellGfx + 0x168))->Find(*(unsigned int*)(c + 0x248));
      if (*(int*)((char*)q + 0x24) != 0) {
        char r = (char)FUN_00e50620(0xca880d53, 0);
        if (p->fn == 0) return true;
        if (p->done) return true;
        if (r == 0) return true;
        bool ret = p->fn(p, x);
        p->done = 1;
        return ret;
      }
    }
    if (p->fn != 0 && !p->done) {
      bool ret = p->fn(p, x);
      p->done = 1;
      return ret;
    }
  }
  return true;
}

// @ 0x00e59cc0
void FUN_00e59cc0(int* rec, int* a, int* b, float f, int c5, int c6, int c7, int c8, int c9) {
  if (c9 > rec[2] || (c9 == rec[2] && f > *(float*)(rec + 5))) {
    rec[1] = c6;
    rec[0] = c5;
    rec[6] = a[0];
    rec[7] = a[1];
    rec[8] = a[2];
    rec[9] = b[0];
    rec[10] = b[1];
    rec[11] = b[2];
    *(float*)(rec + 5) = f;
    rec[3] = c7;
    rec[4] = c8;
    rec[2] = c9;
  }
  if (c9 == rec[2] && c9 == 8 && c5 == *(int*)((char*)gspCellGame + 0x411c)) {
    rec[0] = c5;
    rec[1] = c6;
    rec[6] = a[0];
    rec[7] = a[1];
    rec[8] = a[2];
    rec[9] = b[0];
    rec[10] = b[1];
    rec[11] = b[2];
    *(float*)(rec + 5) = f;
    rec[3] = c7;
    rec[4] = c8;
    rec[2] = 8;
  }
}

// @ 0x00e59d90
int FUN_00e59d90(int id) {
  int result = 2;
  CellPool* pool = &gspCellGame->mCells;
  char* c = (char*)pool->Get(id);
  if (c) {
    char obj[4];
    ((ObjHolder*)obj)->Init();
    char* r = (char*)FUN_00e823a0(*(int*)(c + 0x108), obj);
    int v = *(int*)(r + 0xc0);
    if (v != 0) {
      ((ObjHolder*)obj)->Cleanup();
      return v;
    }
    switch (*(int*)(r + 0xb4)) {
      case 1: result = 3; break;
      case 2: result = 1; break;
      case 3: result = 2; break;
      case 4: result = 4; break;
    }
    ((ObjHolder*)obj)->Cleanup();
  }
  return result;
}

// @ 0x00e59e50
bool FUN_00e59e50(int p, int arg) {
  if (*(int*)(p + 0x108) != FUN_00e4cce0(arg)) return false;
  if (FUN_00e57340(p) == 4) return true;
  return false;
}

// @ 0x00e59e80
void FUN_00e59e80() {
  *(char*)((char*)gspCellGame + 0x4120) = 0;
  int local;
  { CellPool* pool = &gspCellGame->mCells; local = pool->Begin(); }
  char* p;
  { CellPool* pool = &gspCellGame->mCells; p = (char*)pool->Next(&local); }
  while (p) {
    memset_thunk(p + 0x16c, 0, 0x44);
    { CellPool* pool = &gspCellGame->mCells; p = (char*)pool->Next(&local); }
  }
}

// @ 0x00e59ee0
void SP_sUpdateFluidParticles(float dt) {
  char* fp = *(char**)((char*)gspCellGame + 0x4108);
  FluidParticlesUpdate(fp, dt);
  int off = 0;
  int idx = 0x18e74;
  do {
    char* c = fp + off;
    *(float*)(c + 0xc) = 0.0f;
    *(float*)(c + 0x465c) = 0.0f;
    *(float*)(c + 0xd2fc) = 0.0f;
    *(float*)(c + 0x1194c) = 0.0f;
    float* pos = (float*)(c + 4);
    float fy = *(float*)(c + 0xd2f8) * dt + *(float*)(c + 0x4658);
    float fx = *(float*)(c + 0x4654) + *(float*)(c + 0xd2f4) * dt;
    *(float*)(c + 0x4654) = fx;
    *(float*)(c + 0x4658) = fy;
    float fz = *(float*)(c + 0x465c) + dt * *(float*)(c + 0xd2fc);
    *(float*)(c + 0x465c) = fz;
    fy = (fy * dt + *(float*)(c + 0x11948)) + *(float*)(c + 8);
    fx = *pos + (fx * dt + *(float*)(c + 0x11944));
    *pos = fx;
    *(float*)(c + 8) = fy;
    *(float*)(c + 0xc) = (fz * dt + *(float*)(c + 0x1194c)) + *(float*)(c + 0xc);
    if ((fx < gExtentXMin || gExtentXMax < fx || fy < gExtentYMin || gExtentYMax < fy) &&
        *(int*)(fp + idx) == 0) {
      if (gExtentXMin <= fx) {
        if (gExtentXMax < fx) *pos = fx - (gExtentXMax - gExtentXMin);
      } else {
        *pos = (gExtentXMax - gExtentXMin) + fx;
      }
      if (gExtentYMin <= fy) {
        if (gExtentYMax < fy) *(float*)(c + 8) = fy - (gExtentYMax - gExtentYMin);
      } else {
        *(float*)(c + 8) = (gExtentYMax - gExtentYMin) + fy;
      }
      int col, row;
      FUN_00e56c30(*(float*)((char*)gspCellGame + 4), pos, &col, &row);
      float s = *(float*)((char*)gspCellGame + 8);
      int t = row * 0x80 + col;
      float vc = s * *(float*)(*(int*)(*(int*)(char*)gspCellGame + 0x18) + t * 0xc);
      float v8 = s * *(float*)(*(int*)(*(int*)(char*)gspCellGame + 0x18) + 4 + t * 0xc);
      float v4 = s * 0.0f;
      *(float*)(c + 0x4654) = vc;
      *(float*)(c + 0x4658) = v8;
      *(float*)(c + 0x465c) = v4;
    }
    idx += 4;
    off += 0xc;
  } while (idx < 0x1a5e4);
  memset_thunk(fp + 0xd2f4, 0, 18000);
  memset_thunk(fp + 0x11944, 0, 18000);
}

// @ 0x00e5a1a0
static void FUN_00e5a1a0(char* cell) {
  if (*(int*)(cell + 0x248) != 0 &&
      *(int*)(cell + 0x35c) != *(int*)((char*)gspCellGame + 0x4100)) {
    float f = *(float*)(cell + 0x58);
    int lvl;
    if (f < kf1470f1c) {
      if (f < kf1485720) {
        lvl = (f < kf13eb8c8) ? 0 : 1;
      } else {
        lvl = 2;
      }
    } else {
      lvl = 3;
    }
    if (*(int*)(cell + 0x24c) != lvl) {
      char o1[4];
      char o2[4];
      ((ObjHolder*)o1)->Init();
      char* r = (char*)FUN_00e823a0(*(int*)(cell + 0x108), o1);
      ((ObjHolder*)o2)->Init();
      FUN_00e823a0(*(int*)r, o2);
      int state = *(int*)(r + 0xb4);
      if (state != 0 && state != 5) {
        FUN_00e51a40(0x16ae800, *(int*)cell, cell + 0x250, *(int*)(cell + 0x24c));
        *(int*)(cell + 0x24c) = lvl;
      }
      ((ObjHolder*)o2)->Cleanup();
      ((ObjHolder*)o1)->Cleanup();
    }
  }
}

// @ 0x00e5a2a0
float FUN_00e5a2a0(float* a, float* b, float d) {
  if ((g16b4440 & 1) == 0) {
    g16b4440 |= 1;
    g16b4434 = -kf15a7c34;
    g16b4438 = -kf15a7c38;
    g16b443c = -kf15a7c3c;
  }
  float va[3], vb[3];
  va[0] = (a[6] * g16b443c + a[3] * g16b4438) + a[0] * g16b4434;
  va[1] = (a[7] * g16b443c + a[4] * g16b4438) + a[1] * g16b4434;
  va[2] = (a[8] * g16b443c + a[5] * g16b4438) + a[2] * g16b4434;
  vb[0] = (b[6] * g16b443c + b[3] * g16b4438) + b[0] * g16b4434;
  vb[1] = (b[7] * g16b443c + b[4] * g16b4438) + b[1] * g16b4434;
  vb[2] = (b[8] * g16b443c + b[5] * g16b4438) + b[2] * g16b4434;
  return FUN_006994a0(va, vb, &kf15a7c40) / d;
}

// ---- stand-in callers: force register conventions for TU-local statics ----
bool keep_00e59a70(int x) { return FUN_00e59a70(x); }
bool keep_00e598e0(int x, float f) { return FUN_00e598e0(x, f); }
bool keep_00e599b0(int x) { return FUN_00e599b0(x); }
void keep_00e5a1a0(char* c) { FUN_00e5a1a0(c); }
