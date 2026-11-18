// Description text (0x0060d200): the command's help text ("pollen_test <arg>...").
#include "game/types.h"

struct Command_60d200 {
    const char* GetDescription(int mode) const;
};

// @ 0x0060d200
const char* Command_60d200::GetDescription(int mode) const
{
    (void)mode;
    return "pollen_test <arg>";
}
