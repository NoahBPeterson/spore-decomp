// Slice s00e50810 (batch bfs0, slice 32). Region 0xe50810-0xe51819.
// SP::cCellMode / cell-game camera + input helpers (float math, bounds, source-level
// selection, save/load glue). Optimised: /O2 /MD /Gy /TP /arch:SSE /fp:fast.
#include "types.h"
#include <string.h>

static inline void** Vt(void* p) { return *(void***)p; }

// ---- globals (masked relocations) ----
extern float gBox_16b3c88, gBox_16b3c8c, gBox_16b3c90, gBox_16b3c94,
             gBox_16b3c98, gBox_16b3c9c, gBox_16b3ca0, gBox_16b3ca4,
             gBox_16b3ca8, gBox_16b3cac, gBox_16b3cb0, gBox_16b3cb4;
extern void*  gState_16b3c0c;   // cell-mode state object
extern void*  gCellGame_16b3c04;
extern float  gHalf_15a7c24;    // 180.0f (half period)
extern float  gPeriod_16b3dd0;  // 360.0f
extern float  gK_1473c70, gK_13f46c8, gK_13f46c8b;
extern float  gTable_1483e7c[];
extern int    gTable_1483c14[];
extern float  gOne_1485720, gNegOne_13eb1bc, gK_13eecd8, gK_14007f4, gK_1457e0c;
extern float  gK_1471064, gK_139935c, gK_13ec4d0, gK_13ec5b4, gK_13eb95c;
extern float  gK_1470f1c, gK_13eb8c8, gK_15a7c24b;
extern uint32_t gK_150d6d8;
extern uint32_t gTable_1483e98[];
extern uint32_t gTable_1483e9c[];

// ---- external callees ----
extern "C" void   __cdecl FUN_00743b50();                 // 0x743b50
extern "C" void*  __cdecl FUN_00e4ce40(void*);            // 0xe4ce40
extern "C" void   __cdecl FUN_00e82130();                 // 0xe82130
extern "C" void   __cdecl FUN_006ffe00(void*);            // 0x6ffe00
extern "C" void*  __cdecl FUN_00b3d4d0();                 // 0xb3d4d0
extern "C" void   __cdecl FUN_00ad7e40(void*);            // 0xad7e40
extern "C" void*  __cdecl thunk_FUN_00e823a0(int, void*); // 0xe4cc40
extern "C" void*  __cdecl thunk_FUN_00809970();           // 0xe82da0
extern "C" void   __cdecl FUN_00e836f0(uint32_t, void*, void*); // 0xe836f0
extern "C" void*  __cdecl FUN_00b3d410();                 // 0xb3d410
extern "C" bool   __cdecl FUN_00e393b0();                 // 0xe393b0
extern "C" bool   __cdecl FUN_00e82cd0();                 // 0xe82cd0
extern "C" bool   __cdecl FUN_00e82cc0();                 // 0xe82cc0
extern "C" bool   __cdecl FUN_00e00b00();                 // 0xe00b00
extern "C" bool   __cdecl FUN_00e00ac0();                 // 0xe00ac0
extern "C" bool   __cdecl FUN_00e18c70(void*);            // 0xe18c70
extern "C" void*  __cdecl FUN_0067cb20();                 // 0x67cb20
extern "C" void*  __cdecl FUN_0067de90(int, int);         // 0x67de90
extern "C" void*  __cdecl FUN_007ec160(int, int);         // 0x7ec160
extern "C" void   __cdecl FUN_007eb820(int);              // 0x7eb820
extern "C" void   __cdecl FUN_00e394f0(uint32_t, void*, void*, void*, void*); // 0xe394f0
extern "C" float  __cdecl FUN_01041cd0(void*, void*, void*); // 0x1041cd0
extern "C" void*  __cdecl EA_IO_WriteUint32(void*, void*, int, int); // 0x93aa70
extern "C" int    __cdecl SP_sGetSourceLevel();           // 0xe4ee60
struct cVarListSerializer {
  void Ctor(int a, void* b, uint32_t c);   // 0x692f90
  void Serialize(void* o);                 // 0x692900
};
struct cLocalInputState {
  uint32_t OnKeyUp(int, int);              // 0x697a80
  uint32_t OnMouseWheel(float, float, int);// 0x697b20
};
extern "C" void* __cdecl FUN_00b3d3f0(int, void*);

