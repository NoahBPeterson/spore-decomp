// Description text (0x0096bcc0): the command's help text ("WinDialog...").
#include "game/types.h"

struct Command_96bcc0 {
    const char* GetDescription(int mode) const;
};

// @ 0x0096bcc0
const char* Command_96bcc0::GetDescription(int mode) const
{
    (void)mode;
    return "WinDialog";
}
