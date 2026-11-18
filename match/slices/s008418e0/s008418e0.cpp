// Description text (0x008418e0): the command's help text ("Parse the given argument as a command...").
#include "game/types.h"

struct Command_8418e0 {
    const char* GetDescription(int mode) const;
};

// @ 0x008418e0
const char* Command_8418e0::GetDescription(int mode) const
{
    (void)mode;
    return "Parse the given argument as a command";
}
