// Flags: /O2 /MD /Gy /TP /GS-
#include "types.h"

struct cCommandBase {
  void* vt;
  int a;
  int b;
};

void __fastcall FUN_0083c800(cCommandBase* self); // 0x0083c800
extern "C" int __cdecl atexit(void (__cdecl*)(void)); // 0x011e07ef

cCommandBase g_16b0c3c;

// @ 0x0137e810
void dynamic_init_0137e810() {
  FUN_0083c800(&g_16b0c3c);
  g_16b0c3c.vt = (void*)0x01482dfc;
  atexit((void (__cdecl*)(void))0x013c7d70);
}
