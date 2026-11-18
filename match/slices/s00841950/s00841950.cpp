// Description text (0x00841950): the command's help text ("Sets a variable with a value restricted to a set of enumerat...").
#include "game/types.h"

struct Command_841950 {
    const char* GetDescription(int mode) const;
};

// @ 0x00841950
const char* Command_841950::GetDescription(int mode) const
{
    (void)mode;
    return "Sets a variable with a value restricted to a set of enumerations";
}
