// Description text (0x007e1610): the command's help text ("returns true if the given definition exists...").
#include "game/types.h"

struct Command_7e1610 {
    const char* GetDescription(int mode) const;
};

// @ 0x007e1610
const char* Command_7e1610::GetDescription(int mode) const
{
    (void)mode;
    return "returns true if the given definition exists";
}
