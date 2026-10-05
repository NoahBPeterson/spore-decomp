// slice s005d12c0 -- SP::cSPEditorSpine block/vertebra bookkeeping and EASTL-style element copies.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include <new>
#include "types.h"

namespace SP {

// 0x14-byte sub-object with an out-of-line copy constructor / assignment (0x005d1240).
struct Sub24 {
  int mW[5];
  Sub24(const Sub24& other);
  Sub24& operator=(const Sub24& other);
};

// 0x24-byte element: 4 leading words + a 0x14-byte Sub24.
struct Elem24 {
  int mA;
  float mB;
  float mC;
  float mD;
  Sub24 mSub;
  Elem24(const Elem24& other) : mA(other.mA), mB(other.mB), mC(other.mC), mD(other.mD), mSub(other.mSub) {}
};

class cSpine75 {
 public:
  char pad00[0xc5];
  bool mFieldC5;  // +0xc5

  void SetFlag(bool enable, int unused);  // 005d1600
  void EnableBody();                      // 005d1530
  void DisableBody();                     // 005d14a0
};

// @ 0x005D1600
void cSpine75::SetFlag(bool enable, int) {
  if (enable) {
    if (!mFieldC5) {
      EnableBody();
      mFieldC5 = true;
    }
  } else {
    if (mFieldC5) {
      DisableBody();
      mFieldC5 = false;
    }
  }
}

// @ 0x005D13F0  (uninitialized_copy of the 0x24-byte element)
Elem24* CopyElem24(Elem24* first, Elem24* last, Elem24* dest) {
  if (first != last) {
    do {
      if (dest) {
        dest->mA = first->mA;
        dest->mB = first->mB;
        dest->mC = first->mC;
        dest->mD = first->mD;
        new ((void*)&dest->mSub) Sub24(first->mSub);
      }
      ++first;
      ++dest;
    } while (first != last);
  }
  return dest;
}

// @ 0x005D1450  (uninitialized relocation, backward)
Elem24* RelocateElem24Backward(Elem24* first, Elem24* last, Elem24* dest) {
  if (last == first) return dest;
  do {
    --last;
    --dest;
    dest->mA = last->mA;
    dest->mB = last->mB;
    dest->mC = last->mC;
    dest->mD = last->mD;
    dest->mSub = last->mSub;
  } while (last != first);
  return dest;
}

// --- skeletons for the remaining slice functions (partial; see partial.txt) ---

// @ 0x005D12C0
// PARTIAL: 0x126-byte cSPEditorSpine::RecordBlockCoordinates not reconstructed.
void RecordBlockCoordinatesSkeleton(void*, void*) {}

// @ 0x005D14A0
// PARTIAL: 0x8e-byte limb-vector teardown not reconstructed.
void FUN_005d14a0(int) {}

// @ 0x005D1530
// PARTIAL: 0xcf-byte limb reconstruction not reconstructed.
void FUN_005d1530(int) {}

// @ 0x005D1640
// PARTIAL: 0x13b-byte helper not reconstructed.
void FUN_005d1640(int) {}

// @ 0x005D1780
// PARTIAL: 0x25d-byte helper not reconstructed.
void FUN_005d1780(int) {}

// @ 0x005D19E0
// PARTIAL: 0x1b8-byte cSPEditorSpine::RepinArea not reconstructed.
void FUN_005d19e0(int) {}

// @ 0x005D1BA0
// PARTIAL: 0x197-byte helper not reconstructed.
void FUN_005d1ba0(int) {}

// @ 0x005D1D40
// PARTIAL: 0x124-byte cSPEditorSpine::UpdateVertebraeOrderAndCollisionFilters not reconstructed.
void FUN_005d1d40(int) {}

// @ 0x005D1E70
// PARTIAL: 0xb7-byte rbtree teardown helper not reconstructed.
void FUN_005d1e70(int) {}

}  // namespace SP
