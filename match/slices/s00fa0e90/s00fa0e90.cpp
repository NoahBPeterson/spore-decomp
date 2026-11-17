// Setter (0x00fa0e90): store the byte argument in the member at +0x8ac.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_fa0e90 {
    char mPad[0x8ac];
    uint8_t mValue;                             // +0x8ac
    void SetValue(uint8_t value);
};
#pragma pack(pop)

// @ 0x00fa0e90
void Owner_fa0e90::SetValue(uint8_t value)
{
    mValue = value;
}
