// Description text (0x008001f0): the command's help text ("cSPUIRotateEffect...").
#include "game/types.h"

struct Command_8001f0 {
    const char* GetDescription(int mode) const;
};

// @ 0x008001f0
const char* Command_8001f0::GetDescription(int mode) const
{
    (void)mode;
    return "cSPUIRotateEffect";
}
