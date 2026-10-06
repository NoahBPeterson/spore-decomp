// Slice s00c649b0 — Simulator::cArrowMorphHandle / cSimpleRotationRing/Ball helpers.
// Flags /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"
#include <math.h>

void* __cdecl operator_new(unsigned, const char*, int, int, const char*, int);
void  __cdecl operator_delete__(void*);
void* __cdecl SP_ModelManager();                        // 0x67dd80
bool  __cdecl FUN_00c8a550(void*, void*);               // 0xc8a550
void  __cdecl FUN_00c8a420();                           // 0xc8a420
void  __cdecl FUN_00b184c0();                           // 0xb184c0
void  __cdecl FUN_00c640e0();                           // 0xc640e0
void  __cdecl FUN_00c64170();                           // 0xc64170
void  __cdecl FUN_0059aed0(void*, void*, void*);        // 0x59aed0
void  __cdecl EA_LimitStopwatch_SetTimeLimit(void*, int, int); // 0x93a480

struct Base {
  void __thiscall Ctor();     // cMorphHandle ctor 0xc63be0
  void __thiscall Dtor();
};

struct A {
  // @ 0x00c64a70
  bool __thiscall Contains(int key);
  // @ 0x00c64b50
  void __thiscall EnableFlag(char b);
  // @ 0x00c654b0
  void __thiscall SetA(float v);
  // @ 0x00c654e0
  void __thiscall SetB(float v);
  // @ 0x00c65510
  void __thiscall SetC(float v);
  // @ 0x00c658e0
  void __thiscall SetPos(float* p);
  void __thiscall FUN_00c64db0();
};

// @ 0x00c64a70
bool __thiscall A::Contains(int key) {
  int* p = *(int**)((char*)this + 4);
  int n = (int)((*(int**)((char*)this + 8) - p) >> 2);
  for (int i = 0; i < n; ++i) {
    if (p[i] == key) return true;
  }
  return false;
}

// @ 0x00c64b50
void __thiscall A::EnableFlag(char b) {
  *(char*)((char*)this + 0x115) = b;
  if (*(int*)((char*)this + 0xd0) != 0) {
    void* mm = SP_ModelManager();
    int base = *(int*)((char*)this + 0xd0);
    char c = *(char*)((char*)this + 0x115);
    unsigned idx = (*(unsigned(__thiscall*)(void*, int, int))((*(void***)mm)[0x28 / 4]))(mm, 0x7aa969b, 0);
    if (idx < 0x40) {
      unsigned* w = (unsigned*)(base + 0x44 + ((idx >> 5) << 2));
      if (c != 0) *w |= 1u << (idx & 0x1f);
      else        *w &= ~(1u << (idx & 0x1f));
    }
  }
}

// @ 0x00c654b0
void __thiscall A::SetA(float v) {
  if (*(float*)((char*)this + 0x1bc) != v) {
    *(float*)((char*)this + 0x1bc) = v;
    FUN_00c640e0();
  }
}
// @ 0x00c654e0
void __thiscall A::SetB(float v) {
  if (*(float*)((char*)this + 0x1c0) != v) {
    *(float*)((char*)this + 0x1c0) = v;
    FUN_00c64170();
  }
}
// @ 0x00c65510
void __thiscall A::SetC(float v) {
  if (*(float*)((char*)this + 0x1c4) != v) {
    *(float*)((char*)this + 0x1c4) = v;
    FUN_00c64170();
  }
}
// @ 0x00c658e0
void __thiscall A::SetPos(float* p) {
  if (*(float*)((char*)this + 0x150) != p[0] ||
      *(float*)((char*)this + 0x154) != p[1] ||
      *(float*)((char*)this + 0x158) != p[2]) {
    *(float*)((char*)this + 0x150) = p[0];
    *(float*)((char*)this + 0x154) = p[1];
    *(float*)((char*)this + 0x158) = p[2];
    FUN_00c64db0();
  }
}

// @ 0x00c64ad0  quaternion normalise
void __cdecl FUN_00c64ad0(float* out, float* in) {
  float x = in[0], y = in[1], z = in[2], w = in[3];
  float inv = 1.0f / sqrtf(((x*x + y*y) + z*z) + w*w + 1e-08f);
  out[0] = x * inv;
  out[1] = y * inv;
  out[2] = inv * z;
  out[3] = inv * w;
}

// @ 0x00c653e0 / 0x00c65540  dtors
void __fastcall FUN_00c653e0(void* self) {
  *(void**)self = (void*)0x1471288;
  *(void**)((char*)self + 4) = (void*)0x1471274;
  *(void**)((char*)self + 0x34) = (void*)0x14711b0;
  *(void**)((char*)self + 0x118) = (void*)0x14711a8;
  *(void**)((char*)self + 0x118) = (void*)0x14711a4;
  void* p = *(void**)((char*)self + 0x148);
  if (p && *(int*)((char*)p - 4) != 0) operator_delete__(p);
  *(void**)self = (void*)0x1470eb8;
  *(void**)((char*)self + 4) = (void*)0x147112c;
  *(void**)((char*)self + 0x34) = (void*)0x1470df0;
  FUN_00c8a420();
  FUN_00b184c0();
}
void __fastcall FUN_00c65540(void* self) {
  *(void**)self = (void*)0x14713c8;
  *(void**)((char*)self + 4) = (void*)0x14713b4;
  *(void**)((char*)self + 0x34) = (void*)0x14712f0;
  *(void**)((char*)self + 0x118) = (void*)0x14712ec;
  *(void**)((char*)self + 0x118) = (void*)0x14711a4;
  void* p = *(void**)((char*)self + 0x148);
  if (p && *(int*)((char*)p - 4) != 0) operator_delete__(p);
  *(void**)self = (void*)0x1470eb8;
  *(void**)((char*)self + 4) = (void*)0x147112c;
  *(void**)((char*)self + 0x34) = (void*)0x1470df0;
  FUN_00c8a420();
  FUN_00b184c0();
}

// ---- partial / stubbed ------------------------------------------------
void __fastcall FUN_00c649b0(void* self, int _e, void* b) { (void)self;(void)b; }
void* __fastcall cArrowMorphHandle_ctor(void* self) { return self; }
void __thiscall A::FUN_00c64db0() { }
void __fastcall FUN_00c64f00(void* self) { (void)self; }
void* __fastcall FUN_00c650d0(void* self, int _e, void* a, void* b) { (void)self;(void)a;(void)b; return a; }
void __fastcall FUN_00c65610(void* self) { (void)self; }
unsigned char __fastcall FUN_00c656c0(void* self, int _e, void* a) { (void)self;(void)a; return 0; }
void __fastcall FUN_00c65780(void* self, int _e, void* a) { (void)self;(void)a; }
