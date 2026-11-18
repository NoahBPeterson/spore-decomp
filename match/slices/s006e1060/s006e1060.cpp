// Description text (0x006e1060): the command's help text ("vb -<used> dumps information about the RenderWare vertex buf...").
#include "game/types.h"

struct Command_6e1060 {
    const char* GetDescription(int mode) const;
};

// @ 0x006e1060
const char* Command_6e1060::GetDescription(int mode) const
{
    (void)mode;
    return "vb -<used> dumps information about the RenderWare vertex buffer free (or used) lists.";
}
