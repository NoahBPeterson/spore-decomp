// Slice s006cb500: per-vertex bake helpers (see ../s006c5940/bake.h).
// All four are the same BakeCore instantiation with a different block transform
// and packed-colour format: point transform + u16x4 colours, and the offset
// transform with byte4 / u16x2 / u16x4 colours.
// (bake.h's transform declarations must return float*, as the originals do.)
#include "../s006c5940/bake.h"

// @ 0x006cb500
bool FUN_006cb500(float* out, int count, int res, int* data, int vtx, const float* scalePair,
                  const char* params, int blockIdx, int assignIdx, int layout) {
  BakeCore(out, count, res, data, vtx, scalePair, params, blockIdx, assignIdx, layout,
           XF_POINT, CF_USHORT4, 2, 0, 1);
  return true;
}

// @ 0x006cb830
bool FUN_006cb830(float* out, int count, int res, int* data, int vtx, const float* scalePair,
                  const char* params, int blockIdx, int assignIdx, int layout) {
  BakeCore(out, count, res, data, vtx, scalePair, params, blockIdx, assignIdx, layout,
           XF_OFFSET, CF_BYTE4, 2, 0, 1);
  return true;
}

// @ 0x006cbb80
bool FUN_006cbb80(float* out, int count, int res, int* data, int vtx, const float* scalePair,
                  const char* params, int blockIdx, int assignIdx, int layout) {
  BakeCore(out, count, res, data, vtx, scalePair, params, blockIdx, assignIdx, layout,
           XF_OFFSET, CF_USHORT2, 2, 0, 1);
  return true;
}

// @ 0x006cbea0
bool FUN_006cbea0(float* out, int count, int res, int* data, int vtx, const float* scalePair,
                  const char* params, int blockIdx, int assignIdx, int layout) {
  BakeCore(out, count, res, data, vtx, scalePair, params, blockIdx, assignIdx, layout,
           XF_OFFSET, CF_USHORT4, 2, 0, 1);
  return true;
}
