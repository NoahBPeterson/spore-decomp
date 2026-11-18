// Description text (0x00841ad0): the command's help text ("Instantiate the given definition...").
#include "game/types.h"

struct Command_841ad0 {
    const char* GetDescription(int mode) const;
};

// @ 0x00841ad0
const char* Command_841ad0::GetDescription(int mode) const
{
    (void)mode;
    return "Instantiate the given definition";
}
