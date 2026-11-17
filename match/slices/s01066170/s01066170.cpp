// Setter (0x01066170): store the byte argument in the member at +0x5d5.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_1066170 {
    char mPad[0x5d5];
    uint8_t mValue;                             // +0x5d5
    void SetValue(uint8_t value);
};
#pragma pack(pop)

// @ 0x01066170
void Owner_1066170::SetValue(uint8_t value)
{
    mValue = value;
}
