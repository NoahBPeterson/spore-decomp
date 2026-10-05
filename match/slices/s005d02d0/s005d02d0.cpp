// slice s005d02d0 -- SP::cSPEditorSpine leg queries (first/last) plus Update/ctor and a large builder.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

extern void EASTL_allocator_deallocate(void* p);  // 0x00f47380

namespace SP {

struct Leg {
  char pad[0xdc0];
  float mFieldDC0;  // +0xdc0
};

// A 3-pointer growable vector whose heap buffer carries an ownership word just before the
// first element (the original frees it only when that word is non-zero).
class LimbVector {
 public:
  Leg** mpBegin;
  Leg** mpEnd;
  Leg** mpCapacity;
  void* mReserved0;
  void* mReserved1;
  LimbVector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
  ~LimbVector() {
    if (mpBegin != 0 && ((int*)mpBegin)[-1] != 0)
      EASTL_allocator_deallocate(mpBegin);
  }
  unsigned int size() const { return (unsigned int)(mpEnd - mpBegin); }
  Leg* operator[](unsigned int i) const { return mpBegin[i]; }
};

namespace EditorUtils {
void GetAllLimbs(void* manager, LimbVector* out, int flag);  // 0x004a0020
void* GetFirstFootBlock(void* leg);                          // 0x004a9840
}

class cSPEditorSpine {
 public:
  char pad00[0xe8];
  void* mpLimbs;  // +0xe8

  Leg* GetFirstLeg();   // 005d0ce0
  Leg* GetLastLeg();    // 005d0d90
};

// @ 0x005D0CE0
Leg* cSPEditorSpine::GetFirstLeg() {
  LimbVector limbs;
  EditorUtils::GetAllLimbs(mpLimbs, &limbs, 1);
  Leg* best = 0;
  for (unsigned int i = 0; i < limbs.size(); ++i) {
    Leg* leg = limbs[i];
    if (EditorUtils::GetFirstFootBlock(leg) != 0) {
      if (best == 0 || leg->mFieldDC0 < best->mFieldDC0)
        best = leg;
    }
  }
  return best;
}

// @ 0x005D0D90
Leg* cSPEditorSpine::GetLastLeg() {
  LimbVector limbs;
  EditorUtils::GetAllLimbs(mpLimbs, &limbs, 1);
  Leg* best = 0;
  for (unsigned int i = 0; i < limbs.size(); ++i) {
    Leg* leg = limbs[i];
    if (EditorUtils::GetFirstFootBlock(leg) != 0) {
      if (best == 0 || leg->mFieldDC0 > best->mFieldDC0)
        best = leg;
    }
  }
  return best;
}

}  // namespace SP

// @ 0x005D02D0
// PARTIAL: 0x51e-byte spine builder/updater not reconstructed; see partial.txt.
void FUN_005d02d0(int, int, float, float) {}

// @ 0x005D07F0
// PARTIAL: 0x4f0-byte cSPEditorSpine::Update not reconstructed; see partial.txt.
void FUN_005d07f0(int) {}

// @ 0x005D0EA0
// PARTIAL: 0x38d-byte cSPEditorSpine constructor not reconstructed; see partial.txt.
void FUN_005d0ea0(int) {}
