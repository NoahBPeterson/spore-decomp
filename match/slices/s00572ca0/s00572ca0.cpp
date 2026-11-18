// Description text (0x00572ca0): the command's help text ("increases your DNA points ...").
#include "game/types.h"

struct Command_572ca0 {
    const char* GetDescription(int mode) const;
};

// @ 0x00572ca0
const char* Command_572ca0::GetDescription(int mode) const
{
    (void)mode;
    return "increases your DNA points\n";
}
