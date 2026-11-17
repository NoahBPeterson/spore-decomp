// Setter (0x007eaf20): store the byte argument in the member at +0x38.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_7eaf20 {
    char mPad[0x38];
    uint8_t mValue;                             // +0x38
    void SetValue(uint8_t value);
};
#pragma pack(pop)

// @ 0x007eaf20
void Owner_7eaf20::SetValue(uint8_t value)
{
    mValue = value;
}
