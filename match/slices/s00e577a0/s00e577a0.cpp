// Slice s00e577a0 (batch spcg1, slice 5). Object: SPGonzago/SPCellGame.obj
// SP::cCellGame cell-mode / part-icon / health-UI helpers.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

#define PVCAT2(a, b) a##b
#define PVCAT(a, b) PVCAT2(a, b)
#define PV virtual void PVCAT(pv_, __COUNTER__)();
#define PV2 PV PV
#define PV4 PV2 PV2
#define PV8 PV4 PV4

extern "C" double sqrt(double);

// ---- globals ------------------------------------------------------------
extern char* gspCellGfx;    // 0x016b3c08  SP::cCellGfx*

extern const float kf1485378;   // 0.0f
extern const float kf1485720;   // 1.0f
extern const float kf1488874;   // 0.1f
extern const float kf1470f1c;   // 2.0f
extern const float kf14853e0;   // 4.0f
extern const float kf1440f84;   // 0.16666667f
extern const float kf1486374;   // 0.8f
extern const float kf13f2100;   // 255.0f
extern const float kf14007f4;   // 15.0f
extern const float kf13ebc5c;   // 25.0f
extern const float kf13eb8b0;   // sign-bit mask
extern const float kf15a7c28, kf15a7c2c, kf15a7c30;   // forward axes
extern const float kf15a7c34, kf15a7c38, kf15a7c3c;   // reference axes

// ---- callees / helpers --------------------------------------------------
struct CellPool { void* Get(unsigned int id); };       // 0x00b721d0
struct ResMap   { void* Find(unsigned int id); };      // 0x00b72210
struct CellGame { char pad0[0x1c]; CellPool mCells; };
extern CellGame* gspCellGame;        // 0x016b3c04  SP::cCellGame*

struct ObjHolder { void Init(); void Cleanup(); };     // 0x00743b50 / 0x00e82130

void* FUN_00e823a0(int id, void* out);                 // thunk 0x00e4cc40
int   FUN_00e57340(int cell);
int   FUN_00e83470(void* a, int b);
void  FUN_00e50680(int a, void* b);
void  FUN_00e504b0(void* w, float v);
void  FUN_00e50750(float* a, float* b, float* c);
float FUN_005a6e00(float v);                           // Clamp01
void  FUN_00e54880(int cell);
char  FUN_00e52960(void* p);
int __fastcall FUN_00e4ee60(void* self, void* p);      // SP::sGetSourceLevel

struct RNG { double Next(double x); };                 // 0x009360d0
#define sMathRandom (*(RNG*)(void*)0x1601760)

// ---- UI -----------------------------------------------------------------
struct IWindow {
  PV8 PV4 PV                              // 0x00 .. 0x30 (13)
  virtual float* GetArea();               // 0x34 (13)
  PV8 PV                                  // 0x38 .. 0x58 (9)
  virtual void SetColor(unsigned c);      // 0x5c (23)
  virtual void SetArea(const float* r);   // 0x60 (24)
  virtual void SetSize(float w, float h); // 0x64 (25)
  PV4 PV                                  // 0x68 .. 0x78 (5)
  virtual void SetFlag(int flag, int on); // 0x7c (31)
};
struct cSPUILayout {
  IWindow* FindWindowByID(unsigned int id, int recurse);   // 0x008105b0
};
struct ConfigMgr {
  PV8 PV4
  virtual int Query(unsigned int id);     // 0x30
};
ConfigMgr* __cdecl ConfigManager();                        // 0x0067dd30

// ---- cell-mode selection (also exposed as FUN_00e52910) -----------------
// Defined here so the optimizer knows this callee leaves EDX intact (retail
// build had whole-program knowledge; 00e57890 keeps param_1 in EDX).
__declspec(noinline) char* FUN_00e52910(int param_1) {
  int iVar1 = *(int*)(*(int*)((char*)gspCellGame + 0x5190) + 0x7c);
  char* p;
  if (iVar1 == 0) {
    p = (char*)(param_1 + 0x248);
  } else {
    if (iVar1 != 2) return (char*)(param_1 + 0xe0);
    p = (char*)(param_1 + 0x194);
  }
  if (*(int*)p == -1) p = (char*)(param_1 + 0xe0);
  return p;
}

