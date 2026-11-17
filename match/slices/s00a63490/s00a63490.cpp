// Setter (0x00a63490): store the dword argument in the member at +0x58.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_a63490 {
    char mPad[0x58];
    uint32_t mValue;                             // +0x58
    void SetValue(uint32_t value);
};
#pragma pack(pop)

// @ 0x00a63490
void Owner_a63490::SetValue(uint32_t value)
{
    mValue = value;
}
