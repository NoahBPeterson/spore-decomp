// Description text (0x0097d1f0): the command's help text ("ImageDrawable...").
#include "game/types.h"

struct Command_97d1f0 {
    const char* GetDescription(int mode) const;
};

// @ 0x0097d1f0
const char* Command_97d1f0::GetDescription(int mode) const
{
    (void)mode;
    return "ImageDrawable";
}
