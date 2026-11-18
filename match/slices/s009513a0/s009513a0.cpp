// Description text (0x009513a0): the command's help text ("AnimationPath2D...").
#include "game/types.h"

struct Command_9513a0 {
    const char* GetDescription(int mode) const;
};

// @ 0x009513a0
const char* Command_9513a0::GetDescription(int mode) const
{
    (void)mode;
    return "AnimationPath2D";
}
