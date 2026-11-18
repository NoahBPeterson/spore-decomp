// Description text (0x00841a30): the command's help text ("Purge variable definitions from the given namespace scope...").
#include "game/types.h"

struct Command_841a30 {
    const char* GetDescription(int mode) const;
};

// @ 0x00841a30
const char* Command_841a30::GetDescription(int mode) const
{
    (void)mode;
    return "Purge variable definitions from the given namespace scope";
}
