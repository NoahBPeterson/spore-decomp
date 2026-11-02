// src/game/UTFSpore_Win32/allocator1.cpp -- migrated from slice(s) s00950bb0 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/allocator1.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/UTFWin/RenderContext.h"
#include "EA/UTFWin/Window.h"
#include <intrin.h>

// ---- items of slice s00950bb0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace EA {
namespace UTFWin {
class MultiHeapObject_s0095_0bb0 { public:
    static void operator_delete(void* p);
};
}
}
namespace EA {
namespace UTFWin {
struct MemPoolObj { void Free(void*); };
}
}
namespace EA {
namespace UTFWin {
extern MemPoolObj* g_pool16c8b44;
}
}
// ---- items of slice s00950bb0 end

// @ 0x00951330
namespace EA { namespace UTFWin {
void MultiHeapObject_s0095_0bb0::operator_delete(void* p)
{
    if (p) {
        int* alloc = *(int**)((char*)p - 8);
        p = (char*)p - 8;
        if (alloc) {
            ((void(__thiscall*)(void*, void*, int))((void**)*(void**)alloc)[3])(alloc, p, 0);
        } else {
            g_pool16c8b44->Free(p);
        }
    }
}
}}  // namespace EA::UTFWin
