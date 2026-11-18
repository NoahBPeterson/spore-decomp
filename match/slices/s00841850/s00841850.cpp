// Description text (0x00841850): the command's help text ("Includes the given file...").
#include "game/types.h"

struct Command_841850 {
    const char* GetDescription(int mode) const;
};

// @ 0x00841850
const char* Command_841850::GetDescription(int mode) const
{
    (void)mode;
    return "Includes the given file";
}
