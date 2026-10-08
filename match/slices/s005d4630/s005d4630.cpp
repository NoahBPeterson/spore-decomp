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
// @ 0x005D5050
// PARTIAL: 0xcb-byte curve/segment helper not reconstructed.
void FUN_005d5050(int) {}
// @ 0x005D5250
// PARTIAL: 0x186-byte curve/segment helper not reconstructed.
void FUN_005d5250(int) {}

// ============================================================================================
// 0x005D4970: spine handle "belt of circles" builder.  Builds one Circle per spine node, runs the
// pairwise tangent setup, then finds the entry/exit hits for the two end directions and, when
// the belt is valid, rebuilds the two outline paths (c1/c2) and the per-node parameters.
// (Method of the same SpineHandle class that slice s005ce9b0 declares.)
// ============================================================================================
void* operator new(unsigned int size, const char* name, int flags, unsigned int debugFlags, const char* file, int line);   // 0x00F473A0
void operator delete(void* p);                                                                                           // 0x00F47380

namespace SPB {

struct Vec2 { float x, y; };

// SP vector: the allocator keeps a header word in front of each block.
template <class T> struct sp_vector {
  T* mpBegin;
  T* mpEnd;
  T* mpCapacity;
  uint32_t mAllocator[2];
  sp_vector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
  sp_vector(const sp_vector& o);   // out of line (0x005D1240 for E20)
  ~sp_vector() {
    if (mpBegin && ((uint32_t*)mpBegin)[-1] != 0) operator delete(mpBegin);
  }
};

struct Circle {          // 0x24 bytes
  uint32_t id;
  float x, y, r;
  sp_vector<E20> arcs;   // +0x10
  Circle(int idx, struct SpineNode* n);                       // 0x005D57D0 (thiscall, ret 8)
  Circle(const Circle& o) : id(o.id), x(o.x), y(o.y), r(o.r), arcs(o.arcs) {}
  ~Circle() {}
  void FUN_005d5be0(Circle* other);                           // 0x005D5BE0 (thiscall, ret 4)
  void FUN_005d5cf0(Vec2* p0, Vec2* p1, Circle* c);           // 0x005D5CF0 (thiscall, ret 0xc)
  void FUN_005d5b60(Vec2* p, int a, int b);                   // 0x005D5B60 (thiscall, ret 0xc)
};

struct CircleVec {
  Circle* mpBegin;
  Circle* mpEnd;
  Circle* mpCapacity;
  CircleVec() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
  ~CircleVec() {
    destruct(mpBegin, mpEnd);
    if (mpBegin && ((uint32_t*)mpBegin)[-1] != 0) operator delete(mpBegin);
  }
  void DoInsertValue(Circle* pos, const Circle& v);           // 0x005D47C0 (thiscall, ret 8)
  static void destruct(Circle* first, Circle* last) {
    for (; first < last; ++first) first->~Circle();
  }
  void push_back(const Circle& v) {
    if (mpEnd < mpCapacity) {
      Circle* p = mpEnd++;
      if (p) new ((void*)p) Circle(v);
    } else
      DoInsertValue(mpEnd, v);
  }
  int size() const { return (int)(mpEnd - mpBegin); }
};

struct PathObj {         // 0x18 bytes, allocated with the EA "Editor" allocator
  PathObj();             // 0x005D57B0
  ~PathObj();            // 0x005D59C0
};

struct SpineNode {
  char pad0[0x64];
  float m64, m68, m6c;
  float m70, m74, m78;
  float m7c, m80;
  char pad84[0xdc0 - 0x84];
  uint32_t param0, param1;   // +0xdc0, +0xdc4
};

SpineNode* NextNode(SpineNode* n);   // 0x004A5970 (cdecl)

extern float gDirX;   // 0x01517F44
extern float gDirY;   // 0x01517F48
extern float gDirZ;   // 0x01517F4C

struct SpineHandle {
  char pad0[0xe8];
  SpineNode* n1;         // +0xe8
  SpineNode* n2;         // +0xec
  char pad1[0x120 - 0xf0];
  PathObj* c1;           // +0x120
  PathObj* c2;           // +0x124

