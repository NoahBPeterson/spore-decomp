// Setter (0x00714300): store the dword argument in the member at +0x14c.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_714300 {
    char mPad[0x14c];
    uint32_t mValue;                             // +0x14c
    void SetValue(uint32_t value);
};
#pragma pack(pop)

// @ 0x00714300
void Owner_714300::SetValue(uint32_t value)
{
    mValue = value;
}
