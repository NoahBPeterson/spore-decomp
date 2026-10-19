// src/game/UTFSpore_Win32/EATextUnicode.cpp -- migrated from slice(s) s0089d3b0 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/EATextUnicode.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/Text/BidiClass.h"
#include "EA/Text/GlyphLayoutInfo.h"
#include "EA/Text/LayoutSettings.h"
#include "EA/Text/LineLayout.h"
#include "EA/Text/TextStyle.h"
#include "EA/Text/Typesetter.h"

// ---- items of slice s0089d3b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace EA {
namespace Text {
extern unsigned char gBidiClassTable256[256];
}
}
namespace EA {
namespace Text {
extern unsigned char gBidiClassTableArabic[256];
}
}
// ---- items of slice s0089d3b0 end

// @ 0x0089e170
namespace EA {
namespace Text {
BidiClass GetBidiClass(wchar_t c)
{
    unsigned short ch = c;
    if (ch < 0x100) return (BidiClass)gBidiClassTable256[ch];
    unsigned u = ch;
    if (u - 0x3400 <= 0x6bbb) return (BidiClass)1;
    if (u - 0xac00 <= 0x2ba3) return (BidiClass)1;
    if (u - 0xff10 <= 9) return (BidiClass)4;
    if (u - 0x2000 <= 10 || ch == 0x2028 || ch == 0x3000) return (BidiClass)12;
    if (u - 0x300 <= 0x6f) return (BidiClass)6;
    if (ch == 0x202f || ch == 0x60c) return (BidiClass)7;
    if (u - 0x20a0 <= 0x2f) return (BidiClass)9;
    if (u - 0xe34 <= 6) return (BidiClass)6;
    if (u - 0xe47 <= 7) return (BidiClass)6;
    if (ch == 0xe31) return (BidiClass)6;
    if (u - 0x590 <= 0x6f)
        return (BidiClass)((((ch < 0x5c5) ? -1 : 0) & 4) + 2);
    if (u - 0x600 <= 0xff) return (BidiClass)gBidiClassTableArabic[u];
    if (ch == 0xfeff) return (BidiClass)10;
    if (u - 0x200b <= 2) return (BidiClass)10;
    if (u - 0x2060 <= 3) return (BidiClass)10;
    if (u - 0x2018 <= 5) return (BidiClass)10;
    if (u - 0x202a <= 4) {
        switch (ch) {
        case 0x202a: return (BidiClass)0x11;
        case 0x202b: return (BidiClass)0xf;
        case 0x202c: return (BidiClass)0x12;
        case 0x202d: return (BidiClass)0x10;
        case 0x202e: return (BidiClass)0xe;
        }
    }
    if (u - 0xeb4 <= 5) return (BidiClass)6;
    if (u - 0xebb <= 1) return (BidiClass)6;
    if (u - 0xec8 <= 5) return (BidiClass)6;
    return (BidiClass)((((ch != 0xeb1) - 1) & 5) + 1);
}
}
}  // namespace EA::Text
