// Description text (0x00800310): the command's help text ("cSPUITextWin...").
#include "game/types.h"

struct Command_800310 {
    const char* GetDescription(int mode) const;
};

// @ 0x00800310
const char* Command_800310::GetDescription(int mode) const
{
    (void)mode;
    return "cSPUITextWin";
}
