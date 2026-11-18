// Description text (0x00841990): the command's help text ("Sets a variable with a RGB or ARGB color value...").
#include "game/types.h"

struct Command_841990 {
    const char* GetDescription(int mode) const;
};

// @ 0x00841990
const char* Command_841990::GetDescription(int mode) const
{
    (void)mode;
    return "Sets a variable with a RGB or ARGB color value";
}
