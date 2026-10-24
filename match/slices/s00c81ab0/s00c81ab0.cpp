// Slice s00c81ab0 (batch gold6, worker 44). Region 0x00c81ab0-0x00c82900.
// SP::cSimPlanetLowLOD plant/animal cell simulation cluster: SetSimPlantAt,
// per-cell plant re-roll (FUN_00c81f40), SetAnimalDensity, SetSimAnimalAt,
// random reseed helper and animal seeding helper.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"
#include <math.h>

typedef unsigned int   u32;
typedef unsigned short u16;
typedef unsigned char  u8;
typedef          int   s32;
typedef          short s16;
typedef          char  s8;

// ---- external callees (address in comment) ------------------------------
void* __cdecl SP_PlanetModel();                        // 0x00b3d350 SP::PlanetModel
void  __cdecl FUN_00b3d450();                          // 0x00b3d450
void  __cdecl FUN_00b3d420(void* a);                   // 0x00b3d420
void  __cdecl FUN_00b3d3b0(void* a);                   // 0x00b3d3b0 (also 0-arg overload)
void  __cdecl FUN_00b2bbe0();                          // 0x00b2bbe0
void* __cdecl FUN_00b90410(void* cell);                // 0x00b90410
s32   __cdecl FUN_00b8f860();                          // 0x00b8f860
u32   __cdecl FUN_00b2a750(u32 a);                     // 0x00b2a750
void* __cdecl FUN_00b3d3e0(void* a, void* b, u32 c, u32 d, u32 e, u32 f); // 0x00b3d3e0 SP::EventLog
s32   __cdecl FUN_00401090(void* key);                 // 0x00401090 GetSetting9
void* __cdecl FUN_004df550(void* key);                 // 0x004df550 GetProfile (thiscall, ecx=key)
void  __cdecl FUN_00c732c0(void* key);                 // 0x00c732c0
void* __cdecl FUN_00c80110(void* p);                   // 0x00c80110
void* __cdecl FUN_0103de50(void* p);                   // 0x0103de50
void* __cdecl FUN_010666a0(void* a);                   // 0x010666a0
void  __cdecl FUN_0106dcd0(void* a);                   // 0x0106dcd0 (thiscall, ecx=a)
void* __cdecl FUN_00c71e30(void* a);                   // 0x00c71e30 (thiscall, ecx=a)
void* __cdecl FUN_01021300();                          // 0x01021300 GetPlayerEmpire
s32   __cdecl FUN_00c7f390();                          // 0x00c7f390
void  __cdecl FUN_00c7ff60(void* p);                   // 0x00c7ff60 (thiscall, ecx=p)
void  __cdecl FUN_00c805b0(void* self, void* pos, void* vec, u32 a); // 0x00c805b0 (thiscall)
u8    __cdecl FUN_00c772c0(void* self, void* id);      // 0x00c772c0 (thiscall, bool)
void  __cdecl FUN_00c77bf0(void* self, void* id);      // 0x00c77bf0 (thiscall)
void* __cdecl FUN_00b3d300();                          // 0x00b3d300 SP::NounManager
void* __cdecl FUN_00f67d90(void* a);                   // 0x00f67d90 GetCurrentTerrainSphere (thiscall)
void  __cdecl FUN_00f47380(void* p);                   // 0x00f47380 operator_delete_array
u32   __cdecl FUN_00936090();                          // 0x00936090 SetSeed (thiscall)
u32   __cdecl FUN_00a68fb0(void* self, u32 n);         // 0x00a68fb0 RandomUint32Uniform
double __cdecl FUN_a68fd0(void* self);                 // 0x00a68fd0 RandomDoubleUniform
void* __cdecl FUN_00705250(void* a, void* b, void* c);// 0x00705250 copy_impl
void* __cdecl FUN_00dd8640(void* self, u32 a, u32 b, u32 c, u32 d, u32 e, u32 f); // PostFeedbackEvent

// SP helpers referenced by address.
u32   __cdecl SP_SetPlantDensity(void* self, void* dens, void* pos, int a, void* out);  // placeholder

