// Slice s00d57b50 (batch gold6, worker 44). Region 0x00d57b50-0x00d588a0.
// SP city/abandoned-citizen visualizer cluster: vignette spot setup/stop,
// animation recharge walkers, city police update, citizen locomotion ctor,
// heap/vector sort helpers and body-scale range setup.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"
#include <math.h>

typedef unsigned int   u32;
typedef unsigned short u16;
typedef unsigned char  u8;
typedef          int   s32;
typedef          short s16;
typedef          char  s8;
typedef unsigned long long u64;
typedef          long long s64;

// ---- external callees (address in comment) ------------------------------
void* __cdecl FUN_00bd9e80(void* self, u32 idx);       // 0x00bd9e80 (thiscall)
void  __cdecl FUN_00bd9ea0(void* self, int a, int b, int c);  // 0x00bd9ea0 (thiscall)
void* __cdecl FUN_00bd9480(void* self, void* out);     // 0x00bd9480 (thiscall)
void  __cdecl FUN_00af9cf0(void* pos, float r, void* f, float alt); // 0x00af9cf0 SetAtCenter
void  __cdecl FUN_00afdfe0(void* self, float r);       // 0x00afdfe0 EmitRing (thiscall)
void  __cdecl FUN_00bc3170(void* p);                   // 0x00bc3170
void  __cdecl FUN_00bc97f0(u32 a, u32 b, float c, u32 d); // 0x00bc97f0
float __cdecl FUN_00bc9980(float f);                   // 0x00bc9980
void* __cdecl FUN_00b3d380();                          // 0x00b3d380 GameTimeManager
u64   __cdecl FUN_00b316c0(void* self);                // 0x00b316c0 (thiscall)
void* __cdecl FUN_00d995f0(float f, double d, u32 a, void* b, void* c, u32 d2, u32 e, u32 g); // 0x00d995f0
u32   __cdecl FUN_00a68fb0(void* self, u32 n);         // 0x00a68fb0 RandomUint32Uniform (thiscall)
void* __cdecl FUN_00bd7f40(void* self);                // 0x00bd7f40 (thiscall)
void* __cdecl FUN_00af9ff0(void* self, u32 idx);       // 0x00af9ff0 cActionCircle::SlotAt (thiscall)
void* __cdecl FUN_00fcc210(void* self);                // 0x00fcc210 (thiscall)
s32   __cdecl FUN_00c0b780(void* self);                // 0x00c0b780 (thiscall)
s32   __cdecl FUN_00c0b7a0(void* self);                // 0x00c0b7a0 (thiscall)
s32   __cdecl FUN_008e7f80(void* self);                // 0x008e7f80 GetFileCount (thiscall)
void  __cdecl FUN_00ae6690(void* p);                   // 0x00ae6690
void* __cdecl FUN_00b3d350();                          // 0x00b3d350 SP::PlanetModel
void  __cdecl FUN_00b7f250(void* pm, void* out, void* pos, void* dir); // 0x00b7f250 BuildSurfaceOrientation2
char  __cdecl FUN_00ac0730(void* a, void* b);          // 0x00ac0730
void* __cdecl FUN_0067de30();                          // 0x0067de30 PropertyManager
float* __cdecl FUN_0041ea70(void* p);                  // 0x0041ea70 Property::GetFloat (thiscall)

// ======================================================================
// 0x00d57b50 - SP::cCityVisualizer::SetupVignetteSpots. thiscall, ret 4.
// ======================================================================

