// Slice s00e51820 (batch bfs0, slice 33). Region 0xe51820-0xe5205f.
// cCellFluidMap / cell effect query + spawn helpers, box-size multiplier table.
// Optimised: /O2 /MD /Gy /TP /arch:SSE /fp:fast.
#include "types.h"

static inline void** Vt(void* p) { return *(void***)p; }

extern void*  gCellGame_16b3c04;   // cCellGame*
extern void*  gCellGfx_16b3c08;    // cCellGfx*
extern float  gOne_1485720, gHalf_1471064, gQuarter_13eb8a0,
              gEighth_1486d94, gSixteenth_13f115c, g32nd_140e964;
extern float  gVec_16b3c28[4];
extern float  gVec_15a7c4c[4];

extern "C" void  __cdecl SP_FluidParticlesSampleVelMagnitude(void* fluid, float* out); // 0xe4e590
extern "C" void* __cdecl SP_FluidParticlesSampleVelocity(float* out, void* fluid, float* in); // 0xe4e3c0
struct CellList {
  int   Head();       // 0xb72160
  char* Find(int id); // 0xb72210
};
extern "C" int   __fastcall SP_sGetSourceLevel(void* obj, int level); // 0xe4ee60
extern "C" int   __cdecl FUN_00e4f750(int a, int b, int c, int d, int e, int f, int g); // 0xe4f750
extern "C" int   __cdecl FUN_00e4dbc0(void* fluid, void* a, void* b, float c, float d); // 0xe4dbc0
extern "C" int   __cdecl FUN_00e4ec30(void* fluid, int id); // 0xe4ec30

// @ 0x00e51820
void __stdcall FUN_00e51820(float* p) {
  float local[3];
  local[0] = p[0];
  local[1] = p[1];
  local[2] = p[2];
  SP_FluidParticlesSampleVelMagnitude(*(void**)((char*)gCellGame_16b3c04 + 0x4108), local);
}

// @ 0x00e51870
float* __stdcall FUN_00e51870(float* out, float* in) {
  float local[3];
  float tmp[3];
  local[0] = in[0];
  local[1] = in[1];
  local[2] = in[2];
  float* r = (float*)SP_FluidParticlesSampleVelocity(tmp, *(void**)((char*)gCellGame_16b3c04 + 0x4108), local);
  out[0] = r[0];
  out[1] = r[1];
  out[2] = r[2];
  return out;
}

// @ 0x00e518d0
void __stdcall FUN_00e518d0(float* out, int) {
  float one = gOne_1485720;
  out[0] = one;
  out[1] = one;
  out[2] = one;
  out[3] = one;
}

// @ 0x00e51900
int __fastcall FUN_00e51900(char* self) {
  int id = *(int*)(self + 0x248);
  if (id == 0) return 0;
  if (*(int*)(self + 0xfc) == 0) return 0;
  char* g = (char*)gCellGfx_16b3c08 + 0x168;
  char* rf = ((CellList*)g)->Find(id); int r = (int)rf;
  return *(int*)(r + 0x24);
}

// @ 0x00e51930
static void FUN_00e51930(char* self) {
  int id = *(int*)(self + 0x248);
  if (id != 0 && *(int*)(self + 0xfc) != 0) {
    char* g = (char*)gCellGfx_16b3c08 + 0x168;
    char* rf = ((CellList*)g)->Find(id); int r = (int)rf;
    int o = *(int*)(r + 0x24);
    if (o) {
      void* sub = *(void**)(o + 0x190);
      ((void(__thiscall*)(void*, int, int, int))Vt(sub)[0x40 / 4])(sub, o, 2, 1);
    }
  }
  int idx = *(int*)((char*)gCellGfx_16b3c08 + 0x16254);
  *(uint32_t*)((char*)gCellGfx_16b3c08 + 0x16214 + idx * 4) = *(uint32_t*)self;
  ++*(int*)((char*)gCellGfx_16b3c08 + 0x16254);
}

