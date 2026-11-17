// Setter (0x007dbd50): store the byte argument in the member at +0x1b0.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_7dbd50 {
    char mPad[0x1b0];
    uint8_t mValue;                             // +0x1b0
    void SetValue(uint8_t value);
};
#pragma pack(pop)

// @ 0x007dbd50
void Owner_7dbd50::SetValue(uint8_t value)
{
    mValue = value;
}
