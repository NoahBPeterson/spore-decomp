// Description text (0x0067aed0): the command's help text ("Remove all hints from the game....").
#include "game/types.h"

struct Command_67aed0 {
    const char* GetDescription(int mode) const;
};

// @ 0x0067aed0
const char* Command_67aed0::GetDescription(int mode) const
{
    (void)mode;
    return "Remove all hints from the game.";
}
