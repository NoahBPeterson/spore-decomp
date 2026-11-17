// Setter (0x0059ac50): store the byte argument in the member at +0x54.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_59ac50 {
    char mPad[0x54];
    uint8_t mValue;                             // +0x54
    void SetValue(uint8_t value);
};
#pragma pack(pop)

// @ 0x0059ac50
void Owner_59ac50::SetValue(uint8_t value)
{
    mValue = value;
}
