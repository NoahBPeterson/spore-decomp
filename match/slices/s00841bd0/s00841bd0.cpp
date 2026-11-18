// Description text (0x00841bd0): the command's help text ("Output the arguments of this command...").
#include "game/types.h"

struct Command_841bd0 {
    const char* GetDescription(int mode) const;
};

// @ 0x00841bd0
const char* Command_841bd0::GetDescription(int mode) const
{
    (void)mode;
    return "Output the arguments of this command";
}
