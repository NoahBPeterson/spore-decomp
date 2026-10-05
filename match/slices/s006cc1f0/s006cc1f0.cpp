// Slice s006cc1f0: per-vertex bake helpers (see ../s006c5940/bake.h).
#include "../s006c5940/bake.h"

// @ 0x006cc1f0
bool FUN_006cc1f0(float* out, int count, int res, int* data, int vtx, const float* scalePair,
                  const char* params, int blockIdx, int assignIdx, int layout) {
  BakeCore(out, count, res, data, vtx, scalePair, params, blockIdx, assignIdx, layout,
           XF_WEIGHT2, CF_BYTE4);
  return true;
}

// @ 0x006cc550
bool FUN_006cc550(float* out, int count, int res, int* data, int vtx, const float* scalePair,
                  const char* params, int blockIdx, int assignIdx, int layout) {
  BakeCore(out, count, res, data, vtx, scalePair, params, blockIdx, assignIdx, layout,
           XF_WEIGHT2, CF_USHORT2);
  return true;
}

// @ 0x006cc870
bool FUN_006cc870(float* out, int count, int res, int* data, int vtx, const float* scalePair,
                  const char* params, int blockIdx, int assignIdx, int layout) {
  BakeCore(out, count, res, data, vtx, scalePair, params, blockIdx, assignIdx, layout,
           XF_WEIGHT2, CF_USHORT4);
  return true;
}

// @ 0x006ccbd0
bool FUN_006ccbd0(float* out, int count, int res, int* data, int vtx, const float* scalePair,
                  const char* params, int blockIdx, int assignIdx, int layout) {
  BakeCore(out, count, res, data, vtx, scalePair, params, blockIdx, assignIdx, layout,
           XF_WEIGHT3, CF_BYTE4);
  return true;
}
