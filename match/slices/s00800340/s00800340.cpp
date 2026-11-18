// Description text (0x00800340): the command's help text ("cSPUIStdDrawableImageInfo...").
#include "game/types.h"

struct Command_800340 {
    const char* GetDescription(int mode) const;
};

// @ 0x00800340
const char* Command_800340::GetDescription(int mode) const
{
    (void)mode;
    return "cSPUIStdDrawableImageInfo";
}
