// src/game/UTFSpore_Win32/ImageCursorProvider.cpp -- migrated from slice(s) s0097cea0 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/ImageCursorProvider.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/UTFWin/Image.h"
#include "EA/UTFWinControls/ImageDrawable.h"
#include "EA/UTFWin/RenderContext.h"
#include "EA/UTFWin/cDropShadowDescriptor.h"
#include <math.h>

// ---- items of slice s0097cea0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct ImageCursorProvider {
    virtual void slot0();
    virtual void slot1();   // added to make the vtable live
    char pad[0x0c];
    void* AsInterface(unsigned int id);
};
// ---- items of slice s0097cea0 end

// @ 0x0097da60
void* ImageCursorProvider::AsInterface(unsigned int id)
{
    if (id <= 0xee3f516e) {
        if (id == 0xee3f516e) return this;
        if (id == 0x2ce4360) return this;
        if (id == 0x2cf3268) return this;
    } else if (id == 0xeec58382 && this != 0) {
        return (char*)this + 4;
    }
    return 0;
}

// @ 0x0097dad0
void CursorWindow_ctor(void* self)
{ (void)self; }
