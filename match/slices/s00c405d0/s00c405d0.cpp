// Setter (0x00c405d0): store the byte argument in the member at +0x23c.
#include "game/types.h"

#pragma pack(push, 1)
struct Owner_c405d0 {
    char mPad[0x23c];
    uint8_t mValue;                             // +0x23c
    void SetValue(uint8_t value);
};
#pragma pack(pop)

// @ 0x00c405d0
void Owner_c405d0::SetValue(uint8_t value)
{
    mValue = value;
}