// @ 0x00e50810
void FUN_00e50810(float* p) {
  gBox_16b3c88 = p[0] - gK_1473c70;
  gBox_16b3c94 = p[0] + gK_1473c70;
  gBox_16b3c8c = p[1] - gK_13f46c8;
  gBox_16b3c98 = p[1] + gK_13f46c8;
  gBox_16b3c90 = 0.0f;
  gBox_16b3c9c = 0.0f;
  float local[1];
  FUN_00743b50();
  void* r = FUN_00e4ce40(local);
  float v = *(float*)((char*)r + 0x68);
  FUN_00e82130();
  float f = v * 0.06666667f + 1.0f;
  float w = (f * 20.0f) * 0.5f;
  gBox_16b3ca0 = p[0] - w;
  gBox_16b3cac = w + p[0];
  float h = (f * 15.0f) * 0.5f;
  gBox_16b3ca4 = p[1] - h;
  gBox_16b3cb0 = h + p[1];
  gBox_16b3ca8 = 0.0f;
  gBox_16b3cb4 = 0.0f;
  FUN_006ffe00((void*)0x16b4378);
}

// @ 0x00e50940
void FUN_00e50940(int a, uint8_t b) {
  (void)a;
  void* r = FUN_00b3d4d0();
  FUN_00ad7e40(r);
  *(uint8_t*)((char*)gState_16b3c0c + 0x936) = 0;
  *(uint32_t*)((char*)gState_16b3c0c + 0xe0) = 0;
  *(uint8_t*)((char*)gCellGame_16b3c04 + 0x51d8) = 1;
  *(uint8_t*)((char*)gCellGame_16b3c04 + 0x51d9) = b;
}

// @ 0x00e50990
int FUN_00e50990(int a) {
  float local[1];
  FUN_00743b50();
  char* r = (char*)thunk_FUN_00e823a0(a, local);
  if (*(int*)(r + 0xb4) != 6) { FUN_00e82130(); return 0; }
  int v = *(int*)(r + 0xb8);
  FUN_00e82130();
  return v;
}

// @ 0x00e509d0
bool __cdecl FUN_00e509d0(int a, char* obj) {
  if (obj == 0) return true;
  if ((*(uint8_t*)(obj + 0xb0) & 1) != 0) {
    switch (a) {
      case 2: return false;
      case 3: return true;
      case 4: return false;
      default: return *(int*)(obj + 0xb4) == 3;
    }
  }
  return *(int*)(obj + 0xb4) == 3;
}

// @ 0x00e50a10
int FUN_00e50a10(float* a, float* b, float c, float d, float e) {
  float x = *a;
  if (x == c && *b == 0.0f) return 1;
  float sign = 1.0f;
  if (x > c) sign = -1.0f;
  float diff = (c - x) * sign;
  float bv = *b;
  if (bv * e > diff) { *a = c; *b = 0.0f; return 1; }
  float step = sign * d * e;
  // |bv| / d * bv * sign < diff  -> move back
  float cmp = ((bv < 0 ? -bv : bv) / d * bv) * sign;
  if (diff < cmp) { bv = bv - step; *b = bv; *a = bv * e + *a; return 0; }
  bv = step + bv; *b = bv; *a = bv * e + *a; return 0;
}

// @ 0x00e50b80
void FUN_00e50b80(char* base, int* count, float* value, int cap) {
  if (*count < cap) { *(float*)(base + *count * 8) = 0.0f; ++*count; }
  int n = *count;
  float v = *value;
  if (*(float*)(base + n * 8 - 8) <= v) {
    int i = n - 1;
    while (i >= 0 && *(float*)(base + i * 8) <= v) --i;
    float* dst = (float*)(base + (i + 1) * 8);
    memmove((char*)dst + 8, dst, (n - (i + 1)) * 8 - 8);
    dst[0] = value[0];
    dst[1] = value[1];
  }
}

// @ 0x00e50c50
float FUN_00e50c50(float a) {
  for (; a <= -gHalf_15a7c24; a = gPeriod_16b3dd0 + a) {}
  for (; gHalf_15a7c24 < a; a = a - gPeriod_16b3dd0) {}
  return a;
}

