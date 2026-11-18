// Description text (0x00800460): the command's help text ("cSPUIBehaviorWinBoolStateEvent...").
#include "game/types.h"

struct Command_800460 {
    const char* GetDescription(int mode) const;
};

// @ 0x00800460
const char* Command_800460::GetDescription(int mode) const
{
    (void)mode;
    return "cSPUIBehaviorWinBoolStateEvent";
}
