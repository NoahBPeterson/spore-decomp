// src/game/UTFSpore_Win32/EATextOutlineFont.cpp -- migrated from slice(s) s00890010 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/EATextOutlineFont.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/Text/AnalysisInfo.h"
#include "EA/Text/Font.h"
#include "EA/Text/FontServer.h"
#include "EA/Text/FontType.h"
#include "EA/Text/LayoutSettings.h"
#include "EA/Text/TextStyle.h"

// ---- items of slice s00890010 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace EA {
namespace Text {
struct OutlineFont {
    uint8_t mData[0x10];                  // +0x000
    EA::IO::IStream* mpStream;            // +0x010
    uint8_t mData014[0x150];              // +0x014
    bool    mbOption1;                    // +0x164
    void SetOption(int option, int value);   // 0x00890fa0
    FontType GetFontType();                  // 0x00891190
};
}
}
// ---- items of slice s00890010 end

// @ 0x00890fa0
void EA::Text::OutlineFont::SetOption(int option, int value)
{
    if (option == 1)
        mbOption1 = (value != 0);
}

// @ 0x00891190
EA::Text::FontType EA::Text::OutlineFont::GetFontType()
{
    return mpStream ? kFontTypeOutline : kFontTypeUnknown;
}
