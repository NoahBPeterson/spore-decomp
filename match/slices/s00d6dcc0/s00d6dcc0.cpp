// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
// Play-fight callback. The pointer sits at 0x0158403c, beside SP::PLAY_FIGHT_Tick.
// Retail loads the creature from the first stack argument and calls cSPCreatureBase::Hover(false).
#include "types.h"

namespace SP {

class cSPCreatureBase {
public:
    bool Hover(bool enable); // 0x00c13a30
};

// @ 0x00d6dcc0
void __cdecl FUN_00d6dcc0(cSPCreatureBase* creature)
{
    creature->Hover(false);
}

}
