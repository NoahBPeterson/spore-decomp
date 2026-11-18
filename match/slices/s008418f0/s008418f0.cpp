// Description text (0x008418f0): the command's help text ("Set the value of a variable...").
#include "game/types.h"

struct Command_8418f0 {
    const char* GetDescription(int mode) const;
};

// @ 0x008418f0
const char* Command_8418f0::GetDescription(int mode) const
{
    (void)mode;
    return "Set the value of a variable";
}
