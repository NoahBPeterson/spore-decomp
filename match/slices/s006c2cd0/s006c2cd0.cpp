// Slice s006c2cd0: helpers from the anonymous-namespace cBakedArenaResource module
// (Graphics / RenderWare arena baked-resource data). The slice mixes:
//   * 4x4 float-matrix helpers (row copy, row scale),
//   * a 24-byte sortable record and the EASTL heap algorithms over it,
//   * container/descriptor views of baked arena blocks,
//   * octahedral-ish basis projection used to build per-vertex 2-float attributes.
#include "types.h"
#include <math.h>
#include <xmmintrin.h>

// Single-precision multiply with exactly one float32 rounding. cl15 emits x87
// for scalar float (even with /arch:SSE), and the harness runs x87 at 24-bit
// precision: multiplying a normal by a denormal then storing to float32 then
// double-rounds and lands one ulp off. The original here is SSE-scalar
// (mulss), so route the denormal-sensitive multiplies through SSE to round once.
static __forceinline float MulSS(float a, float b) {
  return _mm_cvtss_f32(_mm_mul_ss(_mm_set_ss(a), _mm_set_ss(b)));
}

// Single-precision add with float32 rounding only (same reason as MulSS). Also
// pins the operation order: the original re-associates the dot products (e.g.
// `b2*m8` first for outA[0]), and a plain C expression lets cl15 pick its own
// grouping, which shows up as 1-ulp and signed-zero differences.
static __forceinline float AddSS(float a, float b) {
  return _mm_cvtss_f32(_mm_add_ss(_mm_set_ss(a), _mm_set_ss(b)));
}

// ---------------------------------------------------------------------------
// Small shared value types.
// ---------------------------------------------------------------------------

struct Mat4 {
  float m[16];
  void SetRows(const float* r0, const float* r1, const float* r2, const float* r3); // 0x006c2740
};

// The sortable record used by the heap helpers: 24 bytes compared field-wise.
struct Rec24 { uint32_t f0, f1, f2, f3, f4, f5; };

// eastl adjust_heap (hole/len/top + the value being sifted). 0x006c2bc0
void AdjustHeap(Rec24* base, int hole, int len, int top, Rec24 value);

// Resource block lookup by (type, flag). 0x0071ddc0
int FUN_0071ddc0(int res, int a, int b, int c, int d);

// ---------------------------------------------------------------------------
// Matrix helpers
// ---------------------------------------------------------------------------

// @ 0x006c2cd0
// out = m * scale, with the four rows emitted in reverse order (row3 first).
float* ScaleMatrixReversed(float* out, const float* m, float s) {
  float t[16];
  t[0]  = m[0xc] * s; t[1]  = m[0xd] * s; t[2]  = m[0xe] * s; t[3]  = m[0xf] * s;
  t[4]  = m[0x8] * s; t[5]  = m[0x9] * s; t[6]  = m[0xa] * s; t[7]  = m[0xb] * s;
  t[8]  = m[0x4] * s; t[9]  = m[0x5] * s; t[10] = m[0x6] * s; t[11] = m[0x7] * s;
  t[12] = m[0x0] * s; t[13] = m[0x1] * s; t[14] = m[0x2] * s; t[15] = m[0x3] * s;
  // The temporary is filled bottom-up, so the rows go back to SetRows in reverse:
  // out row 0 is the last-computed block (m[0..3]*s).
  ((Mat4*)out)->SetRows(t + 12, t + 8, t + 4, t);
  return out;
}

// ---------------------------------------------------------------------------
// Heap algorithms over Rec24
// ---------------------------------------------------------------------------

// @ 0x006c2e00
// pop_heap: move the root to the last slot (the peeled value is sifted from the root).
void PopHeap(Rec24* first, Rec24* last) {
  Rec24 value = last[-1];
  last[-1] = first[0];
  AdjustHeap(first, 0, (int)(last - first) - 1, 0, value);
}

// @ 0x006c33b0
// make_heap: sift down every internal node from the last parent up to the root.
void MakeHeap(Rec24* first, Rec24* last) {
  int len = (int)(last - first);
  if (len >= 2) {
    int i = ((len - 2) >> 1) + 1;
    do {
      --i;
      AdjustHeap(first, i, len, i, first[i]);
    } while (i != 0);
  }
}

// @ 0x006c3430
// sort_heap: repeatedly pop the root to the shrinking end.
void SortHeap(Rec24* first, Rec24* last) {
  while (last - first > 1) {
    PopHeap(first, last);
    --last;
  }
}

// ---------------------------------------------------------------------------
// Baked-arena block views
// ---------------------------------------------------------------------------

