// Description text (0x00841180): the command's help text ("returns maximum accepted script version....").
#include "game/types.h"

struct Command_841180 {
    const char* GetDescription(int mode) const;
};

// @ 0x00841180
const char* Command_841180::GetDescription(int mode) const
{
    (void)mode;
    return "returns maximum accepted script version.";
}
