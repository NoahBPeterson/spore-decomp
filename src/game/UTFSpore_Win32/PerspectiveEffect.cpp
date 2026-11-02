// src/game/UTFSpore_Win32/PerspectiveEffect.cpp -- migrated from slice(s) s0097f390 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/PerspectiveEffect.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/UTFWinControls/IWinButton.h"
#include "EA/UTFWin/IWindow.h"

// unnamed retail callees and globals (address in the comment)
extern "C" unsigned __cdecl wcslen(const wchar_t*);
#pragma intrinsic(wcslen)

// ---- items of slice s0097f390 begin (TODO(rewrite): local stubs, replace by canonical classes)
void* GetDefaultAllocator();                                     // 0x009512c0
void* AllocObject(int size, int align, const char* name, void* allocator);  // 0x009512d0
namespace EA {
namespace UTFWinControls {
struct PerspectiveEffect {
    void* m00;
    void* volatile m04;
    void* m08;
    void* volatile m0c;
    float m10;
};
}
}
namespace EA {
namespace UTFWinControls {
struct BasicFactory_PerspectiveEffect {
    void* CreateInstance(void* ctx, void* allocator);
};
}
}
// ---- items of slice s0097f390 end

// @ 0x00980680
namespace EA { namespace UTFWinControls {
void* BasicFactory_PerspectiveEffect::CreateInstance(void* ctx, void* allocator)
{
    if (!allocator)
        allocator = GetDefaultAllocator();
    PerspectiveEffect* p = (PerspectiveEffect*)AllocObject(
        0x14, 4, "UTFWin/EA::UTFWinControls::PerspectiveEffect", allocator);
    if (p) {
        p->m04 = (void*)0x13fa72c;
        p->m08 = 0;
        p->m0c = (void*)0x14426a0;
        p->m00 = (void*)0x14440d0;
        p->m04 = (void*)0x14440b4;
        p->m0c = (void*)0x1444098;
        p->m10 = 400.0f;
        return p;
    }
    return 0;
}
}}  // namespace EA::UTFWinControls
