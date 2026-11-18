// Description text (0x00842b40): the command's help text ("Start a conditional block...").
#include "game/types.h"

struct Command_842b40 {
    const char* GetDescription(int mode) const;
};

// @ 0x00842b40
const char* Command_842b40::GetDescription(int mode) const
{
    (void)mode;
    return "Start a conditional block";
}
