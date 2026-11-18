// Description text (0x00844850): the command's help text ("Create a definition block up until enddef...").
#include "game/types.h"

struct Command_844850 {
    const char* GetDescription(int mode) const;
};

// @ 0x00844850
const char* Command_844850::GetDescription(int mode) const
{
    (void)mode;
    return "Create a definition block up until enddef";
}
