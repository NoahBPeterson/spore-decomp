// Description text (0x008419c0): the command's help text ("Sets a vector4 variable...").
#include "game/types.h"

struct Command_8419c0 {
    const char* GetDescription(int mode) const;
};

// @ 0x008419c0
const char* Command_8419c0::GetDescription(int mode) const
{
    (void)mode;
    return "Sets a vector4 variable";
}
