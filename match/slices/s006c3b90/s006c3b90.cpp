// Slice s006c3b90: EASTL sort machinery over a 24-byte keyed record plus two
// per-vertex "bake" helpers that combine N weighted block matrices.
#include "types.h"
#include <math.h>

// 24-byte record: a 16-byte key (two little-endian 64-bit words) and an 8-byte payload.
// operator< compares the key as (high,low) 64-bit words: f1,f0 then f3,f2.
struct Rec24 {
  uint64_t k0, k1, k2;
};

inline bool operator<(const Rec24& a, const Rec24& b) {
  return a.k0 < b.k0 || (a.k0 == b.k0 && a.k1 < b.k1);
}

void AdjustHeap(Rec24* base, int hole, int len, int top, Rec24 value); // 0x006c2bc0
void MakeHeap(Rec24* first, Rec24* last);                              // 0x006c33b0
void SortHeap(Rec24* first, Rec24* last);                              // 0x006c3430

struct Mat4 {
  float m[16];
  void SetRows(const float* r0, const float* r1, const float* r2, const float* r3);
  void Assign(const float* a, const float* b, const float* c, const float* d); // 0x006c2740
};
float* ScaleMatrixReversed(float* out, const float* m, float s); // 0x006c2cd0

inline void Mat4::SetRows(const float* r0, const float* r1, const float* r2, const float* r3) {
  Assign(r0, r1, r2, r3);
}

// @ 0x006c2740
void Mat4::Assign(const float* a, const float* b, const float* c, const float* d)
{
  for (int i = 0; i < 4; ++i) m[i] = a[i];
  for (int i = 0; i < 4; ++i) m[4 + i] = b[i];
  for (int i = 0; i < 4; ++i) m[8 + i] = c[i];
  for (int i = 0; i < 4; ++i) m[12 + i] = d[i];
}

// ---------------------------------------------------------------------------
// EASTL get_partition, instantiated for Rec24 (pivot passed by value).
// ---------------------------------------------------------------------------

// @ 0x006c4870
Rec24* GetPartition(Rec24* first, Rec24* last, Rec24 pivot) {
  for (;; ++first) {
    while (*first < pivot) ++first;
    --last;
    while (pivot < *last) --last;
    if (first >= last) return first;
    Rec24 tmp = *first;
    *first = *last;
    *last = tmp;
  }
}

// ---------------------------------------------------------------------------
// EASTL partial_sort (also used as the heap-sort fallback of introsort).
// ---------------------------------------------------------------------------

// @ 0x006c4960
void PartialSort(Rec24* first, Rec24* middle, Rec24* last) {
  MakeHeap(first, middle);
  for (Rec24* i = middle; i < last; ++i) {
    if (*i < *first) {
      Rec24 value = *i;
      *i = *first;
      AdjustHeap(first, 0, (int)(middle - first), 0, value);
    }
  }
  SortHeap(first, middle);
}

// ---------------------------------------------------------------------------
// Weighted block-matrix bake (N = 2 / N = 3)
// ---------------------------------------------------------------------------

// Combines `count` weighted block matrices selected by idx[k] (k=0..count) with
// weights s[k], then transforms base and dir through the result.
static void BakeWeighted(float* outA, float* outB, const float* base, const float* dir,
                         const float* s, const int* idx, int layout, int count) {
  uint16_t stride = *(uint16_t*)(layout + 0xa);
  char* seg = (char*)*(int*)(layout + 4);
  char* blk = seg + stride * idx[0];
  float fourth[4] = {0.0f, 0.0f, 0.0f, 1.0f};
  Mat4 m;
  m.SetRows((const float*)blk, (const float*)(blk + 0x10), (const float*)(blk + 0x20), fourth);
  float sm[16];
  ScaleMatrixReversed(sm, m.m, s[0]);

  for (int k = 1; k <= count; ++k) {
    const float* q = (const float*)(seg + stride * idx[k]);
    float w = s[k];
    float zw = w * 0.0f;
    sm[0]  += q[0]  * w; sm[1]  += q[1]  * w; sm[2]  += q[2]  * w; sm[3]  += q[3]  * w;
    sm[4]  += q[4]  * w; sm[5]  += q[5]  * w; sm[6]  += q[6]  * w; sm[7]  += q[7]  * w;
    sm[8]  += q[8]  * w; sm[9]  += q[9]  * w; sm[10] += q[10] * w; sm[11] += q[11] * w;
    sm[12] += zw; sm[13] += zw; sm[14] += zw; sm[15] += w;
  }

  float d0 = dir[0], d1 = dir[1], d2 = dir[2];
  float b0 = base[0], b1 = base[1], b2 = base[2];

  outB[0] = ((d2 * sm[8] + d0 * sm[0]) + d1 * sm[4]) + sm[12] * 0.0f;
  outB[1] = ((d1 * sm[5] + d2 * sm[9]) + d0 * sm[1]) + sm[13] * 0.0f;
  outB[2] = ((d1 * sm[6] + d2 * sm[10]) + d0 * sm[2]) + sm[14] * 0.0f;

  outA[0] = ((b2 * sm[8] + b0 * sm[0]) + b1 * sm[4]) + sm[12];
  outA[1] = ((b1 * sm[5] + b2 * sm[9]) + b0 * sm[1]) + sm[13];
  outA[2] = ((b1 * sm[6] + b2 * sm[10]) + b0 * sm[2]) + sm[14];
}
// @ 0x006c3b90
float* FUN_006c3b90(float* outA, float* outB, const float* base, const float* dir,
                    const float* s, const int* idx, int layout) {
  BakeWeighted(outA, outB, base, dir, s, idx, layout, 2);
  return outA;
}

// @ 0x006c4200
float* FUN_006c4200(float* outA, float* outB, const float* base, const float* dir,
                    const float* s, const int* idx, int layout) {
  BakeWeighted(outA, outB, base, dir, s, idx, layout, 3);
  return outA;
}
