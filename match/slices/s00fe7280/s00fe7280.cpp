// Setter (0x00fe7280): store the byte argument in the member at +0x28.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_fe7280 {
    char mPad[0x28];
    uint8_t mValue;                             // +0x28
    void SetValue(uint8_t value);
};
#pragma pack(pop)

// @ 0x00fe7280
void Owner_fe7280::SetValue(uint8_t value)
{
    mValue = value;
}