// @ 0x00e577a0
void FUN_00e577a0(int param_1, float* param_2, float* param_3, float* param_4, float* param_5) {
  float d[3];
  if (*param_2 > 0.0f) {
    d[0] = kf15a7c28; d[1] = kf15a7c2c; d[2] = kf15a7c30;
  } else {
    d[0] = -kf15a7c28; d[1] = -kf15a7c2c; d[2] = -kf15a7c30;
  }
  param_4[0] = param_3[0] + d[0] * kf14007f4;
  param_4[1] = param_3[1] + d[1] * kf14007f4;
  param_4[2] = param_3[2] + d[2] * kf14007f4;
  param_5[0] = param_3[0] + d[0] * kf13ebc5c;
  param_5[1] = param_3[1] + d[1] * kf13ebc5c;
  param_5[2] = param_3[2] + d[2] * kf13ebc5c;
}

// @ 0x00e57890
void FUN_00e57890(char* param_1, char* param_2) {
  int mode = *(int*)(*(int*)((char*)gspCellGame + 0x5190) + 0x7c);
  char* sel;
  switch (mode) {
    case 0:
      sel = param_2 + 0x248;
      if (*(int*)sel == -1) sel = param_2 + 0xe0;
      break;
    case 2:
      sel = param_2 + 0x194;
      if (*(int*)sel == -1) sel = param_2 + 0xe0;
      break;
    case 1:
      sel = param_2 + 0xe0;
      break;
    default:
      sel = param_2 + 0xe0;
      break;
  }
  if (0.0f < *(float*)(sel + 0x88)) {
    *(float*)(param_1 + 0x230) = 0.0f;
    char* r = FUN_00e52910((int)param_2);
    *(float*)(param_1 + 0x224) = *(float*)(r + 0x88);
    *(float*)(param_1 + 0x238) = 0.0f;
  }
}

// @ 0x00e57910  static register-ABI helper (this in ESI)
static void FUN_00e57910(char* self) {
  char local[4];
  ((ObjHolder*)local)->Init();
  char* obj = (char*)FUN_00e823a0(*(int*)(self + 0x108), local);
  int mode = *(int*)(*(int*)((char*)gspCellGame + 0x5190) + 0x7c);
  char* sel;
  if (mode == 0) {
    sel = obj + 0x248;
  } else if (mode == 2) {
    sel = obj + 0x194;
  } else {
    sel = obj + 0xe0;
  }
  if (mode == 0 || mode == 2) {
    if (*(int*)sel == -1) sel = obj + 0xe0;
  }
  switch (*(int*)sel) {
    case 0x1006:
      FUN_00e57890(self, obj);
      break;
  }
  ((ObjHolder*)local)->Cleanup();
}

// @ 0x00e579c0
char FUN_00e579c0(unsigned int id, int state) {
  CellPool* pool = &gspCellGame->mCells;
  char* p = (char*)pool->Get(id);
  if (p == 0) return 0;
  *(int*)(p + 0x170) = state;
  int e = *(int*)(p + 0x18c);
  *(char*)(p + 0x17e) = 1;
  if (e == 0 || (unsigned)(e - 0x15) <= 1) *(int*)(p + 0x18c) = 0x15;
  return 1;
}

// @ 0x00e57a10
void FUN_00e57a10(char* param_1, int param_2) {
  *(int*)(param_1 + 0x174) = param_2;
  if (*(int*)(param_1 + 0x248) == 0) return;
  if (*(int*)(param_1 + 0xfc) == 0) return;
  ResMap* map = (ResMap*)(gspCellGfx + 0x168);
  void* q = map->Find(*(unsigned int*)(param_1 + 0x248));
  char* s = *(char**)((char*)q + 0x24);
  if (s != 0) *(int*)(s + 0x174) = FUN_00e83470(s, param_2);
}