// @ 0x00d57b50
void __fastcall FUN_00d57b50(void* self, void* /*edx*/, char flag) {
  char* p = (char*)self;
  char* esi = p + 0x488;
  for (int i = 0; i < 4; ++i) {
    char* e = (char*)FUN_00bd9e80(*(void**)(p + 0xaf0), (u32)i);
    if (*(int*)(e + 0x78) != 0) {
      float* o = (float*)(*(float*(__thiscall**)(void*))(*(void***)*(void**)(e + 0x78) + 0x2c / 4))(*(void**)(e + 0x78));
      float cx = o[0], cy = o[1], cz = o[2];
      u8 tmp[12];
      float* b = (float*)FUN_00bd9480(*(void**)(p + 0xaf0), tmp);
      float dx = cx - b[0];
      float dy = cy - b[1];
      float dz = cz - b[2];
      float inv = 1.0f / (float)sqrt((double)(dx * dx + (dy * dy + dz * dz)) + 1e-08);
      float nx = dx * inv;
      float ny = dy * inv;
      float nz = dz * inv;
      float px = nx * -5.0f + cx;
      float py = ny * -5.0f + cy;
      float pz = nz * -5.0f + cz;
      FUN_00af9cf0(&px, 3.0f, &nx, 0.0f);
      FUN_00afdfe0(esi, 1.5f);
      px = nx * -7.0f + px;
      py = ny * -7.0f + py;
      pz = nz * -7.0f + pz;
      FUN_00af9cf0(&px, 7.0f, &nx, 0.0f);
      FUN_00afdfe0(esi - 0x64, 1.5f);

      FUN_00bd9ea0(*(void**)(p + 0xaf0), (u32)i,
                   (*(int*)(esi - 0x14) - *(int*)(esi - 0x18)) / 0x18,
                   (*(int*)(esi + 0x54) - *(int*)(esi + 0x50)) / 0x18);

      int* dst = (int*)(esi + 0x8c);
      int* src = (int*)(e + 8);
      for (int k = 0; k < 2; ++k) {
        if (flag == 0) {
          dst[0] = 0;
          dst[2] = 0;
        } else {
          dst[0] = src[0];
        }
        ++src;
        ++dst;
      }
      *(u32*)(esi - 0xf8) = 0;
      *(u32*)(esi - 0xf0) = 0;
      *(u32*)(esi - 0xec) = 0;
      FUN_00bc3170(esi - 0xe8);
      FUN_00af9cf0(&px, 7.0f, &nx, 0.0f);
      FUN_00afdfe0(esi - 0xc8, 1.5f);
    }
    esi += 0x198;
  }
}

// ======================================================================
// 0x00d57e20 - animation recharge walker. thiscall, ret 4.
// ======================================================================

// @ 0x00d57e20
void __fastcall FUN_00d57e20(void* self, void* /*edx*/, char flag) {
  char* p = (char*)self;
  *(u32*)(p + 0x9f0) = 0;
  if (*(char*)(*(int*)(p + 0xaf0) + 0x2a0) != 0) return;

  int local_4 = 0;
  char* iVar5 = p + 0x390;
  do {
    char* e = (char*)((void*(__thiscall*)(void*, int))FUN_00bd9e80)(*(void**)(p + 0xaf0), local_4);
    if (*(int*)(e + 0x78) != 0) {
      int iVar3 = 0;
      do {
        if (*(char*)(e + 0x20) == 0) {
          int iVar4 = *(int*)(e + 8 + iVar3 * 4);
          int iVar6 = 0;
          if (flag == 0) {
            iVar4 = *(int*)(e + 0x18 + iVar3 * 4);
            iVar6 = *(int*)(e + 0x10 + iVar3 * 4);
            if (iVar4 > 0 && iVar3 == 0) {
              *(int*)(p + 0x9f0) += iVar4;
            }
          } else {
            *(int*)(p + 0x9f0) += iVar4;
            iVar6 = 0;
          }
          *(int*)(iVar5 + 0x184 + iVar3 * 4) += iVar4;
          *(int*)(iVar5 + 0x18c + iVar3 * 4) += iVar6;
        } else {
          *(u32*)(iVar5 + 0x184 + iVar3 * 4) = 0;
          *(u32*)(iVar5 + 0x18c + iVar3 * 4) = 0;
        }
        ++iVar3;
      } while (iVar3 < 2);
    }
    ++local_4;
    iVar5 += 0x198;
  } while (local_4 < 4);
}

