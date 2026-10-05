// Slice s006c8d80: per-vertex bake helpers (see ../s006c5940/bake.h).
#include "../s006c5940/bake.h"

// @ 0x006c8d80
bool FUN_006c8d80(float* out, int count, int res, int* data, int vtx, const float* scalePair,
                  const char* params, int blockIdx, int assignIdx, int layout) {
  BakeCore(out, count, res, data, vtx, scalePair, params, blockIdx, assignIdx, layout,
           XF_OFFSET, CF_USHORT4);
  return true;
}

// @ 0x006c90d0
bool FUN_006c90d0(float* out, int count, int res, int* data, int vtx, const float* scalePair,
                  const char* params, int blockIdx, int assignIdx, int layout) {
  BakeCore(out, count, res, data, vtx, scalePair, params, blockIdx, assignIdx, layout,
           XF_WEIGHT2, CF_BYTE4);
  return true;
}

// @ 0x006c9430
bool FUN_006c9430(float* out, int count, int res, int* data, int vtx, const float* scalePair,
                  const char* params, int blockIdx, int assignIdx, int layout) {
  BakeCore(out, count, res, data, vtx, scalePair, params, blockIdx, assignIdx, layout,
           XF_WEIGHT2, CF_USHORT2);
  return true;
}

// @ 0x006c9750
bool FUN_006c9750(float* out, int count, int res, int* data, int vtx, const float* scalePair,
                  const char* params, int blockIdx, int assignIdx, int layout) {
  BakeCore(out, count, res, data, vtx, scalePair, params, blockIdx, assignIdx, layout,
           XF_WEIGHT2, CF_USHORT4);
  return true;
}
