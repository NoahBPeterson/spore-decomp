// Description text (0x00957840): the command's help text ("Image...").
#include "game/types.h"

struct Command_957840 {
    const char* GetDescription(int mode) const;
};

// @ 0x00957840
const char* Command_957840::GetDescription(int mode) const
{
    (void)mode;
    return "Image";
}
