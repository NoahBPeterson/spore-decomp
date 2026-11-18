// Description text (0x009680e0): the command's help text ("WinComboBox...").
#include "game/types.h"

struct Command_9680e0 {
    const char* GetDescription(int mode) const;
};

// @ 0x009680e0
const char* Command_9680e0::GetDescription(int mode) const
{
    (void)mode;
    return "WinComboBox";
}
