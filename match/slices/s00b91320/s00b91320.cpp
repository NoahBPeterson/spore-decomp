// slice s00b91320 -- planet cube-face grid (height + region ownership), cube-map helpers.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"
#include <math.h>
#include <xmmintrin.h>

struct Vec3 { float x, y, z; };

namespace SP {
int __cdecl WrapCubeFace(int n, int* face, int* x, int* y, int a, int b);  // @ 0x684ca0
}
int __cdecl CubeSpan(int n, int* abf, int radius, void* rects);    // @ 0x685450 -> rect count (stride 5 ints)
void __cdecl CubeWrap3(int n, int* face, int* x, int* y);          // @ 0x6906f0 (FUN_00b906f0)
extern const unsigned char g_cubeAxes[];                           // @ 0x1465948: 4 bytes per face pair

struct Region {
  char valid;       // +0
  char face;        // +1
  short y0;         // +2
  short y1;         // +4
  short x0;         // +6
  short x1;         // +8
  short pad;        // +0xa
  int area;         // +0xc
};
struct Cell {
  Region* owner;    // +0
  unsigned int flags;  // +4
  int pad;
};

struct cCubeGrid {
  char pad0[0x24];
  int mN;                      // +0x24 cells per face edge
  char pad1[4];
  unsigned short* mHeights;    // +0x2c
  char pad2[4];
  Cell* mCells;                // +0x34
  int mStrideA;                // +0x38
  int mStrideB;                // +0x3c
  char pad3[4];
  float mScale;                // +0x44
  int mBase;                   // +0x48
  float mBias;                 // +0x4c

  bool IsCellFree(int idx, int face, int x, int y);   // @ 0xb907f0
  Cell* GetCell(int face, int x, int y);              // @ 0xb90750
  bool CheckCell(int face, int x, int y);
  void MarkSphere(const Vec3* dir, float radius, unsigned int flag);
  void GrowRegion(const int* seed, Region* r);
  float GetHeight(const int* p);
  bool GetCellDir(unsigned int mask, int face, int x, int y, Vec3* out);

  // wrap (face,x,y) onto the cube and return the cell
  Cell& CellAt(int f, int x, int y) {
    int a = f, b = x, c = y;
    do {
    } while (SP::WrapCubeFace(mN, &a, &b, &c, 0, 0));
    return mCells[(a * mN + c) * mN + b];
  }
  bool Owned(int f, int x, int y) { return CellAt(f, x, y).owner != 0; }
  bool Open(int f, int x, int y) {
    int a = f, b = x, c = y;
    do {
    } while (SP::WrapCubeFace(mN, &a, &b, &c, 0, 0));
    return IsCellFree((a * mN + c) * mN + b, a, b, c);
  }
};

