// Slice s006c9ab0: per-vertex bake helpers (see ../s006c5940/bake.h).
// The object cache keys on the slice source + headers in this directory only, so this
// comment also serves as a cache-buster: any edit to the shared ../s006c5940/bake.h
// needs a byte change here to force a fresh compile.
#include "../s006c5940/bake.h"

// @ 0x006c9ab0
bool FUN_006c9ab0(float* out, int count, int res, int* data, int vtx, const float* scalePair,
                  const char* params, int blockIdx, int assignIdx, int layout) {
  BakeCore(out, count, res, data, vtx, scalePair, params, blockIdx, assignIdx, layout,
           XF_WEIGHT3, CF_BYTE4);
  return true;
}

// @ 0x006c9e30
bool FUN_006c9e30(float* out, int count, int res, int* data, int vtx, const float* scalePair,
                  const char* params, int blockIdx, int assignIdx, int layout) {
  BakeCore(out, count, res, data, vtx, scalePair, params, blockIdx, assignIdx, layout,
           XF_WEIGHT3, CF_USHORT2);
  return true;
}

// @ 0x006ca180
bool FUN_006ca180(float* out, int count, int res, int* data, int vtx, const float* scalePair,
                  const char* params, int blockIdx, int assignIdx, int layout) {
  BakeCore(out, count, res, data, vtx, scalePair, params, blockIdx, assignIdx, layout,
           XF_WEIGHT3, CF_USHORT4);
  return true;
}

// @ 0x006ca500
bool FUN_006ca500(float* out, int count, int res, int* data, int vtx, const float* scalePair,
                  const char* params, int blockIdx, int assignIdx, int layout) {
  BakeCore(out, count, res, data, vtx, scalePair, params, blockIdx, assignIdx, layout,
           XF_WEIGHT3, CF_BYTE4);
  return true;
}
