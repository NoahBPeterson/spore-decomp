// Setter (0x00bcd100): store the byte argument in the member at +0x1f4.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_bcd100 {
    char mPad[0x1f4];
    uint8_t mValue;                             // +0x1f4
    void SetValue(uint8_t value);
};
#pragma pack(pop)

// @ 0x00bcd100
void Owner_bcd100::SetValue(uint8_t value)
{
    mValue = value;
}
