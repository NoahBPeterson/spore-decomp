// Setter (0x010882a0): store the dword argument in the member at +0xc0.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_10882a0 {
    char mPad[0xc0];
    uint32_t mValue;                             // +0xc0
    void SetValue(uint32_t value);
};
#pragma pack(pop)

// @ 0x010882a0
void Owner_10882a0::SetValue(uint32_t value)
{
    mValue = value;
}
