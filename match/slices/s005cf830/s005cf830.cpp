// slice s005cf830 -- SP::cSPEditorSpine static tuning + a large spine geometry builder.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

namespace SP {
class cSPEditorSpine {
 public:
  // @ 0x005CF830
  // PARTIAL: 0x5a5-byte property-driven static tuning load not reconstructed; see partial.txt.
  void LoadStaticTuning();
};
}  // namespace SP

// @ 0x005CF830
void SP::cSPEditorSpine::LoadStaticTuning() {}

// @ 0x005CFDE0
// PARTIAL: 0x4e6-byte spine segment/frame geometry builder not reconstructed; see partial.txt.
void FUN_005cfde0(int, int, float*, int, float*, float*, int, char) {}
