// Description text (0x00963ee0): the command's help text ("ButtonDrawableRadio...").
#include "game/types.h"

struct Command_963ee0 {
    const char* GetDescription(int mode) const;
};

// @ 0x00963ee0
const char* Command_963ee0::GetDescription(int mode) const
{
    (void)mode;
    return "ButtonDrawableRadio";
}
