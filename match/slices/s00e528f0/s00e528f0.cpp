// Flags: /O2 /MD /Gy /TP /GS-
#include "types.h"
struct Pool { char* Get(unsigned id); };
extern char* g_16b3c04;
// Retail: id in eax; idx at [esp+4]; float at [esp+8]; store xmm to [row+0xc+idx*4]
// @ 0x00e528f0
void FUN_00e528f0(unsigned id, unsigned idx, float v) {
  char* row = ((Pool*)(g_16b3c04 + 0x54))->Get(id);
  ((float*)(row + 0xc))[idx] = v;
}
