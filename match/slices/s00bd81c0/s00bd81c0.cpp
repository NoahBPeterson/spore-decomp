// Setter (0x00bd81c0): store the byte argument in the member at +0x33c.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_bd81c0 {
    char mPad[0x33c];
    uint8_t mValue;                             // +0x33c
    void SetValue(uint8_t value);
};
#pragma pack(pop)

// @ 0x00bd81c0
void Owner_bd81c0::SetValue(uint8_t value)
{
    mValue = value;
}
