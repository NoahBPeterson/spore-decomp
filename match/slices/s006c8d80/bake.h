// Shared implementation of the cBakedArenaResource per-vertex bake helpers used by
// slices s006c5940 .. s006cc1f0. Each slice's functions are thin, differently-typed
// instantiations of this core: they resolve a baked-arena block, ref-count it, and
// for every vertex map the packed vertex colour through one of four block transforms
// into a 2-float attribute (angle, and 1-cos).
//
// Local copy for s006c8d80: the four functions in this slice consume the transform
// result as (outA[1], outA[2], outA[0]) for (1-cos, dy, dz), whereas s006c5940 uses
// (outA[0], outA[1], outA[2]).  Keeping the variant here avoids racing the shared
// ../s006c5940/bake.h, which another slice is editing.
#pragma once
#include "types.h"
#include <math.h>
#include <xmmintrin.h>

struct RefCounted {
  virtual void AddRef();
  virtual void Release();
};

// 16-byte arena-block descriptor: base address at +4, u16 element stride at
// +0xa, ref-counted payload at +0xc.
struct BakeRange {
  int unk0;          // +0
  int base;          // +4
  uint16_t unk8;     // +8
  uint16_t stride;   // +0xa
  RefCounted* rc;    // +0xc
};

// Handle_Assign (0x00424f70): __thiscall, dst in ecx, src on the stack. Named by
// its address so the resolver binds it.
void FUN_00424f70(void* src);   // Handle_Assign

// Block-matrix transforms (defined in slices s006c2cd0 / s006c3b90).
void FUN_006c3550(float* outA, float* outB, const float* base, const float* dir,
                  const float* s, const int* idx, int layout); // point transform
void FUN_006c3780(float* outA, float* outB, const float* base, const float* dir,
                  const float* s, const int* idx, int layout); // offset transform
void FUN_006c3b90(float* outA, float* outB, const float* base, const float* dir,
                  const float* s, const int* idx, int layout); // weighted x2
void FUN_006c4200(float* outA, float* outB, const float* base, const float* dir,
                  const float* s, const int* idx, int layout); // weighted x3

enum BakeXForm { XF_POINT, XF_OFFSET, XF_WEIGHT2, XF_WEIGHT3 };
enum BakeColor { CF_BYTE4, CF_USHORT4, CF_USHORT2 };

static __forceinline void BakeCore(float* out, int count, int res, const int* data, int vtx,
                     const float* scalePair, const char* params, int blockIdx, int assignIdx,
                     int layout, BakeXForm xf, BakeColor cf) {
  char* e = (char*)(*(int*)(res + 8) + blockIdx * 0x20 + 0x10);

  // Bake block (colours): copied out of the block table and AddRef'd.
  BakeRange blk;
  blk.unk0 = *(int*)(e + 0);
  blk.base = *(int*)(e + 4);
  blk.unk8 = *(uint16_t*)(e + 8);
  blk.stride = *(uint16_t*)(e + 0xa);
  blk.rc = *(RefCounted**)(e + 0xc);
  if (blk.rc) blk.rc->AddRef();

  // Companion "assign" block (the s vector): a zeroed range is assigned from
  // the block at assignIdx.
  BakeRange asg = {0, 0, 0, 0, 0};
  if (assignIdx >= 0) {
    const BakeRange* ai =
        (const BakeRange*)(*(int*)(res + 8) + assignIdx * 0x20 + 0x10);
    ((void(__thiscall*)(void*, const void*))FUN_00424f70)(&asg, ai);
  }

  for (int i = 0; i < count; ++i) {
    const unsigned char* cb = (const unsigned char*)(blk.base + blk.stride * data[3]);
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
    // Transform-specific offset vector: point transforms use a constant, the
    // others take 2 (offset), 3 (weighted x2) or 4 (weighted x3) floats from the
    // assigned companion block.
    float s[4] = {1.0f, 0.0f, 0.0f, 0.0f};
    if (xf != XF_POINT) {
      const float* bp = (const float*)(asg.base + asg.stride * data[2]);
      s[0] = bp[0];
      s[1] = bp[1];
      if (xf == XF_WEIGHT2 || xf == XF_WEIGHT3) {
        s[2] = bp[2];
        if (xf == XF_WEIGHT3) s[3] = bp[3];
      }
    }
    float dir[3] = {1.0f, 0.0f, 0.0f};
    float outA[3], outB[3];
    switch (xf) {
      case XF_POINT:   FUN_006c3550(outA, outB, v, dir, s, col, layout); break;
      case XF_OFFSET:  FUN_006c3780(outA, outB, v, dir, s, col, layout); break;
      case XF_WEIGHT2: FUN_006c3b90(outA, outB, v, dir, s, col, layout); break;
      case XF_WEIGHT3: FUN_006c4200(outA, outB, v, dir, s, col, layout); break;
    }

    // This slice's instantiations read the transform result rotated by one:
    // 1-cos from outA[1], dy from outA[2], dz from outA[0].
    __m128 vone = _mm_mul_ss(_mm_load_ss(&scalePair[1]), _mm_load_ss(&outA[1]));
    __m128 vdy = _mm_sub_ss(_mm_load_ss(&outA[2]), _mm_load_ss(&scalePair[2]));
    __m128 vdz = _mm_sub_ss(_mm_load_ss(&outA[0]), _mm_load_ss(&scalePair[3]));
    __m128 len2 = _mm_add_ss(_mm_mul_ss(vdy, vdy), _mm_mul_ss(vdz, vdz));
    float ratio = _mm_cvtss_f32(_mm_div_ss(vdy, _mm_sqrt_ss(len2)));
    float ang = acosf(ratio);
    float k = *(const float*)(params + 0x10);
    __m128 o0 = _mm_mul_ss(_mm_load_ss(&scalePair[0]), _mm_set_ss(ang));
    o0 = _mm_mul_ss(o0, _mm_set_ss(1.2732406f));
    o0 = _mm_mul_ss(o0, _mm_set_ss(k));
    _mm_store_ss(&out[0], o0);
    __m128 o1 = _mm_sub_ss(_mm_set_ss(1.0f), vone);
    o1 = _mm_mul_ss(o1, _mm_set_ss(k));
    _mm_store_ss(&out[1], o1);

    data += 6;
    out += 2;
  }
  if (asg.rc) asg.rc->Release();
  if (blk.rc) blk.rc->Release();
}
