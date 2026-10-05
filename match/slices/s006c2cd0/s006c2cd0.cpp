// Slice s006c2cd0: helpers from the anonymous-namespace cBakedArenaResource module
// (Graphics / RenderWare arena baked-resource data). The slice mixes:
//   * 4x4 float-matrix helpers (row copy, row scale),
//   * a 24-byte sortable record and the EASTL heap algorithms over it,
//   * container/descriptor views of baked arena blocks,
//   * octahedral-ish basis projection used to build per-vertex 2-float attributes.
#include "types.h"
#include <math.h>

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
  ((Mat4*)out)->SetRows(t, t + 4, t + 8, t + 12);
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

void RBTreeInsert(RBNode* node, RBNode* hint, RBNode* header, bool right); // 0x009216a0
void* EASTL_alloc(int size, const char* tag, int a, int b, const char* file, int line); // 0x00f473a0

struct RBTree {
  char pad0[0x14];
  int count;       // +0x14
  void insert(RBNode** out, RBNode* hint, const int* key, bool flag);
};

// @ 0x006c3330
void RBTree::insert(RBNode** out, RBNode* hint, const int* key, bool flag) {
  bool right = (flag == 0) && ((char*)hint != (char*)this + 4) && (hint->key0 <= key[0]);
  RBNode* node = (RBNode*)EASTL_alloc(0x18, "Graphics", 0, 0, "EASTL/allocator.h", 0xd1);
  if ((char*)node + 0x10 != 0) {
    node->key0 = key[0];
    node->key1 = key[1];
  }
  RBTreeInsert(node, hint, (RBNode*)((char*)this + 4), right);
  ++count;
  *out = node;
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

  out[0] = (axis[1] * u + axis[0] * (g3 * g0) + axis[0] * t) * scale[0];
  out[1] = -((axis[2] * (sign0 * u) + axis[1] * ((g3 * g0) * sign2) + axis[2] * (-sign1 * t)) * scale[1]);

  float k = *(const float*)((const char*)obj + 0x10);
  out[0] *= k;
  out[1] *= k;
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
void FUN_006c3550(float* outA, float* outB, const float* base, const float* dir,
                  const float* s, const int* idx, int layout) {
  char* p = (char*)(*(int*)(layout + 4) + (uint16_t)*(uint16_t*)(layout + 0xa) * idx[0]);
  float fourth[4] = {0.0f, 0.0f, 0.0f, 1.0f};
  Mat4 m;
  m.SetRows((const float*)p, (const float*)(p + 0x10), (const float*)(p + 0x20), fourth);
  float sm[16];
  ScaleMatrixReversed(sm, m.m, s[0]);

  outB[0] = sm[0] * dir[0] + sm[4] * dir[1] + sm[8] * dir[2];
  outB[1] = sm[1] * dir[0] + sm[5] * dir[1] + sm[9] * dir[2];
  outB[2] = sm[2] * dir[0] + sm[6] * dir[1] + sm[10] * dir[2];

  outA[0] = sm[0] * base[0] + sm[4] * base[1] + sm[8] * base[2] + sm[12];
  outA[1] = sm[1] * base[0] + sm[5] * base[1] + sm[9] * base[2] + sm[13];
  outA[2] = sm[2] * base[0] + sm[6] * base[1] + sm[10] * base[2] + sm[14];
}

// @ 0x006c3780
// As FUN_006c3550, but a second block contributes a per-row offset weighted by s[1].
void FUN_006c3780(float* outA, float* outB, const float* base, const float* dir,
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
  sm[0] += off[0] * k; sm[1] += off[1] * k; sm[2] += off[2] * k;
  sm[4] += off[4] * k; sm[5] += off[5] * k; sm[6] += off[6] * k;
  sm[8] += off[8] * k; sm[9] += off[9] * k; sm[10] += off[10] * k;

  outB[0] = sm[0] * dir[0] + sm[4] * dir[1] + sm[8] * dir[2];
  outB[1] = sm[1] * dir[0] + sm[5] * dir[1] + sm[9] * dir[2];
  outB[2] = sm[2] * dir[0] + sm[6] * dir[1] + sm[10] * dir[2];

  outA[0] = sm[0] * base[0] + sm[4] * base[1] + sm[8] * base[2] + sm[12];
  outA[1] = sm[1] * base[0] + sm[5] * base[1] + sm[9] * base[2] + sm[13];
  outA[2] = sm[2] * base[0] + sm[6] * base[1] + sm[10] * base[2] + sm[14];
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
