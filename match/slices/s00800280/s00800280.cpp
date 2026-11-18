// Description text (0x00800280): the command's help text ("cSPUILayerIdWinProc...").
#include "game/types.h"

struct Command_800280 {
    const char* GetDescription(int mode) const;
};

// @ 0x00800280
const char* Command_800280::GetDescription(int mode) const
{
    (void)mode;
    return "cSPUILayerIdWinProc";
}
