// Description text (0x00841a20): the command's help text ("Begins a new namespace scope...").
#include "game/types.h"

struct Command_841a20 {
    const char* GetDescription(int mode) const;
};

// @ 0x00841a20
const char* Command_841a20::GetDescription(int mode) const
{
    (void)mode;
    return "Begins a new namespace scope";
}
