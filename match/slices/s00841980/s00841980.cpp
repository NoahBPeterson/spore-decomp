// Description text (0x00841980): the command's help text ("Sets a variable with a floating point value...").
#include "game/types.h"

struct Command_841980 {
    const char* GetDescription(int mode) const;
};

// @ 0x00841980
const char* Command_841980::GetDescription(int mode) const
{
    (void)mode;
    return "Sets a variable with a floating point value";
}
