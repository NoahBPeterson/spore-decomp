// slice s005ce9b0 -- spine handle geometry / vertex interpolation helpers (all unnamed in the dev PDB).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include <new>
#include <math.h>
#include <float.h>
#include "types.h"

namespace SP {

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

}  // namespace SP
using namespace SP;

// @ 0x005CF7A0  (EASTL uninitialized_copy of a 0x14-byte, non-trivially-copyable element)
E20Iter CopyE20(E20Iter first, E20Iter last, E20Iter dest) {
  E20Iter currentDest(dest);
  for (; first != last; ++first, ++currentDest)
    if (&*currentDest) new ((void*)&*currentDest) E20(*first);
  return currentDest;
}


// ---- spine-handle geometry (names are guesses: the dev PDB has no entries for these) ----
namespace SP {

struct Vec2 { float x, y; };
struct V3 { float x, y, z; };

struct Hit;
struct Circle {            // 0x24-byte record of the spine "belt" outline
  uint32_t id;
  float x, y, r;
  uint32_t pad[5];
  float FindHit(const Vec2* pt, int ccw, Hit** out);   // 0x005D53E0, thiscall
};
struct Hit {
  Circle* a;
  Circle* b;
  float x, y;
  int kind;                // 0 = tangent hop, 1 = search, 2 = finish
};
struct CircleVec { Circle* begin; Circle* end; };

struct OutPath {           // vector of dwords + helpers
  uint32_t* begin;
  uint32_t* end;
  void Arc(const Vec2* center, float r, const Vec2* pt, float ang);   // 0x005D5A30
  void Join(const Vec2* a, const Vec2* b);                            // 0x005D5AD0
};

struct Curve { void Eval(Vec2* out, float t); };                      // 0x005D5050

struct SpineNode {
  uint32_t pad0[0x13];
  float px, py;            // +0x4c, +0x50
  uint32_t pad1[(0xdc0 - 0x54) / 4];
  float param;             // +0xdc0
  uint32_t pad2;
  uint32_t flags;          // +0xdc8
};

struct KeyHolder { uint32_t pad[0x16]; uint32_t key; };
struct Block {
  uint32_t pad[10];
  KeyHolder* holder;       // +0x28
  int GetSymmetryIndex();  // 0x0044F220
};

struct SpineHandle {
  uint32_t pad0[0x3a];
  SpineNode* n1;           // +0xe8
  SpineNode* n2;           // +0xec
  uint32_t pad1[(0x120 - 0xf0) / 4];
  Curve* c1;               // +0x120
  Curve* c2;               // +0x124
  Vec2* NearestParam(Vec2* res, SpineNode* o);                        // 0x005CF110
  void Extrude(Block* blk, float t, float s, int a4);                 // 0x005CF4F0
};

}  // namespace SP

float* FUN_004a5d10(void* out, SpineNode* n);
float FUN_004a5bd0(SpineNode* n);
void FUN_0049d6b0(Block* b, V3 c, V3 d, int a4, int flag, float mx);
void FUN_0069b650(Vec2* out, const Vec2* p, const Vec2* a, const Vec2* b);
char FUN_005d4ff0(const Vec2* p, const Vec2* q, const Vec2* r);
int FUN_005d5630(Vec2 a, Vec2 b, V3 circ, float* out4);

template <class T> inline const T& MaxRef(const T& a, const T& b) { return (b < a) ? a : b; }
template <class T> inline const T& MinRef(const T& a, const T& b) { return (a < b) ? a : b; }