// @ 0x00e50cb0
float FUN_00e50cb0(float a, float b, float* out) {
  b = b - a;
  for (; b <= -gHalf_15a7c24; b = gPeriod_16b3dd0 + b) {}
  for (; gHalf_15a7c24 < b; b = b - gPeriod_16b3dd0) {}
  *out = b < 0 ? -b : b;
  return b >= 0.0f ? 1.0f : -1.0f;
}

// @ 0x00e50d50
void FUN_00e50d50(float dt) {
  char* s = (char*)gState_16b3c0c;
  if (((*(uint32_t*)(s + 0xc) >> 0xb) & 1) || ((*(uint32_t*)(s + 0x14) >> 0x1b) & 1)) {
    if (!thunk_FUN_00809970()) {
      *(float*)(s + 0xf8) = dt * gK_139935c + *(float*)(s + 0xf8);
      float lo, hi;
      FUN_00e836f0(0x71cb8a60, &lo, &hi);
      float t = *(float*)(s + 0xf8);
      if (t <= lo) t = lo;
      if (hi <= t) t = hi;
      *(float*)(s + 0xf8) = t;
      *(uint32_t*)(s + 0x88) = 0;
    }
  }
  s = (char*)gState_16b3c0c;
  if (((*(uint32_t*)(s + 0xc) >> 0xd) & 1) || ((*(uint32_t*)(s + 0x14) >> 0x1d) & 1)) {
    if (!thunk_FUN_00809970()) {
      *(float*)(s + 0xf8) = *(float*)(s + 0xf8) - dt * gK_139935c;
      float lo, hi;
      FUN_00e836f0(0x71cb8a60, &lo, &hi);
      float t = *(float*)(s + 0xf8);
      if (t <= lo) t = lo;
      if (hi <= t) t = hi;
      *(float*)(s + 0xf8) = t;
      *(uint32_t*)(s + 0x88) = 0;
    }
  }
}

// @ 0x00e50ed0
float FUN_00e50ed0(float a) {
  float a2 = a * a;
  float q = a2 * 3.0f;
  float p = (a2 * a) * 2.0f;
  return ((p - q) + 1.0f) * 0.3f + (q - p);
}

// @ 0x00e50f30
bool FUN_00e50f30() {
  char* r = (char*)FUN_00b3d4d0();
  int v = *(int*)(r + 0x2c);
  if (v == 1 || v == 2) return true;
  return *(char*)((char*)gState_16b3c0c + 0x936) != 0;
}

// @ 0x00e50f60
void FUN_00e50f60(int n) {
  char* s = (char*)gState_16b3c0c;
  *(float*)(s + 0x80) = *(float*)(s + 0x80) - (float)n * 100.0f;
  float t = *(float*)(s + 0x80);
  if (t <= 20.0f) t = 20.0f;
  if (t >= 1000.0f) t = 1000.0f;
  *(float*)(s + 0x80) = t;
  *(uint32_t*)(s + 0x88) = 0;
}

// @ 0x00e51010
struct cCellMode {
  bool OnKeyUp(int a, int b);
  bool OnMouseMove(float a, float b, int c);
};

bool cCellMode::OnKeyUp(int a, int b) {
  ((cLocalInputState*)gState_16b3c0c)->OnKeyUp(a, b);
  return false;
}

bool cCellMode::OnMouseMove(float a, float b, int c) {
  ((cLocalInputState*)gState_16b3c0c)->OnMouseWheel(a, b, c);
  return false;
}

// @ 0x00e51060
void FUN_00e51060(float n) {
  char* s = (char*)gState_16b3c0c;
  *(float*)(s + 0xf8) = (float)(int)n + *(float*)(s + 0xf8);
  float lo, hi;
  FUN_00e836f0(0x71cb8a60, &n, &lo);
  (void)hi;
  float t = *(float*)(s + 0xf8);
  if (t <= n) t = n;
  if (lo <= t) t = lo;
  *(float*)(s + 0xf8) = t;
  *(uint32_t*)(s + 0x88) = 0;
}

