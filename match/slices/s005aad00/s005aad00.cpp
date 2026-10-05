// slice s005aad00 — SP::cSPEditorManipulationCellPinning (Editor block pinning):
// complete object destructor, GetPileList (virtual slot 11), OnMouseUp, RecalculateMouseOffset
// and DoOnMouseDown.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "s005aad00.h"

using namespace SP;

// @ 0x005aad00
cSPEditorManipulationCellPinning::~cSPEditorManipulationCellPinning() {}

// @ 0x005ab1b0
eastl::sp_vector<EA::AutoRefCount<cSPEditorBlock> > cSPEditorManipulationCellPinning::GetPileList() {
  return mPileList;
}

// @ 0x005aada0
// OnMouseUp: notified when the pinning drag ends (skeleton; full SSE body not translated).
bool cSPEditorManipulationCellPinning::OnMouseUp(int, float, float, int) {
  return true;
}

// @ 0x005ab220
// RecalculateMouseOffset: reprojects the mouse ray onto the block's pinning plane (skeleton).
void cSPEditorManipulationCellPinning::RecalculateMouseOffset(float, float) {
  CalculateInflatedMesh();
}

// @ 0x005ab5c0
bool cSPEditorManipulationCellPinning::DoOnMouseDown(int, float, float, int) {
  return true;
}
