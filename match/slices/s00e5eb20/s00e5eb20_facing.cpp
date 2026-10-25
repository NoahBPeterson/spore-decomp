// Slice s00e5eb20, third TU: SP::sCellGetFacing. Retail keeps it in its own object file -- the callers in
// SPCellGame.obj call it instead of inlining it and must save a callee-saved register for the cell pointer.
// Retail module: /O2 /MD /Gy /TP /arch:SSE /fp:fast, no /EHsc.
#include "types.h"
#include <math.h>
#pragma intrinsic(sqrt)

struct cCell {
  char  mReserved00[0x5c];
  float mOrient[9];               // +0x05c
};

extern const float gKAxisX;         // 0x015a7c34  0.0f
extern const float gKAxisY;         // 0x015a7c38  1.0f
extern const float gKAxisZ;         // 0x015a7c3c  0.0f
extern const float gKEpsilon;       // 0x013ec4b8  1e-8f

namespace SP {

// @ 0x00e5eb20
void __cdecl sCellGetFacing(float* out, const cCell* cell) {
  const float ax = -gKAxisX;
  const float ay = -gKAxisY;
  const float az = -gKAxisZ;
  const float dx = (cell->mOrient[3] * ay + cell->mOrient[6] * az) + ax * cell->mOrient[0];
  const float dy = (cell->mOrient[1] * ax + cell->mOrient[4] * ay) + cell->mOrient[7] * az;
  const float s = (float)(1.0 / sqrt((double)(dx * dx + dy * dy + gKEpsilon)));
  out[0] = s * dx;
  out[1] = s * dy;
  out[2] = s * 0.0f;
}

}  // namespace SP