struct RefCounted {
  virtual void AddRef();   // vtable[0]
  virtual void Release();  // vtable[1]
};

// A range/layout descriptor: integer element base at +4, u16 element stride at +0xa.
struct Range {
  char pad0[4];
  int base;        // +4
  char pad1[2];
  uint16_t stride; // +0xa
};

// Resource with a table of 0x20-byte block descriptors at +8.
struct ArenaRes {
  char pad0[8];
  char* blocks;    // +8
};

// Descriptor produced by Container::MakeDescriptor.
struct Descriptor;

struct Container {
  virtual void slot0(Descriptor* out, int b);  // vtable[0]
  char pad0[8];
  char* begin;  // +0xc
  char* end;    // +0x10
  Descriptor* MakeDescriptor(Descriptor* out);
};

struct Descriptor {
  int count;        // +0
  void* first;      // +4
  uint16_t a;       // +8
  uint16_t b;       // +0xa
  Container* owner; // +0xc
};

// @ 0x006c32f0
Descriptor* Container::MakeDescriptor(Descriptor* out) {
  char* begin = this->begin;
  char* end = this->end;
  out->count = (int)(end - begin) >> 3;
  out->first = begin;
  out->a = 8;
  out->b = 8;
  out->owner = this;
  slot0(out, 0);
  return out;
}

// ---------------------------------------------------------------------------
// Red-black tree node insertion (EASTL map instance)
// ---------------------------------------------------------------------------

struct RBNode {
  char pad0[0x10];
  int key0;  // +0x10
  int key1;  // +0x14
};

// The side selector is compared as a whole dword by 0x009216a0 (`cmp [esp+0x18], 0`),
// so it must be a well-formed 0/1 int, not a byte-sized bool.
void RBTreeInsert(RBNode* node, RBNode* hint, RBNode* header, int side); // 0x009216a0
void* EASTL_alloc(int size, const char* tag, int a, int b, const char* file, int line); // 0x00f473a0

struct RBTree {
  char pad0[0x14];
  int count;       // +0x14
  RBNode** insert(RBNode** out, RBNode* hint, const int* key, bool flag);
};

// @ 0x006c3330
// The original leaves the out slot pointer in eax (callers do `mov eax, edi`
// with edi == out), so it returns the parameter.
RBNode** RBTree::insert(RBNode** out, RBNode* hint, const int* key, bool flag) {
  int side = (!flag && (char*)hint != (char*)this + 4 && !(key[0] < hint->key0)) ? 1 : 0;
  RBNode* node = (RBNode*)EASTL_alloc(0x18, "Graphics", 0, 0,
                                      "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\"
                                      "SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\"
                                      "EASTL/allocator.h",
                                      0xd1);
  if ((char*)node + 0x10 != 0) {
    node->key0 = key[0];
    node->key1 = key[1];
  }
  RBTreeInsert(node, hint, (RBNode*)((char*)this + 4), side);
  ++count;
  *out = node;
  return out;
}

// ---------------------------------------------------------------------------
// Basis projection
// ---------------------------------------------------------------------------

static float SignF(float v) {
  if (v > 0.0f) return 1.0f;
  if (v < 0.0f) return -1.0f;
  return 0.0f;
}

// @ 0x006c2ea0
// Encodes a direction n against an axis frame into two floats (octahedral map).
float* FUN_006c2ea0(float* out, const float* axis, const float* n, const float* scale, const void* obj) {
  float n0 = n[0], n1 = n[1], n2 = n[2];
  float a0 = fabsf(n0), a1 = fabsf(n1), a2 = fabsf(n2);
  float g0 = (a2 < a0) ? 0.0f : 1.0f;
  float g1 = (a1 < a2) ? 0.0f : 1.0f;
  float g2 = (a0 < a1) ? 0.0f : 1.0f;
  float g3 = (a2 < a1) ? 0.0f : 1.0f;
  float g4 = (a1 < a0) ? 0.0f : 1.0f;
  float g5 = (a0 < a2) ? 0.0f : 1.0f;
  float sign2 = SignF(n2);
  float sign1 = SignF(n1);
  float sign0 = SignF(n0);

  float t = -(g4 * g1 * sign1);
  float u = sign0 * (g5 * g2);

  // The original is SSE-scalar: every add/mul rounds to float32. cl15 emits
  // x87, whose 24-bit precision double-rounds denormal results, so the
  // multiplies that can produce a denormal go through MulSS (single rounding).
  volatile float r0 = axis[1] * u;
  r0 = r0 + axis[0] * (g3 * g0);
  r0 = r0 + axis[0] * t;
  volatile float p0 = MulSS(r0, scale[0]);

  volatile float r1 = axis[2] * (sign0 * u);
  r1 = r1 + axis[1] * ((g3 * g0) * sign2);
  r1 = r1 + axis[2] * (-sign1 * t);
  volatile float p1 = -MulSS(r1, scale[1]);

  float k = *(const float*)((const char*)obj + 0x10);
  out[0] = MulSS(p0, k);
  out[1] = MulSS(p1, k);
  return out;
}

