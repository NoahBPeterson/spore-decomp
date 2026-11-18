// Description text (0x008005b0): the command's help text ("cSPUIBehaviorWinInterpolatorShadeColor...").
#include "game/types.h"

struct Command_8005b0 {
    const char* GetDescription(int mode) const;
};

// @ 0x008005b0
const char* Command_8005b0::GetDescription(int mode) const
{
    (void)mode;
    return "cSPUIBehaviorWinInterpolatorShadeColor";
}
