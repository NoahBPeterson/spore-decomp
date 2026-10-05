// slice s005ac950 — tail of SP::cSPEditorManipulationCellPinning plus editor manipulation
// helper methods (block pinning/interpenetration state setters).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "../s005aad00/s005aad00.h"

using namespace SP;

// @ 0x005ac950
void* cSPEditorManipulationCellPinning::AsInterface(uint32_t typeID) {
  void* result = this;
  if (typeID != 0xee3f516e && typeID != 0xefdf6da5)
    result = 0;
  return result;
}

// ---- state helpers (offsets taken from the retail code; class identity unconfirmed) ----
struct RefA {  // AddRef at slot 1 (+4), Release at slot 2 (+8)
  virtual ~RefA();
  virtual int AddRef();
  virtual int Release();
};
struct RefB {  // Release at vtable slot 1 (+4)
  virtual int AddRef();
  virtual int Release();
};

// @ 0x005acc30
struct SPin30 {
  char pad_0[4];
  bool mChanged;   // +0x4
  char pad_5[0x1c - 0x5];
  void* m1c;       // +0x1c
  void* m20;       // +0x20
  char pad_24[0x40 - 0x24];
  float mX;        // +0x40
  float mY;        // +0x44
  int m48;         // +0x48
  bool DoOnMouseMove(float x, float y, int z);
};
bool SPin30::DoOnMouseMove(float x, float y, int z) {
  if (m1c == 0 || m20 == 0)
    return false;
  if ((mX != x || mY != y) && !mChanged)
    mChanged = true;
  m48 = z;
  mX = x;
  mY = y;
  return true;
}

// @ 0x005acc90
struct SPin90 {
  char pad_0[0x1c];
  RefA* m1c;   // +0x1c
  RefB* m20;   // +0x20
  int m24;     // +0x24
  void Shutdown();
};
void SPin90::Shutdown() {
  if (m20) {
    RefB* p = m20;
    m20 = 0;
    p->Release();
  }
  if (m1c) {
    RefA* p = m1c;
    m1c = 0;
    p->Release();
  }
  m24 = 0;
}

// @ 0x005ad930
struct SPin930 {
  char pad_0[0x1c];
  RefA* m1c;         // +0x1c
  void* m20;         // +0x20
  char pad_24[0x38 - 0x24];
  uint32_t m38;      // +0x38
  uint32_t m3c;      // +0x3c
  uint32_t m40;      // +0x40
  bool m44;          // +0x44
  void SetBlock(RefA** src, uint32_t a, uint32_t b, uint32_t c, bool d);
};
void SPin930::SetBlock(RefA** src, uint32_t a, uint32_t b, uint32_t c, bool d) {
  RefA* blk = *src;
  RefA* old = m1c;
  if (blk != old) {
    if (blk)
      blk->AddRef();
    m1c = blk;
    if (old)
      old->Release();
  }
  m38 = a;
  m3c = b;
  m40 = c;
  m44 = d;
  if (m1c)
    m20 = *(void**)((char*)m1c + 0x33c);
}

// ---- not translated ----
// @ 0x005ac980
void Stub005ac980() {}
// @ 0x005ac9f0
void Stub005ac9f0() {}
// @ 0x005aca70
void Stub005aca70() {}
// @ 0x005accc0
void Stub005accc0() {}
// @ 0x005acdb0
void Stub005acdb0() {}
// @ 0x005acec0
void Stub005acec0() {}
// @ 0x005ad430
void Stub005ad430() {}
// @ 0x005ad5d0
void Stub005ad5d0() {}