// @ 0x00B91320  flag every unclaimed cell within `radius` of the direction `dir` (cube-face spans)
void cCubeGrid::MarkSphere(const Vec3* dir, float radius, unsigned int flag) {
  Vec3 v = *dir;
  float len = (float)sqrt((v.z * v.z + v.y * v.y) + v.x * v.x);
  if (len > 1.5258789e-05f && radius >= 1.5258789e-05f) {
    int n = mN;
    float inv = 1.0f / len;
    v.x = v.x * inv;
    float ax = (float)fabs(v.x);
    v.y = v.y * inv;
    v.z = v.z * inv;
    float ay = (float)fabs(v.y);
    float r2 = (inv * radius) * (inv * radius);
    float az = (float)fabs(v.z);
    float half = (float)n * 0.5f;
    float x = v.x, y = v.y, z = v.z;
    int seed[3];  // x, y, face
    if (az < ax || az < ay) {
      if (ay < ax) {
        seed[0] = (int)((y / x + 1.0f) * half);
        seed[1] = (int)((z / ax + 1.0f) * half);
        seed[2] = (x < 0.0f) ? 3 : 2;
      } else {
        seed[0] = (int)((z / y + 1.0f) * half);
        seed[1] = (int)((x / ay + 1.0f) * half);
        seed[2] = (y < 0.0f) ? 5 : 4;
      }
    } else {
      seed[0] = (int)((x / z + 1.0f) * half);
      seed[1] = (int)((y / az + 1.0f) * half);
      seed[2] = (z < 0.0f) ? 1 : 0;
    }
    if (seed[0] == n) seed[0]--;
    if (seed[1] == n) seed[1]--;
    float span = ((float)n * inv) * radius;
    int ispan = _mm_cvtss_si32(_mm_set_ss(span));
    if ((float)ispan < span) ispan++;
    struct Rect { int face, a0, b0, a1, b1; } rects[6];
    int count = CubeSpan(mN, seed, ispan, rects);
    unsigned int mask = flag | 7;
    for (int i = 0; i < count; i++) {
      unsigned int face = rects[i].face;
      for (int b = rects[i].b0; b < rects[i].b1; b++) {
        for (int a = rects[i].a0; a < rects[i].a1; a++) {
          unsigned int* pf = &mCells[(mN * face + b) * mN + a].flags;
          unsigned int f = *pf;
          if ((mask & f) == 0) {
            float fb = (((float)b + 0.5f) * (1.0f / (float)mN)) * 2.0f - 1.0f;
            float fa = (((float)a + 0.5f) * (1.0f / (float)mN)) * 2.0f - 1.0f;
            const unsigned char* t = &g_cubeAxes[((int)face >> 1) * 4];
            float nrm = 1.0f / (float)sqrt((fa * fa + fb * fb) + 1.0f);
            float s = nrm;
            if (face & 1) s = -nrm;
            float v[3];
            v[t[0]] = s * fa;
            v[t[1]] = nrm * fb;
            v[t[2]] = s;
            if (((v[2] - z) * (v[2] - z) + (v[1] - y) * (v[1] - y)) + (v[0] - x) * (v[0] - x) <= r2)
              *pf = f | flag;
          }
        }
      }
    }
  }
}

// @ 0x00B91750  wrap a cell onto the cube and test it
bool cCubeGrid::CheckCell(int face, int x, int y) {
  int n = mN;
  do {
  } while (SP::WrapCubeFace(n, &face, &x, &y, 0, 0));
  int m = mN;
  int idx = (m * face + y) * m + x;
  return IsCellFree(idx, face, x, y);
}

// @ 0x00B917B0  terrain height at a grid sample
float cCubeGrid::GetHeight(const int* p) {
  unsigned int a = (unsigned int)(mStrideA * p[0]) / (unsigned int)mN;
  unsigned int b = (unsigned int)(p[1] * mStrideB) / (unsigned int)mN;
  int idx = a + b + p[2] * mStrideB + mBase;
  int h = (int)mHeights[idx] - 0x8000;
  return ((float)h * mScale) * 3.051851e-05f + mBias;
}

