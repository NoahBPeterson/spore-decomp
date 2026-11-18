// Description text (0x00841870): the command's help text ("end a block...").
#include "game/types.h"

struct Command_841870 {
    const char* GetDescription(int mode) const;
};

// @ 0x00841870
const char* Command_841870::GetDescription(int mode) const
{
    (void)mode;
    return "end a block";
}
