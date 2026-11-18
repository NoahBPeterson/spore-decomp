// Description text (0x00572cc0): the command's help text ("Export the current creature as a collada file (.dae) ...").
#include "game/types.h"

struct Command_572cc0 {
    const char* GetDescription(int mode) const;
};

// @ 0x00572cc0
const char* Command_572cc0::GetDescription(int mode) const
{
    (void)mode;
    return "Export the current creature as a collada file (.dae)\n";
}
