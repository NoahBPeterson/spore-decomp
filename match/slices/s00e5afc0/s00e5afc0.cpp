// Flags: /O2 /MD /Gy /TP /GS-
#include "types.h"
extern unsigned char* g_16b3c04;
// @ 0x00e5afc0
unsigned char FUN_00e5afc0(unsigned* obj) {
  if (obj[0] == *(unsigned*)(g_16b3c04 + 0x411c))
    return false;
  return obj[0xfc/4] == *(unsigned*)(*(unsigned*)(g_16b3c04 + 0x5190) + 0x10);
}
