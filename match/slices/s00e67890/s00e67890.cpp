// Slice s00e67890 (batch spcg1, slice 4). Object: SPGonzago/SPCellGame.obj
// SP::cCellGame cell-position / cell-state helpers.  Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

extern "C" double sqrt(double);
extern "C" double sin(double);
extern "C" double cos(double);

// ---- globals ------------------------------------------------------------
extern char* gspCellGfx;    // 0x016b3c08  SP::cCellGfx*

extern const float kf1485378;   // 0.0f
extern const float kf1485720;   // 1.0f
extern const float kf14851ec;   // 1.5258789e-05
extern const float kf13eb8b0;   // sign-bit mask
extern const float kf13ec4b8;   // 1e-08
extern const float kf1488874;   // 0.1
extern const float kf1471064;   // 0.5
extern const float kf15a7c24;   // pi
extern const float kf16b3dd0;   // 2*pi
extern const float kf15a7c34, kf15a7c38, kf15a7c3c;   // reference axes
extern const float kf15a7c40, kf15a7c44, kf15a7c48;   // up vector

// ---- callees / helpers --------------------------------------------------
struct CellPool { void* Get(unsigned int id); };       // 0x00b721d0
struct ResMap   { void* Find(unsigned int id); };      // 0x00b72210
struct CellGame { char pad0[0x1c]; CellPool mCells; };
extern CellGame* gspCellGame;        // 0x016b3c04  SP::cCellGame*

struct ObjHolder { void Init(); void Cleanup(); };     // 0x00743b50 / 0x00e82130
struct MapTree   { void* Find(void* out, int* key); }; // 0x00e39fb0
struct RbTree    { int   Insert(int* key); };          // 0x00e67940

void* FUN_00e823a0(int id, void* out);                 // thunk 0x00e4cc40
int   FUN_00e57340(int a);
int   FUN_00e573e0(int a, int b);
int   FUN_00e50540(int a);
int   FUN_00e66840(int a, int b);
// 12-byte key struct passed by value (cell coordinates):
struct CellKey { int a, b, c; };
int   FUN_00e679e0(CellKey key);
void  FUN_00e83e30(int a, int b, void* c);
void  FUN_00e52060(int a, int b);
void  FUN_00e4fe90(int a, int b);
void  FUN_00e84150(int a, int b, void* c);
void  FUN_00e5eb20(void* out, int cell);
char* FUN_00e52910(int a);
void  FUN_00e62a20(void* p);
void  FUN_00e658a0(void* a, void* b, void* c, unsigned d);

float  FUN_006994a0(float* a, float* b, const void* c);
float* SP_QuaternionFromFacingAndUp(float* out, float* dir, const void* up); // 0x0069b600
void   SP_normalized_safe(float* out, float* in);      // 0x00449c20
float* FUN_0046d660(float* out, float* a, float* b);   // 0x0046d660
float* FUN_007dcb00(float* out, float* in);            // 0x007dcb00

// SP::cSPTransform (all the observed fields; matches the asm layout).
struct cSPTransform {
  unsigned short flags;      // 0x00
  unsigned short modCount;   // 0x02
  float tx, ty, tz;          // 0x04 / 0x08 / 0x0c
  float scale;               // 0x10
  float rot[9];              // 0x14 .. 0x37
  void Assign(const cSPTransform& rhs);   // 0x00537dc0
};

// Defined here so the optimizer knows this callee leaves EDX/EBX/ESI/EDI intact
// (the retail build had whole-program knowledge; 00e67c40 keeps param_1 in EDX).
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

// @ 0x00e67890
void FUN_00e67890(int param_1) {
  int iVar1 = param_1;
  int iVar5 = 0;
  switch (FUN_00e57340(param_1)) {
    case 0: case 1: iVar5 = 1; break;
    case 2: case 3: iVar5 = 0; break;
    case 4: iVar5 = 2; break;
  }
  char o1[4];
  ((ObjHolder*)o1)->Init();
  char* r = (char*)FUN_00e823a0(*(int*)(iVar1 + 0x108), o1);
  char o2[4];
  ((ObjHolder*)o2)->Init();
  char* e = (char*)FUN_00e823a0(*(int*)r, o2);
  if (*(int*)(e + iVar5 * 4) == 0) iVar5 = 0;
  int v = *(int*)(e + iVar5 * 4);
  if (v != 0) FUN_00e66840(iVar1, v);
  ((ObjHolder*)o2)->Cleanup();
  ((ObjHolder*)o1)->Cleanup();
}

