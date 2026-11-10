// Flags: /O2 /MD /Gy /TP /GS-
#include "types.h"
struct Objs00c44f10 {
  char pad[0xf4];
  unsigned mVal;
  unsigned Get();
};
// @ 0x00c44f10
unsigned Objs00c44f10::Get() { return mVal; }
