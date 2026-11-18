// Description text (0x00980200): the command's help text ("ModulateEffect...").
#include "game/types.h"

struct Command_980200 {
    const char* GetDescription(int mode) const;
};

// @ 0x00980200
const char* Command_980200::GetDescription(int mode) const
{
    (void)mode;
    return "ModulateEffect";
}