// @ 0x00e67940  eastl::rbtree<int,...>::insert helper
int RbTree::Insert(int* key) {
  char* self = (char*)this;
  char* head = self + 4;
  char* cand = head;
  char* n = *(char**)(self + 0xc);
  if (n != 0) {
    do {
      if (*(int*)(n + 0x10) < *key) {
        n = *(char**)n;
      } else {
        cand = n;
        n = *(char**)(n + 4);
      }
    } while (n != 0);
  }
  if (cand != head && *(int*)(cand + 0x10) <= *key) {
    return (int)(cand + 0x14);
  }
  int buf[0x2528 / 4];
  char* b = (char*)buf;
  int* slot = (int*)(b + 0x12a0);
  *slot = *key;
  FUN_00e62a20(b + 0x12a8);
  FUN_00e658a0(b, cand, slot, *(unsigned*)b);
  return (int)(b + 0x14);
}

// @ 0x00e679e0
int FUN_00e679e0(CellKey key) {
  char* base = (char*)gspCellGame;
  char out[4];
  int local = key.a;
  void* it = ((MapTree*)(base + 0x70))->Find(out, &local);
  local = key.a;
  if (*(int*)it != (int)(base + 0x74)) {
    return ((RbTree*)(base + 0x70))->Insert(&local);
  }
  int r = ((RbTree*)(base + 0x70))->Insert(&local);
  FUN_00e83e30(r, r + 4, &key);
  FUN_00e52060(r + 4, 0);
  return r;
}

// @ 0x00e67a60
char FUN_00e67a60() {
  char* m = *(char**)((char*)gspCellGame + 0x5190);
  char* r = (char*)FUN_00e679e0(*(CellKey*)(m + 0x10));
  return 0 < *(int*)(r + 0x1210);
}

// @ 0x00e67aa0
char FUN_00e67aa0() {
  char* m = *(char**)((char*)gspCellGame + 0x5190);
  char* r = (char*)FUN_00e679e0(*(CellKey*)(m + 0x10));
  return 0 < *(int*)(r + 0x120c);
}

// @ 0x00e67ae0
int FUN_00e67ae0(int param_1) {
  if (param_1 == 0) {
    char* m = *(char**)((char*)gspCellGame + 0x5190);
    char* r = (char*)FUN_00e679e0(*(CellKey*)(m + 0x10));
    if (*(int*)(r + 0x120c) > 0) return 0;
  } else if (param_1 == 4) {
    char* m = *(char**)((char*)gspCellGame + 0x5190);
    char* r = (char*)FUN_00e679e0(*(CellKey*)(m + 0x10));
    if (*(int*)(r + 0x120c) <= 0) return 0;
    if (FUN_00e67a60()) return 0;
    param_1 = 0;
  } else if (param_1 == 5) {
    if (!FUN_00e67aa0()) return 0;
    if (!FUN_00e67a60()) return 0;
    param_1 = 0;
  }
  char* m = *(char**)((char*)gspCellGame + 0x5190);
  switch (*(int*)(m + param_1 * 0x10 + 0x80)) {
    case 0: return 0;
    case 1: return param_1 != 3;
    case 2: return 2;
    case 3: if (0.0f < *(float*)(m + param_1 * 0x10 + 0x8c)) return 2; break;
  }
  return 0;
}

// @ 0x00e67be0
void FUN_00e67be0(float param_1) {
  int i = 0;
  int off = 0;
  do {
    char* base = *(char**)((char*)gspCellGame + 0x5190);
    float* p = (float*)(base + off + 0x8c);
    if (0.0f < *p) *p = *p - param_1;
    FUN_00e4fe90(i, FUN_00e67ae0(i));
    off += 0x10;
    ++i;
  } while (off < 0x60);
}

// @ 0x00e67c40
int FUN_00e67c40(int param_1, int param_2) {
  if (*(int*)(param_1 + 0xfc) == 0) return 1;
  if (*(int*)(FUN_00e52910(param_2) + 0x10) != 0) {
    return *(int*)(FUN_00e52910(param_2) + 0x10);
  }
  char* r = (char*)FUN_00e679e0(*(CellKey*)(param_1 + 0xfc));
  return *(int*)(r + 0x1254);
}

