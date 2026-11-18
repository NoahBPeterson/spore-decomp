// Description text (0x00980620): the command's help text ("PerspectiveEffect...").
#include "game/types.h"

struct Command_980620 {
    const char* GetDescription(int mode) const;
};

// @ 0x00980620
const char* Command_980620::GetDescription(int mode) const
{
    (void)mode;
    return "PerspectiveEffect";
}
