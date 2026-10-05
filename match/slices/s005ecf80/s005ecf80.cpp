// Slice s005ecf80: SP::cSPPaletteItemRollover and neighbours.  Layout offsets taken from
// the binary (fields at +0x1c, +0x20, +0x78, +0xb0, +0xb4, +0xb8).  Large functions stubbed.
#include "types.h"

#define PV(n) virtual void _pv##n();

class cRenderTarget {
 public:
  void Render();
};

// 3-slot refcounted object (Release at vtable +0x08).
class cRefObj3 {
 public:
  PV(0) PV(1)
  virtual void Release();  // +0x08
};

void* __stdcall AddBoundingBox(void* box, int arg, int flag);
void ResetLayout(int value);

namespace SP {
class cSPPaletteItemRollover {
 public:
  char pad00[0x1c];
  int mField1c;   // +0x1c
  int mField20;   // +0x20
  char pad24[0x78 - 0x24];
  void* mField78;  // +0x78
  char pad7c[0xb0 - 0x7c];
  void* mFieldB0;  // +0xb0
  void* mFieldB4;  // +0xb4
  bool mFieldB8;   // +0xb8
  char padB9[3];
  float mFieldBc;  // +0xbc

  void AddBox(int arg);
  void GetAreaPair(int* out);
  void ResetRollover();
  void ShutdownRollover();
  void Destroy();
};

// @ 0x005ed340
void cSPPaletteItemRollover::GetAreaPair(int* out) {
  struct IntPair {
    int a;
    int b;
  };
  *(IntPair*)out = *(IntPair*)&mField1c;
}

// @ 0x005ed320
void cSPPaletteItemRollover::AddBox(int arg) {
  void* box = mField78;
  void* target = AddBoundingBox(box, arg, 1);
  ((cRenderTarget*)target)->Render();
}

// @ 0x005ed6c0
void cSPPaletteItemRollover::ResetRollover() {
  if (!mFieldB8)
    ResetLayout(0);
  if (mFieldB4) {
    mFieldB4 = 0;
    ((cRefObj3*)mFieldB4)->Release();
  }
}

// @ 0x005ecf80
void cSPPaletteItemRollover::ShutdownRollover() {}

// @ 0x005ed650
void cSPPaletteItemRollover::Destroy() {}

// @ 0x005ed360
void cSPPaletteItemRolloverCtor(cSPPaletteItemRollover* self, bool flag) {
  (void)self;
  (void)flag;
}

// @ 0x005ed420
void cSPPaletteItemRolloverInit(cSPPaletteItemRollover* self) { (void)self; }

// @ 0x005ed700
void cSPPaletteItemRolloverDtor(cSPPaletteItemRollover* self, unsigned int flags) {
  (void)self;
  (void)flags;
}
}  // namespace SP
