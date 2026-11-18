// Description text (0x008411e0): the command's help text ("string comparison....").
#include "game/types.h"

struct Command_8411e0 {
    const char* GetDescription(int mode) const;
};

// @ 0x008411e0
const char* Command_8411e0::GetDescription(int mode) const
{
    (void)mode;
    return "string comparison.";
}
