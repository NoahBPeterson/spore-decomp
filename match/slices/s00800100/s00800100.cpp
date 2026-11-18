// Description text (0x00800100): the command's help text ("cSPUIAnimatedIconWin...").
#include "game/types.h"

struct Command_800100 {
    const char* GetDescription(int mode) const;
};

// @ 0x00800100
const char* Command_800100::GetDescription(int mode) const
{
    (void)mode;
    return "cSPUIAnimatedIconWin";
}
