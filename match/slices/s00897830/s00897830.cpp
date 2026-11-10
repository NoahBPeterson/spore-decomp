// Slice s00897830: EA::Text::Typesetter::SetGlyphLayoutInfo (EA::Text manager2.obj).
#include "game/types.h"
#include "EA/Text/Typesetter.h"
#include "EA/Text/GlyphLayoutInfo.h"
#include "EA/Text/GlyphMetrics.h"

namespace EA {
namespace Text {

// @ 0x00897830
void Typesetter::SetGlyphLayoutInfo(GlyphLayoutInfo& info, float penX,
                                    EA::Text::GlyphMetrics const& metrics)
{
  info.mfPenX = penX;
  info.mfPenY = 0.0f;
  info.mfX1 = penX + metrics.mfHBearingX;
  float yScale = mLayoutSettings.mfYScale;
  info.mfY1 = -(yScale * metrics.mfHBearingY);
  info.mfX2 = (metrics.mfSizeX + metrics.mfHBearingX) + penX;
  info.mfY2 = -((metrics.mfHBearingY - metrics.mfSizeY) * mLayoutSettings.mfYScale);
  info.mfAdvance = metrics.mfHAdvanceX;
}

}  // namespace Text
}  // namespace EA
