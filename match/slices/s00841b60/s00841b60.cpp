// Description text (0x00841b60): the command's help text ("instantiate the named definition a given number of times...").
#include "game/types.h"

struct Command_841b60 {
    const char* GetDescription(int mode) const;
};

// @ 0x00841b60
const char* Command_841b60::GetDescription(int mode) const
{
    (void)mode;
    return "instantiate the named definition a given number of times";
}
