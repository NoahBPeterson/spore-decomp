// src/game/SPGonzago/SPBreakpoints.cpp -- migrated from slice(s) s0041e730 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPBreakpoints.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern "C" long __cdecl _InterlockedIncrement(volatile long*);
extern unsigned g_defaultUInt;   // 0x015d1164
#pragma intrinsic(_InterlockedIncrement)

// ---- items of slice s0041e730 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern unsigned g_defaultUInt;   // 0x015d1164
struct Property {
    char* data; unsigned pad[3]; unsigned short flags; unsigned short type;   // flags 0x10, type 0x12
    void* GetStorage() { if (flags & 0x30) { return data; } else if (type) return this; return 0; }
    bool* GetBool();
    int* GetInt();
    unsigned* GetUInt();
    float* GetFloat();
};
// ---- items of slice s0041e730 end

// @ 0x0041ea00
unsigned* Property::GetUInt()
{
    if (type == 10 || type == 0x10) { return (unsigned*)GetStorage(); }
    return &g_defaultUInt;
}
