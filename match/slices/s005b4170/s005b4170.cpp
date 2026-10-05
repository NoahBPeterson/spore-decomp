// slice s005b4170 — SP editor manipulation objects: planar interpenetration ctor/setter and
// mouse-move state helper.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "../s005aad00/s005aad00.h"

using namespace SP;
using namespace EA;

namespace {
struct RefA {  // AddRef slot 1, Release slot 2
  virtual ~RefA();
  virtual int AddRef();
  virtual int Release();
};
struct RefB {  // Release slot 1
  virtual int AddRef();
  virtual int Release();
};
struct BaseManip : EA::COM::IUnknown32 {
  virtual ~BaseManip();
  bool mChangedObject;         // +0x4
  bool mUseDeadZone;           // +0x5
  bool mMovedOutsideDeadZone;  // +0x6
  char pad_7;
  float mDeadZoneSize;   // +0x8
  float mInitialX;       // +0xc
  float mInitialY;       // +0x10
  BaseManip();
};
}  // namespace

// @ 0x005b4b40
class PlanarInter : public BaseManip, public EA::RefCountVTemplate<int> {
 public:
  RefA* m1c;   // +0x1c
  void* m20;   // +0x20
  void* m24;   // +0x24
  void* m28;   // +0x28
  void* m2c;   // +0x2c
  char pad_30[0x38 - 0x30];
  cSPVector3 mV;  // +0x38
  bool m44;       // +0x44
  bool m45;       // +0x45
  PlanarInter();
  void SetBlock(RefA** src, uint32_t a, uint32_t b, uint32_t c, bool d, bool e);
};
PlanarInter::PlanarInter()
    : m1c(0), m20(0), m24(0), m28(0), m2c(0), mV(), m44(false), m45(false) {
  mChangedObject = false;
}

// @ 0x005b4ad0
void PlanarInter::SetBlock(RefA** src, uint32_t a, uint32_t b, uint32_t c, bool d, bool e) {
  RefA* blk = *src;
  RefA* old = m1c;
  if (blk != old) {
    if (blk)
      blk->AddRef();
    m1c = blk;
    if (old)
      old->Release();
  }
  *(uint32_t*)&mV.x = a;
  *(uint32_t*)&mV.y = b;
  *(uint32_t*)&mV.z = c;
  m44 = e;
  m45 = d;
  if (m1c)
    m20 = *(void**)((char*)m1c + 0x33c);
}

// @ 0x005b50a0
struct SPin50 {
  char pad_0[4];
  bool mChanged;   // +0x4
  char pad_5[0x20 - 0x5];
  void* m20;       // +0x20
  char pad_24[0x140 - 0x24];
  float mX;        // +0x140
  float mY;        // +0x144
  char pad_148[0x154 - 0x148];
  int m154;        // +0x154
  bool DoOnMouseMove(float x, float y, int z);
};
bool SPin50::DoOnMouseMove(float x, float y, int z) {
  if (m20) {
    if ((mX != x || mY != y) && !mChanged)
      mChanged = true;
    m154 = z;
    mX = x;
    mY = y;
    return true;
  }
  return false;
}

// ---- not translated ----
// @ 0x005b4170
void Stub_005b4170() {}
// @ 0x005b4340
void Stub_005b4340() {}
// @ 0x005b4bf0
void Stub_005b4bf0() {}
// @ 0x005b4f20
void Stub_005b4f20() {}
// @ 0x005b4fa0
void Stub_005b4fa0() {}
