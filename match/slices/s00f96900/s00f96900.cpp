// Setter (0x00f96900): store the byte argument in the member at +0x4f5.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_f96900 {
    char mPad[0x4f5];
    uint8_t mValue;                             // +0x4f5
    void SetValue(uint8_t value);
};
#pragma pack(pop)

// @ 0x00f96900
void Owner_f96900::SetValue(uint8_t value)
{
    mValue = value;
}
