// slice s00754310 -- SP::RegisterModel / CreateModelInstance / model-instance jobs.
//
// Region: /O2 /MD /Gy /EHsc /TP /GS- /arch:SSE2.  Byte-exact: CreateModelInstance.
// The rest are best-effort translations or compiling skeletons.

#include "types.h"

// ---------------------------------------------------------------------------
// Callees (masked relocations): signatures/conventions only.
// ---------------------------------------------------------------------------
bool FUN_00754960(void*, void*, void*);
void FUN_006acfe0(void*, void*);
void FUN_0067dd60();
void FUN_007004d0();

class RefT_007545b0 {
 public:
  virtual int AddRef();
  virtual int Release();
};

// @ 0x00754310  SP::RegisterModel (456 bytes)  -- skeleton
void SP_RegisterModel_00754310(void* self, void* a, void* b) { (void)self; (void)a; (void)b; }

// @ 0x007544e0  (193 bytes) EH operator new + ctor + assign -- skeleton
void FUN_007544e0(void* self) { (void)self; }

// @ 0x007545b0  (102 bytes) refcounted swap into this->m44+0x13c
struct S_007545b0 {
  char pad_0[0x44];
  void* m044;  // +0x44
  char pad_48[0x100 - 0x48];
  RefT_007545b0* m100;  // +0x100
  bool FUN_007545b0(int param_2);
};
bool S_007545b0::FUN_007545b0(int param_2) {
  int v = *(int*)(param_2 + 0x1c);
  if (v == 0) {
    if (m100 != 0) {
      FUN_006acfe0((char*)this + 0xf4, m100);
      int* slot = (int*)(*(int*)((char*)this + 0x44) + 0x13c);
      RefT_007545b0* piVar2 = m100;
      RefT_007545b0* piVar3 = (RefT_007545b0*)*slot;
      if (piVar2 != piVar3) {
        if (piVar2 != 0) piVar2->AddRef();
        *slot = (int)piVar2;
        if (piVar3 != 0) piVar3->Release();
      }
    }
  }
  return true;
}

// @ 0x00754620  (296 bytes) property lookup loop (EH) -- skeleton
void FUN_00754620(void* self, void* a) { (void)self; (void)a; }

// @ 0x00754770  (495 bytes) -- skeleton
void FUN_00754770(void* self) { (void)self; }

// @ 0x00754960  (561 bytes) -- skeleton
void FUN_00754960_impl(void* self) { (void)self; }

// @ 0x00754ba0  SP::CreateModelInstance
bool CreateModelInstance_00754ba0(int a1, int a2, int a3, int a4) {
  struct K {
    int a;
    int b;
    int c;
  } k;
  k.a = a1;
  k.b = 0xe6bce5;
  k.c = a2;
  if (FUN_00754960(&k, (void*)a3, (void*)a4)) {
    return true;
  }
  k.b = 0x2f4e681b;
  return FUN_00754960(&k, (void*)a3, (void*)a4);
}

// @ 0x00754c20  (114 bytes) job continuation -- skeleton
void FUN_00754c20(void* self, void* job) { (void)self; (void)job; }

// @ 0x00754ca0  SP::CompileToPropertyModel (725 bytes, EH) -- skeleton
void FUN_00754ca0(void* self) { (void)self; }

// @ 0x00755070  (445 bytes) -- skeleton
void FUN_00755070(void* self) { (void)self; }

// @ 0x00755240  cCreateModelInstanceJob::LoadAsArenaJob (160 bytes) -- skeleton
void FUN_00755240(void* self) { (void)self; }

// @ 0x007552e0  (223 bytes) -- skeleton
void FUN_007552e0(void* self) { (void)self; }
