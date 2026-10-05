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
  void SetRows(const float* r0, const float* r1, const float* r2, const float* r3); // 0x006c2740
};
float* ScaleMatrixReversed(float* out, const float* m, float s); // 0x006c2cd0

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
    sm[0]  += q[0]  * w; sm[1]  += q[1]  * w; sm[2]  += q[2]  * w; sm[3]  += q[3]  * w;
    sm[4]  += q[4]  * w; sm[5]  += q[5]  * w; sm[6]  += q[6]  * w; sm[7]  += q[7]  * w;
    sm[8]  += q[8]  * w; sm[9]  += q[9]  * w; sm[10] += q[10] * w; sm[11] += q[11] * w;
  }

  outB[0] = sm[0] * dir[0] + sm[4] * dir[1] + sm[8] * dir[2];
  outB[1] = sm[1] * dir[0] + sm[5] * dir[1] + sm[9] * dir[2];
  outB[2] = sm[2] * dir[0] + sm[6] * dir[1] + sm[10] * dir[2];

  outA[0] = sm[0] * base[0] + sm[4] * base[1] + sm[8] * base[2] + sm[12];
  outA[1] = sm[1] * base[0] + sm[5] * base[1] + sm[9] * base[2] + sm[13];
  outA[2] = sm[2] * base[0] + sm[6] * base[1] + sm[10] * base[2] + sm[14];
}

// @ 0x006c3b90
void FUN_006c3b90(float* outA, float* outB, const float* base, const float* dir,
                  const float* s, const int* idx, int layout) {
  BakeWeighted(outA, outB, base, dir, s, idx, layout, 2);
}

// @ 0x006c4200
void FUN_006c4200(float* outA, float* outB, const float* base, const float* dir,
                  const float* s, const int* idx, int layout) {
  BakeWeighted(outA, outB, base, dir, s, idx, layout, 3);
}
