// Description text (0x008002e0): the command's help text ("cSPUITooltipWinProc...").
#include "game/types.h"

struct Command_8002e0 {
    const char* GetDescription(int mode) const;
};

// @ 0x008002e0
const char* Command_8002e0::GetDescription(int mode) const
{
    (void)mode;
    return "cSPUITooltipWinProc";
}
