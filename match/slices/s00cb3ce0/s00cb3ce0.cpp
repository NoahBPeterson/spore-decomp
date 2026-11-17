// Setter (0x00cb3ce0): store the byte argument in the member at +0x16f.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_cb3ce0 {
    char mPad[0x16f];
    uint8_t mValue;                             // +0x16f
    void SetValue(uint8_t value);
};
#pragma pack(pop)

// @ 0x00cb3ce0
void Owner_cb3ce0::SetValue(uint8_t value)
{
    mValue = value;
}
