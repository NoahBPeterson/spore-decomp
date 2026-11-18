// Description text (0x008003d0): the command's help text ("cSPUILayoutZoom...").
#include "game/types.h"

struct Command_8003d0 {
    const char* GetDescription(int mode) const;
};

// @ 0x008003d0
const char* Command_8003d0::GetDescription(int mode) const
{
    (void)mode;
    return "cSPUILayoutZoom";
}
