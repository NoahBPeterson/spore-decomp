// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
// Play-fight callback beside 0x00d6dcc0. Retail calls Simulator_cCreatureBase::CountValid
// and returns 0.0f when the count is positive, otherwise 1.0f.
#include "types.h"

class Simulator_cCreatureBase {
public:
    int CountValid(); // 0x00c0f570
};

// @ 0x00d6dcd0
float __cdecl FUN_00d6dcd0(Simulator_cCreatureBase* creature)
{
    if (creature->CountValid() > 0)
        return 0.0f;
    return 1.0f;
}
