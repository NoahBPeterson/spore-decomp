// Flags: /O2 /MD /Gy /TP /GS-
#include "types.h"
// @ 0x00e52a40
int FUN_00e52a40(int a, int b) {
  int sum = a + b;
  int hi = 0x13;
  int lo = 0;
  int* p = (sum < 0) ? &lo : &sum;
  if (*p > 0x13) p = &hi;
  return *p;
}
