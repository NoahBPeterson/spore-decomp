// Slice s006c6630: per-vertex bake helpers, weighted block-matrix form (x2 / x3).
// Each entry point resolves a baked-arena block, assigns the "weight" block into a
// local handle, and maps every packed vertex colour to a 2-float attribute
// (angle, 1-cos) through the weighted transform. The block-table layout matches the
// point-transform helpers of s006c4a70.
#include "types.h"
#include <math.h>
#include <xmmintrin.h>

struct RefCounted {
  virtual void AddRef();
  virtual void Release();
};

// Block descriptor: the 0x10-byte header of a 0x20-byte block-table entry.
// Base pointer at +4, u16 element stride at +0xa, ref-counted companion at +0xc.
struct Handle {
  int m0;
  int m4;
  uint16_t m8;
  uint16_t ma;
  RefCounted* mc;
  Handle& Assign(const Handle& src);  // 0x00424f70 (thiscall, one stack argument)
};

struct BlockEntry {
  Handle desc;
  int m10;
  int m14;
  int m18;
  int m1c;
};

// Header in front of the entries (entries start at +0x10, 0x20 bytes each).
struct BlockTable {
  int m0;
  int m4;
  int m8;
  int mc;
  BlockEntry entries[1];
};

// Baked arena resource: block-table pointer at +8.
struct BakeResource {
  int m0;
  int m4;
  BlockTable* table;
};

// Vertex range: element base at +4, u16 element stride at +0xa.
struct VertexRange {
  char pad0[4];
  int base;
  char pad1[2];
  uint16_t stride;
};

// Per-vertex parameters: output scale at +0x10.
struct BakeParams {
  char pad0[0x10];
  float scale;
};

void FUN_006c3b90(float* outA, float* outB, const float* base, const float* dir,
                  const float* s, const int* idx, int layout); // weighted x2
void FUN_006c4200(float* outA, float* outB, const float* base, const float* dir,
                  const float* s, const int* idx, int layout); // weighted x3

enum BakeXForm { XF_WEIGHT2, XF_WEIGHT3 };
enum BakeColor { CF_USHORT4, CF_BYTE4, CF_USHORT2 };
enum BakeWeight { WF_FLOAT3, WF_BYTE4 };

static const float kByteWeight = 0.0039215688593685627f; // 0x3b808081, 1/255
static const float kAngleScale = 1.2732406f;             // 0x3fa2f98c

static void BakeCore(float* out, int count, int res, const int* data, int vtx,
                     const float* scalePair, const BakeParams* params, int blockIdx,
                     int assignIdx, int layout, BakeXForm xf, BakeColor cf, BakeWeight wf) {
  const BlockTable* table = ((const BakeResource*)res)->table;
  const BlockEntry* e = &table->entries[blockIdx];
  int blockBase = e->desc.m4;
  uint16_t blockStride = e->desc.ma;
  RefCounted* rc = e->desc.mc;
  if (rc) rc->AddRef();

  Handle assigned;
  assigned.m0 = 0;
  assigned.m4 = 0;
  assigned.m8 = 0;
  assigned.ma = 0;
  assigned.mc = 0;
  if (assignIdx >= 0) assigned.Assign(table->entries[assignIdx].desc);

  const VertexRange* vr = (const VertexRange*)vtx;
  int n = count;
  if (n) {
    float dir[3] = {1.0f, 0.0f, 0.0f};
    do {
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

      const unsigned char* wp =
          (const unsigned char*)(assigned.m4 + (uint32_t)assigned.ma * data[2]);
      float s[4];
      if (wf == WF_FLOAT3) {
        const float* wf3 = (const float*)wp;
        s[0] = wf3[0]; s[1] = wf3[1]; s[2] = wf3[2]; s[3] = 0.0f;
      } else {
        s[0] = wp[0] * kByteWeight;
        s[1] = wp[1] * kByteWeight;
        s[2] = wp[2] * kByteWeight;
        s[3] = wp[3] * kByteWeight;
      }

      const float* q = (const float*)(vr->base + (uint32_t)vr->stride * data[0]);
      float base[3] = {q[0], q[1], q[2]};
      float outA[3], outB[3];
      if (xf == XF_WEIGHT2)
        FUN_006c3b90(outA, outB, base, dir, s, col, layout);
      else
        FUN_006c4200(outA, outB, base, dir, s, col, layout);

      __m128 dy = _mm_sub_ss(_mm_load_ss(&outA[1]), _mm_load_ss(&scalePair[2]));
      __m128 dz = _mm_sub_ss(_mm_load_ss(&outA[2]), _mm_load_ss(&scalePair[3]));
      __m128 len2 = _mm_add_ss(_mm_mul_ss(dy, dy), _mm_mul_ss(dz, dz));
      float ratio = _mm_cvtss_f32(_mm_div_ss(dy, _mm_sqrt_ss(len2)));
      float ang = acosf(ratio);
      float k = params->scale;

      __m128 o0 = _mm_mul_ss(_mm_load_ss(&scalePair[0]), _mm_set_ss(ang));
      o0 = _mm_mul_ss(o0, _mm_set_ss(kAngleScale));
      o0 = _mm_mul_ss(o0, _mm_set_ss(k));
      _mm_store_ss(&out[0], o0);

      __m128 o1 = _mm_mul_ss(_mm_load_ss(&scalePair[1]), _mm_load_ss(&outA[0]));
      o1 = _mm_sub_ss(_mm_set_ss(1.0f), o1);
      o1 = _mm_mul_ss(o1, _mm_set_ss(k));
      _mm_store_ss(&out[1], o1);

      data += 6;
      out += 2;
    } while (--n);
  }
  if (assigned.mc) assigned.mc->Release();
  if (rc) rc->Release();
}

// @ 0x006c6630
bool FUN_006c6630(float* out, int count, int res, int* data, int vtx, const float* scalePair,
                  const char* params, int blockIdx, int assignIdx, int layout) {
  BakeCore(out, count, res, data, vtx, scalePair, (const BakeParams*)params, blockIdx, assignIdx,
           layout, XF_WEIGHT2, CF_USHORT4, WF_FLOAT3);
  return true;
}

// @ 0x006c6990
bool FUN_006c6990(float* out, int count, int res, int* data, int vtx, const float* scalePair,
                  const char* params, int blockIdx, int assignIdx, int layout) {
  BakeCore(out, count, res, data, vtx, scalePair, (const BakeParams*)params, blockIdx, assignIdx,
           layout, XF_WEIGHT3, CF_BYTE4, WF_BYTE4);
  return true;
}

// @ 0x006c6d10
bool FUN_006c6d10(float* out, int count, int res, int* data, int vtx, const float* scalePair,
                  const char* params, int blockIdx, int assignIdx, int layout) {
  BakeCore(out, count, res, data, vtx, scalePair, (const BakeParams*)params, blockIdx, assignIdx,
           layout, XF_WEIGHT3, CF_USHORT2, WF_BYTE4);
  return true;
}

// @ 0x006c7060
bool FUN_006c7060(float* out, int count, int res, int* data, int vtx, const float* scalePair,
                  const char* params, int blockIdx, int assignIdx, int layout) {
  BakeCore(out, count, res, data, vtx, scalePair, (const BakeParams*)params, blockIdx, assignIdx,
           layout, XF_WEIGHT3, CF_USHORT4, WF_BYTE4);
  return true;
}
