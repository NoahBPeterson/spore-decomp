// Description text (0x0096ffc0): the command's help text ("GlideEffect...").
#include "game/types.h"

struct Command_96ffc0 {
    const char* GetDescription(int mode) const;
};

// @ 0x0096ffc0
const char* Command_96ffc0::GetDescription(int mode) const
{
    (void)mode;
    return "GlideEffect";
}
