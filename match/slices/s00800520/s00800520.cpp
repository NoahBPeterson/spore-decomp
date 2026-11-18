// Description text (0x00800520): the command's help text ("cSPUIBehaviorTimeFunctionRamp...").
#include "game/types.h"

struct Command_800520 {
    const char* GetDescription(int mode) const;
};

// @ 0x00800520
const char* Command_800520::GetDescription(int mode) const
{
    (void)mode;
    return "cSPUIBehaviorTimeFunctionRamp";
}
