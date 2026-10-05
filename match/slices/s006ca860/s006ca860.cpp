// Slice s006ca860: per-vertex bake helpers (see ../s006c5940/bake.h).
#include "../s006c5940/bake.h"

// @ 0x006ca860
bool FUN_006ca860(float* out, int count, int res, int* data, int vtx, const float* scalePair,
                  const char* params, int blockIdx, int assignIdx, int layout) {
  BakeCore(out, count, res, data, vtx, scalePair, params, blockIdx, assignIdx, layout,
           XF_WEIGHT3, CF_USHORT2);
  return true;
}

// @ 0x006cab80
bool FUN_006cab80(float* out, int count, int res, int* data, int vtx, const float* scalePair,
                  const char* params, int blockIdx, int assignIdx, int layout) {
  BakeCore(out, count, res, data, vtx, scalePair, params, blockIdx, assignIdx, layout,
           XF_WEIGHT3, CF_USHORT4);
  return true;
}

// @ 0x006caee0
bool FUN_006caee0(float* out, int count, int res, int* data, int vtx, const float* scalePair,
                  const char* params, int blockIdx, int assignIdx, int layout) {
  BakeCore(out, count, res, data, vtx, scalePair, params, blockIdx, assignIdx, layout,
           XF_POINT, CF_BYTE4);
  return true;
}

// @ 0x006cb210
bool FUN_006cb210(float* out, int count, int res, int* data, int vtx, const float* scalePair,
                  const char* params, int blockIdx, int assignIdx, int layout) {
  BakeCore(out, count, res, data, vtx, scalePair, params, blockIdx, assignIdx, layout,
           XF_POINT, CF_USHORT2);
  return true;
}
