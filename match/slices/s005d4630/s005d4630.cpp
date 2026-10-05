// slice s005d4630 -- SP spine 2D curve/segment helpers (unnamed in the dev PDB).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include <new>
#include <math.h>
#include "types.h"

struct E20 {
  int a;
  int b;
  float c;
  float d;
  int e;
  E20() {}
  E20(const E20& o) : a(o.a), b(o.b), c(o.c), d(o.d), e(o.e) {}
};

struct E20Iter {
  E20* mpNode;
  E20Iter() {}
  E20Iter(E20* p) : mpNode(p) {}
  E20& operator*() const { return *mpNode; }
  bool operator!=(const E20Iter& o) const { return mpNode != o.mpNode; }
  E20Iter& operator++() {
    ++mpNode;
    return *this;
  }
};

struct Curve2D {
  char pad04[4];
  float x0;    // +0x4
  float y0;    // +0x8
  float x1;    // +0xc
  float y1;    // +0x10
  float angle; // +0x14
  void Lerp(float* out, float t);  // 005d5200
  void Arc(float* out, float t);   // 005d5160
};

// 9 bytes: |angle| * (float at +0x18); returns a float in ST0 via x87.
// @ 0x005D4FE0
float __fastcall AbsAngleTimes(void* p) {
  float* f = (float*)p;
  return fabsf(f[5]) * f[6];
}

// @ 0x005D4FF0
bool CrossSideCcw(float* p1, float* p2, float* p3) {
  float v = (p1[1] - p2[1]) * (p3[0] - p2[0]) - (p3[1] - p2[1]) * (p1[0] - p2[0]);
  if (0.0f > v) return true;
  return false;
}

// @ 0x005D5120
void CopyE20Range(E20Iter first, E20Iter last, E20Iter dest) {
  for (; first != last; ++first, ++dest)
    if (&*dest) new ((void*)&*dest) E20(*first);
}

// @ 0x005D51E0
float __fastcall SegmentLength(void* p) {
  float* f = (float*)p;
  float dx = f[3] - f[1];
  float dy = f[4] - f[2];
  float sum = dx * dx;
  sum = sum + dy * dy;
  return sqrtf(sum);
}

// @ 0x005D5200
void Curve2D::Lerp(float* out, float t) {
  float dx = x1 - x0;
  float dy = y1 - y0;
  dx *= t;
  dy *= t;
  out[0] = x0 + dx;
  out[1] = y0 + dy;
}

// @ 0x005D5160
void Curve2D::Arc(float* out, float t) {
  float dx = x1 - x0;
  float dy = y1 - y0;
  float a = -(angle * t);
  float c = cosf(a);
  float s = sinf(a);
  out[0] = x0 + (dx * c - dy * s);
  out[1] = y0 + (dx * s + dy * c);
}

// --- skeletons for the remaining slice functions (partial; see partial.txt) ---

// @ 0x005D4630
// PARTIAL: 0x185-byte curve/segment helper not reconstructed.
void FUN_005d4630(int) {}
// @ 0x005D47C0
// PARTIAL: 0x18e-byte curve/segment helper not reconstructed.
void FUN_005d47c0(int) {}
// @ 0x005D4970
// PARTIAL: 0x662-byte curve/segment solver not reconstructed.
void FUN_005d4970(int) {}
// @ 0x005D5050
// PARTIAL: 0xcb-byte curve/segment helper not reconstructed.
void FUN_005d5050(int) {}
// @ 0x005D5250
// PARTIAL: 0x186-byte curve/segment helper not reconstructed.
void FUN_005d5250(int) {}