// ======================================================================
// Forward decls for intra-slice functions.
// ======================================================================
void __fastcall FUN_00c81f40(void* self, void* /*edx*/, void* arg);
void __fastcall FUN_00c821b0(void* self, void* /*edx*/, void* a, void* b, int c, void* d);

extern "C" {
  // 0x01694c00 / 0x01694c04 random state singletons (EA::Random).
}

// ======================================================================
// 0x00c81ab0 - SP::cSimPlanetLowLOD::SetSimPlantAt. thiscall.
// ======================================================================

// @ 0x00c81ab0
u32 __fastcall FUN_00c81ab0(void* self, void* /*edx*/, void* arg1, float* pos,
                            char flag) {
  char* p = (char*)self;
  int* key = (int*)arg1;              // species/resource key (3 dwords)
  float x = pos[0];
  float y = pos[1];
  float z = pos[2];

  // Early-out: exact match against the "invalid position" sentinel.
  if (x == *(float*)0x01694bac) {
    if (y == *(float*)0x01694bb0) {
      if (z == *(float*)0x01694bb4) {
        return 1;
      }
    }
  }
  // Early-out: key equals sentinel.
  if (key[0] == *(int*)0x01694bb8 && key[1] == *(int*)0x01694bbc &&
      key[2] == *(int*)0x01694bc0) {
    return 1;
  }

  // iVar15 = cell array base (mCubeSim at +0x4c, +0x13c -> array).
  int* arr = *(int**)(*(int*)(p + 0x4c) + 0x13c);
  int lo = arr[0xbc / 4];
  int hi = arr[0xc0 / 4];
  int cubeCount = (hi - lo) / 12;

  float ax = (float)fabs(x);
  float ay = (float)fabs(y);
  float az = (float)fabs(z);

  int local_20, local_1c, local_18;
  if (az < ax || az < ay) {
    if (ay < ax) {
      local_20 = (int)((y / x + 1.0) * 2.0);
      local_1c = (int)((z / ax + 1.0) * 2.0);
      local_18 = (x < 0.0f) ? 3 : 2;
    } else {
      local_20 = (int)((z / y + 1.0) * 2.0);
      local_1c = (int)((x / ay + 1.0) * 2.0);
      local_18 = (y < 0.0f) ? 5 : 4;
    }
  } else {
    local_20 = (int)((x / z + 1.0) * 2.0);
    local_1c = (int)((y / az + 1.0) * 2.0);
    local_18 = (z < 0.0f) ? 1 : 0;
  }
  if (local_20 == 4) local_20 = 3;
  if (local_1c == 4) local_1c = 3;

  int* dens = &arr[(local_1c + local_18 * 4) * 4 + local_20];

  int* vec = 0;
  int* vecEnd = 0;
  u32 vecCap = 0;
  ((void(__thiscall*)(void*, void*, void*, u32))FUN_00c805b0)(p + 0x50, pos, &vec, 0);
  if ((u32)((char*)vecEnd - (char*)vec) / 16 < 3) {
    ((void(__thiscall*)(void*, void*, void*, u32))FUN_00c805b0)(p + 0x50, pos, &vec, 1);
  }
  if (vec != vecEnd && vec[0] == local_20 && vec[1] == local_1c &&
      vec[2] == local_18 && (int*)vec[3] == dens) {
    ((void(__thiscall*)(void*))FUN_00c7ff60)(vec);
  }
  int* first = vec;
  FUN_00c821b0(p, 0, dens, key, 1, 0);  // SetPlantDensity
  if (*dens < 3 && first != vecEnd) {
    int* dens2 = (int*)first[3];
    ((void(__thiscall*)(void*))FUN_00c7ff60)(first);
    FUN_00c821b0(p, 0, dens2, key, 1, 0);
    first = vec;
  }

  FUN_00b3d3b0(0);
  FUN_00b2bbe0();
  FUN_00b3d420(key);
  u32 ret = 0;
  char* cell = (char*)FUN_00b90410(key);
  if (cell != 0) {
    u32 kind = 0;
    s32 k = FUN_00b8f860();
    if (k == 0x29c388a) kind = 2;
    else if (k == 0x3a8be428) kind = 4;
    else if (k == 0x6d60a1cc) kind = 1;
    FUN_00b3d3b0((void*)kind);
    ret = FUN_00b2a750(kind);
  }

  if (flag != 0) {
    int n = *(int*)((char*)arr + 0xc0) - *(int*)((char*)arr + 0xbc);
    u32 cnt = (u32)(n / 12);
    if ((u32)((hi - lo) / 12) < cnt && (cnt % 3 == 0) &&
        (*(u32*)((char*)arr + 0x2c) & 0x800) == 0) {
      *(u32*)(p + 0x1f8) = 1;   // mExtinctionInfoMap field
      char* nm = (char*)FUN_00b3d300();
      void* sphere = (void*)0;
      (void)nm; (void)sphere;
      // UI feedback event path.
      FUN_00c772c0(nm, (void*)0x541a716);
    }
  }
  if (first != 0 && first[-1] != 0) {
    FUN_00f47380(first);
  }
  return ret;
}

