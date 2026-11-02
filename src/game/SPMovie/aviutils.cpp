// src/game/SPMovie/aviutils.cpp -- migrated from slice(s) s00fc7430 by tools/migrate/rewrite.py
// Object file: SPMovie/aviutils.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// ---- items of slice s00fc7430 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef bool (__cdecl* AviChunkCb)(unsigned* p, unsigned ctx);
// ---- items of slice s00fc7430 end

// @ 0x00fc81f0
unsigned __cdecl AVIStreamerParseFunc(unsigned* p, unsigned size, unsigned a2, unsigned a3, AviChunkCb cb, unsigned ctx, unsigned* out)
{
  if (size < 4)
    return 0;
  if (cb != 0 && cb(p, ctx) == 0)
    return 0;
  if (size < 8)
    return 0;

  unsigned remaining = size;
  unsigned tag = 0;
  unsigned len = 0;
  do {
    if (remaining >= 8) {
      tag = p[0];
      len = p[1];
      p += 2;
      remaining -= 8;
    }
    if (tag == *(unsigned*)0x15b179c || tag == *(unsigned*)0x15b17a4) {
      if (remaining < 4)
        return 0;
      unsigned form = *p++;
      remaining -= 4;
      if (form == *(unsigned*)0x15b17c0) {
        *out = size - remaining;
        return 1;
      }
    } else if (tag == *(unsigned*)0x15b17d8) {
      return 2;
    } else {
      unsigned skip = (len + 1) & 0xfffffffeu;
      if (remaining < skip)
        return 0;
      unsigned short hi = (unsigned short)(tag >> 16);
      if (hi == *(unsigned short*)0x15b17dc || hi == *(unsigned short*)0x15b17e0 ||
          hi == *(unsigned short*)0x15b17e4 || hi == *(unsigned short*)0x15b17e8) {
        *out = skip + 8;
        return 1;
      }
      remaining -= skip;
      p = (unsigned*)((char*)p + skip);
    }
  } while (remaining >= 8);
  return 0;
}
