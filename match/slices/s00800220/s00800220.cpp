// Description text (0x00800220): the command's help text ("cSPUISwarmEffect...").
#include "game/types.h"

struct Command_800220 {
    const char* GetDescription(int mode) const;
};

// @ 0x00800220
const char* Command_800220::GetDescription(int mode) const
{
    (void)mode;
    return "cSPUISwarmEffect";
}
