// Description text (0x00800550): the command's help text ("cSPUIBehaviorTimeFunctionSmoothRamp...").
#include "game/types.h"

struct Command_800550 {
    const char* GetDescription(int mode) const;
};

// @ 0x00800550
const char* Command_800550::GetDescription(int mode) const
{
    (void)mode;
    return "cSPUIBehaviorTimeFunctionSmoothRamp";
}
