// Flags: /O2 /MD /Gy /TP /GS-
#include "types.h"
struct Objs00c44c70 {
  char pad[0x84];
  unsigned mVal;
  unsigned Get();
};
// @ 0x00c44c70
unsigned Objs00c44c70::Get() { return mVal; }
