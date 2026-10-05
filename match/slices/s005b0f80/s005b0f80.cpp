// slice s005b0f80 — SP::cSPEditorManipulationObject base (ctor, AsInterface, OnMouseDown,
// OnMouseMove) and small helper types used by the editor manipulation objects.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "math.h"
#include "types.h"

// @ 0x005b0f80
struct MObj {
  virtual ~MObj() {}
  bool mChangedObject;         // +0x4
  bool mUseDeadZone;           // +0x5
  bool mMovedOutsideDeadZone;  // +0x6
  char pad_7;
  float mDeadZoneSize;   // +0x8
  float mInitialX;       // +0xc
  float mInitialY;       // +0x10
  MObj();
  void* AsInterface(int typeID);
};
MObj::MObj()
    : mChangedObject(false), mUseDeadZone(true), mMovedOutsideDeadZone(false),
      mDeadZoneSize(2.0f), mInitialX(0.0f), mInitialY(0.0f) {}

// @ 0x005b0fb0
void* MObj::AsInterface(int typeID) {
  void* result = this;
  if (typeID != 0xee3f516e)
    result = 0;
  return result;
}

// @ 0x005b1080
struct S80 {
  float m0, m1, m2, m3, m4, m5;   // +0x0..+0x14
  bool  m18;                      // +0x18
  void Set(float a, float b, float c, float d, float e, float f);
  S80(float a, float b, float c, float d, float e, float f);
};
S80::S80(float a, float b, float c, float d, float e, float f)
    : m0(a), m1(b), m2(c), m3(d), m4(e), m5(f), m18(false) {}
void S80::Set(float a, float b, float c, float d, float e, float f) {
  S80* self = this;
  self->m0 = a; self->m1 = b; self->m2 = c; self->m3 = d; self->m4 = e; self->m5 = f;
  self->m18 = false;
}

// @ 0x005b10d0
struct Sd0 {
  float mX, mY, mZ;        // +0x0
  char pad_c[0x18 - 0xc];
  bool  mHasBest;          // +0x18
  char pad_19[3];
  float mBestX, mBestY, mBestZ;   // +0x1c
  float mBestDist;                // +0x28
  void Consider(float x, float y, float z);
};
void Sd0::Consider(float x, float y, float z) {
  float dx = mX - x;
  float dy = mY - y;
  float dz = mZ - z;
  float d = sqrtf(dx * dx + dy * dy + dz * dz);
  if (!mHasBest || d < mBestDist) {
    mBestX = x;
    mBestY = y;
    mHasBest = true;
    mBestDist = d;
    mBestZ = z;
  }
}

// ---- not translated ----
// @ 0x005b0fd0
void Stub_005b0fd0() {}
// @ 0x005b1010
void Stub_005b1010() {}
// @ 0x005b1130
void Stub_005b1130() {}
// @ 0x005b11e0
void Stub_005b11e0() {}
// @ 0x005b1310
void Stub_005b1310() {}
// @ 0x005b15e0
void Stub_005b15e0() {}
// @ 0x005b1870
void Stub_005b1870() {}
// @ 0x005b1c80
void Stub_005b1c80() {}
// @ 0x005b1cd0
void Stub_005b1cd0() {}