// @ 0x005CE9B0
// Walks the belt of circles from circles[idx], emitting arcs/segments into out until the walk finishes.
int __stdcall FUN_005ce9b0(OutPath* out, CircleVec* v, int idx, float px, float py, unsigned flag) {
  Circle* cur = v->begin + idx;
  Vec2 pt;
  pt.x = px;
  pt.y = py;
  uint32_t id = cur->id;
  Hit* hit;
  float ang = cur->FindHit(&pt, flag, &hit);
  int kind = hit->kind;
  for (;;) {
    if (kind == 2) {
      Vec2 c;
      c.x = cur->x;
      c.y = cur->y;
      out->Arc(&c, cur->r, &pt, ang);
      return 1;
    }
    Circle* next = 0;
    if (kind == 0) {
      next = hit->a;
      if (next->id == id) next = hit->b;
      Vec2 c;
      c.x = cur->x;
      c.y = cur->y;
      out->Arc(&c, cur->r, &pt, ang);
      pt.x = hit->x;
      pt.y = hit->y;
    } else if (kind == 1) {
      uint32_t j = hit->b->id;
      Circle* c2 = v->begin + j;
      float dx, dy;
      do {
        next = c2;
        if (j >= (uint32_t)(v->end - v->begin)) return 0;
        dx = next->x - cur->x;
        dy = next->y - cur->y;
        float dist2 = dx * dx + dy * dy;
        ++j;
        c2 = next + 1;
        if (!(cur->r > sqrtf(dist2))) break;
      } while (true);
      float r2 = next->r;
      float r1 = cur->r;
      float dist = sqrtf(dx * dx + dy * dy);
      float a = acosf(fabsf(r2 - r1) / dist);
      if (r1 < r2) a = 3.14159265f - a;
      if ((char)flag == 0) a = -a;
      float cs = cosf(a), sn = sinf(a);
      float ry = dx * sn + dy * cs;
      float rx = dx * cs - dy * sn;
      float inv = 1.0f / sqrtf(ry * ry + rx * rx + 1e-8f);
      rx = inv * rx;
      ry = inv * ry;
      Vec2 q, q2;
      q.x = cur->x + rx * r1;
      q.y = cur->y + ry * r1;
      q2.x = next->x + rx * next->r;
      q2.y = next->y + ry * next->r;
      float ex = pt.x - cur->x, ey = pt.y - cur->y;
      float inv2 = 1.0f / sqrtf(ex * ex + ey * ey + 1e-8f);
      float nx = inv2 * ex, ny = inv2 * ey;
      Vec2 cc;
      cc.x = cur->x;
      cc.y = cur->y;
      char c = FUN_005d4ff0(&cc, &pt, &q);
      if ((char)flag == 0) c = (c == 0);
      if (c) {
        float a2 = acosf(nx * rx + ny * ry);
        if ((char)flag == 0) a2 = -a2;
        Vec2 c3;
        c3.x = cur->x;
        c3.y = cur->y;
        out->Arc(&c3, cur->r, &pt, a2);
      } else {
        q.x = pt.x;
        q.y = pt.y;
      }
      float bx = q2.x - q.x, by = q2.y - q.y;
      float best = sqrtf(bx * bx + by * by);
      Vec2 bp = q2;
      for (uint32_t k = 0; k < (uint32_t)(v->end - v->begin); ++k) {
        if (k != cur->id) {
          Circle* o = v->begin + k;
          V3 oc;
          oc.x = o->x;
          oc.y = o->y;
          oc.z = o->r;
          float res[4];
          if (FUN_005d5630(q, q2, oc, res) == 2) {
            float vx = res[0] - q.x, vy = res[1] - q.y;
            if (vy * by + vx * bx > -1.5258789e-05f) {
              float l = sqrtf(vx * vx + vy * vy);
              if (l > 1.5258789e-05f && best > l) {
                bp.x = res[0];
                bp.y = res[1];
                best = l;
                next = o;
              }
            }
            vx = res[2] - q.x;
            vy = res[3] - q.y;
            if (vy * by + vx * bx > -1.5258789e-05f) {
              float l = sqrtf(vx * vx + vy * vy);
              if (l > 1.5258789e-05f && best > l) {
                bp.x = res[2];
                bp.y = res[3];
                best = l;
                next = o;
              }
            }
          }
        }
      }
      out->Join(&q, &bp);
      pt = bp;
    } else {
      // kind other than 0/1/2: nothing emitted, fall through to the loop guard
    }
    if ((int)(out->end - out->begin) > (int)(v->end - v->begin) * 4) return 0;
    cur = next;
    id = cur->id;
    ang = cur->FindHit(&pt, flag, &hit);
    kind = hit->kind;
  }
}

