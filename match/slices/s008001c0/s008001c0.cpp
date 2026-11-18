// Description text (0x008001c0): the command's help text ("cSPUIPopupMenuWin...").
#include "game/types.h"

struct Command_8001c0 {
    const char* GetDescription(int mode) const;
};

// @ 0x008001c0
const char* Command_8001c0::GetDescription(int mode) const
{
    (void)mode;
    return "cSPUIPopupMenuWin";
}