// @ 0x00e67cb0
void FUN_00e67cb0(int param_1, float* param_2) {
  if (*(int*)(param_1 + 0xfc) == 0) {
    float one = kf1485720;
    param_2[0] = one;
    param_2[1] = one;
    param_2[2] = one;
    param_2[3] = one;
    return;
  }
  char* r = (char*)FUN_00e679e0(*(CellKey*)(param_1 + 0xfc));
  param_2[0] = *(float*)(r + 0x1258);
  param_2[1] = *(float*)(r + 0x1258);
  param_2[2] = *(float*)(r + 0x1258);
  param_2[3] = *(float*)(r + 0x1258);
}

// @ 0x00e67d30
float* FUN_00e67d30(float* out, int cell, int idx) {
  if (*(int*)(cell + 0x248) == 0) {
    FUN_00e5eb20(out, cell);
    return out;
  }
  if (*(int*)(cell + 0xfc) == 0) {
    FUN_00e5eb20(out, cell);
    return out;
  }
  if (idx == -1) {
    FUN_00e5eb20(out, cell);
    return out;
  }
  {
    char* r = (char*)FUN_00e679e0(*(CellKey*)(cell + 0xfc));
    float n34 = -kf15a7c34;
    float n38 = -kf15a7c38;
    float n3c = -kf15a7c3c;
    float* m = (float*)(r + idx * 0x48 + 0x18);
    float vx = (m[3] * n38 + m[6] * n3c) + m[0] * n34;
    float vy = (m[4] * n38 + m[1] * n34) + m[7] * n3c;
    float vz = (m[5] * n38 + m[2] * n34) + m[8] * n3c;
    float f3 = vx, f4 = vy, f5 = vz;
    if (*(unsigned char*)(cell + 0x48) & 2) {
      float c00 = *(float*)(cell + 0x5c), c01 = *(float*)(cell + 0x60), c02 = *(float*)(cell + 0x64);
      float c10 = *(float*)(cell + 0x68), c11 = *(float*)(cell + 0x6c), c12 = *(float*)(cell + 0x70);
      float c20 = *(float*)(cell + 0x74), c21 = *(float*)(cell + 0x78), c22 = *(float*)(cell + 0x7c);
      f3 = (c20 * vz + c10 * vy) + c00 * vx;
      f4 = (c21 * vz + c11 * vy) + c01 * vx;
      f5 = (c22 * vz + c12 * vy) + c02 * vx;
    }
    out[0] = f3;
    out[1] = f4;
    out[2] = f5;
    return out;
  }
}

// @ 0x00e67ec0
float* FUN_00e67ec0(float* out, int cell, int idx) {
  if (*(int*)(cell + 0x248) == 0) {
    out[0] = *(float*)(cell + 0x4c);
    out[1] = *(float*)(cell + 0x50);
    out[2] = *(float*)(cell + 0x54);
    return out;
  }
  if (*(int*)(cell + 0xfc) == 0) {
    out[0] = *(float*)(cell + 0x4c);
    out[1] = *(float*)(cell + 0x50);
    out[2] = *(float*)(cell + 0x54);
    return out;
  }
  if (idx == -1) {
    out[0] = *(float*)(cell + 0x4c);
    out[1] = *(float*)(cell + 0x50);
    out[2] = *(float*)(cell + 0x54);
    return out;
  }
  {
    char* r = (char*)FUN_00e679e0(*(CellKey*)(cell + 0xfc));
    float vx = *(float*)(r + idx * 0x48 + 0x0c);
    float vy = *(float*)(r + idx * 0x48 + 0x10);
    float vz = *(float*)(r + idx * 0x48 + 0x14);
    if (*(unsigned char*)(cell + 0x48) & 2) {
      float c00 = *(float*)(cell + 0x5c), c01 = *(float*)(cell + 0x60), c02 = *(float*)(cell + 0x64);
      float c10 = *(float*)(cell + 0x68), c11 = *(float*)(cell + 0x6c), c12 = *(float*)(cell + 0x70);
      float c20 = *(float*)(cell + 0x74), c21 = *(float*)(cell + 0x78), c22 = *(float*)(cell + 0x7c);
      float nx = (c10 * vy + c20 * vz) + c00 * vx;
      float ny = (c11 * vy + c01 * vx) + c21 * vz;
      float nz = (c12 * vy + c02 * vx) + c22 * vz;
      vx = nx; vy = ny; vz = nz;
    }
    float s = *(float*)(cell + 0x58);
    out[0] = *(float*)(cell + 0x4c) + s * vx;
    out[1] = *(float*)(cell + 0x50) + s * vy;
    out[2] = *(float*)(cell + 0x54) + s * vz;
    return out;
  }
}

