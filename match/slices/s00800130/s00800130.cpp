// Description text (0x00800130): the command's help text ("cSPUIProgressBarWin...").
#include "game/types.h"

struct Command_800130 {
    const char* GetDescription(int mode) const;
};

// @ 0x00800130
const char* Command_800130::GetDescription(int mode) const
{
    (void)mode;
    return "cSPUIProgressBarWin";
}
