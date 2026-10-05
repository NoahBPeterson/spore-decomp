// slice s005d1f30 -- SP::cSPEditorSpine vertebra tree maintenance helpers.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

struct RBNode {
  RBNode* mpNodeLeft;    // +0
  RBNode* mpNodeRight;   // +4
  RBNode* mpNodeParent;  // +8
  int mnColor;           // +0xc
};

extern RBNode* RBTreeIncrement(RBNode* node);  // eastl::RBTreeIncrement, 0x00921580

namespace SP {

class cSpine76 {
 public:
  char pad00[0xa8];
  float mFieldA8;  // +0xa8
  float mFieldAC;  // +0xac
  char padB0[0xd4 - 0xb0];
  RBNode* mpFirst;  // +0xd4 (tree begin; sentinel is this+0xd0)

  void SetTuning(int unused);  // 005d2740
  void Refresh(int unused);    // 005d2790
  __declspec(noinline) void FUN_005d1ba0();     // 005d1ba0
  __declspec(noinline) void FUN_005d1e70();     // 005d1e70
  __declspec(noinline) void FUN_005d1f30(int);  // 005d1f30
  __declspec(noinline) void FUN_005d2480(int);  // 005d2480
};

// @ 0x005D2740
void cSpine76::SetTuning(int) {
  for (RBNode* n = mpFirst; n != (RBNode*)((char*)this + 0xd0); n = RBTreeIncrement(n)) {
    int limb = *(int*)((char*)n + 0x14);
    char* obj = *(char**)(limb + 0x58);
    *(float*)(obj + 0xc8) = mFieldA8;
    *(float*)(obj + 0xcc) = mFieldAC;
  }
  FUN_005d1ba0();
}

// @ 0x005D2790
void cSpine76::Refresh(int arg) {
  FUN_005d1e70();
  for (RBNode* n = mpFirst; n != (RBNode*)((char*)this + 0xd0); n = RBTreeIncrement(n))
    FUN_005d2480(*(int*)((char*)n + 0x10));
  FUN_005d1f30(arg);
}

// --- skeletons for the remaining slice functions (partial; see partial.txt) ---
// Bodies carry an observable side effect so cl keeps the out-of-line calls in their
// callers above (these helpers are reconstructed separately and are approximate).
volatile int g_spine76Sink = 0;

// @ 0x005D1F30
// PARTIAL: 0x546-byte tree rebuild not reconstructed.
__declspec(noinline) void cSpine76::FUN_005d1f30(int x) { g_spine76Sink = x; }
// @ 0x005D2480
// PARTIAL: 0x135-byte per-vertebra update not reconstructed.
__declspec(noinline) void cSpine76::FUN_005d2480(int x) { g_spine76Sink = x; }
// @ 0x005D1BA0
// PARTIAL: 0x197-byte helper not reconstructed.
__declspec(noinline) void cSpine76::FUN_005d1ba0() { g_spine76Sink = 2; }
// @ 0x005D1E70
// PARTIAL: 0xb7-byte tree teardown not reconstructed.
__declspec(noinline) void cSpine76::FUN_005d1e70() { g_spine76Sink = 3; }

}  // namespace SP

// @ 0x005D25C0
// PARTIAL: 0x174-byte per-vertebra update not reconstructed.
void FUN_005d25c0(int) {}
