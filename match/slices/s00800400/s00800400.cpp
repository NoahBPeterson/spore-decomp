// Description text (0x00800400): the command's help text ("cSPUIBehaviorEventBase...").
#include "game/types.h"

struct Command_800400 {
    const char* GetDescription(int mode) const;
};

// @ 0x00800400
const char* Command_800400::GetDescription(int mode) const
{
    (void)mode;
    return "cSPUIBehaviorEventBase";
}
