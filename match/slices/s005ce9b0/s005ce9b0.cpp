// slice s005ce9b0 -- spine handle geometry / vertex interpolation helpers (all unnamed in the dev PDB).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include <new>
#include <math.h>
#include "types.h"

namespace SP {

struct E20 {
  int a;
  int b;
  float c;
  float d;
  int e;
  E20() {}
  E20(const E20& o) : a(o.a), b(o.b), c(o.c), d(o.d), e(o.e) {}
};

struct E20Iter {
  E20* mpNode;
  E20Iter() {}
  E20Iter(E20* p) : mpNode(p) {}
  E20& operator*() const { return *mpNode; }
  bool operator!=(const E20Iter& o) const { return mpNode != o.mpNode; }
  E20Iter& operator++() {
    ++mpNode;
    return *this;
  }
};

}  // namespace SP
using namespace SP;

// @ 0x005CF7A0  (EASTL uninitialized_copy of a 0x14-byte, non-trivially-copyable element)
E20Iter CopyE20(E20Iter first, E20Iter last, E20Iter dest) {
  E20Iter currentDest(dest);
  for (; first != last; ++first, ++currentDest)
    if (&*currentDest) new ((void*)&*currentDest) E20(*first);
  return currentDest;
}

// @ 0x005CE9B0
// PARTIAL: 0x758-byte spine-handle ray/segment solver (points, distances, segment intersections)
// not reconstructed; see partial.txt.
float* FUN_005ce9b0(int, int, int, int, float*, int) { return 0; }

// @ 0x005CF110
// PARTIAL: 0x3d6-byte spine-handle geometry helper not reconstructed; see partial.txt.
float* FUN_005cf110(int, float*, int) { return 0; }

// @ 0x005CF4F0
// PARTIAL: 0x2ae-byte spine-handle vertex interpolation/extrusion helper not reconstructed; see partial.txt.
void FUN_005cf4f0(int, int, float, float, int) {}
