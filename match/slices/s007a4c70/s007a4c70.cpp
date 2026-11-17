// Setter (0x007a4c70): store the byte argument in the member at +0x169.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_7a4c70 {
    char mPad[0x169];
    uint8_t mValue;                             // +0x169
    void SetValue(uint8_t value);
};
#pragma pack(pop)

// @ 0x007a4c70
void Owner_7a4c70::SetValue(uint8_t value)
{
    mValue = value;
}
