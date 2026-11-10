// Flags: /O2 /MD /Gy /TP /GS-
#include "types.h"
struct Obj00c0b8d0 {
  char mPad[0xb88];
  unsigned mValue;
  unsigned GetValue();
};
// @ 0x00c0b8d0
unsigned Obj00c0b8d0::GetValue() { return mValue; }
