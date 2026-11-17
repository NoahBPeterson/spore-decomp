// Setter (0x00cf7470): store the byte argument in the member at +0xf0.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_cf7470 {
    char mPad[0xf0];
    uint8_t mValue;                             // +0xf0
    void SetValue(uint8_t value);
};
#pragma pack(pop)

// @ 0x00cf7470
void Owner_cf7470::SetValue(uint8_t value)
{
    mValue = value;
}
