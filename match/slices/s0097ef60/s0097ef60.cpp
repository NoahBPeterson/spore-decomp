// Description text (0x0097ef60): the command's help text ("WinMessageBox...").
#include "game/types.h"

struct Command_97ef60 {
    const char* GetDescription(int mode) const;
};

// @ 0x0097ef60
const char* Command_97ef60::GetDescription(int mode) const
{
    (void)mode;
    return "WinMessageBox";
}
