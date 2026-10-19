// src/game/UTFSpore_Win32/Utils.cpp -- migrated from slice(s) s0095eeb0 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/Utils.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// @ 0x0095f8c0
namespace EA {
namespace UTFWin {
unsigned int ModulateARGB32(unsigned int c1, unsigned int c2)
{
    uint32_t g = (c1 >> 8 & 0xff) * (c2 & 0xff00) + 0x100;
    uint32_t r = (c1 >> 0x10 & 0xff) * (c2 & 0xff0000) + 0x10000;
    uint32_t b = (c1 & 0xff) * (c2 & 0xff) + 1;
    uint32_t a = (c1 >> 0x18) * (c2 >> 0x18) + 1;
    return (((g >> 8) + g) & 0xff0000) | (((r >> 8) + r) & 0xff0000ff) |
           (((b >> 8) + b)) | ((((a & 0xffffff00) + a * 0x100) & 0xff0000) << 8);
}
}
}  // namespace EA::UTFWin
