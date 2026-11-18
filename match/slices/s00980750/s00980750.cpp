// Description text (0x00980750): the command's help text ("RelativeNavigator...").
#include "game/types.h"

struct Command_980750 {
    const char* GetDescription(int mode) const;
};

// @ 0x00980750
const char* Command_980750::GetDescription(int mode) const
{
    (void)mode;
    return "RelativeNavigator";
}
