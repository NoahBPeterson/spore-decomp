// Tier-2 (byte-exact) sources. Each function: minimal idiomatic source compiled with
// VS2008 cl 15.00.30729.01 and verified with tools/matching/cmpobj.py.
#include <stdlib.h>

// @ 0x0092C270  RefPack::ReadBigEndian
unsigned int RefPackReadBigEndian(const void* p, int n) {
  if (n == 1)
    return *(const unsigned char*)p;
  if (n == 4)
    return _byteswap_ulong(*(const unsigned int*)p);
  if (n == 2)
    return _byteswap_ushort(*(const unsigned short*)p);
  if (n == 3) {
    const unsigned char* b = (const unsigned char*)p;
    return (((b[0] << 8) | b[1]) << 8) | b[2];
  }
  return 0;
}

// @ 0x0092CAD0  RefPack::IsValidHeader
bool __stdcall RefPackIsValidHeader(const void* p, unsigned int /*size*/) {
  return (_byteswap_ushort(*(const unsigned short*)p) & 0x1FFF) == 0x10FB;
}