// @ 0x00B91810  grow a rectangular region of unclaimed free cells around a seed and claim it
void cCubeGrid::GrowRegion(const int* seed, Region* r) {
  int x0 = seed[0], y0 = seed[1], face = seed[2];
  int n = mN;
  int cur, cand;

  cur = x0;
  for (;;) {
    cand = cur - 1;
    if (Owned(face, cand, y0)) break;
    if (!Open(face, cand, y0) || cand <= x0 - 4 * n) break;
    cur = cand;
  }
  int xl = cur;

  cur = x0;
  for (;;) {
    cand = cur + 1;
    if (Owned(face, cand, y0)) break;
    if (!Open(face, cand, y0) || x0 + 4 * n <= cand) break;
    cur = cand;
  }
  int xm = (cur - xl) / 2 + xl;

  cur = y0;
  for (;;) {
    cand = cur - 1;
    if (Owned(face, xm, cand)) break;
    if (!Open(face, xm, cand) || cand <= y0 - 4 * n) break;
    cur = cand;
  }
  int yl = cur;

  cand = y0;
  for (;;) {
    cand = cand + 1;
    if (Owned(face, xm, cand)) break;
    if (!Open(face, xm, cand) || y0 + 4 * n <= cand) break;
  }
  int ym = ((cand - yl) - 1) / 2 + yl;

  bool L = true, R = true, T = true, B = true;
  int xlo = xm, xhi = xm, ylo = ym, yhi = ym;
  int iy = ym;
  int top, bot, ix;

X_TOP:
  if (L || R) {
    if (iy <= yhi) {
      bool ok;
      if (L) {
        ok = !Owned(face, xlo - 1, iy) && CheckCell(face, xlo - 1, iy);
      } else {
        ok = false;
      }
      L = L & ok;
      if (R) {
        if (!Owned(face, xhi + 1, iy) && CheckCell(face, xhi + 1, iy)) {
          iy++;
          goto X_TOP;
        }
      }
      R = false;
      iy++;
      goto X_TOP;
    }
    if (L) xlo--;
    if (R) xhi++;
  }

  top = ylo - 1;
  bot = yhi + 1;
  ix = xlo;
  for (;;) {
    if (!T && !B) goto FINAL;
    if (xhi < ix) break;
    bool ok;
    if (T) {
      ok = !Owned(face, ix, top) && Open(face, ix, top);
    } else {
      ok = false;
    }
    T = T & ok;
    if (B) {
      ok = !Owned(face, ix, bot) && Open(face, ix, bot);
    } else {
      ok = false;
    }
    B = B & ok;
    ix++;
  }
  if (T) ylo = top;
  if (B) yhi = bot;
  iy = ylo;
  if ((!T || (!L && !R)) && (!B || (!L && !R))) goto FINAL;
  goto X_TOP;

FINAL:
  r->face = (char)face;
  r->x0 = (short)xlo;
  r->valid = 1;
  r->y0 = (short)ylo;
  r->x1 = (short)xhi;
  r->y1 = (short)yhi;
  for (int y = ylo; y <= yhi; y++) {
    for (int x = xlo; x <= xhi; x++) {
      CellAt(face, x, y).owner = r;
    }
  }
  r->area = ((int)r->x1 - (int)r->x0 + 1) * ((int)r->y1 - (int)r->y0 + 1);
}

// @ 0x00B920B0  direction (scaled by terrain height) of a cell center; returns whether the cell has any of `mask`
bool cCubeGrid::GetCellDir(unsigned int mask, int face, int x, int y, Vec3* out) {
  int cx = x, cy = y, f = face;
  CubeWrap3(mN, &f, &cx, &cy);
  float inv = 1.0f / (float)mN;
  float fa = (((float)cx + 0.5f) * inv) * 2.0f - 1.0f;
  float fb = (((float)cy + 0.5f) * inv) * 2.0f - 1.0f;
  const unsigned char* t = &g_cubeAxes[(f >> 1) * 4];
  float nrm = 1.0f / (float)sqrt((fa * fa + fb * fb) + 1.0f);
  float s = nrm;
  if (f & 1) s = -nrm;
  float v[3];
  v[t[0]] = s * fa;
  v[t[1]] = nrm * fb;
  v[t[2]] = s;
  unsigned int a0 = (unsigned int)(mStrideA * cx) / (unsigned int)mN;
  unsigned int b0 = (unsigned int)(mStrideB * cy) / (unsigned int)mN;
  int idx = a0 + b0 + mStrideB * f + mBase;
  int h = (int)mHeights[idx] - 0x8000;
  float height = ((float)h * mScale) * 3.051851e-05f + mBias;
  Vec3 res;
  res.x = v[0] * height;
  res.y = v[1] * height;
  res.z = v[2] * height;
  Cell* c = GetCell(face, x, y);
  *out = res;
  return (c->flags & mask) != 0;
}

// ---- planet model queries ----
struct PlanetModel {
  char pad[0x64];
  unsigned char* mFlags;  // +0x64
  int Lookup(unsigned int a);        // @ 0xb88590
  unsigned int Count(int idx);       // @ 0xb7ea00
};
PlanetModel* GetPlanetModel();  // @ 0xb3d350

// @ 0x00B92280
bool __stdcall PlanetModelIndexInRange(unsigned int a, unsigned int limit) {
  bool r = false;
  PlanetModel* pm = GetPlanetModel();
  int idx = pm->Lookup(a);
  if (pm->mFlags[idx] == r) {
    unsigned int v = pm->Count(idx);
    if (v > limit) r = true;
  }
  return r;
}
