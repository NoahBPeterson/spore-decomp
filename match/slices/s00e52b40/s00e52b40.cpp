// Flags: /O2 /MD /Gy /TP /GS-
#include "types.h"
extern unsigned* g_16b3c04; // actually Mgr*
// @ 0x00e52b40
int FUN_00e52b40(int idx) {
  unsigned* table = *(unsigned**)((char*)g_16b3c04 + 0x5190);
  unsigned v = table[idx + (0x34/4)]; // [ecx + edx*4 + 0x34]
  if (v == 1 || v == 2) return 1;
  return 0;
}
