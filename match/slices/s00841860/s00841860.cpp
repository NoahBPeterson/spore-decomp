// Description text (0x00841860): the command's help text ("Includes the given file, with no error if the file does not ...").
#include "game/types.h"

struct Command_841860 {
    const char* GetDescription(int mode) const;
};

// @ 0x00841860
const char* Command_841860::GetDescription(int mode) const
{
    (void)mode;
    return "Includes the given file, with no error if the file does not exist";
}