// @ 0x00e57a60
char FUN_00e57a60(unsigned int id, unsigned int id2, int a2, int state, float* vec) {
  CellPool* pool = &gspCellGame->mCells;
  char* p = (char*)pool->Get(id);
  if (p == 0) return 0;
  CellPool* pool2 = &gspCellGame->mCells;
  if ((char*)pool2->Get(id2) == 0) return 0;
  *(char*)(p + 0x178) = 1;
  *(char*)(p + 0x17f) = 1;
  switch (*(int*)(p + 0x18c)) {
    case 0: case 0x12: case 0x13: case 0x14: case 0x15: case 0x16:
    case 0x2f: case 0x30: case 0x32: case 0x33:
      *(int*)(p + 0x18c) = state;
      float v0 = vec[0];
      float v1 = vec[1];
      float v2 = vec[2];
      *(float*)(p + 0x1a0) = -v0;
      *(float*)(p + 0x1a4) = -v1;
      *(float*)(p + 0x1a8) = -v2;
      FUN_00e57a10(p, a2);
  }
  return 1;
}

// @ 0x00e57b50
char FUN_00e57b50(unsigned int id, unsigned int id2, int state, float* vec) {
  CellPool* pool = &gspCellGame->mCells;
  char* p = (char*)pool->Get(id);
  if (p == 0) return 0;
  *(char*)(p + 0x178) = 1;
  *(char*)(p + 0x17f) = 1;
  switch (*(int*)(p + 0x18c)) {
    case 0: case 0x12: case 0x13: case 0x14: case 0x15: case 0x16:
    case 0x32: case 0x33:
      *(int*)(p + 0x18c) = state;
      float v0 = vec[0];
      float v1 = vec[1];
      float v2 = vec[2];
      *(float*)(p + 0x1a0) = -v0;
      *(float*)(p + 0x1a4) = -v1;
      *(float*)(p + 0x1a8) = -v2;
      FUN_00e57a10(p, id2);
  }
  return 1;
}

// @ 0x00e57c30
char FUN_00e57c30(unsigned int id, unsigned int id2, int state) {
  CellPool* pool = &gspCellGame->mCells;
  char* p = (char*)pool->Get(id);
  if (p == 0) return 0;
  CellPool* pool2 = &gspCellGame->mCells;
  if ((char*)pool2->Get(id2) == 0) return 0;
  int e = *(int*)(p + 0x18c);
  *(char*)(p + 0x17a) = 1;
  if (e == 0 || e == 0x12 || e == 0x30) *(int*)(p + 0x18c) = state;
  return 1;
}

// @ 0x00e57c90
char FUN_00e57c90(unsigned int id, int state) {
  CellPool* pool = &gspCellGame->mCells;
  char* p = (char*)pool->Get(id);
  if (p == 0) return 0;
  *(int*)(p + 0x170) = state;
  int e = *(int*)(p + 0x18c);
  *(char*)(p + 0x17e) = 1;
  if (e == 0 || e == 0x16) *(int*)(p + 0x18c) = 0x16;
  return 1;
}

// @ 0x00e57ce0
char FUN_00e57ce0(int cell, void* p) {
  if (FUN_00e57340(cell) == 1) return 0;
  if (*(int*)(cell + 0xfc) == 0) return 0;
  return FUN_00e52960(p) != 0;
}

// @ 0x00e57d10
void FUN_00e57d10(unsigned int id, float a, float b) {
  CellPool* pool = &gspCellGame->mCells;
  char* p = (char*)pool->Get(id);
  if (p == 0) return;
  float ra = a * kf1488874;
  float r = (float)sMathRandom.Next((double)ra) * ra;
  float v = (ra <= r) ? ra : ((0.0f <= r) ? ra : 0.0f);
  *(float*)(p + 0x234) = v + a;
  float rb = b * kf1488874;
  float r2 = (float)sMathRandom.Next((double)rb) * rb;
  float v2 = (r2 < rb) ? ((r2 < 0.0f) ? 0.0f : rb) : rb;
  *(float*)(p + 0x224) = v2 + b;
}

// @ 0x00e57dc0
char FUN_00e57dc0(unsigned int id) {
  CellPool* pool = &gspCellGame->mCells;
  char* p = (char*)pool->Get(id);
  if (p == 0) return 0;
  int e = *(int*)(p + 0x18c);
  *(char*)(p + 0x180) = 1;
  if (e == 0 || e == 0x12 || e == 0x30) *(int*)(p + 0x18c) = 0x2a;
  return 1;
}

