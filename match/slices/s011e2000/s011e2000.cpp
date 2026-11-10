// Flags: /O2 /MD /Gy /TP /GS-
#include "types.h"
extern int g_16f2974;
void FUN_011eaa50();
struct Obj011e2000 { Obj011e2000* AddRef(); };
// @ 0x011e2000
Obj011e2000* Obj011e2000::AddRef() {
  int old = g_16f2974;
  int neu = *(volatile int*)&g_16f2974;
  ++neu;
  g_16f2974 = neu;
  if (old == 0)
    FUN_011eaa50();
  return this;
}
