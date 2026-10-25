// slice s005d4630 -- SP spine 2D curve/segment helpers (unnamed in the dev PDB).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include <new>
#include <math.h>
#include <xmmintrin.h>
#include "types.h"

// Clamp lo<=v<=hi with the scalar SSE min/max the retail body uses (maxss then minss).  Taking the
// bounds by value forces them into stack slots, which is why the original feeds maxss/minss from
// memory ([esp+..]) instead of a register.
__forceinline float ClampFloat(float v, float lo, float hi) {
  __m128 t = _mm_load_ss(&v);
  t = _mm_max_ss(t, _mm_load_ss(&lo));
  t = _mm_min_ss(t, _mm_load_ss(&hi));
  return _mm_cvtss_f32(t);
}

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

// @ 0x005D5120  eastl::uninitialized_copy_ptr<PathIntersection>: returns the final dest pointer.
E20* CopyE20Range(E20Iter first, E20Iter last, E20Iter dest) {
  for (; first != last; ++first, ++dest)
    if (&*dest) new ((void*)&*dest) E20(*first);
  return dest.mpNode;
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
// The retail body forms both scaled deltas first and only then re-reads x0/y0 from the object
// (movss 0x4(%ecx),%xmm2 after the multiplies, then addss), so it needs just xmm0..xmm2. Writing the
// offset last keeps x0 out of a register: with x0 first, cl hoisted the load into xmm1 and burned a
// fourth register (xmm3), which the harness flags as a write to a register the original never touches.
void Curve2D::Lerp(float* out, float t) {
  out[0] = (x1 - x0) * t + x0;
  out[1] = (y1 - y0) * t + y0;
}

// @ 0x005D5160
// Same shape: the deltas stay live while cos/sin come back from x87 on the stack, the products are
// formed first and x0/y0 are re-read afterwards (movss 0x4(%ecx),%xmm1 / movss 0x8(%ecx),%xmm2).
void Curve2D::Arc(float* out, float t) {
  float a = -(angle * t);
  float c = cosf(a);
  float s = sinf(a);
  float dyc = (y1 - y0) * c;
  float dxc = (x1 - x0) * c;
  float dxs = (x1 - x0) * s;
  out[1] = dxs + dyc + y0;
  out[0] = dxc - (y1 - y0) * s + x0;
}

// --- remaining slice functions ---

// ============================================================================================
// 0x005D5050: walk a list of path segments (this+0x00 is the pointer array, this+0x14 the whole
// path length) accumulating segment lengths scaled by t until the remaining distance falls inside
// a segment, then evaluate that segment at remaining/length.  A short path evaluates its last
// segment at 1.0; an empty path writes a zero point.  Returns `out` (arg1) in eax.
// ============================================================================================
struct PathSegment {
  virtual float Length();                     // vtable slot 0
  virtual void  Eval(float* out, float t);    // vtable slot 1
};

struct PathCurve {
  PathSegment** mpBegin;     // +0x00
  PathSegment** mpEnd;       // +0x04
  PathSegment** mpCapacity;  // +0x08
  char pad0c[8];
  float mTotalLength;        // +0x14

  float* Walk(float* out, float t);
};

// @ 0x005D5050
float* PathCurve::Walk(float* out, float t)
{
  float remaining = mTotalLength * t;
  for (unsigned i = 0; i < (unsigned)(mpEnd - mpBegin); ++i) {
    PathSegment* seg = mpBegin[i];
    float len = seg->Length();
    if (len >= remaining) {
      seg->Eval(out, remaining / len);
      return out;
    }
    remaining -= len;
  }
  unsigned n = (unsigned)(mpEnd - mpBegin);
  if (n >= 1) {
    PathSegment* seg = mpBegin[n - 1];
    seg->Eval(out, 1.0f);
    return out;
  }
  out[0] = 0.0f;
  out[1] = 0.0f;
  return out;
}

// ============================================================================================
// 0x005D5250: intersect two circles {x,y,r}.  Returns 0 (separate), 1 (tangent, one point in
// out[0..1]) or 2 (two points in out[0..3]).
// ============================================================================================
struct CircXY {
  float x, y, r;
  int Intersect(const CircXY* b, float* out);
};

// @ 0x005D5250
int CircXY::Intersect(const CircXY* b, float* out)
{
  float dx = b->x - x;
  float dy = b->y - y;
  float dist2 = dx * dx + dy * dy;
  float dist = sqrtf(dist2);
  if (dist > r + b->r) return 0;
  if (fabsf(b->r - r) > dist) return 0;
  float t = (r * r - b->r * b->r + dist2) / (dist * 2.0f);
  float h = sqrtf(r * r - t * t);
  float inv = 1.0f / dist;
  float X1 = x + dx * t * inv;
  float Y1 = y + dy * t * inv;
  if (h < 1.5258789e-05f) {
    out[0] = X1;
    out[1] = Y1;
    return 1;
  }
  float ox = dy * h * inv;
  float oy = dx * h * inv;
  out[0] = X1 + ox;
  out[1] = Y1 - oy;
  out[2] = X1 - ox;
  out[3] = Y1 + oy;
  return 2;
}

// 0x005D47C0 (CircleVec::DoInsertValue) is defined after the CircleVec declaration below.

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
  sp_vector(const sp_vector& o);                                  // out of line (0x005D1240 for E20)
  sp_vector& operator=(const sp_vector& o);                       // out of line (0x005D12C0 for E20)
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
  // The retail copy-assignment moves the 4-dword trivial prefix with integer moves (bitwise) and
  // only then runs sp_vector::operator= for the trailing container.
  Circle& operator=(const Circle& o)
  {
    *(uint32_t*)&id = *(const uint32_t*)&o.id;
    *(uint32_t*)&x  = *(const uint32_t*)&o.x;
    *(uint32_t*)&y  = *(const uint32_t*)&o.y;
    *(uint32_t*)&r  = *(const uint32_t*)&o.r;
    arcs = o.arcs;
    return *this;
  }
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

// eastl vector insert machinery for the 0x24-byte element (out-of-line helpers in the original TU).
Circle* UninitCopyCircle(Circle* first, Circle* last, Circle* dest);      // 0x005D13F0
void    DestroyCircleRange(Circle* first, Circle* last, Circle* dest);    // 0x005CF7F0
Circle* CopyBackwardCircle(Circle* first, Circle* last, Circle* destEnd); // 0x005D1450

// @ 0x005D47C0
void CircleVec::DoInsertValue(Circle* position, const Circle& value)
{
  if (mpEnd != mpCapacity) {
    const Circle* pValue = &value;
    if (pValue >= position && pValue < mpEnd) ++pValue;
    ::new ((void*)mpEnd) Circle(*(mpEnd - 1));
    CopyBackwardCircle(position, mpEnd - 1, mpEnd);
    *position = *pValue;
    ++mpEnd;
  } else {
    const int nPrevSize = (int)(mpEnd - mpBegin);
    int nNewSize = nPrevSize ? (2 * nPrevSize) : 1;
    Circle* pNewData = nNewSize
        ? (Circle*)operator new(nNewSize * 0x24, "Editor", 0, 0,
                                "c:\\EASTL\\include\\EASTL/allocator.h", 0xd1)
        : 0;
    Circle* pPos = position;
    Circle* pOld = mpBegin;
    Circle* pNewEnd = UninitCopyCircle(pOld, pPos, pNewData);
    DestroyCircleRange(pOld, pPos, pNewData);
    ::new ((void*)pNewEnd) Circle(value);
    Circle* pNewEnd2 = UninitCopyCircle(pPos, mpEnd, ++pNewEnd);
    DestroyCircleRange(pPos, mpEnd, pNewEnd2);
    if (pOld && ((uint32_t*)pOld)[-1] != 0) operator delete(pOld);
    mpBegin = pNewData;
    mpEnd = pNewEnd2;
    mpCapacity = pNewData + nNewSize;
  }
}

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

// --- vertebra bookkeeping: eastl::map<SpineNode*, VInfo> at spine+0xcc, and the rigid bodies ---
struct HkVector4 { float x, y, z, w; };

struct HkMotion { float getMass(); };                 // 0x01088270 hkRigidMotion::getMass
struct HkBody { char pad0[0x58]; HkMotion* motion; };  // hkRigidBody: motion at +0x58

struct MouseSpring {                                   // hkMouseSpringAction (refcounted)
  virtual void* Destroy(int flags);                    // +0
  uint16_t memSize;                                    // +4
  short refCount;                                      // +6
  char pad8[0x30 - 8];
  HkVector4 mMouse;                                    // +0x30 target point of the spring
  char pad40[0x48 - 0x40];
  void setMaxRelativeForce(float f);                   // 0x00C87BC0 (writes +0x48)
};

struct RbNode {
  RbNode* mpRight;    // +0
  RbNode* mpLeft;     // +4
  RbNode* mpParent;   // +8
  int color;          // +0xc
  unsigned key;       // +0x10
  void* body;         // +0x14
};
struct VIter { RbNode* node; };
struct VInfo { void* body; uint32_t a, b, c; };

struct VMap {                    // eastl::map at spine+0xcc (anchor node base at +4)
  int pad0;
  RbNode* anchorRight;           // +0xcc+4
  RbNode* anchorLeft;
  RbNode* root;
  char color;
  unsigned size;
  VIter* Find(VIter* out, const unsigned* k);   // 0x00E5C780  rbtree find, returns `out`
  VInfo* Index(const unsigned* k);              // 0x00632E90  map subscript
  RbNode* Anchor() { return (RbNode*)&anchorRight; }
};

struct SpineHandle {
  char pad0[0x20];
  float wallX0;          // +0x20  min X of the editor wall box
  float wallZ0;          // +0x24  max Z
  float wallX1;          // +0x28  max X
  float wallZ1;          // +0x2c  min Z
  char pad30[0x3c - 0x30];
  MouseSpring* action;   // +0x3c  the mouse spring action currently dragging a vertebra
  char pad40[0xb8 - 0x40];
  float springMaxForce;  // +0xb8
  char padbc[0xcc - 0xbc];
  VMap vertebrae;        // +0xcc
  char padE4[0xe8 - 0xe4];
  SpineNode* n1;         // +0xe8
  SpineNode* n2;         // +0xec
  char pad1[0x120 - 0xf0];
  PathObj* c1;           // +0x120
  PathObj* c2;           // +0x124

  bool FUN_005d4970();
  bool Drag(SpineNode** pBlock, float a, float b, float c, float d, float e, float f);          // 0x005D4630
  float Mass();                                                                                  // 0x005D3100
  uint32_t* NearestParam(Vec2* res, SpineNode* o);                                              // 0x005CF110 (thiscall, ret 8)
  bool WalkBelt(PathObj* out, CircleVec* v, int idx, float px, float py, unsigned flag);        // 0x005CE9B0 (thiscall, ret 0x18; this unused)
};

// @ 0x005D4630
// Mouse-move continuation of StartDrag (0x5D43D0): recompute the ray/plane hit parameter t for
// the vertebra under the pointer, clamp the result into the editor wall box, retarget the mouse
// spring at the clamped point and refresh its force limit (max force / total mass * total mass).
bool SpineHandle::Drag(SpineNode** pBlock, float a, float b, float c, float d, float e, float f)
{
  unsigned key = (unsigned)*pBlock;
  VIter it;
  if (vertebrae.Find(&it, &key)->node == vertebrae.Anchor()) return false;
  VInfo* info = vertebrae.Index(&key);
  if (!info) return false;
  float den = (f + e) * 0.0f + d;
  if (den == 0.0f) return true;
  float t = -(((c + b) * 0.0f + a) / den);
  if (t < 0.0f) return true;
  float cy = b + e * t;
  float cz = c + f * t;
  cy = ClampFloat(cy, wallX0, wallX1);
  cz = ClampFloat(cz, wallZ1, wallZ0);
  HkVector4* mouse = &action->mMouse;
  mouse->x = 0.0f;
  mouse->y = cy;
  mouse->z = cz;
  mouse->w = 0.0f;
  float s = Mass();
  float mass = ((HkBody*)info->body)->motion->getMass();
  action->setMaxRelativeForce(springMaxForce / mass * s);
  return true;
}

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
