// Description text (0x008003a0): the command's help text ("cSPUIVariableWidthDrawable...").
#include "game/types.h"

struct Command_8003a0 {
    const char* GetDescription(int mode) const;
};

// @ 0x008003a0
const char* Command_8003a0::GetDescription(int mode) const
{
    (void)mode;
    return "cSPUIVariableWidthDrawable";
}
