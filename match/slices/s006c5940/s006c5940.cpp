// Slice s006c5940: per-vertex bake helpers (see ../s006c5940/bake.h).
//  006c5940 offset transform, 2-lane 16-bit colours
//  006c5c60 offset transform, 4-lane 16-bit colours
//  006c5fb0 weighted-x2 transform, 4-lane byte colours
//  006c6310 weighted-x2 transform, 2-lane 16-bit colours
#include "../s006c5940/bake.h"

// @ 0x006c5940
bool FUN_006c5940(float* out, int count, int res, int* data, int vtx, const float* scalePair,
                  const char* params, int blockIdx, int assignIdx, int layout) {
  BakeCore(out, count, res, data, vtx, scalePair, params, blockIdx, assignIdx, layout,
           XF_OFFSET, CF_USHORT2);
  return true;
}

// @ 0x006c5c60
bool FUN_006c5c60(float* out, int count, int res, int* data, int vtx, const float* scalePair,
                  const char* params, int blockIdx, int assignIdx, int layout) {
  BakeCore(out, count, res, data, vtx, scalePair, params, blockIdx, assignIdx, layout,
           XF_OFFSET, CF_USHORT4);
  return true;
}

// @ 0x006c5fb0
bool FUN_006c5fb0(float* out, int count, int res, int* data, int vtx, const float* scalePair,
                  const char* params, int blockIdx, int assignIdx, int layout) {
  BakeCore(out, count, res, data, vtx, scalePair, params, blockIdx, assignIdx, layout,
           XF_WEIGHT2, CF_BYTE4);
  return true;
}

// @ 0x006c6310
bool FUN_006c6310(float* out, int count, int res, int* data, int vtx, const float* scalePair,
                  const char* params, int blockIdx, int assignIdx, int layout) {
  BakeCore(out, count, res, data, vtx, scalePair, params, blockIdx, assignIdx, layout,
           XF_WEIGHT2, CF_USHORT2);
  return true;
}
