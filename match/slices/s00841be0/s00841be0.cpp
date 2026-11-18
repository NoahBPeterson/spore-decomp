// Description text (0x00841be0): the command's help text ("Set version of the current script...").
#include "game/types.h"

struct Command_841be0 {
    const char* GetDescription(int mode) const;
};

// @ 0x00841be0
const char* Command_841be0::GetDescription(int mode) const
{
    (void)mode;
    return "Set version of the current script";
}
