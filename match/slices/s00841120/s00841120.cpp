// Description text (0x00841120): the command's help text ("returns minimum accepted script version....").
#include "game/types.h"

struct Command_841120 {
    const char* GetDescription(int mode) const;
};

// @ 0x00841120
const char* Command_841120::GetDescription(int mode) const
{
    (void)mode;
    return "returns minimum accepted script version.";
}
