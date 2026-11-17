// Setter (0x00bd83b0): store the byte argument in the member at +0x80c.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_bd83b0 {
    char mPad[0x80c];
    uint8_t mValue;                             // +0x80c
    void SetValue(uint8_t value);
};
#pragma pack(pop)

// @ 0x00bd83b0
void Owner_bd83b0::SetValue(uint8_t value)
{
    mValue = value;
}
