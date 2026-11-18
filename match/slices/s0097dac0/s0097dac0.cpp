// Description text (0x0097dac0): the command's help text ("ImageCursorProvider...").
#include "game/types.h"

struct Command_97dac0 {
    const char* GetDescription(int mode) const;
};

// @ 0x0097dac0
const char* Command_97dac0::GetDescription(int mode) const
{
    (void)mode;
    return "ImageCursorProvider";
}
