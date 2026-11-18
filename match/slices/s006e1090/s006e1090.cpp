// Description text (0x006e1090): the command's help text ("vb -<used> dumps information about the RenderWare index buff...").
#include "game/types.h"

struct Command_6e1090 {
    const char* GetDescription(int mode) const;
};

// @ 0x006e1090
const char* Command_6e1090::GetDescription(int mode) const
{
    (void)mode;
    return "vb -<used> dumps information about the RenderWare index buffer free (or used) lists.";
}
