// Setter (0x00985db0): store the dword argument in the member at +0x10.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_985db0 {
    char mPad[0x10];
    uint32_t mValue;                             // +0x10
    void SetValue(uint32_t value);
};
#pragma pack(pop)

// @ 0x00985db0
void Owner_985db0::SetValue(uint32_t value)
{
    mValue = value;
}
