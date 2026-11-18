// Description text (0x008004f0): the command's help text ("cSPUIBehaviorActionWinState...").
#include "game/types.h"

struct Command_8004f0 {
    const char* GetDescription(int mode) const;
};

// @ 0x008004f0
const char* Command_8004f0::GetDescription(int mode) const
{
    (void)mode;
    return "cSPUIBehaviorActionWinState";
}
