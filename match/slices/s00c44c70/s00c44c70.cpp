// Flags: /O2 /MD /Gy /TP /GS-
#include "types.h"
#include "../../../src/game/include/SP/eMissionState.h"

namespace SP {

class cSPMission {
public:
    uint32_t mUnknown000[0x84 / sizeof(uint32_t)];
    eMissionState mState;

    eMissionState GetState() const;
};

// @ 0x00c44c70
eMissionState cSPMission::GetState() const
{
    return mState;
}

}
