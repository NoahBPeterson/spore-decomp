// Description text (0x006854d0): the command's help text ("InstalledAddOns parser command...").
#include "game/types.h"

struct Command_6854d0 {
    const char* GetDescription(int mode) const;
};

// @ 0x006854d0
const char* Command_6854d0::GetDescription(int mode) const
{
    (void)mode;
    return "InstalledAddOns parser command";
}
