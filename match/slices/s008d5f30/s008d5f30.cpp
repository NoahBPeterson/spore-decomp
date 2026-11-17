// Setter (0x008d5f30): store the dword argument in the member at +0xb4.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_8d5f30 {
    char mPad[0xb4];
    uint32_t mValue;                             // +0xb4
    void SetValue(uint32_t value);
};
#pragma pack(pop)

// @ 0x008d5f30
void Owner_8d5f30::SetValue(uint32_t value)
{
    mValue = value;
}
