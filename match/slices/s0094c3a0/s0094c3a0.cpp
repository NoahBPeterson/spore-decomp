// Setter (0x0094c3a0): store the byte argument in the member at +0x1c4.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_94c3a0 {
    char mPad[0x1c4];
    uint8_t mValue;                             // +0x1c4
    void SetValue(uint8_t value);
};
#pragma pack(pop)

// @ 0x0094c3a0
void Owner_94c3a0::SetValue(uint8_t value)
{
    mValue = value;
}
