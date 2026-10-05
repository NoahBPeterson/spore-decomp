// slice s005ab7a0 — SP::cSPEditorManipulationCellPinning::DoOnMouseMove (4525 bytes).
// The giant per-frame pinning update (pick, symmetry, snap/replace, repin-to-torso).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "../s005aad00/s005aad00.h"

using namespace SP;

// @ 0x005ab7a0
// Skeleton: full body not translated (4525-byte float/symmetry path).
bool cSPEditorManipulationCellPinning::DoOnMouseMove(float x, float y, int) {
  mX = x;
  mY = y;
  return true;
}
