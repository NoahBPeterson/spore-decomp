// Description text (0x00841100): the command's help text ("Returns true if the given variable exists (has a value)...").
#include "game/types.h"

struct Command_841100 {
    const char* GetDescription(int mode) const;
};

// @ 0x00841100
const char* Command_841100::GetDescription(int mode) const
{
    (void)mode;
    return "Returns true if the given variable exists (has a value)";
}
