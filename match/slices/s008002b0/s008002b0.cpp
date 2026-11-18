// Description text (0x008002b0): the command's help text ("cSPUIMaterialWinProc...").
#include "game/types.h"

struct Command_8002b0 {
    const char* GetDescription(int mode) const;
};

// @ 0x008002b0
const char* Command_8002b0::GetDescription(int mode) const
{
    (void)mode;
    return "cSPUIMaterialWinProc";
}