// @ 0x00e510f0
int FUN_00e510f0() {
  char* s = (char*)gState_16b3c0c;
  if (*(char*)(s + 0x937) != 0) return 0;
  if (FUN_00e00b00()) return 3;
  char* r = (char*)FUN_00b3d4d0();
  int v = *(int*)(r + 0x2c);
  if (v == 1 || v == 2 || *(char*)(s + 0x936) != 0) return 1;
  FUN_00b3d410();
  if (!FUN_00e393b0()) {
    if (!FUN_00e82cd0()) {
      if (!FUN_00e82cc0()) {
        if (!thunk_FUN_00809970()) return (FUN_00e00ac0() == 0) ? 2 + 2 : 2;
        FUN_00b3d3f0(0, 0);
        if (FUN_00e18c70(0)) return 5;
        return (*(char*)(s + 0x938) != 0) ? 5 : 2;
      }
    }
  }
  return 0;
}

// @ 0x00e511b0
void FUN_00e511b0() {
  for (uint32_t* p = (uint32_t*)0x1483f74; (int)p < 0x14851e0; p += 9) {
    uint32_t id = *p;
    void* o = FUN_0067cb20();
    ((void(__thiscall*)(void*, uint32_t, int))Vt(o)[0x2c / 4])(o, id, 0);
  }
}

// @ 0x00e511e0
float FUN_00e511e0(int a, int b) {
  float v = ((1000.0f - (float)(a + b)) * 0.0f + (float)(b - a)) * 0.001f;
  if (v <= -1.0f) v = -1.0f;
  if (v >= 1.0f) v = 1.0f;
  return v;
}

// @ 0x00e51250
int FUN_00e51250(void* owner, int a) {
  void* p = (void*)((int(__thiscall*)(void*))Vt(owner)[0x20 / 4])(owner);
  uint32_t n = 6;
  void* stream = (void*)((int(__thiscall*)(void*))Vt(p)[0x18 / 4])(p);
  EA_IO_WriteUint32(stream, &n, 1, 0);
  char buf[0xa00];
  for (int i = 0; i < 6; ++i) {
    ((cVarListSerializer*)buf)->Ctor(a, (void*)0x15a7d48, 0x1a80d26);
    ((cVarListSerializer*)buf)->Serialize(owner);
    a += 0x10;
  }
  return 1;
}

// @ 0x00e51300
struct Obj51300 { void Write(void* other); };
void Obj51300::Write(void* other) {
  void* self = this;
  uint32_t id = (uint32_t)((int(__thiscall*)(void*))Vt(self)[0x20 / 4])(self);
  void* p = (void*)((int(__thiscall*)(void*))Vt(other)[0x20 / 4])(other);
  void* stream = (void*)((int(__thiscall*)(void*))Vt(p)[0x18 / 4])(p);
  EA_IO_WriteUint32(stream, &id, 1, 0);
  char buf[0xa00];
  ((cVarListSerializer*)buf)->Ctor((int)self, (void*)0x15a7e38, 0x1a80d26);
  ((cVarListSerializer*)buf)->Serialize(other);
}

// @ 0x00e513d0
float FUN_00e513d0(int a, int b, int c, float lo, float hi) {
  float t = (float)FUN_01041cd0((void*)a, (void*)b, (void*)c);
  if (t <= 0.0f) t = 0.0f;
  if (t >= 1.0f) t = 1.0f;
  return (hi - lo) * t + lo;
}

// @ 0x00e51430
int __fastcall FUN_00e51430(int level) {
  float* row;
  if (level == 1000) row = (float*)0x1483e60;
  else {
    int i = 0;
    int* p = (int*)0x1483c34;
    if (level >= 0) { do { p += 7; ++i; } while (*p <= level); }
    row = (float*)(0x1483c14 + i * 0x1c);
  }
  if (level == (int)row[1]) return (int)row[2];
  return (int)(FUN_00e513d0((int)row[1], (int)row[8], level, row[2], row[9]) + 0.5f);
}

// @ 0x00e514c0
void FUN_00e514c0(void* self) {
  char* cg = (char*)gCellGame_16b3c04;
  if (*(char*)(cg + 0x5168) != 0) return;
  void* o = FUN_0067de90(0, 2);
  int r = (int)FUN_007ec160((int)o, 2);
  FUN_007eb820(4);
  char* cg2 = (char*)gCellGame_16b3c04;
  void* dst = *(void**)(r + 0xc);
  *(uint32_t*)dst = *(uint32_t*)(*(int*)(cg2 + 0x5190) + 0x74);
  *(uint32_t*)((char*)dst + 4) = *(uint32_t*)(*(int*)(cg2 + 0x5190) + 0x1c);
  *(uint32_t*)((char*)dst + 0xc) = **(uint32_t**)((char*)self + 0x108);
  if (*(int*)((char*)self + 0xfc) != 0) {
    int local[6] = {0,0,0,0,0,0};
    FUN_00e394f0(0x28b55137, (void*)(*(int*)(cg2 + 0x5190) + 0x10),
                 (char*)self + 0xfc, &local[0], &local[4]);
  }
}

