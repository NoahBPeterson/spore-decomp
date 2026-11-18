// Description text (0x008419a0): the command's help text ("Sets a vector2 variable...").
#include "game/types.h"

struct Command_8419a0 {
    const char* GetDescription(int mode) const;
};

// @ 0x008419a0
const char* Command_8419a0::GetDescription(int mode) const
{
    (void)mode;
    return "Sets a vector2 variable";
}
