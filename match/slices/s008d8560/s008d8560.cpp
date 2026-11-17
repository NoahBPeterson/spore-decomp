// Setter (0x008d8560): store the byte argument in the member at +0x2e0.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_8d8560 {
    char mPad[0x2e0];
    uint8_t mValue;                             // +0x2e0
    void SetValue(uint8_t value);
};
#pragma pack(pop)

// @ 0x008d8560
void Owner_8d8560::SetValue(uint8_t value)
{
    mValue = value;
}
