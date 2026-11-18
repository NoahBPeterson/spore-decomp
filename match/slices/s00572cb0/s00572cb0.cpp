// Description text (0x00572cb0): the command's help text ("toggle the background on/off in the editors (use with Ctrl-H...").
#include "game/types.h"

struct Command_572cb0 {
    const char* GetDescription(int mode) const;
};

// @ 0x00572cb0
const char* Command_572cb0::GetDescription(int mode) const
{
    (void)mode;
    return "toggle the background on/off in the editors (use with Ctrl-H for taking screen shots)\n";
}
