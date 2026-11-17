// Setter (0x00b2fb30): store the dword argument in the member at +0x164.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_b2fb30 {
    char mPad[0x164];
    uint32_t mValue;                             // +0x164
    void SetValue(uint32_t value);
};
#pragma pack(pop)

// @ 0x00b2fb30
void Owner_b2fb30::SetValue(uint32_t value)
{
    mValue = value;
}
