// src/game/SPAudio/eapdsymbolmanager.cpp -- migrated from slice(s) s009a7810 by tools/migrate/rewrite.py
// Object file: SPAudio/eapdsymbolmanager.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern "C" void FUN_009c8900();

// ---- items of slice s009a7810 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void FUN_009c8900();
// ---- items of slice s009a7810 end

// @ 0x009a80e0
void FUN_009a80e0(int param_1)
{
    if (*(int*)(param_1 + 4) != 0) {
        int local_10;
        int local_c;
        int local_8;
        int param = *(int*)(param_1 + 0x10);
        // eastl hashtable equal_range(&local_10, &param)  -- not reproduced, unresolved helper.
        FUN_009c8900();
        (void)local_10; (void)local_c; (void)local_8;
    }
}