  bool FUN_005d4970();
  uint32_t* NearestParam(Vec2* res, SpineNode* o);                                              // 0x005CF110 (thiscall, ret 8)
  bool WalkBelt(PathObj* out, CircleVec* v, int idx, float px, float py, unsigned flag);        // 0x005CE9B0 (thiscall, ret 0x18; this unused)
};

char FindEnd(CircleVec* v, Vec2* dir, Circle* from, char flag, Vec2* out, uint32_t* idx);       // 0x005CE7B0 (cdecl)

}  // namespace SPB
using namespace SPB;

// @ 0x005D4970
bool SpineHandle::FUN_005d4970()
{
  CircleVec circles;
  {
    int i = 0;
    SpineNode* n = n1;
    while (n) {
      Circle c(i, n);
      circles.push_back(c);
      n = NextNode(n);
      ++i;
    }
  }
  unsigned count = (unsigned)circles.size();
  if (count) {
    unsigned k = 1;
    Circle* a = circles.mpBegin;
    unsigned rem = count;
    do {
      if (k < count) {
        Circle* q = a + 1;
        for (unsigned m = count - k; m; --m, ++q) a->FUN_005d5be0(q);
      }
      unsigned m = count - 1;
      if (m) {
        Circle* q = circles.mpBegin + 1;
        for (; m; --m, ++q) {
          Vec2 p1;
          p1.x = q->x;
          p1.y = q->y;
          Vec2 p0;
          p0.x = q[-1].x;
          p0.y = q[-1].y;
          a->FUN_005d5cf0(&p0, &p1, q);
        }
      }
      ++k;
      ++a;
    } while (--rem);
  }
  Vec2 dirEnd;
  dirEnd.x = (n2->m70 * gDirY + n2->m7c * gDirZ) + n2->m64 * gDirX;
  dirEnd.y = (n2->m74 * gDirY + n2->m80 * gDirZ) + n2->m68 * gDirX;
  Vec2 hitB;
  uint32_t idxB;
  if (!FindEnd(&circles, &dirEnd, circles.mpBegin + count - 1, 0, &hitB, &idxB))
    return false;
  circles.mpBegin[idxB].FUN_005d5b60(&hitB, 2, 0);

  Vec2 dirStart;
  float negX = -gDirX, negY = -gDirY, negZ = -gDirZ;
  dirStart.x = (n1->m64 * negX + n1->m70 * negY) + n1->m7c * negZ;
  dirStart.y = (n1->m68 * negX + n1->m74 * negY) + n1->m80 * negZ;
  Vec2 hitA;
  uint32_t idxA;
  if (!FindEnd(&circles, &dirStart, circles.mpBegin, 1, &hitA, &idxA))
    return false;

  Circle* c = circles.mpBegin;
  for (unsigned j = 0; j < count; ++j, ++c) {
    if (c->id != idxA) {
      float dx = c->x - hitA.x;
      float dy = c->y - hitA.y;
      float d = sqrtf(dx * dx + dy * dy);
      if (d < c->r + 1.5258789e-05f) return false;
    }
    if (c->id != idxB) {
      float dx = c->x - hitB.x;
      float dy = c->y - hitB.y;
      float d = sqrtf(dx * dx + dy * dy);
      if (d < c->r + 1.5258789e-05f) {
        circles.destruct(circles.mpBegin, circles.mpEnd);
        return false;
      }
    }
  }

  if (c1) {
    c1->~PathObj();
    operator delete(c1);
  }
  c1 = new ("Editor", 0, 0, 0, 0) PathObj();
  bool okA = WalkBelt(c1, &circles, idxA, hitA.x, hitA.y, 1);
  if (c2) {
    c2->~PathObj();
    operator delete(c2);
  }
  c2 = new ("Editor", 0, 0, 0, 0) PathObj();
  bool okB = WalkBelt(c2, &circles, idxA, hitA.x, hitA.y, 0);
  bool ok = okA & okB;
  if (!ok) {
    if (c1) {
      c1->~PathObj();
      operator delete(c1);
    }
    PathObj* t = c2;
    c1 = 0;
    if (t) {
      t->~PathObj();
      operator delete(t);
    }
    c2 = 0;
  } else {
    for (SpineNode* n = n1; n; n = NextNode(n)) {
      uint32_t* r = NearestParam(&hitA, n);
      n->param0 = r[0];
      n->param1 = r[1];
    }
  }
  return ok;
}
