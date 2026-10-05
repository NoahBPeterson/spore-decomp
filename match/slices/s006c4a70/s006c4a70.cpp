// Slice s006c4a70: EASTL introsort (quick_sort_impl / quick_sort) over the 24-byte
// keyed record, plus four per-vertex bake helpers that map packed vertex colours to
// a 2-float attribute.
#include "types.h"
#include <math.h>

struct Rec24 {
  uint64_t k0, k1, k2;
};

inline bool operator<(const Rec24& a, const Rec24& b) {
  return a.k0 < b.k0 || (a.k0 == b.k0 && a.k1 < b.k1);
}

void AdjustHeap(Rec24* base, int hole, int len, int top, Rec24 value); // 0x006c2bc0
void MakeHeap(Rec24* first, Rec24* last);                              // 0x006c33b0
void SortHeap(Rec24* first, Rec24* last);                              // 0x006c3430
Rec24* GetPartition(Rec24* first, Rec24* last, Rec24 pivot);           // 0x006c4870
void PartialSort(Rec24* first, Rec24* middle, Rec24* last);            // 0x006c4960
Rec24* Median(Rec24* a, Rec24* b, Rec24* c);                           // 0x006c2970
void InsertionSortA(Rec24* first, Rec24* last);                        // 0x006c27b0
void InsertionSortB(Rec24* first, Rec24* last);                        // 0x006c28a0

// ---------------------------------------------------------------------------
// Introsort
// ---------------------------------------------------------------------------

// @ 0x006c4a70
void QuickSortImpl(Rec24* first, Rec24* last, int depth) {
  int n = (int)(last - first);
  while (n > 0x1c && depth > 0) {
    Rec24 pivot = *Median(first, first + (last - first) / 2, last - 1);
    Rec24* mid = GetPartition(first, last, pivot);
    --depth;
    QuickSortImpl(mid, last, depth);
    n = (int)(mid - first);
    last = mid;
  }
  if (depth == 0)
    PartialSort(first, last, last);
}

static inline int Log2(int n) {
  int i = 0;
  while (n > 0) {
    n >>= 1;
    ++i;
  }
  return i - 1;
}

// @ 0x006c4c20
void QuickSort(Rec24* first, Rec24* last) {
  if (first != last) {
    int n = (int)(last - first);
    QuickSortImpl(first, last, 2 * Log2(n));
    if (n > 0x1c) {
      InsertionSortA(first, first + 0x1c);
      InsertionSortB(first + 0x1c, last);
    } else {
      InsertionSortA(first, last);
    }
  }
}

// ---------------------------------------------------------------------------
// Bake helpers
// ---------------------------------------------------------------------------

struct RefCounted {
  virtual void AddRef();
  virtual void Release();
};

// Block range/source descriptor: used both for the vertex source and for the
// packed-colour source. base at +4, u16 stride at +0xa.
void FUN_006c3550(float* outA, float* outB, const float* base, const float* dir,
                  const float* s, const int* idx, int layout); // 0x006c3550
void FUN_006c3780(float* outA, float* outB, const float* base, const float* dir,
                  const float* s, const int* idx, int layout); // 0x006c3780
void Handle_Assign(int blockInfo);                                 // 0x00424f70

// Common preamble: resolve the block descriptor, ref-count it and optionally
// assign the "retail" companion block.
static char* BakeBegin(int res, int blockIdx, int assignIdx, RefCounted** rc,
                       int* blockBase, uint16_t* blockStride) {
  char* e = (char*)(*(int*)(res + 8) + blockIdx * 0x20 + 0x10);
  *blockBase = *(int*)(e + 4);
  *rc = *(RefCounted**)(e + 0xc);
  *blockStride = *(uint16_t*)(e + 0xa);
  if (*rc) (*rc)->AddRef();
  if (assignIdx >= 0) Handle_Assign(*(int*)(res + 8) + assignIdx * 0x20 + 0x10);
  char* first = (char*)(*(int*)(res + 8) + blockIdx * 0x20 + 0x10);
  return first;
}

static void BakeEnd(RefCounted* rc) {
  if (rc) rc->Release();
}

// @ 0x006c4ca0  — byte-packed colour source, point transform.
bool FUN_006c4ca0(float* out, int count, int res, int* data, int vtx, const float* scalePair,
                  const char* params, int blockIdx, int assignIdx, int layout) {
  RefCounted* rc;
  int blockBase;
  uint16_t blockStride;
  BakeBegin(res, blockIdx, assignIdx, &rc, &blockBase, &blockStride);
  if (count) {
    float matA[4] = {1.0f, 0.0f, 0.0f, 0.0f};
    float matB[4] = {1.0f, 0.0f, 0.0f, 0.0f};
    for (int i = 0; i < count; ++i) {
      const unsigned char* pb = (const unsigned char*)(blockBase + blockStride * data[3]);
      int col[4] = {pb[0] / 3, pb[1] / 3, pb[2] / 3, pb[3] / 3};
      const float* q = (const float*)(*(int*)(vtx + 4) + (uint32_t)*(uint16_t*)(vtx + 0xa) * data[0]);
      float v[3] = {q[0], q[1], q[2]};
      float outA[3], outB[3];
      FUN_006c3550(outA, outB, v, matB, matA, col, layout);
      float dy = outA[1] - *(const float*)(params + 8);
      float dz = outA[2] - *(const float*)(params + 0xc);
      float ang = acosf(dy / sqrtf(dy * dy + dz * dz));
      float k = *(const float*)(params + 0x10);
      out[0] = scalePair[0] * ang * 1.2732406f * k;
      out[1] = (1.0f - scalePair[1] * outA[0]) * k;
      data += 6;
      out += 2;
    }
  }
  BakeEnd(rc);
  return true;
}

