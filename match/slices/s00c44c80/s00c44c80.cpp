// Flags: /O2 /MD /Gy /TP /GS-
#include "types.h"
struct Objs00c44c80 {
  char pad[0x84];
  unsigned mState;
  bool Is3();
};
// @ 0x00c44c80
bool Objs00c44c80::Is3() { return mState == 3; }
