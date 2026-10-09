// slice s005ccc90 -- shopping-token translator / editor-spine helpers. Flags:
// /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include <new>
#include "types.h"

extern "C" void EASTL_allocator_deallocate(void* p); // 0x00f47380
void* operator new(unsigned int n, const char* name, int flags, unsigned int debugFlags,
                   const char* file, int line);

#define PV(n) virtual void pv##n();

// ---------------------------------------------------------------------------------------------
class cRefCounted {
 public:
  int mPad0;
  int mRef;  // +4
  void IncRef(int unused);
  void DecRef(int unused);

  char pad0[4];
};

// @ 0x005CDBB0
void cRefCounted::IncRef(int unused) {
  (void)unused;
  mRef++;
}

// @ 0x005CDBC0
void cRefCounted::DecRef(int unused) {
  (void)unused;
  mRef--;
}

// ---------------------------------------------------------------------------------------------
class cTimeObj {
 public:
  PV(0) PV(1)
  virtual int GetType();  // +0x8
  int mPad4, mPad8;
  float mFloat0c;         // +0xc
  cTimeObj* mChild;       // +0x10
};

// @ 0x005CD910
float TimeObjValue(cTimeObj* obj) {
  if (obj->GetType() != 0xe)
    return 0.0f;
  cTimeObj* child = obj->mChild;
  if (child->GetType() != 8)
    return 0.0f;
  return child->mFloat0c;
}

// ---------------------------------------------------------------------------------------------
inline float FMax(float a, float b) { return a > b ? a : b; }
inline float FMin(float a, float b) { return a < b ? a : b; }

class cInterp {
 public:
  char pad0[0x88];
  float mFloat88;  // +0x88
  float mFloat8c;  // +0x8c
  float mFloat90;  // +0x90
  float mFloat94;  // +0x94
  float mFloat98;  // +0x98
  void Interp(float a, float b, float* out1, float* out2);
};

// @ 0x005CD870
void cInterp::Interp(float a, float b, float* out1, float* out2) {
  float t = ((a + b) * 0.5f) / mFloat98;
  t = FMax(t, 0.0f);
  t = FMin(t, 1.0f);
  t = (mFloat94 - mFloat90) * (1.0f - t) + mFloat90;
  *out1 = mFloat88 * t;
  *out2 = mFloat8c * t;
}

// ---------------------------------------------------------------------------------------------
class cSpine {
 public:
  char pad0[0x34];
  int mInt34;       // +0x34
  char pad38[0x74 - 0x38];
  int mInt74;       // +0x74
  char pad78[0x11c - 0x78];
  float mFloat11c;  // +0x11c
  unsigned int GetKey(int index);        // 0x005efd70
  unsigned int MakeVertKey(float a, int b);  // 0x005cdb30
};
float GetExactSkinRadiusFromVertebra(float a);  // 0x004a5b70

// @ 0x005CDB30
unsigned int cSpine::MakeVertKey(float a, int b) {
  unsigned int key = GetKey(b);
  float radius = GetExactSkinRadiusFromVertebra(a);
  int scaled = (int)((radius * -0.5f) / ((mFloat11c * 2.0f) * 0.25f + mFloat11c));
  return (mInt74 - scaled) * 0x400 | ((mInt34 << 0xb) | key) << 5 | 2;
}

// ---------------------------------------------------------------------------------------------
// Large functions: signature-only stubs (partial).

// @ 0x005CCC90
void TranslateTokenStub(void* a, void* b, void* c) {
  (void)a;
  (void)b;
  (void)c;
}

// @ 0x005CD190
void GetDayOfWeekStringStub(int day, void* out) {
  (void)day;
  (void)out;
}

// @ 0x005CD340
void GetTimeStringStub(void* a, void* b) {
  (void)a;
  (void)b;
}

// @ 0x005CD670
void SpineBigStub(void* a, void* b, void* c) {
  (void)a;
  (void)b;
  (void)c;
}

// @ 0x005CD9A0
void CreateVertebraShapeStub(float r) {
  (void)r;
}

// @ 0x005CDAE0
void ReleaseVertStub(void* a) {
  (void)a;
}

// @ 0x005CDBF0
void CreateWallBoxStub(void* a, void* b) {
  (void)a;
  (void)b;
}
