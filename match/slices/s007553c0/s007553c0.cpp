// slice s007553c0 -- cGameModelWriteJob / cJob load/cache helpers.
//
// Region: /O2 /MD /Gy /EHsc /TP /GS- /arch:SSE2.
// Byte-exact: FUN_00755520, FUN_00755d40, FUN_00755fe0.  The rest are
// best-effort translations or compiling skeletons.

#include "types.h"

// ---------------------------------------------------------------------------
// Callees (masked relocations): signatures/conventions only.
// ---------------------------------------------------------------------------
void FUN_007559a0(int, int, char);
void FUN_006b4b60(void*, void*, int, int);
void* GetManager_755d40();
void FUN_007553b0();
void FUN_00429e00(int, unsigned int, int);
int FUN_006df700(int, int, int);
void FUN_0059c410(int, int);

class IFoo_755d40 {
 public:
  virtual void a0();
  virtual void a1();
  virtual void a2();
  virtual int a3(unsigned int id);
  virtual void a4();
  virtual void a5();
  virtual void a6();
  virtual void a7();
  virtual void a8(void*, int, int, int, int);
};

// @ 0x007553c0  (160 bytes) EH constructor -- skeleton
void FUN_007553c0(void* self) { (void)self; }

// @ 0x00755470  (143 bytes) EH destructor -- skeleton
void FUN_00755470(void* self) { (void)self; }

// @ 0x00755520
struct cJob_755520 {
  char pad_0[0x18];
  int mThreadAffinity;  // +0x18
  bool Continuation(void* fn, void* arg);
};
struct X_755520 {
  bool FUN_00754770(cJob_755520* job);
  bool FUN_00755520(cJob_755520* job);
};
bool X_755520::FUN_00755520(cJob_755520* job) {
  if (FUN_00754770(job)) {
    return true;
  }
  job->mThreadAffinity = 0x80000000;
  return job->Continuation((void*)&FUN_007553b0, this);
}

// @ 0x00755570  (92 bytes) vector fill/insert
void FUN_00755570(int* param_1, unsigned int param_2, int param_3) {
  int iVar2 = param_1[1];
  unsigned int uVar3 = (unsigned int)(iVar2 - *param_1) >> 2;
  if (uVar3 < param_2) {
    FUN_00429e00(iVar2, param_2 - uVar3, param_3);
    return;
  }
  int iVar1 = *param_1 + param_2 * 4;
  int uVar4 = FUN_006df700(iVar2, iVar2, iVar1);
  FUN_0059c410(uVar4, param_1[1]);
  param_1[1] = param_1[1] + ((iVar2 - iVar1 >> 2) * -4);
}

// @ 0x007555d0  cGameModelWriteJob::CacheGameModelToDiskJob_KDTree (563) -- skeleton
void FUN_007555d0(void* self) { (void)self; }

// @ 0x00755810  (388 bytes) -- skeleton
void FUN_00755810(void* self) { (void)self; }

// @ 0x007559a0  (724 bytes) -- skeleton
void FUN_007559a0_impl(void* self) { (void)self; }

// @ 0x00755c80  (153 bytes) EA::ResourceMan swap -- skeleton
void FUN_00755c80(void* self) { (void)self; }

// @ 0x00755d40
void FUN_00755d40(int param_1, int param_2, char param_3) {
  if (param_1 != 0) {
    int r = ((IFoo_755d40*)param_1)->a3(0xe6bce5);
    if (r != 0) {
      FUN_007559a0(r, param_2, param_3);
      return;
    }
  }
  if (param_3 != 0) {
    FUN_006b4b60((void*)param_1, (void*)param_2, 0, 0);
    return;
  }
  IFoo_755d40* mgr = (IFoo_755d40*)GetManager_755d40();
  mgr->a8((void*)param_1, 0, param_2, 0, 0);
}

// @ 0x00755da0  (561 bytes) -- skeleton
void FUN_00755da0(void* self) { (void)self; }

// @ 0x00755fe0
class S_755fe0 {
 public:
  char pad_0[0x104];
  IFoo_755d40* m104;  // +0x104
  int m108;           // +0x108
  void FUN_00755fe0(void* arg);
};
void S_755fe0::FUN_00755fe0(void* arg) {
  (void)arg;
  GetManager_755d40();
  int uVar1 = m108;
  IFoo_755d40* piVar2 = m104;
  if (piVar2 != 0) {
    int iVar3 = piVar2->a3(0xe6bce5);
    if (iVar3 != 0) {
      FUN_007559a0(iVar3, uVar1, 1);
      return;
    }
  }
  FUN_006b4b60(piVar2, (void*)uVar1, 0, 0);
}

// @ 0x00756030  (592 bytes) -- skeleton
void FUN_00756030(void* self) { (void)self; }