// @ 0x00e57e10  SP::sDropsWhichParts
void FUN_00e57e10(int param_1, void* param_2) {
  CellPool* pool = &gspCellGame->mCells;
  char* p = (char*)pool->Get(param_1);
  if (p == 0) return;
  void* mode = *(void**)((char*)gspCellGame + 0x5190);
  int lvl = FUN_00e4ee60(gspCellGame, *(void**)((char*)mode + 0x1c));
  int local[3];
  local[0] = 0;
  local[1] = lvl - 1;
  local[2] = 0x13;
  int* pi = local;
  if (lvl - 1 >= 0) pi = local + 1;
  if (*pi > 0x13) pi = local + 2;
  if (*(int*)(p + 0x358) != *pi) {
    char local2[4];
    ((ObjHolder*)local2)->Init();
    char* q = (char*)FUN_00e823a0(*(int*)(p + 0x108), local2);
    int s = *(int*)(q + 0xd4);
    if (s != 0) FUN_00e50680(s, param_2);
    ((ObjHolder*)local2)->Cleanup();
  }
}

// @ 0x00e57ec0  SP::sUpdatePartIcons
void FUN_00e57ec0(int param_1) {
  for (int i = 2; i < 0xb; ++i) {
    if (i == 3 || i == 9) continue;
    cSPUILayout* layout = *(cSPUILayout**)(param_1 + 0x34);
    IWindow* w = layout->FindWindowByID((unsigned)(i + 0x93310500), 1);
    if (w != 0) w->SetFlag(1, 0);
  }
  int buf[4];
  buf[0] = 0; buf[1] = 0; buf[2] = 0; buf[3] = 0;
  FUN_00e57e10(*(int*)(param_1 + 4), buf);
  int n = 0;
  int off = 0x34;
  unsigned id = 0x93310500;
  do {
    if (*(char*)((char*)buf + (id - 0x93310500)) != 0 &&
        *(int*)(off + *(int*)((char*)gspCellGame + 0x5190)) == 0) {
      if (n >= 2) return;
      cSPUILayout* layout = *(cSPUILayout**)(param_1 + 0x34);
      IWindow* w1 = layout->FindWindowByID(id, 1);
      cSPUILayout* layout2 = *(cSPUILayout**)(param_1 + 0x34);
      IWindow* w2 = layout2->FindWindowByID((unsigned)(n + 0x93310400), 1);
      w1->SetArea(w2->GetArea());
      w1->SetFlag(1, 1);
      ++n;
    }
    off += 4;
    ++id;
  } while ((int)(id + 0x6ccefb00) < 0xd);
}