// @ 0x00e51580
void FUN_00e51580(void* self) {
  void* o = FUN_0067de90(0, 3);
  int r = (int)FUN_007ec160((int)o, 3);
  FUN_007eb820(4);
  char* cg = (char*)gCellGame_16b3c04;
  void* dst = *(void**)(r + 0xc);
  *(uint32_t*)dst = *(uint32_t*)(*(int*)(cg + 0x5190) + 0x74);
  *(uint32_t*)((char*)dst + 4) = *(uint32_t*)(*(int*)(cg + 0x5190) + 0x1c);
  *(uint32_t*)((char*)dst + 0xc) = (uint32_t)self;
  uint32_t found = 0;
  for (int i = 0; i < 0xc; ++i) {
    if (gTable_1483e98[i * 2] == (uint32_t)self) { found = gTable_1483e9c[i * 2]; break; }
  }
  int local[8] = {0,0,0,0,0,0,0,0};
  local[0] = found;
  local[1] = 0xb1b104;
  local[2] = gK_150d6d8;
  FUN_00e394f0(0x4ba824f0, (void*)(*(int*)(cg + 0x5190) + 0x10), &local[0], &local[2], &local[6]);
}

// @ 0x00e51650
void FUN_00e51650() {
  char* cg = (char*)gCellGame_16b3c04;
  if (*(char*)(cg + 0x5168) != 0) return;
  void* o = FUN_0067de90(0, 4);
  int r = (int)FUN_007ec160((int)o, 4);
  FUN_007eb820(1);
  void* dst = *(void**)(r + 0xc);
  *(uint32_t*)dst = *(uint32_t*)(*(int*)(cg + 0x5190) + 0x74);
}

// @ 0x00e51690
void FUN_00e51690(int obj) {
  if (*(int*)(obj + 0x358) == -1) SP_sGetSourceLevel();
}

// @ 0x00e516c0
int FUN_00e516c0(int obj) {
  int level = *(int*)(*(int*)((char*)gCellGame_16b3c04 + 0x5190) + 0x1c);
  int* row;
  if (level == 1000) row = (int*)0x1483e60;
  else {
    int i = 0;
    int* p = (int*)0x1483c34;
    if (level >= 0) { do { p += 7; ++i; } while (*p <= level); }
    row = (int*)(0x1483c14 + i * 0x1c);
  }
  int base = row[0];
  int sl = *(int*)(obj + 0x358);
  if (sl == -1) sl = SP_sGetSourceLevel();
  return (sl - base) + 2;
}

// @ 0x00e51720
float FUN_00e51720(int idx) {
  int level = *(int*)(*(int*)((char*)gCellGame_16b3c04 + 0x5190) + 0x1c);
  float* row;
  if (level == 1000) row = (float*)0x1483e60;
  else {
    int i = 0;
    int* p = (int*)0x1483c34;
    if (level >= 0) { do { p += 7; ++i; } while (*p <= level); }
    row = (float*)(0x1483c14 + i * 0x1c);
  }
  float v = row[6] * gTable_1483e7c[idx];
  if (v <= 0.0f) v = 0.0f;
  if (v >= 1.0f) v = 1.0f;
  return v;
}

// @ 0x00e517d0
void __fastcall FUN_00e517d0(char* p) {
  int n = *(int*)(p + 4) + 1;
  *(int*)(p + 4) = n;
}

// @ 0x00e517e0
void __stdcall FUN_00e517e0(float* out) {
  out[0] = gBox_16b3c88;
  out[1] = gBox_16b3c8c;
  out[2] = gBox_16b3c90;
  out[3] = gBox_16b3c94;
  out[4] = gBox_16b3c98;
  out[5] = gBox_16b3c9c;
}
