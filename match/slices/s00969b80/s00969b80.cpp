// Description text (0x00969b80): the command's help text ("ConsoleWindow...").
#include "game/types.h"

struct Command_969b80 {
    const char* GetDescription(int mode) const;
};

// @ 0x00969b80
const char* Command_969b80::GetDescription(int mode) const
{
    (void)mode;
    return "ConsoleWindow";
}