// ======================================================================
// 0x00d57ef0 - reseed the vignette instance counter. thiscall, ret 4.
// ======================================================================

// @ 0x00d57ef0
void __fastcall FUN_00d57ef0(void* self, void* /*edx*/, void* arg) {
  char* p = (char*)self;
  int e = *(int*)(p + 0xaf0);
  if (*(char*)(e + 0x648) == 0 || *(char*)(e + 0x2a0) != 0) {
    *(u32*)(p + 0x9f4) = 0;
    return;
  }
  *(u8*)(e + 0x648) = 0;
  int v = *(int*)(*(int*)(p + 0xaf0) + 0x640);
  arg = (void*)*(int*)(*(int*)(p + 0xaf0) + 0x644);
  (void)arg;
  if (v == 1) {
    u32 r = ((u32(__thiscall*)(void*, u32))FUN_00a68fb0)((void*)0x01601760, 2);
    *(u32*)(p + 0x9f4) = r + 3;
    return;
  }
  if (v == 0) {
    u32 r = ((u32(__thiscall*)(void*, u32))FUN_00a68fb0)((void*)0x01601760, 3);
    *(u32*)(p + 0x9f4) = r + 1;
    return;
  }
}

// ======================================================================
// 0x00d57f80 - SP::cCityVisualizer::StopVignetteInstance. thiscall, ret 4.
// ======================================================================

// @ 0x00d57f80
void __fastcall FUN_00d57f80(void* self, void* /*edx*/, void* arg) {
  char* p = (char*)self;
  char* lst = (char*)arg;
  int n = (*(int*)(lst + 0xc) - *(int*)(lst + 8)) >> 2;
  for (int i = 0; i < n; ++i) {
    void** slot = (void**)(*(int*)(lst + 8) + i * 4);
    void* o = *slot;
    if (o == 0 ||
        (*(void* (__thiscall**)(void*, u32))(*(void***)o + 0xc / 4))(o, 0x4f176642) == 0) {
      void* o2 = *(void**)(*(int*)(lst + 8) + i * 4);
      if (o2 != 0) {
        void* c = (*(void* (__thiscall**)(void*, u32))(*(void***)o2 + 0xc / 4))(o2, 0xd0036e08);
        if (c != 0) {
          ((void(__thiscall*)(void*, u32, s32, u32))0x00c12310)(c, 0x2481db0, -1, 0);
          void** vc = (void**)(p + 0xaf0);
          void* pi = *vc;
          if (pi != 0 &&
              (*(u8(__thiscall**)(void*))(*(void***)pi + 0x2c / 4))(pi) == 0) {
            void* hall = (void*)((void*(__thiscall*)(void*))0x00bd9b40)(pi);
            float f = 2.0f;
            float g = 1.0f;
            void* pt = (*(void* (__thiscall**)(void*, float, float))(*(void***)hall + 0x8c / 4))(hall, g, f);
            ((void(__thiscall*)(void*, int, void*, float, float))0x00c1c1d0)(c, 2, pt, g, f);
          }
        }
      }
    } else {
      FUN_00bc97f0(0x800, 0, 3.402823466e38f, 0);
    }
  }
}

// ======================================================================
// 0x00d58080 - walk city grid slots and emit rings. thiscall.
// ======================================================================

// @ 0x00d58080
void __fastcall FUN_00d58080(void* self, void* /*edx*/) {
  char* p = (char*)self;
  int outer = 0;
  int total = (*(int*)(p + 0xbc0) - *(int*)(p + 0xbbc)) / 0x1c;
  if (total <= 0) return;
  int off = 0;
  do {
    char* e = (char*)(*(int*)(p + 0xbbc) + off);
    int cnt = *(int*)(e + 0xc) - *(int*)(e + 8);
    if ((cnt & 0xfffffffc) > 0) {
      int k = 0;
      do {
        FUN_00bc97f0(0x8000, 0, 1.0f, 0);
        ++k;
      } while (k < (*(int*)(e + 0xc) - *(int*)(e + 8)) >> 2);
    }
    off += 0x1c;
    ++outer;
  } while (outer < (*(int*)(p + 0xbc0) - *(int*)(p + 0xbbc)) / 0x1c);
}