// ======================================================================
// 0x00c81f40 - per-cell plant re-roll helper. thiscall.
// ======================================================================

// @ 0x00c81f40
void __fastcall FUN_00c81f40(void* self, void* /*edx*/, void* arg) {
  char* p = (char*)self;
  int* key = (int*)arg;
  if (key[0] == 1) return;

  int* arr = *(int**)(*(int*)(p + 0x4c) + 0x13c);
  int n = (*(int*)((char*)arr + 0xc0) - *(int*)((char*)arr + 0xbc)) / 12;
  if (n == 0) return;

  FUN_00b3d420(0);
  u32 r6 = FUN_00a68fb0((void*)0x01694c00, 3);
  u32 r7 = FUN_00a68fb0((void*)0x01694c00, 3);
  u32 r8 = FUN_00a68fb0((void*)0x01694c00, 3);

  int vecA = *(int*)((char*)arr + 0x114) - *(int*)((char*)arr + 0x110);
  int vecB = *(int*)((char*)arr + 0xfc) - *(int*)((char*)arr + 0xf8);
  if ((vecA >> 2) == n && (vecB >> 2) == n) {
    double d15 = FUN_a68fd0((void*)0x01694c04);
    double d16 = FUN_a68fd0((void*)0x01694c04);
    double d17 = FUN_a68fd0((void*)0x01694c04);
    for (int i = 0; i < n; ++i) {
      char* cell = (char*)(*(int*)((char*)arr + 0xbc) + i * 12);
      float fv = *(float*)(*(int*)((char*)arr + 0x110) + i * 4);
      int  iv = *(int*)(*(int*)((char*)arr + 0xf8) + i * 4);
      float sc = *(float*)((char*)arr + 0x10c);
      FUN_00b90410(cell);
      s32 k = FUN_00b8f860();
      double dv = d16; u32 rv = r7;
      if (k == 0x29c388a) { /* default */ }
      else if (k == 0x3a8be428) { dv = d17; rv = r8; }
      else if (k == 0x6d60a1cc) { dv = d15; rv = r6; }
      else continue;
      if (iv == (int)rv && (float)dv < fv * sc) {
        FUN_00c821b0(p, 0, key, cell, 1, 0);
      }
    }
    return;
  }

  int la = 0, lb = 0, lc = 0;
  for (int i = 0; i < n; ++i) {
    char* cell = (char*)(*(int*)((char*)arr + 0xbc) + i * 12);
    FUN_00b90410(cell);
    s32 k = FUN_00b8f860();
    int hit = 0;
    if (k == 0x29c388a) { hit = (la == (int)r7); ++la; }
    else if (k == 0x3a8be428) { hit = (lb == (int)r8); ++lb; }
    else if (k == 0x6d60a1cc) { hit = (lc == (int)r6); ++lc; }
    if (hit) {
      FUN_00c821b0(p, 0, key, cell, 1, 0);
    }
  }
}

// ======================================================================
// 0x00c821b0 - SP::cSimPlanetLowLOD::SetAnimalDensity. thiscall.
// ======================================================================

