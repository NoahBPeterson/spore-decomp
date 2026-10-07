// Slice s00c982a0: SP::cTribe::UpdateToolPosition (0x00c987b0, 2445 bytes). PARTIAL.
// Signature from the asm: __thiscall, one stack int (tool type), ret 4, no return value.
// Only the early-exit checks are written; the rest of the body (the 0x9-0xa / 0xb / 0xc / 0xd
// branches, the reservation-grid updates and the float position math) is still missing.
#include "types.h"

namespace SP {
struct cTribe
{
    void UpdateToolPosition(int toolType);
    void* GetToolOfType(int toolType);      // 0x00c8f6e0, thiscall, returns a tool pointer
};
}

void SP::cTribe::UpdateToolPosition(int toolType)
{
    // Fields above +0x2d0 are not in the 2008 PDB; accessed by raw offset.
    uint8_t* self = reinterpret_cast<uint8_t*>(this);
    void* tool = GetToolOfType(toolType);
    if (toolType == 0xd && *reinterpret_cast<int*>(self + 0x260) == 0)
        return;
    if (tool == 0 && toolType != 0xd && toolType != 0xc)
        return;
    // TODO: remaining body, see partial.txt.
}
