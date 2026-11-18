// Description text (0x0097e590): the command's help text ("InflateEffect...").
#include "game/types.h"

struct Command_97e590 {
    const char* GetDescription(int mode) const;
};

// @ 0x0097e590
const char* Command_97e590::GetDescription(int mode) const
{
    (void)mode;
    return "InflateEffect";
}
