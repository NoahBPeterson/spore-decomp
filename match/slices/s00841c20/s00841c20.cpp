// Description text (0x00841c20): the command's help text ("output the given string...").
#include "game/types.h"

struct Command_841c20 {
    const char* GetDescription(int mode) const;
};

// @ 0x00841c20
const char* Command_841c20::GetDescription(int mode) const
{
    (void)mode;
    return "output the given string";
}
