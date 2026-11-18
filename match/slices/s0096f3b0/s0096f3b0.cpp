// Description text (0x0096f3b0): the command's help text ("FrameDrawable...").
#include "game/types.h"

struct Command_96f3b0 {
    const char* GetDescription(int mode) const;
};

// @ 0x0096f3b0
const char* Command_96f3b0::GetDescription(int mode) const
{
    (void)mode;
    return "FrameDrawable";
}
