// Slice s00c649b0 — Simulator::cArrowMorphHandle / cSimpleRotationRing/Ball helpers.
// Flags /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"
#include <math.h>

void* __cdecl operator_new(unsigned, const char*, int, int, const char*, int);
void  __cdecl operator_delete__(void*);
void* __cdecl SP_ModelManager();                        // 0x67dd80
bool  __cdecl FUN_00c8a550(void*, void*);               // 0xc8a550
void  __fastcall FUN_00c8a420(void* self);              // 0xc8a420 (thiscall)
void  __fastcall FUN_00b184c0(void* self);              // 0xb184c0 (thiscall)
void  __cdecl FUN_00c640e0();                           // 0xc640e0
void  __cdecl FUN_00c64170();                           // 0xc64170
void  __cdecl FUN_0059aed0(void*, void*, void*);        // 0x59aed0
void  __cdecl EA_LimitStopwatch_SetTimeLimit(void*, int, int); // 0x93a480

struct Vec3 { float x, y, z; };
struct APos { char _pad[0x150]; Vec3 pos; };

struct Base {
  void __thiscall Ctor();     // cMorphHandle ctor 0xc63be0
  void __thiscall Dtor();
};

struct A {
  bool __thiscall Contains(int key);
  void __thiscall EnableFlag(char b);
  void __thiscall SetA(float v);
  void __thiscall SetB(float v);
  void __thiscall SetC(float v);
  void __thiscall SetPos(float* p);
  void __thiscall FUN_00c64db0();
};

// @ 0x00c64a70
bool __thiscall A::Contains(int key) {
  volatile int* p = *(int**)((char*)this + 4);
  for (int i = 0; i < ((int)*(int**)((char*)this + 8) - (int)*(int**)((char*)this + 4)) >> 2; ++i, ++p) {
    if (key == *p) return true;
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
      if (c != 0) ((unsigned*)(base + 0x44))[idx >> 5] |= 1u << (idx & 0x1f);
      else        ((unsigned*)(base + 0x44))[idx >> 5] &= ~(1u << (idx & 0x1f));
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
  APos* s = (APos*)this;
  if (s->pos.x != p[0] || s->pos.y != p[1] || s->pos.z != p[2]) {
    s->pos = *(Vec3*)p;
    FUN_00c64db0();
  }
}

// @ 0x00c64ad0  quaternion normalise
void __cdecl FUN_00c64ad0(float* out, float* in) {
  float inv = 1.0f / sqrtf(in[0] * in[0] + in[1] * in[1] + in[2] * in[2] + in[3] * in[3] + 1e-08f);
  float r[4];
  r[0] = in[0] * inv;
  r[1] = in[1] * inv;
  r[2] = in[2] * inv;
  r[3] = in[3] * inv;
  out[0] = r[0];
  out[1] = r[1];
  out[2] = r[2];
  out[3] = r[3];
}

// @ 0x00c653e0 dtor
void __fastcall FUN_00c653e0(void* self) {
  void* sub = (char*)self + 0x34;
  *(void**)self = (void*)0x1471288;
  *(void**)((char*)self + 4) = (void*)0x1471274;
  *(void**)sub = (void*)0x14711b0;
  *(void* volatile*)((char*)self + 0x118) = (void*)0x14711a8;
  *(void* volatile*)((char*)self + 0x118) = (void*)0x14711a4;
  void* p = *(void**)((char*)self + 0x148);
  if (p && *(int*)((char*)p - 4) != 0) operator_delete__(p);
  *(void**)self = (void*)0x1470eb8;
  *(void**)((char*)self + 4) = (void*)0x147112c;
  *(void**)sub = (void*)0x1470df0;
  FUN_00c8a420(sub);
  FUN_00b184c0(self);
}
// @ 0x00c65540 dtor
void __fastcall FUN_00c65540(void* self) {
  void* sub = (char*)self + 0x34;
  *(void**)self = (void*)0x14713c8;
  *(void**)((char*)self + 4) = (void*)0x14713b4;
  *(void**)sub = (void*)0x14712f0;
  *(void* volatile*)((char*)self + 0x118) = (void*)0x14712ec;
  *(void* volatile*)((char*)self + 0x118) = (void*)0x14711a4;
  void* p = *(void**)((char*)self + 0x148);
  if (p && *(int*)((char*)p - 4) != 0) operator_delete__(p);
  *(void**)self = (void*)0x1470eb8;
  *(void**)((char*)self + 4) = (void*)0x147112c;
  *(void**)sub = (void*)0x1470df0;
  FUN_00c8a420(sub);
  FUN_00b184c0(self);
}

// ---- partial / stubbed ------------------------------------------------
void __fastcall FUN_00c649b0(void* self, int _e, void* b) { (void)self;(void)b; }
void* __fastcall cArrowMorphHandle_ctor(void* self) { return self; }
__declspec(noinline) void __thiscall A::FUN_00c64db0() { }
void __fastcall FUN_00c64f00(void* self) { (void)self; }
void* __fastcall FUN_00c650d0(void* self, int _e, void* a, void* b) { (void)self;(void)a;(void)b; return a; }
void __fastcall FUN_00c65610(void* self) { (void)self; }
unsigned char __fastcall FUN_00c656c0(void* self, int _e, void* a) { (void)self;(void)a; return 0; }
void __fastcall FUN_00c65780(void* self, int _e, void* a) { (void)self;(void)a; }
