// Flags: /O2 /MD /Gy /TP /GS-
#include "types.h"
struct Obj00c451a0 {
  char pad[0x1d0];
  unsigned* mpBegin;
  unsigned* mpEnd;
  bool Contains(unsigned value);
};
// @ 0x00c451a0
bool Obj00c451a0::Contains(unsigned value) {
  int count = (int)(mpEnd - mpBegin);
  int i = 0;
  if (count > 0) {
    unsigned* begin = *(unsigned* volatile*)&mpBegin;
    do {
      if (*begin == value)
        return true;
      ++i;
      ++begin;
    } while (i < count);
  }
  return false;
}
