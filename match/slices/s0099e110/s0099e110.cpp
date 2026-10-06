// Slice s0099e110: creature-animation static-data loader and small helpers.
// Reconstructed from the annotated disassembly; real names from the 2008 PDB where known.
#include "types.h"

// ---------------------------------------------------------------------------
// stubs
// ---------------------------------------------------------------------------
struct S99d060 { void f(); };                 // release a reference (0x99d060)
struct S99ed90 { int f(void*, char*, int); }; // ReadAnimationStaticDataFromStreamWrapper (external)
extern int FUN_0099ed90();                    // skeleton body for the standalone VA
extern void FUN_f47380(void*);                 // operator delete(void*) cdecl
extern int FUN_00a088e0(int);
extern void FUN_11e073e(void*, int, int);
extern void __stdcall FUN_401930(void*, int, int, void*);
extern void FUN_0099cf50();
extern int g_15504dc;

extern "C" __declspec(dllimport) void* __cdecl fopen(const char*, const char*);
extern "C" __declspec(dllimport) int   __cdecl fclose(void*);

// ---------------------------------------------------------------------------
// @ 0x0099e110  creature animation static-data apply (huge; skeleton)
// ---------------------------------------------------------------------------
void FUN_0099e110() {}

// ---------------------------------------------------------------------------
// @ 0x0099ecb0  AutoRefCount<SP::cSPCreatureBase>::operator=
// ---------------------------------------------------------------------------
struct S99ecb0 {
  S99ecb0* f(int p);
};
S99ecb0* S99ecb0::f(int p) {
  int old = *(int*)this;
  if (p != old) {
    if (p) *(int*)(p + 0x114) += 1;
    *(int*)this = p;
    if (old) ((S99d060*)(size_t)old)->f();
  }
  return this;
}

// ---------------------------------------------------------------------------
// @ 0x0099ece0  two struct-array initialisers + vector ctor + operator new
// ---------------------------------------------------------------------------
struct E16 { float a; float b; unsigned char c; unsigned char d; unsigned short e; char pad[4]; };
struct S99ece0 {
  S99ece0* f();
};
S99ece0* S99ece0::f() {
  char* self = (char*)this;
  char* p = self + 0x24;
  for (int i = 3; i >= 0; i--) {
    *(float*)(p) = 0.0f;
    *(float*)(p + 4) = 0.0f;
    *(unsigned char*)(p + 8) = 0;
    *(unsigned char*)(p + 9) = 0;
    *(unsigned short*)(p + 0xa) = 0;
    p += 0x10;
  }
  p = self + 0x78;
  for (int i = 4; i >= 0; i--) {
    *(float*)(p) = 0.0f;
    *(float*)(p + 4) = 0.0f;
    *(unsigned char*)(p + 8) = 0;
    *(unsigned char*)(p + 9) = 0;
    *(unsigned short*)(p + 0xa) = 0;
    p += 0x10;
  }
  p = self + 0xd0;
  for (int i = 5; i >= 0; i--) {
    FUN_401930(p, 0x10, 2, (void*)FUN_0099cf50);
    p += 0x28;
  }
  FUN_11e073e(self, 0, 0x1b8);
  *(int*)(self + 4) = g_15504dc;
  g_15504dc += 1;
  return this;
}

// ---------------------------------------------------------------------------
// @ 0x0099ed90  ReadAnimationStaticDataFromStreamWrapper  (skeleton body for the VA)
// ---------------------------------------------------------------------------
int FUN_0099ed90() { return 0; }

// ---------------------------------------------------------------------------
// @ 0x0099efa0  uninitialized_copy of 8-byte pairs
// ---------------------------------------------------------------------------
void FUN_0099efa0(char* first, char* last, char* dst) {
  if (first != last) {
    int off = (int)(first - dst);
    do {
      if (dst) {
        *(int*)dst = *(int*)(dst + off);
        *(int*)(dst + 4) = *(int*)(dst + off + 4);
      }
      dst += 8;
    } while (dst + off != last);
  }
}

// ---------------------------------------------------------------------------
// @ 0x0099efd0  nSPCreatureAnim::LoadAnimationStaticData
// ---------------------------------------------------------------------------
int FUN_0099efd0(char* name, int arg) {
  if (name == 0) {
    if (arg != 0) return FUN_00a088e0(arg);
    return 0;
  }
  void* file = fopen(name, "rb");
  if (file == 0) return 0;
  struct { void* vt; void* fp; } local;
  local.vt = (void*)0x1446dd8;
  local.fp = file;
  int r = ((S99ed90*)&local)->f(&local, name, arg);
  fclose(file);
  return r;
}

// ---------------------------------------------------------------------------
// @ 0x0099f050  free array of 0x40 heap blocks
// ---------------------------------------------------------------------------
struct S99f050 { void f(); };
void S99f050::f() {
  int* p = (int*)((char*)this + 0xc2c);
  for (int edi = 0x3f; edi >= 0; edi--) {
    int v = p[-10];
    p = (int*)((char*)p - 0x28);
    if (v && *(int*)(v - 4) != 0) FUN_f47380((void*)v);
  }
}

// ---------------------------------------------------------------------------
// @ 0x0099f090  zero a sub-object
// ---------------------------------------------------------------------------
struct S99f090 { S99f090* f(); };
S99f090* S99f090::f() {
  S99f090* self = this;
  int* p = (int*)this;
  p[0] = 0; p[1] = 0; p[2] = 0; p[3] = 0; p[5] = 0;
  p[7] = 0; p[8] = 0; p[9] = 0; p[0xc] = 0;
  return self;
}
