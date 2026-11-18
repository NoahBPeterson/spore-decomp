// Description text (0x00841110): the command's help text ("returns true if the given command exists...").
#include "game/types.h"

struct Command_841110 {
    const char* GetDescription(int mode) const;
};

// @ 0x00841110
const char* Command_841110::GetDescription(int mode) const
{
    (void)mode;
    return "returns true if the given command exists";
}
