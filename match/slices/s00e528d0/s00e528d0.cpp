// Flags: /O2 /MD /Gy /TP /GS-
#include "types.h"
struct Pool { char* Get(unsigned id); }; // 0xb72210
extern char* g_16b3c04;
// Retail: id live-in eax (push eax; call Get), val at [esp+4], store at row+4.
// MSVC 2008 has no eax-first ABI without naked/asm (forbidden) — left as readable 2-arg form.
// @ 0x00e528d0
void FUN_00e528d0(unsigned id, unsigned val) {
  char* row = ((Pool*)(g_16b3c04 + 0x54))->Get(id);
  *(unsigned*)(row + 4) = val;
}
