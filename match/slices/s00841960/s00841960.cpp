// Description text (0x00841960): the command's help text ("Sets a variable with a boolean value...").
#include "game/types.h"

struct Command_841960 {
    const char* GetDescription(int mode) const;
};

// @ 0x00841960
const char* Command_841960::GetDescription(int mode) const
{
    (void)mode;
    return "Sets a variable with a boolean value";
}
