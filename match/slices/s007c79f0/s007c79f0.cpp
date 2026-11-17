// Setter (0x007c79f0): store the byte argument in the member at +0x62.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_7c79f0 {
    char mPad[0x62];
    uint8_t mValue;                             // +0x62
    void SetValue(uint8_t value);
};
#pragma pack(pop)

// @ 0x007c79f0
void Owner_7c79f0::SetValue(uint8_t value)
{
    mValue = value;
}
