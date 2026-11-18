// Description text (0x008005e0): the command's help text ("cSPUIBehaviorWinInterpolatorScale...").
#include "game/types.h"

struct Command_8005e0 {
    const char* GetDescription(int mode) const;
};

// @ 0x008005e0
const char* Command_8005e0::GetDescription(int mode) const
{
    (void)mode;
    return "cSPUIBehaviorWinInterpolatorScale";
}
