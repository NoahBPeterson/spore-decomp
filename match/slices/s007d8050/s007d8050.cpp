// Description text (0x007d8050): the command's help text ("Show app mode, Set new app mode, or list all modes [-list]...").
#include "game/types.h"

struct Command_7d8050 {
    const char* GetDescription(int mode) const;
};

// @ 0x007d8050
const char* Command_7d8050::GetDescription(int mode) const
{
    (void)mode;
    return "Show app mode, Set new app mode, or list all modes [-list]";
}
