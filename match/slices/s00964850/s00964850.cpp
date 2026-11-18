// Description text (0x00964850): the command's help text ("WinButton...").
#include "game/types.h"

struct Command_964850 {
    const char* GetDescription(int mode) const;
};

// @ 0x00964850
const char* Command_964850::GetDescription(int mode) const
{
    (void)mode;
    return "WinButton";
}
