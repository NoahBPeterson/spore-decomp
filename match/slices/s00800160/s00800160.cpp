// Description text (0x00800160): the command's help text ("cSPUIProgressBarGradientWin...").
#include "game/types.h"

struct Command_800160 {
    const char* GetDescription(int mode) const;
};

// @ 0x00800160
const char* Command_800160::GetDescription(int mode) const
{
    (void)mode;
    return "cSPUIProgressBarGradientWin";
}
