// src/game/SPMovie/aviutils.cpp -- migrated from slice(s) s00fc7430 by tools/migrate/rewrite.py
// Object file: SPMovie/aviutils.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// ---- items of slice s00fc7430 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef bool (__cdecl* AviChunkCb)(unsigned* p, unsigned ctx);
namespace rw {
namespace movie {
// The RIFF four-character codes and the two-character chunk-type codes of an AVI file.
class AVIUtils {
public:
    static const unsigned FCC_RIFF;                          // 0x015b179c
    static const unsigned FCC_LIST;                          // 0x015b17a4
    static const unsigned FCC_movi;                          // 0x015b17c0
    static const unsigned FCC_idx1;                          // 0x015b17d8
    static const unsigned short TCC_chunkTypeDIBbits;        // 0x015b17dc
    static const unsigned short TCC_chunkTypeDIBcompressed;  // 0x015b17e0
    static const unsigned short TCC_chunkTypePaletteChange;  // 0x015b17e4
    static const unsigned short TCC_chunkTypeWaveBytes;      // 0x015b17e8
};
}
}
using rw::movie::AVIUtils;
// A RIFF chunk header: its four-character code and its data size.
struct AviChunkHeader {
    unsigned mId;
    unsigned mSize;
};
// ---- items of slice s00fc7430 end

// @ 0x00fc81f0
unsigned __cdecl AVIStreamerParseFunc(unsigned* data, unsigned size, unsigned a2, unsigned a3, AviChunkCb cb, unsigned ctx, unsigned* out)
{
  unsigned* p = data;
  unsigned remaining = size;
  if (size < 4 || (cb != 0 && !cb(p, ctx)))
    return 0;

  AviChunkHeader hdr;
  while (remaining >= 8) {
    if (remaining >= 8) {
      hdr = *(AviChunkHeader*)p;
      p += 2;
      remaining -= 8;
    }
    if (hdr.mId == AVIUtils::FCC_RIFF || hdr.mId == AVIUtils::FCC_LIST) {
      if (remaining < 4)
        return 0;
      unsigned form = *p++;
      remaining -= 4;
      if (form == AVIUtils::FCC_movi) {
        *out = size - remaining;
        return 1;
      }
    } else if (hdr.mId == AVIUtils::FCC_idx1) {
      return 2;
    } else {
      unsigned skip = (hdr.mSize + 1) & ~1u;
      if (remaining < skip)
        return 0;
      unsigned short type = (unsigned short)(hdr.mId >> 16);
      if (type == AVIUtils::TCC_chunkTypeDIBbits || type == AVIUtils::TCC_chunkTypeDIBcompressed ||
          type == AVIUtils::TCC_chunkTypePaletteChange || type == AVIUtils::TCC_chunkTypeWaveBytes) {
        *out = skip + 8;
        return 1;
      }
      remaining -= skip;
      p = (unsigned*)((char*)p + skip);
    }
  }
  return 0;
}