// @ 0x006c52c0  — 16-bit colour source (four lanes), point transform.
bool FUN_006c52c0(float* out, int count, int res, int* data, int vtx, const float* scalePair,
                  const char* params, int blockIdx, int assignIdx, int layout) {
  RefCounted* rc;
  int blockBase;
  uint16_t blockStride;
  BakeBegin(res, blockIdx, assignIdx, &rc, &blockBase, &blockStride);
  if (count) {
    float matA[4] = {1.0f, 0.0f, 0.0f, 0.0f};
    float matB[4] = {1.0f, 0.0f, 0.0f, 0.0f};
    for (int i = 0; i < count; ++i) {
      const uint16_t* pw = (const uint16_t*)(blockBase + blockStride * data[3]);
      int col[4] = {pw[0] / 3, pw[1] / 3, pw[2] / 3, pw[3] / 3};
      const float* q = (const float*)(*(int*)(vtx + 4) + (uint32_t)*(uint16_t*)(vtx + 0xa) * data[0]);
      float v[3] = {q[0], q[1], q[2]};
      float outA[3], outB[3];
      FUN_006c3550(outA, outB, v, matB, matA, col, layout);
      float dy = outA[1] - *(const float*)(params + 8);
      float dz = outA[2] - *(const float*)(params + 0xc);
      float ang = acosf(dy / sqrtf(dy * dy + dz * dz));
      float k = *(const float*)(params + 0x10);
      out[0] = scalePair[0] * ang * 1.2732406f * k;
      out[1] = (1.0f - scalePair[1] * outA[0]) * k;
      data += 6;
      out += 2;
    }
  }
  BakeEnd(rc);
  return true;
}

// @ 0x006c4fd0  — 16-bit colour source (two lanes), point transform.
bool FUN_006c4fd0(float* out, int count, int res, int* data, int vtx, const float* scalePair,
                  const char* params, int blockIdx, int assignIdx, int layout) {
  RefCounted* rc;
  int blockBase;
  uint16_t blockStride;
  BakeBegin(res, blockIdx, assignIdx, &rc, &blockBase, &blockStride);
  if (count) {
    float matA[4] = {1.0f, 0.0f, 0.0f, 0.0f};
    float matB[4] = {1.0f, 0.0f, 0.0f, 0.0f};
    for (int i = 0; i < count; ++i) {
      const uint16_t* pw = (const uint16_t*)(blockBase + blockStride * data[3]);
      int col[4] = {pw[0] / 3, pw[1] / 3, 0, 0};
      const float* q = (const float*)(*(int*)(vtx + 4) + (uint32_t)*(uint16_t*)(vtx + 0xa) * data[0]);
      float v[3] = {q[0], q[1], q[2]};
      float outA[3], outB[3];
      FUN_006c3550(outA, outB, v, matB, matA, col, layout);
      float dy = outA[1] - *(const float*)(params + 8);
      float dz = outA[2] - *(const float*)(params + 0xc);
      float ang = acosf(dy / sqrtf(dy * dy + dz * dz));
      float k = *(const float*)(params + 0x10);
      out[0] = scalePair[0] * ang * 1.2732406f * k;
      out[1] = (1.0f - scalePair[1] * outA[0]) * k;
      data += 6;
      out += 2;
    }
  }
  BakeEnd(rc);
  return true;
}

// @ 0x006c55f0  — byte-packed colour source, offset transform.
bool FUN_006c55f0(float* out, int count, int res, int* data, int vtx, const float* scalePair,
                  const char* params, int blockIdx, int assignIdx, int layout) {
  RefCounted* rc;
  int blockBase;
  uint16_t blockStride;
  BakeBegin(res, blockIdx, assignIdx, &rc, &blockBase, &blockStride);
  if (count) {
    float matB[4] = {1.0f, 0.0f, 0.0f, 0.0f};
    data += 2;  // the offset form addresses data[-2] as the vertex and data[1] as colour
    for (int i = 0; i < count; ++i) {
      const unsigned char* pb = (const unsigned char*)(blockBase + blockStride * data[1]);
      int col[4] = {pb[0] / 3, pb[1] / 3, pb[2] / 3, pb[3] / 3};
      const float* q = (const float*)(*(int*)(vtx + 4) + (uint32_t)*(uint16_t*)(vtx + 0xa) * data[-2]);
      float v[3] = {q[0], q[1], q[2]};
      float off[4] = {0.0f, 0.0f, 0.0f, 0.0f};
      float outA[3], outB[3];
      FUN_006c3780(outA, outB, v, matB, off, col, layout);
      float dy = outA[1] - *(const float*)(params + 8);
      float dz = outA[2] - *(const float*)(params + 0xc);
      float ang = acosf(dy / sqrtf(dy * dy + dz * dz));
      float k = *(const float*)(params + 0x10);
      out[0] = scalePair[0] * ang * 1.2732406f * k;
      out[1] = (1.0f - scalePair[1] * outA[0]) * k;
      data += 6;
      out += 2;
    }
  }
  BakeEnd(rc);
  return true;
}
