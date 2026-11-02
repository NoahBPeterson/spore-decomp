// src/game/SPAudio/eapdtable.cpp -- migrated from slice(s) s00a61f50 by tools/migrate/rewrite.py
// Object file: SPAudio/eapdtable.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// callees this slice defines outside this object (rewrite.py held_callee_protos)
bool __cdecl fx_register_sequence();  // 0x00a62410 (stays in the slice: not this object's)
bool __cdecl fx_register_decal();  // 0x00a62720 (stays in the slice: not this object's)
bool __cdecl fx_register_metaparticles();  // 0x00a62a50 (stays in the slice: not this object's)
bool __cdecl fx_register_sound();  // 0x00a62ba0 (stays in the slice: not this object's)
bool __cdecl fx_register_core();  // 0x00a62cc0 (stays in the slice: not this object's)

// @ 0x00a62e90
bool __cdecl fx_register_all()
{
    bool ok = fx_register_core();
    ok &= fx_register_sequence();
    ok &= fx_register_decal();
    ok &= fx_register_metaparticles();
    bool last = fx_register_sound();
    return last & ok;
}
