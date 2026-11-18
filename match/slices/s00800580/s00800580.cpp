// Description text (0x00800580): the command's help text ("cSPUIBehaviorTimeFunctionDampedPeriodic...").
#include "game/types.h"

struct Command_800580 {
    const char* GetDescription(int mode) const;
};

// @ 0x00800580
const char* Command_800580::GetDescription(int mode) const
{
    (void)mode;
    return "cSPUIBehaviorTimeFunctionDampedPeriodic";
}
