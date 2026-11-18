// Description text (0x0096f110): the command's help text ("FadeEffect...").
#include "game/types.h"

struct Command_96f110 {
    const char* GetDescription(int mode) const;
};

// @ 0x0096f110
const char* Command_96f110::GetDescription(int mode) const
{
    (void)mode;
    return "FadeEffect";
}