// ======================================================================
// 0x00d581b0 - SP::cCityVisualizer::UpdatePolice. thiscall.
// ======================================================================

// @ 0x00d581b0
void __fastcall FUN_00d581b0(void* self, void* /*edx*/) {
  char* p = (char*)self;
  if (*(void**)(p + 0xa58) != 0) {
    void* pi = *(void**)(p + 0xa58);
    void* q = (*(void* (__thiscall**)(void*))(*(void***)pi + 0xc / 4))(pi);
    if ((*(u8(__thiscall**)(void*))(*(void***)q + 0x2c / 4))(q) != 0 ||
        FUN_008e7f80(*(void**)(p + 0xa58)) == 2) {
      void* old = *(void**)(p + 0xa58);
      *(u32*)(p + 0xa58) = 0;
      if (old != 0) {
        (*(void(__thiscall**)(void*))(*(void***)old + 0x64 / 4))(old);
      }
    }
  }
  if (*(u32*)(p + 0xa58) == 0) {
    int n = (*(int*)(p + 0xacc) - *(int*)(p + 0xac8)) >> 2;
    int i = 0;
    if (n > 0) {
      do {
        char* o = *(char**)(*(int*)(p + 0xac8) + i * 4);
        if (o != 0 &&
            (*(u8(__thiscall**)(char*))(*(void***)o + 0x2c / 4))(o) == 0 &&
            FUN_008e7f80(o + 0x5a8) != 2 &&
            (*(u32*)(*(int*)(o + 0xb4c) + 0x5fc) & 0x80000) != 0) {
          FUN_00ae6690(o + 0x5a8);
          break;
        }
        ++i;
      } while (i < n);
    }
  }
  if (*(u32*)(p + 0xa58) == 0) {
    int n = (*(int*)(p + 0xae0) - *(int*)(p + 0xadc)) >> 2;
    int i = 0;
    if (n > 0) {
      do {
        char* o = *(char**)(*(int*)(p + 0xadc) + i * 4);
        if (o != 0 &&
            (*(u8(__thiscall**)(char*))(*(void***)o + 0x2c / 4))(o) == 0 &&
            FUN_008e7f80(o + 0x5a8) != 2 &&
            FUN_00c0b780(o) != 0 &&
            FUN_00c0b7a0(o) == 0) {
          void* old = *(void**)(p + 0xa58);
          void* np = o + 0x5a8;
          if (np != old) {
            if (np != 0) {
              (*(void(__thiscall**)(void*))(*(void***)np + 0x60 / 4))(np);
            }
            *(void**)(p + 0xa58) = np;
            if (old != 0) {
              (*(void(__thiscall**)(void*))(*(void***)old + 0x64 / 4))(old);
            }
          }
          break;
        }
        ++i;
      } while (i < n);
    }
  }
  *(u32*)(p + 0xa60) = (*(int*)(p + 0xa58) != 0) ? 0 : 5;
}

// ======================================================================
// 0x00d58330 - SP::cAbandonedCitizenVisualizer::OnTick. thiscall, ret 8.
// ======================================================================

