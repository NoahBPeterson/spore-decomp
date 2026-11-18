// Description text (0x00800370): the command's help text ("cSPUIStdDrawable...").
#include "game/types.h"

struct Command_800370 {
    const char* GetDescription(int mode) const;
};

// @ 0x00800370
const char* Command_800370::GetDescription(int mode) const
{
    (void)mode;
    return "cSPUIStdDrawable";
}