// @ 0x006c3080
// Builds count 2-float attributes from one of two baked block formats.
bool FUN_006c3080(float* out, int count, int res, int* data, const Range* vtx,
                  const float* scale, const void* obj) {
  int idx = FUN_0071ddc0(res, 2, 0, 3, 0xe);
  if (idx >= 0) {
    char* e = (char*)(*(int*)(res + 8) + idx * 0x20);
    RefCounted* rc = *(RefCounted**)(e + 0x1c);
    char* blockBase = (char*)*(int*)(e + 0x14);
    uint16_t blockStride = *(uint16_t*)(e + 0x1a);
    if (rc) rc->AddRef();
    for (int i = 0; i < count; ++i) {
      const float* col = (const float*)(blockBase + blockStride * data[1]);
      float n[3] = { col[0], col[1], col[2] };
      const float* p = (const float*)(vtx->base + (int)vtx->stride * data[0]);
      float ax[3] = { p[0], p[1], p[2] };
      float tmp[2];
      FUN_006c2ea0(tmp, ax, n, scale, obj);
      out[0] = tmp[0];
      out[1] = tmp[1];
      data += 6;
      out += 2;
    }
    if (rc) rc->Release();
    return true;
  }
  idx = FUN_0071ddc0(res, 2, 0, 7, 0xe);
  if (idx < 0) return false;
  char* e = (char*)(*(int*)(res + 8) + idx * 0x20);
  RefCounted* rc = *(RefCounted**)(e + 0x1c);
  char* blockBase = (char*)*(int*)(e + 0x14);
  uint16_t blockStride = *(uint16_t*)(e + 0x1a);
  if (rc) rc->AddRef();
  for (int i = 0; i < count; ++i) {
    const float* p = (const float*)(vtx->base + (int)vtx->stride * data[0]);
    float ax[3] = { p[0], p[1], p[2] };
    unsigned packed = *(unsigned*)(blockBase + blockStride * data[1]);
    float n[3];
    n[0] = (float)(packed & 0xff) * (1.0f / 127.0f) - 1.0f;
    n[1] = (float)((packed >> 8) & 0xff) * (1.0f / 127.0f) - 1.0f;
    n[2] = (float)((packed >> 16) & 0xff) * (1.0f / 127.0f) - 1.0f;
    float tmp[2];
    FUN_006c2ea0(tmp, ax, n, scale, obj);
    out[0] = tmp[0];
    out[1] = tmp[1];
    data += 6;
    out += 2;
  }
  if (rc) rc->Release();
  return true;
}

// ---------------------------------------------------------------------------
// Matrix-transform pair
// ---------------------------------------------------------------------------

// @ 0x006c3550
// Transforms a direction and a point by a baked block matrix scaled by s[0].
// The original leaves outA in eax (the hidden return of the out-parameter), so
// declare it as the return value.
float* FUN_006c3550(float* outA, float* outB, const float* base, const float* dir,
                    const float* s, const int* idx, int layout) {
  char* p = (char*)(*(int*)(layout + 4) + (uint16_t)*(uint16_t*)(layout + 0xa) * idx[0]);
  float fourth[4] = {0.0f, 0.0f, 0.0f, 1.0f};
  Mat4 m;
  m.SetRows((const float*)p, (const float*)(p + 0x10), (const float*)(p + 0x20), fourth);
  float sm[16];
  ScaleMatrixReversed(sm, m.m, s[0]);

  // The original is SSE-scalar and groups the products as shown (the direction
  // rows start with the z term, the point rows with the y/z terms); the fourth
  // column is multiplied by the literal 0.0f, which only matters for the sign
  // of an exact zero result. Reproduce that order exactly.
  float d0 = dir[0], d1 = dir[1], d2 = dir[2];
  float b0 = base[0], b1 = base[1], b2 = base[2];
  volatile float vzero = 0.0f;
  float z = vzero;

  outB[0] = AddSS(AddSS(AddSS(MulSS(sm[0], d0), MulSS(sm[8], d2)), MulSS(sm[4], d1)),
                  MulSS(sm[12], z));
  outB[1] = AddSS(AddSS(AddSS(MulSS(sm[9], d2), MulSS(sm[5], d1)), MulSS(sm[1], d0)),
                  MulSS(sm[13], z));
  outB[2] = AddSS(AddSS(AddSS(MulSS(sm[10], d2), MulSS(sm[6], d1)), MulSS(sm[2], d0)),
                  MulSS(sm[14], z));

  outA[0] = AddSS(AddSS(AddSS(MulSS(sm[8], b2), MulSS(sm[0], b0)), MulSS(sm[4], b1)), sm[12]);
  outA[1] = AddSS(AddSS(AddSS(MulSS(sm[5], b1), MulSS(sm[9], b2)), MulSS(sm[1], b0)), sm[13]);
  outA[2] = AddSS(AddSS(AddSS(MulSS(sm[6], b1), MulSS(sm[10], b2)), MulSS(sm[2], b0)), sm[14]);
  return outA;
}

