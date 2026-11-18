// Description text (0x008004c0): the command's help text ("cSPUIBehaviorActionWinInterpolator...").
#include "game/types.h"

struct Command_8004c0 {
    const char* GetDescription(int mode) const;
};

// @ 0x008004c0
const char* Command_8004c0::GetDescription(int mode) const
{
    (void)mode;
    return "cSPUIBehaviorActionWinInterpolator";
}
