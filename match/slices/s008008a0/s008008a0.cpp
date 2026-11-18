// Description text (0x008008a0): the command's help text ("cSPUIFrameSequencer...").
#include "game/types.h"

struct Command_8008a0 {
    const char* GetDescription(int mode) const;
};

// @ 0x008008a0
const char* Command_8008a0::GetDescription(int mode) const
{
    (void)mode;
    return "cSPUIFrameSequencer";
}
