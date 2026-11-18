// Description text (0x0097e7c0): the command's help text ("ProportionalLayout...").
#include "game/types.h"

struct Command_97e7c0 {
    const char* GetDescription(int mode) const;
};

// @ 0x0097e7c0
const char* Command_97e7c0::GetDescription(int mode) const
{
    (void)mode;
    return "ProportionalLayout";
}
