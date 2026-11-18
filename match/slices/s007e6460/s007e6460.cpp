// Description text (0x007e6460): the command's help text ("Quit game...").
#include "game/types.h"

struct Command_7e6460 {
    const char* GetDescription(int mode) const;
};

// @ 0x007e6460
const char* Command_7e6460::GetDescription(int mode) const
{
    (void)mode;
    return "Quit game";
}