// @ 0x005CF110
// Finds the curve parameter (and fraction along the segment) of the point on the handle's
// two guide curves nearest to the node's position: coarse scan, then bisection.
Vec2* SpineHandle::NearestParam(Vec2* res, SpineNode* o) {
  if (!c1 || !c2) return res;
  Vec2 P;
  P.x = o->px;
  P.y = o->py;
  if ((o->flags >> 7) & 1) {
    float tmp[3];
    float* p = FUN_004a5d10(tmp, o);
    P.x = p[1];
    P.y = p[2];
  }
  float bestT = 0.0f, bestD = 1e6f;
  float t = 0.05f;
  Vec2 A, B, Q;
  do {
    c1->Eval(&A, t);
    c2->Eval(&B, t);
    FUN_0069b650(&Q, &P, &A, &B);
    float d = sqrtf((Q.y - P.y) * (Q.y - P.y) + (Q.x - P.x) * (Q.x - P.x));
    if (d < bestD) {
      bestT = t;
      bestD = d;
    }
    t += 0.05f;
  } while (t < 0.99f);
  float a = bestT - 0.15f, z = 0.0f;
  float lo = MaxRef(a, z);
  float b = bestT + 0.15f, one = 1.0f;
  float hi = MinRef(b, one);
  float mid = (hi + lo) * 0.5f;
  for (;;) {
    c1->Eval(&A, mid);
    c2->Eval(&B, mid);
    FUN_0069b650(&Q, &P, &A, &B);
    float d = sqrtf((Q.y - P.y) * (Q.y - P.y) + (Q.x - P.x) * (Q.x - P.x));
    if (d <= 0.001f) break;
    if (FUN_005d4ff0(&P, &B, &A)) lo = mid;
    else hi = mid;
    if (hi - lo < 1e-5f) break;
    mid = (hi + lo) * 0.5f;
  }
  float bx = A.x - B.x, by = A.y - B.y;
  float qx = A.x - Q.x, qy = A.y - Q.y;
  res->x = (hi + lo) * 0.5f;
  res->y = sqrtf(qy * qy + qx * qx) / sqrtf(by * by + bx * bx);
  return res;
}

// @ 0x005CF4F0
void SpineHandle::Extrude(Block* blk, float t, float s, int a4) {
  Vec2 A, B;
  c1->Eval(&A, t);
  c2->Eval(&B, t);
  float dx = B.x - A.x, dy = B.y - A.y;
  float qx = dx * s + A.x, qy = A.y + dy * s;
  float mx = dx * 0.5f + A.x, my = A.y + dy * 0.5f;
  if (s < 0.5f) {
    dy = -dy;
    dx = -dx;
  }
  float k = (float)fabs((double)(s - 0.5f));
  float ex = dx * k, ey = dy * k;
  float r1 = sqrtf(ex * ex + ey * ey);
  float hx = dx * 0.5f, hy = dy * 0.5f;
  float r = sqrtf(hx * hx + hy * hy);
  V3 C;
  if (n1->param > t) {
    float tmp[3];
    float* p = FUN_004a5d10(tmp, n1);
    C = *(V3*)p;
    r = FUN_004a5bd0(n1);
  } else if (t > n2->param) {
    float tmp[3];
    float* p = FUN_004a5d10(tmp, n2);
    C = *(V3*)p;
    r = FUN_004a5bd0(n2);
  } else {
    C.x = 0.0f;
    C.y = mx;
    C.z = my;
  }
  float res;
  if (r1 < r - 1.5258789e-05f) res = sqrtf(r * r - r1 * r1);
  else res = 0.0f;
  float o = (float)blk->GetSymmetryIndex() * res;
  int flag = blk->holder->key != 0xdfad9f51;
  V3 D;
  D.x = o - C.x;
  D.y = qx - C.y;
  D.z = qy - C.z;
  FUN_0049d6b0(blk, C, D, a4, flag, FLT_MAX);
}
