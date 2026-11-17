// Setter (0x00bfc470): store the byte argument in the member at +0x80.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_bfc470 {
    char mPad[0x80];
    uint8_t mValue;                             // +0x80
    void SetValue(uint8_t value);
};
#pragma pack(pop)

// @ 0x00bfc470
void Owner_bfc470::SetValue(uint8_t value)
{
    mValue = value;
}
