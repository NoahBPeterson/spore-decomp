// Flags: /O2 /MD /Gy /TP /GS-
#include "types.h"
struct Member00c45140 {
  char data[0x20];
  void Dtor();
};
struct Obj00c45140 {
  void* vt0;
  void* vt4;
  char pad8[0x34 - 8];
  void* vt34;
  Member00c45140 m38;
  Member00c45140 m58;
  void BaseDtor();
  void Dtor();
};
// @ 0x00c45140
void Obj00c45140::Dtor() {
  vt0 = (void*)0x0146d188;
  vt4 = (void*)0x0146d174;
  vt34 = (void*)0x0146d164;
  m58.Dtor();
  m38.Dtor();
  vt34 = (void*)0x013eb394;
  BaseDtor();
}
