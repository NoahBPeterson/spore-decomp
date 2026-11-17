// Setter (0x007a4a70): store the byte argument in the member at +0x188.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_7a4a70 {
    char mPad[0x188];
    uint8_t mValue;                             // +0x188
    void SetValue(uint8_t value);
};
#pragma pack(pop)

// @ 0x007a4a70
void Owner_7a4a70::SetValue(uint8_t value)
{
    mValue = value;
}