// @ 0x00e68000
void FUN_00e68000(int cell, int idx, cSPTransform* out) {
  if (idx == -1) {
    out->Assign(*(cSPTransform*)((char*)cell + 0x48));
    return;
  }
  if (*(int*)(cell + 0x248) != 0 && *(int*)(cell + 0xfc) != 0) {
    void* q = ((ResMap*)(gspCellGfx + 0x168))->Find(*(unsigned int*)(cell + 0x248));
    int p = *(int*)((char*)q + 0x24);
    if (p != 0) {
      FUN_00e84150(p, idx, out);
      char* r = (char*)FUN_00e679e0(*(CellKey*)(cell + 0xfc));
      float a = *(float*)(r + idx * 0x48 + 0x40);
      float b = *(float*)(r + idx * 0x48 + 0x44);
      float c = *(float*)(r + idx * 0x48 + 0x48);
      if (out->flags & 2) {
        float nx = out->rot[3] * b + out->rot[6] * c + out->rot[0] * a;
        float ny = out->rot[1] * a + out->rot[4] * b + out->rot[7] * c;
        a = nx; b = ny;
      }
      out->tx = out->tx + out->scale * a;
      out->ty = out->ty + out->scale * b;
      out->tz = out->tz;
      out->modCount++;
      out->flags |= 4;
      return;
    }
  }
  out->Assign(*(cSPTransform*)((char*)cell + 0x48));
}

// @ 0x00e68170
void FUN_00e68170(int cell) {
  float l4c, l48, l44, l40;
  float dir[3];
  float tmp[4];
  float q1[4];
  float q2[4];
  if (*(int*)(cell + 0x170) != 0) {
    void* t = ((CellPool*)((char*)gspCellGame + 0x1c))->Get(*(unsigned int*)(cell + 0x170));
    if (t != 0) {
      char* tp = (char*)t;
      l44 = *(float*)(tp + 0x54) - *(float*)(cell + 0x54);
      l48 = *(float*)(tp + 0x50) - *(float*)(cell + 0x50);
      l4c = *(float*)(tp + 0x4c) - *(float*)(cell + 0x4c);
      float inv = 1.0f / (float)sqrt((double)((l4c * l4c + l48 * l48) + l44 * l44) + kf13ec4b8);
      l4c = inv * l4c;
      l44 = l44 * inv;
      l48 = l48 * inv;
      if ((l44 * l44 + l48 * l48) + l4c * l4c <= kf14851ec) return;
      l4c = -l4c; l48 = -l48; l44 = -l44;
      dir[0] = l4c; dir[1] = l48; dir[2] = l44;
      SP_QuaternionFromFacingAndUp(q1, dir, &kf15a7c40);
      *(float*)(cell + 0x14) = q1[0];
      *(float*)(cell + 0x18) = q1[1];
      *(float*)(cell + 0x1c) = q1[2];
      *(float*)(cell + 0x20) = q1[3];
      if (*(int*)(cell + 0x174) == 0) return;
      float* pf = FUN_00e67ec0(dir, cell, *(int*)(cell + 0x174));
      l4c = *(float*)(tp + 0x4c) - pf[0];
      l48 = *(float*)(tp + 0x50) - pf[1];
      l44 = *(float*)(tp + 0x54) - pf[2];
      SP_normalized_safe(tmp, &l4c);
      FUN_00e67d30(q2, cell, *(int*)(cell + 0x174));
      float ang = FUN_006994a0(q2, tmp, &kf15a7c40);
      if (kf15a7c24 <= ang) ang = ang - kf16b3dd0;
      ang = (ang * kf1488874) * kf1471064;
      float sn = (float)sin((double)ang);
      float cs = (float)cos((double)ang);
      float axis[4];
      axis[0] = sn * kf15a7c40;
      axis[1] = sn * kf15a7c44;
      axis[2] = sn * kf15a7c48;
      axis[3] = cs;
      float* rr = FUN_0046d660(q1, (float*)(cell + 0x5c), axis);
      float* qq = FUN_007dcb00(q2, rr);
      *(float*)(cell + 0x14) = qq[0];
      *(float*)(cell + 0x18) = qq[1];
      *(float*)(cell + 0x1c) = qq[2];
      *(float*)(cell + 0x20) = qq[3];
      return;
    }
    *(int*)(cell + 0x170) = 0;
  }
  l4c = *(float*)(cell + 8) - *(float*)(cell + 0x4c);
  l44 = *(float*)(cell + 0x10) - *(float*)(cell + 0x54);
  l48 = *(float*)(cell + 0xc) - *(float*)(cell + 0x50);
  if (kf14851ec < (l4c * l4c + l44 * l44) + l48 * l48) {
    l4c = -l4c; l48 = -l48; l44 = -l44;
    dir[0] = l4c; dir[1] = l48; dir[2] = l44;
    SP_QuaternionFromFacingAndUp(q1, dir, &kf15a7c40);
    *(float*)(cell + 0x14) = q1[0];
    *(float*)(cell + 0x18) = q1[1];
    *(float*)(cell + 0x1c) = q1[2];
    *(float*)(cell + 0x20) = q1[3];
  }
}

