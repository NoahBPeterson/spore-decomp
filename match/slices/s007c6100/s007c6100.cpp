// Setter (0x007c6100): store the dword argument in the member at +0xb0.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_7c6100 {
    char mPad[0xb0];
    uint32_t mValue;                             // +0xb0
    void SetValue(uint32_t value);
};
#pragma pack(pop)

// @ 0x007c6100
void Owner_7c6100::SetValue(uint32_t value)
{
    mValue = value;
}
