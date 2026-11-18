// Description text (0x0096ee70): the command's help text ("ExplicitNavigator...").
#include "game/types.h"

struct Command_96ee70 {
    const char* GetDescription(int mode) const;
};

// @ 0x0096ee70
const char* Command_96ee70::GetDescription(int mode) const
{
    (void)mode;
    return "ExplicitNavigator";
}
