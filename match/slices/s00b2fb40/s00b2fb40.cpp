// Setter (0x00b2fb40): store the byte argument in the member at +0x159.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_b2fb40 {
    char mPad[0x159];
    uint8_t mValue;                             // +0x159
    void SetValue(uint8_t value);
};
#pragma pack(pop)

// @ 0x00b2fb40
void Owner_b2fb40::SetValue(uint8_t value)
{
    mValue = value;
}
