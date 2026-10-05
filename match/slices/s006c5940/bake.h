// Shared implementation of the cBakedArenaResource per-vertex bake helpers used by
// slices s006c5940 .. s006cc1f0. Each slice's functions are thin, differently-typed
// instantiations of this core: they resolve a baked-arena block, ref-count it, and
// for every vertex map the packed vertex colour through one of four block transforms
// into a 2-float attribute (angle, and 1-cos).
#pragma once
#include "types.h"
#include <math.h>

struct RefCounted {
  virtual void AddRef();
  virtual void Release();
};

// Base address at +4, u16 element stride at +0xa.
struct BakeRange {
  char pad0[4];
  int base;         // +4
  char pad1[2];
  uint16_t stride;  // +0xa
};

// Block-matrix transforms (defined in slices s006c2cd0 / s006c3b90).
void FUN_006c3550(float* outA, float* outB, const float* base, const float* dir,
                  const float* s, const int* idx, int layout); // point transform
void FUN_006c3780(float* outA, float* outB, const float* base, const float* dir,
                  const float* s, const int* idx, int layout); // offset transform
void FUN_006c3b90(float* outA, float* outB, const float* base, const float* dir,
                  const float* s, const int* idx, int layout); // weighted x2
void FUN_006c4200(float* outA, float* outB, const float* base, const float* dir,
                  const float* s, const int* idx, int layout); // weighted x3

void Handle_Assign(int blockInfo); // 0x00424f70

enum BakeXForm { XF_POINT, XF_OFFSET, XF_WEIGHT2, XF_WEIGHT3 };
enum BakeColor { CF_BYTE4, CF_USHORT4, CF_USHORT2 };

static void BakeCore(float* out, int count, int res, const int* data, int vtx,
                     const float* scalePair, const char* params, int blockIdx, int assignIdx,
                     int layout, BakeXForm xf, BakeColor cf) {
  char* e = (char*)(*(int*)(res + 8) + blockIdx * 0x20 + 0x10);
  int blockBase = *(int*)(e + 4);
  RefCounted* rc = *(RefCounted**)(e + 0xc);
  uint16_t blockStride = *(uint16_t*)(e + 0xa);
  if (rc) rc->AddRef();
  if (assignIdx >= 0) Handle_Assign(*(int*)(res + 8) + assignIdx * 0x20 + 0x10);

  for (int i = 0; i < count; ++i) {
    const unsigned char* cb = (const unsigned char*)(blockBase + blockStride * data[3]);
    int col[4];
    if (cf == CF_BYTE4) {
      col[0] = cb[0] / 3; col[1] = cb[1] / 3; col[2] = cb[2] / 3; col[3] = cb[3] / 3;
    } else if (cf == CF_USHORT4) {
      const uint16_t* cw = (const uint16_t*)cb;
      col[0] = cw[0] / 3; col[1] = cw[1] / 3; col[2] = cw[2] / 3; col[3] = cw[3] / 3;
    } else {
      const uint16_t* cw = (const uint16_t*)cb;
      col[0] = cw[0] / 3; col[1] = cw[1] / 3; col[2] = 0; col[3] = 0;
    }

    const float* q = (const float*)(*(int*)(vtx + 4) + (uint32_t)*(uint16_t*)(vtx + 0xa) * data[0]);
    float v[3] = {q[0], q[1], q[2]};
    float matA[4] = {1.0f, 0.0f, 0.0f, 0.0f};
    float matB[4] = {1.0f, 0.0f, 0.0f, 0.0f};
    float outA[3], outB[3];
    switch (xf) {
      case XF_POINT:   FUN_006c3550(outA, outB, v, matB, matA, col, layout); break;
      case XF_OFFSET:  FUN_006c3780(outA, outB, v, matB, matA, col, layout); break;
      case XF_WEIGHT2: FUN_006c3b90(outA, outB, v, matB, matA, col, layout); break;
      case XF_WEIGHT3: FUN_006c4200(outA, outB, v, matB, matA, col, layout); break;
    }

    float dy = outA[1] - *(const float*)(params + 8);
    float dz = outA[2] - *(const float*)(params + 0xc);
    float ang = acosf(dy / sqrtf(dy * dy + dz * dz));
    float k = *(const float*)(params + 0x10);
    out[0] = scalePair[0] * ang * 1.2732406f * k;
    out[1] = (1.0f - scalePair[1] * outA[0]) * k;

    data += 6;
    out += 2;
  }
  if (rc) rc->Release();
}
