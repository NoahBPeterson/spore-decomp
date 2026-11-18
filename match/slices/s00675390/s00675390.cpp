// Description text (0x00675390): the command's help text ("achievement_test [-give <guid>] || [[-guid <accumulator guid...").
#include "game/types.h"

struct Command_675390 {
    const char* GetDescription(int mode) const;
};

// @ 0x00675390
const char* Command_675390::GetDescription(int mode) const
{
    (void)mode;
    return "achievement_test [-give <guid>] || [[-guid <accumulator guid>] [-bits <bitfield>]] || [-cheater] || -ui";
}
