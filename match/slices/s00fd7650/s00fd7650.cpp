// Setter (0x00fd7650): store the byte argument in the member at +0xa1.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_fd7650 {
    char mPad[0xa1];
    uint8_t mValue;                             // +0xa1
    void SetValue(uint8_t value);
};
#pragma pack(pop)

// @ 0x00fd7650
void Owner_fd7650::SetValue(uint8_t value)
{
    mValue = value;
}
