// Flags: /O2 /MD /Gy /TP /GS-
#include "types.h"
struct Obj { void Meth(); };
Obj g_16ad698;
// @ 0x0137e830
void FUN_0137e830() {
  g_16ad698.Meth();
}