// @ 0x00e57fd0  SP::sUpdateHealthUIValues
void FUN_00e57fd0(int param_1) {
  if (!(*(float*)(param_1 + 0x2c) > 0.0f) || *(char*)(param_1 + 0x30) == 0) {
    goto hide;
  }
  if (ConfigManager()->Query(0x679b833) != 0) goto hide;
  FUN_00e57ec0(param_1);
  {
    cSPUILayout* layout = *(cSPUILayout**)(param_1 + 0x34);
    IWindow* w = layout->FindWindowByID(0x933103ea, 1);
    if (w != 0) {
      w->SetFlag(1, 1);
      unsigned c = ((unsigned)(int)(*(float*)(param_1 + 0x2c) * kf13f2100) << 0x18) | 0xffffff;
      w->SetColor(c);
    }
  }
  goto after;
hide:
  {
    cSPUILayout* layout = *(cSPUILayout**)(param_1 + 0x34);
    IWindow* w = layout->FindWindowByID(0x933103ea, 1);
    if (w != 0) w->SetFlag(1, 0);
  }
after:
  {
    cSPUILayout* layout = *(cSPUILayout**)(param_1 + 0x34);
    IWindow* w = layout->FindWindowByID(0x93310e4a, 1);
    if (w != 0) {
      unsigned c = ((unsigned)(int)(*(float*)(param_1 + 0x20) * kf13f2100) << 0x18) | 0xffffff;
      w->SetColor(c);
    }
  }
  IWindow* bar = ((cSPUILayout*)*(cSPUILayout**)(param_1 + 0x34))->FindWindowByID(0x26e0df3, 1);
  IWindow* f1;
  IWindow* f2;
  {
    char* cell = (char*)((CellPool*)&gspCellGame->mCells)->Get(*(unsigned int*)(param_1 + 4));
    if (cell != 0 && FUN_00e57340((int)cell) == 4) {
      f1 = ((cSPUILayout*)*(cSPUILayout**)(param_1 + 0x34))->FindWindowByID(0x26e0df4, 1);
      f2 = ((cSPUILayout*)*(cSPUILayout**)(param_1 + 0x34))->FindWindowByID(0x26e0df0, 1);
    } else {
      f1 = ((cSPUILayout*)*(cSPUILayout**)(param_1 + 0x34))->FindWindowByID(0x26e0df0, 1);
      f2 = ((cSPUILayout*)*(cSPUILayout**)(param_1 + 0x34))->FindWindowByID(0x26e0df4, 1);
    }
  }
  float fv = *(float*)(param_1 + 8);
  if (f1 != 0) {
    float r[4];
    float* a = bar->GetArea();
    r[0] = 0.0f; r[1] = 0.0f;
    r[2] = (a[2] - a[0]) * fv;
    r[3] = a[3] - a[1];
    f1->SetArea(r);
    f1->SetFlag(1, 1);
  }
  if (f2 != 0) f2->SetFlag(1, 0);
  IWindow* g1 = ((cSPUILayout*)*(cSPUILayout**)(param_1 + 0x34))->FindWindowByID(0x26e0df2, 1);
  IWindow* g2 = ((cSPUILayout*)*(cSPUILayout**)(param_1 + 0x34))->FindWindowByID(0x26e0df1, 1);
  fv = *(float*)(param_1 + 0x14);
  if (g1 != 0) {
    float r[4];
    float* a = bar->GetArea();
    r[0] = 0.0f; r[1] = 0.0f;
    r[2] = (a[2] - a[0]) * fv;
    r[3] = a[3] - a[1];
    g1->SetArea(r);
  }
  fv = *(float*)(param_1 + 0x1c);
  if (g2 != 0) {
    float r[4];
    float* a = bar->GetArea();
    r[0] = 0.0f; r[1] = 0.0f;
    r[2] = (a[2] - a[0]) * fv;
    r[3] = a[3] - a[1];
    g2->SetArea(r);
  }
  FUN_00e504b0(g1, *(float*)(param_1 + 0x10));
  FUN_00e504b0(g2, *(float*)(param_1 + 0x18));
}