// @ 0x00d58330
void __fastcall FUN_00d58330(void* self, void* /*edx*/, s32 p2, u32 p3) {
  char* p = (char*)self;
  int n = (*(int*)(p + 8) - *(int*)(p + 4)) >> 2;
  float dt = (float)((double)(s64)(((u64)p2 | ((u64)p3 << 32)) & 0x7fffffffffffffffULL) *
                     0.001);
  (void)dt;
  float f = (float)((double)p3 * 0.001);
  if (n <= 0) return;
  for (int i = 0; i < n; ++i) {
    char* c = *(char**)(*(int*)(p + 4) + i * 4);
    if (*(char*)(c + 0xb63) == 0 && *(int*)(*(int*)(c + 0xb4c)) != 0) {
      u32 r = (u32)FUN_00bc9980(f);
      void* gt = FUN_00b3d380();
      u64 t = FUN_00b316c0(gt);
      int* q = *(int**)(c + 0xb4c);
      FUN_00d995f0(f, (double)t * 0.0010000000474974513, (u32)q[0], c, q + 0x74,
                   *(u32*)((char*)q + 0x5e8), 0, r);
    }
  }
}

// ======================================================================
// 0x00d58460 - walk objects and notify non-flagged ones. thiscall.
// ======================================================================

// @ 0x00d58460
void __fastcall FUN_00d58460(void* self, void* /*edx*/) {
  u32 i = 0;
  char* p = (char*)self;
  int n = *(int*)(p + 8) - *(int*)(p + 4);
  if ((u32)(n >> 2) == 0) return;
  do {
    char* o = *(char**)(*(int*)(p + 4) + i * 4);
    if (*(char*)(o + 0x137) == 0) {
      (*(void(__thiscall**)(char*, int))(*(void***)o + 0xc8 / 4))(o, 1);
    } else {
      ++i;
    }
  } while (i < (u32)((*(int*)(p + 8) - *(int*)(p + 4)) >> 2));
}

// ======================================================================
// 0x00d584b0 - Simulator::cCitizenLocomotion ctor. thiscall, ret 4.
// ======================================================================

// @ 0x00d584b0
void* __fastcall FUN_00d584b0(void* self, void* /*edx*/, void* arg) {
  char* p = (char*)self;
  void* old = 0;
  *(u32*)(p + 8) = 0x13ec458;
  *(u32*)(p + 0xc) = (u32)old;
  *(u32*)p = 0x147b9bc;
  *(u32*)(p + 8) = 0x147b9ac;
  *(u32*)(p + 0x10) = (u32)old;
  if (arg != old) {
    if (arg != 0) {
      (*(void(__thiscall**)(void*))(*(void***)arg + 0))(arg);
    }
    *(void**)(p + 0x10) = arg;
    if (old != 0) {
      (*(void(__thiscall**)(void*))(*(void***)old + 1))(old);
    }
  }
  *(u8*)(p + 0x14) = 0;
  return p;
}

// ======================================================================
// 0x00d58510 - build a surface orientation or copy a reference matrix.
// thiscall, ret 0xc.
// ======================================================================

// @ 0x00d58510
void** __fastcall FUN_00d58510(void* self, void* /*edx*/, void* out, void* obj,
                               float* pos) {
  (void)self;
  float dot = pos[0] * pos[0] + pos[1] * pos[1] + pos[2] * pos[2];
  if (dot > 0.0f) {
    float* o = (float*)(*(float*(__thiscall**)(void*))(*(void***)obj + 0x2c / 4))(obj);
    float dz = pos[2] - o[2];
    float dx = pos[0] - o[0];
    float dy = pos[1] - o[1];
    float d2 = dz * dz + dy * dy + dx * dx;
    if (d2 > 0.0f) {
      float dir[3];
      dir[0] = dx; dir[1] = dy; dir[2] = dz;
      float* o2 = (float*)(*(float*(__thiscall**)(void*, float*))(*(void***)obj + 0x2c / 4))(obj, dir);
      void* pm = FUN_00b3d350();
      FUN_00b7f250(out, pm, pos, dir);
      return (void**)out;
    }
  }
  float* m = (float*)(*(float*(__thiscall**)(void*))(*(void***)obj + 0x30 / 4))(obj);
  ((float*)out)[0] = m[0];
  ((float*)out)[1] = m[1];
  ((float*)out)[2] = m[2];
  ((float*)out)[3] = m[3];
  return (void**)out;
}

