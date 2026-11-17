// Setter (0x00feba80): store the byte argument in the member at +0x18.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_feba80 {
    char mPad[0x18];
    uint8_t mValue;                             // +0x18
    void SetValue(uint8_t value);
};
#pragma pack(pop)

// @ 0x00feba80
void Owner_feba80::SetValue(uint8_t value)
{
    mValue = value;
}
