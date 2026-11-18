// Description text (0x008411f0): the command's help text ("returns true on a wildcard match....").
#include "game/types.h"

struct Command_8411f0 {
    const char* GetDescription(int mode) const;
};

// @ 0x008411f0
const char* Command_8411f0::GetDescription(int mode) const
{
    (void)mode;
    return "returns true on a wildcard match.";
}
