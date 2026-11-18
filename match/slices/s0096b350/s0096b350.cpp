// Description text (0x0096b350): the command's help text ("DialogDrawable...").
#include "game/types.h"

struct Command_96b350 {
    const char* GetDescription(int mode) const;
};

// @ 0x0096b350
const char* Command_96b350::GetDescription(int mode) const
{
    (void)mode;
    return "DialogDrawable";
}
