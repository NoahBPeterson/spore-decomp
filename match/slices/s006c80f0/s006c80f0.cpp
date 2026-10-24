// Slice s006c80f0: per-vertex bake helpers (see ../s006c5940/bake.h).
// BakeCore is __forceinline so each helper is self-contained (the original inlined it);
// it copies the colour block and the assign block into BakeRange locals, which is what
// the original does before calling Handle_Assign, and keeps the colour / attribute
// math in scalar SSE like the original (shared header, per-transform component order).
#include "../s006c5940/bake.h"

// @ 0x006c80f0
bool FUN_006c80f0(float* out, int count, int res, int* data, int vtx, const float* scalePair,
                  const char* params, int blockIdx, int assignIdx, int layout) {
  BakeCore(out, count, res, data, vtx, scalePair, params, blockIdx, assignIdx, layout,
           XF_POINT, CF_USHORT2);
  return true;
}

// @ 0x006c83e0
bool FUN_006c83e0(float* out, int count, int res, int* data, int vtx, const float* scalePair,
                  const char* params, int blockIdx, int assignIdx, int layout) {
  BakeCore(out, count, res, data, vtx, scalePair, params, blockIdx, assignIdx, layout,
           XF_POINT, CF_USHORT4);
  return true;
}

// @ 0x006c8710
bool FUN_006c8710(float* out, int count, int res, int* data, int vtx, const float* scalePair,
                  const char* params, int blockIdx, int assignIdx, int layout) {
  BakeCore(out, count, res, data, vtx, scalePair, params, blockIdx, assignIdx, layout,
           XF_OFFSET, CF_BYTE4);
  return true;
}

// @ 0x006c8a60
bool FUN_006c8a60(float* out, int count, int res, int* data, int vtx, const float* scalePair,
                  const char* params, int blockIdx, int assignIdx, int layout) {
  BakeCore(out, count, res, data, vtx, scalePair, params, blockIdx, assignIdx, layout,
           XF_OFFSET, CF_USHORT2);
  return true;
}
