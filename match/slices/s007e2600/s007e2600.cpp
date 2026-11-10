// Flags: /O2 /MD /Gy /TP /GS-
#include "types.h"
struct Obj007e2600 {
  unsigned slot[20];
  Obj007e2600* Init();
};
// @ 0x007e2600
Obj007e2600* Obj007e2600::Init() {
  unsigned* p = (unsigned*)this;
  unsigned z = 0;
  p[0]=z; p[1]=z; p[2]=z;
  p[5]=z; p[6]=z; p[7]=z;
  p[10]=z; p[11]=z; p[12]=z;
  unsigned c = 0x1667bac;
  p[15]=c; p[16]=c;
  p[17]=0x1667bad;
  p[19]=0xffffffff;
  return this;
}
