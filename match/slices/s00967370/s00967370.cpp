// Description text (0x00967370): the command's help text ("CascadeEffect...").
#include "game/types.h"

struct Command_967370 {
    const char* GetDescription(int mode) const;
};

// @ 0x00967370
const char* Command_967370::GetDescription(int mode) const
{
    (void)mode;
    return "CascadeEffect";
}
