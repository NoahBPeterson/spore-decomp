// Setter (0x00b2fb80): store the byte argument in the member at +0x150.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_b2fb80 {
    char mPad[0x150];
    uint8_t mValue;                             // +0x150
    void SetValue(uint8_t value);
};
#pragma pack(pop)

// @ 0x00b2fb80
void Owner_b2fb80::SetValue(uint8_t value)
{
    mValue = value;
}