// @ 0x00c821b0
void __fastcall FUN_00c821b0(void* self, void* /*edx*/, void* a2, void* a3,
                             int a4, void* a5) {
  char* p = (char*)self;
  int* dens = (int*)a2;     // density record ptr
  int* key = (int*)a3;      // species key
  int pi = a4;
  int* out = (int*)a5;

  int* arr = *(int**)(*(int*)(p + 0x4c) + 0x13c);
  int* begin = *(int**)((char*)arr + 0xd0);
  int* end = *(int**)((char*)arr + 0xd4);
  int* found = begin;
  while (found != end) {
    if (found[0] == key[0] && found[1] == key[1] && found[2] == key[2]) break;
    found += 3;
  }
  if (found == end && (u32)((char*)end - (char*)begin) / 12 < 9) {
    FUN_00401090(key);
    if (FUN_004df550(key) != 0) {
      FUN_00c732c0(key);
      u32* slot = (u32*)FUN_00c80110(key);
      *slot = 0;
    }
  }

  FUN_00401090(key);
  void* prof = FUN_004df550(key);
  int hasProf = (prof != 0 && *(int*)((char*)prof + 0x608) != 0) ? 1 : 0;
  int off = hasProf * 0x10;

  int* rec = (int*)((char*)dens + off + 0x34);
  int oldv0 = rec[0], oldv1 = rec[1], oldv2 = rec[2], oldv3 = rec[3];
  rec[0] = key[0]; rec[1] = key[1]; rec[2] = key[2]; rec[3] = pi;

  if (rec[0] != oldv0 || rec[1] != oldv1 || rec[2] != oldv2 || oldv3 != pi) {
    if (pi > 0 && (rec[0] != *(int*)0x01694bb8 || rec[1] != *(int*)0x01694bbc ||
                   rec[2] != *(int*)0x01694bc0)) {
      int* c = (int*)FUN_00c80110(rec);
      *c = *c + 1;
    }
    if (oldv3 > 0 && (oldv0 != *(int*)0x01694bb8 || oldv1 != *(int*)0x01694bbc ||
                      oldv2 != *(int*)0x01694bc0)) {
      int tmp[3];
      tmp[0] = oldv0; tmp[1] = oldv1; tmp[2] = oldv2;
      int* c = (int*)FUN_00c80110(tmp);
      *c = *c - 1;
      if (*c == 0) {
        if (out != 0) {
          int cntr = out[1] - out[0];
          int total = cntr >> 4;
          for (int i = 0; i < total; ++i) {
            int* e = *(int**)((char*)out[0] + i * 16 + 12);
            int* r = e + hasProf * 4 + 0xd;
            if (*e > 1) {
              if (r[3] == 0) {
                r[0] = tmp[0]; r[3] = oldv3; r[1] = oldv1; r[2] = oldv2;
                int* c2 = (int*)FUN_00c80110(tmp);
                *c2 = *c2 + 1;
                return;
              }
              int* c2 = (int*)FUN_00c80110(r);
              if (*c2 > 1) {
                if (r[3] > 0 && (r[0] != *(int*)0x01694bb8 ||
                                 r[1] != *(int*)0x01694bbc ||
                                 r[2] != *(int*)0x01694bc0)) {
                  int* c3 = (int*)FUN_00c80110(r);
                  *c3 = *c3 - 1;
                }
                r[0] = tmp[0]; r[3] = oldv3; r[1] = oldv1; r[2] = oldv2;
                int* c4 = (int*)FUN_00c80110(tmp);
                *c4 = *c4 + 1;
                return;
              }
            }
          }
        }
        u32* t = (u32*)FUN_0103de50(tmp);
        *t = 0x388deb10;
      }
    }
  }
  (void)found;
}

// ======================================================================
// 0x00c82400 - SP::cSimPlanetLowLOD::SetSimAnimalAt. thiscall.
// ======================================================================