// @ 0x00e68470
char FUN_00e68470(int param_1, int param_2) {
  if (*(int*)(param_1 + 0xfc) == 0) return 0;
  char obj[4];
  ((ObjHolder*)obj)->Init();
  char* r = (char*)FUN_00e823a0(*(int*)(param_2 + 0x108), obj);
  int a = *(int*)(r + 0xb4);
  char* st = (char*)FUN_00e679e0(*(CellKey*)(param_1 + 0xfc));
  int b = FUN_00e573e0(param_1, param_2);
  if ((*(unsigned char*)(r + 0xb0) & 1) != 0 && b == 1) {
    ((ObjHolder*)obj)->Cleanup();
    return 1;
  }
  char f = *(char*)(st + 0x1251);
  if (f != 0 && a == 3 && b == 1) {
    ((ObjHolder*)obj)->Cleanup();
    return 1;
  }
  if (f != 0 && a == 3 && FUN_00e57340(param_1) == 1 && b == 2) {
    ((ObjHolder*)obj)->Cleanup();
    return 1;
  }
  if (*(char*)(st + 0x1250) != 0 && a == 2) {
    if (b == 0 || b == 1) {
      ((ObjHolder*)obj)->Cleanup();
      return 1;
    }
    if (b == a) {
      if (*(char*)(param_1 + 0x112) == 0) {
        ((ObjHolder*)obj)->Cleanup();
        return 1;
      }
      ((ObjHolder*)obj)->Cleanup();
      return 0;
    }
    if (b == 3) {
      if (FUN_00e57340(param_1) == 1) {
        if (*(char*)(param_2 + 0x112) != 0) {
          ((ObjHolder*)obj)->Cleanup();
          return 1;
        }
        if (FUN_00e50540(param_1) != 0) {
          ((ObjHolder*)obj)->Cleanup();
          return 1;
        }
      }
    }
  }
  ((ObjHolder*)obj)->Cleanup();
  return 0;
}

// @ 0x00e685b0
char FUN_00e685b0(int param_1) {
  if (*(int*)(param_1 + 0xfc) == 0) return 0;
  char* r = (char*)FUN_00e679e0(*(CellKey*)(param_1 + 0xfc));
  return *(char*)(r + 0x1250);
}

// @ 0x00e685f0
char FUN_00e685f0(int param_1) {
  if (*(int*)(param_1 + 0xfc) == 0) return 0;
  char* r = (char*)FUN_00e679e0(*(CellKey*)(param_1 + 0xfc));
  return *(char*)(r + 0x1248);
}

// @ 0x00e68630
char FUN_00e68630(int param_1) {
  if (*(int*)(param_1 + 0x248) != 0 && *(int*)(param_1 + 0xfc) != 0 &&
      *(char*)(param_1 + 0x112) == 0 &&
      *(int*)(param_1 + 0x18c) != 0x2b && *(int*)(param_1 + 0x18c) != 0x2c) {
    if (FUN_00e57340(param_1) > 1) {
      char* r = (char*)FUN_00e679e0(*(CellKey*)(param_1 + 0xfc));
      if (*(float*)(r + 0x1270) != 0.0f) return 1;
    }
  }
  return 0;
}
