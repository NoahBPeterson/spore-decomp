// Setter (0x0080d7d0): store the byte argument in the member at +0x78.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_80d7d0 {
    char mPad[0x78];
    uint8_t mValue;                             // +0x78
    void SetValue(uint8_t value);
};
#pragma pack(pop)

// @ 0x0080d7d0
void Owner_80d7d0::SetValue(uint8_t value)
{
    mValue = value;
}
