// Setter (0x008f2c90): store the dword argument in the member at +0x3a8.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_8f2c90 {
    char mPad[0x3a8];
    uint32_t mValue;                             // +0x3a8
    void SetValue(uint32_t value);
};
#pragma pack(pop)

// @ 0x008f2c90
void Owner_8f2c90::SetValue(uint32_t value)
{
    mValue = value;
}
