// Flags: /O2 /MD /Gy /TP /GS-
#include "types.h"
struct Host {
  void Bind(void* a, void* b, void* c); // 0x00695b40
};
// @ 0x00c45100
bool FUN_00c45100(Host* self, void* p) {
  if (p)
    self->Bind(p, (void*)0x01574c48, (void*)0x0146d138);
  return true;
}
