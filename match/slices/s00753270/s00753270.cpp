// slice s00753270 -- SP::cModelWorld / cMWGroupInternal / cLoadQueue helpers.
//
// Region: /O2 /MD /Gy /EHsc /TP /GS- /arch:SSE2 (EH prologue, no stack cookie).
// Byte-exact: FUN_00753dc0, FUN_00754110, FUN_007542b0.  The rest are best-effort
// translations or compiling skeletons (see nonmatching.txt / partial.txt).

#include "types.h"

// ---------------------------------------------------------------------------
// Callees (masked relocations in the original): only signature/convention matter.
// ---------------------------------------------------------------------------
void FUN_007387f0(void*);
void FUN_007389c0(void*, int);
void FUN_00738900(void*);
void FUN_006b4b60(void*, void*, int, int);
char FUN_0071ded0(int, int, void*, void*, void*, void*, int);
void FUN_00738610(int, int, void*);
void* RBTreeIncrement(void*);
void FUN_0074fea0(void*);
void FUN_0093dd80_754250(int, int, int, int, int);

// @ 0x00753270  (708 bytes) large cModelWorld helper; skeleton
void FUN_00753270(void* self) { (void)self; }

// @ 0x00753540  (62 bytes) tree foreach
struct TreeNode_00753540 {
  char pad_0[0x14];
  void* mObject;  // +0x14
};
struct TreeWalker_00753540 {
  char pad_0[0x10];
  void* mEnd;   // +0x10
  void* mRoot;  // +0x14
  void ForEach(float a, float b);
};
struct NodeRunThunk {
  void Run(float a, float b);
};
void TreeWalker_00753540::ForEach(float a, float b) {
  void* n = mRoot;
  void* end = (char*)this + 0x10;
  while (n != end) {
    ((NodeRunThunk*)((TreeNode_00753540*)n)->mObject)->Run(a, b);
    n = RBTreeIncrement(n);
  }
}

// @ 0x00753580  (79 bytes) cMWGroupInternal teardown/scalar-deleting dtor
void cMWGroupInternal_00753580(void* self) { (void)self; }

// @ 0x00753630  (316 bytes) job queue lookup; skeleton
void FUN_00753630(void* self, int* p) { (void)self; (void)p; }

// @ 0x00753770  (126 bytes) element constructor (inlined cSPTransform ctor)
void* FUN_00753770(void* self, void* a, void* b) { (void)a; (void)b; return self; }

// @ 0x00753810  (108 bytes) vector-of-model-info constructor
void* FUN_00753810(void* self, void* a, int n, void* src) { (void)a; (void)n; (void)src; return self; }

// @ 0x00753880  (127 bytes) cLoadQueue constructor (EH)
void cLoadQueue_ctor_00753880(void* self) { (void)self; }

// @ 0x00753900  (678 bytes) cModelWorld constructor (EH); skeleton
void cModelWorld_ctor_00753900(void* self) { (void)self; }

// @ 0x00753bb0  (155 bytes) fixed-allocator + node insert (EH)
void* FUN_00753bb0(void* self, void* a, void* b) { (void)a; (void)b; return 0; }

// @ 0x00753c50  (187 bytes) SP::cModelWorld::FinalRelease
void cModelWorld_FinalRelease_00753c50(void* self) { (void)self; }

// @ 0x00753d10  (174 bytes) operator new + ctor + assign (EH)
void* FUN_00753d10(void* self, void* a, void* b, void* c) { (void)a; (void)b; (void)c; return 0; }

// @ 0x00753dc0  (59 bytes)
void FUN_00753dc0(int param_1, unsigned char param_2) {
  if ((param_2 & 2) != 0) {
    FUN_007387f0((void*)param_1);
  } else if ((param_2 & 4) != 0) {
    FUN_007389c0((void*)param_1, 1);
  }
  if ((param_2 & 8) != 0) {
    FUN_00738900((void*)param_1);
  }
}

// @ 0x00753e00  (383 bytes) skeleton
void FUN_00753e00(void* self) { (void)self; }

// @ 0x00753fc0  (31 bytes) callback refcount release; register allocation differs
struct RC_00753fc0 {
  void* p;
  volatile int n;
};
void FUN_00753fc0(RC_00753fc0* param_1) {
  int n = (param_1->n += -1);
  if (n == 0) {
    param_1->n = 1;
    typedef void(__stdcall *Fn)(int);
    Fn fn = *(Fn*)param_1->p;
    fn(1);
  }
}

// @ 0x00753fe0  (301 bytes) KDTree asset build (EH); skeleton
void FUN_00753fe0(void* self, void* a) { (void)self; (void)a; }

// @ 0x00754110  (25 bytes)
class Stub_754110 {
 public:
  char pad_0[0x64];
  void* m064;
  void* m068;
  bool FUN_00754110(int arg);
};
bool Stub_754110::FUN_00754110(int arg) {
  FUN_006b4b60(m068, m064, 0, 0);
  return true;
}

// @ 0x007541b0  (158 bytes) find-or-insert into a 0x20-stride table
void FUN_007541b0(int param_1, int param_2, int param_3) {
  int local_20 = -1;
  int local_1c = -1;
  int local_18 = 2;
  int local_14 = 2;
  int local_10 = param_2;
  int local_c = param_3;
  int local_8 = 8;
  int local_4 = 8;
  char c = (char)FUN_0071ded0(param_1, 2, &local_20, &local_8, &local_10, &local_18, 0);
  if (c != 0) {
    *(int*)(local_1c * 0x20 + 4 + *(int*)(param_1 + 8)) = param_2;
    FUN_00738610(param_1, 1, &local_20);
    return;
  }
  if (local_1c >= 0) {
    *(int*)(local_1c * 0x20 + 4 + *(int*)(param_1 + 8)) = param_2;
  }
}

// @ 0x00754250  (94 bytes) two-short init + thunk ctor (EH)
int FUN_00754250(int param_1, int param_2) {
  *(uint16_t*)(param_1 + 0x10) = 2;
  *(uint16_t*)(param_1 + 0x12) = 0x39;
  FUN_0093dd80_754250(0x39, 0, param_2, 0x18, 1);
  return param_1;
}

// @ 0x007542b0  (79 bytes)
bool FUN_007542b0(int param_1, int param_2) {
  if (param_2 != 0) {
    ++*(int*)(param_2 + 4);
    void* fn = *(void**)(param_1 + 0x24);
    void* a = *(void**)(param_1 + 0x20);
    *(int*)(param_1 + 0x20) = param_2;
    *(void**)(param_1 + 0x24) = (void*)&FUN_00753fc0;
    if (fn != 0) {
      ((void(__cdecl*)(void*))fn)(a);
    }
  } else {
    void* fn = *(void**)(param_1 + 0x24);
    void* a = *(void**)(param_1 + 0x20);
    *(void**)(param_1 + 0x20) = 0;
    *(void**)(param_1 + 0x24) = 0;
    if (fn != 0) {
      ((void(__cdecl*)(void*))fn)(a);
      return true;
    }
  }
  return true;
}
