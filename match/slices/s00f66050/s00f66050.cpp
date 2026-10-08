// Slice s00f66050: Terrain/DistGrid cell initialiser (function 00f660d0, a ctor-like thiscall that
// returns this). Writes scalar defaults, two Matrix3 copies (Assign, 0x0041cb40), allocates a
// count*6*0x18 array with operator new (0x00f473a0), frees the previous array (0x00f47380) and
// fills the table header fields. Raw offsets are used because the layout is only partly known.
// Flags: /O2 /MD /Gy /EHsc /TP
#include "types.h"

extern "C" void __cdecl operator_delete__(void* p);  // 0x00f47380
void* operator new(unsigned int size, const char* name, int flags, unsigned debugFlags, const char* file, int line);  // 0x00f473a0

struct Matrix3Ref {  // 0x0041cb40: thiscall, one pointer arg (copies 9 floats)
  void Assign(const float* src);  // 0x0041cb40
};

struct DistCell {
  char raw[0x104];
  DistCell* Construct();  // 0x00f660d0 (thiscall, returns this)
};

#define I32(o) (*(int32_t*)((char*)this + (o)))
#define U32(o) (*(uint32_t*)((char*)this + (o)))
#define U16(o) (*(uint16_t*)((char*)this + (o)))
#define F32(o) (*(float*)((char*)this + (o)))
#define MAT3(o) (*(Matrix3Ref*)((char*)this + (o)))

DistCell* DistCell::Construct() {
  I32(0x00) = 0;
  I32(0x04) = 0;
  U32(0x08) = 0x555;
  I32(0x0c) = 0;
  I32(0x24) = 0;
  I32(0x28) = 0;
  F32(0x2c) = 0.0f;
  F32(0x30) = 0.0f;
  I32(0x34) = 0;
  I32(0x38) = 0;
  I32(0x3c) = 0;
  U32(0x48) = 0x7f;
  U32(0x4c) = 0x3fffffff;
  U32(0x50) = 0x3fffffff;
  F32(0x54) = *(const float*)0x016c95f8;
  F32(0x58) = *(const float*)0x016c95fc;
  F32(0x5c) = *(const float*)0x016c9600;
  MAT3(0x60).Assign((const float*)0x016c9674);
  F32(0x84) = *(const float*)0x015b0cc8;
  F32(0x88) = *(const float*)0x015b0ccc;
  F32(0x8c) = *(const float*)0x015b0cd0;
  F32(0x90) = 0.0f;
  F32(0x94) = *(const float*)0x015b0cd4;
  F32(0x98) = *(const float*)0x015b0cd8;
  F32(0x9c) = *(const float*)0x015b0cdc;
  I32(0xa0) = 0;
  I32(0xa4) = -1;
  U16(0xaa) = 0;
  U16(0xa8) = 0;
  F32(0xac) = *(const float*)0x016c9638;
  F32(0xb0) = *(const float*)0x016c963c;
  F32(0xb4) = *(const float*)0x016c9640;
  F32(0xb8) = *(const float*)0x01485720;
  MAT3(0xbc).Assign((const float*)0x016c9614);

  uint32_t count = U32(0x08);
  uint32_t n = count * 6;
  uint32_t bytes = n * 0x18;
  void* fresh = operator new(bytes, "Terrain/DistGrid/cCell", 0, 0, 0, 0);
  void* old = (void*)U32(0x24);
  U32(0x24) = (uint32_t)fresh;
  U32(0x10) = 1;
  U32(0x14) = 5;
  U32(0x18) = 0x15;
  U32(0x1c) = 0x55;
  U32(0x20) = 0x155;
  I32(0xe0) = -1;
  I32(0xe4) = -1;
  I32(0xe8) = -1;
  I32(0xec) = -1;
  I32(0xf0) = -1;
  I32(0xf4) = -1;
  I32(0xf8) = -1;
  I32(0xfc) = -1;
  I32(0x100) = -1;
  operator_delete__(old);
  return this;
}
