// Slice s00d6dcc0: the MATE_LEAD helper that clears a creature's hover mode.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast /GS-
#include "types.h"

struct Creature {
    bool Hover(int on);                         // 0x00c13a30
};

// @ 0x00d6dcc0
bool FUN_00d6dcc0(Creature* creature) {
    return creature->Hover(0);
}
