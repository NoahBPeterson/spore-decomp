#include <wchar.h>

// @ 0x0068C680  Resource::HashNameN
unsigned int HashNameN(const char* s, int n) {
  unsigned int h = 0x811C9DC5;
  while (n--)
    h = (h * 0x01000193) ^ towlower((wchar_t)*s++);
  return h;
}
