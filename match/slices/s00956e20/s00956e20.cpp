// Description text (0x00956e20): the command's help text ("Window...").
#include "game/types.h"

struct Command_956e20 {
    const char* GetDescription(int mode) const;
};

// @ 0x00956e20
const char* Command_956e20::GetDescription(int mode) const
{
    (void)mode;
    return "Window";
}