// ======================================================================
// 0x00d58610 - heap-sort-like sift for a pointer vector. thiscall.
// ======================================================================

// @ 0x00d58610
void __cdecl FUN_00d58610(void** lo, void** hi) {
  void** p = lo;
  if (lo == hi) return;
  u32 cmpobj;
  while (1) {
    p = p + 1;
    if (p == hi) break;
    void* v = *p;
    void** q;
    if (v != 0) {
      (*(void(__thiscall**)(void*))(*(void***)v + 0))(v);
    }
    q = p;
    for (; q != lo; --q) {
      void* c1 = q[-1];
      void* a = c1 ? (char*)c1 + 0xc0 : 0;
      void* b = v ? (char*)v + 0xc0 : 0;
      if (((char(__thiscall*)(void*, void*, void*))FUN_00ac0730)(&cmpobj, b, a) == 0) break;
      void* up = q[-1];
      void* cur = *q;
      if (up != cur) {
        if (up != 0) {
          (*(void(__thiscall**)(void*))(*(void***)up + 0))(up);
        }
        *q = up;
        if (cur != 0) {
          (*(void(__thiscall**)(void*))(*(void***)cur + 1))(cur);
        }
      }
    }
    void* cur = *q;
    if (v != cur) {
      if (v != 0) {
        (*(void(__thiscall**)(void*))(*(void***)v + 0))(v);
      }
      *q = v;
      if (cur != 0) {
        (*(void(__thiscall**)(void*))(*(void***)cur + 1))(cur);
      }
    }
    if (v != 0) {
      (*(void(__thiscall**)(void*))(*(void***)v + 1))(v);
    }
  }
}

// ======================================================================
// 0x00d58700 - shift-down helper for a pointer vector. thiscall.
// ======================================================================

// @ 0x00d58700
void __fastcall FUN_00d58700(void* self, void* /*edx*/, void** lo, void** hi) {
  (void)self;
  void** p = lo;
  if (lo == hi) return;
  while (1) {
    void* v = *p;
    void** q = p;
    if (v != 0) {
      (*(void(__thiscall**)(void*))(*(void***)v + 0))(v);
    }
    while (1) {
      void* c1 = q[-1];
      void* a = (c1 == 0) ? 0 : (char*)c1 + 0xc0;
      void* b = (v == 0) ? 0 : (char*)v + 0xc0;
      if (FUN_00ac0730(b, a) == 0) break;
      void* up = q[-1];
      void* cur = *q;
      if (up != cur) {
        if (up != 0) {
          (*(void(__thiscall**)(void*))(*(void***)up + 0))(up);
        }
        *q = up;
        if (cur != 0) {
          (*(void(__thiscall**)(void*))(*(void***)cur + 1))(cur);
        }
      }
      --q;
    }
    void* cur = *q;
    if (v != cur) {
      if (v != 0) {
        (*(void(__thiscall**)(void*))(*(void***)v + 0))(v);
      }
      *q = v;
      if (cur != 0) {
        (*(void(__thiscall**)(void*))(*(void***)cur + 1))(cur);
      }
    }
    if (v != 0) {
      (*(void(__thiscall**)(void*))(*(void***)v + 1))(v);
    }
    ++p;
    if (p == hi) break;
  }
}

// ======================================================================
// 0x00d587e0 - sift-up helper for a pointer vector. thiscall.
// ======================================================================

