// Flags: /O2 /MD /Gy /TP /GS-
#include "types.h"
struct Obj00ad33a0 {
  char pad[0xd4];
  void* vt;
  Obj00ad33a0* Dtor(unsigned flags);
};
void __fastcall FUN_00c8a420(Obj00ad33a0* self);
void __cdecl operator_delete(void* p); // 0xf47380
// @ 0x00ad33a0
Obj00ad33a0* Obj00ad33a0::Dtor(unsigned flags) {
  vt = (void*)0x013ef094;
  FUN_00c8a420(this);
  if (flags & 1)
    operator_delete(this);
  return this;
}
