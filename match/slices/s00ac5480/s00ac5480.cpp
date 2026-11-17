// Setter (0x00ac5480): store the byte argument in the member at +0x8.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_ac5480 {
    char mPad[0x8];
    uint8_t mValue;                             // +0x8
    void SetValue(uint8_t value);
};
#pragma pack(pop)

// @ 0x00ac5480
void Owner_ac5480::SetValue(uint8_t value)
{
    mValue = value;
}
