// Setter (0x008f28f0): store the dword argument in the member at +0x248.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_8f28f0 {
    char mPad[0x248];
    uint32_t mValue;                             // +0x248
    void SetValue(uint32_t value);
};
#pragma pack(pop)

// @ 0x008f28f0
void Owner_8f28f0::SetValue(uint32_t value)
{
    mValue = value;
}