// @ 0x00c82400
s32 __fastcall FUN_00c82400(void* self, void* /*edx*/, void* key, float* pos,
                            char flag) {
  char* p = (char*)self;              // ebx
  int* arr = *(int**)(p + 0x4c);
  int* ents = *(int**)((char*)arr + 0x13c);   // esi

  int n = (*(int*)((char*)ents + 0xd4) - *(int*)((char*)ents + 0xd0)) / 12;  // edi
  s32 ret = n;

  if ((*(u32*)((char*)ents + 0x2c) & 0x800) == 0) {
    float x = pos[0];
    float ax = (float)fabs((double)x);
    float y = pos[1];
    float ay = (float)fabs((double)y);
    float z = pos[2];
    float az = (float)fabs((double)z);

    int l20, l1c, l18;
    if (az < ax || az < ay) {
      if (ay < ax) {
        l20 = (int)((y / x + 1.0) * 2.0);
        l1c = (int)((z / ax + 1.0) * 2.0);
        l18 = (x < 0.0f) ? 3 : 2;
      } else {
        l20 = (int)((z / y + 1.0) * 2.0);
        l1c = (int)((x / ay + 1.0) * 2.0);
        l18 = (y < 0.0f) ? 5 : 4;
      }
    } else {
      l20 = (int)((x / z + 1.0) * 2.0);
      l1c = (int)((y / az + 1.0) * 2.0);
      l18 = (z < 0.0f) ? 1 : 0;
    }
    if (l20 == 4) l20 = 3;
    if (l1c == 4) l1c = 3;

    int* dens = (int*)((char*)p + 0x50 +
                       (l20 + (l1c + l18 * 4) * 4) * 0x54 + 0x1f8 - 0x1f8);
    // density record base: p+0x50 + idx*0x54 ; fields +0x1f8? -- use computed base.
    dens = (int*)((char*)p + 0x50 + (l20 + (l1c + l18 * 4) * 4) * 0x54);
    dens = (int*)((char*)dens + 0x1f8);
    (void)dens;

    int* vec = 0;
    int* vecEnd = 0;
    int  vecCap = 0;
    ((void(__thiscall*)(void*, void*, void*, u32))FUN_00c805b0)((void*)(p + 0x50), pos, &vec, 0);
    if ((u32)(((char*)vecEnd - (char*)vec) >> 4) < 3) {
      ((void(__thiscall*)(void*, void*, void*, u32))FUN_00c805b0)((void*)(p + 0x50), pos, &vec, 1);
    }
    int* base = (int*)((char*)p + 0x50 + (l20 + (l1c + l18 * 4) * 4) * 0x54);
    if (vec != vecEnd && vec[0] == l20 && vec[1] == l1c &&
        vec[2] == l18 && vec[3] == (int)base) {
      ((void(__thiscall*)(void*))FUN_00c7ff60)(&vec);
    }
    int* first = vec;
    FUN_00c821b0(p, 0, base, key, 1, &vec);
    if (base[0] < 3 && first != vecEnd) {
      int* d2 = (int*)first[3];
      if (first + 4 < vecEnd) {
        FUN_00705250(first + 4, vecEnd, first);
      }
      vecEnd = vecEnd - 4;
      FUN_00c821b0(p, 0, d2, key, 1, &vec);
    }
    if (first != 0 && first[-1] != 0) {
      FUN_00f47380(first);
    }
    (void)vecCap;
  }

  if (flag != 0) {
    s32 e = (s32)((void*(__thiscall*)(void*))FUN_00c71e30)(arr);
    if (e == 0 || e == (s32)FUN_01021300()) {
      int m = (*(int*)((char*)ents + 0xd4) - *(int*)((char*)ents + 0xd0)) / 12;
      if (n < m) {
        if ((*(u32*)((char*)ents + 0x2c) & 0x800) != 0) {
          u32 prof = (u32)((void*(__thiscall*)(void*))FUN_004df550)((void*)FUN_00401090(key));
          u32* g = *(u32**)0x016e0d08;
          g[5] = 0;
          g[9] = prof;
          g[3] = (u32)ents;
          void* log = FUN_00b3d3e0((void*)0xb003894, (void*)0x131a9f54, 0, 0, 1, 0);
          return (s32)FUN_00dd8640(log, 0xb003894, 0x131a9f54, 0, 0, 1, 0);
        }
        if (m % 3 == 0) {
          void* nm = FUN_00b3d300();
          void* sph = (void*)((void*(__thiscall*)(void*))FUN_00f67d90)(nm);
          if (sph == 0 || FUN_00c772c0(sph, (void*)0x541a72f) != 0) {
            void* log = FUN_00b3d3e0((void*)0x739dc1e3, (void*)0x131a9f54, 0, 0, 1, 0);
            FUN_00dd8640(log, 0x739dc1e3, 0x131a9f54, 0, 0, 1, 0);
          } else {
            ((void(__thiscall*)(void*, void*))FUN_00c77bf0)(sph, (void*)0x541a72f);
            void* t = FUN_010666a0((void*)0x73adb79d);
            ((void(__thiscall*)(void*))FUN_0106dcd0)(t);
          }
          void* nm2 = FUN_00b3d300();
          (void*)((void*(__thiscall*)(void*))FUN_00f67d90)(nm2);
          s32 r = FUN_00c772c0((void*)0x9fc86b19, 0);
          if ((char)r == 0) {
            return FUN_00c7f390();
          }
        }
      }
    }
  }
  return ret;
}