// @ 0x00e51990
void FUN_00e51990(char* ctx, char* vec) {
  for (int i = 0; i < (*(int*)(vec + 0xb4) - *(int*)(vec + 0xb0)) >> 2; ++i) {
    void* o = *(void**)(*(int*)(vec + 0xb0) + i * 4);
    if (!((bool(__thiscall*)(void*))Vt(o)[0x10 / 4])(o)) {
      ((void(__thiscall*)(void*))Vt(o)[4 / 4])(o);
      *(uint32_t*)(*(int*)(vec + 0xb0) + i * 4) = 0;
      int b = *(int*)(vec + 0xb0);
      *(uint32_t*)(b + i * 4) = *(uint32_t*)(b + (((*(int*)(vec + 0xb4) - b) >> 2) - 1) * 4);
      *(int*)(vec + 0xb4) -= 4;
      --i;
    } else {
      ((void(__thiscall*)(void*, void*))Vt(o)[0x18 / 4])(o, ctx + 0x48);
    }
  }
}

// @ 0x00e51a40  spawn effects along a segment (partial: mid-section not fully reconstructed)
int FUN_00e51a40(int a, int b, int* out, int countIn) {
  (void)a; (void)b; (void)countIn;
  if (out) *out = 0;
  return 0;
}

// @ 0x00e51ee0
int FUN_00e51ee0(int p1, float p2, int p3, int p4, int p5, int p6, int p7, int p8,
                 float p9, float p10, float* p11, float* p12, float* p13, int p14,
                 uint8_t p15, int p16) {
  void* g = (void*)((char*)gCellGame_16b3c04 + 0x54);
  CellList* list = (CellList*)((char*)gCellGame_16b3c04 + 0x54);
  int h = list->Head();
  char* o = list->Find(h);
  (void)g;
  *(int*)(o + 0x28) = p3;
  *(int*)(o + 0x24) = p1;
  *(int*)(o + 0x30) = p5;
  *(int*)(o + 0x2c) = p4;
  *(float*)(o + 0x1c) = p2;
  *(float*)(o + 0x20) = p2;
  *(int*)(o + 0x38) = p7;
  *(int*)(o + 0x34) = p6;
  *(int*)(o + 0x40) = p8;
  *(float*)(o + 0x3c) = p9;
  *(float*)(o + 0x44) = p10;
  float* v11 = p11 ? p11 : gVec_16b3c28;
  *(float*)(o + 0x48) = v11[0];
  *(float*)(o + 0x4c) = v11[1];
  *(float*)(o + 0x50) = v11[2];
  float* v12 = p12 ? p12 : gVec_16b3c28;
  *(float*)(o + 0x54) = v12[0];
  *(float*)(o + 0x58) = v12[1];
  *(float*)(o + 0x5c) = v12[2];
  float* v13 = p13 ? p13 : gVec_15a7c4c;
  *(float*)(o + 0x60) = v13[0];
  *(float*)(o + 0x64) = v13[1];
  *(float*)(o + 0x68) = v13[2];
  *(float*)(o + 0x6c) = v13[3];
  *(int*)(o + 0x70) = p14;
  *(uint8_t*)(o + 0x74) = p15;
  *(int*)(o + 0x78) = p16;
  *(int*)(o + 4) = 0;
  *(uint8_t*)(o + 8) = 0;
  return h;
}

// @ 0x00e51ff0
float __cdecl FUN_00e51ff0(int level) {
  void* o = *(void**)((char*)gCellGame_16b3c04 + 0x5190);
  int lv = *(int*)((char*)o + 0x1c);
  int d = level - SP_sGetSourceLevel(o, lv);
  if (d <= -2) return 1.0f;
  if (d >= 5) return g32nd_140e964;
  switch (d) {
    case -1: return 1.0f;
    case 0:  return gHalf_1471064;
    case 1:  return gQuarter_13eb8a0;
    case 2:  return gEighth_1486d94;
    case 3:  return gSixteenth_13f115c;
    case 4:  return g32nd_140e964;
    default: return gHalf_1471064;
  }
}
