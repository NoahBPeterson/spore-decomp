// src/game/UTFSpore_Win32/pngmem.cpp -- migrated from slice(s) s0086d090 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/pngmem.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <setjmp.h>

// ---- items of slice s0086d090 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef void* png_voidp;
__declspec(noinline) void png_destroy_struct(png_voidp struct_ptr);
// ---- items of slice s0086d090 end

// @ 0x0086d7d0
void png_destroy_struct(png_voidp struct_ptr)
{
   if (struct_ptr != 0)
      free(struct_ptr);
}