// ======================================================================
// 0x00c82870 - reseed the two EA random streams from the planet seed. thiscall.
// ======================================================================

// @ 0x00c82870
void __fastcall FUN_00c82870(void* self, void* /*edx*/) {
  char* p = (char*)self;
  int* pm = *(int**)((char*)SP_PlanetModel() + 0x24);
  if (pm == 0) {
    ((u32(__thiscall*)(void*, u32))FUN_00936090)((void*)0x01694c00, 0);
    ((u32(__thiscall*)(void*, u32))FUN_00936090)((void*)0x01694c04, 0);
  } else {
    u32 s = (*(u32(__thiscall**)(int*))(*(int**)pm + 0x18 / 4))(pm);
    ((u32(__thiscall*)(void*, u32))FUN_00936090)((void*)0x01694c00, s);
    s = (*(u32(__thiscall**)(int*))(*(int**)pm + 0x18 / 4))(pm);
    ((u32(__thiscall*)(void*, u32))FUN_00936090)((void*)0x01694c04, s);
  }

  char* cell = p + 0x50;
  if (cell != 0) {
    int outer = 0, mid = 0, inner = 0;
    do {
      ((void(__thiscall*)(void*, void*))FUN_00c81f40)(p, cell);
      ++inner; cell += 0x54;
      if (inner > 3) {
        ++mid; inner = 0;
        if (mid > 3) {
          ++outer; mid = 0;
          if (outer > 5) break;
        }
      }
    } while (cell != 0);
  }
}

// ======================================================================
// 0x00c82900 - SP::cSimPlanetLowLOD::SeedCellAnimals. thiscall, ret 4.
// ======================================================================

// @ 0x00c82900
void __fastcall FUN_00c82900(void* self, void* /*edx*/, void* arg) {
  char* p = (char*)self;
  int* arr;
  int* begin;
  int* end;
  int count;
  int off;
  int cA;
  int cB;
  u32 r6;
  u32 r3;

  FUN_00b3d450();
  r6 = ((u32(__thiscall*)(void*, u32))FUN_00a68fb0)((void*)0x01601760, 6);
  r3 = ((u32(__thiscall*)(void*, u32))FUN_00a68fb0)((void*)0x01601760, 3);

  arr = *(int**)(*(int*)(p + 0x4c) + 0x13c);
  begin = *(int**)((char*)arr + 0xd0);
  end = *(int**)((char*)arr + 0xd4);
  count = (int)((char*)end - (char*)begin) / 12;

  off = 0;
  cA = 0;
  cB = 0;
  if (count > 0) {
    do {
      char* key = (char*)((char*)begin + off);
      int kk = FUN_00401090(key);
      void* prof = FUN_004df550((void*)kk);
      if (prof != 0) {
        int hit;
        if (*(int*)((char*)prof + 0x608) != 0) {
          hit = (cA == (int)r3);
          ++cA;
        } else {
          hit = (cB == (int)r6);
          ++cB;
        }
        if (hit) {
          FUN_00c821b0(p, 0, key, arg, 1, 0);
        }
      }
      off += 0xc;
      --count;
    } while (count != 0);
  }
}
