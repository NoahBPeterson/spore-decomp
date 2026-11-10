// Flags: /O2 /MD /Gy /TP /GS-
#include "types.h"
void Free_f47380(void*);
struct Obj007e27a0 {
  char pad[4];
  void* mp4;
  unsigned m8;
  unsigned mC;
  void Helper(void* a, unsigned b); // 0x93dc70
  void Clear();
};
// @ 0x007e27a0
void Obj007e27a0::Clear() {
  Helper(mp4, m8);
  mC = 0;
  if (m8 > 1)
    Free_f47380(mp4);
}