// @ 0x00d587e0
void __fastcall FUN_00d587e0(void* self, void* /*edx*/, void** base, s32 lo, s32 hi,
                             void* v) {
  (void)self;
  void** arr = base;
  while (hi > lo) {
    s32 parent = (hi - 1) >> 1;
    void* a = (v == 0) ? 0 : (char*)v + 0xc0;
    void* up = arr[parent];
    void* b = (up == 0) ? 0 : (char*)up + 0xc0;
    if (FUN_00ac0730(b, a) == 0) break;
    void* pv = arr[parent];
    void* cur = arr[hi];
    if (pv != cur) {
      if (pv != 0) {
        (*(void(__thiscall**)(void*))(*(void***)pv + 0))(pv);
      }
      arr[hi] = pv;
      if (cur != 0) {
        (*(void(__thiscall**)(void*))(*(void***)cur + 1))(cur);
      }
    }
    hi = parent;
  }
  void* cur = arr[hi];
  if (v != cur) {
    if (v != 0) {
      (*(void(__thiscall**)(void*))(*(void***)v + 0))(v);
    }
    arr[hi] = v;
    if (cur != 0) {
      (*(void(__thiscall**)(void*))(*(void***)cur + 1))(cur);
    }
  }
  if (v != 0) {
    (*(void(__thiscall**)(void*))(*(void***)v + 1))(v);
  }
}

// ======================================================================
// 0x00d588a0 - SP::SetUpCitizenBodyScaleRanges.
// ======================================================================

// @ 0x00d588a0
void __cdecl FUN_00d588a0(int* obj, float* out) {
  float local_c = *(float*)((char*)obj + 0x554);
  float local_8 = *(float*)((char*)obj + 0x558);
  float local_10 = (local_8 <= local_c) ? local_c : local_8;
  float local_18 = 0.75f;
  float val = *(float*)0x013f08e4;      // default property value
  float e = 0.0f;                        // prop 0x4dbf459 result
  void* holder = 0;
  int* pm = (int*)FUN_0067de30();
  if (holder != 0) {
    holder = 0;
    (*(void(__thiscall**)(void*))(*(void***)holder + 1))(holder);
  }
  if (holder != 0) {
    holder = 0;
    (*(void(__thiscall**)(void*))(*(void***)holder + 1))(holder);
  }
  if ((*(u8(__thiscall**)(int*, u32, void**))(*(int**)pm + 0x30 / 4))(pm, 0xb6a5c63d, &holder) != 0 &&
      holder != 0) {
    int* p1 = 0;
    if ((*(u8(__thiscall**)(void*, u32, int**))(*(int**)holder + 0x24 / 4))(holder, 0x4dbf457, &p1) != 0 &&
        *(short*)((char*)p1 + 0x12) == 0xd) {
      float* f = FUN_0041ea70(p1);
      *out = *f;
    }
    if (holder != 0) {
      int* p2 = 0;
      if ((*(u8(__thiscall**)(void*, u32, int**))(*(int**)holder + 0x24 / 4))(holder, 0x4dbf458, &p2) != 0 &&
          *(short*)((char*)p2 + 0x12) == 0xd) {
        float* f = FUN_0041ea70(p2);
        val = *f;
      }
      if (holder != 0) {
        int* p3 = 0;
        if ((*(u8(__thiscall**)(void*, u32, int**))(*(int**)holder + 0x24 / 4))(holder, 0x4dbf459, &p3) != 0 &&
            *(short*)((char*)p3 + 0x12) == 0xd) {
          float* f = FUN_0041ea70(p3);
          e = *f;
        }
        if (holder != 0) {
          int* p4 = 0;
          if ((*(u8(__thiscall**)(void*, u32, int**))(*(int**)holder + 0x24 / 4))(holder, 0x4dbf45a, &p4) != 0 &&
              *(short*)((char*)p4 + 0x12) == 0xd) {
            float* f = FUN_0041ea70(p4);
            val = *f;
          }
        }
      }
    }
  }
  if (local_10 <= local_18) {
    if (val < local_18) {
      *out = val / local_18;
    }
  } else {
    *out = e / local_18;
  }
  if (holder != 0) {
    (*(void(__thiscall**)(void*))(*(void***)holder + 1))(holder);
  }
}
