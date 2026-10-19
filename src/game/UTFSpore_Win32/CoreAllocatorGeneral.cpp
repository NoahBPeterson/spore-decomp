// src/game/UTFSpore_Win32/CoreAllocatorGeneral.cpp -- migrated from slice(s) s00925770 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/CoreAllocatorGeneral.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <windows.h>
#include <stddef.h>
#include <string.h>

// ---- items of slice s00925770 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace EA {
namespace Trace {
extern void* g_01668eac;
}
}
namespace EA {
namespace Trace {
extern void* g_0154df84;
}
}
namespace EA {
namespace Trace {
extern char  g_0154df88;
}
}
namespace EA {
namespace Trace {
extern void* g_0154df8c;
}
}
namespace EA {
namespace Trace {
extern void* g_0154df90;
}
}
namespace EA {
namespace Trace {
extern void* g_016c8b44;
}
}
// ---- items of slice s00925770 end

// @ 0x00925cb0
namespace EA { namespace Trace {
void* GetDefaultAllocatorX()
{
    if (!g_01668eac) {
        if (!g_0154df84) {
            g_0154df84 = g_016c8b44;
            g_0154df88 = 0;
            g_0154df8c = 0;
            g_0154df90 = 0;
        }
        g_01668eac = (void*)0x0154df80;
    }
    return g_01668eac;
}
}}  // namespace EA::Trace
