// Slice s00891190 - EA::Text::OutlineFont (EAText) virtual leaf helpers.
// Flags: /O2 /MD /Gy /TP /arch:SSE /GS- /fp:fast  (the EAText module has no /EHsc).
#include "types.h"

namespace EA { namespace Text {

// EA::Text::FontType: kFontTypeUnknown = 0, kFontTypeOutline = 2.
// EA::Text::OutlineFont : public Font.  Only the member the retail helper reads is modelled.
struct OutlineFont {
    uint32_t pad00[4];                              // +0x00 .. +0x0f
    void*    mpOTF;                                 // +0x10 (the OpenType face object)

    uint32_t GetFontType();                          // 0x00891190
};

// @ 0x00891190
uint32_t OutlineFont::GetFontType()
{
    return mpOTF ? 2 : 0;
}

}}  // namespace EA::Text
