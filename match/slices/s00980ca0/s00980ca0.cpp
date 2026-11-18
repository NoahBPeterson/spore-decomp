// Description text (0x00980ca0): the command's help text ("RotateEffect...").
#include "game/types.h"

struct Command_980ca0 {
    const char* GetDescription(int mode) const;
};

// @ 0x00980ca0
const char* Command_980ca0::GetDescription(int mode) const
{
    (void)mode;
    return "RotateEffect";
}
