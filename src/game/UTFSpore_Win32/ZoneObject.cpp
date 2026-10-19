// src/game/UTFSpore_Win32/ZoneObject.cpp -- migrated from slice(s) s00925770 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/ZoneObject.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <windows.h>
#include <stddef.h>
#include <string.h>

// ---- items of slice s00925770 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace EA {
namespace Trace {
struct C25f30 { void F(int a2, int a3, int a4); };
}
}
// ---- items of slice s00925770 end

// callees this slice defines outside this object (rewrite.py held_callee_protos)
namespace EA { namespace Trace { void* GetDefaultAllocatorX(); }}  // 0x00925cb0 (stays in the slice: not this object's)

// @ 0x00925f30
namespace EA { namespace Trace {
void C25f30::F(int a2, int a3, int a4)
{
    int* p = (int*)this;
    p[1] = a2;
    p[5] = a4;
    p[2] = 0; p[3] = 0; p[4] = 0;
    p[6] = a3;
    *p = 0x0143e104;
    p[7] = 0;
}
}}  // namespace EA::Trace

// @ 0x00926020
namespace EA { namespace Trace {
void* ZoneObject_new(int a1, int a2, int a3)
{
    void* alloc = GetDefaultAllocatorX();
    int* r = (int*)((void* (__thiscall*)(void*, int, int, int, int, int))(*(void***)alloc)[1])
        (alloc, a1 + 8, a2, a3, 4, 0);
    if (r) { *r = (int)alloc; return r + 2; }
    return 0;
}
}}  // namespace EA::Trace

// @ 0x00926060
namespace EA { namespace Trace {
void ZoneObject_delete(void* p)
{
    if (p) {
        void* base = (char*)p - 8;
        ((void (__thiscall*)(void*, int))(*(void***)*(void**)base)[3])(base, 0);
    }
}
}}  // namespace EA::Trace
