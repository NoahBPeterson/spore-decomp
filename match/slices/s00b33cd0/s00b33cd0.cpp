// Setter (0x00b33cd0): store the byte argument in the member at +0xc2.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_b33cd0 {
    char mPad[0xc2];
    uint8_t mValue;                             // +0xc2
    void SetValue(uint8_t value);
};
#pragma pack(pop)

// @ 0x00b33cd0
void Owner_b33cd0::SetValue(uint8_t value)
{
    mValue = value;
}