// @ 0x00e582c0  SP::sUpdateHealthUI
void FUN_00e582c0(int param_1, float param_2) {
  float d, en, cap, cur, g, a0, a1, a2, o0, o1, v;
  float* ph;
  float* pe;
  char* cell;
  bool enUp, gPos;
  IWindow* w;

  if (*(char*)((char*)gspCellGame + 0x5169) == 1) {
    FUN_00e54880(param_1);
    return;
  }

  d = param_2 * kf14853e0;                 // param_2 * 4.0
  ph = (float*)(param_1 + 0x2c);           // blinking-threshold slot
  *ph = *ph - d;
  if (*ph < kf1485378) *ph = kf1485378;    // clamp threshold to [0,1]
  if (*ph > kf1485720) *ph = kf1485720;

  cell = (char*)((CellPool*)&gspCellGame->mCells)->Get(*(unsigned int*)(param_1 + 4));
  if (cell == 0) {
    pe = (float*)(param_1 + 0x20);         // energy slot
    *pe = *pe - d;
    if (*(char*)(param_1 + 0x30) != 0) {
      if (!(*ph > *pe)) ph = pe;
      *pe = *ph;
    }
    FUN_00e57fd0(param_1);
    if (!(*pe > kf1485378)) FUN_00e54880(param_1);
    return;
  }

  cap = (float)*(int*)(cell + 0x244) * kf1440f84;   // capacity = max * 1/6
  cur = *(float*)(param_1 + 8);
  *(float*)(param_1 + 0xc) = cap;
  if (cur < cap) {
    *(float*)(param_1 + 0x14) = cap;
    *(float*)(param_1 + 0x1c) = cap;
  }
  if (*(float*)(param_1 + 0x28) > kf1485378) {      // death timer counts down
    *(float*)(param_1 + 0x28) = *(float*)(param_1 + 0x28) - param_2;
    goto done;
  }

  en = *(float*)(param_1 + 0x20);
  pe = (float*)(param_1 + 0x20);
  enUp = (kf1485720 > en && cur != cap);
  if (!enUp) {
    if (cur < cap) {
      if (*(float*)(param_1 + 0x10) > kf1485378)
        *(float*)(param_1 + 0x10) = FUN_005a6e00(*(float*)(param_1 + 0x10) - d);
      if (*(float*)(param_1 + 0x18) >= kf1485720) {
        v = param_2 * kf1470f1c + *(float*)(param_1 + 8);
        *(float*)(param_1 + 8) = v;
        if (*(float*)(param_1 + 0xc) <= v) *(float*)(param_1 + 8) = *(float*)(param_1 + 0xc);
      } else {
        *(float*)(param_1 + 0x18) = FUN_005a6e00(*(float*)(param_1 + 0x18) + d);
      }
      goto done;
    }
    if (cur == cap) {
      if (*(float*)(param_1 + 0x18) > kf1485378 && *(float*)(param_1 + 0x1c) > cur) {
        *(float*)(param_1 + 0x10) = FUN_005a6e00(*(float*)(param_1 + 0x10) - param_2);
        goto done;
      }
      if (*(float*)(param_1 + 0x24) > kf1485378) {
        if (kf1485720 > en) {
          enUp = true;
        } else {
          *(float*)(param_1 + 0x24) = *(float*)(param_1 + 0x24) - param_2;
          goto done;
        }
      } else {
        *pe = en - d;
        if (*(char*)(param_1 + 0x30) != 0) {
          if (!(*ph > *pe)) ph = pe;
          *pe = *ph;
        }
        if (!(*pe > kf1485378)) { FUN_00e54880(param_1); return; }
        goto done;
      }
    } else {                                   // cur > cap
      g = *(float*)(param_1 + 0x18);
      gPos = false;
      if (g > kf1485378) {
        *(float*)(param_1 + 0x18) = FUN_005a6e00(g - d);
        gPos = true;
      }
      if (*(float*)(param_1 + 0x10) >= kf1485720 || *(float*)(param_1 + 0x14) <= cur) {
        *(float*)(param_1 + 0x10) = kf1485720;
        if (!gPos) {
          v = *(float*)(param_1 + 8) - param_2 * kf1470f1c;
          *(float*)(param_1 + 8) = v;
          if (v <= *(float*)(param_1 + 0xc)) *(float*)(param_1 + 8) = *(float*)(param_1 + 0xc);
        }
        goto done;
      }
      *(float*)(param_1 + 0x10) = FUN_005a6e00(*(float*)(param_1 + 0x10) + d);
      goto done;
    }
  }
  // enUp: energy rises toward 1.0 (clamped)
  *pe = en + d;
  *pe = FUN_005a6e00(*pe);
  if (*(char*)(param_1 + 0x30) != 0) {
    if (!(*ph > *pe)) ph = pe;
    *pe = *ph;
  }

done:
  if (FUN_00e57340((int)cell) == 4) {
    a0 = *(float*)(cell + 0x4c);
    a1 = *(float*)(cell + 0x50);
    a2 = *(float*)(cell + 0x54);
  } else {
    v = *(float*)(cell + 0x58);
    a0 = *(float*)(cell + 0x4c) + (kf15a7c34 * v) * kf1486374;
    a1 = *(float*)(cell + 0x50) + (kf15a7c38 * v) * kf1486374;
    a2 = *(float*)(cell + 0x54) + (kf15a7c3c * v) * kf1486374;
  }
  FUN_00e50750(&a0, &o0, &o1);
  w = ((cSPUILayout*)*(cSPUILayout**)(param_1 + 0x34))->FindWindowByID(0x93310e4a, 1);
  w->SetSize(o0, o1);
  FUN_00e57fd0(param_1);
}

// ---- stand-in callers: force register conventions for TU-local statics ----
void keep_00e57910(char* c) { FUN_00e57910(c); }
