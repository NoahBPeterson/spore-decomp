// Description text (0x008000d0): the command's help text ("cSPUILaunchScreenWinProc...").
#include "game/types.h"

struct Command_8000d0 {
    const char* GetDescription(int mode) const;
};

// @ 0x008000d0
const char* Command_8000d0::GetDescription(int mode) const
{
    (void)mode;
    return "cSPUILaunchScreenWinProc";
}
