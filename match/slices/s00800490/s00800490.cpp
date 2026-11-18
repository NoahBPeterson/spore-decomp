// Description text (0x00800490): the command's help text ("cSPUIBehaviorPredicateWinState...").
#include "game/types.h"

struct Command_800490 {
    const char* GetDescription(int mode) const;
};

// @ 0x00800490
const char* Command_800490::GetDescription(int mode) const
{
    (void)mode;
    return "cSPUIBehaviorPredicateWinState";
}
