// Slice s00828c30 -- UI/render helper thunks around cSPUIPropertyLayout.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include "types.h"

// ===========================================================================
// 008290e0  conditional virtual-dispatch thunk (MATCH)
// ===========================================================================
struct C25c {
  char pad0[0x10];
  void* m10;          // +0x10
  char pad14[0x14];   // +0x14 .. +0x27
  void* m28;          // +0x28
  void Do(int arg);
};
void C25c::Do(int arg) {
  if (m10) {
    ((void(__thiscall*)(void*, int))(*(void***)m10)[2])(m10, arg);
  } else {
    void* o = m28;
    if (o) ((void(__thiscall*)(void*, int))(*(void***)o)[0x6c / 4])(o, arg);
  }
}

// ===========================================================================
// 00828df0  three virtual calls guarded by (m10 && mObj)
//   complete but not byte-exact: cl emits `cmp [mem],0; reload` for the null
//   test instead of the original `mov ecx,[mem]; test ecx,ecx`.
// ===========================================================================
struct IThing {
  virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
  virtual void v4(); virtual void v5(int, int); virtual void v6();
};
struct C25b {
  char pad0[0xc];
  IThing* mObj;       // +0xc
  int m10;            // +0x10
  void Do(int arg);
};
void C25b::Do(int arg) {
  if (m10 && mObj) {
    mObj->v4();
    mObj->v5(arg, m10);
    mObj->v6();
  }
}
