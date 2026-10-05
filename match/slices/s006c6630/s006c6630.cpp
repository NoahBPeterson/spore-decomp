// Slice s006c6630: per-vertex bake helpers (see ../s006c5940/bake.h).
#include "../s006c5940/bake.h"

// @ 0x006c6630
bool FUN_006c6630(float* out, int count, int res, int* data, int vtx, const float* scalePair,
                  const char* params, int blockIdx, int assignIdx, int layout) {
  BakeCore(out, count, res, data, vtx, scalePair, params, blockIdx, assignIdx, layout,
           XF_WEIGHT2, CF_USHORT4);
  return true;
}

// @ 0x006c6990
bool FUN_006c6990(float* out, int count, int res, int* data, int vtx, const float* scalePair,
                  const char* params, int blockIdx, int assignIdx, int layout) {
  BakeCore(out, count, res, data, vtx, scalePair, params, blockIdx, assignIdx, layout,
           XF_WEIGHT3, CF_BYTE4);
  return true;
}

// @ 0x006c6d10
bool FUN_006c6d10(float* out, int count, int res, int* data, int vtx, const float* scalePair,
                  const char* params, int blockIdx, int assignIdx, int layout) {
  BakeCore(out, count, res, data, vtx, scalePair, params, blockIdx, assignIdx, layout,
           XF_WEIGHT3, CF_USHORT2);
  return true;
}

// @ 0x006c7060
bool FUN_006c7060(float* out, int count, int res, int* data, int vtx, const float* scalePair,
                  const char* params, int blockIdx, int assignIdx, int layout) {
  BakeCore(out, count, res, data, vtx, scalePair, params, blockIdx, assignIdx, layout,
           XF_WEIGHT3, CF_USHORT4);
  return true;
}
