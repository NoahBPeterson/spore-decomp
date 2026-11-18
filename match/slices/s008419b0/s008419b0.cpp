// Description text (0x008419b0): the command's help text ("Sets a vector3 variable...").
#include "game/types.h"

struct Command_8419b0 {
    const char* GetDescription(int mode) const;
};

// @ 0x008419b0
const char* Command_8419b0::GetDescription(int mode) const
{
    (void)mode;
    return "Sets a vector3 variable";
}
