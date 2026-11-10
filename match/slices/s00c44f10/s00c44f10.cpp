// Flags: /O2 /MD /Gy /TP /GS-
#include "types.h"
#include "../../../src/game/include/SP/ePlanetClueType.h"

namespace SP {

class cSPMission {
public:
    uint32_t mUnknown000[0xf4 / sizeof(uint32_t)];
    ePlanetClueType mPlanetClueType;

    ePlanetClueType GetPlanetClueType() const;
};

// @ 0x00c44f10
ePlanetClueType cSPMission::GetPlanetClueType() const
{
    return mPlanetClueType;
}

}
