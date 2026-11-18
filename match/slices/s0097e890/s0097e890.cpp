// Description text (0x0097e890): the command's help text ("SimpleLayout...").
#include "game/types.h"

struct Command_97e890 {
    const char* GetDescription(int mode) const;
};

// @ 0x0097e890
const char* Command_97e890::GetDescription(int mode) const
{
    (void)mode;
    return "SimpleLayout";
}
