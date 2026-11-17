// Setter (0x00b2fbb0): store the byte argument in the member at +0x158.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_b2fbb0 {
    char mPad[0x158];
    uint8_t mValue;                             // +0x158
    void SetValue(uint8_t value);
};
#pragma pack(pop)

// @ 0x00b2fbb0
void Owner_b2fbb0::SetValue(uint8_t value)
{
    mValue = value;
}
