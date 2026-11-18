// Description text (0x00841970): the command's help text ("Sets a variable with an integer value...").
#include "game/types.h"

struct Command_841970 {
    const char* GetDescription(int mode) const;
};

// @ 0x00841970
const char* Command_841970::GetDescription(int mode) const
{
    (void)mode;
    return "Sets a variable with an integer value";
}
