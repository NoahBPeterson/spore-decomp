// Flags: /O2 /MD /Gy /TP /GS-
#include "types.h"
struct Iter007e27d0 {
  unsigned* node;
  unsigned* bucket;
};
struct Table007e27d0 {
  unsigned unused0;
  unsigned** buckets;
  unsigned bucketCount;
  void Find(Iter007e27d0* out, const unsigned* key);
};
struct Obj007e27d0 {
  char pad[0xb8];
  Table007e27d0 table;
  unsigned char Contains(unsigned key);
};
// @ 0x007e27d0
unsigned char Obj007e27d0::Contains(unsigned key) {
  Table007e27d0* tablePtr = &table;
  Iter007e27d0 it;
  tablePtr->Find(&it, &key);
  return it.node != tablePtr->buckets[tablePtr->bucketCount];
}