// @ 0x006c3780
// As FUN_006c3550, but a second block contributes a per-row offset weighted by s[1].
float* FUN_006c3780(float* outA, float* outB, const float* base, const float* dir,
                    const float* s, const int* idx, int layout) {
  uint16_t stride = *(uint16_t*)(layout + 0xa);
  char* seg = (char*)*(int*)(layout + 4);
  char* p = seg + stride * idx[0];
  float fourth[4] = {0.0f, 0.0f, 0.0f, 1.0f};
  Mat4 m;
  m.SetRows((const float*)p, (const float*)(p + 0x10), (const float*)(p + 0x20), fourth);
  float sm[16];
  ScaleMatrixReversed(sm, m.m, s[0]);

  const float* off = (const float*)(seg + stride * idx[1]);
  float k = s[1];
  volatile float vzero = 0.0f;
  float z = vzero;
  // A zero-width lane of the offset block is folded into the translation column
  // (s[1] * 0.0f): it can flip an exact -0.0 translation to +0.0.
  float t12 = AddSS(sm[12], MulSS(k, z));
  float t13 = AddSS(sm[13], MulSS(k, z));
  float t14 = AddSS(sm[14], MulSS(k, z));

  float o0 = AddSS(sm[0], MulSS(off[0], k));
  float o1 = AddSS(sm[1], MulSS(off[1], k));
  float o2 = AddSS(sm[2], MulSS(off[2], k));
  float o4 = AddSS(sm[4], MulSS(off[4], k));
  float o5 = AddSS(sm[5], MulSS(off[5], k));
  float o6 = AddSS(sm[6], MulSS(off[6], k));
  float o8 = AddSS(sm[8], MulSS(off[8], k));
  float o9 = AddSS(sm[9], MulSS(off[9], k));
  float o10 = AddSS(sm[10], MulSS(off[10], k));

  float d0 = dir[0], d1 = dir[1], d2 = dir[2];
  float b0 = base[0], b1 = base[1], b2 = base[2];

  outB[0] = AddSS(AddSS(AddSS(MulSS(o0, d0), MulSS(o8, d2)), MulSS(o4, d1)), MulSS(t12, z));
  outB[1] = AddSS(AddSS(AddSS(MulSS(o5, d1), MulSS(o9, d2)), MulSS(o1, d0)), MulSS(t13, z));
  outB[2] = AddSS(AddSS(AddSS(MulSS(o6, d1), MulSS(o10, d2)), MulSS(o2, d0)), MulSS(t14, z));

  outA[0] = AddSS(AddSS(AddSS(MulSS(o8, b2), MulSS(o0, b0)), MulSS(o4, b1)), t12);
  outA[1] = AddSS(AddSS(AddSS(MulSS(o5, b1), MulSS(o9, b2)), MulSS(o1, b0)), t13);
  outA[2] = AddSS(AddSS(AddSS(MulSS(o6, b1), MulSS(o10, b2)), MulSS(o2, b0)), t14);
  return outA;
}

// ---------------------------------------------------------------------------
// Constructor
// ---------------------------------------------------------------------------

// Two polymorphic bases at offsets 0 and 4 (as in the baked-arena resource).
struct BaseA {
  virtual void a0(); virtual void a1(); virtual void a2(); virtual void a3(); virtual void a4();
};
struct BaseB {
  virtual void b0(); virtual void b1(); virtual void b2(); virtual void b3(); virtual void b4();
};

struct BakedArenaThing : BaseA, BaseB {
  int m_ref;      // +8
  int m_c;        // +0xc
  int m_10;       // +0x10
  int m_14;       // +0x14
  int m_20;       // +0x20
  BakedArenaThing();
};

// @ 0x006c3510
BakedArenaThing::BakedArenaThing()
  : m_ref(0), m_c(0), m_10(0), m_14(0), m_20(0) {}
