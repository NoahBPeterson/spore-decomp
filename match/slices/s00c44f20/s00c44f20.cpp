// Flags: /O2 /MD /Gy /TP /GS-
#include "types.h"
struct Obj00c44f20 {
  char pad[0x148];
  int mHandle;
  void Clear();
};
void* __stdcall FUN_00b3d3e0(int handle, int flag);
struct T { void Meth(); };
// @ 0x00c44f20
void Obj00c44f20::Clear() {
  if (mHandle != -1) {
    T* p = (T*)FUN_00b3d3e0(mHandle, 1);
    p->Meth();
    mHandle = -1;
  }
}
