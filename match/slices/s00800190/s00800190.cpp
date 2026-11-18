// Description text (0x00800190): the command's help text ("cSPUIPopupMenuItemWin...").
#include "game/types.h"

struct Command_800190 {
    const char* GetDescription(int mode) const;
};

// @ 0x00800190
const char* Command_800190::GetDescription(int mode) const
{
    (void)mode;
    return "cSPUIPopupMenuItemWin";
}
