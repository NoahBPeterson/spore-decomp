// Flags: /O1 /MD /Gy /TP /GS-
#include "types.h"
extern int g_16f2974;
void FUN_011eaa80();
// @ 0x011e2030
void FUN_011e2030() {
  int v = g_16f2974 - 1;
  g_16f2974 = v;
  if (!v)
    FUN_011eaa80();
}
