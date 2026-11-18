// Description text (0x00800430): the command's help text ("cSPUIBehaviorWinEventBase...").
#include "game/types.h"

struct Command_800430 {
    const char* GetDescription(int mode) const;
};

// @ 0x00800430
const char* Command_800430::GetDescription(int mode) const
{
    (void)mode;
    return "cSPUIBehaviorWinEventBase";
}
