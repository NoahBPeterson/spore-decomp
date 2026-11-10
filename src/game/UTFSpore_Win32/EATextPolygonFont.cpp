// src/game/UTFSpore_Win32/EATextPolygonFont.cpp -- migrated from slice(s) s0071f410 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/EATextPolygonFont.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/Text/Font.h"
#include "EA/Text/FontDescription.h"

namespace EA {
namespace Text {
class PolygonFont : public Font {
 public:
  virtual bool GetFontDescription(FontDescription& fontDescription);    // slot 11

  uint32_t mUnknown048;                                        // 0x048
  FontDescription mFontDescription;                            // 0x04c
};
}  // namespace Text
}  // namespace EA

// ---- items of slice s0071f410 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Vertex3D {
    uint32_t m[6];
};
// ---- items of slice s0071f410 end

// @ 0x00720250
void CopyVertex3D(Vertex3D* first, Vertex3D* last, Vertex3D* dest)
{
    while (first != last) {
        *dest = *first;
        ++first;
        ++dest;
    }
}

// @ 0x008924d0
bool EA::Text::PolygonFont::GetFontDescription(FontDescription& fontDescription)
{
    fontDescription = mFontDescription;
    return true;
}
