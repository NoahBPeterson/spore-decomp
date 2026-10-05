// slice s007507e0 -- SP::EditorUtils::cRegisterSkinModelJob::Stage2
//
// Single 3441-byte /O2 function (MSVC 15.00.30729.01, EH prologue, no /GS cookie).
// It is dominated by inlined EASTL vector primitives, refcount release, a large
// x87/SSE skin-point solver and several intrusive-vector push_backs, so a
// byte-exact reconstruction is not yet available.  This is a compiling skeleton;
// see partial.txt.
//
// Flags that match the surrounding region: /O2 /MD /Gy /EHsc /TP /GS- /arch:SSE2

#include "types.h"

namespace SP {
namespace EditorUtils {

// Opaque stub with the members touched by Stage2 (offsets from the disassembly).
class cRegisterSkinModelJob {
 public:
  char pad_000[0x2d8];
  uint32_t mVecBegin;   // +0x2d8
  uint32_t mVecEnd;     // +0x2dc
  uint32_t mVecCap;     // +0x2e0

  void Stage2();
};

// @ 0x007507e0
void cRegisterSkinModelJob::Stage2() {
  // Skeleton: full body pending (see partial.txt).
}

}  // namespace EditorUtils
}  // namespace SP
