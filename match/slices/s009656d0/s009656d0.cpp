// @ 0x009656D0
//
// UTFWin drawable paint / renderable build (PDB candidate:
// EA::UTFWinControls::ButtonDrawable::CreateRenderables). Original is
// __thiscall (this in ECX, three stack args, `ret 0xc`) and is ~5185 bytes:
// it begins 2D rendering (RenderContext::Begin2D + vtable slot +4), then
// dispatches on the drawable state and emits the images/text through the
// render context vtable.
//
// PARTIAL: entry signature only. The full renderable build was not
// reconstructed; listed in partial.txt.
#include "types.h"

struct DrawableSelf;
struct RenderContext;

void DrawablePaint(DrawableSelf* self, RenderContext* ctx, float* a3, uint32_t* a4) {
  (void)self;
  (void)ctx;
  (void)a3;
  (void)a4;
}
