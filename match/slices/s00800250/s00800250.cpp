// Description text (0x00800250): the command's help text ("cSPUIMaterialEffect...").
#include "game/types.h"

struct Command_800250 {
    const char* GetDescription(int mode) const;
};

// @ 0x00800250
const char* Command_800250::GetDescription(int mode) const
{
    (void)mode;
    return "cSPUIMaterialEffect";
}
