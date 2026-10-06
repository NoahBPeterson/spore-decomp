// Slice s0081fd70 -- SP::cPropertyUI property-modify overloads / Value helpers.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include "types.h"

// ===========================================================================
// 00820b50 / 00820b80  Value-holder (EA::Variant-like) constructors.
//   Stored order matters: the type-id store is scheduled before the flag store,
//   which makes cl put 0x12/0x13 in eax and 0xb in ecx.
// ===========================================================================
struct VariantCtor12 {
  void* m0;                 // +0x0
  char pad0[0xc];           // +0x4
  unsigned short mFlags;    // +0x10
  unsigned short mTypeId;   // +0x12
  VariantCtor12(int v);
  void Set(int, int, int, int, int);
};

VariantCtor12::VariantCtor12(int v) {
  mTypeId = 0x12;
  mFlags = 0xb;
  Set(0x12, 9, v, 0x10, 1);
}

struct VariantCtor13 {
  void* m0;                 // +0x0
  char pad0[0xc];           // +0x4
  unsigned short mFlags;    // +0x10
  unsigned short mTypeId;   // +0x12
  VariantCtor13(int v);
  void Set(int, int, int, int, int);
};

VariantCtor13::VariantCtor13(int v) {
  mTypeId = 0x13;
  mFlags = 0xb;
  Set(0x13, 9, v, 0x10, 1);
}

// 0x0081fd70  SP::cPropertyUI::ModifyVec4     -- not reconstructed (partial.txt)
// 0x00820210  SP::cPropertyUI::ModifyRGB      -- not reconstructed (partial.txt)
// 0x00820680  SP::cPropertyUI::ModifyRGBA     -- not reconstructed (partial.txt)
// 0x00820bb0  eastl::vector<T*>::DoInsertValue -- not reconstructed (partial.txt)
