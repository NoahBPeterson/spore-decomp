// Description text (0x00970ce0): the command's help text ("WinGrid...").
#include "game/types.h"

struct Command_970ce0 {
    const char* GetDescription(int mode) const;
};

// @ 0x00970ce0
const char* Command_970ce0::GetDescription(int mode) const
{
    (void)mode;
    return "WinGrid";
}
