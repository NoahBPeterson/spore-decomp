// Setter (0x0083f670): store the byte argument in the member at +0x29.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_83f670 {
    char mPad[0x29];
    uint8_t mValue;                             // +0x29
    void SetValue(uint8_t value);
};
#pragma pack(pop)

// @ 0x0083f670
void Owner_83f670::SetValue(uint8_t value)
{
    mValue = value;
}
