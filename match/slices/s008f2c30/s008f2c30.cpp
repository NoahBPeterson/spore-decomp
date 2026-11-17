// Setter (0x008f2c30): store the dword argument in the member at +0x37c.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_8f2c30 {
    char mPad[0x37c];
    uint32_t mValue;                             // +0x37c
    void SetValue(uint32_t value);
};
#pragma pack(pop)

// @ 0x008f2c30
void Owner_8f2c30::SetValue(uint32_t value)
{
    mValue = value;
}
