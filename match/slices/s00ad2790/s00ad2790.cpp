// Setter (0x00ad2790): store the byte argument in the member at +0x76.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_ad2790 {
    char mPad[0x76];
    uint8_t mValue;                             // +0x76
    void SetValue(uint8_t value);
};
#pragma pack(pop)

// @ 0x00ad2790
void Owner_ad2790::SetValue(uint8_t value)
{
    mValue = value;
}
