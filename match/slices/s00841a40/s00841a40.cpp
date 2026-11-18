// Description text (0x00841a40): the command's help text ("Undefine a previously defined macro...").
#include "game/types.h"

struct Command_841a40 {
    const char* GetDescription(int mode) const;
};

// @ 0x00841a40
const char* Command_841a40::GetDescription(int mode) const
{
    (void)mode;
    return "Undefine a previously defined macro";
}
